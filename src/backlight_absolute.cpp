#include "backlight.hpp"
#include "logging.hpp"
#include "parse_arguments.hpp"
#include "utility.hpp"
#include <filesystem>
#include <vector>

using std::vector;
using std::filesystem::path;
using namespace logging;
using namespace utility;
using namespace backlight;

/** @brief Single argument increments/decrements current brightness by N% */
int main(const int argc, const char *argv[]) {
  int percentage = arguments::parse_args(argc, argv);

  /** builtin search paths */
 

  for (auto config_file : default_paths()) {
    vector<path> devices = get_backlights_from_config_file(config_file);
    if (devices.empty()) {
      devices = scan_for_valid_backlights();
    }
    if (!devices.empty()){
      for (auto device : devices) {
        adjust_brightness_to_target_percentage(device, percentage);
      }
    }
  }
  return (EXIT_SUCCESS);
}