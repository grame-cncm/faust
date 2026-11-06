/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include <climits>

#include "xtendedCodegen.hh"
#include "code_container.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

/*
 -mapp computes floor and ceil from int(x) instead of calling the library. The primitive
 keeps its own type and is replaced only here, by the code generation: rewritten as a
 signal, it would be typed as the rewriting, whose interval is wider (a select2 joins
 both branches), and -mapp would reject programs the default compilation accepts (a
 delay found possibly negative). The type of the primitive is the interval of floor or
 ceil, so the generated code must compute exactly this value: int(x) is exact only when
 its result fits an int (INT_MIN - 1 < x < INT_MAX + 1); beyond, the conversion is not
 portable (x86 gives INT_MIN, ARM saturates) and the library function is called.
 */
bool xtendedCodegen::approxByTruncation(::Type arg)
{
    if (!gGlobal->gMathApprox) {
        return false;
    }
    interval i = arg->getInterval();
    return !i.isEmpty() && i.lo() > double(INT_MIN) - 1. && i.hi() < double(INT_MAX) + 1.;
}

ValueInst* xtendedCodegen::generateFun(CodeContainer* container, const string& fun_name,
                                const Values& args, ::Type result, ConstTypes types)
{
    Typed::VarType         rtype = convert2FIRType(result->nature());
    vector<Typed::VarType> atypes;
    for (size_t i = 0; i < types.size(); i++) {
        atypes.push_back(convert2FIRType(types[i]->nature()));
    }
    return container->pushFunction(fun_name, rtype, atypes, args);
}
