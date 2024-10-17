cmake_minimum_required(VERSION 3.20)
project(backlight
    VERSION 0.0.4
    DESCRIPTION "Simple backlight adjustment for laptops"
    LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include (GNUInstallDirs)
find_package(Threads REQUIRED)
option(BIG_WARN "Use strict compiler flags" ON)
configure_file(src/version.hpp.in project_version.hpp)
configure_file(src/GNUInstallDirs.hpp.in GNUInstallDirs.hpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library (backlight SHARED
        src/backlight.cpp)
    set_target_properties(backlight
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "backlight.hpp"
    if (BIG_WARN)
        target_compile_options( backlight
        PRIVATE -Wall -Wextra -pedantic -Werror )
    endif(BIG_WARN)
    install(TARGETS backlight
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libjh/
        )
)
add_executable( bli
        src/backlight_increment.cpp)
    set_target_properties(bli
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        VERSION ${PROJECT_VERSION})
    target_compile_definitions (bli
        PRIVATE VERSION=${PROJECT_VERSION})
    if (BIG_WARN)
        target_compile_options( bli
            PRIVATE -Wall -Wextra -pedantic -Werror )
    endif(BIG_WARN)
    target_link_libraries( bli backlight)
    install(TARGETS bli
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
add_executable( bld
        src/backlight_decrement.cpp)
    set_target_properties(bld
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        VERSION ${PROJECT_VERSION})
    target_compile_definitions (bld
        PRIVATE VERSION=${PROJECT_VERSION})
    if (BIG_WARN)
        target_compile_options( bld
            PRIVATE -Wall -Wextra -pedantic -Werror )
    endif(BIG_WARN)
    target_link_libraries (bld backlight)
    install(TARGETS bld
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
add_executable( bla
       src/backlight_absolute.cpp)
    set_target_properties(bla
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        VERSION ${PROJECT_VERSION})
    target_compile_definitions (bla
        PRIVATE VERSION=${PROJECT_VERSION})
    if (BIG_WARN)
        target_compile_options( bla
            PRIVATE -Wall -Wextra -pedantic -Werror )
    endif (BIG_WARN)
    target_link_libraries(bla backlight)
    install(TARGETS bla
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
add_executable( bl-scanner 
       src/bl_scanner.cpp
       )
    target_link_libraries( 
        bl-scanner
        backlight
        #env-arg-parser
        )
    set_target_properties( bl-scanner
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        VERSION ${PROJECT_VERSION})
        target_compile_definitions (bl-scanner
        PRIVATE VERSION=${PROJECT_VERSION})
    if (BIG_WARN)
        target_compile_options( bl-scanner
            PRIVATE -Wall -Wextra -pedantic -Werror -fconcepts-diagnostics-depth=5)
    endif( BIG_WARN)
    #target_link_libraries(bl-scanner backlight)
    install(TARGETS bl-scanner
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_executable( swayutil
       src/swayutil.cpp)
    target_link_libraries(swayutil 
        Threads::Threads
        backlight )
    set_target_properties(swayutil
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        VERSION ${PROJECT_VERSION})
    target_compile_definitions (swayutil
        PRIVATE VERSION=${PROJECT_VERSION})
    if (BIG_WARN)
        target_compile_options( swayutil
            PRIVATE -Wall -Wextra -pedantic -Werror )
    endif (BIG_WARN)
    install(TARGETS swayutil
       RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_executable( const_array_generator
    tools/generate_consts.cpp)