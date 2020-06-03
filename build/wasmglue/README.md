
# Faust as WebAssembly Library

This folder contains libraries that are linked to the Faust wasm library.
These libraries are picked up from the Csound project. 

In case of trouble at link time, it might likely come from a difference between emcc options (or version) used to build the current Faust wasm output and the libraries. A fresh new build of the csound libraries should solve the problem.

The current Csound libraries have been build using emcc version 1.39.16.

## Building the Csound libraries

First, get the Csound source from github: 
~~~~~~~~
$ git clone git@github.com:csound/csound.git
~~~~~~~~

Next go to the `Emscripten` folder (at the root of the csound folder) and follow the instructions in the README. At the end of the process, you'll find the libraries in `Emscripten/deps/lib`. Copy the required libraries to this folder.


**Note**  
If the csound/emscripten build process fails, the required libraries may still be available. Check the output folder.




