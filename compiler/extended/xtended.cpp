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

#include "xtended.hh"
#include "floats.hh"

void xtended::prepareTypeArgsResult(::Type result,
                                    const list<ValueInst*>& args,
                                    vector< ::Type> const& types,
                                    Typed::VarType& result_type,
                                    vector<Typed::VarType>& arg_types,
                                    list<ValueInst*>& casted_args)
{
    result_type = (result->nature() == kInt) ? Typed::kInt32 : itfloat();
    vector< ::Type>::const_iterator it1;
    list<ValueInst*>::const_iterator it2 = args.begin();
    
    for (it1 = types.begin(); it1 != types.end(); it1++, it2++) {
        casted_args.push_back(promote2real((*it1)->nature(), (*it2)));
        // Force type to float/double
        arg_types.push_back(itfloat());
    }
}

