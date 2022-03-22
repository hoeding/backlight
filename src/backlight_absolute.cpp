#include "backlight.hpp"
#include "logging.hpp"
#include "parse_arguments.hpp"
#include "parse_config_file.hpp"
#include "utility.hpp"
#include <filesystem>

#include <vector>

using std::vector;
using std::filesystem::path;
using namespace logging;
using namespace utility;

/** @brief Single argument increments/decrements current brightness by N% */
int main(const int argc, const char *argv[]) {
  int percentage = arguments::parse_args(argc, argv);
  /** builtin search paths */
  vector<path> paths_to_config_files{{"/etc/backlight/config"}};
  paths_to_config_files.push_back(backlight::get_xdg_config_path());

#ifndef NDEBUG
  dbg(true, 0, "", paths_to_config_files);
#endif
  for (auto config_file : paths_to_config_files) {
    vector<path> devices =
        configfile::get_backlights_from_config_file(config_file);
    for (auto device : devices) {
      backlight::adjust_brightness_to_target_percentage(device, percentage);
    }
  }
  return (EXIT_SUCCESS);
}