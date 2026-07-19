/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

#ifndef _LINEN_INSTRUCTIONS_H
#define _LINEN_INSTRUCTIONS_H

#include "nnx_base_instructions.hh"

// In Linen every struct variable routes to state[""] (no params/state split);
// every other variable is a bare local.
inline void linenEmitNamedAddress(std::ostream* out, NamedAddress* named)
{
    if (named->isStruct() || named->isStaticStruct()) {
        *out << "state[\"" << named->fName << "\"]";
    } else {
        *out << named->fName;
    }
}

/**
 * Linen init fields visitor.
 * All struct variables (UI params and state) route to state[""].
 */
struct LinenInitFieldsVisitor : public NNXBaseInitFieldsVisitor {
    using NNXBaseInitFieldsVisitor::NNXBaseInitFieldsVisitor;

    void visit(NamedAddress* named) override { linenEmitNamedAddress(fOut, named); }
};

/**
 * Linen main instruction visitor.
 * All struct variables (UI params and state) route to state[""].
 */
class LinenInstVisitor : public NNXBaseInstVisitor {
   public:
    using NNXBaseInstVisitor::NNXBaseInstVisitor;

    void visit(NamedAddress* named) override { linenEmitNamedAddress(fOut, named); }
};

#endif
