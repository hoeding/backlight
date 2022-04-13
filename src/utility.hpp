#ifndef BACKLIGHT_UTILITY_HPP
#define BACKLIGHT_UTILITY_HPP
#include "logging.hpp"
#include <concepts>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

namespace utility {
using namespace std;
using logging::dbg;
using std::filesystem::path;

/* @brief Average two numbers, returns 0 if indivisble */
template <concepts::floatable Ta, concepts::floatable Tb>
float ez_pct(const Ta numerator, const Tb denominator) {
  auto returner = 420.69;
  try {
    returner =
        (100.0 * (float)numerator) / (float)denominator; // Integer rounding
  } catch (...) { cerr << "ez_pct threw exception" << endl; }
  return returner;
};
/* @brief  Attempt to get an integer from a file, always returns */
int get_int_from_file(path path) noexcept {
  try {
    ifstream infile;
    infile.open(path);
    string str;
    getline(infile, str);
    int i = std::stoi(str);
    infile.close();
    return i;
  } catch (std::exception &e) {
    cerr << "\n Caught:" << e.what();
    return 0;
  } catch (...) {
    cerr << "\nUnhandled exception reading path:" << path << endl;
    return 0;
  }
};

void put_int_to_file(int i, path path) {
  try {
    ofstream outfile{path};
    outfile << i << endl;
    outfile.close();
  } catch (...) { cerr << "Could not write " << i << " to " << path << endl; }
}

vector<string> filename_to_vector_of_strings(path filename) {
  vector<string> returner{};
  // Open the File
  ifstream in(filename);
  string str;
  // Check if object is valid
  if (!in) {
    dbg(true, 0, "Cannot open the File:", filename);
  } else {
    dbg(true, 0, "File opened:", filename);

    // Read the next line from File untill it reaches the end.
    while (getline(in, str)) {
      // Line contains string of length > 0 then save it in vector
      if (str.size() > 0)
        returner.push_back(str);
    }
  }
  // Close The File
  in.close();
  return returner;
}

void strings_to_file(string str, path filename) noexcept {
  try {
    ofstream out(filename);
    if (!out) {
      dbg(true, 0, "Cannot open the File : ", filename);
      out.close();
    }
  } catch (...) {
    dbg(true, 0, "Unhandled exception writing:", str);
    dbg(false, 1, "to path:", filename);
  };
}
void strings_to_file(vector<string> vecOfStr, path filename) {
  string big_string = accumulate(vecOfStr.begin(), vecOfStr.end(), string{});
  strings_to_file(big_string, filename);
}

} // namespace utility

namespace arguments {
using namespace std;
using logging::dbg;

/** @brief Safely handle arguments. Will either return through
 * parameter (-100,100) or terminate*/
int args_to_plus_minus_100_percent(const int &argc, const char *argv[]) {
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