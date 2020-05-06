# Faust Android API

This API allows to interact with a natively compiled Faust object and its associated audio engine at a very high level from the JAVA layer of an Android app. The idea is that all the audio part of the app is implemented in Faust allowing developers to focus on the design of the app itself. 

For more details on how to create Android apps from scratch using this tool, check the [`faust2api` documentation](https://ccrma.stanford.edu/~rmichon/faust2api) or the [*Adding Faust Real-Time Audio Support to Android Apps Tutorial*](https://ccrma.stanford.edu/~rmichon/faustTutorials/#adding-faust-real-time-audio-support-to-android-apps).

## Using This Package

This section is an accelerated version of the [*Adding Faust Real-Time Audio Support to Android Apps Tutorial*](https://ccrma.stanford.edu/~rmichon/faustTutorials/#adding-faust-real-time-audio-support-to-android-apps). We strongly recommend you to read it if this is the first time that you use this tool or if you never used the Android NDK (Native Development Kit).

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
add_library( 
	dsp_faust 
	SHARED 
	src/main/cpp/java_interface_wrap.cpp 
	src/main/cpp/DspFaust.cpp 
)
find_library( log-lib log )
target_link_libraries( dsp_faust ${log-lib} )
```

Finally, since your Faust object might need to access the audio input of your device, the following line should be added to the manifest of your app (typically before the `application` tag):

	<uses-permission android:name="android.permission.RECORD_AUDIO"/>

After this, re-synchronize Gradle and try to compile the Android app. Hopefully, things should go well!

### Using the JAVA API

The Faust JAVA API is designed to seamlessly integrate to the life cycle of an Android app. It is accessible through a single `DspFaust` object. The constructor of that object is used to set the sampling rate and the block size:

	DspFaust dspFaust = new DspFaust(SR, blockSize);

The `start()` method is used to start the audio computing and would typically be placed in the `onCreate()` method of the app activity.

Similarly, `stop()` can be called to stop the audio computing and can be placed in `onDetroy()`, etc.

Garbage collection on the native side is taken care of so you don't have to worry about it.

It is possible to interact with the different parameters of the Faust object by using the `setParamValue` method. Two versions of this method exist: one where the parameter can be selected by its address and one where it can be selected using its ID. The [Parameters List](#parameters-list) section gives a list of the addresses and corresponding IDs of the current Faust object.

If your Faust object is polyphonic (e.g. if you used the `-nvoices` option when generating this API), then you can use the MIDI polyphony methods like `keyOn`, `keyOff`, etc.

It is possible to change the parameters of polyphonic voices independently using the `setVoiceParamValue` method. This method takes as one of its arguments the address to the voice returned by `keyOn` or `newVoice` when it is called. E.g:

	long voiceAddress = dspFaust.keyOn(70, 100);
	dspFaust.setVoiceParamValue(1, voiceAddress, 214);
	dspFaust.keyOff(70);
	
In the example above, a new note is created and its parameter ID 1 is modified. This note is then terminated. Note that parameters addresses (path) are different for independent voices than when using `setParamValue`. The list of these addresses is provided in a separate sub-section of the [Parameters List](#parameters-list) section.

Finally, note that new voices don't necessarily have to be created using `keyOn`. Indeed, you might choose to just use the `newVoice` method for that:

	long voiceAddress = dspFaust.newVoice;
	dspFaust.setVoiceParamValue(1, voiceAddress, 214);
	dspFaust.deleteVoice(voiceAddress);

This is particularly useful when making apps where each finger of the user is an independent sound that doesn't necessarily has a pitch.

In case you would like to use the the built-in accelerometer or gyroscope of your device to control some of the parameters of your Faust object, all you have to do is to send the raw accelerometer data to it by using the `propagateAcc` or `propagateGyr` for the gyroscope. After that, mappings can be configured directly from the Faust code using [this technique](#using-built-in-sensors-to-control-parameters) or using the `setAccConverter` and `setGyrConverter` method.

