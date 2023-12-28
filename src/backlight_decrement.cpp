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
  int percentage = (-1) * arguments::args_to_plus_minus_100_percent(argc, argv);
  vector<path> paths_to_config_files = default_paths();
  for (auto config_file : paths_to_config_files) {
    vector<path> devices = get_backlights_from_config_file(config_file);
    if (devices.empty()) {
      devices = scan_for_valid_backlights();
    }
    if (!devices.empty()) {
      for (auto device : devices) {
        backlight::adjust_brightness_by_increment(device, percentage);
      }
    }
  }
  return (EXIT_SUCCESS);
}