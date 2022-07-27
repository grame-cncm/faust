/************************************************************************
 ************************************************************************
 FAUST API Architecture File 
 Copyright (C) 2017 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2014-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
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
