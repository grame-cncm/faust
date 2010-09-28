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

#ifndef _FIR_CODE_CONTAINER_H
#define _FIR_CODE_CONTAINER_H

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
using namespace std;

#include "code_container.hh"
#include "fir_instructions.hh"

class FirCodeContainer : public CodeContainer {

     public:
    
        FirCodeContainer(int numInputs, int numOutputs)
            :CodeContainer(numInputs, numOutputs)
        {}
        virtual ~FirCodeContainer()
        {}
        
        CodeContainer* createScalarContainer(const string& name);
        void produceInternal() {}
                  
};

class FirScalarCodeContainer : public FirCodeContainer {

    protected:
    
   
    public:
    
        FirScalarCodeContainer(int numInputs, int numOutputs)
            :FirCodeContainer(numInputs, numOutputs)
        {}
        virtual ~FirScalarCodeContainer()
        {}
        
        void dump(ostream* dst);
         
};

class FirVectorCodeContainer : public FirCodeContainer {

    protected:
    
   
    public:
    
        FirVectorCodeContainer(int numInputs, int numOutputs)
            :FirCodeContainer(numInputs, numOutputs)
        {}
        virtual ~FirVectorCodeContainer()
        {}
        
        void dump(ostream* dst);
         
};

class FirOpenMPCodeContainer : public FirCodeContainer {

    protected:
    
   
    public:
    
        FirOpenMPCodeContainer(int numInputs, int numOutputs)
            :FirCodeContainer(numInputs, numOutputs)
        {}
        virtual ~FirOpenMPCodeContainer()
        {}
        
        void dump(ostream* dst);
         
};

class FirWorkStealingCodeContainer : public FirCodeContainer {

    protected:
    
   
    public:
    
        FirWorkStealingCodeContainer(int numInputs, int numOutputs)
            :FirCodeContainer(numInputs, numOutputs)
        {}
        virtual ~FirWorkStealingCodeContainer()
        {}
        
        void dump(ostream* dst);
         
};

#endif
