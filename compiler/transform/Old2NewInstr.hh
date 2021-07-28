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

#pragma once

#include <cstdlib>
#include "Instr.hh"
#include "property.hh"
#include "signalVisitor.hh"
#include "sigtyperules.hh"
#include "tree.hh"

//-------------------------Old2NewInstr-------------------------------
// Converts old tre-based instructions into new nlpl instructions
//----------------------------------------------------------------------

class Old2NewInstr : public SignalVisitor {
    bool fVisitGen{false};

   public:
    Old2NewInstr() = default;

   protected:
    void visit(Tree t) override;
    void traceEnter(Tree t) override;
    void traceExit(Tree t) override;
};
