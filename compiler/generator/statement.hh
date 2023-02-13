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

#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>

// Implements a code statement with an optional condition

class Statement {
   private:
    const bool fHasCondition;
    const std::string fCondition;
    const std::string fCode;

   public:
    Statement(const std::string& condition, const std::string& code)
    : fHasCondition(true), fCondition(condition), fCode(code) {}

    bool  hasCondition() { return fHasCondition; }
    bool  hasCondition(const std::string& cond) { return (fCondition == cond); }
    const std::string& condition() { return fCondition; }
    const std::string& code() { return fCode; }
};

#endif  // STATEMENT_H
