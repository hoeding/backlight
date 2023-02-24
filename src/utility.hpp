#ifndef BACKLIGHT_UTILITY_HPP
#define BACKLIGHT_UTILITY_HPP
#include "concepts.hpp"
#include "filesystem.hpp"
#include "logging.hpp"
#include <charconv>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

namespace utility {
using namespace std;
using logging::dbg;
using fs::path;

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
inline int get_int_from_file(path path) noexcept {
  try {
    ifstream infile;
    infile.open(path);
    string str;
    getline(infile, str);
    int i = std::stoi(str);
    infile.close();
    return i;
  } catch (std::exception &e) {
    //cerr << "\n Caught:" << e.what();
    return 0;
  } catch (...) {
    cerr << "\nUnhandled exception reading path:" << path << endl;
    return 0;
  }
};

inline void put_int_to_file(int i, path path) {
  try {
    ofstream outfile{path};
    outfile << i << endl;
    outfile.close();
  } catch (...) { cerr << "Could not write " << i << " to " << path << endl; }
}

template <concepts::convertible_to_string T>
inline void strings_to_file(T str, path filename) noexcept {
  try {
    ofstream out(filename);
    if (!out) {
      dbg(true, 0, "Cannot open the File : ", filename);
      out.close();
    }
    out << str;
    out.close();
  } catch (...) {
    dbg(true, 0, "Unhandled exception writing:", str);
    dbg(false, 1, "to path:", filename);
  };
}
template <concepts::convertible_to_string T>
inline void strings_to_file(vector<T> vecOfStr, path filename) {
  string big_string = accumulate(vecOfStr.begin(), vecOfStr.end(), string{});
  strings_to_file(big_string, filename);
}

template <concepts::convertible_to_string T>
inline void strings_to_file_with_newline(vector<T> vecOfStr, path filename) {
  string big_string;
  for (T stringline : vecOfStr){
    big_string.append((string)stringline + "\n");
  }
  strings_to_file(big_string, filename);
}


//TODO
template<concepts::floatable T>
void to_string_sigfigures (T value, string stringy, int left, int right) {
  int char_count;
  if (right > 0) {
    char_count = right + left + 1; // decimal point
  } else {
    char_count = left;
  }
  stringy.reserve(char_count);
  to_chars(stringy.data(), stringy.data() + char_count, value, chars_format::fixed, 3);
}
} // namespace utility
#endif

// to_chars( char* first, char* last, float value, std::chars_format fmt, int precision );