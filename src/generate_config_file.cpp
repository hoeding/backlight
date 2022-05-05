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
  path manual_path = "/dev/null";

  /* */

  /* Look through the entries in /sys/class/backlight and find all supported
   * devices */
  vector<path> valid_paths{};
  path backlight_path{"/sys/class/backlight"};
  if (exists(backlight_path) and is_directory(backlight_path)) {
    for (path device : directory_iterator{backlight_path}) {
      if (exists(device / "brightness")) {
        valid_paths.emplace_back(device.filename());
        dbg(false, 0, "Device supports brightness", device);
      } else {
        dbg(true, 0, "Device does not support brightness", device);
      }
    }
  } else {
    dbg(true, 0,
        "/sys/class/backlight/ path does not exist. Please ensure that \
        the necessary kernel options are enabled (kernel option: BACKLIGHT_CLASS_DEVICE)");
    std::exit(EXIT_FAILURE);
  }

  /* */

#ifndef NDEBUG
  dbg(true, 0, "Debug - valid_paths", valid_paths);
  dbg(true, 0);
#endif
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