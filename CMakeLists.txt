cmake_minimum_required(VERSION 3.20)
project(backlight
    VERSION 0.0.1
    DESCRIPTION "Simple backlight adjustment for laptops"
    LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include (GNUInstallDirs)


add_executable( bl-increment
        src/backlight_increment.cpp)
set_target_properties(bl-increment
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    VERSION ${PROJECT_VERSION})
target_compile_options( bl-increment
    PRIVATE -Wall -Wextra -pedantic -Werror
)
install(TARGETS bl-increment
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


add_executable( bl-absolute
    src/backlight_absolute.cpp)
set_target_properties(bl-absolute
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    VERSION ${PROJECT_VERSION})
target_compile_options( bl-absolute
    PRIVATE -Wall -Wextra -pedantic -Werror
)
install(TARGETS bl-absolute
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

