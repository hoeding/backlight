#ifndef BACKLIGHT_CONCEPTS_HPP
#define BACKLIGHT_CONCEPTS_HPP
#include <iostream>
#include <concepts>
#include <filesystem>
#include <fstream>
#include <cstdio>
namespace concepts {
  using namespace std;
  using std::filesystem::path;
template <class T>
concept printable = requires(T a) {
  cout << a;
  cerr << a;
};
} // namespace concepts
#endif