# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/bruno/paradiseo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bruno/paradiseo/build

# Include any dependencies generated for this target.
include eo/src/CMakeFiles/eo.dir/depend.make

# Include the progress variables for this target.
include eo/src/CMakeFiles/eo.dir/progress.make

# Include the compile flags for this target's objects.
include eo/src/CMakeFiles/eo.dir/flags.make

eo/src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o: eo/src/CMakeFiles/eo.dir/flags.make
eo/src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o: ../eo/src/eoFunctorStore.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bruno/paradiseo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object eo/src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/eo.dir/eoFunctorStore.cpp.o -c /home/bruno/paradiseo/eo/src/eoFunctorStore.cpp

eo/src/CMakeFiles/eo.dir/eoFunctorStore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eo.dir/eoFunctorStore.cpp.i"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bruno/paradiseo/eo/src/eoFunctorStore.cpp > CMakeFiles/eo.dir/eoFunctorStore.cpp.i

eo/src/CMakeFiles/eo.dir/eoFunctorStore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eo.dir/eoFunctorStore.cpp.s"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bruno/paradiseo/eo/src/eoFunctorStore.cpp -o CMakeFiles/eo.dir/eoFunctorStore.cpp.s

eo/src/CMakeFiles/eo.dir/eoPersistent.cpp.o: eo/src/CMakeFiles/eo.dir/flags.make
eo/src/CMakeFiles/eo.dir/eoPersistent.cpp.o: ../eo/src/eoPersistent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bruno/paradiseo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object eo/src/CMakeFiles/eo.dir/eoPersistent.cpp.o"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/eo.dir/eoPersistent.cpp.o -c /home/bruno/paradiseo/eo/src/eoPersistent.cpp

eo/src/CMakeFiles/eo.dir/eoPersistent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eo.dir/eoPersistent.cpp.i"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bruno/paradiseo/eo/src/eoPersistent.cpp > CMakeFiles/eo.dir/eoPersistent.cpp.i

eo/src/CMakeFiles/eo.dir/eoPersistent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eo.dir/eoPersistent.cpp.s"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bruno/paradiseo/eo/src/eoPersistent.cpp -o CMakeFiles/eo.dir/eoPersistent.cpp.s

eo/src/CMakeFiles/eo.dir/eoPrintable.cpp.o: eo/src/CMakeFiles/eo.dir/flags.make
eo/src/CMakeFiles/eo.dir/eoPrintable.cpp.o: ../eo/src/eoPrintable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bruno/paradiseo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object eo/src/CMakeFiles/eo.dir/eoPrintable.cpp.o"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/eo.dir/eoPrintable.cpp.o -c /home/bruno/paradiseo/eo/src/eoPrintable.cpp

eo/src/CMakeFiles/eo.dir/eoPrintable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eo.dir/eoPrintable.cpp.i"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bruno/paradiseo/eo/src/eoPrintable.cpp > CMakeFiles/eo.dir/eoPrintable.cpp.i

eo/src/CMakeFiles/eo.dir/eoPrintable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eo.dir/eoPrintable.cpp.s"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bruno/paradiseo/eo/src/eoPrintable.cpp -o CMakeFiles/eo.dir/eoPrintable.cpp.s

eo/src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o: eo/src/CMakeFiles/eo.dir/flags.make
eo/src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o: ../eo/src/eoCtrlCContinue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bruno/paradiseo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object eo/src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o -c /home/bruno/paradiseo/eo/src/eoCtrlCContinue.cpp

eo/src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eo.dir/eoCtrlCContinue.cpp.i"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bruno/paradiseo/eo/src/eoCtrlCContinue.cpp > CMakeFiles/eo.dir/eoCtrlCContinue.cpp.i

eo/src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eo.dir/eoCtrlCContinue.cpp.s"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bruno/paradiseo/eo/src/eoCtrlCContinue.cpp -o CMakeFiles/eo.dir/eoCtrlCContinue.cpp.s

eo/src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o: eo/src/CMakeFiles/eo.dir/flags.make
eo/src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o: ../eo/src/eoScalarFitnessAssembled.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bruno/paradiseo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object eo/src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o -c /home/bruno/paradiseo/eo/src/eoScalarFitnessAssembled.cpp

eo/src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.i"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bruno/paradiseo/eo/src/eoScalarFitnessAssembled.cpp > CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.i

eo/src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.s"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bruno/paradiseo/eo/src/eoScalarFitnessAssembled.cpp -o CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.s

eo/src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o: eo/src/CMakeFiles/eo.dir/flags.make
eo/src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o: ../eo/src/eoSIGContinue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bruno/paradiseo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object eo/src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/eo.dir/eoSIGContinue.cpp.o -c /home/bruno/paradiseo/eo/src/eoSIGContinue.cpp

eo/src/CMakeFiles/eo.dir/eoSIGContinue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eo.dir/eoSIGContinue.cpp.i"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bruno/paradiseo/eo/src/eoSIGContinue.cpp > CMakeFiles/eo.dir/eoSIGContinue.cpp.i

eo/src/CMakeFiles/eo.dir/eoSIGContinue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eo.dir/eoSIGContinue.cpp.s"
	cd /home/bruno/paradiseo/build/eo/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bruno/paradiseo/eo/src/eoSIGContinue.cpp -o CMakeFiles/eo.dir/eoSIGContinue.cpp.s

# Object files for target eo
eo_OBJECTS = \
"CMakeFiles/eo.dir/eoFunctorStore.cpp.o" \
"CMakeFiles/eo.dir/eoPersistent.cpp.o" \
"CMakeFiles/eo.dir/eoPrintable.cpp.o" \
"CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o" \
"CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o" \
"CMakeFiles/eo.dir/eoSIGContinue.cpp.o"

# External object files for target eo
eo_EXTERNAL_OBJECTS =

lib/libeo.a: eo/src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o
lib/libeo.a: eo/src/CMakeFiles/eo.dir/eoPersistent.cpp.o
lib/libeo.a: eo/src/CMakeFiles/eo.dir/eoPrintable.cpp.o
lib/libeo.a: eo/src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o
lib/libeo.a: eo/src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o
lib/libeo.a: eo/src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o
lib/libeo.a: eo/src/CMakeFiles/eo.dir/build.make
lib/libeo.a: eo/src/CMakeFiles/eo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bruno/paradiseo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library ../../lib/libeo.a"
	cd /home/bruno/paradiseo/build/eo/src && $(CMAKE_COMMAND) -P CMakeFiles/eo.dir/cmake_clean_target.cmake
	cd /home/bruno/paradiseo/build/eo/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
eo/src/CMakeFiles/eo.dir/build: lib/libeo.a

.PHONY : eo/src/CMakeFiles/eo.dir/build

eo/src/CMakeFiles/eo.dir/clean:
	cd /home/bruno/paradiseo/build/eo/src && $(CMAKE_COMMAND) -P CMakeFiles/eo.dir/cmake_clean.cmake
.PHONY : eo/src/CMakeFiles/eo.dir/clean

eo/src/CMakeFiles/eo.dir/depend:
	cd /home/bruno/paradiseo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bruno/paradiseo /home/bruno/paradiseo/eo/src /home/bruno/paradiseo/build /home/bruno/paradiseo/build/eo/src /home/bruno/paradiseo/build/eo/src/CMakeFiles/eo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : eo/src/CMakeFiles/eo.dir/depend

