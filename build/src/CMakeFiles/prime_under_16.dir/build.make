# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joshua/gits/libsnark-circuit

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joshua/gits/libsnark-circuit/build

# Include any dependencies generated for this target.
include src/CMakeFiles/prime_under_16.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/prime_under_16.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/prime_under_16.dir/flags.make

src/CMakeFiles/prime_under_16.dir/prime_under_16.cpp.o: src/CMakeFiles/prime_under_16.dir/flags.make
src/CMakeFiles/prime_under_16.dir/prime_under_16.cpp.o: ../src/prime_under_16.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshua/gits/libsnark-circuit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/prime_under_16.dir/prime_under_16.cpp.o"
	cd /home/joshua/gits/libsnark-circuit/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/prime_under_16.dir/prime_under_16.cpp.o -c /home/joshua/gits/libsnark-circuit/src/prime_under_16.cpp

src/CMakeFiles/prime_under_16.dir/prime_under_16.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prime_under_16.dir/prime_under_16.cpp.i"
	cd /home/joshua/gits/libsnark-circuit/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshua/gits/libsnark-circuit/src/prime_under_16.cpp > CMakeFiles/prime_under_16.dir/prime_under_16.cpp.i

src/CMakeFiles/prime_under_16.dir/prime_under_16.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prime_under_16.dir/prime_under_16.cpp.s"
	cd /home/joshua/gits/libsnark-circuit/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshua/gits/libsnark-circuit/src/prime_under_16.cpp -o CMakeFiles/prime_under_16.dir/prime_under_16.cpp.s

# Object files for target prime_under_16
prime_under_16_OBJECTS = \
"CMakeFiles/prime_under_16.dir/prime_under_16.cpp.o"

# External object files for target prime_under_16
prime_under_16_EXTERNAL_OBJECTS =

src/prime_under_16: src/CMakeFiles/prime_under_16.dir/prime_under_16.cpp.o
src/prime_under_16: src/CMakeFiles/prime_under_16.dir/build.make
src/prime_under_16: depends/libsnark/libsnark/libsnark.a
src/prime_under_16: depends/libsnark/depends/libff/libff/libff.a
src/prime_under_16: /usr/lib/x86_64-linux-gnu/libgmp.so
src/prime_under_16: /usr/lib/x86_64-linux-gnu/libgmp.so
src/prime_under_16: /usr/lib/x86_64-linux-gnu/libgmpxx.so
src/prime_under_16: src/CMakeFiles/prime_under_16.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joshua/gits/libsnark-circuit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable prime_under_16"
	cd /home/joshua/gits/libsnark-circuit/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prime_under_16.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/prime_under_16.dir/build: src/prime_under_16

.PHONY : src/CMakeFiles/prime_under_16.dir/build

src/CMakeFiles/prime_under_16.dir/clean:
	cd /home/joshua/gits/libsnark-circuit/build/src && $(CMAKE_COMMAND) -P CMakeFiles/prime_under_16.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/prime_under_16.dir/clean

src/CMakeFiles/prime_under_16.dir/depend:
	cd /home/joshua/gits/libsnark-circuit/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joshua/gits/libsnark-circuit /home/joshua/gits/libsnark-circuit/src /home/joshua/gits/libsnark-circuit/build /home/joshua/gits/libsnark-circuit/build/src /home/joshua/gits/libsnark-circuit/build/src/CMakeFiles/prime_under_16.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/prime_under_16.dir/depend

