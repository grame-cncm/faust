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

#include "code_container.hh"
#include "fir_instructions.hh"
#include "vec_code_container.hh"
#include "omp_code_container.hh"
#include "wss_code_container.hh"

using namespace std;

class FirCodeContainer : public virtual CodeContainer {
    
    private:
        
        void dumpGlobalsAndInit(FIRInstVisitor& firvisitor, ostream* dst);
        void dumpUserInterface(FIRInstVisitor& firvisitor, ostream* dst);
        void dumpSubContainers(FIRInstVisitor& firvisitor, ostream* dst);
        
        virtual void dumpThread(FIRInstVisitor& firvisitor, ostream* dst) {};
        virtual void dumpComputeBlock(FIRInstVisitor& firvisitor, ostream* dst);
        virtual void dumpCompute(FIRInstVisitor& firvisitor, ostream* dst) = 0;
        virtual void dumpMemory(ostream* dst);
        virtual void dumpFlatten(ostream* dst);
        
        std::ostream* fOut;
        
    protected:
        
        FirCodeContainer(const string& name, int numInputs, int numOutputs, ostream* dst, bool top_level)
        {
            fTopLevel = top_level;
            fKlassName = name;
            fOut = dst;
            initializeCodeContainer(numInputs, numOutputs);
        }
        
        CodeContainer* createScalarContainer(const string& name, int sub_container_type);
        void produceInternal();
        void produceClass();
    
        virtual dsp_factory_base* produceFactory();
        
        bool fTopLevel;

    public:
    
        static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs, ostream* dst, bool top_level = false);
    
};

class FirScalarCodeContainer : public FirCodeContainer {
    
    private:
    
        virtual void dumpCompute(FIRInstVisitor& firvisitor, ostream* dst);


    public:
    
        FirScalarCodeContainer(const string& name, int numInputs, int numOutputs, int sub_container_type, ostream* dst, bool top_level)
            :FirCodeContainer(name, numInputs, numOutputs, dst, top_level)
        {
            fSubContainerType = sub_container_type;
        }

};

class FirVectorCodeContainer : public VectorCodeContainer, public FirCodeContainer {

    private:
    
        virtual void dumpCompute(FIRInstVisitor& firvisitor, ostream* dst);
    
    public:
        
        FirVectorCodeContainer(const string& name, int numInputs, int numOutputs, ostream* dst, bool top_level)
        :VectorCodeContainer(numInputs, numOutputs), FirCodeContainer(name, numInputs, numOutputs, dst, top_level)
        {}
    
};

class FirOpenMPCodeContainer : public OpenMPCodeContainer, public FirCodeContainer {

    private:
    
        virtual void dumpCompute(FIRInstVisitor& firvisitor, ostream* dst);
    
    public:
        
        FirOpenMPCodeContainer(const string& name, int numInputs, int numOutputs, ostream* dst, bool top_level)
        :OpenMPCodeContainer(numInputs, numOutputs), FirCodeContainer(name, numInputs, numOutputs, dst, top_level)
        {}
    
};

class FirWorkStealingCodeContainer : public WSSCodeContainer, public FirCodeContainer {

    private:
        
        virtual void dumpCompute(FIRInstVisitor& firvisitor, ostream* dst);
        virtual void dumpThread(FIRInstVisitor& firvisitor, ostream* dst);
        virtual void dumpMemory(ostream* dst);

    public:

        FirWorkStealingCodeContainer(const string& name, int numInputs, int numOutputs, ostream* dst, bool top_level)
            :WSSCodeContainer(numInputs, numOutputs, "this"), FirCodeContainer(name, numInputs, numOutputs, dst, top_level)
        {}

 };

#endif
