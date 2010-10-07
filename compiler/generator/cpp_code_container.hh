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

#ifndef _CPP_CODE_CONTAINER_H
#define _CPP_CODE_CONTAINER_H

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
#include "code_container.hh"
#include "cpp_instructions.hh"

using namespace std;

class CPPCodeContainer : public CodeContainer {

    protected:

        CPPInstVisitor fCodeProducer;
        std::ostream* fOut;
        string fKlassName;
        string fSuperKlassName;

    public:

        CPPCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
            :CodeContainer(numInputs, numOutputs), fCodeProducer(out), fOut(out), fKlassName(name), fSuperKlassName(super)
        {}
        virtual ~CPPCodeContainer()
        {}

        virtual void produceClass();
        virtual void generateCompute(int tab) = 0;
        virtual void produceInternal();

        CodeContainer* createScalarContainer(const string& name);

};

class CPPScalarCodeContainer : public CPPCodeContainer {

    protected:


    public:

        CPPScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
        virtual ~CPPScalarCodeContainer();

        void generateCompute(int tab);

};

class CPPVectorCodeContainer : public CPPCodeContainer {

    protected:


    public:

        CPPVectorCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
        virtual ~CPPVectorCodeContainer();

        void generateCompute(int tab);

};


class CPPOpenMPCodeContainer : public CPPCodeContainer {

    protected:


    public:

        CPPOpenMPCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
        virtual ~CPPOpenMPCodeContainer();

        void generateCompute(int tab);

};

class CPPWorkStealingCodeContainer : public CPPCodeContainer {

    protected:


    public:

        CPPWorkStealingCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
        virtual ~CPPWorkStealingCodeContainer();

        void produceClass();
        void generateCompute(int tab);

};

#endif
