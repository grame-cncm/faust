/*
TODO header needed
*/
%module faust_dsp
%{
#include "faust_dsp.h"
%}

// Enable the JNI class to load the required native library.
%pragma(java) jniclasscode=%{
  static {
    try {
        java.lang.System.loadLibrary("faust_dsp");
    } catch (UnsatisfiedLinkError e) {
        java.lang.System.err.println("native code library failed to load.\n" + e);
        java.lang.System.exit(1);
    }
  }
%}

%include "carrays.i"
%array_functions(int, intArray);
%array_functions(float, floatArray);
%array_functions(char, charArray);

%include "faust_dsp.h"