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
#include "property.hh"
#include "signalVisitor.hh"
#include "sigtyperules.hh"
#include "tree.hh"
#include "treeTraversal.hh"
#include "codegen_vhdl.hh"
#include "xtended.hh"

//-------------------------Signal2VHDLVisitor-------------------------------
// A a signal visitor used to compile signals to vhdl code
//----------------------------------------------------------------------
using namespace std;

class Signal2VHDLVisitor : public TreeTraversal {
    bool fVisitGen;
    set<Tree> fVisited;           // avoid visiting a tree twice
    map<string, bool> fEntity;
    string input;
    string bloc_0;
    string bloc_1;
    string bloc_2;
    string bloc_3;
    string bloc_4;
    string bloc_5;

   public:
    Signal2VHDLVisitor() : TreeTraversal(), fVisitGen(false){};

    void self(Tree t);
    void sigToVHDL(Tree sig, ofstream& fout);

   protected:
    void visit(Tree sig) override;
};
