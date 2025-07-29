
# Compiling on Windows using MSVC

### Prerequisites
The Microsoft Visual Studio environment.

## CMake commands to setup your project.

This section assumes that you're directly using `cmake` commands instead of `make` commands.

Start opening a command prompt or Windows PowerShell, then go to the faust/build folder, create a `msvc` folder and change dir to this folder.
~~~
$ cd your/faust/folder/build
$ mkdir msvc
$ cd msvc
 ~~~

**Note**: use a separate folder for your build is recommended. The example above creates a folder named `msvc` but you could use any name and create as many folders as you want. By doing so, your project setup and state will always remain local to your folder.

Then create your project invoking cmake as follows:

~~~
$ cmake -C ../backends/abackendfile.cmake -C ../targets/atargetfile.cmake .. -G "a visual studio generator"
 ~~~

The first options (-C file) are intended to populate the cmake cache with settings that select the backends to be compiled and the targets to be included in the output project. The third option (..) tells cmake where to find the project description (actually CMakeFiles.txt). And the last option selects a cmake generator (see `cmake -help` for the possible generators).

For example, the following will create a project using _regular_ backends and targets (have a look at the corresponding files) for Visual Studio 14 and for a 64 bits architecture.

~~~
$ cmake -C ../backends/regular.cmake -C ../targets/regular.cmake .. -G "Visual Studio 14 2015 Win64"
 ~~~

**Note**: once the cmake cache is populated and the generator selected, you don't need to give these options again, unless you want to change them. Thus calling `cmake ..` after that is enough to regenerate the project.

**Note**: changing the generator (e.g. another Visual Studio version or another architecture) implies to remove the cmake cache and thus to restart from the beginning.


## Building the faust project

Open the `faust.sln` visual studio solution and proceed as usual.

You can also compile from the command line:
~~~
$ cmake --build . --config Release (or debug)
 ~~~
Type `cmake -help build_command` for details about the --build command.


## CMake options

### Static runtime libraries
With MSVC, you can choose which C runtime library (CRT) to use: the dynamic library (default) using the compile flag /MD for release or /MDd for debug or the static library using the compile flag /MT for release or /MTd for debug.
By default the generated project uses the dynamic libray. To change, use the following option:
~~~
$ cmake -DMSVC_STATIC=on ..
 ~~~

 ### LLVM config strategy
 By default, cmake try to get the LLVM options from `llvm-config.exe` (only if the LLVM backend is included). The output of `llvm-config` is generally not suitable for Visual Studio projects (ill formatted).  Another strategy is available and works better that consists a `LLVMConfig.cmake` file.
To do so, use the following option:
 ~~~
 $ cmake -DUSE_LLVM_CONFIG=off ..
  ~~~
It is recommended to use this option in a first place.
