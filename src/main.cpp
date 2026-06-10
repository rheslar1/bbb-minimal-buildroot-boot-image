#include "bbb_boot/BbbBootImage.hpp"

#include <iostream>

int main() {
  bbb_boot::BbbBootImageValidator validator;
  bbb_boot::TextBootImageReporter reporter(std::cout);

  std::cout << "BBB Minimal Buildroot Boot Image\n";
  std::cout << "Target: BeagleBone Black AM335x microSD boot to BusyBox login\n\n";

  const auto report = validator.validate(bbb_boot::demoBoard(),
                                         bbb_boot::demoBootChain(),
                                         bbb_boot::demoRootfs(),
                                         bbb_boot::demoLayout(),
                                         bbb_boot::demoTiming());
  reporter.publish(report);
  return report.accepted ? 0 : 1;
}
