# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.23.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.23.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build

# Include any dependencies generated for this target.
include external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/compiler_depend.make

# Include the progress variables for this target.
include external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/flags.make

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.o: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/flags.make
external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.o: ../external/glfw-3.1.2/tests/cursor.c
external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.o: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.o"
	cd /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build/external/glfw-3.1.2/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.o -MF CMakeFiles/cursor.dir/cursor.c.o.d -o CMakeFiles/cursor.dir/cursor.c.o -c /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/external/glfw-3.1.2/tests/cursor.c

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cursor.dir/cursor.c.i"
	cd /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build/external/glfw-3.1.2/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/external/glfw-3.1.2/tests/cursor.c > CMakeFiles/cursor.dir/cursor.c.i

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cursor.dir/cursor.c.s"
	cd /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build/external/glfw-3.1.2/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/external/glfw-3.1.2/tests/cursor.c -o CMakeFiles/cursor.dir/cursor.c.s

# Object files for target cursor
cursor_OBJECTS = \
"CMakeFiles/cursor.dir/cursor.c.o"

# External object files for target cursor
cursor_EXTERNAL_OBJECTS =

external/glfw-3.1.2/tests/cursor: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.o
external/glfw-3.1.2/tests/cursor: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/build.make
external/glfw-3.1.2/tests/cursor: external/glfw-3.1.2/src/libglfw3.a
external/glfw-3.1.2/tests/cursor: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cursor"
	cd /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build/external/glfw-3.1.2/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cursor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/build: external/glfw-3.1.2/tests/cursor
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/build

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/clean:
	cd /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build/external/glfw-3.1.2/tests && $(CMAKE_COMMAND) -P CMakeFiles/cursor.dir/cmake_clean.cmake
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/clean

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/depend:
	cd /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/external/glfw-3.1.2/tests /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build/external/glfw-3.1.2/tests /Users/s0ran/Desktop/Laboratory/Assignments/Comb-IPCG/build/external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/depend

