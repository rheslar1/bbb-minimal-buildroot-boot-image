#ifndef BBB_BOOT_BBB_BOOT_IMAGE_HPP_
#define BBB_BOOT_BBB_BOOT_IMAGE_HPP_

#include <cstdint>
#include <iosfwd>
#include <string>
#include <vector>

namespace bbb_boot {

enum class CheckStatus {
  Pass,
  Fail
};

std::string toString(CheckStatus status);

struct BoardTarget {
  std::string board;
  std::string soc;
  std::string defconfig;
  std::string deviceTree;
  bool microSdBoot{};
};

struct BootChain {
  std::string spl;
  std::string uboot;
  std::string kernelImage;
  bool mloFirstSector{};
  bool bootEnvUsesUart0{};
};

struct RootfsProfile {
  std::string initSystem;
  std::uint32_t sizeMiB{};
  bool busyboxOnly{};
  bool sshDisabled{};
  bool gettyOnTtyO0{};
};

struct PartitionLayout {
  std::string bootFs;
  std::string rootFs;
  std::uint32_t bootMiB{};
  std::uint32_t rootMiB{};
  bool bootFlag{};
};

struct BootTiming {
  std::uint32_t splMs{};
  std::uint32_t ubootMs{};
  std::uint32_t kernelMs{};
  std::uint32_t rootfsMs{};
  std::uint32_t targetLoginMs{5000};
};

struct ImageCheck {
  std::string step;
  CheckStatus status{CheckStatus::Fail};
  std::string detail;
};

struct ImageReport {
  bool accepted{};
  std::string reason;
  std::vector<ImageCheck> checks;
};

class BbbBootImageValidator {
 public:
  ImageReport validate(const BoardTarget& target,
                       const BootChain& bootChain,
                       const RootfsProfile& rootfs,
                       const PartitionLayout& layout,
                       const BootTiming& timing) const;
};

class TextBootImageReporter {
 public:
  explicit TextBootImageReporter(std::ostream& stream);

  void publish(const ImageReport& report) const;

 private:
  std::ostream& stream_;
};

BoardTarget demoBoard();
BootChain demoBootChain();
RootfsProfile demoRootfs();
PartitionLayout demoLayout();
BootTiming demoTiming();

}  // namespace bbb_boot

#endif  // BBB_BOOT_BBB_BOOT_IMAGE_HPP_
