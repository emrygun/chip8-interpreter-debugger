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
CMAKE_SOURCE_DIR = /home/emre/repos/chip8-interpreter-debugger

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/emre/repos/chip8-interpreter-debugger/make

# Include any dependencies generated for this target.
include CMakeFiles/chip8-interpreter-debugger.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/chip8-interpreter-debugger.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chip8-interpreter-debugger.dir/flags.make

CMakeFiles/chip8-interpreter-debugger.dir/src/main.c.o: CMakeFiles/chip8-interpreter-debugger.dir/flags.make
CMakeFiles/chip8-interpreter-debugger.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/emre/repos/chip8-interpreter-debugger/make/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/chip8-interpreter-debugger.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chip8-interpreter-debugger.dir/src/main.c.o   -c /home/emre/repos/chip8-interpreter-debugger/src/main.c

CMakeFiles/chip8-interpreter-debugger.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chip8-interpreter-debugger.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/emre/repos/chip8-interpreter-debugger/src/main.c > CMakeFiles/chip8-interpreter-debugger.dir/src/main.c.i

CMakeFiles/chip8-interpreter-debugger.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chip8-interpreter-debugger.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/emre/repos/chip8-interpreter-debugger/src/main.c -o CMakeFiles/chip8-interpreter-debugger.dir/src/main.c.s

CMakeFiles/chip8-interpreter-debugger.dir/src/chip8.c.o: CMakeFiles/chip8-interpreter-debugger.dir/flags.make
CMakeFiles/chip8-interpreter-debugger.dir/src/chip8.c.o: ../src/chip8.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/emre/repos/chip8-interpreter-debugger/make/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/chip8-interpreter-debugger.dir/src/chip8.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chip8-interpreter-debugger.dir/src/chip8.c.o   -c /home/emre/repos/chip8-interpreter-debugger/src/chip8.c

CMakeFiles/chip8-interpreter-debugger.dir/src/chip8.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chip8-interpreter-debugger.dir/src/chip8.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/emre/repos/chip8-interpreter-debugger/src/chip8.c > CMakeFiles/chip8-interpreter-debugger.dir/src/chip8.c.i

CMakeFiles/chip8-interpreter-debugger.dir/src/chip8.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chip8-interpreter-debugger.dir/src/chip8.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/emre/repos/chip8-interpreter-debugger/src/chip8.c -o CMakeFiles/chip8-interpreter-debugger.dir/src/chip8.c.s

CMakeFiles/chip8-interpreter-debugger.dir/src/utils.c.o: CMakeFiles/chip8-interpreter-debugger.dir/flags.make
CMakeFiles/chip8-interpreter-debugger.dir/src/utils.c.o: ../src/utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/emre/repos/chip8-interpreter-debugger/make/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/chip8-interpreter-debugger.dir/src/utils.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chip8-interpreter-debugger.dir/src/utils.c.o   -c /home/emre/repos/chip8-interpreter-debugger/src/utils.c

CMakeFiles/chip8-interpreter-debugger.dir/src/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chip8-interpreter-debugger.dir/src/utils.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/emre/repos/chip8-interpreter-debugger/src/utils.c > CMakeFiles/chip8-interpreter-debugger.dir/src/utils.c.i

CMakeFiles/chip8-interpreter-debugger.dir/src/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chip8-interpreter-debugger.dir/src/utils.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/emre/repos/chip8-interpreter-debugger/src/utils.c -o CMakeFiles/chip8-interpreter-debugger.dir/src/utils.c.s

# Object files for target chip8-interpreter-debugger
chip8__interpreter__debugger_OBJECTS = \
"CMakeFiles/chip8-interpreter-debugger.dir/src/main.c.o" \
"CMakeFiles/chip8-interpreter-debugger.dir/src/chip8.c.o" \
"CMakeFiles/chip8-interpreter-debugger.dir/src/utils.c.o"

# External object files for target chip8-interpreter-debugger
chip8__interpreter__debugger_EXTERNAL_OBJECTS =

chip8-interpreter-debugger: CMakeFiles/chip8-interpreter-debugger.dir/src/main.c.o
chip8-interpreter-debugger: CMakeFiles/chip8-interpreter-debugger.dir/src/chip8.c.o
chip8-interpreter-debugger: CMakeFiles/chip8-interpreter-debugger.dir/src/utils.c.o
chip8-interpreter-debugger: CMakeFiles/chip8-interpreter-debugger.dir/build.make
chip8-interpreter-debugger: /usr/lib/x86_64-linux-gnu/libcurses.so
chip8-interpreter-debugger: CMakeFiles/chip8-interpreter-debugger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/emre/repos/chip8-interpreter-debugger/make/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable chip8-interpreter-debugger"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chip8-interpreter-debugger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chip8-interpreter-debugger.dir/build: chip8-interpreter-debugger

.PHONY : CMakeFiles/chip8-interpreter-debugger.dir/build

CMakeFiles/chip8-interpreter-debugger.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/chip8-interpreter-debugger.dir/cmake_clean.cmake
.PHONY : CMakeFiles/chip8-interpreter-debugger.dir/clean

CMakeFiles/chip8-interpreter-debugger.dir/depend:
	cd /home/emre/repos/chip8-interpreter-debugger/make && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/emre/repos/chip8-interpreter-debugger /home/emre/repos/chip8-interpreter-debugger /home/emre/repos/chip8-interpreter-debugger/make /home/emre/repos/chip8-interpreter-debugger/make /home/emre/repos/chip8-interpreter-debugger/make/CMakeFiles/chip8-interpreter-debugger.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/chip8-interpreter-debugger.dir/depend

