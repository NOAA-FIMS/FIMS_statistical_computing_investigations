# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build

# Include any dependencies generated for this target.
include tools/CMakeFiles/stxxl_tool.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tools/CMakeFiles/stxxl_tool.dir/compiler_depend.make

# Include the progress variables for this target.
include tools/CMakeFiles/stxxl_tool.dir/progress.make

# Include the compile flags for this target's objects.
include tools/CMakeFiles/stxxl_tool.dir/flags.make

tools/CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.o: tools/CMakeFiles/stxxl_tool.dir/flags.make
tools/CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.o: ../tools/stxxl_tool.cpp
tools/CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.o: tools/CMakeFiles/stxxl_tool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.o"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tools/CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.o -MF CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.o.d -o CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.o -c /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/stxxl_tool.cpp

tools/CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.i"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/stxxl_tool.cpp > CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.i

tools/CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.s"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/stxxl_tool.cpp -o CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.s

tools/CMakeFiles/stxxl_tool.dir/create_files.cpp.o: tools/CMakeFiles/stxxl_tool.dir/flags.make
tools/CMakeFiles/stxxl_tool.dir/create_files.cpp.o: ../tools/create_files.cpp
tools/CMakeFiles/stxxl_tool.dir/create_files.cpp.o: tools/CMakeFiles/stxxl_tool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tools/CMakeFiles/stxxl_tool.dir/create_files.cpp.o"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tools/CMakeFiles/stxxl_tool.dir/create_files.cpp.o -MF CMakeFiles/stxxl_tool.dir/create_files.cpp.o.d -o CMakeFiles/stxxl_tool.dir/create_files.cpp.o -c /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/create_files.cpp

tools/CMakeFiles/stxxl_tool.dir/create_files.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stxxl_tool.dir/create_files.cpp.i"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/create_files.cpp > CMakeFiles/stxxl_tool.dir/create_files.cpp.i

tools/CMakeFiles/stxxl_tool.dir/create_files.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stxxl_tool.dir/create_files.cpp.s"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/create_files.cpp -o CMakeFiles/stxxl_tool.dir/create_files.cpp.s

tools/CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.o: tools/CMakeFiles/stxxl_tool.dir/flags.make
tools/CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.o: ../tools/benchmark_disks.cpp
tools/CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.o: tools/CMakeFiles/stxxl_tool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object tools/CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.o"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tools/CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.o -MF CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.o.d -o CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.o -c /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_disks.cpp

tools/CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.i"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_disks.cpp > CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.i

tools/CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.s"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_disks.cpp -o CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.s

tools/CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.o: tools/CMakeFiles/stxxl_tool.dir/flags.make
tools/CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.o: ../tools/benchmark_files.cpp
tools/CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.o: tools/CMakeFiles/stxxl_tool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object tools/CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.o"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tools/CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.o -MF CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.o.d -o CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.o -c /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_files.cpp

tools/CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.i"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_files.cpp > CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.i

tools/CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.s"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_files.cpp -o CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.s

tools/CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.o: tools/CMakeFiles/stxxl_tool.dir/flags.make
tools/CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.o: ../tools/benchmark_sort.cpp
tools/CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.o: tools/CMakeFiles/stxxl_tool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object tools/CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.o"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tools/CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.o -MF CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.o.d -o CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.o -c /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_sort.cpp

tools/CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.i"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_sort.cpp > CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.i

tools/CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.s"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_sort.cpp -o CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.s

tools/CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.o: tools/CMakeFiles/stxxl_tool.dir/flags.make
tools/CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.o: ../tools/benchmark_disks_random.cpp
tools/CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.o: tools/CMakeFiles/stxxl_tool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object tools/CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.o"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tools/CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.o -MF CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.o.d -o CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.o -c /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_disks_random.cpp

tools/CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.i"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_disks_random.cpp > CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.i

tools/CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.s"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_disks_random.cpp -o CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.s

tools/CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.o: tools/CMakeFiles/stxxl_tool.dir/flags.make
tools/CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.o: ../tools/benchmark_pqueue.cpp
tools/CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.o: tools/CMakeFiles/stxxl_tool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object tools/CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.o"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tools/CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.o -MF CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.o.d -o CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.o -c /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_pqueue.cpp

tools/CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.i"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_pqueue.cpp > CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.i

tools/CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.s"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/benchmark_pqueue.cpp -o CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.s

tools/CMakeFiles/stxxl_tool.dir/mlock.cpp.o: tools/CMakeFiles/stxxl_tool.dir/flags.make
tools/CMakeFiles/stxxl_tool.dir/mlock.cpp.o: ../tools/mlock.cpp
tools/CMakeFiles/stxxl_tool.dir/mlock.cpp.o: tools/CMakeFiles/stxxl_tool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object tools/CMakeFiles/stxxl_tool.dir/mlock.cpp.o"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tools/CMakeFiles/stxxl_tool.dir/mlock.cpp.o -MF CMakeFiles/stxxl_tool.dir/mlock.cpp.o.d -o CMakeFiles/stxxl_tool.dir/mlock.cpp.o -c /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/mlock.cpp

tools/CMakeFiles/stxxl_tool.dir/mlock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stxxl_tool.dir/mlock.cpp.i"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/mlock.cpp > CMakeFiles/stxxl_tool.dir/mlock.cpp.i

tools/CMakeFiles/stxxl_tool.dir/mlock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stxxl_tool.dir/mlock.cpp.s"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/mlock.cpp -o CMakeFiles/stxxl_tool.dir/mlock.cpp.s

tools/CMakeFiles/stxxl_tool.dir/mallinfo.cpp.o: tools/CMakeFiles/stxxl_tool.dir/flags.make
tools/CMakeFiles/stxxl_tool.dir/mallinfo.cpp.o: ../tools/mallinfo.cpp
tools/CMakeFiles/stxxl_tool.dir/mallinfo.cpp.o: tools/CMakeFiles/stxxl_tool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object tools/CMakeFiles/stxxl_tool.dir/mallinfo.cpp.o"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tools/CMakeFiles/stxxl_tool.dir/mallinfo.cpp.o -MF CMakeFiles/stxxl_tool.dir/mallinfo.cpp.o.d -o CMakeFiles/stxxl_tool.dir/mallinfo.cpp.o -c /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/mallinfo.cpp

tools/CMakeFiles/stxxl_tool.dir/mallinfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stxxl_tool.dir/mallinfo.cpp.i"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/mallinfo.cpp > CMakeFiles/stxxl_tool.dir/mallinfo.cpp.i

tools/CMakeFiles/stxxl_tool.dir/mallinfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stxxl_tool.dir/mallinfo.cpp.s"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools/mallinfo.cpp -o CMakeFiles/stxxl_tool.dir/mallinfo.cpp.s

# Object files for target stxxl_tool
stxxl_tool_OBJECTS = \
"CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.o" \
"CMakeFiles/stxxl_tool.dir/create_files.cpp.o" \
"CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.o" \
"CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.o" \
"CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.o" \
"CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.o" \
"CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.o" \
"CMakeFiles/stxxl_tool.dir/mlock.cpp.o" \
"CMakeFiles/stxxl_tool.dir/mallinfo.cpp.o"

# External object files for target stxxl_tool
stxxl_tool_EXTERNAL_OBJECTS =

tools/stxxl_tool: tools/CMakeFiles/stxxl_tool.dir/stxxl_tool.cpp.o
tools/stxxl_tool: tools/CMakeFiles/stxxl_tool.dir/create_files.cpp.o
tools/stxxl_tool: tools/CMakeFiles/stxxl_tool.dir/benchmark_disks.cpp.o
tools/stxxl_tool: tools/CMakeFiles/stxxl_tool.dir/benchmark_files.cpp.o
tools/stxxl_tool: tools/CMakeFiles/stxxl_tool.dir/benchmark_sort.cpp.o
tools/stxxl_tool: tools/CMakeFiles/stxxl_tool.dir/benchmark_disks_random.cpp.o
tools/stxxl_tool: tools/CMakeFiles/stxxl_tool.dir/benchmark_pqueue.cpp.o
tools/stxxl_tool: tools/CMakeFiles/stxxl_tool.dir/mlock.cpp.o
tools/stxxl_tool: tools/CMakeFiles/stxxl_tool.dir/mallinfo.cpp.o
tools/stxxl_tool: tools/CMakeFiles/stxxl_tool.dir/build.make
tools/stxxl_tool: lib/libstxxl_debug.a
tools/stxxl_tool: tools/CMakeFiles/stxxl_tool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable stxxl_tool"
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stxxl_tool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/CMakeFiles/stxxl_tool.dir/build: tools/stxxl_tool
.PHONY : tools/CMakeFiles/stxxl_tool.dir/build

tools/CMakeFiles/stxxl_tool.dir/clean:
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools && $(CMAKE_COMMAND) -P CMakeFiles/stxxl_tool.dir/cmake_clean.cmake
.PHONY : tools/CMakeFiles/stxxl_tool.dir/clean

tools/CMakeFiles/stxxl_tool.dir/depend:
	cd /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/tools /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools /Users/mattadmin/FIMS-Testing/FIMS_statistical_computing_investigations/include/stxxl/build/tools/CMakeFiles/stxxl_tool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/CMakeFiles/stxxl_tool.dir/depend
