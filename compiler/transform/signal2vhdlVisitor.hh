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
//#include "codegen_vhdl.hh"
#include "xtended.hh"

//-------------------------Signal2VHDLVisitor-------------------------------
// A a signal visitor used to compile signals to vhdl code
//----------------------------------------------------------------------
using namespace std;

class Signal2VHDLVisitor : public TreeTraversal {
    bool fVisitGen;
    set<Tree> fVisited;           // avoid visiting a tree twice
    map<string, bool> fEntity;
    string finput;
    string fDeclEntity;
    string fFaustEntity;
    string fDeclSig;
    string fDeclCompnt;
    string fFaustProcess;
    string fMapCompnt;

   public:
    Signal2VHDLVisitor() : TreeTraversal(), fVisitGen(false){};

    void self(Tree t);
    void sigToVHDL(Tree sig, ofstream& fout);
    void treatment(string name, const char* op, Tree sig, Tree x, Tree y);

    string addr_to_str(Tree t);
    string val_to_str(Tree t);

    void entity_header(string & str);
    void generic_decl(string & str);
    void port_decl(int input, string & str);

    void entity_bin_op(string name, const char* op, string & str);  // arith + mod
    void entity_delay(string & str);  // delay
    void entity_bypass(string name, string & str);  // proj
    void entity_faust(string & str);  // faust

    void component_standard(string name, int input, string & str);  // arith + mod + proj
    void component_delay(string & str); // delay

    void faust_process(string & str);

    void inst_delay(Tree sig, Tree x, Tree y, string & str); // delay
    void inst_proj(Tree sig, Tree x, string & str); // proj -- passer sur le premier
    void inst_bin_op(string name, Tree sig, Tree x, Tree y, string & str); // arith + mod

    void decl_sig(Tree x, string & str);
    void input_affectation(Tree sig, string & str);

   protected:
    void visit(Tree sig) override;
};
