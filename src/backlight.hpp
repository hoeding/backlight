#ifndef BACKLIGHT_BACKLIGHT_HPP
#define BACKLIGHT_BACKLIGHT_HPP
#include "filesystem.hpp"
#include <stdexcept>
#include <vector>


namespace backlight {
using namespace std;
using std::vector;

/** @brief Change brightness of device relative to current brightness
 * @param path sysfs path of device containing brightness knobs
 * @param percentage increment/decrement */
void adjust_brightness_by_increment(const fs::path path, const int percentage);

/** @brief Change brightness of device to a given percentage
 * @param path sysfs path of device containing brightness knobs
 * @param percentage target percentage */
void adjust_brightness_to_target_percentage(const fs::path path,
                                            const int percentage);
float get_current_brightness_percentage(const fs::path device);
fs::path get_xdg_config_path();
vector<fs::path> default_paths();

/** Loads device paths from config file*/
vector<fs::path> get_backlights_from_config_file(fs::path config);
/** Scans through sysfs and returns full paths to valid devices */
vector<fs::path> scan_for_valid_backlights();
vector<fs::path> scan_for_valid_backlights_unique();
} // namespace backlight
#endif