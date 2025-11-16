cmake_minimum_required(VERSION 3.16)
project(KhezChessEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -O3")

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Include directories
include_directories(src)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Create library for chess engine
add_library(khez_engine ${SOURCES})

# Create executable
add_executable(khez src/main.cpp)
target_link_libraries(khez khez_engine)

# Enable testing
enable_testing()

# Simple test executable without external dependencies
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_executable(khez_tests ${TEST_SOURCES})
target_link_libraries(khez_tests khez_engine)

add_test(NAME unit_tests COMMAND khez_tests)