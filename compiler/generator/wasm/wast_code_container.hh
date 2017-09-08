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

#ifndef _WAST_CODE_CONTAINER_H
#define _WAST_CODE_CONTAINER_H

#include "code_container.hh"
#include "wast_instructions.hh"
#include "dsp_factory.hh"
#include "fir_to_fir.hh"

using namespace std;

class WASTCodeContainer : public virtual CodeContainer {

    protected:

        std::ostream* fOut;
        std::stringstream fOutAux;
        std::stringstream fHelper;
        int fInternalMemory;
    
        void generateWASTBlock(BlockInst* instructions)
        {
            // Moves all variables declaration at the beginning of the block
            MoveVariablesInFront3 mover;
            BlockInst* block = mover.getCode(instructions);
            block->accept(gGlobal->gWASTVisitor);
        }
    
        DeclareFunInst* generateInstanceInitFun(const string& name, const string& obj, bool ismethod, bool isvirtual, bool addreturn);
    
    public:

        WASTCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, bool internal_memory);
        virtual ~WASTCodeContainer()
        {}

        virtual void produceClass();
        virtual void generateCompute(int tab) = 0;
    
        void produceInternal();
        virtual dsp_factory_base* produceFactory();
    
        CodeContainer* createScalarContainer(const string& name, int sub_container_type);
        CodeContainer* createScalarContainer(const string& name, int sub_container_type, bool internal_memory = true);

        static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs, std::ostream* dst, bool internal_memory);
};

class WASTScalarCodeContainer : public WASTCodeContainer {

    protected:

    public:

        WASTScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, int sub_container_type, bool internal_memory);
        virtual ~WASTScalarCodeContainer();

        void generateCompute(int tab);

};

class WASTVectorCodeContainer : public WASTCodeContainer {
    
    protected:
        
    public:
        
        WASTVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, bool internal_memory);
        virtual ~WASTVectorCodeContainer();
        
        void generateCompute(int tab);
    
};

#endif
