# Validation Plan

## Current Host Checks

- CMake configure completes.
- C++17 BBB boot-image validator builds.
- Executable accepts the BeagleBone Black minimal Buildroot boot profile.
- CTest verifies device tree, MLO placement, rootfs size, microSD layout, and login timing.
- GitHub Actions runs configure, build, executable smoke run, and CTest.

## Hardware Evidence To Add

- Buildroot build log and generated image list.
- `genimage` output showing FAT boot and ext4 rootfs partitions.
- BBB serial boot log from AM335x ROM through login prompt.
- Timing evidence for SPL, U-Boot, kernel, and rootfs phases.
- Photo of microSD boot wiring and serial console.
- CI screenshot after the public repository is pushed.

## Project-Specific Evidence Target

Board-specific boot-chain ownership, fast minimal Linux image generation, and clear startup-time evidence.
