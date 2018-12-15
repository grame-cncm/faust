# faust2unity

`faust2unity` transforms a Faust DSP program into a fully working Unity audio plugin, which can be an effect or a synthesiser to perform procedural audio.

The compiled folder is a Unity package (i.e. FaustPlugin_<dspname>.unitypackage) which contains two different types of files :

    - Libraries (in `libFaustPlugin_<dspname>.bundle`) containing the native C++ part.
    - Two C# scripts (`FaustPlugin_<dspname>.cs` and `FaustUtilities_<dspname>.cs`) containing the methods and classes which link the native part to the Unity audio system, and manage the plugin inspector interface.

Libraries are available for several platforms and architectures:

    - Windows 32 bits and 64 bits (.dll)
    - macOS (.bundle)
    - iOS (.a)
    - Android armeabi-v7a and x86 (.so)
    - Linux (.so).

## How to use

`faust2unity` is used with the following command:

`faust2unity [-w32] [-w64] [-osx] [-ios] [-android] [-linux] [-nvoices <num>] [-source] [-unpacked] <file1.dsp> [<file2.dsp>]`

By default it will create a Unity package containing the C# script and sub-folders with all available architectures. Relevant achitectures can be chosen by including their corresponding options as listed above. Several DSP files can be compiled at the same time and will be generated in different packages.

The relevant architecture setup should be filled in for each file in the plugin inspector.

Finally, the C# script `FaustPlugin_<dspname>` should be attached to a game object. `FaustPlugin_<dspname>.cs` is the public interface and contains the dsp class and methods that allow to access and change the parameters (i.e. `getParameter()` and `setParameter()`). `FaustUtilities_<dspname>` contains additional code to access the plugin and generate the inspector interface. This file shouldn't be changed.

The source files can be produced with the `-source` option.

The `-nvoices <num>` option can be used to produce a polyphonic self-contained DSP with `num` voices, ready to be used with MIDI. The C# script will contain keyOn/KeyOff functions to control the instrument.

Unity packages have a specific organization in order to be correctly read by the Unity editor. `faust2unity` calls `encoderunitypackage` to correctly encode the compiled files. The `-unpacked` option stops the script before the encoding step, the intermediate folder is named `FaustPlugin_<dspname>_Assets` and organized like the Assets hierarchy of a Unity project. It allows to add additional files to the package before packing it. Then, use the `encoderunitypackage <folder>` command to encode and pack the folder as a Unity package.

## Compiler requirements

### Windows 32 bits and 64 bits

The compiler used for Windows libraries is Mingw (http://www.mingw.org). `i686-w64-mingw32-gcc` (32bits) and `x86_64-w64-mingw32-gcc` (64bits) packages have to be installed. On macOS, they are available on [Macports](https://www.macports.org).

### Android

Android SDK (containing Android NDK) should be installed to generate Android libraries and the ANDROID_HOME environment variable should be defined. It should point on the sdk folder. If the SDK has been installed by Android Studio, the path should be `~/Library/Android/sdk`. Other architectures are available in the Android NDK. To use them, the `achitecture/unity/Android/Android.mk` file should be updated and the APP_ABI line should be modified. See [Android NDK](https://developer.android.com/ndk/guides/android_mk.html) for more info.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             

## Options

The following options are available :

  - `-w32`          : produces a Windows 32bits library
  - `-w64`          : produces a Windows 64bits library
  - `-osx`          : produces a macOS library
  - `-ios`          : produces an iOS library
  - `-android`      : produces Android armeabi-v7a and x86 libraries
  - `-linux`        : produces a Linux library
  - `-nvoices <num>`: produces a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI
  - `-source`       : produces an uncompressed folder with the selected architecture and the source files used to compile the libraries
  - `-unpacked`     : produces a folder with all selected architectures ordered like the Unity Assets hierarchy (i.e. `Assets/Plugins/FaustPlugin_<dspname>/iOS/libFaustPlugin_<dspname>.a`).
  - `-help or -h`   : shows different options and comments

`faust2unity` script calls six different commands :

  - `faust2w32unity <file.dsp>`
  - `faust2w64unity <file.dsp>`
  - `faust2osxiosunity [-ios] <file.dsp>`
  - `faust2androidunity <file.dsp>`
  - `faust2linuxunity <file.dsp>`
  - `encoderunitypackage <folder>`

These commands can be called independently and will generate the libraries only (without the C# files). Specific compilation options can be changed in `faust2<platform>unity` scripts.
