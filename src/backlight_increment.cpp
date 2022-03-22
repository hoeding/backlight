#include "backlight.hpp"
#include <filesystem>
#include "logging.hpp"
#include "utility.hpp"
#include "parse_arguments.hpp"
#include "parse_config_file.hpp"
#include <vector>

using std::vector;
using std::filesystem::path;
using namespace logging;
using namespace utility;


/** builtin search paths */
const vector<path> default_paths{{"/etc/backlight/config"},
                                 {"/home/jeff/.config/backlight/config"}};

/** @brief Single argument increments/decrements current brightness by N% */
int main(const int argc, const char *argv[]) {
  int percentage = arguments::parse_args(argc, argv);
  vector<path> paths_to_config_files = default_paths;
  for (auto config_file : paths_to_config_files) {
    vector<path> devices = configfile::get_backlights_from_config_file(config_file);
    for (auto device : devices) {
      backlight::adjust_brightness_by_increment(device, percentage);
    }
  }
  return (EXIT_SUCCESS);
}