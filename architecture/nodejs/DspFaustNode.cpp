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

#include <string>
#include "DspFaustNode.h"

using namespace v8;

Persistent<Function> DspFaustNode::constructor;

bool isInteger(const std::string & s) {
  if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
  char * p ;
  strtol(s.c_str(), &p, 10) ;
  return (*p == 0) ;
}

DspFaustNode::DspFaustNode() : DspFaust() {}

DspFaustNode::DspFaustNode(int sample_rate, int buffer_size) : 
  DspFaust(sample_rate, buffer_size) {}

DspFaustNode::~DspFaustNode() {}

void DspFaustNode::Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "DspFaustNode"));
  tpl->InstanceTemplate()->SetInternalFieldCount(2);

  // Prototypes
  NODE_SET_PROTOTYPE_METHOD(tpl, "destroy", destroy);
  NODE_SET_PROTOTYPE_METHOD(tpl, "start", start);
  NODE_SET_PROTOTYPE_METHOD(tpl, "stop", stop);
  NODE_SET_PROTOTYPE_METHOD(tpl, "isRunning", isRunning);
  NODE_SET_PROTOTYPE_METHOD(tpl, "keyOn", keyOn);
  NODE_SET_PROTOTYPE_METHOD(tpl, "keyOff", keyOff);
  NODE_SET_PROTOTYPE_METHOD(tpl, "newVoice", newVoice);
  NODE_SET_PROTOTYPE_METHOD(tpl, "deleteVoice", deleteVoice);
  NODE_SET_PROTOTYPE_METHOD(tpl, "allNotesOff", allNotesOff);
  NODE_SET_PROTOTYPE_METHOD(tpl, "propagateMidi", propagateMidi);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getJSONUI", getJSONUI);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getJSONMeta", getJSONMeta);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getParamsCount", getParamsCount);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setParamValue", setParamValue);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getParamValue", getParamValue);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setVoiceParamValue", setVoiceParamValue);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getVoiceParamValue", getVoiceParamValue);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getParamAddress", getParamAddress);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getVoiceParamAddress", getVoiceParamAddress);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getParamMin", getParamMin);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getParamMax", getParamMax);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getParamInit", getParamInit);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getMetadata", getMetadata);
  NODE_SET_PROTOTYPE_METHOD(tpl, "propagateAcc", propagateAcc);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAccConverter", setAccConverter);
  NODE_SET_PROTOTYPE_METHOD(tpl, "propagateGyr", propagateGyr);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setGyrConverter", setGyrConverter);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getCPULoad", getCPULoad);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "DspFaustNode"),
               tpl->GetFunction());
}

void DspFaustNode::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  DspFaustNode* dspFaustNode;
  if(args[0]->IsUndefined()){ // if arg 0 is undefined then should be same for arg1
    dspFaustNode = new DspFaustNode();
  }
  else{
    dspFaustNode = new DspFaustNode((int)args[0]->NumberValue(), 
      (int)args[1]->NumberValue());
  }
  dspFaustNode->Wrap(args.This());
  args.GetReturnValue().Set(args.This());
}

void DspFaustNode::destroy(const v8::FunctionCallbackInfo<v8::Value>& args) {
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  fNode->persistent().Reset();
  delete fNode;
}

void DspFaustNode::start(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  args.GetReturnValue().Set(Boolean::New(isolate, fNode->DspFaust::start()));
}

void DspFaustNode::stop(const v8::FunctionCallbackInfo<v8::Value>& args) {
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  fNode->DspFaust::stop();
}

void DspFaustNode::isRunning(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  args.GetReturnValue().Set(Boolean::New(isolate, fNode->DspFaust::isRunning()));
}

void DspFaustNode::keyOn(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && !args[1]->IsUndefined()) {
    int pitch = (int) args[0]->NumberValue();
    int velocity = (int) args[1]->NumberValue();
    args.GetReturnValue().Set(
      Number::New(isolate, fNode->DspFaust::keyOn(pitch,velocity)));
  }
  else {
    printf("Missing argument\n");
  }
}

void DspFaustNode::keyOff(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    int pitch = (int) args[0]->NumberValue();
    args.GetReturnValue().Set(
      Integer::New(isolate, fNode->DspFaust::keyOff(pitch)));
  }
  else {
    printf("Missing argument\n");
  }
}

void DspFaustNode::newVoice(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  args.GetReturnValue().Set(Number::New(isolate,fNode->DspFaust::newVoice()));
}

void DspFaustNode::deleteVoice(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    unsigned long voice = (unsigned long) args[0]->NumberValue();
    args.GetReturnValue().Set(
      Integer::New(isolate, fNode->DspFaust::deleteVoice(voice)));
  }
  else {
    printf("Missing argument\n");
  }
}

void DspFaustNode::allNotesOff(const v8::FunctionCallbackInfo<v8::Value>& args) {
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  fNode->DspFaust::allNotesOff();
}

void DspFaustNode::propagateMidi(const v8::FunctionCallbackInfo<v8::Value>& args) {
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && 
      !args[1]->IsUndefined() &&
      !args[2]->IsUndefined() &&
      !args[3]->IsUndefined() &&
      !args[4]->IsUndefined() &&
      !args[5]->IsUndefined()) {
    int count = (int) args[0]->NumberValue();
    double time = (int) args[1]->NumberValue();
    int type = (int) args[2]->NumberValue();
    int channel = (int) args[3]->NumberValue();
    int data1 = (int) args[4]->NumberValue();
    int data2 = (int) args[5]->NumberValue();
    fNode->DspFaust::propagateMidi(count,time,type,channel,data1,data2);
  }
  else {
    printf("Missing argument\n");
  }
}

void DspFaustNode::getJSONUI(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  args.GetReturnValue().Set(String::NewFromUtf8(isolate,fNode->DspFaust::getJSONUI()));
}

void DspFaustNode::getJSONMeta(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  args.GetReturnValue().Set(String::NewFromUtf8(isolate,fNode->DspFaust::getJSONMeta()));
}

void DspFaustNode::getParamsCount(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  args.GetReturnValue().Set(Integer::New(isolate,fNode->DspFaust::getParamsCount()));
}

void DspFaustNode::setParamValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && !args[1]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    float paramValue = (float) args[1]->NumberValue();
    if(isInteger(paramAddress)) {
      fNode->DspFaust::setParamValue(std::stoi(paramAddress),paramValue);
    }
    else {
      fNode->DspFaust::setParamValue(paramAddress.c_str(),paramValue);
    }
  }
  else {
    printf("Missing argument\n");
  }
}

void DspFaustNode::getParamValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    if(isInteger(paramAddress)) {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->DspFaust::getParamValue(std::stoi(paramAddress))));
    }
    else {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->DspFaust::getParamValue(paramAddress.c_str())));
    }
  }
  else {
    printf("Missing argument\n");
  }
}

void DspFaustNode::setVoiceParamValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && !args[1]->IsUndefined() && !args[2]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    unsigned long voice = (unsigned long) args[1]->NumberValue();
    float paramValue = (float) args[2]->NumberValue();
    if(isInteger(paramAddress)) {
      fNode->DspFaust::setVoiceParamValue(std::stoi(paramAddress),voice,paramValue);
    }
    else {
      fNode->DspFaust::setVoiceParamValue(paramAddress.c_str(),voice,paramValue);
    }
  }
  else {
    printf("Missing argument\n");
  }
}

void DspFaustNode::getVoiceParamValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && !args[1]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    unsigned long voice = (unsigned long) args[1]->NumberValue();
    if(isInteger(paramAddress)) {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->DspFaust::getVoiceParamValue(std::stoi(paramAddress),voice)));
    }
    else {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->DspFaust::getVoiceParamValue(paramAddress.c_str(),voice)));
    }
  }
  else {
    printf("Missing argument\n");
  }
}

void DspFaustNode::getParamAddress(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    int paramID = (int) args[0]->NumberValue();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate,
      fNode->DspFaust::getParamAddress(paramID)));
  }
  else {
    printf("Missing argument\n");
  }
}

void DspFaustNode::getVoiceParamAddress(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && !args[1]->IsUndefined()) {
    int paramID = (int) args[0]->NumberValue();
    unsigned long voice = (unsigned long) args[1]->NumberValue();
    const char* address = fNode->DspFaust::getVoiceParamAddress(paramID,voice);
    // TODO: smothing's not working here but don't really know what. probably
    // some typing issue
    printf("Toto: %s\n",address);
    //args.GetReturnValue().Set(String::NewFromUtf8(isolate,
    //  fNode->DspFaust::getVoiceParamAddress(paramID,voice)));
      args.GetReturnValue().Set(String::NewFromUtf8(isolate,(char*)address));
  }
  else {
    printf("Missing argument\n");
  }
}

void DspFaustNode::getParamMin(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    if(isInteger(paramAddress)) {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->DspFaust::getParamMin(std::stoi(paramAddress))));
    }
    else {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->DspFaust::getParamMin(paramAddress.c_str())));
    }
  }
  else {
    printf("Missing argument\n");
  }
}

void DspFaustNode::getParamMax(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    if(isInteger(paramAddress)) {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->DspFaust::getParamMax(std::stoi(paramAddress))));
    }
    else {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->DspFaust::getParamMax(paramAddress.c_str())));
    }
  }
  else {
    printf("Missing argument\n");
  }
}

void DspFaustNode::getParamInit(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    if(isInteger(paramAddress)) {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->DspFaust::getParamInit(std::stoi(paramAddress))));
    }
    else {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->DspFaust::getParamInit(paramAddress.c_str())));
    }
  }
  else {
    printf("Missing argument\n");
  }
}

void DspFaustNode::getMetadata(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && !args[1]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    std::string key(*v8::String::Utf8Value(args[1]->ToString()));
    if(isInteger(paramAddress)) {
      args.GetReturnValue().Set(String::NewFromUtf8(isolate,
        fNode->DspFaust::getMetadata(std::stoi(paramAddress),key.c_str())));
    }
    else {
      args.GetReturnValue().Set(String::NewFromUtf8(isolate,
        fNode->DspFaust::getMetadata(paramAddress.c_str(),key.c_str())));
    }
  }
  else {
    printf("Missing argument\n");
  }
}  

void DspFaustNode::propagateAcc(const v8::FunctionCallbackInfo<v8::Value>& args) {
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && !args[1]->IsUndefined()) {
    int acc = (int) args[0]->NumberValue();
    float value = (float) args[1]->NumberValue();
    fNode->DspFaust::propagateAcc(acc,value);
  }
  else {
    printf("Missing argument\n");
  }
}  

void DspFaustNode::setAccConverter(const v8::FunctionCallbackInfo<v8::Value>& args) {
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && 
      !args[1]->IsUndefined() &&
      !args[2]->IsUndefined() &&
      !args[3]->IsUndefined() &&
      !args[4]->IsUndefined() &&
      !args[5]->IsUndefined()) {
    int p = (int) args[0]->NumberValue();
    int acc = (int) args[1]->NumberValue();
    int curve = (int) args[2]->NumberValue();
    float amin = (float) args[3]->NumberValue();
    float amid = (float) args[4]->NumberValue();
    float amax = (float) args[5]->NumberValue();
    fNode->DspFaust::setAccConverter(p,acc,curve,amin,amid,amax);
  }
  else {
    printf("Missing argument\n");
  }
}  

void DspFaustNode::propagateGyr(const v8::FunctionCallbackInfo<v8::Value>& args) {
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && !args[1]->IsUndefined()) {
    int gyr = (int) args[0]->NumberValue();
    float value = (float) args[1]->NumberValue();
    fNode->DspFaust::propagateGyr(gyr,value);
  }
  else {
    printf("Missing argument\n");
  }
} 

void DspFaustNode::setGyrConverter(const v8::FunctionCallbackInfo<v8::Value>& args) {
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && 
      !args[1]->IsUndefined() &&
      !args[2]->IsUndefined() &&
      !args[3]->IsUndefined() &&
      !args[4]->IsUndefined() &&
      !args[5]->IsUndefined()) {
    int p = (int) args[0]->NumberValue();
    int gyr = (int) args[1]->NumberValue();
    int curve = (int) args[2]->NumberValue();
    float amin = (float) args[3]->NumberValue();
    float amid = (float) args[4]->NumberValue();
    float amax = (float) args[5]->NumberValue();
    fNode->DspFaust::setGyrConverter(p,gyr,curve,amin,amid,amax);
  }
  else {
    printf("Missing argument\n");
  }
}   

void DspFaustNode::getCPULoad(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  DspFaustNode* fNode = ObjectWrap::Unwrap<DspFaustNode>(args.Holder());
  args.GetReturnValue().Set(Integer::New(isolate,fNode->DspFaust::getCPULoad()));
}
