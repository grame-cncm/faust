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

using namespace std;

class WASMCodeContainer : public virtual CodeContainer {

    protected:

        WASMInstVisitor fCodeProducer;
        std::ostream* fOut;
        
        void produceInfoFunctions(int tabs, const string& classname, bool isvirtual);

    public:

        WASMCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
            :fCodeProducer(out), fOut(out)
        {
            initializeCodeContainer(numInputs, numOutputs);
            fKlassName = name;
        }
        virtual ~WASMCodeContainer()
        {}

        virtual void produceClass();
        virtual void generateCompute(int tab) = 0;
        void produceInternal();

        CodeContainer* createScalarContainer(const string& name, int sub_container_type);

        static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs, ostream* dst);
};

class WASMScalarCodeContainer : public WASMCodeContainer {

    protected:

    public:

        WASMScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, int sub_container_type);
        virtual ~WASMScalarCodeContainer();

        void generateCompute(int tab);

};

#endif
