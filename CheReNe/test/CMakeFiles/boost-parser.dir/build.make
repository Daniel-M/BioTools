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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/damejia/Academicos/Github/BioTools/CheReNe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/damejia/Academicos/Github/BioTools/CheReNe/test

# Include any dependencies generated for this target.
include CMakeFiles/boost-parser.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/boost-parser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/boost-parser.dir/flags.make

CMakeFiles/boost-parser.dir/src/boost_test.cpp.o: CMakeFiles/boost-parser.dir/flags.make
CMakeFiles/boost-parser.dir/src/boost_test.cpp.o: ../src/boost_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/damejia/Academicos/Github/BioTools/CheReNe/test/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/boost-parser.dir/src/boost_test.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/boost-parser.dir/src/boost_test.cpp.o -c /home/damejia/Academicos/Github/BioTools/CheReNe/src/boost_test.cpp

CMakeFiles/boost-parser.dir/src/boost_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boost-parser.dir/src/boost_test.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/damejia/Academicos/Github/BioTools/CheReNe/src/boost_test.cpp > CMakeFiles/boost-parser.dir/src/boost_test.cpp.i

CMakeFiles/boost-parser.dir/src/boost_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boost-parser.dir/src/boost_test.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/damejia/Academicos/Github/BioTools/CheReNe/src/boost_test.cpp -o CMakeFiles/boost-parser.dir/src/boost_test.cpp.s

CMakeFiles/boost-parser.dir/src/boost_test.cpp.o.requires:
.PHONY : CMakeFiles/boost-parser.dir/src/boost_test.cpp.o.requires

CMakeFiles/boost-parser.dir/src/boost_test.cpp.o.provides: CMakeFiles/boost-parser.dir/src/boost_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/boost-parser.dir/build.make CMakeFiles/boost-parser.dir/src/boost_test.cpp.o.provides.build
.PHONY : CMakeFiles/boost-parser.dir/src/boost_test.cpp.o.provides

CMakeFiles/boost-parser.dir/src/boost_test.cpp.o.provides.build: CMakeFiles/boost-parser.dir/src/boost_test.cpp.o

# Object files for target boost-parser
boost__parser_OBJECTS = \
"CMakeFiles/boost-parser.dir/src/boost_test.cpp.o"

# External object files for target boost-parser
boost__parser_EXTERNAL_OBJECTS =

boost-parser: CMakeFiles/boost-parser.dir/src/boost_test.cpp.o
boost-parser: CMakeFiles/boost-parser.dir/build.make
boost-parser: CMakeFiles/boost-parser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable boost-parser"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/boost-parser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/boost-parser.dir/build: boost-parser
.PHONY : CMakeFiles/boost-parser.dir/build

CMakeFiles/boost-parser.dir/requires: CMakeFiles/boost-parser.dir/src/boost_test.cpp.o.requires
.PHONY : CMakeFiles/boost-parser.dir/requires

CMakeFiles/boost-parser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/boost-parser.dir/cmake_clean.cmake
.PHONY : CMakeFiles/boost-parser.dir/clean

CMakeFiles/boost-parser.dir/depend:
	cd /home/damejia/Academicos/Github/BioTools/CheReNe/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/damejia/Academicos/Github/BioTools/CheReNe /home/damejia/Academicos/Github/BioTools/CheReNe /home/damejia/Academicos/Github/BioTools/CheReNe/test /home/damejia/Academicos/Github/BioTools/CheReNe/test /home/damejia/Academicos/Github/BioTools/CheReNe/test/CMakeFiles/boost-parser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/boost-parser.dir/depend

