/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifdef WIN32
#pragma warning(disable : 4141 4146 4244 4267 4800 4291)
#endif

#include "binop.hh"
#include "compatibility.hh"
#include "signals.hh"

bool falsePredicate(Node const& a)
{
    return false;
}

static bool noNtrl(const Node& n)
{
    return falsePredicate(n);
}

#ifdef LLVM_BUILD
#include <llvm/IR/Instructions.h>

using namespace llvm;

/*
Implementing C operator priority: https://en.cppreference.com/w/c/language/operator_precedence
but coded in reverse order. 
*/

BinOp* gBinOpTable[] = {

    new BinOp("+", "add_vec", "add_scal", "add nsw", "fadd", Instruction::Add, Instruction::FAdd, "i32.add", "i64.add",
              "f32.add", "f64.add", WasmOp::I32Add, WasmOp::I64Add, WasmOp::F32Add, WasmOp::F64Add,
              FBCInstruction::kAddInt, FBCInstruction::kAddReal, 7, true, &addNode, &isZero, &isZero),
    new BinOp("-", "sub_vec", "sub_scal", "sub nsw", "fsub", Instruction::Sub, Instruction::FSub, "i32.sub", "i64.sub",
              "f32.sub", "f64.sub", WasmOp::I32Sub, WasmOp::I64Sub, WasmOp::F32Sub, WasmOp::F64Sub,
              FBCInstruction::kSubInt, FBCInstruction::kSubReal, 7, false, &subNode, &noNtrl, &isZero),
    
    new BinOp("*", "mul_vec", "mul_scal", "mul nsw", "fmul", Instruction::Mul, Instruction::FMul, "i32.mul", "i64.mul",
              "f32.mul", "f64.mul", WasmOp::I32Mul, WasmOp::I64Mul, WasmOp::F32Mul, WasmOp::F64Mul,
              FBCInstruction::kMultInt, FBCInstruction::kMultReal, 8, true, &mulNode, &isOne, &isOne, isZero, isZero),
    new BinOp("/", "div_vec", "div_scal", "sdiv", "fdiv", Instruction::SDiv, Instruction::FDiv, "i32.div_s",
              "i64.div_s", "f32.div", "f64.div", WasmOp::I32DivS, WasmOp::I64DivS, WasmOp::F32Div, WasmOp::F64Div,
              FBCInstruction::kDivInt, FBCInstruction::kDivReal, 8, false, &divExtendedNode, &noNtrl, &isOne),
    new BinOp("%", "mod_vec", "mod_scal", "srem", "frem", Instruction::SRem, Instruction::FRem, "i32.rem_s",
              "i64.rem_s", "dummy", "dummy", WasmOp::I32RemS, WasmOp::I64RemS, WasmOp::Dummy, WasmOp::Dummy,
              FBCInstruction::kRemInt, FBCInstruction::kRemReal, 8, false, &remNode, &noNtrl, &noNtrl),

    new BinOp("<<", "shift_left_vec", "shift_left_scal", "", "", Instruction::Shl, Instruction::Shl, "i32.shl",
              "i64.shl", "dummy", "dummy", WasmOp::I32Shl, WasmOp::I64Shl, WasmOp::Dummy, WasmOp::Dummy,
              FBCInstruction::kLshInt, FBCInstruction::kLshInt, 6, false, &lshNode, &noNtrl, &isZero),
    new BinOp(">>", "ashift_right_vec", "ashift_right_scal", "", "", Instruction::AShr, Instruction::AShr, "i32.shr_s",
              "i64.shr_s", "dummy", "dummy", WasmOp::I32ShrS, WasmOp::I64ShrS, WasmOp::Dummy, WasmOp::Dummy,
              FBCInstruction::kARshInt, FBCInstruction::kARshInt, 6, false, &arshNode, &noNtrl, &isZero),
    new BinOp(">>>", "lshift_right_vec", "lshift_right_scal", "", "", Instruction::LShr, Instruction::LShr, "i32.shr_u",
              "i64.shr_u", "dummy", "dummy", WasmOp::I32ShrU, WasmOp::I64ShrU, WasmOp::Dummy, WasmOp::Dummy,
              FBCInstruction::kLRshInt, FBCInstruction::kLRshInt, 6, false, &lrshNode, &noNtrl, &isZero),

    new BinOp(">", "gt_vec", "gt_scal", "icmp sgt", "fcmp sgt", ICmpInst::ICMP_SGT, FCmpInst::FCMP_OGT, "i32.gt_s",
              "i64.gt_s", "f32.gt", "f64.gt", WasmOp::I32GtS, WasmOp::I64GtS, WasmOp::F32Gt, WasmOp::F64Gt,
              FBCInstruction::kGTInt, FBCInstruction::kGTReal, 5, false, &gtNode, &noNtrl, &noNtrl),
    new BinOp("<", "lt_vec", "lt_scal", "icmp slt", "fcmp slt", ICmpInst::ICMP_SLT, FCmpInst::FCMP_OLT, "i32.lt_s",
              "i64.lt_s", "f32.lt", "f64.lt", WasmOp::I32LtS, WasmOp::I64LtS, WasmOp::F32Lt, WasmOp::F64Lt,
              FBCInstruction::kLTInt, FBCInstruction::kLTReal, 5, false,&ltNode, &noNtrl, &noNtrl),
    new BinOp(">=", "ge_vec", "ge_scal", "icmp sge", "fcmp sge", ICmpInst::ICMP_SGE, FCmpInst::FCMP_OGE, "i32.ge_s",
              "i64.ge_s", "f32.ge", "f64.ge", WasmOp::I32GeS, WasmOp::I64GeS, WasmOp::F32Ge, WasmOp::F64Ge,
              FBCInstruction::kGEInt, FBCInstruction::kGEReal, 5, false,&geNode, &noNtrl, &noNtrl),
    new BinOp("<=", "le_vec", "le_scal", "icmp sle", "fcmp sle", ICmpInst::ICMP_SLE, FCmpInst::FCMP_OLE, "i32.le_s",
              "i64.le_s", "f32.le", "f64.le", WasmOp::I32LeS, WasmOp::I64LeS, WasmOp::F32Le, WasmOp::F64Le,
              FBCInstruction::kLEInt, FBCInstruction::kLEReal, 5, false,&leNode, &noNtrl, &noNtrl),
    
    new BinOp("==", "eq_vec", "eq_scal", "icmp eq", "fcmp eq", ICmpInst::ICMP_EQ, FCmpInst::FCMP_OEQ, "i32.eq",
              "i64.eq", "f32.eq", "f64.eq", WasmOp::I32Eq, WasmOp::I64Eq, WasmOp::F32Eq, WasmOp::F64Eq,
              FBCInstruction::kEQInt, FBCInstruction::kEQReal, 4, false, &eqNode, &noNtrl, &noNtrl),
    new BinOp("!=", "neq_vec", "neq_scal", "icmp ne", "fcmp ne", ICmpInst::ICMP_NE, FCmpInst::FCMP_ONE, "i32.ne",
              "i64.ne", "f32.ne", "f64.ne", WasmOp::I32Ne, WasmOp::I64Ne, WasmOp::F32Ne, WasmOp::F64Ne,
              FBCInstruction::kNEInt, FBCInstruction::kNEReal, 4, false, &neNode, &noNtrl, &noNtrl),

    new BinOp("&", "and_vec", "and_scal", "and", "and", Instruction::And, Instruction::And, "i32.and", "i64.and",
              "dummy", "dummy", WasmOp::I32And, WasmOp::I64And, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kANDInt,
              FBCInstruction::kANDInt, 3, false, &andNode, &isMinusOne, &isMinusOne, isZero, isZero),
    new BinOp("|", "or_vec", "or_scal", "or", "or", Instruction::Or, Instruction::Or, "i32.or", "i64.or", "dummy",
              "dummy", WasmOp::I32Or, WasmOp::I64Or, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kORInt,
              FBCInstruction::kORInt, 1, false, &orNode, &isZero, &isZero, &isMinusOne, &isMinusOne),
    new BinOp("^", "xor_vec", "xor_scal", "xor", "xor", Instruction::Xor, Instruction::Xor, "i32.xor", "i64.xor",
              "dummy", "dummy", WasmOp::I32Xor, WasmOp::I64Xor, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kXORInt,
              FBCInstruction::kXORInt, 2, false, &xorNode, &noNtrl, &noNtrl)
};

#else

BinOp* gBinOpTable[] = {

    new BinOp("+", "add_vec", "add_scal", "add nsw", "fadd", 0, 0, "i32.add", "i64.add", "f32.add", "f64.add",
              WasmOp::I32Add, WasmOp::I64Add, WasmOp::F32Add, WasmOp::F64Add, FBCInstruction::kAddInt,
              FBCInstruction::kAddReal, 7, true, &addNode, &isZero, &isZero),
    new BinOp("-", "sub_vec", "sub_scal", "sub nsw", "fsub", 0, 0, "i32.sub", "i64.sub", "f32.sub", "f64.sub",
              WasmOp::I32Sub, WasmOp::I64Sub, WasmOp::F32Sub, WasmOp::F64Sub, FBCInstruction::kSubInt,
              FBCInstruction::kSubReal, 7, false, &subNode, &noNtrl, &isZero),
    
    new BinOp("*", "mul_vec", "mul_scal", "mul nsw", "fmul", 0, 0, "i32.mul", "i64.mul", "f32.mul", "f64.mul",
              WasmOp::I32Mul, WasmOp::I64Mul, WasmOp::F32Mul, WasmOp::F64Mul, FBCInstruction::kMultInt,
              FBCInstruction::kMultReal, 8, true, &mulNode, &isOne, &isOne, isZero, isZero),
    new BinOp("/", "div_vec", "div_scal", "sdiv", "fdiv", 0, 0, "i32.div_s", "i64.div_s", "f32.div", "f64.div",
              WasmOp::I32DivS, WasmOp::I64DivS, WasmOp::F32Div, WasmOp::F64Div, FBCInstruction::kDivInt,
              FBCInstruction::kDivReal, 8, false, &divExtendedNode, &noNtrl, &isOne),
    new BinOp("%", "mod_vec", "mod_scal", "srem", "frem", 0, 0, "i32.rem_s", "i64.rem_s", "dummy", "dummy",
              WasmOp::I32RemS, WasmOp::I64RemS, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kRemInt,
              FBCInstruction::kRemReal, 8, false, &remNode, &noNtrl, &noNtrl),

    new BinOp("<<", "shift_left_vec", "shift_left_scal", "", "", 0, 0, "i32.shl", "i64.shl", "dummy", "dummy",
              WasmOp::I32Shl, WasmOp::I64Shl, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kLshInt,
              FBCInstruction::kLshInt, 6, false, &lshNode, &noNtrl, &isZero),
    new BinOp(">>", "ashift_right_vec", "ashift_right_scal", "", "", 0, 0, "i32.shr_s", "i64.shr_s", "dummy", "dummy",
              WasmOp::I32ShrS, WasmOp::I64ShrS, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kARshInt,
              FBCInstruction::kARshInt, 6, false, &arshNode, &noNtrl, &isZero),
    new BinOp(">>>", "lshift_right_vec", "lshift_right_scal", "", "", 0, 0, "i32.shr_u", "i64.shr_u", "dummy", "dummy",
              WasmOp::I32ShrU, WasmOp::I64ShrU, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kLRshInt,
              FBCInstruction::kLRshInt, 6, false, &lrshNode, &noNtrl, &isZero),

    new BinOp(">", "gt_vec", "gt_scal", "icmp sgt", "fcmp sgt", 0, 0, "i32.gt_s", "i64.gt_s", "f32.gt", "f64.gt",
              WasmOp::I32GtS, WasmOp::I64GtS, WasmOp::F32Gt, WasmOp::F64Gt, FBCInstruction::kGTInt,
              FBCInstruction::kGTReal, 5, false, &gtNode, &noNtrl, &noNtrl),
    new BinOp("<", "lt_vec", "lt_scal", "icmp slt", "fcmp slt", 0, 0, "i32.lt_s", "i64.lt_s", "f32.lt", "f64.lt",
              WasmOp::I32LtS, WasmOp::I64LtS, WasmOp::F32Lt, WasmOp::F64Lt, FBCInstruction::kLTInt,
              FBCInstruction::kLTReal, 5, false, &ltNode, &noNtrl, &noNtrl),
    new BinOp(">=", "ge_vec", "ge_scal", "icmp sge", "fcmp sge", 0, 0, "i32.ge_s", "i64.ge_s", "f32.ge", "f64.ge",
              WasmOp::I32GeS, WasmOp::I64GeS, WasmOp::F32Ge, WasmOp::F64Ge, FBCInstruction::kGEInt,
              FBCInstruction::kGEReal, 5, false, &geNode, &noNtrl, &noNtrl),
    new BinOp("<=", "le_vec", "le_scal", "icmp sle", "fcmp sle", 0, 0, "i32.le_s", "i64.le_s", "f32.le", "f64.le",
              WasmOp::I32LeS, WasmOp::I64LeS, WasmOp::F32Le, WasmOp::F64Le, FBCInstruction::kLEInt,
              FBCInstruction::kLEReal, 5, false, &leNode, &noNtrl, &noNtrl),
    
    new BinOp("==", "eq_vec", "eq_scal", "icmp eq", "fcmp eq", 0, 0, "i32.eq", "i64.eq", "f32.eq", "f64.eq",
              WasmOp::I32Eq, WasmOp::I64Eq, WasmOp::F32Eq, WasmOp::F64Eq, FBCInstruction::kEQInt,
              FBCInstruction::kEQReal, 4, false,  &eqNode, &noNtrl, &noNtrl),
    new BinOp("!=", "neq_vec", "neq_scal", "icmp ne", "fcmp ne", 0, 0, "i32.ne", "i64.ne", "f32.ne", "f64.ne",
              WasmOp::I32Ne, WasmOp::I64Ne, WasmOp::F32Ne, WasmOp::F64Ne, FBCInstruction::kNEInt,
              FBCInstruction::kNEReal, 4, false, &neNode, &noNtrl, &noNtrl),

    new BinOp("&", "and_vec", "and_scal", "and", "and", 0, 0, "i32.and", "i64.and", "dummy", "dummy", WasmOp::I32And,
              WasmOp::I64And, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kANDInt, FBCInstruction::kANDInt, 3, false,
              &andNode, &isMinusOne, &isMinusOne, isZero, isZero),
    new BinOp("|", "or_vec", "or_scal", "or", "or", 0, 0, "i32.or", "i64.or", "dummy", "dummy", WasmOp::I32Or,
              WasmOp::I64Or, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kORInt, FBCInstruction::kORInt, 1, false,
              &orNode, &isZero, &isZero, &isMinusOne, &isMinusOne),
    new BinOp("^", "xor_vec", "xor_scal", "xor", "xor", 0, 0, "i32.xor", "i64.xor", "dummy", "dummy", WasmOp::I32Xor,
              WasmOp::I64Xor, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kXORInt, FBCInstruction::kXORInt, 2, false,
              &xorNode, &noNtrl, &noNtrl)
};

#endif

BinOp* gBinOpLateqTable[] = {

    new BinOp("+", "add_vec", "add_scal", "add nsw", "fadd", 0, 0, "i32.add", "i64.add", "f32.add", "f64.add",
              WasmOp::I32Add, WasmOp::I64Add, WasmOp::F32Add, WasmOp::F64Add, FBCInstruction::kAddInt,
              FBCInstruction::kAddReal, 7, true, &addNode, &isZero, &isZero),
    new BinOp("-", "sub_vec", "sub_scal", "sub nsw", "fsub", 0, 0, "i32.sub", "i64.sub", "f32.sub", "f64.sub",
              WasmOp::I32Sub, WasmOp::I64Sub, WasmOp::F32Sub, WasmOp::F64Sub, FBCInstruction::kSubInt,
              FBCInstruction::kSubReal, 7, false, &subNode, &noNtrl, &isZero),
    
    new BinOp("*", "mul_vec", "mul_scal", "mul nsw", "fmul", 0, 0, "i32.mul", "i64.mul", "f32.mul", "f64.mul",
              WasmOp::I32Mul, WasmOp::I64Mul, WasmOp::F32Mul, WasmOp::F64Mul, FBCInstruction::kMultInt,
              FBCInstruction::kMultReal, 8, true, &mulNode, &isOne, &isOne, isZero,
              isZero),  // \DeclareMathSymbol{*}{\mathbin}{symbols}{"01}
    new BinOp("/", "div_vec", "div_scal", "sdiv", "fdiv", 0, 0, "i32.div_s", "i64.div_s", "f32.div", "f64.div",
              WasmOp::I32DivS, WasmOp::I64DivS, WasmOp::F32Div, WasmOp::F64Div, FBCInstruction::kDivInt,
              FBCInstruction::kDivReal, 8, false, &divExtendedNode, &noNtrl, &isOne),  // \frac{}{} used in generateBinOp
    new BinOp("\\bmod", "mod_vec", "mod_scal", "srem", "frem", 0, 0, "i32.rem_s", "i64.rem_s", "dummy", "dummy",
              WasmOp::I32RemS, WasmOp::I64RemS, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kRemInt,
              FBCInstruction::kRemReal, 8, false, &remNode, &noNtrl, &noNtrl),
    
    new BinOp("\\hiderel{\\ll}", "shift_left_vec", "shift_left_scal", "", "", 0, 0, "i32.shl", "i64.shl", "dummy",
              "dummy", WasmOp::I32Shl, WasmOp::I64Shl, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kLshInt,
              FBCInstruction::kLshInt, 6, false, &lshNode, &noNtrl, &isZero),
    new BinOp("\\hiderel{\\gg}", "ashift_right_vec", "ashift_right_scal", "", "", 0, 0, "i32.shr_s", "i64.shr_s",
              "dummy", "dummy", WasmOp::I32ShrS, WasmOp::I64ShrS, WasmOp::Dummy, WasmOp::Dummy,
              FBCInstruction::kARshInt, FBCInstruction::kARshInt, 6, false, &arshNode, &noNtrl, &isZero),
    new BinOp("\\hiderel{\\gg}", "lshift_right_vec", "lshift_right_scal", "", "", 0, 0, "i32.shr_u", "i64.shr_u",
              "dummy", "dummy", WasmOp::I32ShrU, WasmOp::I64ShrU, WasmOp::Dummy, WasmOp::Dummy,
              FBCInstruction::kLRshInt, FBCInstruction::kLRshInt, 6, false, &lrshNode, &noNtrl, &isZero),
    
    new BinOp("\\hiderel{>}", "gt_vec", "gt_scal", "icmp sgt", "fcmp sgt", 0, 0, "i32.gt_s", "i64.gt_s", "f32.gt",
              "f64.gt", WasmOp::I32GtS, WasmOp::I64GtS, WasmOp::F32Gt, WasmOp::F64Gt, FBCInstruction::kGTInt,
              FBCInstruction::kGTReal, 5, false, &gtNode, &noNtrl, &noNtrl),
    new BinOp("\\hiderel{<}", "lt_vec", "lt_scal", "icmp slt", "fcmp slt", 0, 0, "i32.lt_s", "i64.lt_s", "f32.lt",
              "f64.lt", WasmOp::I32LtS, WasmOp::I64LtS, WasmOp::F32Lt, WasmOp::F64Lt, FBCInstruction::kLTInt,
              FBCInstruction::kLTReal, 5, false, &ltNode, &noNtrl, &noNtrl),
    new BinOp("\\hiderel{\\geq}", "ge_vec", "ge_scal", "icmp sge", "fcmp sge", 0, 0, "i32.ge_s", "i64.ge_s", "f32.ge",
              "f64.ge", WasmOp::I32GeS, WasmOp::I64GeS, WasmOp::F32Ge, WasmOp::F64Ge, FBCInstruction::kGEInt,
              FBCInstruction::kGEReal, 5, false, &geNode, &noNtrl, &noNtrl),
    new BinOp("\\hiderel{\\leq}", "le_vec", "le_scal", "icmp sle", "fcmp sle", 0, 0, "i32.le_s", "i64.le_s", "f32.le",
              "f64.le", WasmOp::I32LeS, WasmOp::I64LeS, WasmOp::F32Le, WasmOp::F64Le, FBCInstruction::kLEInt,
              FBCInstruction::kLEReal, 5, false, &leNode, &noNtrl, &noNtrl),
    
    new BinOp("\\hiderel{\\equiv}", "eq_vec", "eq_scal", "icmp eq", "fcmp eq", 0, 0, "i32.eq", "i64.eq", "f32.eq",
              "f64.eq", WasmOp::I32Eq, WasmOp::I64Eq, WasmOp::F32Eq, WasmOp::F64Eq, FBCInstruction::kEQInt,
              FBCInstruction::kEQReal, 4, false, &eqNode, &noNtrl, &noNtrl),
    new BinOp("\\hiderel{\\neq}", "neq_vec", "neq_scal", "icmp ne", "fcmp ne", 0, 0, "i32.ne", "i64.ne", "f32.ne",
              "f64.ne", WasmOp::I32Ne, WasmOp::I64Ne, WasmOp::F32Ne, WasmOp::F64Ne, FBCInstruction::kNEInt,
              FBCInstruction::kNEReal, 4, false, &neNode, &noNtrl, &noNtrl),
    
    new BinOp("\\wedge", "and_vec", "and_scal", "and", "and", 0, 0, "i32.and", "i64.and", "dummy", "dummy",
              WasmOp::I32And, WasmOp::I64And, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kANDInt,
              FBCInstruction::kANDInt, 3, false, &andNode, &isMinusOne, &isMinusOne, isZero, isZero),
    new BinOp("\\vee", "or_vec", "or_scal", "or", "or", 0, 0, "i32.or", "i64.or", "dummy", "dummy", WasmOp::I32Or,
              WasmOp::I64Or, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kORInt, FBCInstruction::kORInt, 3, false, &orNode,
              &isZero, &isZero, &isMinusOne, &isMinusOne),
    new BinOp("\\veebar", "xor_vec", "xor_scal", "xor", "xor", 0, 0, "i32.xor", "i64.xor", "dummy", "dummy",
              WasmOp::I32Xor, WasmOp::I64Xor, WasmOp::Dummy, WasmOp::Dummy, FBCInstruction::kXORInt,
              FBCInstruction::kXORInt, 2, false, &xorNode, &noNtrl, &noNtrl)
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

bool isShiftOpcode(int o)
{
    return (o >= kLsh && o <= kARsh);
}

const char* BinOp::getString(int op)
{
    static const char* table[] = { "kAdd", "kSub", "kMul", "kDiv", "kRem", "kLsh", "kARsh", "kLRsh", "kGT", "kLT", "kGE", "kLE", "kEQ", "kNE", "kAND", "kOR", "kXOR" };
    
    faustassert(op >= kAdd && op <= kXOR);
    return table[op];
}
