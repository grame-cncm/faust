#!/bin/sh

export ANDROID_NDK_ROOT=/home/romain/Android/android-ndk-r8d

rm -rf src/faust_dsp
mkdir -p src/faust_dsp

swig -java -package faust_dsp -includeall -verbose -outdir src/faust_dsp -c++ -I/usr/share/swig2.0 -I/usr/local/include -I/System/Library/Frameworks/JavaVM.framework/Headers -I./jni -o jni/java_interface_wrap.cpp faust_dsp_interface.i

$ANDROID_NDK_ROOT/ndk-build TARGET_PLATFORM=android-14 V=1
