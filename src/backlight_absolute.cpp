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
#ifndef NDEBUG
  dbg(true, 0, "backlight-absolute version VERSION");
#endif
  int percentage = arguments::parse_args(argc, argv);
  /** builtin search paths */
  vector<path> paths_to_config_files{{"/etc/backlight/config"}};
  paths_to_config_files.push_back(backlight::get_xdg_config_path());

#ifndef NDEBUG
  dbg(true, 0, "", paths_to_config_files);
#endif
  for (auto config_file : paths_to_config_files) {
    vector<path> devices = get_backlights_from_config_file(config_file);
    for (auto device : devices) {
      adjust_brightness_to_target_percentage(device, percentage);
    }
  }
  return (EXIT_SUCCESS);
}