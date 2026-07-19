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

#ifndef _NNX_INSTRUCTIONS_H
#define _NNX_INSTRUCTIONS_H

#include "nnx_base_instructions.hh"

// Routes struct variables to params[""] (UI parameters) or state[""]; every
// other variable is a bare local. kStaticStruct are actually merged in the
// main DSP.
inline void nnxEmitNamedAddress(std::ostream* out, NamedAddress* named)
{
    if (named->isStruct() || named->isStaticStruct()) {
        const std::string& name      = named->fName;
        bool               isUIParam = (name.find("fButton") == 0) ||
                         (name.find("fCheckbox") == 0) ||
                         (name.find("fVslider") == 0) ||
                         (name.find("fHslider") == 0) ||
                         (name.find("fEntry") == 0) ||
                         (name.find("fVbargraph") == 0) ||
                         (name.find("fHbargraph") == 0);
        *out << (isUIParam ? "params[\"" : "state[\"") << name << "\"]";
    } else {
        *out << named->fName;
    }
}

/**
 * NNX init fields visitor.
 * Routes UI parameters to params[""], state variables to state[""].
 */
struct NNXInitFieldsVisitor : public NNXBaseInitFieldsVisitor {
    using NNXBaseInitFieldsVisitor::NNXBaseInitFieldsVisitor;

    void visit(NamedAddress* named) override { nnxEmitNamedAddress(fOut, named); }
};

/**
 * NNX main instruction visitor.
 * Routes UI parameters to params[""], state variables to state[""].
 */
class NNXInstVisitor : public NNXBaseInstVisitor {
   public:
    using NNXBaseInstVisitor::NNXBaseInstVisitor;

    void visit(NamedAddress* named) override { nnxEmitNamedAddress(fOut, named); }
};

#endif
