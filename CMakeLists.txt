cmake_minimum_required(VERSION 3.10)
project(FilesystemSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This executable is your "production" or "demo" program
add_executable(ws
    src/main.cpp
    src/Filesystem.cpp
    src/Directory.cpp
    src/File.cpp
    # plus any other .cpp files
)

# This executable is your tester program
add_executable(tester
    src/tester_1.cpp
    src/Filesystem.cpp
    src/Directory.cpp
    src/File.cpp
    # plus any other .cpp files
)

# Tell CMake to look for header files in the src directory.
target_include_directories(ws PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
