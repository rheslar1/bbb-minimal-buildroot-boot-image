#include "bbb_boot/BbbBootImage.hpp"

#include <ostream>
#include <utility>

namespace bbb_boot {
namespace {

void addCheck(ImageReport& report,
              std::string step,
              const bool passed,
              std::string detail) {
  report.checks.push_back(
      ImageCheck{std::move(step),
                 passed ? CheckStatus::Pass : CheckStatus::Fail,
                 std::move(detail)});
}

std::uint32_t totalBootMs(const BootTiming& timing) {
  return timing.splMs + timing.ubootMs + timing.kernelMs + timing.rootfsMs;
}

bool validateTarget(const BoardTarget& target, std::string& reason) {
  if (target.board != "BeagleBone Black" || target.soc != "AM335x") {
    reason = "target must be BeagleBone Black AM335x";
    return false;
  }

  if (target.defconfig.empty() || target.deviceTree != "am335x-boneblack.dtb") {
    reason = "BBB Buildroot defconfig and am335x-boneblack.dtb are required";
    return false;
  }

  if (!target.microSdBoot) {
    reason = "microSD boot must be enabled";
    return false;
  }

  reason = target.board + " " + target.soc + " with " + target.defconfig;
  return true;
}

bool validateBootChain(const BootChain& bootChain, std::string& reason) {
  if (bootChain.spl != "MLO" || bootChain.uboot != "u-boot.img") {
    reason = "AM335x ROM expects MLO followed by u-boot.img";
    return false;
  }

  if (bootChain.kernelImage != "zImage") {
    reason = "BBB minimal image expects zImage";
    return false;
  }

  if (!bootChain.mloFirstSector || !bootChain.bootEnvUsesUart0) {
    reason = "MLO placement and UART0 bootargs are required";
    return false;
  }

  reason = "MLO, u-boot.img, zImage, and UART0 bootargs configured";
  return true;
}

bool validateRootfs(const RootfsProfile& rootfs, std::string& reason) {
  if (rootfs.initSystem != "busybox-init") {
    reason = "minimal BBB image should use busybox-init";
    return false;
  }

  if (rootfs.sizeMiB == 0U || rootfs.sizeMiB > 64U) {
    reason = "rootfs must be tiny and <= 64 MiB";
    return false;
  }

  if (!rootfs.busyboxOnly || !rootfs.sshDisabled || !rootfs.gettyOnTtyO0) {
    reason = "rootfs requires BusyBox-only userspace, no SSH, and ttyO0 getty";
    return false;
  }

  reason = "BusyBox rootfs " + std::to_string(rootfs.sizeMiB) +
           " MiB with ttyO0 login";
  return true;
}

bool validateLayout(const PartitionLayout& layout, std::string& reason) {
  if (layout.bootFs != "FAT32" || layout.rootFs != "ext4") {
    reason = "microSD must use FAT32 boot and ext4 root partitions";
    return false;
  }

  if (layout.bootMiB < 64U || layout.rootMiB < 128U || !layout.bootFlag) {
    reason = "boot partition flag and minimum partition sizes are required";
    return false;
  }

  reason = "microSD layout " + layout.bootFs + " boot " +
           std::to_string(layout.bootMiB) + " MiB, " + layout.rootFs +
           " root " + std::to_string(layout.rootMiB) + " MiB";
  return true;
}

bool validateTiming(const BootTiming& timing, std::string& reason) {
  const auto total = totalBootMs(timing);
  if (total == 0U || timing.targetLoginMs == 0U) {
    reason = "boot timing must include measured phases";
    return false;
  }

  if (total > timing.targetLoginMs) {
    reason = "login prompt " + std::to_string(total) + " ms exceeds target " +
             std::to_string(timing.targetLoginMs) + " ms";
    return false;
  }

  reason = "login prompt " + std::to_string(total) + " ms inside " +
           std::to_string(timing.targetLoginMs) + " ms target";
  return true;
}

}  // namespace

std::string toString(const CheckStatus status) {
  return status == CheckStatus::Pass ? "PASS" : "FAIL";
}

ImageReport BbbBootImageValidator::validate(const BoardTarget& target,
                                            const BootChain& bootChain,
                                            const RootfsProfile& rootfs,
                                            const PartitionLayout& layout,
                                            const BootTiming& timing) const {
  ImageReport report;

  auto fail = [&](std::string reason) {
    report.accepted = false;
    report.reason = std::move(reason);
    return report;
  };

  std::string reason;
  const bool targetOk = validateTarget(target, reason);
  addCheck(report, "board-target", targetOk, reason);
  if (!targetOk) {
    return fail(reason);
  }

  const bool bootOk = validateBootChain(bootChain, reason);
  addCheck(report, "boot-chain", bootOk, reason);
  if (!bootOk) {
    return fail(reason);
  }

  const bool rootfsOk = validateRootfs(rootfs, reason);
  addCheck(report, "tiny-rootfs", rootfsOk, reason);
  if (!rootfsOk) {
    return fail(reason);
  }

  const bool layoutOk = validateLayout(layout, reason);
  addCheck(report, "microsd-layout", layoutOk, reason);
  if (!layoutOk) {
    return fail(reason);
  }

  const bool timingOk = validateTiming(timing, reason);
  addCheck(report, "boot-timing", timingOk, reason);
  if (!timingOk) {
    return fail(reason);
  }

  report.accepted = true;
  report.reason = "BBB minimal Buildroot boot image accepted";
  return report;
}

TextBootImageReporter::TextBootImageReporter(std::ostream& stream)
    : stream_(stream) {}

void TextBootImageReporter::publish(const ImageReport& report) const {
  stream_ << "bbb_boot_image=" << (report.accepted ? "PASS" : "FAIL")
          << " reason=\"" << report.reason << "\"\n";
  for (const auto& check : report.checks) {
    stream_ << "  [" << toString(check.status) << "] " << check.step << ": "
            << check.detail << '\n';
  }
}

BoardTarget demoBoard() {
  return BoardTarget{"BeagleBone Black",
                     "AM335x",
                     "rheslar_bbb_minimal_defconfig",
                     "am335x-boneblack.dtb",
                     true};
}

BootChain demoBootChain() {
  return BootChain{"MLO", "u-boot.img", "zImage", true, true};
}

RootfsProfile demoRootfs() {
  return RootfsProfile{"busybox-init", 32U, true, true, true};
}

PartitionLayout demoLayout() {
  return PartitionLayout{"FAT32", "ext4", 96U, 256U, true};
}

BootTiming demoTiming() {
  return BootTiming{320U, 760U, 2140U, 980U, 5000U};
}

}  // namespace bbb_boot
