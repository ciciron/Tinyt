# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/mdn/projects/tinyt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mdn/projects/tinyt

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target test
test:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running tests..."
	/usr/bin/ctest --force-new-ctest-process $(ARGS)
.PHONY : test

# Special rule for the target test
test/fast: test

.PHONY : test/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/mdn/projects/tinyt/CMakeFiles /home/mdn/projects/tinyt/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/mdn/projects/tinyt/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named tinyts

# Build rule for target.
tinyts: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tinyts
.PHONY : tinyts

# fast build rule for target.
tinyts/fast:
	$(MAKE) -f CMakeFiles/tinyts.dir/build.make CMakeFiles/tinyts.dir/build
.PHONY : tinyts/fast

#=============================================================================
# Target rules for targets named tinysrv

# Build rule for target.
tinysrv: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tinysrv
.PHONY : tinysrv

# fast build rule for target.
tinysrv/fast:
	$(MAKE) -f CMakeFiles/tinysrv.dir/build.make CMakeFiles/tinysrv.dir/build
.PHONY : tinysrv/fast

#=============================================================================
# Target rules for targets named uninstall

# Build rule for target.
uninstall: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 uninstall
.PHONY : uninstall

# fast build rule for target.
uninstall/fast:
	$(MAKE) -f CMakeFiles/uninstall.dir/build.make CMakeFiles/uninstall.dir/build
.PHONY : uninstall/fast

#=============================================================================
# Target rules for targets named clang-tidy-check

# Build rule for target.
clang-tidy-check: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 clang-tidy-check
.PHONY : clang-tidy-check

# fast build rule for target.
clang-tidy-check/fast:
	$(MAKE) -f CMakeFiles/clang-tidy-check.dir/build.make CMakeFiles/clang-tidy-check.dir/build
.PHONY : clang-tidy-check/fast

#=============================================================================
# Target rules for targets named srvc_t

# Build rule for target.
srvc_t: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 srvc_t
.PHONY : srvc_t

# fast build rule for target.
srvc_t/fast:
	$(MAKE) -f test/CMakeFiles/srvc_t.dir/build.make test/CMakeFiles/srvc_t.dir/build
.PHONY : srvc_t/fast

#=============================================================================
# Target rules for targets named realm_t

# Build rule for target.
realm_t: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 realm_t
.PHONY : realm_t

# fast build rule for target.
realm_t/fast:
	$(MAKE) -f test/CMakeFiles/realm_t.dir/build.make test/CMakeFiles/realm_t.dir/build
.PHONY : realm_t/fast

src/Abuser.o: src/Abuser.cpp.o

.PHONY : src/Abuser.o

# target to build an object file
src/Abuser.cpp.o:
	$(MAKE) -f CMakeFiles/tinyts.dir/build.make CMakeFiles/tinyts.dir/src/Abuser.cpp.o
.PHONY : src/Abuser.cpp.o

src/Abuser.i: src/Abuser.cpp.i

.PHONY : src/Abuser.i

# target to preprocess a source file
src/Abuser.cpp.i:
	$(MAKE) -f CMakeFiles/tinyts.dir/build.make CMakeFiles/tinyts.dir/src/Abuser.cpp.i
.PHONY : src/Abuser.cpp.i

src/Abuser.s: src/Abuser.cpp.s

.PHONY : src/Abuser.s

# target to generate assembly for a file
src/Abuser.cpp.s:
	$(MAKE) -f CMakeFiles/tinyts.dir/build.make CMakeFiles/tinyts.dir/src/Abuser.cpp.s
.PHONY : src/Abuser.cpp.s

src/Commands.o: src/Commands.cpp.o

.PHONY : src/Commands.o

# target to build an object file
src/Commands.cpp.o:
	$(MAKE) -f CMakeFiles/tinysrv.dir/build.make CMakeFiles/tinysrv.dir/src/Commands.cpp.o
.PHONY : src/Commands.cpp.o

src/Commands.i: src/Commands.cpp.i

.PHONY : src/Commands.i

# target to preprocess a source file
src/Commands.cpp.i:
	$(MAKE) -f CMakeFiles/tinysrv.dir/build.make CMakeFiles/tinysrv.dir/src/Commands.cpp.i
.PHONY : src/Commands.cpp.i

src/Commands.s: src/Commands.cpp.s

.PHONY : src/Commands.s

# target to generate assembly for a file
src/Commands.cpp.s:
	$(MAKE) -f CMakeFiles/tinysrv.dir/build.make CMakeFiles/tinysrv.dir/src/Commands.cpp.s
.PHONY : src/Commands.cpp.s

src/Main.o: src/Main.cpp.o

.PHONY : src/Main.o

# target to build an object file
src/Main.cpp.o:
	$(MAKE) -f CMakeFiles/tinyts.dir/build.make CMakeFiles/tinyts.dir/src/Main.cpp.o
.PHONY : src/Main.cpp.o

src/Main.i: src/Main.cpp.i

.PHONY : src/Main.i

# target to preprocess a source file
src/Main.cpp.i:
	$(MAKE) -f CMakeFiles/tinyts.dir/build.make CMakeFiles/tinyts.dir/src/Main.cpp.i
.PHONY : src/Main.cpp.i

src/Main.s: src/Main.cpp.s

.PHONY : src/Main.s

# target to generate assembly for a file
src/Main.cpp.s:
	$(MAKE) -f CMakeFiles/tinyts.dir/build.make CMakeFiles/tinyts.dir/src/Main.cpp.s
.PHONY : src/Main.cpp.s

src/Realm.o: src/Realm.cpp.o

.PHONY : src/Realm.o

# target to build an object file
src/Realm.cpp.o:
	$(MAKE) -f CMakeFiles/tinysrv.dir/build.make CMakeFiles/tinysrv.dir/src/Realm.cpp.o
.PHONY : src/Realm.cpp.o

src/Realm.i: src/Realm.cpp.i

.PHONY : src/Realm.i

# target to preprocess a source file
src/Realm.cpp.i:
	$(MAKE) -f CMakeFiles/tinysrv.dir/build.make CMakeFiles/tinysrv.dir/src/Realm.cpp.i
.PHONY : src/Realm.cpp.i

src/Realm.s: src/Realm.cpp.s

.PHONY : src/Realm.s

# target to generate assembly for a file
src/Realm.cpp.s:
	$(MAKE) -f CMakeFiles/tinysrv.dir/build.make CMakeFiles/tinysrv.dir/src/Realm.cpp.s
.PHONY : src/Realm.cpp.s

src/ServerImpl.o: src/ServerImpl.cpp.o

.PHONY : src/ServerImpl.o

# target to build an object file
src/ServerImpl.cpp.o:
	$(MAKE) -f CMakeFiles/tinysrv.dir/build.make CMakeFiles/tinysrv.dir/src/ServerImpl.cpp.o
.PHONY : src/ServerImpl.cpp.o

src/ServerImpl.i: src/ServerImpl.cpp.i

.PHONY : src/ServerImpl.i

# target to preprocess a source file
src/ServerImpl.cpp.i:
	$(MAKE) -f CMakeFiles/tinysrv.dir/build.make CMakeFiles/tinysrv.dir/src/ServerImpl.cpp.i
.PHONY : src/ServerImpl.cpp.i

src/ServerImpl.s: src/ServerImpl.cpp.s

.PHONY : src/ServerImpl.s

# target to generate assembly for a file
src/ServerImpl.cpp.s:
	$(MAKE) -f CMakeFiles/tinysrv.dir/build.make CMakeFiles/tinysrv.dir/src/ServerImpl.cpp.s
.PHONY : src/ServerImpl.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... install/strip"
	@echo "... install"
	@echo "... rebuild_cache"
	@echo "... tinyts"
	@echo "... edit_cache"
	@echo "... list_install_components"
	@echo "... tinysrv"
	@echo "... uninstall"
	@echo "... clang-tidy-check"
	@echo "... install/local"
	@echo "... test"
	@echo "... srvc_t"
	@echo "... realm_t"
	@echo "... src/Abuser.o"
	@echo "... src/Abuser.i"
	@echo "... src/Abuser.s"
	@echo "... src/Commands.o"
	@echo "... src/Commands.i"
	@echo "... src/Commands.s"
	@echo "... src/Main.o"
	@echo "... src/Main.i"
	@echo "... src/Main.s"
	@echo "... src/Realm.o"
	@echo "... src/Realm.i"
	@echo "... src/Realm.s"
	@echo "... src/ServerImpl.o"
	@echo "... src/ServerImpl.i"
	@echo "... src/ServerImpl.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

