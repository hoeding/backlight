#include "backlight.hpp"
#include "logging.hpp"
#include "parse_arguments.hpp"
#include "parse_config_file.hpp"
#include "utility.hpp"
#include <filesystem>
#include <vector>

using std::vector;
using std::filesystem::directory_iterator;
using std::filesystem::path;
using namespace logging;
using namespace utility;

/** @brief Single argument increments/decrements current brightness by N% */
int main([[maybe_unused]]const int argc, [[maybe_unused]] const char *argv[]) {

  /* Configuration variables, TODO: make configurable */

  bool all_users = true;
  bool current_user = true;
  bool by_path = true;
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
  dbg(true, 0, "Debug - valid_paths", valid_paths); dbg(true, 0);
  #endif
  if (all_users) {
    // install to /etc/backlight/config
  };

  if (current_user) {
    // install to XDG config dir "~/.config/backlight/config"
  };

  if (by_path) {
    // install to given file
  }

  return (EXIT_SUCCESS);
}