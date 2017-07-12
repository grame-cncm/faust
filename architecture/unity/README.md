# Faust2unity

`faust2unity` transforms a Faust DSP program into a fully working Unity audio plugin, which can be an effect or a synthesiser to perform procedural audio. 

The compiled folder contains two different types of files :

    - Librairies (i.e. `libFaustPlugin_<file>.bundle`) containing the native C++ part.
    - a C# script (i.e. `FaustPlugin_<file>.cs`) containing the managed part which links the native part to the unity audio system and managed the plugin inspector interface.

Libraries are available for several platforms and architectures : 
    - Windows 32 bits and 64 bits (.dll)
    - MacOS (.bundle)
    - iOS (.a)
    - Android armeabi-v7a and x86 (.so)
    - Linux (.so).


## How to use

`faust2unity` is used with the following command :

`faust2unity [-w32] [-w64] [-osx] [-ios] [-android] [-linux] <file1.dsp> [<file2.dsp>]`

By default it will create a folder containing the c# script and sub-folders with all avalaible architecture. Relevant achitectures can be chosen by adding the right arguments. Several DSP files can be compiled at the same time and will be generated in different folders.

The library files should be in the Assets/Plugins folder in your Unity project. Then, the relevant architecture set up should be filled in for each file in the plugin inspector.

Finally, attache the c# script to a game object. 


## Compiler requirements

### Windows 32 bits and 64 bits

The compiler used for Windows libraries is Mingw (http://www.mingw.org). `i686-w64-mingw32-gcc` (32bits) and `x86_64-w64-mingw32-gcc` (64bits) packages have to be installed. They are available on [Macports](https://www.macports.org).

### Android

Android SDK (containing Android NDK) should be installed to generate Android libraries and the ANDROID_HOME environment variable should be defined. It should point on the sdk folder. If the SDK has been installed by Android Studio, the path should be `~/Library/Android/sdk`. Other architectures are available in the Android NDK. To use them, the `achitecture/unity/Android/Android.mk` file should be updated and the APP_ABI line should be modified. See [Android NDK](https://developer.android.com/ndk/guides/android_mk.html) for more info.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
## Options

The following options are available :
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
    - `-w32`        : produces a Windows 32bits library
    - `-w64`        : produces a Windows 64bits library
    - `-osx`        : produces a MacOS library
    - `-ios`        : produces an iOS library
    - `-android`    : produces Android armeabi-v7a and x86 libraries
    - `-linux`      : produces a Linux library
    - `-help or -h` : shows different options and comments

`faust2unity` script calls five different commands :

    - `faust2w32unity <file.dsp>` 
    - `faust2w64unity <file.dsp>`
    - `faust2osxiosunity [-ios] <file.dsp>`
    - `faust2androidunity <file.dsp>`
    - `faust2linuxunity <file.dsp>`

This commands can be called independently and will generate the libraries only (without the c# file). Specific compilation options can be changed in `faust2<platform>unity` scripts.


