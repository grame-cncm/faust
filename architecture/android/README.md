# Android Faust Architecture

This template Android project is used by `faust2android` to generate Android applications from a Faust code.

## Usage

```
faust2android faustFile.dsp
```

### Options

* `-install`: once compilation is over, installs the generated app on the Android device connected to the computer
* `-source`: creates an eclipse project of the app in the current directory.
* `-swig`: regenerate the C++ and the JAVA interface for the native portion of the app.
*` -faust`: only carries out the Faust compilation and install the generated C++ file in the JNI folder.
* `-reuse`: keep build directory and reuse it to speedup compilation.
* `-debug`: verbose output.

Any other options are considered as Faust options. To get a list of the Faust options type: `faust -h`
