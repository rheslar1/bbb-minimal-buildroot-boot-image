# BBB Minimal Buildroot Boot Image

BeagleBone Black AM335x project that builds U-Boot, Linux kernel, and a tiny root filesystem with Buildroot for a sub-5-second login prompt.

## Portfolio Purpose

This repository is an Embedded Systems project scaffold for the Rheslar portfolio. It is designed to become a hardware-backed project with build output, validation logs, and reviewable implementation evidence.

## Stack

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
python -m unittest discover -s tests
```

## Implementation Slices

- Native starter executable that exposes the project identity, stack, and validation target.
- Architecture document with control boundaries, data flow, safety assumptions, and evidence plan.
- Unit smoke test that keeps source, docs, and CI files present as the repo grows.
- GitHub Actions workflow for configure, build, executable smoke run, and repository validation.

## Evidence Target

Board-specific boot-chain ownership, fast minimal Linux image generation, and clear startup-time evidence.

## Remote

Intended public repository: https://github.com/rheslar1/bbb-minimal-buildroot-boot-image
