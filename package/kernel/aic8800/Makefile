include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=aic8800
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=
PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=HEAD

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define KernelPackage/aic8800
  SUBMENU:=Wireless Drivers
  TITLE:=AIC8800 Wireless Driver
  DEPENDS:=+kmod-mac80211
  FILES:=$(PKG_BUILD_DIR)/aic8800/aic_load_fw/aic_load_fw.ko \
          $(PKG_BUILD_DIR)/aic8800/aic8800_fdrv/aic8800_fdrv.ko
  AUTOLOAD:=$(call AutoLoad,35,aic_load_fw aic8800_fdrv)
endef

define KernelPackage/aic8800/description
  Driver for AIC8800 wireless chipset (USB and SDIO)
endef

EXTRA_KCONFIG:= \
CONFIG_AIC_LOADFW_SUPPORT=m \
CONFIG_AIC8800_WLAN_SUPPORT=m \
CONFIG_SDIO_SUPPORT=y \
CONFIG_PLATFORM_ALLWINNER=y \
CONFIG_RWNX_FULLMAC=y

EXTRA_CFLAGS:= \
-I$(PKG_BUILD_DIR)/aic8800/aic_load_fw \
-I$(PKG_BUILD_DIR)/aic8800/aic8800_fdrv

MAKE_OPTS:= \
ARCH=$(LINUX_KARCH) \
CROSS_COMPILE=$(TARGET_CROSS) \
SUBDIRS=$(PKG_BUILD_DIR)/aic8800 \
CONFIG_AIC_LOADFW_SUPPORT=m \
CONFIG_AIC8800_WLAN_SUPPORT=m \
CONFIG_SDIO_SUPPORT=y \
CONFIG_PLATFORM_ALLWINNER=y \
CONFIG_RWNX_FULLMAC=y \
CONFIG_PLATFORM_UBUNTU=n

define Build/Compile
$(MAKE) -C $(LINUX_DIR) $(MAKE_OPTS) modules
endef

define Build/InstallDev
$(INSTALL_DIR) $(1)/usr/include
endef

$(eval $(call KernelPackage,aic8800))
