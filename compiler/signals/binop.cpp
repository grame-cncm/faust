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
 
 
 
#include "binop.hh"
	
static bool noNtrl(const Node& n) { return false; }

BinOp* gBinOpTable[] = { 

	new BinOp("+","add_vec","add_scal", &addNode, &isZero, &isZero),
	new BinOp("-","sub_vec","sub_scal", &subNode, &noNtrl, &isZero),
	new BinOp("*","mul_vec","mul_scal", &mulNode, &isOne, &isOne),
	new BinOp("/","div_vec","div_scal", &divNode, &noNtrl, &isOne),
	new BinOp("%","mod_vec","mod_scal", &remNode, &noNtrl, &noNtrl),

	new BinOp("<<","shift_left_vec","shift_left_scal", &lshNode, &noNtrl, &isZero),
	new BinOp(">>","shift_right_vec","shift_right_scal", &rshNode, &noNtrl, &isZero),

	new BinOp(">","gt_vec","gt_scal", &gtNode, &noNtrl, &noNtrl),
	new BinOp("<","lt_vec","lt_scal", &ltNode, &noNtrl, &noNtrl),
	new BinOp(">=","ge_vec","ge_scal", &geNode, &noNtrl, &noNtrl),
	new BinOp("<=","le_vec","le_scal", &leNode, &noNtrl, &noNtrl),
	new BinOp("==","eq_vec","eq_scal", &eqNode, &noNtrl, &noNtrl),
	new BinOp("!=","neq_vec","neq_scal", &neNode, &noNtrl, &noNtrl),

	new BinOp("&","and_vec","and_scal", &andNode, &isMinusOne, &isMinusOne),
	new BinOp("|","or_vec","or_scal", &orNode, &isZero, &isZero),
	new BinOp("^","xor_vec","xor_scal", &xorNode, &noNtrl, &noNtrl)
};

