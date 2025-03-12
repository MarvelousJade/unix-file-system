# UNIX-like Filesystem Simulation

This repository contains a C++ project that simulates a simple UNIX-like filesystem. The project is part of an OOP345 workshop exercise and demonstrates the use of polymorphism, STL containers, dynamic memory management, and exception handling in C++.

---

## Overview

The project models a basic filesystem with support for files and directories. It provides functionalities to:

- **Create a Filesystem**: Load a filesystem structure from a text file (`filesystem.txt`) where each line represents either a file or a directory.
- **Navigate Directories**: Change the current working directory manually via an interactive menu.
- **Display Contents**: Show directory contents in both brief and detailed (long) formats.
- **Interactive Menu**: A simple console-based interface allows you to move around directories, view their contents, and return to the root directory.
- **(Optional) Search and Remove**: You can easily extend the code to locate resources (files or directories) or remove them.

---

## Project Structure

```plaintext
unix-file-system/
├── CMakeLists.txt           # CMake build configuration
├── README.md                # This file
├── reflect.txt              # Reflection on the design and learning outcomes
└── src/
    ├── Filesystem.h         # Declaration of the Filesystem module
    ├── Filesystem.cpp       # Implementation of the Filesystem module
    ├── Directory.h          # Declaration of the Directory module
    ├── Directory.cpp        # Implementation of the Directory module
    ├── File.h               # Declaration of the File module
    ├── File.cpp             # Implementation of the File module
    ├── Flags.h              # Flags and enumerations for formatting and operations
    ├── Resource.h           # Base class for filesystem resources
    ├── tester_1.cpp         # Test program verifying functionalities
    ├── main.cpp             # Interactive console-based main
    ├── filesystem.txt       # Sample input file describing the filesystem structure
    └── sample_output.txt    # Expected output for the test harness
```

## Features
#### 1. Modular Design
Each major part of the filesystem (Directory, File, and Filesystem) is separated into distinct classes and source files.

#### 2. Polymorphism
A base Resource class is used to manage both files (File) and directories (Directory) within a single container.

#### 3. Exception Handling
The code throws exceptions for invalid operations (e.g., changing to a non-existent directory or removing a directory without recursion).

#### 4. Dynamic Memory Management
Each Directory object manages its contained resources, ensuring no leaks by deleting them in its destructor.

#### 5. STL Utilization
Uses std::vector for storing polymorphic pointers, plus standard algorithms like std::find for searching.

#### 6. Test Harness (tester_1.cpp)
Demonstrates the functional correctness of adding/removing files and directories, searching, size calculations, etc.

## Building the Project
### Prerequisites
- **C++ Compiler**: A compiler supporting C++17 (e.g., GCC 7+, Clang 5+, MSVC 2017+).
- **CMake**: Version 3.10 or higher recommended.
### Steps
#### 1. Clone the Repository

```bash
git clone https://github.com/yourusername/unix-file-system.git
cd unix-file-system
```
Create a Build Directory and Run CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```
This will compile the project and generate an executable named ws.

## Usage
### Running the Interactive Program
The executable built from main.cpp provides an interactive menu. To run the program, use:

```bash
./ws ../src/filesystem.txt
```
(Ensure the path to filesystem.txt is correct relative to your build directory.)

The interactive menu will display options such as:

```markdown
Current directory: /
Choose an option:
 1. List current directory contents (brief)
 2. List current directory contents (long format)
 3. Change directory
 4. Go to root directory
 5. Exit
Enter your choice:
```
- **List (Brief)**: Displays the current directory’s contents without extra details.
- **List (Long)**: Displays detailed information including item counts and sizes.
- **Change Directory**: Prompts for a directory name (e.g., images/) and navigates into it if it exists.
- **Go to Root Directory**: Resets the current directory to the root.
- **Exit**: Ends the program.

### Running the Test Harness
The file tester_1.cpp contains a separate main function for automated testing. To build and run the test harness instead, modify your CMakeLists.txt or create an additional executable:

``````cmake
# Interactive main
add_executable(ws
    src/main.cpp
    src/Filesystem.cpp
    src/Directory.cpp
    src/File.cpp
)

# Test harness
add_executable(tester
    src/tester_1.cpp
    src/Filesystem.cpp
    src/Directory.cpp
    src/File.cpp
)
``````
Then run the test harness with:

``````bash
./tester ../src/filesystem.txt
``````
