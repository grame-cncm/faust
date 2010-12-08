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
#include "code_container.hh"
#include "fir_instructions.hh"

#include "wss_code_container.hh"

using namespace std;

class FirCodeContainer : public virtual CodeContainer {
public:
    void dump(ostream* dst);

protected:
    FirCodeContainer(int numInputs, int numOutputs)
        :CodeContainer(numInputs, numOutputs)
    {}

    CodeContainer* createScalarContainer(const string& name, int sub_container_type);
    void produceInternal() {}

private:
    void dumpGlobalsAndInit(FIRInstVisitor & firvisitor, ostream* dst);

    virtual void prepareDump(void) {};
    virtual void dumpThread(FIRInstVisitor & firvisitor, ostream* dst) {};
    virtual void dumpComputeBlock(FIRInstVisitor & firvisitor, ostream* dst);
    virtual void dumpCompute(FIRInstVisitor & firvisitor, ostream* dst) = 0;
};

class FirScalarCodeContainer : public FirCodeContainer {
public:
    FirScalarCodeContainer(int numInputs, int numOutputs, int sub_container_type)
        :FirCodeContainer(numInputs, numOutputs)
    {
        fSubContainerType = sub_container_type;
    }

private:
    virtual void dumpCompute(FIRInstVisitor & firvisitor, ostream* dst);
};

class FirVectorCodeContainer : public FirCodeContainer {
public:
    FirVectorCodeContainer(int numInputs, int numOutputs)
        :FirCodeContainer(numInputs, numOutputs)
    {}

private:
    virtual void prepareDump(void);
    virtual void dumpCompute(FIRInstVisitor & firvisitor, ostream* dst);
};

class FirOpenMPCodeContainer : public FirCodeContainer {
public:

    FirOpenMPCodeContainer(int numInputs, int numOutputs)
        :FirCodeContainer(numInputs, numOutputs)
    {}

private:
    virtual void prepareDump(void);
    virtual void dumpCompute(FIRInstVisitor & firvisitor, ostream* dst);
};

class FirWorkStealingCodeContainer : public WSSCodeContainer, public FirCodeContainer {
public:

    FirWorkStealingCodeContainer(int numInputs, int numOutputs)
        :WSSCodeContainer(numInputs, numOutputs), FirCodeContainer(numInputs, numOutputs)
    {}

private:
    virtual void prepareDump(void);
    virtual void dumpCompute(FIRInstVisitor & firvisitor, ostream* dst);
    virtual void dumpThread(FIRInstVisitor & firvisitor, ostream* dst);
};

#endif
