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

#ifndef _WASM_CODE_CONTAINER_H
#define _WASM_CODE_CONTAINER_H

#include "code_container.hh"
#include "wasm_instructions.hh"
#include "dsp_factory.hh"
#include "fir_to_fir.hh"

using namespace std;

class WASMCodeContainer : public virtual CodeContainer {

    protected:

        std::ostream* fOut;
        BufferWithRandomAccess fBinaryOut;
        std::stringstream fHelper;
        int fInternalMemory; // Whether memory is allocated inside wasm module or JS
    
        DeclareFunInst* generateInstanceInitFun(const string& name, const string& obj, bool ismethod, bool isvirtual, bool addreturn);
        DeclareFunInst* generateClassInit(const string& name);
        DeclareFunInst* generateInstanceClear(const string& name, const string& obj, bool ismethod, bool isvirtual);
        DeclareFunInst* generateInstanceConstants(const string& name, const string& obj, bool ismethod, bool isvirtual);
        DeclareFunInst* generateInstanceResetUserInterface(const string& name, const string& obj, bool ismethod, bool isvirtual);
   
    public:

        WASMCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, bool internal_memory = true);
        virtual ~WASMCodeContainer()
        {}

        virtual void produceClass();
        virtual void generateCompute() = 0;
    
        void produceInternal();
        virtual dsp_factory_base* produceFactory();
    
        CodeContainer* createScalarContainer(const string& name, int sub_container_type);
        CodeContainer* createScalarContainer(const string& name, int sub_container_type, bool internal_memory = true);

        static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs, std::ostream* dst, bool internal_memory);
};

class WASMScalarCodeContainer : public WASMCodeContainer {

    protected:

    public:

        WASMScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, int sub_container_type, bool internal_memory);
        virtual ~WASMScalarCodeContainer();

        void generateCompute();

};

class WASMVectorCodeContainer : public WASMCodeContainer {
    
    protected:
        
    public:
        
        WASMVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, bool internal_memory);
        virtual ~WASMVectorCodeContainer();
        
        void generateCompute();
    
};

#endif
