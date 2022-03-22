#ifndef BACKLIGHT_UTILITY_HPP
#define BACKLIGHT_UTILITY_HPP
#include <filesystem>
#include "logging.hpp"
#include <fstream>
#include <iostream>
#include <vector>

namespace utility {
using namespace std;
using logging::dbg;
using std::filesystem::path;
int get_int_from_file(path path) {
  try {
    ifstream infile;
    infile.open(path);
    string str;
    getline(infile, str);
    int i = std::stoi(str);
    infile.close();
    return i;
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
  } catch (...) {
    cerr << "Could not write " << i << " to " << path << endl;
  }
}

vector<string> filename_to_vector_of_strings(path filename) {
  vector<string> returner{};
  // Open the File
  ifstream in(filename);
  string str;
  // Check if object is valid
  if (!in) {
    dbg(true, 0, "Cannot open the File : ", filename);
  } else {
    dbg(true, 0, "File opened :", filename);

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

} // namespace utility
#endif