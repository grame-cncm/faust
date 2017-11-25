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

#ifndef STATEMENT_H
#define STATEMENT_H

// implements a code statement with an optional condition

namespace std{}
using namespace std;

#include <string>

class Statement
{
    
    private:
    
        const bool fHasCondition;
        const string fCondition;
        const string fCode;
        
    public:
        
        Statement(const string& condition, const string& code):fHasCondition(true), fCondition(condition), fCode(code)
        {}

        bool hasCondition() { return fHasCondition; }
        bool hasCondition(const string& cond) { return (fCondition == cond); }
        const string& condition() { return fCondition; }
        const string& code() { return fCode; }
    
};

#endif // STATEMENT_H
