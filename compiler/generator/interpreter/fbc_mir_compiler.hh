/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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

#ifndef _FBC_MIR_COMPILER_H
#define _FBC_MIR_COMPILER_H

#include <string>
#include <map>
#include <stdio.h>

#include "interpreter_bytecode.hh"
#include "fbc_executor.hh"

#ifdef __cplusplus
extern "C" {
#endif

//#include "mir.h"
//#include "mir-gen.h"

#include "/Documents/JIT-compilation/mir/mir.h"
#include "/Documents/JIT-compilation/mir/mir-gen.h"
    
#ifdef __cplusplus
}
#endif

#define typedReal(op1, op2) ((sizeof(T) == sizeof(float)) ? op1 : op2)

// FBC MIR compiler
template <class T>
class FBCMIRCompiler : public FBCExecuteFun<T> {

    typedef void (*compiledFun)(MIR_val_t int_heap, MIR_val_t real_heap, MIR_val_t inputs, MIR_val_t outputs);

   protected:
    compiledFun fCompiledFun;
    
    std::map<std::string, int> fIDCounters;
    std::map<std::string, MIR_item_t> fFunProto;
    std::string fIdent;
    
    MIR_context_t fContext;
    MIR_item_t fCompute;

    MIR_reg_t fMIRStack[512];
  
    int fMIRStackIndex;
    int fAddrStackIndex;

    MIR_reg_t fMIRIntHeap;
    MIR_reg_t fMIRRealHeap;
    MIR_reg_t fMIRInputs;
    MIR_reg_t fMIROutputs;
    
    char* getFreshID(const std::string& prefix)
    {
        if (fIDCounters.find(prefix) == fIDCounters.end()) {
            fIDCounters[prefix] = 0;
        }
        int n = fIDCounters[prefix];
        fIDCounters[prefix] = n + 1;
        fIdent = prefix + std::to_string(n);
        return (char*)fIdent.c_str();
    }
   
    MIR_op_t genFloat(float num) { return MIR_new_float_op(fContext, num); }
    MIR_op_t genDouble(double num) { return MIR_new_double_op(fContext, num); }
    MIR_op_t genReal(double num) { return (sizeof(T) == sizeof(double)) ? genDouble(num) : genFloat(num); }
    MIR_op_t genInt32(int num) { return MIR_new_int_op(fContext, num); }
    MIR_op_t genInt64(long long num) { return MIR_new_int_op(fContext, num); }

    MIR_type_t getFloatTy() { return MIR_T_F; }
    MIR_type_t getDoubleTy() { return MIR_T_D; }
    MIR_type_t getRealTy() { return (sizeof(T) == sizeof(double)) ? getDoubleTy() : getFloatTy(); }
    MIR_type_t getInt32Ty() { return MIR_T_I32; }
    MIR_type_t getInt64Ty() { return MIR_T_I64; }
  
    std::string getMathName(const std::string& name) { return (sizeof(T) == sizeof(float)) ? (name + "f") : name; }

    void pushValue(MIR_reg_t val) { fMIRStack[fMIRStackIndex++] = val; }
    MIR_reg_t popValue() { return fMIRStack[--fMIRStackIndex]; }

    void pushBinop(MIR_insn_code_t op, MIR_type_t type, const std::string& res_name = "binop")
    {
        MIR_reg_t binop_res = MIR_new_func_reg(fContext, fCompute->u.func, type, getFreshID(res_name));
        MIR_insn_t insn = MIR_new_insn(fContext, op,
                                       MIR_new_reg_op(fContext, binop_res),
                                       MIR_new_reg_op(fContext, popValue()),
                                       MIR_new_reg_op(fContext, popValue()));
        MIR_append_insn(fContext, fCompute, insn);
        pushValue(binop_res);
    }
    
    void pushIntComp(MIR_insn_code_t op)
    {
        pushBinop(op, getInt64Ty(), "comp_i64");
    }
    
    void pushRealComp(MIR_insn_code_t op)
    {
        pushBinop(op, getInt64Ty(), "comp_real");
    }
    
    void pushUnaryCall(const std::string& name_aux, MIR_type_t type, bool rename)
    {
        std::string name = (rename) ? getMathName(name_aux) : name_aux;
        std::string name_proto = name + "_proto";
        // Generate call
        MIR_type_t res_type = type;
        MIR_var_t var[1];
        var[0].name = "val";
        var[0].type = type;
        MIR_reg_t call_res = MIR_new_func_reg(fContext, fCompute->u.func, type, getFreshID("unary_call"));
        
        // Check proto
        if (fFunProto.find(name_proto) == fFunProto.end()) {
            fFunProto[name_proto] = MIR_new_proto_arr(fContext, name_proto.c_str(), 1, &res_type, 1, var);;
        }
        MIR_item_t proto = fFunProto[name_proto];
        
        MIR_item_t fun = MIR_new_import(fContext, name.c_str());
        MIR_insn_t insn = MIR_new_call_insn(fContext, 4,
                                            MIR_new_ref_op(fContext, proto),
                                            MIR_new_ref_op(fContext, fun),
                                            MIR_new_reg_op(fContext, call_res),
                                            MIR_new_reg_op(fContext, popValue()));
        MIR_append_insn(fContext, fCompute, insn);
        pushValue(call_res);
    }
  
    void pushUnaryIntCall(const std::string& name, bool rename = true)
    {
        return pushUnaryCall(name, getInt64Ty(), rename);
    }
    
    void pushUnaryRealCall(const std::string& name, bool rename = true)
    {
        return pushUnaryCall(name, getRealTy(), rename);
    }

    void pushBinaryCall(const std::string& name_aux, MIR_type_t type, bool rename)
    {
        std::string name = (rename) ? getMathName(name_aux) : name_aux;
        std::string name_proto = name + "_proto";
        // Generate call
        MIR_type_t res_type = type;
        MIR_var_t var[2];
        var[0].name = "val1";
        var[0].type = type;
        var[1].name = "val2";
        var[1].type = type;
        MIR_reg_t call_res = MIR_new_func_reg(fContext, fCompute->u.func, type, getFreshID("binary_call"));
        
        // Check proto
        if (fFunProto.find(name_proto) == fFunProto.end()) {
            fFunProto[name_proto] = MIR_new_proto_arr(fContext, name_proto.c_str(), 1, &res_type, 2, var);
        }
        MIR_item_t proto = fFunProto[name_proto];
        
        MIR_item_t fun = MIR_new_import(fContext, name.c_str());
        MIR_insn_t insn = MIR_new_call_insn(fContext, 5,
                                            MIR_new_ref_op(fContext, proto),
                                            MIR_new_ref_op(fContext, fun),
                                            MIR_new_reg_op(fContext, call_res),
                                            MIR_new_reg_op(fContext, popValue()),
                                            MIR_new_reg_op(fContext, popValue()));
        MIR_append_insn(fContext, fCompute, insn);
        pushValue(call_res);
    }

    void pushBinaryIntCall(const std::string& name, bool rename = true)
    {
        pushBinaryCall(name, getInt64Ty(), rename);
    }

    void pushBinaryRealCall(const std::string& name, bool rename = true)
    {
        pushBinaryCall(name, getRealTy(), rename);
    }

    MIR_reg_t createIndexReg(int index)
    {
        // Load index in a local
        MIR_reg_t index_reg = MIR_new_func_reg(fContext, fCompute->u.func, getInt64Ty(), getFreshID("array_id"));
        MIR_append_insn(fContext, fCompute, MIR_new_insn(fContext,
                                                         MIR_MOV,
                                                         MIR_new_reg_op(fContext, index_reg),
                                                         genInt64(index)));
        return index_reg;
    }
    
    MIR_reg_t createAddOffsetReg(int index)
    {
        // Load index in a local
        MIR_reg_t index_reg = MIR_new_func_reg(fContext, fCompute->u.func, getInt64Ty(), getFreshID("array_id"));
        MIR_append_insn(fContext, fCompute, MIR_new_insn(fContext,
                                                         MIR_MOV,
                                                         MIR_new_reg_op(fContext, index_reg),
                                                         genInt64(index)));
        
        // Add offset result
        MIR_reg_t add_res = MIR_new_func_reg(fContext, fCompute->u.func, getInt64Ty(), getFreshID("add_offset"));
        MIR_insn_t insn = MIR_new_insn(fContext, MIR_ADDS,
                                       MIR_new_reg_op(fContext, add_res),
                                       MIR_new_reg_op(fContext, index_reg),
                                       MIR_new_reg_op(fContext, popValue()));
        MIR_append_insn(fContext, fCompute, insn);
        return add_res;
    }
    
    void pushLoadIntArray(int index)
    {
        // Load index in a local
        pushLoadIntArrayImp(createIndexReg(index));
    }
    
    void pushLoadIntArrayImp(MIR_reg_t index_reg)
    {
        // Create a local res
        MIR_reg_t load_res = MIR_new_func_reg(fContext, fCompute->u.func, getInt64Ty(), getFreshID("load_i64"));
        // Load the int32 value
        MIR_append_insn(fContext, fCompute, MIR_new_insn(fContext, MIR_MOV,
                                                         MIR_new_reg_op(fContext, load_res),
                                                         MIR_new_mem_op(fContext,
                                                                        MIR_T_I32, 0,
                                                                        fMIRIntHeap,
                                                                        index_reg,
                                                                        sizeof(int))));
        pushValue(load_res);
    }
    
    void pushLoadRealArray(int index)
    {
        // Load index in a local
        pushLoadRealArrayImp(createIndexReg(index));
    }
    
    void pushLoadRealArrayImp(MIR_reg_t index_reg)
    {
        // Create a local res
        MIR_reg_t load_res = MIR_new_func_reg(fContext, fCompute->u.func, typedReal(MIR_T_F, MIR_T_D), getFreshID("load_real"));
        // Load the value
        MIR_append_insn(fContext, fCompute, MIR_new_insn(fContext, typedReal(MIR_FMOV, MIR_DMOV),
                                                         MIR_new_reg_op(fContext, load_res),
                                                         MIR_new_mem_op(fContext,
                                                                        typedReal(MIR_T_F, MIR_T_D), 0,
                                                                        fMIRRealHeap,
                                                                        index_reg,
                                                                        sizeof(T))));
        pushValue(load_res);
    }
    
    void pushStoreIntArray(int index)
    {
        // Load index in a local
        pushStoreIntArrayImp(createIndexReg(index));
    }

    void pushStoreIntArrayImp(MIR_reg_t index_reg)
    {
        // Store the value
        MIR_append_insn(fContext, fCompute, MIR_new_insn(fContext, MIR_MOV,
                                                         MIR_new_mem_op(fContext,
                                                                        MIR_T_I32, 0,
                                                                        fMIRIntHeap, index_reg,
                                                                        sizeof(int)),
                                                         MIR_new_reg_op(fContext, popValue())));
    }
    
    void pushStoreRealArray(int index)
    {
        // Load index in a local
        pushStoreRealArrayImp(createIndexReg(index));
    }
    
    void pushStoreRealArrayImp(MIR_reg_t index_reg)
    {
        // Store the value
        MIR_append_insn(fContext, fCompute, MIR_new_insn(fContext, typedReal(MIR_FMOV, MIR_DMOV),
                                                         MIR_new_mem_op(fContext,
                                                                        typedReal(MIR_T_F, MIR_T_D), 0,
                                                                        fMIRRealHeap, index_reg,
                                                                        sizeof(T)),
                                                         MIR_new_reg_op(fContext, popValue())));
    }

    void pushLoadInput(int index)
    {
        // Load index in a local
        MIR_reg_t index_reg = createIndexReg(index);
        MIR_reg_t load_res_ptr = MIR_new_func_reg(fContext, fCompute->u.func, getInt64Ty(), getFreshID("load_ptr"));
        
        // Load the buffer
        MIR_append_insn(fContext, fCompute, MIR_new_insn(fContext, MIR_MOV,
                                                         MIR_new_reg_op(fContext, load_res_ptr),
                                                         MIR_new_mem_op(fContext,
                                                                        getInt64Ty(), 0,
                                                                        fMIRInputs, index_reg,
                                                                        sizeof(int64_t))));
        
        // Create a local res
        MIR_reg_t load_res = MIR_new_func_reg(fContext, fCompute->u.func, typedReal(MIR_T_F, MIR_T_D), getFreshID("load_real"));
        // Load the value
        MIR_append_insn(fContext, fCompute, MIR_new_insn(fContext, typedReal(MIR_FMOV, MIR_DMOV),
                                                         MIR_new_reg_op(fContext, load_res),
                                                         MIR_new_mem_op(fContext,
                                                                        typedReal(MIR_T_F, MIR_T_D), 0,
                                                                        load_res_ptr, popValue(),
                                                                        sizeof(T))));
        pushValue(load_res);
    }

    void pushStoreOutput(int index)
    {
        // Load index in a local
        MIR_reg_t index_reg = createIndexReg(index);
        MIR_reg_t store_res_ptr = MIR_new_func_reg(fContext, fCompute->u.func, getInt64Ty(), getFreshID("store_ptr"));
        
        // Load the buffer
        MIR_append_insn(fContext, fCompute, MIR_new_insn(fContext, MIR_MOV,
                                                         MIR_new_reg_op(fContext, store_res_ptr),
                                                         MIR_new_mem_op(fContext,
                                                                        getInt64Ty(), 0,
                                                                        fMIROutputs, index_reg,
                                                                        sizeof(int64_t))));
        
        // Store the value
        MIR_append_insn(fContext, fCompute, MIR_new_insn(fContext, typedReal(MIR_FMOV, MIR_DMOV),
                                                         MIR_new_mem_op(fContext,
                                                                        typedReal(MIR_T_F, MIR_T_D), 0,
                                                                        store_res_ptr, popValue(),
                                                                        sizeof(T)),
                                                         MIR_new_reg_op(fContext, popValue())));
    }
   
    // Select that only computes one branch: a local variable is create and written in 'then' and 'else' blocks, and loaded in the 'merge' block
    void createSelectBlock(InstructionIT it, MIR_reg_t typed_res, MIR_insn_code_t mov_code)
    {
        MIR_label_t then_block = MIR_new_label(fContext);
        MIR_label_t else_block = MIR_new_label(fContext);
        MIR_label_t merge_block = MIR_new_label(fContext);
        
        // Branch in 'else_block' if false
        MIR_append_insn(fContext, fCompute,
                        MIR_new_insn(fContext, MIR_BFS,
                                     MIR_new_label_op(fContext, else_block),
                                     MIR_new_reg_op(fContext, popValue())));
     
        // Compile then branch (= branch1)
        CompileBlock((*it)->fBranch1, then_block);
        
        // Keep result in 'typed_res'
        MIR_append_insn(fContext, fCompute,
                        MIR_new_insn(fContext, mov_code,
                                     MIR_new_reg_op(fContext, typed_res),
                                     MIR_new_reg_op(fContext, popValue())));
        
        // Branch in 'merge_block'
        MIR_append_insn(fContext, fCompute,
                        MIR_new_insn(fContext, MIR_JMP,
                                     MIR_new_label_op(fContext, merge_block)));
        
        // Compile else branch (= branch2)
        CompileBlock((*it)->fBranch2, else_block);
        
        // Keep result in 'typed_res'
        MIR_append_insn(fContext, fCompute,
                        MIR_new_insn(fContext, mov_code,
                                     MIR_new_reg_op(fContext, typed_res),
                                     MIR_new_reg_op(fContext, popValue())));
        
        // Merge block
        MIR_append_insn(fContext, fCompute, merge_block);
        
        // Push result
        pushValue(typed_res);
    }
    
    // Integer version
    static int mir_abs(int val) { return abs(val); }
    
    static int mir_min_i(int val1, int val2) { return std::min(val1, val2); }
    static int mir_max_i(int val1, int val2) { return std::max(val1, val2); }
    
    // Float versions
    static float mir_fabsf(float val) { return fabsf(val); }
    static float mir_acosf(float val) { return acosf(val); }
    static float mir_acoshf(float val) { return acoshf(val); }
    static float mir_asinf(float val) { return asinf(val); }
    static float mir_asinhf(float val) { return asinhf(val); }
    static float mir_atanf(float val) { return atanf(val); }
    static float mir_atanhf(float val) { return atanhf(val); }
    static float mir_ceilf(float val) { return ceilf(val); }
    static float mir_cosf(float val) { return cosf(val); }
    static float mir_coshf(float val) { return coshf(val); }
    static float mir_expf(float val) { return expf(val); }
    static float mir_floorf(float val) { return floorf(val); }
    static float mir_logf(float val) { return logf(val); }
    static float mir_log10f(float val) { return log10f(val); }
    static float mir_rintf(float val) { return rintf(val); }
    static float mir_roundf(float val) { return roundf(val); }
    static float mir_sinf(float val) { return sinf(val); }
    static float mir_sinhf(float val) { return sinhf(val); }
    static float mir_sqrtf(float val) { return sqrtf(val); }
    static float mir_tanf(float val) { return tanf(val); }
    static float mir_tanhf(float val) { return tanhf(val); }
    static float mir_atan2f(float val1, float val2) { return atan2f(val1, val2); }
    static float mir_fmodf(float val1, float val2) { return fmodf(val1, val2); }
    static float mir_powf(float val1, float val2) { return powf(val1, val2); }
    static float mir_remainderf(float val1, float val2) { return remainderf(val1, val2); }
    
    static float mir_minf(float val1, float val2) { return std::min(val1, val2); }
    static float mir_maxf(float val1, float val2) { return std::max(val1, val2); }
    
    // Double version
    static double mir_fabs(double val) { return fabs(val); }
    static double mir_acos(double val) { return acos(val); }
    static double mir_acosh(double val) { return acosh(val); }
    static double mir_asin(double val) { return asin(val); }
    static double mir_asinh(double val) { return asinh(val); }
    static double mir_atan(double val) { return atan(val); }
    static double mir_atanh(double val) { return atanh(val); }
    static double mir_ceil(double val) { return ceil(val); }
    static double mir_cos(double val) { return cos(val); }
    static double mir_cosh(double val) { return cosh(val); }
    static double mir_exp(double val) { return exp(val); }
    static double mir_floor(double val) { return floor(val); }
    static double mir_log(double val) { return log(val); }
    static double mir_log10(double val) { return log10(val); }
    static double mir_rint(double val) { return rint(val); }
    static double mir_round(double val) { return round(val); }
    static double mir_sin(double val) { return sin(val); }
    static double mir_sinh(double val) { return sinh(val); }
    static double mir_sqrt(double val) { return sqrt(val); }
    static double mir_tan(double val) { return tan(val); }
    static double mir_tanh(double val) { return tanh(val); }
    static double mir_atan2(double val1, double val2) { return atan2(val1, val2); }
    static double mir_fmod(double val1, double val2) { return fmod(val1, val2); }
    static double mir_pow(double val1, double val2) { return pow(val1, val2); }
    static double mir_remainder(double val1, double val2) { return remainder(val1, val2); }
    
    static double mir_min(double val1, double val2) { return std::min(val1, val2); }
    static double mir_max(double val1, double val2) { return std::max(val1, val2); }
    
    static void* importResolver(const char* name)
    {
        // Integer version
        if (strcmp(name, "mir_abs") == 0) return (void*)mir_abs;
        
        if (strcmp(name, "mir_min_i") == 0) return (void*)mir_min_i;
        if (strcmp(name, "mir_max_i") == 0) return (void*)mir_max_i;
        
        // Float versions
        if (strcmp(name, "mir_fabsf") == 0) return (void*)mir_fabsf;
        if (strcmp(name, "mir_acosf") == 0) return (void*)mir_acosf;
        if (strcmp(name, "mir_acoshf") == 0) return (void*)mir_acoshf;
        if (strcmp(name, "mir_asinf") == 0) return (void*)mir_asinf;
        if (strcmp(name, "mir_asinhf") == 0) return (void*)mir_asinhf;
        if (strcmp(name, "mir_atanf") == 0) return (void*)mir_atanf;
        if (strcmp(name, "mir_atanhf") == 0) return (void*)mir_atanhf;
        if (strcmp(name, "mir_ceilf") == 0) return (void*)mir_ceilf;
        if (strcmp(name, "mir_cosf") == 0) return (void*)mir_cosf;
        if (strcmp(name, "mir_coshf") == 0) return (void*)mir_coshf;
        if (strcmp(name, "mir_expf") == 0) return (void*)mir_expf;
        if (strcmp(name, "mir_floorf") == 0) return (void*)mir_floorf;
        if (strcmp(name, "mir_logf") == 0) return (void*)mir_logf;
        if (strcmp(name, "mir_log10f") == 0) return (void*)mir_log10f;
        if (strcmp(name, "mir_rintf") == 0) return (void*)mir_rintf;
        if (strcmp(name, "mir_roundf") == 0) return (void*)mir_roundf;
        if (strcmp(name, "mir_sinf") == 0) return (void*)mir_sinf;
        if (strcmp(name, "mir_sinhf") == 0) return (void*)mir_sinhf;
        if (strcmp(name, "mir_sqrtf") == 0) return (void*)mir_sqrtf;
        if (strcmp(name, "mir_tanf") == 0) return (void*)mir_tanf;
        if (strcmp(name, "mir_tanhf") == 0) return (void*)mir_tanhf;
        if (strcmp(name, "mir_atan2f") == 0) return (void*)mir_atan2f;
        if (strcmp(name, "mir_fmodf") == 0) return (void*)mir_fmodf;
        if (strcmp(name, "mir_powf") == 0) return (void*)mir_powf;
        if (strcmp(name, "mir_remainderf") == 0) return (void*)mir_remainderf;
        
        if (strcmp(name, "mir_minf") == 0) return (void*)mir_minf;
        if (strcmp(name, "mir_maxf") == 0) return (void*)mir_maxf;
        
        // Double versions
        if (strcmp(name, "mir_fabs") == 0) return (void*)mir_fabs;
        if (strcmp(name, "mir_acos") == 0) return (void*)mir_acos;
        if (strcmp(name, "mir_acosh") == 0) return (void*)mir_acosh;
        if (strcmp(name, "mir_asin") == 0) return (void*)mir_asin;
        if (strcmp(name, "mir_asinh") == 0) return (void*)mir_asinh;
        if (strcmp(name, "mir_atan") == 0) return (void*)mir_atan;
        if (strcmp(name, "mir_atanh") == 0) return (void*)mir_atanh;
        if (strcmp(name, "mir_ceil") == 0) return (void*)mir_ceil;
        if (strcmp(name, "mir_cos") == 0) return (void*)mir_cos;
        if (strcmp(name, "mir_cosh") == 0) return (void*)mir_cosh;
        if (strcmp(name, "mir_exp") == 0) return (void*)mir_exp;
        if (strcmp(name, "mir_floor") == 0) return (void*)mir_floor;
        if (strcmp(name, "mir_log") == 0) return (void*)mir_log;
        if (strcmp(name, "mir_log10") == 0) return (void*)mir_log10;
        if (strcmp(name, "mir_rint") == 0) return (void*)mir_rint;
        if (strcmp(name, "mir_round") == 0) return (void*)mir_round;
        if (strcmp(name, "mir_sin") == 0) return (void*)mir_sin;
        if (strcmp(name, "mir_sinh") == 0) return (void*)mir_sinh;
        if (strcmp(name, "mir_sqrt") == 0) return (void*)mir_sqrt;
        if (strcmp(name, "mir_tan") == 0) return (void*)mir_tan;
        if (strcmp(name, "mir_tanh") == 0) return (void*)mir_tanh;
        if (strcmp(name, "mir_atan2") == 0) return (void*)mir_atan2;
        if (strcmp(name, "mir_fmod") == 0) return (void*)mir_fmod;
        if (strcmp(name, "mir_pow") == 0) return (void*)mir_pow;
        if (strcmp(name, "mir_remainder") == 0) return (void*)mir_remainder;
        
        if (strcmp(name, "mir_min") == 0) return (void*)mir_min;
        if (strcmp(name, "mir_max") == 0) return (void*)mir_max;
        
        std::cerr << "importResolver " << name << std::endl;
        faustassert(false);
        return nullptr;
    }
    
    void CompileBlock(FBCBlockInstruction<T>* block, MIR_label_t code_block)
    {
        InstructionIT it  = block->fInstructions.begin();
        bool          end = false;
        
        // Push the block label
        MIR_append_insn(fContext, fCompute, code_block);

        while ((it != block->fInstructions.end()) && !end) {
            //(*it)->write(&std::cout);
            //MIR_output(fContext, stderr);

            switch ((*it)->fOpcode) {
                    // Numbers
                case FBCInstruction::kRealValue: {
                    MIR_reg_t var = MIR_new_func_reg(fContext, fCompute->u.func, getRealTy(), getFreshID("var_real"));
                    MIR_insn_t insn = MIR_new_insn(fContext,
                                                   typedReal(MIR_FMOV, MIR_DMOV),
                                                   MIR_new_reg_op(fContext, var),
                                                   genReal((*it)->fRealValue));
                    MIR_append_insn(fContext, fCompute, insn);
                    pushValue(var);
                    it++;
                    break;
                }

                case FBCInstruction::kInt32Value: {
                    MIR_reg_t var = MIR_new_func_reg(fContext, fCompute->u.func, getInt64Ty(), getFreshID("var_i64"));
                    MIR_insn_t insn = MIR_new_insn(fContext,
                                                   MIR_MOV,
                                                   MIR_new_reg_op(fContext, var),
                                                   genInt64((*it)->fIntValue));
                    MIR_append_insn(fContext, fCompute, insn);
                    pushValue(var);
                    it++;
                    break;
                }

                    // Memory load/store
                case FBCInstruction::kLoadReal:
                    pushLoadRealArray((*it)->fOffset1);
                    it++;
                    break;

                case FBCInstruction::kLoadInt:
                    pushLoadIntArray((*it)->fOffset1);
                    it++;
                    break;

                case FBCInstruction::kStoreReal:
                    pushStoreRealArray((*it)->fOffset1);
                    it++;
                    break;

                case FBCInstruction::kStoreInt:
                    pushStoreIntArray((*it)->fOffset1);
                    it++;
                    break;

                    // Indexed memory load/store: constant values are added at generation time by CreateBinOp...
                case FBCInstruction::kLoadIndexedReal: {
                    MIR_reg_t add_res = createAddOffsetReg((*it)->fOffset1);
                    pushLoadRealArrayImp(add_res);
                    it++;
                    break;
                }

                case FBCInstruction::kLoadIndexedInt: {
                    MIR_reg_t add_res = createAddOffsetReg((*it)->fOffset1);
                    pushLoadIntArrayImp(add_res);
                    it++;
                    break;
                }

                case FBCInstruction::kStoreIndexedReal: {
                    MIR_reg_t add_res = createAddOffsetReg((*it)->fOffset1);
                    pushStoreRealArrayImp(add_res);
                    it++;
                    break;
                }

                case FBCInstruction::kStoreIndexedInt: {
                    MIR_reg_t add_res = createAddOffsetReg((*it)->fOffset1);
                    pushStoreIntArrayImp(add_res);
                    it++;
                    break;
                }

                    // Memory shift
                case FBCInstruction::kBlockShiftReal: {
                    for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
                        pushLoadRealArray(i - 1);
                        pushStoreRealArray(i);
                    }
                    it++;
                    break;
                }

                case FBCInstruction::kBlockShiftInt: {
                    for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
                        pushLoadIntArray(i - 1);
                        pushStoreIntArray(i);
                    }
                    it++;
                    break;
                }

                    // Input/output
                case FBCInstruction::kLoadInput:
                    pushLoadInput((*it)->fOffset1);
                    it++;
                    break;

                case FBCInstruction::kStoreOutput:
                    pushStoreOutput((*it)->fOffset1);
                    it++;
                    break;

                    // Cast
                case FBCInstruction::kCastReal: {
                    MIR_reg_t var = MIR_new_func_reg(fContext, fCompute->u.func, getRealTy(), getFreshID("cast_real"));
                    MIR_insn_t insn = MIR_new_insn(fContext,
                                                   typedReal(MIR_I2F, MIR_I2D),
                                                   MIR_new_reg_op(fContext, var),
                                                   MIR_new_reg_op(fContext, popValue()));
                    MIR_append_insn(fContext, fCompute, insn);
                    pushValue(var);
                    it++;
                    break;
                }
          
                case FBCInstruction::kCastInt: {
                    MIR_reg_t var = MIR_new_func_reg(fContext, fCompute->u.func, getInt64Ty(), getFreshID("cast_i64"));
                    MIR_insn_t insn = MIR_new_insn(fContext,
                                                   typedReal(MIR_F2I, MIR_D2I),
                                                   MIR_new_reg_op(fContext, var),
                                                   MIR_new_reg_op(fContext, popValue()));
                    MIR_append_insn(fContext, fCompute, insn);
                    pushValue(var);
                    it++;
                    break;
                }

                case FBCInstruction::kBitcastInt: {
                    // TODO
                    faustassert(false);
                    MIR_reg_t val = popValue();
                    it++;
                    break;
                }

                case FBCInstruction::kBitcastReal: {
                    // TODO
                    faustassert(false);
                    MIR_reg_t val = popValue();
                    it++;
                    break;
                }

                    // Binary math
                case FBCInstruction::kAddReal:
                    pushBinop(typedReal(MIR_FADD, MIR_DADD), getRealTy());
                    it++;
                    break;

                case FBCInstruction::kAddInt:
                    pushBinop(MIR_ADDS, getInt64Ty());
                    it++;
                    break;

                case FBCInstruction::kSubReal:
                    pushBinop(typedReal(MIR_FSUB, MIR_DSUB), getRealTy());
                    it++;
                    break;

                case FBCInstruction::kSubInt:
                    pushBinop(MIR_SUBS, getInt64Ty());
                    it++;
                    break;

                case FBCInstruction::kMultReal:
                    pushBinop(typedReal(MIR_FMUL, MIR_DMUL), getRealTy());
                    it++;
                    break;

                case FBCInstruction::kMultInt:
                    pushBinop(MIR_MULS, getInt64Ty());
                    it++;
                    break;

                case FBCInstruction::kDivReal:
                    pushBinop(typedReal(MIR_FDIV, MIR_DDIV), getRealTy());
                    it++;
                    break;

                case FBCInstruction::kDivInt:
                    pushBinop(MIR_DIVS, getInt64Ty());
                    it++;
                    break;

                case FBCInstruction::kRemReal:
                    pushBinaryRealCall("mir_remainder");
                    it++;
                    break;

                case FBCInstruction::kRemInt:
                    pushBinop(MIR_MODS, getInt64Ty());
                    it++;
                    break;

                case FBCInstruction::kLshInt:
                    pushBinop(MIR_LSHS, getInt64Ty());
                    it++;
                    break;

                case FBCInstruction::kRshInt:
                    pushBinop(MIR_RSHS, getInt64Ty());
                    it++;
                    break;

                case FBCInstruction::kGTInt:
                    pushIntComp(MIR_GTS);
                    it++;
                    break;

                case FBCInstruction::kLTInt:
                    pushIntComp(MIR_LTS);
                    it++;
                    break;

                case FBCInstruction::kGEInt:
                    pushIntComp(MIR_GES);
                    it++;
                    break;

                case FBCInstruction::kLEInt:
                    pushIntComp(MIR_LES);
                    it++;
                    break;

                case FBCInstruction::kEQInt:
                    pushIntComp(MIR_EQS);
                    it++;
                    break;

                case FBCInstruction::kNEInt:
                    pushIntComp(MIR_NES);
                    it++;
                    break;

                case FBCInstruction::kGTReal:
                    pushRealComp(typedReal(MIR_FGT, MIR_DGT));
                    it++;
                    break;

                case FBCInstruction::kLTReal:
                    pushRealComp(typedReal(MIR_FLT, MIR_DLT));
                    it++;
                    break;

                case FBCInstruction::kGEReal:
                    pushRealComp(typedReal(MIR_FGE, MIR_DGE));
                    it++;
                    break;

                case FBCInstruction::kLEReal:
                    pushRealComp(typedReal(MIR_FLE, MIR_DLE));
                    it++;
                    break;

                case FBCInstruction::kEQReal:
                    pushRealComp(typedReal(MIR_FEQ, MIR_DEQ));
                    it++;
                    break;

                case FBCInstruction::kNEReal:
                    pushRealComp(typedReal(MIR_FNE, MIR_DNE));
                    it++;
                    break;

                case FBCInstruction::kANDInt:
                    pushBinop(MIR_ANDS, getInt64Ty());
                    it++;
                    break;

                case FBCInstruction::kORInt:
                    pushBinop(MIR_ORS, getInt64Ty());
                    it++;
                    break;

                case FBCInstruction::kXORInt:
                    pushBinop(MIR_XORS, getInt64Ty());
                    it++;
                    break;

                    // Extended unary math
                case FBCInstruction::kAbs:
                    pushUnaryIntCall("mir_abs", false);
                    it++;
                    break;

                case FBCInstruction::kAbsf:
                    pushUnaryRealCall("mir_fabs");
                    it++;
                    break;

                case FBCInstruction::kAcosf:
                    pushUnaryRealCall("mir_acos");
                    it++;
                    break;
                    
                case FBCInstruction::kAcoshf:
                    pushUnaryRealCall("mir_acosh");
                    it++;
                    break;

                case FBCInstruction::kAsinf:
                    pushUnaryRealCall("mir_asin");
                    it++;
                    break;
                    
                case FBCInstruction::kAsinhf:
                    pushUnaryRealCall("mir_asinh");
                    it++;
                    break;

                case FBCInstruction::kAtanf:
                    pushUnaryRealCall("mir_atan");
                    it++;
                    break;
                    
                case FBCInstruction::kAtanhf:
                    pushUnaryRealCall("mir_atanh");
                    it++;
                    break;

                case FBCInstruction::kCeilf:
                    pushUnaryRealCall("mir_ceil");
                    it++;
                    break;

                case FBCInstruction::kCosf:
                    pushUnaryRealCall("mir_cos");
                    it++;
                    break;

                case FBCInstruction::kCoshf:
                    pushUnaryRealCall("mir_cosh");
                    it++;
                    break;

                case FBCInstruction::kExpf:
                    pushUnaryRealCall("mir_exp");
                    it++;
                    break;

                case FBCInstruction::kFloorf:
                    pushUnaryRealCall("mir_floor");
                    it++;
                    break;

                case FBCInstruction::kLogf:
                    pushUnaryRealCall("mir_log");
                    it++;
                    break;

                case FBCInstruction::kLog10f:
                    pushUnaryRealCall("mir_log10");
                    it++;
                    break;
                    
                case FBCInstruction::kRintf:
                    pushUnaryRealCall("mir_rint");
                    it++;
                    break;

                case FBCInstruction::kRoundf:
                    pushUnaryRealCall("mir_round");
                    it++;
                    break;

                case FBCInstruction::kSinf:
                    pushUnaryRealCall("mir_sin");
                    it++;
                    break;

                case FBCInstruction::kSinhf:
                    pushUnaryRealCall("mir_sinh");
                    it++;
                    break;

                case FBCInstruction::kSqrtf:
                    pushUnaryRealCall("mir_sqrt");
                    it++;
                    break;

                case FBCInstruction::kTanf:
                    pushUnaryRealCall("mir_tan");
                    it++;
                    break;

                case FBCInstruction::kTanhf:
                    pushUnaryRealCall("mir_tanh");
                    it++;
                    break;

                    // Extended binary math
                case FBCInstruction::kAtan2f:
                    pushBinaryRealCall("mir_atan2");
                    it++;
                    break;

                case FBCInstruction::kFmodf:
                    pushBinaryRealCall("mir_fmod");
                    it++;
                    break;

                case FBCInstruction::kPowf:
                    pushBinaryRealCall("mir_pow");
                    it++;
                    break;

                case FBCInstruction::kMax: {
                    pushBinaryIntCall("mir_max_i", false);
                    it++;
                    break;
                }

                case FBCInstruction::kMaxf: {
                    pushBinaryRealCall("mir_max");
                    it++;
                    break;
                }

                case FBCInstruction::kMin: {
                    pushBinaryIntCall("mir_min_i", false);
                    it++;
                    break;
                }

                case FBCInstruction::kMinf: {
                    pushBinaryRealCall("mir_min");
                    it++;
                    break;
                }

                    // Control
                case FBCInstruction::kReturn:
                    end = true;
                    break;

                case FBCInstruction::kIf: {
                    // TODO
                    faustassert(false);
                    break;
                }
                    
                case FBCInstruction::kSelectInt: {
                    // Create typed local variable
                    MIR_reg_t typed_res = MIR_new_func_reg(fContext, fCompute->u.func, getInt64Ty(), getFreshID("select_i64"));
                    createSelectBlock(it, typed_res, MIR_MOV);
                    it++;
                    break;
                }
                    
                case FBCInstruction::kSelectReal: {
                    // Create typed local variable
                    MIR_reg_t typed_res = MIR_new_func_reg(fContext, fCompute->u.func, getRealTy(), getFreshID("select_real"));
                    createSelectBlock(it, typed_res, typedReal(MIR_FMOV, MIR_DMOV));
                    it++;
                    break;
                }

                case FBCInstruction::kCondBranch: {
                    MIR_reg_t cond_res = MIR_new_func_reg(fContext, fCompute->u.func, getInt64Ty(), getFreshID("cond_i64"));
                    MIR_append_insn(fContext, fCompute, MIR_new_insn(fContext, MIR_MOV, MIR_new_reg_op(fContext, cond_res), genInt64(0)));
                    MIR_append_insn(fContext, fCompute, MIR_new_insn(fContext,
                                                                     MIR_BNES,
                                                                     MIR_new_label_op(fContext, code_block),
                                                                     MIR_new_reg_op(fContext, cond_res),
                                                                     MIR_new_reg_op(fContext, popValue())));
                    it++;
                    break;
                }

                case FBCInstruction::kLoop: {
                    MIR_label_t init_block = MIR_new_label(fContext);
                    MIR_label_t loop_body_block = MIR_new_label(fContext);
                    
                    // Compile init branch (= branch1)
                    CompileBlock((*it)->fBranch1, init_block);
                    
                    // Compile loop branch (= branch2)
                    CompileBlock((*it)->fBranch2, loop_body_block);
                    it++;
                    break;
                }

                default:
                    (*it)->write(&std::cout);
                    faustassert(false);
                    break;
            }
        }
    }
    
   public:
    FBCMIRCompiler(FBCBlockInstruction<T>* fbc_block)
    {
        fMIRStackIndex = 0;
        fAddrStackIndex = 0;

        fContext = MIR_init();
        MIR_module_t module = MIR_new_module(fContext, "Faust");
        
        // Create 'compute' function
        fCompute = MIR_new_func(fContext, "compute", 0,
                                NULL, 4,
                                MIR_T_P, "int_heap",
                                MIR_T_P, "real_heap",
                                MIR_T_P, "inputs",
                                MIR_T_P, "outputs");
        
        // Get the 4 function parameters
        fMIRIntHeap = MIR_reg(fContext, "int_heap", fCompute->u.func);
        fMIRRealHeap = MIR_reg(fContext, "real_heap", fCompute->u.func);
        fMIRInputs = MIR_reg(fContext, "inputs", fCompute->u.func);
        fMIROutputs = MIR_reg(fContext, "outputs", fCompute->u.func);
        
        // Compile compute body
        MIR_label_t entry_block = MIR_new_label(fContext);
        CompileBlock(fbc_block, entry_block);
       
        // Add return
        MIR_append_insn(fContext, fCompute, MIR_new_ret_insn(fContext, 0));
        
        // Finish function
        MIR_finish_func(fContext);
        
        // Finish module
        MIR_finish_module(fContext);
        
        // Load module and link
        MIR_load_module(fContext, module);
        MIR_link(fContext, MIR_set_interp_interface, importResolver);
        
        // Code generation
        MIR_gen_init(fContext);
        fCompiledFun = (compiledFun)MIR_gen(fContext, fCompute);
        MIR_gen_finish(fContext);
        
        // Print module
        //MIR_output(fContext, stderr);
    }

    virtual ~FBCMIRCompiler()
    {
        MIR_finish(fContext);
    }

    void Execute(int* int_heap, T* real_heap, T** inputs, T** outputs)
    {
        fCompiledFun((MIR_val_t){.a = (void*)int_heap},
                     (MIR_val_t){.a = (void*)real_heap},
                     (MIR_val_t){.a = (void*)inputs},
                     (MIR_val_t){.a = (void*)outputs});
        /*
        // Interpreter mode
        MIR_interp(fContext, fCompute, NULL, 4,
                   (MIR_val_t){.a = (void*)int_heap},
                   (MIR_val_t){.a = (void*)real_heap},
                   (MIR_val_t){.a = (void*)inputs},
                   (MIR_val_t){.a = (void*)outputs});
        */
    }
    
};

#endif
