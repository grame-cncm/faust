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

StatementInst* InstructionsCompiler1::generateInitArray(const string& vname, BasicTyped* ctype, int delay)
{
    ValueInst*  init  = InstBuilder::genTypedZero(ctype);
    BasicTyped* typed = ctype;
    string      index = gGlobal->getFreshID("l");

    // Generates table declaration
    pushDeclare(InstBuilder::genDecStructVar(vname, InstBuilder::genArrayTyped(typed, delay)));

    ValueInst* upperBound = InstBuilder::genInt32NumInst(delay);
    // Generates init table loop
    SimpleForLoopInst* loop = InstBuilder::genSimpleForLoopInst(index, upperBound);

    LoadVarInst* loadVarInst = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop));
    loop->pushFrontInst(InstBuilder::genStoreArrayStructVar(vname, loadVarInst, init));
    return loop;
}

StatementInst* InstructionsCompiler1::generateShiftArray(const string& vname, int delay)
{
    string index = gGlobal->getFreshID("j");

    ValueInst*         upperBound  = InstBuilder::genInt32NumInst(delay);
    ValueInst*         lowerBound  = InstBuilder::genInt32NumInst(1);
    
    SimpleForLoopInst* loop        = InstBuilder::genSimpleForLoopInst(index, upperBound, lowerBound, true);
    LoadVarInst*       loadVarInst = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop));
    ValueInst*         load_value2 = InstBuilder::genSub(loadVarInst, InstBuilder::genInt32NumInst(1));
    ValueInst*         load_value3 = InstBuilder::genLoadArrayStructVar(vname, load_value2);

    loop->pushFrontInst(InstBuilder::genStoreArrayStructVar(vname, loadVarInst, load_value3));
    return loop;
}

StatementInst* InstructionsCompiler1::generateCopyArray(const string& vname_to, const string& vname_from, int size)
{
    string index = gGlobal->getFreshID("j");

    ValueInst*         upperBound  = InstBuilder::genInt32NumInst(size);
    SimpleForLoopInst* loop        = InstBuilder::genSimpleForLoopInst(index, upperBound);
    LoadVarInst*       loadVarInst = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop));
    ValueInst*         load_value  = InstBuilder::genLoadArrayStructVar(vname_from, loadVarInst);

    loop->pushFrontInst(InstBuilder::genStoreArrayStackVar(vname_to, loadVarInst, load_value));
    return loop;
}
