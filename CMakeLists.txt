cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(chesstra LANGUAGES CXX)

include(Sanitizers.cmake)

if (ENABLE_ASAN)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

if (ENABLE_UBSAN)
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
endif()

find_package(Catch2 REQUIRED)
# find_package(Curses REQUIRED)

# Find ncursesw library
find_library(NCURSESW_LIBRARY NAMES ncursesw)

# Check if ncursesw library is found
if (NOT NCURSESW_LIBRARY)
    message(FATAL_ERROR "ncursesw library not found")
endif()

add_executable(chesstra app/chesstra.cpp lib/display.cpp)
target_include_directories(chesstra PUBLIC include ${CURSES_INCLUDE_DIRS})
add_compile_options(-lncursesw)
target_link_libraries(chesstra PUBLIC ${NCURSESW_LIBRARY})
