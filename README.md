# BBB Minimal Buildroot Boot Image

BeagleBone Black AM335x project that builds U-Boot, Linux kernel, and a tiny root filesystem with Buildroot for a sub-5-second login prompt.

## Portfolio Purpose

This repository implements a host-testable BeagleBone Black minimal Buildroot boot-image profile. It validates the AM335x boot chain, U-Boot SPL artifacts, kernel/device tree selection, microSD partition layout, BusyBox rootfs, UART login, and sub-5-second login-prompt evidence.

## Stack

- C++17
- C++ Design Patterns
- SOLID
- BeagleBone Black
- AM335x
- Buildroot
- U-Boot
- Kernel build
- microSD boot

## Quick Start

```bash
cmake -S . -B build
cmake --build build
./build/bbb_minimal_buildroot_boot_image
ctest --test-dir build --output-on-failure
```

## Implementation Slices

- BBB AM335x board profile using `am335x-boneblack.dtb`.
- Buildroot defconfig sample for U-Boot SPL, `MLO`, `u-boot.img`, `zImage`, and BusyBox userspace.
- `genimage.cfg` sample for FAT32 boot and ext4 rootfs microSD layout.
- Rootfs overlay with `ttyO0` getty for serial login.
- Boot timing model for SPL, U-Boot, kernel, and rootfs phases.
- CTest coverage for accepted image, wrong device tree, missing MLO placement, oversized rootfs, slow login, and report evidence.

## Evidence Target

Board-specific boot-chain ownership, fast minimal Linux image generation, and clear startup-time evidence.

## Remote

Intended public repository: https://github.com/rheslar1/bbb-minimal-buildroot-boot-image

<!-- cpp17-solid-implementation:start -->
## C++17, Design Patterns, and SOLID Implementation

This repository includes a host-buildable C++17 implementation, not only documentation. The implementation applies:

- Strategy pattern for validation rules.
- Adapter interfaces for input samples and telemetry/reporting.
- Composite validation for combining safety and readiness checks.
- Facade orchestration through the project runtime class.
- SOLID boundaries between profile data, input acquisition, validation, telemetry encoding, and tests.
<!-- cpp17-solid-implementation:end -->

<!-- deep-architecture-links:start -->
## Deep Architecture and UML

- [Deep architecture](docs/deep-architecture.md)
- [Full UML Draw.io source](docs/diagrams/full-system-uml.drawio)
- [Full UML PNG export](docs/diagrams/full-system-uml.png)
<!-- deep-architecture-links:end -->
