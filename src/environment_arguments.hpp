#ifndef ENVIRONMENT_ARGUMENTS_HPP
#define ENVIRONMENT_ARGUMENTS_HPP

#include <GNUInstallDirs.hpp>

namespace NOT_YET_NAMED {
using std::is_same;

class short_opt : public std::string {};
class long_opt : public std::string {};
class help_t : public std::string {};
class param_t : public std::string {};
using success = bool;
using std::vector;

enum class style_e : uint8_t { 
  none =      0b0, 
  bool_e =    0b1, 
  string_e =  0b10, 
  int_e =     0b100,
  float_e =   0b1000
};

enum class flags_e : uint8_t {
  none =          0b0,
  no_arg =        0b1,
  optional_arg =  0b10,
  mandatory_arg = 0b100,
  error =         0b1000,
  help =          0b10000
};


template <class T>
concept pointy_boi = (std::is_pointer<T>::value);

class parameter_pack{

  public: /* constructors */
  template<pointy_boi Ta>
  parameter_pack (int const &argc_, const Ta argv_) {
    add(argc_, argv_);
  }
  template<pointy_boi Ta, pointy_boi Tb>
  parameter_pack (int const &argc_, Ta const argv_, Tb const envp_) {
    add(argc_, argv_, envp_);
  }

  /*members*/
  template <pointy_boi Tb, pointy_boi Tc, class... Ts>
  void add(int const &argc_, Tb const argv_, Tc const envp_,
           const Ts &...rest) {
    argc = argc_;
    argv = const_cast<char **> (argv_);
    envp = const_cast<char **> (envp_);
    if constexpr (sizeof...(rest) > 0) {
      add(rest...);
    }
  }
  template <int Ta, pointy_boi Tb, class... Ts>
  void add(int const &argc_, Tb const argv_, const Ts &...rest) {
    argc = argc_;
    argv = argv_;
    if constexpr (sizeof...(rest) > 0) {
      add(rest...);
    }
  }
  template <pointy_boi Ta, class... Ts>
  void add(Ta const envp_, const Ts &...rest) {
    envp = envp_;
    if constexpr (sizeof...(rest) > 0) {
      add(rest...);
    }
  }
  void add(int argc_, char **argv_) { // Construct using arguments only
    argc = argc_;
    argv = argv_;
  }
  void add(char **envp_) { // Construct using environment only
    envp = envp_;
  };
  void add(int argc_, char **argv_,
           char **envp_) { // Construct using arguments and environment
    add(argc_, argv_);
    add(envp_);
  };
private:
  int argc = 0;
  char **argv = nullptr;
  char **envp = nullptr;
};

template <class T>
concept option_pack_constructable =
    (is_same<T, short_opt>::value or is_same<T, long_opt>::value or
     is_same<T, help_t>::value or is_same<T, param_t>::value or
     is_same<T, style_e>::value or is_same<T, flags_e>::value
);
class option_pack {
public:
  template <option_pack_constructable T, option_pack_constructable... Ts>
  option_pack(T const &first, Ts const &...rest) {
    add(first);
    if constexpr (sizeof...(rest) > 0) {
      add(rest...);
    }
  }

  template <option_pack_constructable T, option_pack_constructable... Ts>
  void add(T const &first, Ts const &...rest) {
    add(first);
    if constexpr (sizeof...(rest) > 0) {
      add(rest...);
    }
  }
  bool is_it_true() {return true;};

protected:
  void add(long_opt value) { long_opts.emplace_back(value); }
  void add(help_t value) { help_text = value; }
  void add(param_t value) { param_value = value; }

private:
  vector<short_opt> short_opts;
  vector<long_opt> long_opts;
  help_t help_text;
  param_t param_value;
};

template <class T>
concept options_manager_constructable = (
  std::is_same<T, option_pack>::value or
  std::is_same<T, parameter_pack>::value
);

class options_manager {
public:
  template <options_manager_constructable Ta,
            options_manager_constructable... Ts>
  options_manager(Ta const &first, Ts const &...rest) {
    add(first);
    if constexpr (sizeof...(rest) > 0) {
      add(rest...);
    }
  }
  protected:
  void add([[maybe_unused]] parameter_pack value) {};
  void add([[maybe_unused]] option_pack value) { /*respect order */};
  template<options_manager_constructable T, options_manager_constructable... Ts>
  void add([[maybe_unused]] T const &first, Ts const &...rest){
    add(first);
    if constexpr (sizeof...(rest) > 0) {
      add(rest...);
    }
  }
  };
}

 // namespace NOT_YET_NAMED

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

#endif
