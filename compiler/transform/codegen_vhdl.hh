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
#include <string>
#include "property.hh"
//#include "signalVisitor.hh"
#include "sigtyperules.hh"
#include "tree.hh"
//#include "treeTraversal.hh"


using namespace std;

string addr_to_str(Tree t);
string val_to_str(Tree t);

void arith_entity(string name, const char* op, string & str);
void delay_entity(string & str);
void faust_entity(string & str);
void empty_entity(string name, string & str);
void faust_process(string & str);
void box_component(string name, int input, string & str);
void delay_instantiate(Tree sig, Tree x, Tree y, string & str);
void proj_instantiate(Tree sig, Tree x, string & str);
void box_instantiate(string name, Tree sig, Tree x, Tree y, string & str);
void decl_sig_1(Tree x, string & str);
void decl_sig_2(Tree x, Tree y, string & str);
void input_affectation(Tree sig, string & str);
