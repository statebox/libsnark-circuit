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

# Utility rule file for ContinuousStart.

# Include the progress variables for this target.
include depends/libsnark/libsnark/CMakeFiles/ContinuousStart.dir/progress.make

depends/libsnark/libsnark/CMakeFiles/ContinuousStart:
	cd /home/joshua/gits/libsnark-circuit/build/depends/libsnark/libsnark && /usr/bin/ctest -D ContinuousStart

ContinuousStart: depends/libsnark/libsnark/CMakeFiles/ContinuousStart
ContinuousStart: depends/libsnark/libsnark/CMakeFiles/ContinuousStart.dir/build.make

.PHONY : ContinuousStart

# Rule to build all files generated by this target.
depends/libsnark/libsnark/CMakeFiles/ContinuousStart.dir/build: ContinuousStart

.PHONY : depends/libsnark/libsnark/CMakeFiles/ContinuousStart.dir/build

depends/libsnark/libsnark/CMakeFiles/ContinuousStart.dir/clean:
	cd /home/joshua/gits/libsnark-circuit/build/depends/libsnark/libsnark && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousStart.dir/cmake_clean.cmake
.PHONY : depends/libsnark/libsnark/CMakeFiles/ContinuousStart.dir/clean

depends/libsnark/libsnark/CMakeFiles/ContinuousStart.dir/depend:
	cd /home/joshua/gits/libsnark-circuit/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joshua/gits/libsnark-circuit /home/joshua/gits/libsnark-circuit/depends/libsnark/libsnark /home/joshua/gits/libsnark-circuit/build /home/joshua/gits/libsnark-circuit/build/depends/libsnark/libsnark /home/joshua/gits/libsnark-circuit/build/depends/libsnark/libsnark/CMakeFiles/ContinuousStart.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : depends/libsnark/libsnark/CMakeFiles/ContinuousStart.dir/depend

