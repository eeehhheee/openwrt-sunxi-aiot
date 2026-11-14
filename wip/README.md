# 未接入构建的文件

## patches-6.18-inapplicable/

原 `target/linux/allwinner/patches-6.18/` 中的补丁并非都作用于 Linux 内核：

- `*-uboot-*`、`0102-uboot-*`：U-Boot 源树补丁，路径在 Linux 树中不存在；
- `mesa-*`：Mesa 源码补丁；
- `orangepi-build.patch`、`0300-packaging-armbian-builddeb.patch`：构建系统/打包补丁；
- `0003-disable-uboot-pcie-training.patch`：补丁体损坏（`corrupt patch at line 36`），且其 DTS 改动已由 `target/linux/allwinner/files/` 提供；
- 其余 DP/eDP/BSP 补丁依赖 `bsp/` 私有驱动树，经 `git apply --check` 验证无法应用。

保留的 8 个补丁均已按“先复制 `files/`，再按文件名顺序应用”的流程验证可干净应用。
`0001-allwinner-a733-orangepi-4-pro-6.18-mainline.patch` 已裁剪：只保留驱动与 dt-bindings 部分，
去掉与项目自带 `sun60iw2p1.dtsi`/`sun60iw2p1-cpu-vf.dtsi` 冲突的 OrangePi 板级 DTS 与 DTS Makefile 行。

## patches-6.6-inapplicable/

`0003-disable-uboot-pcie-training.patch`（损坏、重复）、`0004-uboot-pcie-skip-training.patch`（U-Boot API，内核树无此路径）、
`aic8800d80-sdio-eapol-and-header-fix.patch`（内核树无 `drivers/net/wireless/aic8800`）。

## aic8800-pkg/

包本身不可构建：`PKG_SOURCE_URL` 为空、`PKG_SOURCE_PROTO:=git`、`PKG_SOURCE_VERSION:=HEAD`，
且 Kconfig 指向不存在的 `drivers/net/wireless/aic8800/...`。移出 `package/` 以免影响 Kconfig/defconfig，
修复后再移回并启用 `CONFIG_PACKAGE_kmod-aic8800`。
