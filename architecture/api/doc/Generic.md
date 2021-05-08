# Faust API

This API allows to interact with a Faust object and its associated audio engine at a high level. The idea is that all the audio part of the app is implemented in Faust allowing developers to focus on the design of the application itself. 

### Application Set-Up

Import `DspFaust.h` and `DspFaust.cpp` in your project (this can be done simply by dragging these files in your project tree). Then, import `DspFaust.h` (`#include "DspFaust.h"`) in the file where you want to create/control the Faust object. 

### Using the C++ API

The current Faust API is designed to seamlessly integrate to the life cycle of an app. It is accessible through a single `DspFaust` object. The constructor of that object is used to set the sampling rate and the buffer size:

	DspFaust* dspFaust = new DspFaust(SR, BS);

The `start()` method is used to start the audio computing. Similarly, `stop()` can be called to stop the audio computing.

It is possible to interact with the different parameters of the Faust object by using the `setParamValue` method. Two versions of this method exist: one where the parameter can be selected by its address and one where it can be selected using its ID. The [Parameters List](#parameters-list) section gives a list of the addresses and corresponding IDs of the current Faust object.

If your Faust object is polyphonic (e.g. if you used the `-nvoices` option when generating this API), then you can use the MIDI polyphony methods like `keyOn`, `keyOff`, etc.

It is possible to change the parameters of polyphonic voices independently using the `setVoiceParamValue` method. This method takes as one of its arguments the address to the voice returned by `keyOn` or `newVoice` when it is called. E.g:

	uintptr_t voiceAddress = dspFaust->keyOn(70, 100);
	dspFaust->setVoiceParamValue(1, voiceAddress, 214);
	dspFaust->keyOff(70);
	
In the example above, a new note is created and its parameter ID 1 is modified. This note is then terminated. Note that parameters addresses (path) are different for independent voices than when using `setParamValue`. The list of these addresses is provided in a separate sub-section of the [Parameters List](#parameters-list) section.

Finally, note that new voices don't necessarily have to be created using `keyOn`. Indeed, you might choose to just use the `newVoice` method for that:

	uintptr_t voiceAddress = dspFaust->newVoice();
	dspFaust->setVoiceParamValue(1, voiceAddress, 214);
	dspFaust->deleteVoice(voiceAddress);

This is particularly useful when making applications where each finger of the user is an independent sound that doesn't necessarily has a pitch.

In case you would like to use the built-in accelerometer or gyroscope of your device to control some of the parameters of your Faust object, all you have to do is to send the raw accelerometer data to it by using the `propagateAcc` or `propagateGyr` for the gyroscope. After that, mappings can be configured directly from the Faust code using [this technique](#using-built-in-sensors-to-control-parameters) or using the `setAccConverter` and `setGyrConverter` method.

