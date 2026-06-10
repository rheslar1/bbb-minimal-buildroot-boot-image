#include "bbb_boot/BbbBootImage.hpp"

#include <cassert>
#include <sstream>
#include <string>

namespace {

bool contains(const std::string& value, const std::string& needle) {
  return value.find(needle) != std::string::npos;
}

bbb_boot::ImageReport validate(
    bbb_boot::BoardTarget target = bbb_boot::demoBoard(),
    bbb_boot::BootChain bootChain = bbb_boot::demoBootChain(),
    bbb_boot::RootfsProfile rootfs = bbb_boot::demoRootfs(),
    bbb_boot::PartitionLayout layout = bbb_boot::demoLayout(),
    bbb_boot::BootTiming timing = bbb_boot::demoTiming()) {
  bbb_boot::BbbBootImageValidator validator;
  return validator.validate(target, bootChain, rootfs, layout, timing);
}

void acceptsNominalBbbImage() {
  const auto report = validate();

  assert(report.accepted);
  assert(report.reason == "BBB minimal Buildroot boot image accepted");
  assert(report.checks.size() == 5U);
}

void rejectsWrongDeviceTree() {
  auto target = bbb_boot::demoBoard();
  target.deviceTree = "am335x-bone.dtb";

  const auto report = validate(target);

  assert(!report.accepted);
  assert(contains(report.reason, "am335x-boneblack"));
}

void rejectsMissingMloPlacement() {
  auto bootChain = bbb_boot::demoBootChain();
  bootChain.mloFirstSector = false;

  const auto report = validate(bbb_boot::demoBoard(), bootChain);

  assert(!report.accepted);
  assert(contains(report.reason, "MLO"));
}

void rejectsLargeRootfs() {
  auto rootfs = bbb_boot::demoRootfs();
  rootfs.sizeMiB = 96U;

  const auto report =
      validate(bbb_boot::demoBoard(), bbb_boot::demoBootChain(), rootfs);

  assert(!report.accepted);
  assert(contains(report.reason, "64 MiB"));
}

void rejectsSlowLoginPrompt() {
  auto timing = bbb_boot::demoTiming();
  timing.rootfsMs = 2400U;

  const auto report = validate(bbb_boot::demoBoard(),
                               bbb_boot::demoBootChain(),
                               bbb_boot::demoRootfs(),
                               bbb_boot::demoLayout(),
                               timing);

  assert(!report.accepted);
  assert(contains(report.reason, "exceeds"));
}

void reporterIncludesBootEvidence() {
  const auto report = validate();
  std::ostringstream output;
  bbb_boot::TextBootImageReporter reporter(output);
  reporter.publish(report);

  assert(contains(output.str(), "bbb_boot_image=PASS"));
  assert(contains(output.str(), "boot-timing"));
}

}  // namespace

int main() {
  acceptsNominalBbbImage();
  rejectsWrongDeviceTree();
  rejectsMissingMloPlacement();
  rejectsLargeRootfs();
  rejectsSlowLoginPrompt();
  reporterIncludesBootEvidence();
  return 0;
}
