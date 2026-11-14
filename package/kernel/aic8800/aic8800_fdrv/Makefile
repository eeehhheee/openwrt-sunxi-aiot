EXTRA_CFLAGS += $(USER_EXTRA_CFLAGS)
EXTRA_CFLAGS += -Wno-implicit-fallthrough

RWNX_VERS_NUM := 6.4.3.0

CONFIG_AIC8800_WLAN_SUPPORT = m
MODULE_NAME = aic8800_fdrv
CONFIG_COUNTRY_CODE = "00"

# Support of bootrom start
CONFIG_START_FROM_BOOTROM = y

# Support of pmic setting
CONFIG_PMIC_SETTING ?=n

# DCDC_VRF mode for Allwinner
CONFIG_VRF_DCDC_MODE = y

# ROM patch enabled option
CONFIG_ROM_PATCH_EN ?=y

# MAC mode configuration
CONFIG_RWNX_SOFTMAC ?= n
CONFIG_RWNX_FULLMAC ?= y
CONFIG_RWNX_FHOST ?= n

# SDIO Support - ENABLED for A7Z/A7A
CONFIG_SDIO_SUPPORT = y

# USB Support - Disabled for embedded use
CONFIG_USB_SUPPORT = n

# Platform configuration
CONFIG_PLATFORM_ROCKCHIP = n
CONFIG_PLATFORM_ALLWINNER = y
CONFIG_PLATFORM_AMLOGIC = n
CONFIG_PLATFORM_HI = n
CONFIG_PLATFORM_UBUNTU = n

# SDIO configuration
ifeq ($(CONFIG_SDIO_SUPPORT), y)
ccflags-y += -DAICWF_SDIO_SUPPORT
endif

# Allwinner platform settings
ifeq ($(CONFIG_PLATFORM_ALLWINNER), y)
ccflags-y += -DAICWF_PLATFORM_ALLWINNER
endif

# Full MAC mode
ifeq ($(CONFIG_RWNX_FULLMAC), y)
ccflags-y += -DAICWF_FULLMAC_AICWF
endif

# Firmware loading support
ccflags-y += -DAICWF_FW_BUILTIN

# Version information
ccflags-y += -DRWNX_VERS_NUM=$(RWNX_VERS_NUM)
ccflags-y += -DAICWF_CONFIG_COUNTRY_CODE=$(CONFIG_COUNTRY_CODE)

# Includes
EXTRA_CFLAGS += -I$(src)

# Source files
$(MODULE_NAME)-$(CONFIG_AIC8800_WLAN_SUPPORT) := aic8800_fdrv.o

$(MODULE_NAME)-$(CONFIG_AIC8800_WLAN_SUPPORT) += rwnx_main.o
$(MODULE_NAME)-$(CONFIG_AIC8800_WLAN_SUPPORT) += rwnx_rx.o
$(MODULE_NAME)-$(CONFIG_AIC8800_WLAN_SUPPORT) += rwnx_tx.o
$(MODULE_NAME)-$(CONFIG_AIC8800_WLAN_SUPPORT) += rwnx_utils.o
$(MODULE_NAME)-$(CONFIG_AIC8800_WLAN_SUPPORT) += rwnx_cmds.o
$(MODULE_NAME)-$(CONFIG_AIC8800_WLAN_SUPPORT) += rwnx_platform.o

# SDIO interface
$(MODULE_NAME)-$(CONFIG_SDIO_SUPPORT) += sdio_host.o
$(MODULE_NAME)-$(CONFIG_SDIO_SUPPORT) += aicwf_txrxif.o
$(MODULE_NAME)-$(CONFIG_SDIO_SUPPORT) += aicwf_sdio.o

# USB interface (disabled)
$(MODULE_NAME)-$(CONFIG_USB_SUPPORT) += aicwf_usb.o

# Common modules
$(MODULE_NAME)-$(CONFIG_AIC8800_WLAN_SUPPORT) += aic_br_ext.o
$(MODULE_NAME)-$(CONFIG_AIC8800_WLAN_SUPPORT) += aic_priv_cmd.o
$(MODULE_NAME)-$(CONFIG_AIC8800_WLAN_SUPPORT) += aic_vendor.o
$(MODULE_NAME)-$(CONFIG_AIC8800_WLAN_SUPPORT) += aicwf_tcp_ack.o

# D80 specific compatibility
$(MODULE_NAME)-$(CONFIG_AIC8800_WLAN_SUPPORT) += aicwf_compat_8800d80.o
$(MODULE_NAME)-$(CONFIG_AIC8800_WLAN_SUPPORT) += aicwf_compat_8800dc.o

# Module definition
obj-$(CONFIG_AIC8800_WLAN_SUPPORT) += $(MODULE_NAME).o

