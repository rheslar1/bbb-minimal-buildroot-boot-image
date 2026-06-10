# BBB Minimal Buildroot Plan

## Boot Chain

- AM335x ROM loads `MLO` from the FAT boot partition.
- SPL loads `u-boot.img`.
- U-Boot loads `zImage` and `am335x-boneblack.dtb`.
- Kernel mounts a tiny ext4 BusyBox rootfs.
- `ttyO0` getty presents a login prompt at 115200 baud.

## Buildroot Artifacts

- `buildroot/board/rheslar/bbb-minimal/rheslar_bbb_minimal_defconfig`
- `buildroot/board/rheslar/bbb-minimal/genimage.cfg`
- `buildroot/board/rheslar/bbb-minimal/rootfs-overlay/etc/inittab`

The host C++ validator checks the boot-chain assumptions and sub-5-second login target without requiring a full Buildroot checkout in CI.
