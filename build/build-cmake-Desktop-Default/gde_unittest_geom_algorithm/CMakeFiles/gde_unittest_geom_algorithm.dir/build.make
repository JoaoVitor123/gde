# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joao/GDE/gde/build/cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joao/GDE/gde/build/build-cmake-Desktop-Default

# Include any dependencies generated for this target.
include gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/depend.make

# Include the progress variables for this target.
include gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/progress.make

# Include the compile flags for this target's objects.
include gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/flags.make

gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o: gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/flags.make
gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o: /home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/joao/GDE/gde/build/build-cmake-Desktop-Default/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o"
	cd /home/joao/GDE/gde/build/build-cmake-Desktop-Default/gde_unittest_geom_algorithm && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o -c /home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp

gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.i"
	cd /home/joao/GDE/gde/build/build-cmake-Desktop-Default/gde_unittest_geom_algorithm && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp > CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.i

gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.s"
	cd /home/joao/GDE/gde/build/build-cmake-Desktop-Default/gde_unittest_geom_algorithm && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp -o CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.s

gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o.requires:
.PHONY : gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o.requires

gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o.provides: gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o.requires
	$(MAKE) -f gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/build.make gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o.provides.build
.PHONY : gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o.provides

gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o.provides.build: gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o

# Object files for target gde_unittest_geom_algorithm
gde_unittest_geom_algorithm_OBJECTS = \
"CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o"

# External object files for target gde_unittest_geom_algorithm
gde_unittest_geom_algorithm_EXTERNAL_OBJECTS =

bin/gde_unittest_geom_algorithm: gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o
bin/gde_unittest_geom_algorithm: gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/build.make
bin/gde_unittest_geom_algorithm: bin/libgde_mod_geom_algorithm.a
bin/gde_unittest_geom_algorithm: gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/gde_unittest_geom_algorithm"
	cd /home/joao/GDE/gde/build/build-cmake-Desktop-Default/gde_unittest_geom_algorithm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gde_unittest_geom_algorithm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/build: bin/gde_unittest_geom_algorithm
.PHONY : gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/build

gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/requires: gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/home/joao/GDE/gde/src/unittest/geom/algorithm/main.cpp.o.requires
.PHONY : gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/requires

gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/clean:
	cd /home/joao/GDE/gde/build/build-cmake-Desktop-Default/gde_unittest_geom_algorithm && $(CMAKE_COMMAND) -P CMakeFiles/gde_unittest_geom_algorithm.dir/cmake_clean.cmake
.PHONY : gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/clean

gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/depend:
	cd /home/joao/GDE/gde/build/build-cmake-Desktop-Default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joao/GDE/gde/build/cmake /home/joao/GDE/gde/build/cmake/gde_unittest_geom_algorithm /home/joao/GDE/gde/build/build-cmake-Desktop-Default /home/joao/GDE/gde/build/build-cmake-Desktop-Default/gde_unittest_geom_algorithm /home/joao/GDE/gde/build/build-cmake-Desktop-Default/gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : gde_unittest_geom_algorithm/CMakeFiles/gde_unittest_geom_algorithm.dir/depend

