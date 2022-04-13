#include "backlight.hpp"
#include "environment_arguments.hpp"
#include "logging.hpp"
#include "utility.hpp"
#include <GNUInstallDirs.hpp>
#include <filesystem>
#include <vector>

using std::vector;
using std::filesystem::directory_iterator;
using std::filesystem::path;
using namespace logging;
using namespace utility;
using namespace options;

/** @brief Single argument increments/decrements current brightness by N% */
int main([[maybe_unused]] const int argc, [[maybe_unused]] const char *argv[]) {

  /* Configuration variables, TODO: make configurable */

  getopts_getargs_getenv opt{{
    {short_opt{"h"}, long_opt{"help"}, help_text{"long form help description"}, flags_e::error},
    {short_opt{"a"}, long_opt{"all_users"}, help_text{"Write the generated config file to default location (SHAREDSTATEDIR)"}},
    {short_opt{"c"}, long_opt{"current_user"}, help_text{"optional long option description"}}
  };

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