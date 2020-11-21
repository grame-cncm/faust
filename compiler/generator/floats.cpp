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

#define FLOATMACRO "FAUSTFLOAT"
#define FLOATMACROPTR "FAUSTFLOAT*"
#define FLOATCASTER "(" FLOATMACRO ")"

//-----------------------------------------------
// float size coding :
//-----------------------------------------------
//          0: external float (macro name)
//          1: single precision float
//          2: double precision float
//          3: long double precision float

static const char* mathsuffix[4];  // suffix for math functions
static const char* numsuffix[4];   // suffix for numeric constants
static const char* floatname[4];   // float types
static const char* castname[4];    // float castings
static double      floatmin[4];    // minimum float values before denormals

void initFaustFloat()
{
    // Using in FIR code generation to code math functions type (float/double/quad), same for Rust and C/C++ backends
    mathsuffix[0] = "";
    mathsuffix[1] = "f";
    mathsuffix[2] = "";
    mathsuffix[3] = "l";
    
    // Specific for Rust backend
    if (gGlobal->gOutputLang == "rust") {
        numsuffix[0] = "";
        numsuffix[1] = "";
        numsuffix[2] = "";
        numsuffix[3] = "";
        
        floatname[0] = FLOATMACRO;
        floatname[1] = "f32";
        floatname[2] = "f64";
        floatname[3] = "dummy";
        
        castname[0] = FLOATCASTER;
        castname[1] = "as f32";
        castname[2] = "as f64";
        castname[3] = "(dummy)";
        
        floatmin[0] = 0;
        floatmin[1] = FLT_MIN;
        floatmin[2] = DBL_MIN;
        floatmin[3] = LDBL_MIN;
        
        // Specific for D backend
    }
    else if (gGlobal->gOutputLang == "dlang") {
        numsuffix[0] = "";
        numsuffix[1] = "";
        numsuffix[2] = "";
        numsuffix[3] = "";
        
        floatname[0] = FLOATMACRO;
        floatname[1] = "float";
        floatname[2] = "double";
        floatname[3] = "real";
        
        castname[0] = FLOATCASTER;
        castname[1] = "cast(float)";
        castname[2] = "cast(double)";
        castname[3] = "cast(real)";
        
        floatmin[0] = 0;
        floatmin[1] = FLT_MIN;
        floatmin[2] = DBL_MIN;
        floatmin[3] = LDBL_MIN;
        
        // Specific for C/C++ backends
    } 
     else {
        numsuffix[0] = "";
        numsuffix[1] = "f";
        numsuffix[2] = "";
        numsuffix[3] = "L";
        
        floatname[0] = FLOATMACRO;
        floatname[1] = "float";
        floatname[2] = "double";
        floatname[3] = "quad";
        
        castname[0] = FLOATCASTER;
        castname[1] = "(float)";
        castname[2] = "(double)";
        castname[3] = "(quad)";
        
        floatmin[0] = 0;
        floatmin[1] = FLT_MIN;
        floatmin[2] = DBL_MIN;
        floatmin[3] = LDBL_MIN;
    }
}

const char* isuffix()
{
    return mathsuffix[gGlobal->gFloatSize];
}  ///< suffix for math functions
const char* inumix()
{
    return numsuffix[gGlobal->gFloatSize];
}  ///< suffix for numeric constants
const char* ifloat()
{
    return floatname[gGlobal->gFloatSize];
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
            return 4;
        case 2:
            return 8;
        case 3:
            return 16;
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
        default:
            faustassert(false);
            return Typed::kNoType;
    }
}

void printfloatdef(std::ostream& fout, bool quad)
{
    fout << "#ifndef " << FLOATMACRO << std::endl;
    fout << "#define " << FLOATMACRO << " float" << std::endl;
    fout << "#endif " << std::endl;
    fout << std::endl;
    if (quad) {
        fout << "typedef long double quad;" << std::endl;
    }
}
