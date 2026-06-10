#include <array>
#include <cassert>
#include <string_view>

class IReadinessRule {
 public:
  virtual ~IReadinessRule() = default;
  virtual bool passes(std::string_view evidenceTarget) const = 0;
};

class RequiredEvidenceRule final : public IReadinessRule {
 public:
  bool passes(std::string_view evidenceTarget) const override {
    return !evidenceTarget.empty();
  }
};

struct ProjectProfile {
  std::string_view title;
  std::string_view summary;
  std::string_view evidenceTarget;
  std::array<std::string_view, 9> tags;
};

constexpr ProjectProfile profile{
  "BBB Minimal Buildroot Boot Image",
  "BeagleBone Black AM335x project that builds U-Boot, Linux kernel, and a tiny root filesystem with Buildroot for a sub-5-second login prompt.",
  "Board-specific boot-chain ownership, fast minimal Linux image generation, and clear startup-time evidence.",
  {
    "C++17",
    "C++ Design Patterns",
    "SOLID",
    "BeagleBone Black",
    "AM335x",
    "Buildroot",
    "U-Boot",
    "Kernel build",
    "microSD boot"
  }
};

int main() {
  const RequiredEvidenceRule rule;
  assert(!profile.title.empty());
  assert(!profile.summary.empty());
  assert(rule.passes(profile.evidenceTarget));
  assert(profile.tags[0] == "C++17");
  return 0;
}
