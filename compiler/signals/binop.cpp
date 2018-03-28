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
#include "signals.hh"
#include "compatibility.hh"

bool falsePredicate(Node const & a)
{
    return false;
}

static bool noNtrl(const Node& n) { return falsePredicate(n); }

#ifdef WIN32
#pragma warning (disable: 4291)
#endif

#ifdef LLVM_BUILD

#if defined(LLVM_35) || defined(LLVM_38)
#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#include <llvm/IR/Instructions.h>

using namespace llvm;

BinOp* gBinOpTable[] = {

	new BinOp("+","add_vec","add_scal", "add nsw", "fadd", Instruction::Add, Instruction::FAdd,
        "i32.add", "i64.add", "f32.add", "f64.add",
        WasmOp::I32Add, WasmOp::I64Add, WasmOp::F32Add, WasmOp::F64Add,
        FIRInstruction::kAddInt, FIRInstruction::kAddReal, &addNode, &isZero, &isZero, 6),
	new BinOp("-","sub_vec","sub_scal", "sub nsw", "fsub", Instruction::Sub, Instruction::FSub,
        "i32.sub", "i64.sub", "f32.sub", "f64.sub",
        WasmOp::I32Sub, WasmOp::I64Sub, WasmOp::F32Sub, WasmOp::F64Sub,
        FIRInstruction::kSubInt, FIRInstruction::kSubReal, &subNode, &noNtrl, &isZero, 7),
	new BinOp("*","mul_vec","mul_scal", "mul nsw", "fmul", Instruction::Mul, Instruction::FMul,
        "i32.mul", "i64.mul", "f32.mul", "f64.mul",
        WasmOp::I32Mul, WasmOp::I64Mul, WasmOp::F32Mul, WasmOp::F64Mul,
        FIRInstruction::kMultInt, FIRInstruction::kMultReal, &mulNode, &isOne, &isOne, 8, isZero, isZero),
	new BinOp("/","div_vec","div_scal", "sdiv", "fdiv", Instruction::SDiv, Instruction::FDiv,
        "i32.div_s", "i64.div_s", "f32.div", "f64.div",
        WasmOp::I32DivS, WasmOp::I64DivS, WasmOp::F32Div, WasmOp::F64Div,
        FIRInstruction::kDivInt, FIRInstruction::kDivReal, &divExtendedNode, &noNtrl, &isOne, 10),
	new BinOp("%","mod_vec","mod_scal", "srem", "frem", Instruction::SRem, Instruction::FRem,
        "i32.rem", "i64.rem", "dummy", "dummy",
        WasmOp::I32RemS, WasmOp::I64RemS, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kRemInt, FIRInstruction::kRemReal, &remNode, &noNtrl, &noNtrl, 9),

	new BinOp("<<","shift_left_vec","shift_left_scal", "","", Instruction::Shl, Instruction::Shl,
        "i32.shl", "i64.shl", "dummy", "dummy",
        WasmOp::I32Shl, WasmOp::I64Shl, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kLshInt, FIRInstruction::kLshInt, &lshNode, &noNtrl, &isZero, 8),
	new BinOp(">>","shift_right_vec","shift_right_scal","","", Instruction::LShr, Instruction::LShr,
        "i32.shr_s", "i64.shr_s", "dummy", "dummy",
        WasmOp::I32ShrS, WasmOp::I64ShrS, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kRshInt, FIRInstruction::kRshInt, &rshNode, &noNtrl, &isZero, 8),

	new BinOp(">","gt_vec","gt_scal", "icmp sgt", "fcmp sgt", ICmpInst::ICMP_SGT, FCmpInst::FCMP_OGT,
        "i32.gt_s", "i64.gt_s", "f32.gt", "f64.gt",
        WasmOp::I32GtS, WasmOp::I64GtS, WasmOp::F32Gt, WasmOp::F64Gt,
        FIRInstruction::kGTInt, FIRInstruction::kGTReal, &gtNode, &noNtrl, &noNtrl, 5),
	new BinOp("<","lt_vec","lt_scal", "icmp slt", "fcmp slt", ICmpInst::ICMP_SLT, FCmpInst::FCMP_OLT,
        "i32.lt_s", "i64.lt_s", "f32.lt", "f64.lt",
        WasmOp::I32LtS, WasmOp::I64LtS, WasmOp::F32Lt, WasmOp::F64Lt,
        FIRInstruction::kLTInt, FIRInstruction::kLTReal, &ltNode, &noNtrl, &noNtrl, 5),
	new BinOp(">=","ge_vec","ge_scal", "icmp sge", "fcmp sge", ICmpInst::ICMP_SGE, FCmpInst::FCMP_OGE,
        "i32.ge_s", "i64.ge_s", "f32.ge", "f64.ge",
        WasmOp::I32GeS, WasmOp::I64GeS, WasmOp::F32Ge, WasmOp::F64Ge,
        FIRInstruction::kGEInt, FIRInstruction::kGEReal, &geNode, &noNtrl, &noNtrl, 5),
	new BinOp("<=","le_vec","le_scal", "icmp sle", "fcmp sle", ICmpInst::ICMP_SLE, FCmpInst::FCMP_OLE,
        "i32.le_s", "i64.le_s", "f32.le", "f64.le",
        WasmOp::I32LeS, WasmOp::I64LeS, WasmOp::F32Le, WasmOp::F64Le,
        FIRInstruction::kLEInt, FIRInstruction::kLEReal, &leNode, &noNtrl, &noNtrl, 5),
	new BinOp("==","eq_vec","eq_scal", "icmp eq", "fcmp eq", ICmpInst::ICMP_EQ, FCmpInst::FCMP_OEQ,
        "i32.eq", "i64.eq", "f32.eq", "f64.eq",
        WasmOp::I32Eq, WasmOp::I64Eq, WasmOp::F32Eq, WasmOp::F64Eq,
        FIRInstruction::kEQInt, FIRInstruction::kEQReal, &eqNode, &noNtrl, &noNtrl, 5),
	new BinOp("!=","neq_vec","neq_scal", "icmp ne", "fcmp ne", ICmpInst::ICMP_NE, FCmpInst::FCMP_ONE,
        "i32.ne", "i64.ne", "f32.ne", "f64.ne",
        WasmOp::I32Ne, WasmOp::I64Ne, WasmOp::F32Ne, WasmOp::F64Ne,
        FIRInstruction::kNEInt, FIRInstruction::kNEReal, &neNode, &noNtrl, &noNtrl, 5),

	new BinOp("&","and_vec","and_scal", "and", "and", Instruction::And, Instruction::And,
        "i32.and", "i64.and", "dummy", "dummy",
        WasmOp::I32And, WasmOp::I64And, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kANDInt, FIRInstruction::kANDInt, &andNode, &isMinusOne, &isMinusOne, 8, isZero, isZero),
	new BinOp("|","or_vec","or_scal", "or", "or", Instruction::Or, Instruction::Or,
        "i32.or", "i64.or", "dummy", "dummy",
        WasmOp::I32Or, WasmOp::I64Or, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kORInt, FIRInstruction::kORInt, &orNode, &isZero, &isZero, 7),
	new BinOp("^","xor_vec","xor_scal", "xor", "xor", Instruction::Xor, Instruction::Xor,
        "i32.xor", "i64.xor", "dummy", "dummy",
        WasmOp::I32Xor, WasmOp::I64Xor, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kXORInt, FIRInstruction::kXORInt, &xorNode, &noNtrl, &noNtrl, 8)
};

#else

BinOp* gBinOpTable[] = {
    
	new BinOp("+","add_vec","add_scal", "add nsw", "fadd", 0, 0,
        "i32.add", "i64.add", "f32.add", "f64.add",
        WasmOp::I32Add, WasmOp::I64Add, WasmOp::F32Add, WasmOp::F64Add,
        FIRInstruction::kAddInt, FIRInstruction::kAddReal, &addNode, &isZero, &isZero, 6),
	new BinOp("-","sub_vec","sub_scal", "sub nsw", "fsub", 0, 0,
        "i32.sub", "i64.sub", "f32.sub", "f64.sub",
        WasmOp::I32Sub, WasmOp::I64Sub, WasmOp::F32Sub, WasmOp::F64Sub,
        FIRInstruction::kSubInt, FIRInstruction::kSubReal, &subNode, &noNtrl, &isZero, 7),
	new BinOp("*","mul_vec","mul_scal", "mul nsw", "fmul", 0, 0,
        "i32.mul", "i64.mul", "f32.mul", "f64.mul",
        WasmOp::I32Mul, WasmOp::I64Mul, WasmOp::F32Mul, WasmOp::F64Mul,
        FIRInstruction::kMultInt, FIRInstruction::kMultReal, &mulNode, &isOne, &isOne, 8, isZero, isZero),
	new BinOp("/","div_vec","div_scal", "sdiv", "fdiv", 0, 0,
        "i32.div_s", "i64.div_s", "f32.div", "f64.div",
        WasmOp::I32DivS, WasmOp::I64DivS, WasmOp::F32Div, WasmOp::F64Div,
        FIRInstruction::kDivInt, FIRInstruction::kDivReal, &divExtendedNode, &noNtrl, &isOne, 10),
	new BinOp("%","mod_vec","mod_scal", "srem", "frem", 0, 0,
        "i32.rem", "i64.rem", "dummy", "dummy",
        WasmOp::I32RemS, WasmOp::I64RemS, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kRemInt, FIRInstruction::kRemReal, &remNode, &noNtrl, &noNtrl, 9),
    
	new BinOp("<<","shift_left_vec","shift_left_scal", "","", 0, 0,
        "i32.shl", "i64.shl", "dummy", "dummy",
        WasmOp::I32Shl, WasmOp::I64Shl, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kLshInt, FIRInstruction::kLshInt, &lshNode, &noNtrl, &isZero, 8),
	new BinOp(">>","shift_right_vec","shift_right_scal","","", 0, 0,
        "i32.shr_s", "i64.shr_s", "dummy", "dummy",
        WasmOp::I32ShrS, WasmOp::I64ShrS, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kRshInt, FIRInstruction::kRshInt, &rshNode, &noNtrl, &isZero, 8),
    
	new BinOp(">","gt_vec","gt_scal", "icmp sgt", "fcmp sgt", 0, 0,
        "i32.gt_s", "i64.gt_s", "f32.gt", "f64.gt",
        WasmOp::I32GtS, WasmOp::I64GtS, WasmOp::F32Gt, WasmOp::F64Gt,
        FIRInstruction::kGTInt, FIRInstruction::kGTReal, &gtNode, &noNtrl, &noNtrl, 5),
	new BinOp("<","lt_vec","lt_scal", "icmp slt", "fcmp slt", 0, 0,
        "i32.lt_s", "i64.lt_s", "f32.lt", "f64.lt",
        WasmOp::I32LtS, WasmOp::I64LtS, WasmOp::F32Lt, WasmOp::F64Lt,
        FIRInstruction::kLTInt, FIRInstruction::kLTReal, &ltNode, &noNtrl, &noNtrl, 5),
	new BinOp(">=","ge_vec","ge_scal", "icmp sge", "fcmp sge", 0, 0,
        "i32.ge_s", "i64.ge_s", "f32.ge", "f64.ge",
        WasmOp::I32GeS, WasmOp::I64GeS, WasmOp::F32Ge, WasmOp::F64Ge,
        FIRInstruction::kGEInt, FIRInstruction::kGEReal, &geNode, &noNtrl, &noNtrl, 5),
	new BinOp("<=","le_vec","le_scal", "icmp sle", "fcmp sle", 0, 0,
        "i32.le_s", "i64.le_s", "f32.le", "f64.le",
        WasmOp::I32LeS, WasmOp::I64LeS, WasmOp::F32Le, WasmOp::F64Le,
        FIRInstruction::kLEInt, FIRInstruction::kLEReal, &leNode, &noNtrl, &noNtrl, 5),
	new BinOp("==","eq_vec","eq_scal", "icmp eq", "fcmp eq", 0, 0,
        "i32.eq", "i64.eq", "f32.eq", "f64.eq",
        WasmOp::I32Eq, WasmOp::I64Eq, WasmOp::F32Eq, WasmOp::F64Eq,
        FIRInstruction::kEQInt, FIRInstruction::kEQReal, &eqNode, &noNtrl, &noNtrl, 5),
	new BinOp("!=","neq_vec","neq_scal", "icmp ne", "fcmp ne", 0, 0,
        "i32.ne", "i64.ne", "f32.ne", "f64.ne",
        WasmOp::I32Ne, WasmOp::I64Ne, WasmOp::F32Ne, WasmOp::F64Ne,
        FIRInstruction::kNEInt, FIRInstruction::kNEReal, &neNode, &noNtrl, &noNtrl, 5),
    
	new BinOp("&","and_vec","and_scal", "and", "and", 0, 0,
        "i32.and", "i64.and", "dummy", "dummy",
        WasmOp::I32And, WasmOp::I64And, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kANDInt, FIRInstruction::kANDInt, &andNode, &isMinusOne, &isMinusOne, 8, isZero, isZero),
	new BinOp("|","or_vec","or_scal", "or", "or", 0, 0,
        "i32.or", "i64.or", "dummy", "dummy",
        WasmOp::I32Or, WasmOp::I64Or, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kORInt, FIRInstruction::kORInt, &orNode, &isZero, &isZero, 7),
	new BinOp("^","xor_vec","xor_scal", "xor", "xor", 0, 0,
        "i32.xor", "i64.xor", "dummy", "dummy",
        WasmOp::I32Xor, WasmOp::I64Xor, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kXORInt, FIRInstruction::kXORInt, &xorNode, &noNtrl, &noNtrl, 8)
};

#endif

BinOp* gBinOpLateqTable[] = {

	new BinOp("+","add_vec","add_scal", "add nsw", "fadd", 0, 0,
        "i32.add", "i64.add", "f32.add", "f64.add",
        WasmOp::I32Add, WasmOp::I64Add, WasmOp::F32Add, WasmOp::F64Add,
        FIRInstruction::kAddInt, FIRInstruction::kAddReal, &addNode, &isZero, &isZero, 6),
	new BinOp("-","sub_vec","sub_scal", "sub nsw", "fsub", 0, 0,
        "i32.sub", "i64.sub", "f32.sub", "f64.sub",
        WasmOp::I32Sub, WasmOp::I64Sub, WasmOp::F32Sub, WasmOp::F64Sub,
        FIRInstruction::kSubInt, FIRInstruction::kSubReal, &subNode, &noNtrl, &isZero, 7),
	new BinOp("*","mul_vec","mul_scal", "mul nsw", "fmul", 0, 0,
        "i32.mul", "i64.mul", "f32.mul", "f64.mul",
        WasmOp::I32Mul, WasmOp::I64Mul, WasmOp::F32Mul, WasmOp::F64Mul,
        FIRInstruction::kMultInt, FIRInstruction::kMultReal, &mulNode, &isOne, &isOne, 8, isZero, isZero), // \DeclareMathSymbol{*}{\mathbin}{symbols}{"01}
	new BinOp("/","div_vec","div_scal", "sdiv", "fdiv", 0, 0,
        "i32.div_s", "i64.div_s", "f32.div", "f64.div",
        WasmOp::I32DivS, WasmOp::I64DivS, WasmOp::F32Div, WasmOp::F64Div,
        FIRInstruction::kDivInt, FIRInstruction::kDivReal, &divExtendedNode, &noNtrl, &isOne, 10), // \frac{}{} used in generateBinOp
	new BinOp("\\bmod","mod_vec","mod_scal", "srem", "frem", 0, 0,
        "i32.rem", "i64.rem", "dummy", "dummy",
        WasmOp::I32RemS, WasmOp::I64RemS, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kRemInt, FIRInstruction::kRemReal, &remNode, &noNtrl, &noNtrl, 9),

	new BinOp("\\hiderel{\\ll}","shift_left_vec","shift_left_scal","","", 0, 0,
        "i32.shl", "i64.shl", "dummy", "dummy",
        WasmOp::I32Shl, WasmOp::I64Shl, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kLshInt, FIRInstruction::kLshInt, &lshNode, &noNtrl, &isZero, 8),
	new BinOp("\\hiderel{\\gg}","shift_right_vec","shift_right_scal","","", 0, 0,
        "i32.shr_s", "i64.shr_s", "dummy", "dummy",
        WasmOp::I32ShrS, WasmOp::I64ShrS, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kRshInt, FIRInstruction::kRshInt, &rshNode, &noNtrl, &isZero, 8),

	new BinOp("\\hiderel{>}","gt_vec","gt_scal", "icmp sgt", "fcmp sgt", 0, 0,
        "i32.gt_s", "i64.gt_s", "f32.gt", "f64.gt",
        WasmOp::I32GtS, WasmOp::I64GtS, WasmOp::F32Gt, WasmOp::F64Gt,
        FIRInstruction::kGTInt, FIRInstruction::kGTReal, &gtNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{<}","lt_vec","lt_scal", "icmp slt", "fcmp slt", 0, 0,
        "i32.lt_s", "i64.lt_s", "f32.lt", "f64.lt",
        WasmOp::I32LtS, WasmOp::I64LtS, WasmOp::F32Lt, WasmOp::F64Lt,
        FIRInstruction::kLTInt, FIRInstruction::kLTReal, &ltNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{\\geq}","ge_vec","ge_scal", "icmp sge", "fcmp sge", 0, 0,
        "i32.ge_s", "i64.ge_s", "f32.ge", "f64.ge",
        WasmOp::I32GeS, WasmOp::I64GeS, WasmOp::F32Ge, WasmOp::F64Ge,
        FIRInstruction::kGEInt, FIRInstruction::kGEReal, &geNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{\\leq}","le_vec","le_scal", "icmp sle", "fcmp sle", 0, 0,
        "i32.le_s", "i64.le_s", "f32.le", "f64.le",
        WasmOp::I32LeS, WasmOp::I64LeS, WasmOp::F32Le, WasmOp::F64Le,
        FIRInstruction::kLEInt, FIRInstruction::kLEReal, &leNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{\\equiv}","eq_vec","eq_scal", "icmp eq", "fcmp eq", 0, 0,
        "i32.eq", "i64.eq", "f32.eq", "f64.eq",
        WasmOp::I32Eq, WasmOp::I64Eq, WasmOp::F32Eq, WasmOp::F64Eq,
        FIRInstruction::kEQInt, FIRInstruction::kEQReal, &eqNode, &noNtrl, &noNtrl, 5),
	new BinOp("\\hiderel{\\neq}","neq_vec","neq_scal", "icmp ne", "fcmp ne", 0, 0,
        "i32.ne", "i64.ne", "f32.ne", "f64.ne",
        WasmOp::I32Ne, WasmOp::I64Ne, WasmOp::F32Ne, WasmOp::F64Ne,
        FIRInstruction::kNEInt, FIRInstruction::kNEReal, &neNode, &noNtrl, &noNtrl, 5),

	new BinOp("\\wedge","and_vec","and_scal", "and", "and", 0, 0,
        "i32.and", "i64.and", "dummy", "dummy",
        WasmOp::I32And, WasmOp::I64And, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kANDInt, FIRInstruction::kANDInt, &andNode, &isMinusOne, &isMinusOne, 8, isZero, isZero),
	new BinOp("\\vee","or_vec","or_scal","or", "or", 0, 0,
        "i32.or", "i64.or", "dummy", "dummy",
        WasmOp::I32Or, WasmOp::I64Or, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kORInt, FIRInstruction::kORInt, &orNode, &isZero, &isZero, 7),
	new BinOp("\\veebar","xor_vec","xor_scal", "xor", "xor", 0, 0,
        "i32.xor", "i64.xor", "dummy", "dummy",
        WasmOp::I32Xor, WasmOp::I64Xor, WasmOp::Dummy, WasmOp::Dummy,
        FIRInstruction::kXORInt, FIRInstruction::kXORInt, &xorNode, &noNtrl, &noNtrl, 8)
};

bool isBoolOpcode(int o)
{
    return (o >= kGT && o <= kNE);
}

bool isCommutativeOpcode(int o)
{
    return ((o == kAdd) || (o == kMul) || (o == kEQ) || (o == kNE) || (o == kAND) || (o == kOR) || (o == kXOR));
}

bool isLogicalOpcode(int o)
{
    return (o >= kAND && o <= kXOR);
}
