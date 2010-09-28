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

#include <llvm/Instructions.h>
#include <llvm/Instruction.h>

using namespace llvm;
	
static bool noNtrl(const Node& n) { return false; }

BinOp* gBinOpTable[] = { 

	new BinOp("+","add_vec","add_scal", "add nsw", "fadd", Instruction::Add, Instruction::FAdd, &addNode, &isZero, &isZero, 6),
	new BinOp("-","sub_vec","sub_scal", "sub nsw", "fsub", Instruction::Sub, Instruction::FSub, &subNode, &noNtrl, &isZero, 6),
	new BinOp("*","mul_vec","mul_scal", "mul nsw", "fmul", Instruction::Mul, Instruction::FMul, &mulNode, &isOne, &isOne, 7),
	new BinOp("/","div_vec","div_scal", "sdiv", "fdiv", Instruction::SDiv, Instruction::FDiv, &divNode, &noNtrl, &isOne, 8),
	new BinOp("%","mod_vec","mod_scal", "srem", "frem", Instruction::SRem, Instruction::FRem, &remNode, &noNtrl, &noNtrl, 8),

	new BinOp("<<","shift_left_vec","shift_left_scal", "","", Instruction::Shl, Instruction::Shl, &lshNode, &noNtrl, &isZero, 7),
	new BinOp(">>","shift_right_vec","shift_right_scal","","", Instruction::LShr, Instruction::LShr, &rshNode, &noNtrl, &isZero, 7),

	new BinOp(">","gt_vec","gt_scal", "icmp ugt", "fcmp ugt", ICmpInst::ICMP_UGT, FCmpInst::FCMP_OGT, &gtNode, &noNtrl, &noNtrl, 5),
	new BinOp("<","lt_vec","lt_scal", "icmp ult", "fcmp ult", ICmpInst::ICMP_ULT, FCmpInst::FCMP_OLT, &ltNode, &noNtrl, &noNtrl, 5),
	new BinOp(">=","ge_vec","ge_scal", "icmp uge", "fcmp uge", ICmpInst::ICMP_UGE, FCmpInst::FCMP_OGE, &geNode, &noNtrl, &noNtrl, 5),
	new BinOp("<=","le_vec","le_scal", "icmp ule", "fcmp ule", ICmpInst::ICMP_ULE, FCmpInst::FCMP_OLE, &leNode, &noNtrl, &noNtrl, 5),
	new BinOp("==","eq_vec","eq_scal", "icmp eq", "fcmp eq", ICmpInst::ICMP_EQ, FCmpInst::FCMP_OEQ, &eqNode, &noNtrl, &noNtrl, 5),
	new BinOp("!=","neq_vec","neq_scal", "icmp ne", "fcmp ne", ICmpInst::ICMP_NE, FCmpInst::FCMP_ONE, &neNode, &noNtrl, &noNtrl, 5),

	new BinOp("&","and_vec","and_scal", "and", "and", Instruction::And, Instruction::And, &andNode, &isMinusOne, &isMinusOne, 7),
	new BinOp("|","or_vec","or_scal", "or", "or", Instruction::Or, Instruction::Or, &orNode, &isZero, &isZero, 6),
	new BinOp("^","xor_vec","xor_scal", "xor", "xor", Instruction::Xor, Instruction::Xor, &xorNode, &noNtrl, &noNtrl, 7)
};
/*
    switch (CE->getPredicate()) {
          case ICmpInst::ICMP_EQ:  Out << "EQ"; break;
          case ICmpInst::ICMP_NE:  Out << "NE"; break;
          case ICmpInst::ICMP_SLT: Out << "SLT"; break;
          case ICmpInst::ICMP_ULT: Out << "ULT"; break;
          case ICmpInst::ICMP_SGT: Out << "SGT"; break;
          case ICmpInst::ICMP_UGT: Out << "UGT"; break;
          case ICmpInst::ICMP_SLE: Out << "SLE"; break;
          case ICmpInst::ICMP_ULE: Out << "ULE"; break;
          case ICmpInst::ICMP_SGE: Out << "SGE"; break;
          case ICmpInst::ICMP_UGE: Out << "UGE"; break;
          default: error("Invalid ICmp Predicate");
          }
          break;
        case Instruction::FCmp:
          Out << "getFCmp(FCmpInst::FCMP_";
          switch (CE->getPredicate()) {
          case FCmpInst::FCMP_FALSE: Out << "FALSE"; break;
          case FCmpInst::FCMP_ORD:   Out << "ORD"; break;
          case FCmpInst::FCMP_UNO:   Out << "UNO"; break;
          case FCmpInst::FCMP_OEQ:   Out << "OEQ"; break;
          case FCmpInst::FCMP_UEQ:   Out << "UEQ"; break;
          case FCmpInst::FCMP_ONE:   Out << "ONE"; break;
          case FCmpInst::FCMP_UNE:   Out << "UNE"; break;
          case FCmpInst::FCMP_OLT:   Out << "OLT"; break;
          case FCmpInst::FCMP_ULT:   Out << "ULT"; break;
          case FCmpInst::FCMP_OGT:   Out << "OGT"; break;
          case FCmpInst::FCMP_UGT:   Out << "UGT"; break;
          case FCmpInst::FCMP_OLE:   Out << "OLE"; break;
          case FCmpInst::FCMP_ULE:   Out << "ULE"; break;
          case FCmpInst::FCMP_OGE:   Out << "OGE"; break;
          case FCmpInst::FCMP_UGE:   Out << "UGE"; break;
          case FCmpInst::FCMP_TRUE:  Out << "TRUE"; break;
*/

BinOp* gBinOpLateqTable[] = { 

	new BinOp("+","add_vec","add_scal", "add nsw", "fadd", 0, 0, &addNode, &isZero, &isZero, 6),
	new BinOp("-","sub_vec","sub_scal", "sub nsw", "fsub", 0, 0, &subNode, &noNtrl, &isZero, 6),
	new BinOp("*","mul_vec","mul_scal", "mul nsw", "fmul", 0, 0, &mulNode, &isOne, &isOne, 7), // \DeclareMathSymbol{*}{\mathbin}{symbols}{"01}
	new BinOp("/","div_vec","div_scal", "div", "fdiv", 0, 0, &divNode, &noNtrl, &isOne, 9), // \frac{}{} used in generateBinOp
	new BinOp("\\bmod","mod_vec","mod_scal", "srem", "frem", 0, 0, &remNode, &noNtrl, &noNtrl, 8),
	
	new BinOp("\\hiderel{\\ll}","shift_left_vec","shift_left_scal","","", 0, 0, &lshNode, &noNtrl, &isZero, 7),
	new BinOp("\\hiderel{\\gg}","shift_right_vec","shift_right_scal","","", 0, 0, &rshNode, &noNtrl, &isZero, 7),
	
	new BinOp("\\hiderel{>}","gt_vec","gt_scal", "icmp ugt", "fcmp ugt", 0, 0, &gtNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{<}","lt_vec","lt_scal", "icmp ult", "fcmp ult", 0, 0, &ltNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{\\geq}","ge_vec","ge_scal", "icmp uge", "fcmp uge", 0, 0, &geNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{\\leq}","le_vec","le_scal", "icmp ule", "fcmp ule", 0, 0, &leNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{\\equiv}","eq_vec","eq_scal", "icmp eq", "fcmp eq", 0, 0, &eqNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{\\neq}","neq_vec","neq_scal", "icmp ne", "fcmp ne", 0, 0, &neNode, &noNtrl, &noNtrl, 5),
	
	new BinOp("\\wedge","and_vec","and_scal", "and", "and", 0, 0, &andNode, &isMinusOne, &isMinusOne, 7),
	new BinOp("\\vee","or_vec","or_scal","or", "or", 0, 0, &orNode, &isZero, &isZero, 6),
	new BinOp("\\veebar","xor_vec","xor_scal", "xor", "xor", 0, 0, &xorNode, &noNtrl, &noNtrl, 7)
};
