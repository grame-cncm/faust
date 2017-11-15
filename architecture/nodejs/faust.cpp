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

#include <node.h>
#include "DspFaustNode.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  DspFaustNode::Init(exports);
}

NODE_MODULE(faust, InitAll)