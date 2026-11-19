/* SPDX-License-Identifier: GPL-2.0 */
/*
 * platform_driver::remove migration shim.
 *
 * Up to Linux 6.6 struct platform_driver had both .remove (returning int) and
 * .remove_new (returning void).  Linux 6.11 turned .remove into a void
 * callback, kept .remove_new as a deprecated alias, and Linux 6.13 finally
 * dropped .remove_new.  The vendor BSP was written against the 6.6 shape, so
 * every driver callback is converted to return void and the registration site
 * is spelled through this macro, which picks whichever field the kernel under
 * build actually has.
 *
 * Usage:  SUNXI_PLATFORM_REMOVE(ddr_clock_remove),
 */
#ifndef __SUNXI_PLATFORM_H
#define __SUNXI_PLATFORM_H

#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0)
#define SUNXI_PLATFORM_REMOVE(fn)	.remove = fn
#else
#define SUNXI_PLATFORM_REMOVE(fn)	.remove_new = fn
#endif

#endif /* __SUNXI_PLATFORM_H */
