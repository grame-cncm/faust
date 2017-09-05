# `faust2api`: Android Support

The JNI interface of the Faust support for Android can be regenerated at any point simply by running the following command from `/architecture/api/android`:

```
swig -java -package com.DspFaust -includeall -verbose -outdir jni -c++ -I/System/Library/Frameworks/JavaVM.framework/Headers -Ijni -I../ -o jni/java_interface_wrap.cpp jni/dsp_faust_interface.i
```

This command should work both on Linux and OSX. This might be useful in case new methods are added to `/architecture/api/android/DspFaust.h`.
