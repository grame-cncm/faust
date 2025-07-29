
# Compiling on Windows using MSYS2

### Prerequisites
The [MSYS2](http://www.msys2.org/) environment.

## A little note on MSYS2 for beginners.


After installing MSYS2, in the Start menu MSYS2 folder you will see links to the following 3 pre-configured environments:
- A) MSYS2 MSYS
- B) MSYS2 MinGW 32-bit
- C) MSYS2 MinGW 64-bit

To make native Windows binaries that don't rely on POSIX emulative sublayers, you should use (B) or (C) of the above environments.

Let's suppose we are on a 64-bit Windows system... Then you should launch "MSYS2 MinGW 64-bit". If you use the MSYS environments (A), you will easily incur in many problems during the compiling process.

## Building from MSYS2 MinGW 64-bit

To build Faust from the "MSYS2 MinGW 64-bit" environment, install the following packages:
- mingw-w64-x86_64-gcc
- mingw-w64-x86_64-llvm
- mingw-w64-x86_64-libmicrohttpd
- mingw-w64-x86_64-make
- mingw-w64-x86_64-cmake
- git

The MSYS package utility is `pacman`. To install a package named _yourPackage_, you must execute the command `pacman -S yourPackage`

**Note**: apart from 'git', make sure you use the "mingw-w64-x86_64-..." version of the above packages, because the development tools and libraries installed from packages without the mingw-w64-x86_64 prefix are intended to work correctly only in the MSYS environment, not in the MinGW32/64 one.

Then:
~~~
$ git clone https://github.com/grame-cncm/faust.git
$ cd faust
$ git submodule update --init
 ~~~

To make the default building of Faust (faust.exe + OSC and HTTPD static libs with following backends included: ASMJS, C, CPP, JAVA, JS, OLDCPP, WASM):
~~~
$ make
~~~

or, to build Faust for all the targets (executable, static and dynamic libraries of the compiler, OSC and HTTPD with all the backends included: ASMJS, C, CPP, FIR, JAVA, JS, LLVM, OLDCPP, RUST, WASM):
~~~
$ cd build
$ make cmake BACKENDS=world.cmake TARGETS=world.cmake
$ make
~~~
------
