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

#include "fir_to_fir.hh"

using namespace std;

bool sortArrayDeclarations(StatementInst* a, StatementInst* b)
{
    if (dynamic_cast<DeclareVarInst*>(a)) {
        DeclareVarInst* inst = dynamic_cast<DeclareVarInst*>(a);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        return (array_typed) ? (array_typed->fSize > 0) : false;
    } else if (dynamic_cast<DeclareVarInst*>(b)) {
        DeclareVarInst* inst = dynamic_cast<DeclareVarInst*>(a);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        return (array_typed) ? (array_typed->fSize > 0) : false;
    } else {
        return false;
    }
}

