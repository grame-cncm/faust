/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
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

#include "interpreter_code_container.hh"
#include "exception.hh"
#include "Text.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

template <class T> map <string, int> InterpreterInstVisitor<T>::gFunctionSymbolTable;     
template <class T> map <string, string> InterpreterInstVisitor<T>::gMathLibTable;

CodeContainer* InterpreterCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new InterpreterScalarCodeContainer(name, 0, 1, sub_container_type);
}

CodeContainer* InterpreterCodeContainer::createContainer(const string& name, int numInputs, int numOutputs)
{
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for Interpreter\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for Interpreter\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for Interpreter\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for Interpreter\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("Vector mode not supported for Interpreter\n");
    } else {
        container = new InterpreterScalarCodeContainer(name, numInputs, numOutputs, kInt);
    }

    return container;
}

// Scalar
InterpreterScalarCodeContainer::InterpreterScalarCodeContainer(const string& name,  int numInputs, int numOutputs, int sub_container_type)
    :InterpreterCodeContainer(name, numInputs, numOutputs)
{
     fSubContainerType = sub_container_type;
}

InterpreterScalarCodeContainer::~InterpreterScalarCodeContainer()
{}

void InterpreterCodeContainer::produceInternal()
{
    
}

interpreter_dsp_aux<float>* InterpreterCodeContainer::produceModuleFloat()
{
    cout << "InterpreterCodeContainer::produceModuleFloat() " << fNumInputs << " " << fNumOutputs << endl;
    
    return new interpreter_dsp_aux<float>(fNumInputs, fNumOutputs, 4096, 4096, fCodeProducer.fUserInterfaceBlock, NULL, NULL, NULL);
}

interpreter_dsp_aux<double>* InterpreterCodeContainer::produceModuleDouble()
{
    cout << "InterpreterCodeContainer::produceModuleDouble()" << endl;
    //return new interpreter_dsp_aux<double>(fNumInputs, fNumOutputs, 0, 0, NULL, NULL, NULL, NULL);
    return NULL;
}

interpreter_dsp_aux<quad>* InterpreterCodeContainer::produceModuleQuad()
{
    cout << "InterpreterCodeContainer::produceModuleQuad()" << endl;
    //return new interpreter_dsp_aux<quad>(fNumInputs, fNumOutputs, 0, 0, NULL, NULL, NULL, NULL);
    return NULL;
}

void InterpreterCodeContainer::produceClass()
{
    printf("InterpreterCodeContainer::produceClass\n");
    generateUserInterface(&fCodeProducer);
}

void InterpreterCodeContainer::produceInfoFunctions(int tabs, const string& classname, bool isvirtual)
{   
   
}

void InterpreterScalarCodeContainer::generateCompute(int n)
{
   
}

