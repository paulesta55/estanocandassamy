# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/paul/clion-2018.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/paul/clion-2018.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/paul/estanocandassamy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paul/estanocandassamy/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/src/client/main.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/client/main.cpp.o: ../src/client/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/estanocandassamy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/client.dir/src/client/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/src/client/main.cpp.o -c /home/paul/estanocandassamy/src/client/main.cpp

CMakeFiles/client.dir/src/client/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/src/client/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paul/estanocandassamy/src/client/main.cpp > CMakeFiles/client.dir/src/client/main.cpp.i

CMakeFiles/client.dir/src/client/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/client/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paul/estanocandassamy/src/client/main.cpp -o CMakeFiles/client.dir/src/client/main.cpp.s

CMakeFiles/client.dir/src/shared/state/ResManager.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/shared/state/ResManager.cpp.o: ../src/shared/state/ResManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/estanocandassamy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/client.dir/src/shared/state/ResManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/src/shared/state/ResManager.cpp.o -c /home/paul/estanocandassamy/src/shared/state/ResManager.cpp

CMakeFiles/client.dir/src/shared/state/ResManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/src/shared/state/ResManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paul/estanocandassamy/src/shared/state/ResManager.cpp > CMakeFiles/client.dir/src/shared/state/ResManager.cpp.i

CMakeFiles/client.dir/src/shared/state/ResManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/shared/state/ResManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paul/estanocandassamy/src/shared/state/ResManager.cpp -o CMakeFiles/client.dir/src/shared/state/ResManager.cpp.s

CMakeFiles/client.dir/extern/jsoncpp-1.8.0/jsoncpp.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/extern/jsoncpp-1.8.0/jsoncpp.cpp.o: ../extern/jsoncpp-1.8.0/jsoncpp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/estanocandassamy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/client.dir/extern/jsoncpp-1.8.0/jsoncpp.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/extern/jsoncpp-1.8.0/jsoncpp.cpp.o -c /home/paul/estanocandassamy/extern/jsoncpp-1.8.0/jsoncpp.cpp

CMakeFiles/client.dir/extern/jsoncpp-1.8.0/jsoncpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/extern/jsoncpp-1.8.0/jsoncpp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paul/estanocandassamy/extern/jsoncpp-1.8.0/jsoncpp.cpp > CMakeFiles/client.dir/extern/jsoncpp-1.8.0/jsoncpp.cpp.i

CMakeFiles/client.dir/extern/jsoncpp-1.8.0/jsoncpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/extern/jsoncpp-1.8.0/jsoncpp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paul/estanocandassamy/extern/jsoncpp-1.8.0/jsoncpp.cpp -o CMakeFiles/client.dir/extern/jsoncpp-1.8.0/jsoncpp.cpp.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/src/client/main.cpp.o" \
"CMakeFiles/client.dir/src/shared/state/ResManager.cpp.o" \
"CMakeFiles/client.dir/extern/jsoncpp-1.8.0/jsoncpp.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

../bin/client: CMakeFiles/client.dir/src/client/main.cpp.o
../bin/client: CMakeFiles/client.dir/src/shared/state/ResManager.cpp.o
../bin/client: CMakeFiles/client.dir/extern/jsoncpp-1.8.0/jsoncpp.cpp.o
../bin/client: CMakeFiles/client.dir/build.make
../bin/client: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
../bin/client: /usr/lib/x86_64-linux-gnu/libsfml-window.so
../bin/client: /usr/lib/x86_64-linux-gnu/libsfml-system.so
../bin/client: /usr/lib/x86_64-linux-gnu/libsfml-network.so
../bin/client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/paul/estanocandassamy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../bin/client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: ../bin/client

.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd /home/paul/estanocandassamy/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paul/estanocandassamy /home/paul/estanocandassamy /home/paul/estanocandassamy/cmake-build-debug /home/paul/estanocandassamy/cmake-build-debug /home/paul/estanocandassamy/cmake-build-debug/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend
