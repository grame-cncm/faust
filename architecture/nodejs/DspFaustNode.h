/************************************************************************
 ************************************************************************
 FAUST API Architecture File 
 Copyright (C) 2017 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2014-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------

 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.

 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

#ifndef __faust_nodejs__
#define __faust_nodejs__

#include <node.h>
#include <node_object_wrap.h>
#include "DspFaust.h"

class DspFaustNode : public node::ObjectWrap, public DspFaust {
public:
  static void Init(v8::Handle<v8::Object> exports);

private:
  explicit DspFaustNode();
  explicit DspFaustNode(int, int);
  ~DspFaustNode();
  static void destroy(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void start(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void stop(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void isRunning(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void keyOn(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void keyOff(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void newVoice(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void deleteVoice(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void allNotesOff(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void propagateMidi(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getJSONUI(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getJSONMeta(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getParamsCount(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void setParamValue(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getParamValue(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void setVoiceParamValue(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getVoiceParamValue(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getParamAddress(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getVoiceParamAddress(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getParamMin(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getParamMax(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getParamInit(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getMetadata(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void propagateAcc(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void setAccConverter(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void propagateGyr(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void setGyrConverter(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getCPULoad(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void configureOSC(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Persistent<v8::Function> constructor;
};

#endif