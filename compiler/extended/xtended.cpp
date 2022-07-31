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

#include "xtended.hh"
#include "floats.hh"
#include "code_container.hh"

ValueInst* xtended::generateFun(CodeContainer* container,
                                const string& fun_name,
                                const Values& args,
                                ::Type result,
                                ConstTypes types)
{
    Typed::VarType rtype = convert2FIRType(result->nature());
    vector<Typed::VarType> atypes;
    for (size_t i = 0; i < types.size(); i++) {
        atypes.push_back(convert2FIRType(types[i]->nature()));
    }
    return container->pushFunction(fun_name, rtype, atypes, args);
}
