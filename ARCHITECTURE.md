# BBB Minimal Buildroot Boot Image Architecture

## Goal

Board-specific boot-chain ownership, fast minimal Linux image generation, and clear startup-time evidence.

## Runtime Shape

1. AM335x ROM loads `MLO` from the microSD FAT boot partition.
2. SPL loads `u-boot.img`.
3. U-Boot loads `zImage` and `am335x-boneblack.dtb`.
4. The kernel mounts a tiny ext4 BusyBox rootfs.
5. BusyBox init starts `ttyO0` getty for a serial login prompt.
6. Boot timing evidence tracks SPL, U-Boot, kernel, and rootfs phases against a five-second target.

## C++17 Design Shape

- `BbbBootImageValidator` owns boot-image composition checks.
- `BoardTarget`, `BootChain`, `RootfsProfile`, `PartitionLayout`, and `BootTiming` make the image contract explicit.
- `TextBootImageReporter` emits CI and portfolio evidence.
- Buildroot snippets under `buildroot/` document the actual board defconfig and image layout.

## SOLID Notes

- Single Responsibility: board target, boot chain, rootfs, partition layout, timing, and reporting are separated.
- Open/Closed: alternate BBB boot profiles can be added through data.
- Liskov Substitution: microSD and eMMC layouts can share the same validation model.
- Interface Segregation: each record carries one focused part of the boot image.
- Dependency Inversion: future Buildroot parsers can feed the same validator.

## Boundaries

- `include/bbb_boot/`: BBB boot image model.
- `src/`: validator, reporter, and CLI demo.
- `buildroot/`: sample BBB defconfig, genimage config, and rootfs overlay.
- `docs/`: validation plans, timing notes, hardware captures, and acceptance evidence.
- `tests/`: host-side boot image composition tests.
- `.github/workflows/`: CI entry point for build and validation evidence.

## Validation Plan

- Build the host BBB boot validator with CMake.
- Run the executable and confirm the minimal boot image is accepted.
- Run CTest to validate boot chain, rootfs, partition layout, and timing.
- Add Buildroot build logs and BBB serial boot captures after hardware integration.
- Capture CI, terminal, and hardware evidence for the portfolio detail page.

## Expansion Notes

- Add parsed Buildroot `.config` and generated `sdcard.img` checks.
- Add boot log parser that computes SPL, U-Boot, kernel, and rootfs timing from serial output.
- Add microSD flashing and checksum scripts once hardware evidence is captured.
