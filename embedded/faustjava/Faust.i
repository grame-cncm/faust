/* File : Faust.i */
%module Faust

%{
#include "faust/dsp/llvm-dsp-c.h"
#include "faust/dsp/libfaust-c.h"
#include "libfaust_ext.h"
%}

/* Let's just grab the original header file here */
%include "faust/dsp/libfaust-c.h"
%include "faust/dsp/llvm-dsp-c.h"
%include "libfaust_ext.h"
