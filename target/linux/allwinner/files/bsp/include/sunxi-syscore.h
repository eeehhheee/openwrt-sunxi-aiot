/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright(c) 2025 Allwinner Technology Co.,Ltd. All rights reserved.
 */
#ifndef _SUNXI_SYSCORE_H
#define _SUNXI_SYSCORE_H

#include <linux/compiler.h>
#include <linux/version.h>
#include <linux/syscore_ops.h>

/*
 * Linux 6.18 split the syscore registration node out of struct syscore_ops:
 * the callbacks now take a void *data argument and drivers register a
 * separate struct syscore through register_syscore().  Older kernels
 * register the ops table itself through register_syscore_ops() and use
 * callbacks without arguments.
 *
 * The BSP keeps its callbacks in the older, argument-less form so that
 * the same source builds against both APIs:
 *
 *	static struct sunxi_syscore foo = {
 *		.suspend = foo_suspend,
 *		.resume  = foo_resume,
 *	};
 *
 *	sunxi_register_syscore(&foo);
 *	sunxi_unregister_syscore(&foo);
 */

struct sunxi_syscore {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 18, 0)
	struct syscore node;
#else
	struct syscore_ops legacy;
#endif
	int (*suspend)(void);
	void (*resume)(void);
	void (*shutdown)(void);
};

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 18, 0)

static inline int sunxi_syscore_compat_suspend(void *data)
{
	struct sunxi_syscore *sc = data;

	return sc->suspend ? sc->suspend() : 0;
}

static inline void sunxi_syscore_compat_resume(void *data)
{
	struct sunxi_syscore *sc = data;

	if (sc->resume)
		sc->resume();
}

static inline void sunxi_syscore_compat_shutdown(void *data)
{
	struct sunxi_syscore *sc = data;

	if (sc->shutdown)
		sc->shutdown();
}

static const struct syscore_ops sunxi_syscore_compat_ops __maybe_unused = {
	.suspend = sunxi_syscore_compat_suspend,
	.resume = sunxi_syscore_compat_resume,
	.shutdown = sunxi_syscore_compat_shutdown,
};

#define sunxi_register_syscore(sc)				\
	do {							\
		(sc)->node.ops = &sunxi_syscore_compat_ops;	\
		(sc)->node.data = (sc);				\
		register_syscore(&(sc)->node);			\
	} while (0)

#define sunxi_unregister_syscore(sc) unregister_syscore(&(sc)->node)

#else /* LINUX_VERSION_CODE < KERNEL_VERSION(6, 18, 0) */

static inline void sunxi_syscore_fill(struct sunxi_syscore *sc)
{
	sc->legacy.suspend = sc->suspend;
	sc->legacy.resume = sc->resume;
	sc->legacy.shutdown = sc->shutdown;
}

#define sunxi_register_syscore(sc)				\
	do {							\
		sunxi_syscore_fill(sc);				\
		register_syscore_ops(&(sc)->legacy);		\
	} while (0)

#define sunxi_unregister_syscore(sc) unregister_syscore_ops(&(sc)->legacy)

#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(6, 18, 0) */

#endif /* _SUNXI_SYSCORE_H */
