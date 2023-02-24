
#include "backlight.hpp"
#include "environment_arguments.hpp"
#include "logging.hpp"
#include "utility.hpp"
#include <GNUInstallDirs.hpp>
#include "filesystem.hpp"
#include <vector>
#include <string>

using std::vector;
using std::filesystem::directory_iterator;
using namespace logging;
using namespace utility;
using namespace NOT_YET_NAMED;

//#define ENV_ARG_USE_ENV
/** @brief*/
int main([[maybe_unused]] const int argc, [[maybe_unused]] const char *argv[], [[maybe_unused]] const char * envp[]) {

  option_pack<bool> verbose 
  { short_opt{"v"},
    long_opt{"verbose"},
    help_t{"loquacious output, useful for debugging"}
  };
  option_pack<bool> all_users 
  { short_opt{"a"},
    long_opt{"all_users"},
    help_t{"Write the generated config to default location (SHAREDSTATEDIR)"}
  };
  option_pack<bool> current_user
  { short_opt{"c"},
    long_opt{"current_user"},
    help_t{"optional long option description"}
  };
  option_pack<path> by_path 
  { short_opt{"p"},
    long_opt{"output-path"},
    help_t{"path to write generated configuration"
#ifdef ENV_ARG_USE_ENV
  , environ_t { "TEST_ENV_VAR_FOO", seperator{" "}, seperator{","}, seperator{{" "},{":"}} }
  , flags_e::concatenate_env
#endif
   }
  };
  option_pack<no_parsing> help 
  { short_opt{"h"},
    long_opt{"help"},
    help_t{"long form help description"},
    flags_e::error
  };
  arg_env_parameter_pack arg_env 
  { argc, argv, envp 
  };

  [[maybe_unused]] options_manager opt{
    arg_env,
    verbose, all_users, current_user, by_path, help
  };

  /* Look through the entries in /sys/class/backlight and find all supported
   * devices */
  vector<fs::path> valid_paths{};
  fs::path backlight_path{"/sys/class/backlight"};
  if (exists(backlight_path) and is_directory(backlight_path)) {
    for (fs::path device : directory_iterator{backlight_path}) {
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
  if (all_users) {
    // install to /etc/backlight/config
  };

  if (current_user) {
    // install to XDG config dir "~/.config/backlight/config"
  };

  if (by_path){
   // fs::path parsed_path = by_path;
    // install to given file
  }

  return (EXIT_SUCCESS);
}
