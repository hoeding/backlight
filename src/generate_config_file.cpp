#include "backlight.hpp"
#include "logging.hpp"
#include "parse_arguments.hpp"
#include "utility.hpp"
#include <filesystem>
#include <vector>

using std::vector;
using std::filesystem::directory_iterator;
using std::filesystem::path;
using namespace logging;
using namespace utility;

/** @brief Single argument increments/decrements current brightness by N% */
int main([[maybe_unused]] const int argc, [[maybe_unused]] const char *argv[]) {

  /* Configuration variables, TODO: make configurable */
  bool all_users = true;
  bool current_user = true;
  
  vector<path> valid_devices {backlight::scan_for_valid_backlights()};
  dbg(true, 0, "Discovered devices (valid_devices) -", valid_devices);
  if (all_users) {
    strings_to_file_with_newline(valid_devices, "/etc/backlight/config");
    // install to /etc/backlight/config
  };

  if (current_user) {
    strings_to_file_with_newline(valid_devices, backlight::get_xdg_config_path());
    // install to XDG config dir "~/.config/backlight/config"
  };

  return (EXIT_SUCCESS);
}