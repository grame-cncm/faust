/************************************************************************
 ************************************************************************
 FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include <iostream>
#include <sstream>
#include <string>

// implements a code statement with an optional condition

/**
 * @brief A code statement, regular or if-then-else
 *
 */
class Statement {
   private:
    const bool        fHasCondition;
    const std::string fCondition;
    const std::string fThenCode;
    const std::string fElseCode;

   public:
    Statement(const std::string& condition, const std::string& thencode, const std::string& elsecode)
        : fHasCondition(true), fCondition(condition), fThenCode(thencode), fElseCode(elsecode)
    {
    }
    Statement(const std::string& thencode) : fHasCondition(false), fCondition(""), fThenCode(thencode), fElseCode("") {}

    bool               hasCondition() const { return fHasCondition; }
    bool               hasCondition(const std::string& cond) const { return (fCondition == cond); }
    const std::string& condition() const { return fCondition; }
    const std::string& thenCode() const { return fThenCode; }
    const std::string& elseCode() const { return fElseCode; }

    friend std::ostream& operator<<(std::ostream& out, const Statement& stmt)
    {
        if (stmt.hasCondition()) {
            if (stmt.elseCode().size() > 0) {
                return out << "if (" << stmt.condition() << ") {" << stmt.thenCode() << "} else {" << stmt.elseCode()
                           << "}";
            } else {
                return out << "if (" << stmt.condition() << ") {" << stmt.thenCode() << "}";
            }
        } else {
            return out << stmt.thenCode();
        }
    }
};

#endif  // STATEMENT_H
