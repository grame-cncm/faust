/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <stdlib.h>
#include <iostream>
#include <sstream>

#include "floats.hh"
#include "global.hh"

using namespace std;

//-----------------------------------------------
// float size coding :
//-----------------------------------------------
//          0: external float (macro name)
//          1: single precision float
//          2: double precision float
//          3: long double precision float
//          4: fixed-point

static const char* mathsuffix[5];       // suffix for math functions
static const char* numsuffix[5];        // suffix for numeric constants
static const char* floatname[5];        // float types
static const char* floatptrname[5];     // float ptr types
static const char* floatptrptrname[5];  // float ptr ptr types
static const char* castname[5];         // float castings
static double      floatmin[5];         // minimum float values before denormals

void initFaustFloat()
{
    // Using in FIR code generation to code math functions type (float/double/quad), same for Rust and C/C++ backends
    mathsuffix[0] = "";
    mathsuffix[1] = "f";
    mathsuffix[2] = "";
    mathsuffix[3] = "l";
    mathsuffix[4] = "";
    
    // Specific for Rust backend
    if (gGlobal->gOutputLang == "rust") {
        numsuffix[0] = "";
        numsuffix[1] = "";
        numsuffix[2] = "";
        numsuffix[3] = "";
        numsuffix[4] = "";
        
        floatname[0] = FLOATMACRO;
        floatname[1] = "F32";
        floatname[2] = "F64";
        floatname[3] = "dummy";
        floatname[4] = "dummy";
        
        floatptrname[0] = FLOATMACROPTR;
        floatptrname[1] = "F32*";
        floatptrname[2] = "F64*";
        floatptrname[3] = "dummy*";
        floatptrname[4] = "dummy*";
        
        floatptrptrname[0] = FLOATMACROPTRPTR;
        floatptrptrname[1] = "F32**";
        floatptrptrname[2] = "F64**";
        floatptrptrname[3] = "dummy**";
        floatptrptrname[4] = "dummy**";
        
        castname[0] = FLOATCASTER;
        castname[1] = "as F32";
        castname[2] = "as F64";
        castname[3] = "(dummy)";
        castname[4] = "(dummy)";
        
        floatmin[0] = 0;
        floatmin[1] = FLT_MIN;
        floatmin[2] = DBL_MIN;
        floatmin[3] = LDBL_MIN;
        floatmin[4] = FLT_MIN;
        
    // Specific for Julia backend
    } else  if (gGlobal->gOutputLang == "julia") {
        numsuffix[0] = "";
        numsuffix[1] = "f0";
        numsuffix[2] = "";
        numsuffix[3] = "";
        numsuffix[4] = "";
        
        floatname[0] = FLOATMACRO;
        floatname[1] = "Float32";
        floatname[2] = "Float64";
        floatname[3] = "dummy";
        floatname[4] = "dummy";
        
        floatptrname[0] = FLOATMACROPTR;
        floatptrname[1] = "Float32*";
        floatptrname[2] = "Float64*";
        floatptrname[3] = "dummy*";
        floatptrname[4] = "dummy*";
        
        floatptrptrname[0] = FLOATMACROPTRPTR;
        floatptrptrname[1] = "Float32**";
        floatptrptrname[2] = "Float64**";
        floatptrptrname[3] = "dummy**";
        floatptrptrname[4] = "dummy**";
        
        castname[0] = FLOATCASTER;
        castname[1] = "(Float32)";
        castname[2] = "(Float64)";
        castname[3] = "(dummy)";
        castname[4] = "(dummy)";
        
        floatmin[0] = 0;
        floatmin[1] = FLT_MIN;
        floatmin[2] = DBL_MIN;
        floatmin[3] = LDBL_MIN;
        floatmin[4] = FLT_MIN;
            
    // Specific for D backend
    } else if (gGlobal->gOutputLang == "dlang") {
        numsuffix[0] = "";
        numsuffix[1] = "";
        numsuffix[2] = "";
        numsuffix[3] = "";
        numsuffix[4] = "";
        
        floatname[0] = FLOATMACRO;
        floatname[1] = "float";
        floatname[2] = "double";
        floatname[3] = "real";
        floatname[4] = "dummy";
        
        floatptrname[0] = FLOATMACROPTR;
        floatptrname[1] = "float*";
        floatptrname[2] = "double*";
        floatptrname[3] = "real*";
        floatptrname[4] = "dummy*";
        
        floatptrptrname[0] = FLOATMACROPTRPTR;
        floatptrptrname[1] = "float**";
        floatptrptrname[2] = "double**";
        floatptrptrname[3] = "real**";
        floatptrptrname[4] = "dummy**";
        
        castname[0] = FLOATCASTER;
        castname[1] = "cast(float)";
        castname[2] = "cast(double)";
        castname[3] = "cast(real)";
        castname[4] = "cast(dummy)";
        
        floatmin[0] = 0;
        floatmin[1] = FLT_MIN;
        floatmin[2] = DBL_MIN;
        floatmin[3] = LDBL_MIN;
        floatmin[4] = FLT_MIN;
        
    // Specific for C/C++ backends
    } else {
        numsuffix[0] = "";
        numsuffix[1] = "f";
        numsuffix[2] = "";
        numsuffix[3] = "L";
        numsuffix[4] = "";
        
        floatname[0] = FLOATMACRO;
        floatname[1] = "float";
        floatname[2] = "double";
        floatname[3] = "quad";
        floatname[4] = "fixpoint_t";
        
        floatptrname[0] = FLOATMACROPTR;
        floatptrname[1] = "float*";
        floatptrname[2] = "double*";
        floatptrname[3] = "quad*";
        floatptrname[4] = "fixpoint_t*";
        
        floatptrptrname[0] = FLOATMACROPTRPTR;
        floatptrptrname[1] = "float**";
        floatptrptrname[2] = "double**";
        floatptrptrname[3] = "quad**";
        floatptrptrname[4] = "fixpoint_t**";
        
        castname[0] = FLOATCASTER;
        castname[1] = "(float)";
        castname[2] = "(double)";
        castname[3] = "(quad)";
        castname[4] = "(fixpoint_t)";
        
        floatmin[0] = 0;
        floatmin[1] = FLT_MIN;
        floatmin[2] = DBL_MIN;
        floatmin[3] = LDBL_MIN;
        floatmin[4] = FLT_MIN;
    }
}

///< suffix for math functions
const char* isuffix()
{
    return mathsuffix[gGlobal->gFloatSize];
}

///< suffix for numeric constants
const char* inumix()
{
    return numsuffix[gGlobal->gFloatSize];
}

const char* ifloat()
{
    return floatname[gGlobal->gFloatSize];
}

const char* ifloatptr()
{
    return floatptrname[gGlobal->gFloatSize];
}

const char* ifloatptrptr()
{
    return floatptrptrname[gGlobal->gFloatSize];
}

const char* icast()
{
    return castname[gGlobal->gFloatSize];
}

double inummin()
{
    return floatmin[gGlobal->gFloatSize];
}

const char* xfloat()
{
    return floatname[0];
}

const char* xcast()
{
    return castname[0];
}

int ifloatsize()
{
    switch (gGlobal->gFloatSize) {
        case 1:
            return gGlobal->gMachineFloatSize;
        case 2:
            return gGlobal->gMachineDoubleSize;
        case 3:
            return gGlobal->gMachineQuadSize;
        case 4:
            return gGlobal->gMachineFixedPointSize;
        default:
            faustassert(false);
            return 0;
    }
}

Typed::VarType itfloat()
{
    switch (gGlobal->gFloatSize) {
        case 1:
            return Typed::kFloat;
        case 2:
            return Typed::kDouble;
        case 3:
            return Typed::kQuad;
        case 4:
            return Typed::kFixedPoint;
        default:
            faustassert(false);
            return Typed::kNoType;
    }
}

Typed::VarType itfloatptr()
{
    switch (gGlobal->gFloatSize) {
        case 1:
            return Typed::kFloat_ptr;
        case 2:
            return Typed::kDouble_ptr;
        case 3:
            return Typed::kQuad_ptr;
        case 4:
            return Typed::kFixedPoint_ptr;
        default:
            faustassert(false);
            return Typed::kNoType;
    }
}

Typed::VarType itfloatptrptr()
{
    switch (gGlobal->gFloatSize) {
        case 1:
            return Typed::kFloat_ptr_ptr;
        case 2:
            return Typed::kDouble_ptr_ptr;
        case 3:
            return Typed::kQuad_ptr_ptr;
        case 4:
            return Typed::kFixedPoint_ptr_ptr;
        default:
            faustassert(false);
            return Typed::kNoType;
    }
}

void printfloatdef(std::ostream& fout)
{
    fout << "#ifndef " << FLOATMACRO << std::endl;
    fout << "#define " << FLOATMACRO << " float" << std::endl;
    fout << "#endif " << std::endl;
    fout << std::endl;
    if (gGlobal->gFloatSize == 3) {
        fout << "typedef long double quad;" << std::endl;
    }
}
