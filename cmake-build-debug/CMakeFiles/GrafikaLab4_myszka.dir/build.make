# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Projects\CLion\GrafikaLab4_myszka

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Projects\CLion\GrafikaLab4_myszka\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\GrafikaLab4_myszka.dir\depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles\GrafikaLab4_myszka.dir\compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles\GrafikaLab4_myszka.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\GrafikaLab4_myszka.dir\flags.make

CMakeFiles\GrafikaLab4_myszka.dir\main.cpp.obj: CMakeFiles\GrafikaLab4_myszka.dir\flags.make
CMakeFiles\GrafikaLab4_myszka.dir\main.cpp.obj: ..\main.cpp
CMakeFiles\GrafikaLab4_myszka.dir\main.cpp.obj: CMakeFiles\GrafikaLab4_myszka.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\CLion\GrafikaLab4_myszka\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GrafikaLab4_myszka.dir/main.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\GrafikaLab4_myszka.dir\main.cpp.obj.d --working-dir=D:\Projects\CLion\GrafikaLab4_myszka\cmake-build-debug --filter-prefix="Uwaga: w tym pliku:  " -- C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1430~1.307\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\GrafikaLab4_myszka.dir\main.cpp.obj /FdCMakeFiles\GrafikaLab4_myszka.dir\ /FS -c D:\Projects\CLion\GrafikaLab4_myszka\main.cpp
<<

CMakeFiles\GrafikaLab4_myszka.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GrafikaLab4_myszka.dir/main.cpp.i"
	C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1430~1.307\bin\Hostx86\x86\cl.exe > CMakeFiles\GrafikaLab4_myszka.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\CLion\GrafikaLab4_myszka\main.cpp
<<

CMakeFiles\GrafikaLab4_myszka.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GrafikaLab4_myszka.dir/main.cpp.s"
	C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1430~1.307\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\GrafikaLab4_myszka.dir\main.cpp.s /c D:\Projects\CLion\GrafikaLab4_myszka\main.cpp
<<

# Object files for target GrafikaLab4_myszka
GrafikaLab4_myszka_OBJECTS = \
"CMakeFiles\GrafikaLab4_myszka.dir\main.cpp.obj"

# External object files for target GrafikaLab4_myszka
GrafikaLab4_myszka_EXTERNAL_OBJECTS =

GrafikaLab4_myszka.exe: CMakeFiles\GrafikaLab4_myszka.dir\main.cpp.obj
GrafikaLab4_myszka.exe: CMakeFiles\GrafikaLab4_myszka.dir\build.make
GrafikaLab4_myszka.exe: CMakeFiles\GrafikaLab4_myszka.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Projects\CLion\GrafikaLab4_myszka\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable GrafikaLab4_myszka.exe"
	"C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\GrafikaLab4_myszka.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests -- C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1430~1.307\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\GrafikaLab4_myszka.dir\objects1.rsp @<<
 /out:GrafikaLab4_myszka.exe /implib:GrafikaLab4_myszka.lib /pdb:D:\Projects\CLion\GrafikaLab4_myszka\cmake-build-debug\GrafikaLab4_myszka.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\GrafikaLab4_myszka.dir\build: GrafikaLab4_myszka.exe
.PHONY : CMakeFiles\GrafikaLab4_myszka.dir\build

CMakeFiles\GrafikaLab4_myszka.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\GrafikaLab4_myszka.dir\cmake_clean.cmake
.PHONY : CMakeFiles\GrafikaLab4_myszka.dir\clean

CMakeFiles\GrafikaLab4_myszka.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\Projects\CLion\GrafikaLab4_myszka D:\Projects\CLion\GrafikaLab4_myszka D:\Projects\CLion\GrafikaLab4_myszka\cmake-build-debug D:\Projects\CLion\GrafikaLab4_myszka\cmake-build-debug D:\Projects\CLion\GrafikaLab4_myszka\cmake-build-debug\CMakeFiles\GrafikaLab4_myszka.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\GrafikaLab4_myszka.dir\depend
