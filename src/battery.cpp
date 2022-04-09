#include "logging.hpp"
#include "parse_arguments.hpp"
#include "utility.hpp"
#include <csignal>
#include <filesystem>
#include <project_version.hpp>

#include <vector>

using std::vector;
using std::filesystem::path;
using namespace logging;
using namespace utility;

/** @brief print battery level every N  */
int main([[maybe_unused]]const int argc, [[maybe_unused]] const char *argv[]) {
  #ifndef NDEBUG
  dbg(true, 0, " version PROJECT_VERSION");
#endif

  return (EXIT_SUCCESS);
}