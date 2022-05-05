#ifndef BACKLIGHT_BACKLIGHT_HPP
#define BACKLIGHT_BACKLIGHT_HPP
#include <filesystem>
#include <stdexcept>
#include <vector>

namespace backlight {
using namespace std;
using std::vector;
using std::filesystem::path;
namespace fs = std::filesystem;

/** @brief Change brightness of device relative to current brightness
 * @param path sysfs path of device containing brightness knobs
 * @param percentage increment/decrement */
void adjust_brightness_by_increment(const path path, const int percentage);

/** @brief Change brightness of device to a given percentage
 * @param path sysfs path of device containing brightness knobs
 * @param percentage target percentage */
void adjust_brightness_to_target_percentage(const path path, const int percentage) ;
float get_current_brightness_percentage(const path device);
path get_xdg_config_path();
vector<path> default_paths();

/** Loads device paths from config file*/
vector<path> get_backlights_from_config_file(path config);
/** Scans through sysfs and returns full paths to valid devices */
vector<path> scan_for_valid_backlights();
} // namespace backlight
#endif