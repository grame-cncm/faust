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

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
#include "fir_code_container.hh"
using namespace std;

extern int gVectorLoopVariant;
map <string, int> FIRInstVisitor::gGlobalTable;

CodeContainer* FirCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new FirScalarCodeContainer(0, 1, sub_container_type);
}

void FirCodeContainer::dumpGlobalsAndInit(FIRInstVisitor & firvisitor, ostream* dst)
{
    // Subclasses
    list<CodeContainer*>::const_iterator it;
    for (it = fSubContainers.begin(); it != fSubContainers.end(); it++) {
        (*it)->dump(dst);
    }

    /// User Interface
    if (fUserInterfaceInstructions->fCode.size() > 0) {
        *dst << "======= User Interface ==========" << std::endl;
        *dst << std::endl;
        fUserInterfaceInstructions->accept(&firvisitor);
        *dst << std::endl;
    }

    // General
    if (fGlobalDeclarationInstructions->fCode.size() > 0) {
        *dst << "======= Global declarations ==========" << std::endl;
        *dst << std::endl;
        fGlobalDeclarationInstructions->accept(&firvisitor);
        *dst << std::endl;
    }

    if (fDeclarationInstructions->fCode.size() > 0) {
        *dst << "======= Declarations ==========" << std::endl;
        *dst << std::endl;
        fDeclarationInstructions->accept(&firvisitor);
        *dst << std::endl;
    }

    if (fInitInstructions->fCode.size() > 0) {
        *dst << "======= Init ==========" << std::endl;
        *dst << std::endl;
        fInitInstructions->accept(&firvisitor);
        *dst << std::endl;
    }

    if (fStaticInitInstructions->fCode.size() > 0) {
        *dst << "======= Static Init ==========" << std::endl;
        *dst << std::endl;
        fStaticInitInstructions->accept(&firvisitor);
        *dst << std::endl;
    }

    if (fDestroyInstructions->fCode.size() > 0) {
        *dst << "======= Destroy ==========" << std::endl;
        *dst << std::endl;
        fDestroyInstructions->accept(&firvisitor);
        *dst << std::endl;
    }
}

void FirCodeContainer::dumpComputeBlock(FIRInstVisitor & firvisitor, ostream* dst)
{
    if (fComputeBlockInstructions->fCode.size() > 0) {
        *dst << "======= Compute Block ==========" << std::endl;
        *dst << std::endl;
        fComputeBlockInstructions->accept(&firvisitor);
        *dst << std::endl;
    }
}

void FirCodeContainer::dump(ostream* dst)
{
    prepareDump();

    FIRInstVisitor firvisitor(dst);
    dumpGlobalsAndInit(firvisitor, dst);
    dumpThread(firvisitor, dst);
    dumpComputeBlock(firvisitor, dst);
    dumpCompute(firvisitor, dst);
}

void FirScalarCodeContainer::dumpCompute(FIRInstVisitor & firvisitor, ostream* dst)
{
    *dst << "======= Compute DSP ==========" << std::endl;
    *dst << std::endl;
    ForLoopInst* loop = fCurLoop->generateScalarLoop("count");
    loop->accept(&firvisitor);
    *dst << std::endl;
}

void FirVectorCodeContainer::dumpCompute(FIRInstVisitor & firvisitor, ostream* dst)
{
    // Generate it
    fDAGBlock->accept(&firvisitor);

    // Possibly generate separated functions
    if (fComputeFunctions->fCode.size() > 0) {
        *dst << std::endl;
        *dst << "======= Separated functions ==========" << std::endl;
        *dst << std::endl;
        fComputeFunctions->accept(&firvisitor);
        *dst << std::endl;
    } else {
        *dst << std::endl;
    }
}

void FirOpenMPCodeContainer::dumpCompute(FIRInstVisitor & firvisitor, ostream* dst)
{
    // Generate it
    fGlobalLoopBlock->accept(&firvisitor);

    // Possibly generate separated functions
    if (fComputeFunctions->fCode.size() > 0) {
        *dst << std::endl;
        *dst << "======= Separated functions ==========" << std::endl;
        *dst << std::endl;
        fComputeFunctions->accept(&firvisitor);
        *dst << std::endl;
    }
}

void FirOpenMPCodeContainer::prepareDump()
{
    // Sort arrays to be at the begining
    fComputeBlockInstructions->fCode.sort(sortArrayDeclarations);

    // Prepare global loop
    string counter = "fullcount";
    fGlobalLoopBlock = generateDAGLoopOMP(counter);
}

void FirWorkStealingCodeContainer::dumpCompute(FIRInstVisitor & firvisitor, ostream* dst)
{
    // Possibly generate separated functions
    if (fComputeFunctions->fCode.size() > 0) {
        *dst << std::endl;
        *dst << "======= Separated functions ==========" << std::endl;
        *dst << std::endl;
        fComputeFunctions->accept(&firvisitor);
        *dst << std::endl;
    }
}

void FirWorkStealingCodeContainer::dumpThread(FIRInstVisitor& firvisitor, ostream* dst)
{
    // Generate it
    *dst << "======= Compute Thread ==========" << std::endl;
    *dst << std::endl;
    fThreadLoopBlock->accept(&firvisitor);
    *dst << std::endl;
}
