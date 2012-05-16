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

	new BinOp("+","add_vec","add_scal", &addNode, &isZero, &isZero, 6),
    new BinOp("-","sub_vec","sub_scal", &subNode, &noNtrl, &isZero, 7),
    new BinOp("*","mul_vec","mul_scal", &mulNode, &isOne, &isOne, 8),
    new BinOp("/","div_vec","div_scal", &divExtendedNode, &noNtrl, &isOne, 10),
    new BinOp("%","mod_vec","mod_scal", &remNode, &noNtrl, &noNtrl, 9),

    new BinOp("<<","shift_left_vec","shift_left_scal", &lshNode, &noNtrl, &isZero, 8),
    new BinOp(">>","shift_right_vec","shift_right_scal", &rshNode, &noNtrl, &isZero, 8),

	new BinOp(">","gt_vec","gt_scal", &gtNode, &noNtrl, &noNtrl, 5),
	new BinOp("<","lt_vec","lt_scal", &ltNode, &noNtrl, &noNtrl, 5),
	new BinOp(">=","ge_vec","ge_scal", &geNode, &noNtrl, &noNtrl, 5),
	new BinOp("<=","le_vec","le_scal", &leNode, &noNtrl, &noNtrl, 5),
	new BinOp("==","eq_vec","eq_scal", &eqNode, &noNtrl, &noNtrl, 5),
	new BinOp("!=","neq_vec","neq_scal", &neNode, &noNtrl, &noNtrl, 5),

    new BinOp("&","and_vec","and_scal", &andNode, &isMinusOne, &isMinusOne, 8),
    new BinOp("|","or_vec","or_scal", &orNode, &isZero, &isZero, 7),
    new BinOp("^","xor_vec","xor_scal", &xorNode, &noNtrl, &noNtrl, 8)
};


BinOp* gBinOpLateqTable[] = { 

	new BinOp("+","add_vec","add_scal", &addNode, &isZero, &isZero, 6),
    new BinOp("-","sub_vec","sub_scal", &subNode, &noNtrl, &isZero, 7),
    new BinOp("*","mul_vec","mul_scal", &mulNode, &isOne, &isOne, 8), // \DeclareMathSymbol{*}{\mathbin}{symbols}{"01}
    new BinOp("/","div_vec","div_scal", &divExtendedNode, &noNtrl, &isOne, 10), // \frac{}{} used in generateBinOp
    new BinOp("\\bmod","mod_vec","mod_scal", &remNode, &noNtrl, &noNtrl, 9),
	
    new BinOp("\\hiderel{\\ll}","shift_left_vec","shift_left_scal", &lshNode, &noNtrl, &isZero, 8),
    new BinOp("\\hiderel{\\gg}","shift_right_vec","shift_right_scal", &rshNode, &noNtrl, &isZero, 8),
	
	new BinOp("\\hiderel{>}","gt_vec","gt_scal", &gtNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{<}","lt_vec","lt_scal", &ltNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{\\geq}","ge_vec","ge_scal", &geNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{\\leq}","le_vec","le_scal", &leNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{\\equiv}","eq_vec","eq_scal", &eqNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{\\neq}","neq_vec","neq_scal", &neNode, &noNtrl, &noNtrl, 5),
	
    new BinOp("\\wedge","and_vec","and_scal", &andNode, &isMinusOne, &isMinusOne, 8),
    new BinOp("\\vee","or_vec","or_scal", &orNode, &isZero, &isZero, 7),
    new BinOp("\\veebar","xor_vec","xor_scal", &xorNode, &noNtrl, &noNtrl, 8)
};
