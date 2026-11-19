# SPDX-License-Identifier: GPL-2.0
#
# The vendor BSP predates the warning defaults of Linux 6.18, which enables
# -Wextra plus -Wmissing-declarations/-Wmissing-prototypes for every object
# (scripts/Makefile.extrawarn).  The BSP has thousands of non-static helpers
# without a prototype in a header, so those stylistic warnings are switched
# off for the whole BSP subtree.  Diagnostics that guard real breakage
# (-Werror=implicit-function-declaration, -Werror=incompatible-pointer-types,
# -Werror=return-type) stay enabled.
subdir-ccflags-y += -Wno-missing-prototypes
subdir-ccflags-y += -Wno-missing-declarations
subdir-ccflags-y += -Wno-unused-parameter
subdir-ccflags-y += -Wno-sign-compare
subdir-ccflags-y += -Wno-unused-but-set-variable

KBUILD_CFLAGS += -Wno-unused-function

obj-y += drivers/
