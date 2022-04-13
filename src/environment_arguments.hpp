#ifndef ENVIRONMENT_ARGUMENTS_HPP
#define ENVIRONMENT_ARGUMENTS_HPP

#include <GNUInstallDirs.hpp>

namespace options {

class short_opt : public std::string {};
class long_opt : public std::string {};
class help_text : public std::string {};
class param_value : public std::string {};
using success = bool;
using std::vector;
enum class flags_e {
  none = 0b0,
  no_arg = 0b1,
  optional_arg = 0b10,
  mandatory_arg = 0b100,
  error = 0b1000
};

class option_pack {
public:
  option_pack(short_opt my_value ...){
    short_opts.emplace_back(my_value);

    };
  void and_then([[maybe_unused]] short_opt my_value ...) {
    short_opts.emplace_back(value);

  }
  option_pack(long_opt ...){};
  option_pack(help_text ...){};
  option_pack(param_value ...){};
  option_pack(int, char ** ...){};
  option_pack(int, char **, char ** ...){};


private:
 vector<short_opt> short_opts{};
  vector<long_opt> long_opts{};
  help_text help_text_{};
  param_value param_value_{};
};
class getopts_getargs_getenv {
  public:
  getopts_getargs_getenv (vector<option_pack>){};
  getopts_getargs_getenv (option_pack){};
};





namespace environment_variables {

class state {
public:
  // shared_ptr

  std::string get_value([[maybe_unused]] std::string key) {
    return std::string{};
  }

private:
  struct env_t {
    std::string key{};
    std::vector<std::string> values{};
  };
  std::vector<env_t> environment{};
  char **c_style = nullptr;
};

std::vector<std::filesystem::path> env_path() {
  struct token_t {
    std::string::size_type start;
    std::string::size_type end;
  };
  std::vector<token_t> tokens;
  std::vector<std::filesystem::path> paths{};
  std::string raw_path{getenv("PATH")};

  [[maybe_unused]] std::string::size_type next = 0, prev = 0;

  for (std::string::size_type position = 0; position < raw_path.length();
       position++) {
    std::vector<std::string::size_type> colon_positions{};
    if (raw_path.at(position) == ':') {}
  }

  return paths;
};
} // namespace environment_variables
namespace arguments {}

} // namespace options

#endif
