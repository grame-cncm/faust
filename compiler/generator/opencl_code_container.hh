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

#ifndef _OPENCL_CODE_CONTAINER_H
#define _OPENCL_CODE_CONTAINER_H

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
using namespace std;

#include "code_container.hh"
#include "opencl_instructions.hh"

class OpenCLCodeContainer : public CodeContainer {

    protected:
    
        OpenCLInstVisitor fCodeProducer;
        std::ostream* fOut;
        string fStructName;
        string fPrefix;   // Prefix for function name

    public:
    
        OpenCLCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, const string& prefix = "")
            :OpenCLCodeContainer(numInputs, numOutputs), fCodeProducer(out, name, prefix), fOut(out), fStructName(name), fPrefix(prefix)
        {}
        virtual ~OpenCLCodeContainer()
        {}
        
        virtual void produceClass();
        virtual void generateCompute(int tab) = 0;
        void produceInternal();
        
        void generateCompute(int n);
        
        CodeContainer* createScalarContainer(const string& name);
             
};

#endif
