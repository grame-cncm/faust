/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

#include "julia_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "fir_function_builder.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

/*
 Julia backend and module description:
*/

map<string, bool> JuliaInstVisitor::gFunctionSymbolTable;

dsp_factory_base* JuliaCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), "");
}

CodeContainer* JuliaCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new JuliaScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* JuliaCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
{
    gGlobal->gDSPStruct = true;
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for C\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for C\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for Julia\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for Julia\n");
    } else if (gGlobal->gVectorSwitch) {
        container = new JuliaVectorCodeContainer(name, numInputs, numOutputs, dst);
    } else {
        container = new JuliaScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

void JuliaCodeContainer::produceInternal()
{
}

void JuliaCodeContainer::produceClass()
{
    *fOut << "// TODO: generate Julia code here" << endl;
}

void JuliaCodeContainer::produceMetadata(int tabs)
{
    
}

// Scalar
JuliaScalarCodeContainer::JuliaScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out,
                                                   int sub_container_type)
    : JuliaCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

// Vector
JuliaVectorCodeContainer::JuliaVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    : VectorCodeContainer(numInputs, numOutputs), JuliaCodeContainer(name, numInputs, numOutputs, out)
{
}

