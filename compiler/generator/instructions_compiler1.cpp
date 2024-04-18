/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2017-2021 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "instructions_compiler1.hh"

using namespace std;

StatementInst* InstructionsCompiler1::generateInitArray(const string& vname, BasicTyped* ctype,
                                                        int delay)
{
    ValueInst*  init  = IB::genTypedZero(ctype);
    BasicTyped* typed = ctype;
    string      index = gGlobal->getFreshID("l");

    // Generates table declaration
    pushDeclare(IB::genDecStructVar(vname, IB::genArrayTyped(typed, delay)));

    ValueInst* upperBound = IB::genInt32NumInst(delay);
    // Generates init table loop
    SimpleForLoopInst* loop = IB::genSimpleForLoopInst(index, upperBound);

    LoadVarInst* loadVarInst = IB::genLoadVarInst(IB::genNamedAddress(index, Address::kLoop));
    loop->pushFrontInst(IB::genStoreArrayStructVar(vname, loadVarInst, init));
    return loop;
}

StatementInst* InstructionsCompiler1::generateShiftArray(const string& vname, int delay)
{
    string index = gGlobal->getFreshID("j");

    ValueInst* upperBound = IB::genInt32NumInst(delay);
    ValueInst* lowerBound = IB::genInt32NumInst(1);

    SimpleForLoopInst* loop        = IB::genSimpleForLoopInst(index, upperBound, lowerBound, true);
    LoadVarInst*       loadVarInst = IB::genLoadVarInst(IB::genNamedAddress(index, Address::kLoop));
    ValueInst*         load_value2 = IB::genSub(loadVarInst, IB::genInt32NumInst(1));
    ValueInst*         load_value3 = IB::genLoadArrayStructVar(vname, load_value2);

    loop->pushFrontInst(IB::genStoreArrayStructVar(vname, loadVarInst, load_value3));
    return loop;
}

StatementInst* InstructionsCompiler1::generateCopyArray(const string& vname_to,
                                                        const string& vname_from, int size)
{
    string index = gGlobal->getFreshID("j");

    ValueInst*         upperBound  = IB::genInt32NumInst(size);
    SimpleForLoopInst* loop        = IB::genSimpleForLoopInst(index, upperBound);
    LoadVarInst*       loadVarInst = IB::genLoadVarInst(IB::genNamedAddress(index, Address::kLoop));
    ValueInst*         load_value  = IB::genLoadArrayStructVar(vname_from, loadVarInst);

    loop->pushFrontInst(IB::genStoreArrayStackVar(vname_to, loadVarInst, load_value));
    return loop;
}
