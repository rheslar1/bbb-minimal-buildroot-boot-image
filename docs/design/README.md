# BBB Minimal Buildroot Boot Image Design Package

## Purpose

BeagleBone Black AM335x project that builds U-Boot, Linux kernel, and a tiny root filesystem with Buildroot for a sub-5-second login prompt.

This package defines the project as an implementation-ready embedded system. It covers system architecture, requirements, interface boundaries, runtime design, validation evidence, and phased delivery.

## Project Profile

| Field | Value |
| --- | --- |
| Repository | `rheslar1/bbb-minimal-buildroot-boot-image` |
| Primary stack | C++17, C++ Design Patterns, SOLID, BeagleBone Black, AM335x, Buildroot, U-Boot, Kernel build, microSD boot |
| Review proof point | Board-specific boot-chain ownership, fast minimal Linux image generation, and clear startup-time evidence. |

## Artifacts

- [System Design](system-design.md)
- [Requirements](requirements.md)
- [Interface Control](interface-control.md)
- [Runtime Design](runtime-design.md)
- [Validation Plan](validation-plan.md)
- [Implementation Roadmap](implementation-roadmap.md)
- [Draw.io UML](diagrams/system-design.drawio)
- [PNG UML](diagrams/system-design.png)
