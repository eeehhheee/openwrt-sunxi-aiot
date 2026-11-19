/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright(c) 2024 Allwinner Technology Co.,Ltd. All rights reserved.
 *
 * Transmit buffer compatibility helpers for the Allwinner UART drivers.
 *
 * Linux 6.10 removed the struct circ_buf xmit member from struct uart_state,
 * moved the transmit buffer to struct tty_port as an xmit_fifo kfifo and
 * dropped uart_circ_empty()/uart_circ_chars_pending() together with
 * SERIAL_CIRC_CNT_TO_END().  These helpers hide the difference so the vendor
 * driver can stay close to its original shape.
 *
 * The DMA transmit path aliases struct circ_buf.xmit.buf with the DMA bounce
 * buffer, which is impossible once the tty core owns the kfifo; DMA transmit
 * is therefore compiled out on 6.10 and later and the driver falls back to
 * programmed I/O.
 */
#ifndef _SUNXI_UART_COMPAT_H_
#define _SUNXI_UART_COMPAT_H_

#include <linux/kfifo.h>
#include <linux/serial_core.h>
#include <linux/types.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 10, 0)

/* The tty core owns the transmit fifo, the driver cannot alias it. */
#define SUNXI_UART_XMIT_DMA_ALIAS 0

static inline unsigned int sunxi_uart_tx_pending(struct uart_port *port)
{
	return kfifo_len(&port->state->port.xmit_fifo);
}

static inline bool sunxi_uart_tx_empty(struct uart_port *port)
{
	return kfifo_is_empty(&port->state->port.xmit_fifo);
}

static inline bool sunxi_uart_tx_peek(struct uart_port *port, unsigned char *ch)
{
	return kfifo_peek(&port->state->port.xmit_fifo, ch) == 1;
}

/* Consume @chars already pushed into the FIFO and account them. */
static inline void sunxi_uart_tx_advance(struct uart_port *port, unsigned int chars)
{
	uart_xmit_advance(port, chars);
}

#else

#define SUNXI_UART_XMIT_DMA_ALIAS 1

static inline unsigned int sunxi_uart_tx_pending(struct uart_port *port)
{
	return uart_circ_chars_pending(&port->state->xmit);
}

static inline bool sunxi_uart_tx_empty(struct uart_port *port)
{
	return uart_circ_empty(&port->state->xmit);
}

static inline bool sunxi_uart_tx_peek(struct uart_port *port, unsigned char *ch)
{
	struct circ_buf *xmit = &port->state->xmit;

	if (uart_circ_empty(xmit))
		return false;

	*ch = xmit->buf[xmit->tail];

	return true;
}

static inline void sunxi_uart_tx_advance(struct uart_port *port, unsigned int chars)
{
	struct circ_buf *xmit = &port->state->xmit;

	xmit->tail = (xmit->tail + chars) & (UART_XMIT_SIZE - 1);
	port->icount.tx += chars;
}

#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(6, 10, 0) */

#endif /* _SUNXI_UART_COMPAT_H_ */
