#ifndef BACKLIGHT_PARSE_CONFIG_FILE_HPP
#define BACKLIGHT_PARSE_CONFIG_FILE_HPP
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace configfile {
using namespace std;
using std::filesystem::path;

vector<path> get_backlights_from_config_file(path config) {
  vector<path> returner;
  ifstream infile;
  infile.open(config);
  while (infile.good()) {
    string line;
    getline(infile, line);
    if (line != string{}){
    line = "/sys/class/backlight/" + line;
    returner.push_back(line);}
  }
  return returner;
}

} // namespace configfile
#endif