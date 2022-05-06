#ifndef BACKLIGHT_LOGGING_HPP
#define BACKLIGHT_LOGGING_HPP
#include "concepts.hpp"
#include <bitset>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace logging {
using namespace std;
using concepts::printable;
using std::filesystem::path;

/*


using prio_enum_width = uint8_t;
enum class prio_enum : prio_enum_width {
  SILENT = 0b0,
  USER = 0b1,
  WARN = 0b10,
  ERROR = 0b100,
  FATAL = 0b1000
};

using target_enum_width = uint8_t;
enum class target_enum : target_enum_width {
  NOOP = 0b0,
  STDERR = 0b1,
  STDOUT = 0b10,
  SYSLOG = 0b100,
  LOGFILE = 0b1000
};

template <class T>
concept bitwise_enum = (is_enum<T>::value);

template <bitwise_enum T, class Twidth>
T operator or (T lhs, T rhs) {
  return static_cast <T> (static_cast<Twidth>(lhs) |
      static_cast<Twidth>(rhs));
}
priority_enum operator and (priority_enum lhs, priority_enum rhs){
  return static_cast<priority_enum>(static_cast<priority_enum_thicccness>(lhs) |
                                    static_cast<priority_enum_thicccness>(rhs));
}

*/

inline void header(const bool newLine, const int tabs) {
  if (tabs < 0)
    exit(EXIT_FAILURE);
  if (newLine)
    cout << "\n";
  for (int t = tabs; t; t--) {
    cout << "\t";
  }
}
template <printable T>
inline void dbg(const bool &newLine, const int &tabs, const string &description,
         const T data) {
  header(newLine, tabs);
  try {
    cout << description << std::fixed << std::setprecision(13) << data << flush;
  } catch (exception &e) {
    cerr << "template dbg threw exception: " << e.what() << endl;
  }
}
inline void dbg(const bool &newLine, const int &tabs, const string &description) {
  header(newLine, tabs);
  cout << description << flush;
};
inline void dbg(const bool &newLine, const int &tabs) {
  header(newLine, tabs);
  cout << flush;
};
template <printable T>
inline void dbg(const bool &newLine, const int &tabs, const string &description,
         const vector<T> &data) {
  dbg(newLine, tabs, description);
  for (T datum : data) {
    dbg(true, 1, "", datum);
  };
};
} // namespace logging

#endif