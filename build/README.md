
# Compiling Faust


The Faust distribution uses [CMake](https://cmake.org/) for the build system.
This folder contains configuration files for setting up the different compilation targets with CMake.

By default, you can simply run the commands

~~~
make
sudo make install
~~~

in the root folder of the repository to compile and install the **Faust** compiler and the **OSC and HTTP** libraries. Note that the `libfaust` LLVM backend is not compiled by default. A full tutorial for easily compiling Faust is available on the [wiki](https://github.com/grame-cncm/faust/wiki/BuildingSimple).

For more details on the compilation targets and options (such as the LLVM backend), run `make help` in the root folder or see the [advanced compiling](https://github.com/grame-cncm/faust/wiki/Building) wiki page.
