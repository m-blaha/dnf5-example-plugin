message("Running CMake on dnf5-example-plugin...")
cmake_minimum_required(VERSION 3.6)

project(dnf5-example-plugin LANGUAGES CXX C VERSION 1.0.0)
message("Building ${PROJECT_NAME} version ${PROJECT_VERSION}")


# includes
include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Give inline methods hidden visibility by default
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

# warnings
add_compile_options(-Wall -Wextra -Werror)
add_compile_options(-Wcast-align -Wformat-nonliteral -Wmissing-format-attribute -Wredundant-decls -Wsign-compare -Wsign-conversion -Wtype-limits -Wuninitialized -Wwrite-strings)
add_compile_options(-Werror=unused-result -Wodr)

# not sure about the conversion warnings being errors; review later
add_compile_options(-Wconversion)

# linker options
if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # clang doesn't support this option
    add_compile_options(-Wl,--as-needed)
endif()

add_subdirectory("dnf5_foo_plugin")
add_subdirectory("libdnf5_baz_plugin")
