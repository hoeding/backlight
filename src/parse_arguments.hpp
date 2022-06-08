#ifndef BACKLIGHT_PARSING_HPP
#define BACKLIGHT_PARSING_HPP
#include "logging.hpp"
#include <iostream>
#include <stdexcept>
// cli > envvars > userconfig > globalconfig > defaults
namespace arguments {
using namespace std;
using logging::dbg;

/** @brief Safely handle arguments. Will either return through
 * parameter (-100,100) or terminate*/
int parse_args(const int &argc, const char *argv[]) {
  if (argc != 2) {
    dbg(false, 0, "Incorrect number of arguments\n");
    exit(EXIT_FAILURE);
  }
  int adjustment;
  try {
    adjustment = stoi(argv[1]);
  } catch (...) {
    dbg(true, 0, "Unhandled exception converting to integer");
    exit(EXIT_FAILURE);
  };
  if ((adjustment < -100) or (adjustment > 100)) {
    dbg(true, 0, "Valid inputs are -100 to 100 inclusive");
    exit(EXIT_FAILURE);
  }
  return adjustment;
}

} // namespace arguments
#endif