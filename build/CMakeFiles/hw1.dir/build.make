# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /usr/local/cmake/cmake-3.17.3-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake/cmake-3.17.3-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/build

# Include any dependencies generated for this target.
include CMakeFiles/hw1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw1.dir/flags.make

CMakeFiles/hw1.dir/Database.cpp.o: CMakeFiles/hw1.dir/flags.make
CMakeFiles/hw1.dir/Database.cpp.o: /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src/Database.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw1.dir/Database.cpp.o"
	/data/ssd/hcli/usr/local/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw1.dir/Database.cpp.o -c /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src/Database.cpp

CMakeFiles/hw1.dir/Database.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw1.dir/Database.cpp.i"
	/data/ssd/hcli/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src/Database.cpp > CMakeFiles/hw1.dir/Database.cpp.i

CMakeFiles/hw1.dir/Database.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw1.dir/Database.cpp.s"
	/data/ssd/hcli/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src/Database.cpp -o CMakeFiles/hw1.dir/Database.cpp.s

CMakeFiles/hw1.dir/Partitioner.cpp.o: CMakeFiles/hw1.dir/flags.make
CMakeFiles/hw1.dir/Partitioner.cpp.o: /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src/Partitioner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/hw1.dir/Partitioner.cpp.o"
	/data/ssd/hcli/usr/local/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw1.dir/Partitioner.cpp.o -c /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src/Partitioner.cpp

CMakeFiles/hw1.dir/Partitioner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw1.dir/Partitioner.cpp.i"
	/data/ssd/hcli/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src/Partitioner.cpp > CMakeFiles/hw1.dir/Partitioner.cpp.i

CMakeFiles/hw1.dir/Partitioner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw1.dir/Partitioner.cpp.s"
	/data/ssd/hcli/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src/Partitioner.cpp -o CMakeFiles/hw1.dir/Partitioner.cpp.s

CMakeFiles/hw1.dir/main.cpp.o: CMakeFiles/hw1.dir/flags.make
CMakeFiles/hw1.dir/main.cpp.o: /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/hw1.dir/main.cpp.o"
	/data/ssd/hcli/usr/local/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw1.dir/main.cpp.o -c /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src/main.cpp

CMakeFiles/hw1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw1.dir/main.cpp.i"
	/data/ssd/hcli/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src/main.cpp > CMakeFiles/hw1.dir/main.cpp.i

CMakeFiles/hw1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw1.dir/main.cpp.s"
	/data/ssd/hcli/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src/main.cpp -o CMakeFiles/hw1.dir/main.cpp.s

# Object files for target hw1
hw1_OBJECTS = \
"CMakeFiles/hw1.dir/Database.cpp.o" \
"CMakeFiles/hw1.dir/Partitioner.cpp.o" \
"CMakeFiles/hw1.dir/main.cpp.o"

# External object files for target hw1
hw1_EXTERNAL_OBJECTS =

hw1: CMakeFiles/hw1.dir/Database.cpp.o
hw1: CMakeFiles/hw1.dir/Partitioner.cpp.o
hw1: CMakeFiles/hw1.dir/main.cpp.o
hw1: CMakeFiles/hw1.dir/build.make
hw1: CMakeFiles/hw1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable hw1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw1.dir/build: hw1

.PHONY : CMakeFiles/hw1.dir/build

CMakeFiles/hw1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw1.dir/clean

CMakeFiles/hw1.dir/depend:
	cd /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/src /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/build /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/build /data/ssd/qluo/coarse/CENG5270/CENG5270_HW1/build/CMakeFiles/hw1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw1.dir/depend

