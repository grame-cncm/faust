/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

#ifndef _ASMJAVASCRIPT_CODE_CONTAINER_H
#define _ASMJAVASCRIPT_CODE_CONTAINER_H

#include "code_container.hh"
#include "vec_code_container.hh"
#include "asmjs_instructions.hh"

using namespace std;

class ASMJAVAScriptCodeContainer : public virtual CodeContainer {

    protected:

        // One gASMJSVisitor static visitor for subcontainers and global container moved in global,
        // so that subcontainers and 'mydsp' class are generated with a unique visitor, using a single memory area.
        std::ostream* fOut;
        string fObjPrefix;
 
    public:

        ASMJAVAScriptCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out);
        virtual ~ASMJAVAScriptCodeContainer()
        {}

        virtual void produceClass();
        virtual void generateCompute(int tab) = 0;
        void produceInternal();
    
        int getStructSize(); 

        CodeContainer* createScalarContainer(const string& name, int sub_container_type);

        static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs, ostream* dst);
};

class ASMJAVAScriptScalarCodeContainer : public ASMJAVAScriptCodeContainer {

    protected:

    public:

        ASMJAVAScriptScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, int sub_container_type);
        virtual ~ASMJAVAScriptScalarCodeContainer();

        void generateCompute(int tab);

};

class ASMJAVAScriptVectorCodeContainer : public VectorCodeContainer, public ASMJAVAScriptCodeContainer {

    protected:

    public:

        ASMJAVAScriptVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out);
        virtual ~ASMJAVAScriptVectorCodeContainer();

        void generateCompute(int tab);

};

#endif
