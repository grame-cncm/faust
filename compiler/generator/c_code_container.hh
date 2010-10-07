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

#ifndef _C_CODE_CONTAINER_H
#define _C_CODE_CONTAINER_H

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
#include "code_container.hh"
#include "c_instructions.hh"

using namespace std;

class CCodeContainer : public CodeContainer {

    protected:

        CInstVisitor fCodeProducer;
        std::ostream* fOut;
        string fStructName;
        string fPrefix;   // Prefix for function name

    public:

        CCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, const string& prefix = "")
            :CodeContainer(numInputs, numOutputs), fCodeProducer(out, name, prefix), fOut(out), fStructName(name), fPrefix(prefix)
        {}
        virtual ~CCodeContainer()
        {}

        virtual void produceClass();
        virtual void generateCompute(int tab) = 0;
        void produceInternal();

        CodeContainer* createScalarContainer(const string& name);

};

class CScalarCodeContainer : public CCodeContainer {

    protected:


    public:

        CScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, const string& prefix = "");
        virtual ~CScalarCodeContainer();

        void generateCompute(int tab);

};

class CVectorCodeContainer : public CCodeContainer {

    protected:


    public:

        CVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, const string& prefix = "");
        virtual ~CVectorCodeContainer();

        void generateCompute(int n);

};

class COpenMPCodeContainer : public CCodeContainer {

    protected:


    public:

        COpenMPCodeContainer(const string& name,int numInputs, int numOutputs, std::ostream* out, const string& prefix = "");
        virtual ~COpenMPCodeContainer();

        void generateCompute(int tab);

};

class CWorkStealingCodeContainer : public CCodeContainer {

    protected:


    public:

        CWorkStealingCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, const string& prefix = "");
        virtual ~CWorkStealingCodeContainer();

        void produceClass();
        void generateCompute(int tab);
};

#endif
