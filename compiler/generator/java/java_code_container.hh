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

#ifndef _JAVA_CODE_CONTAINER_H
#define _JAVA_CODE_CONTAINER_H

#include "code_container.hh"
#include "java_instructions.hh"
#include "dsp_factory.hh"

using namespace std;           

class JAVACodeContainer : public virtual CodeContainer {

    protected:

        JAVAInstVisitor fCodeProducer;
        std::ostream* fOut;
        string fSuperKlassName;
    
    public:

        JAVACodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
            :fCodeProducer(out), fOut(out), fSuperKlassName(super)
        {
            initializeCodeContainer(numInputs, numOutputs);
            fKlassName = name;
        }
        virtual ~JAVACodeContainer()
        {}

        virtual void produceClass();
        virtual void generateCompute(int tab) = 0;
        void produceInternal();
    
        virtual dsp_factory_base* produceFactory();
    
        virtual void printHeader()
        {
             CodeContainer::printHeader(*fOut);
        }

        CodeContainer* createScalarContainer(const string& name, int sub_container_type);

        static CodeContainer* createContainer(const string& name, const string& super, int numInputs, int numOutputs, ostream* dst = new stringstream());
};

class JAVAScalarCodeContainer : public JAVACodeContainer {

    protected:

    public:

        JAVAScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out, int sub_container_type);
        virtual ~JAVAScalarCodeContainer();

        void generateCompute(int tab);

};

#endif
