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
#include <algorithm>

using namespace std;

/*
 Sort arrays by size
*/

bool sortArrayDeclarations(StatementInst* a, StatementInst* b)
{
    DeclareVarInst* inst1 = dynamic_cast<DeclareVarInst*>(a);
    DeclareVarInst* inst2 = dynamic_cast<DeclareVarInst*>(b);
      
    if (inst1) {
        ArrayTyped* array_typed1 = dynamic_cast<ArrayTyped*>(inst1->fType);
        if (array_typed1) {
            if (inst2) {
                ArrayTyped* array_typed2 = dynamic_cast<ArrayTyped*>(inst2->fType);
                if (array_typed2) {
                    return (array_typed1->fSize == array_typed2->fSize) 
                            ? (intptr_t)array_typed1 > (intptr_t)array_typed1
                            : array_typed1->fSize > array_typed2->fSize;
                } 
            }
            return true;
        } else {
            return false;
        }
    } else if (inst2) {
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst2->fType);
        return (array_typed) ? (array_typed->fSize > 0) : false;
    } else {
        return false;
    }
}

/*
 Sort arrays by type : integer is moved first
 */

bool sortTypeDeclarations(StatementInst* a, StatementInst* b)
{
    DeclareVarInst* inst1 = dynamic_cast<DeclareVarInst*>(a);
    DeclareVarInst* inst2 = dynamic_cast<DeclareVarInst*>(b);
    
    if (inst1 && inst2) {
        return (inst1->fType->getType() == Typed::kInt32) || (inst1->fType->getType() == Typed::kInt32_ptr);
    } else {
        return false;
    }
}

