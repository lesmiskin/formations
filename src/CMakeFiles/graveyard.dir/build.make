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
CMAKE_SOURCE_DIR = /home/les/dev/graveyard/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/les/dev/graveyard/src

# Include any dependencies generated for this target.
include CMakeFiles/graveyard.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/graveyard.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/graveyard.dir/flags.make

CMakeFiles/graveyard.dir/enemy.c.o: CMakeFiles/graveyard.dir/flags.make
CMakeFiles/graveyard.dir/enemy.c.o: enemy.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/les/dev/graveyard/src/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/graveyard.dir/enemy.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/graveyard.dir/enemy.c.o   -c /home/les/dev/graveyard/src/enemy.c

CMakeFiles/graveyard.dir/enemy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/graveyard.dir/enemy.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/les/dev/graveyard/src/enemy.c > CMakeFiles/graveyard.dir/enemy.c.i

CMakeFiles/graveyard.dir/enemy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/graveyard.dir/enemy.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/les/dev/graveyard/src/enemy.c -o CMakeFiles/graveyard.dir/enemy.c.s

CMakeFiles/graveyard.dir/enemy.c.o.requires:
.PHONY : CMakeFiles/graveyard.dir/enemy.c.o.requires

CMakeFiles/graveyard.dir/enemy.c.o.provides: CMakeFiles/graveyard.dir/enemy.c.o.requires
	$(MAKE) -f CMakeFiles/graveyard.dir/build.make CMakeFiles/graveyard.dir/enemy.c.o.provides.build
.PHONY : CMakeFiles/graveyard.dir/enemy.c.o.provides

CMakeFiles/graveyard.dir/enemy.c.o.provides.build: CMakeFiles/graveyard.dir/enemy.c.o

CMakeFiles/graveyard.dir/hud.c.o: CMakeFiles/graveyard.dir/flags.make
CMakeFiles/graveyard.dir/hud.c.o: hud.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/les/dev/graveyard/src/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/graveyard.dir/hud.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/graveyard.dir/hud.c.o   -c /home/les/dev/graveyard/src/hud.c

CMakeFiles/graveyard.dir/hud.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/graveyard.dir/hud.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/les/dev/graveyard/src/hud.c > CMakeFiles/graveyard.dir/hud.c.i

CMakeFiles/graveyard.dir/hud.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/graveyard.dir/hud.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/les/dev/graveyard/src/hud.c -o CMakeFiles/graveyard.dir/hud.c.s

CMakeFiles/graveyard.dir/hud.c.o.requires:
.PHONY : CMakeFiles/graveyard.dir/hud.c.o.requires

CMakeFiles/graveyard.dir/hud.c.o.provides: CMakeFiles/graveyard.dir/hud.c.o.requires
	$(MAKE) -f CMakeFiles/graveyard.dir/build.make CMakeFiles/graveyard.dir/hud.c.o.provides.build
.PHONY : CMakeFiles/graveyard.dir/hud.c.o.provides

CMakeFiles/graveyard.dir/hud.c.o.provides.build: CMakeFiles/graveyard.dir/hud.c.o

CMakeFiles/graveyard.dir/player.c.o: CMakeFiles/graveyard.dir/flags.make
CMakeFiles/graveyard.dir/player.c.o: player.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/les/dev/graveyard/src/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/graveyard.dir/player.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/graveyard.dir/player.c.o   -c /home/les/dev/graveyard/src/player.c

CMakeFiles/graveyard.dir/player.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/graveyard.dir/player.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/les/dev/graveyard/src/player.c > CMakeFiles/graveyard.dir/player.c.i

CMakeFiles/graveyard.dir/player.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/graveyard.dir/player.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/les/dev/graveyard/src/player.c -o CMakeFiles/graveyard.dir/player.c.s

CMakeFiles/graveyard.dir/player.c.o.requires:
.PHONY : CMakeFiles/graveyard.dir/player.c.o.requires

CMakeFiles/graveyard.dir/player.c.o.provides: CMakeFiles/graveyard.dir/player.c.o.requires
	$(MAKE) -f CMakeFiles/graveyard.dir/build.make CMakeFiles/graveyard.dir/player.c.o.provides.build
.PHONY : CMakeFiles/graveyard.dir/player.c.o.provides

CMakeFiles/graveyard.dir/player.c.o.provides.build: CMakeFiles/graveyard.dir/player.c.o

CMakeFiles/graveyard.dir/scene.c.o: CMakeFiles/graveyard.dir/flags.make
CMakeFiles/graveyard.dir/scene.c.o: scene.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/les/dev/graveyard/src/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/graveyard.dir/scene.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/graveyard.dir/scene.c.o   -c /home/les/dev/graveyard/src/scene.c

CMakeFiles/graveyard.dir/scene.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/graveyard.dir/scene.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/les/dev/graveyard/src/scene.c > CMakeFiles/graveyard.dir/scene.c.i

CMakeFiles/graveyard.dir/scene.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/graveyard.dir/scene.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/les/dev/graveyard/src/scene.c -o CMakeFiles/graveyard.dir/scene.c.s

CMakeFiles/graveyard.dir/scene.c.o.requires:
.PHONY : CMakeFiles/graveyard.dir/scene.c.o.requires

CMakeFiles/graveyard.dir/scene.c.o.provides: CMakeFiles/graveyard.dir/scene.c.o.requires
	$(MAKE) -f CMakeFiles/graveyard.dir/build.make CMakeFiles/graveyard.dir/scene.c.o.provides.build
.PHONY : CMakeFiles/graveyard.dir/scene.c.o.provides

CMakeFiles/graveyard.dir/scene.c.o.provides.build: CMakeFiles/graveyard.dir/scene.c.o

CMakeFiles/graveyard.dir/renderer.c.o: CMakeFiles/graveyard.dir/flags.make
CMakeFiles/graveyard.dir/renderer.c.o: renderer.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/les/dev/graveyard/src/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/graveyard.dir/renderer.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/graveyard.dir/renderer.c.o   -c /home/les/dev/graveyard/src/renderer.c

CMakeFiles/graveyard.dir/renderer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/graveyard.dir/renderer.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/les/dev/graveyard/src/renderer.c > CMakeFiles/graveyard.dir/renderer.c.i

CMakeFiles/graveyard.dir/renderer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/graveyard.dir/renderer.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/les/dev/graveyard/src/renderer.c -o CMakeFiles/graveyard.dir/renderer.c.s

CMakeFiles/graveyard.dir/renderer.c.o.requires:
.PHONY : CMakeFiles/graveyard.dir/renderer.c.o.requires

CMakeFiles/graveyard.dir/renderer.c.o.provides: CMakeFiles/graveyard.dir/renderer.c.o.requires
	$(MAKE) -f CMakeFiles/graveyard.dir/build.make CMakeFiles/graveyard.dir/renderer.c.o.provides.build
.PHONY : CMakeFiles/graveyard.dir/renderer.c.o.provides

CMakeFiles/graveyard.dir/renderer.c.o.provides.build: CMakeFiles/graveyard.dir/renderer.c.o

CMakeFiles/graveyard.dir/assets.c.o: CMakeFiles/graveyard.dir/flags.make
CMakeFiles/graveyard.dir/assets.c.o: assets.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/les/dev/graveyard/src/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/graveyard.dir/assets.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/graveyard.dir/assets.c.o   -c /home/les/dev/graveyard/src/assets.c

CMakeFiles/graveyard.dir/assets.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/graveyard.dir/assets.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/les/dev/graveyard/src/assets.c > CMakeFiles/graveyard.dir/assets.c.i

CMakeFiles/graveyard.dir/assets.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/graveyard.dir/assets.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/les/dev/graveyard/src/assets.c -o CMakeFiles/graveyard.dir/assets.c.s

CMakeFiles/graveyard.dir/assets.c.o.requires:
.PHONY : CMakeFiles/graveyard.dir/assets.c.o.requires

CMakeFiles/graveyard.dir/assets.c.o.provides: CMakeFiles/graveyard.dir/assets.c.o.requires
	$(MAKE) -f CMakeFiles/graveyard.dir/build.make CMakeFiles/graveyard.dir/assets.c.o.provides.build
.PHONY : CMakeFiles/graveyard.dir/assets.c.o.provides

CMakeFiles/graveyard.dir/assets.c.o.provides.build: CMakeFiles/graveyard.dir/assets.c.o

CMakeFiles/graveyard.dir/input.c.o: CMakeFiles/graveyard.dir/flags.make
CMakeFiles/graveyard.dir/input.c.o: input.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/les/dev/graveyard/src/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/graveyard.dir/input.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/graveyard.dir/input.c.o   -c /home/les/dev/graveyard/src/input.c

CMakeFiles/graveyard.dir/input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/graveyard.dir/input.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/les/dev/graveyard/src/input.c > CMakeFiles/graveyard.dir/input.c.i

CMakeFiles/graveyard.dir/input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/graveyard.dir/input.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/les/dev/graveyard/src/input.c -o CMakeFiles/graveyard.dir/input.c.s

CMakeFiles/graveyard.dir/input.c.o.requires:
.PHONY : CMakeFiles/graveyard.dir/input.c.o.requires

CMakeFiles/graveyard.dir/input.c.o.provides: CMakeFiles/graveyard.dir/input.c.o.requires
	$(MAKE) -f CMakeFiles/graveyard.dir/build.make CMakeFiles/graveyard.dir/input.c.o.provides.build
.PHONY : CMakeFiles/graveyard.dir/input.c.o.provides

CMakeFiles/graveyard.dir/input.c.o.provides.build: CMakeFiles/graveyard.dir/input.c.o

CMakeFiles/graveyard.dir/common.c.o: CMakeFiles/graveyard.dir/flags.make
CMakeFiles/graveyard.dir/common.c.o: common.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/les/dev/graveyard/src/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/graveyard.dir/common.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/graveyard.dir/common.c.o   -c /home/les/dev/graveyard/src/common.c

CMakeFiles/graveyard.dir/common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/graveyard.dir/common.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/les/dev/graveyard/src/common.c > CMakeFiles/graveyard.dir/common.c.i

CMakeFiles/graveyard.dir/common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/graveyard.dir/common.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/les/dev/graveyard/src/common.c -o CMakeFiles/graveyard.dir/common.c.s

CMakeFiles/graveyard.dir/common.c.o.requires:
.PHONY : CMakeFiles/graveyard.dir/common.c.o.requires

CMakeFiles/graveyard.dir/common.c.o.provides: CMakeFiles/graveyard.dir/common.c.o.requires
	$(MAKE) -f CMakeFiles/graveyard.dir/build.make CMakeFiles/graveyard.dir/common.c.o.provides.build
.PHONY : CMakeFiles/graveyard.dir/common.c.o.provides

CMakeFiles/graveyard.dir/common.c.o.provides.build: CMakeFiles/graveyard.dir/common.c.o

CMakeFiles/graveyard.dir/main.c.o: CMakeFiles/graveyard.dir/flags.make
CMakeFiles/graveyard.dir/main.c.o: main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/les/dev/graveyard/src/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/graveyard.dir/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/graveyard.dir/main.c.o   -c /home/les/dev/graveyard/src/main.c

CMakeFiles/graveyard.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/graveyard.dir/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/les/dev/graveyard/src/main.c > CMakeFiles/graveyard.dir/main.c.i

CMakeFiles/graveyard.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/graveyard.dir/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/les/dev/graveyard/src/main.c -o CMakeFiles/graveyard.dir/main.c.s

CMakeFiles/graveyard.dir/main.c.o.requires:
.PHONY : CMakeFiles/graveyard.dir/main.c.o.requires

CMakeFiles/graveyard.dir/main.c.o.provides: CMakeFiles/graveyard.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/graveyard.dir/build.make CMakeFiles/graveyard.dir/main.c.o.provides.build
.PHONY : CMakeFiles/graveyard.dir/main.c.o.provides

CMakeFiles/graveyard.dir/main.c.o.provides.build: CMakeFiles/graveyard.dir/main.c.o

# Object files for target graveyard
graveyard_OBJECTS = \
"CMakeFiles/graveyard.dir/enemy.c.o" \
"CMakeFiles/graveyard.dir/hud.c.o" \
"CMakeFiles/graveyard.dir/player.c.o" \
"CMakeFiles/graveyard.dir/scene.c.o" \
"CMakeFiles/graveyard.dir/renderer.c.o" \
"CMakeFiles/graveyard.dir/assets.c.o" \
"CMakeFiles/graveyard.dir/input.c.o" \
"CMakeFiles/graveyard.dir/common.c.o" \
"CMakeFiles/graveyard.dir/main.c.o"

# External object files for target graveyard
graveyard_EXTERNAL_OBJECTS =

graveyard: CMakeFiles/graveyard.dir/enemy.c.o
graveyard: CMakeFiles/graveyard.dir/hud.c.o
graveyard: CMakeFiles/graveyard.dir/player.c.o
graveyard: CMakeFiles/graveyard.dir/scene.c.o
graveyard: CMakeFiles/graveyard.dir/renderer.c.o
graveyard: CMakeFiles/graveyard.dir/assets.c.o
graveyard: CMakeFiles/graveyard.dir/input.c.o
graveyard: CMakeFiles/graveyard.dir/common.c.o
graveyard: CMakeFiles/graveyard.dir/main.c.o
graveyard: CMakeFiles/graveyard.dir/build.make
graveyard: /usr/lib/x86_64-linux-gnu/libSDL2main.a
graveyard: /usr/lib/x86_64-linux-gnu/libSDL2.so
graveyard: /usr/lib/x86_64-linux-gnu/libSDL2_image.so
graveyard: /usr/lib/x86_64-linux-gnu/libSDL2_mixer.so
graveyard: CMakeFiles/graveyard.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable graveyard"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graveyard.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/graveyard.dir/build: graveyard
.PHONY : CMakeFiles/graveyard.dir/build

CMakeFiles/graveyard.dir/requires: CMakeFiles/graveyard.dir/enemy.c.o.requires
CMakeFiles/graveyard.dir/requires: CMakeFiles/graveyard.dir/hud.c.o.requires
CMakeFiles/graveyard.dir/requires: CMakeFiles/graveyard.dir/player.c.o.requires
CMakeFiles/graveyard.dir/requires: CMakeFiles/graveyard.dir/scene.c.o.requires
CMakeFiles/graveyard.dir/requires: CMakeFiles/graveyard.dir/renderer.c.o.requires
CMakeFiles/graveyard.dir/requires: CMakeFiles/graveyard.dir/assets.c.o.requires
CMakeFiles/graveyard.dir/requires: CMakeFiles/graveyard.dir/input.c.o.requires
CMakeFiles/graveyard.dir/requires: CMakeFiles/graveyard.dir/common.c.o.requires
CMakeFiles/graveyard.dir/requires: CMakeFiles/graveyard.dir/main.c.o.requires
.PHONY : CMakeFiles/graveyard.dir/requires

CMakeFiles/graveyard.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/graveyard.dir/cmake_clean.cmake
.PHONY : CMakeFiles/graveyard.dir/clean

CMakeFiles/graveyard.dir/depend:
	cd /home/les/dev/graveyard/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/les/dev/graveyard/src /home/les/dev/graveyard/src /home/les/dev/graveyard/src /home/les/dev/graveyard/src /home/les/dev/graveyard/src/CMakeFiles/graveyard.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/graveyard.dir/depend
