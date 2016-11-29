# Faust Android API

This API allows to interact with a natively compiled Faust object and its associated audio engine at a very high level from the JAVA layer of an Android app. The idea is that all the audio part of the app is implemented in Faust allowing developers to focus on the design of the app itself. 

For tutorials (and more details) on how to create Android apps from scratch using this tool, check [this page](https://ccrma.stanford.edu/~rmichon/faust2api/).

## Using This Package

This section is an accelerated version of the tutorial available at [this page](https://ccrma.stanford.edu/~rmichon/faust2api/). We strongly recommend you to read it if this is the first time that you use this tool or if you never used the Android NDK (Native Development Kit).

### App Set-Up

Very little work has to be done to integrate this package to your Android app. Once this is done, you will be able to interact with the Faust DSP module from JAVA without having to write a line of native C++ code.

This package contains 2 folder: `/cpp` and `/java`. `cpp` hosts the native C++ elements that should be placed in the NDK folder of your app. `/java` contains the JAVA classes that should be placed in the `java` folder of your app in accordance with the JAVA package that was configured when `faust2api` was ran. The default package name is `com.DspFaust`, thus, in that case, the content of `/java` should be placed in `java/com/DspFaust`. You can check the [faust2api documentation](https://ccrma.stanford.edu/~rmichon/faust2api/) to get more information about that. 

In order for things to compile, your Gradle file should have an `externalNativeBuild` with something like that in it:

```
externalNativeBuild {
	cmake {
		cppFlags "-O3 -fexceptions -frtti -lOpenSLES"
	}
}
```

Also, the NDK CMake file should look like this:

```
cmake_minimum_required(VERSION 3.4.1)
add_library( dsp_faust SHARED src/main/cpp/java_interface_wrap.cpp src/main/cpp/DspFaust.cpp )
find_library( log-lib log )
target_link_libraries( dsp_faust ${log-lib} )
```

Finally, since your Faust object might need to access the audio input of your device, the following line should be added to the manifest of your app (typically before the `application` tag):

```
<uses-permission android:name="android.permission.RECORD_AUDIO"/>
```

After this, re-synchronize Gradle and try to compile the Android app. Hopefully, things should go well!

### Using the JAVA API

The Faust JAVA API is designed to easily integrate to the life cycle of an Android app. It is accessible through a single `DspFaust` object. The constructor of that object is used to set the sampling rate and the block size:

```
DspFaust dspFaust = new DspFaust(SR,blockSize);
```

The `start()` method is used to start the audio computing and would typically be placed in the `onCreate()` method the app activity.

Similarly, `stop()` can be called to stop the audio computing and can be called in `onDetroy()`, etc.

Garbage collection on the native side is taken care of so you don't have to worry about it.

It is possible to interact with the different parameters of the Faust object by using the `setParamValue` method. Two versions of this method exist: one where the parameter can be selected by its address and one where it can be selected using its ID. The [Parameters List](#parameters-list) section gives a list of the addresses and corresponding IDs of the current Faust object.

If your Faust object is polyphonic (e.g. if you used the `-polyvoices` option when generating this API), then you can use the MIDI polyphony methods like `keyOn`, `keyOff`, etc.

