#ifndef BACKLIGHT_CONCEPTS_HPP
#define BACKLIGHT_CONCEPTS_HPP
#include <concepts>
#include <cstdio>
#include "filesystem.hpp"
#include <fstream>
#include <iostream>
#include <string>
namespace concepts {
using namespace std;
using std::filesystem::path;
template <class T>
concept printable = requires(T a) {
  cout << a;
  cerr << a;
};
template <class T>
concept convertible_to_string =
    std::is_convertible_v<T, std::string> && requires {
  static_cast<string>(std::declval<T>());
};
template <class T>
concept floatable = (std::is_convertible<T, float>::value);
} // namespace concepts
#endif