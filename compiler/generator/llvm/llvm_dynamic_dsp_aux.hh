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
 
#ifndef LLVM_DYNAMIC_DSP_AUX_H
#define LLVM_DYNAMIC_DSP_AUX_H

#include "llvm_dsp_aux.hh"

class llvm_dynamic_dsp_factory_aux : public llvm_dsp_factory_aux {

    public:
    
        llvm_dynamic_dsp_factory_aux(const string& sha_key,
                                     const std::vector<std::string>& pathname_list,
                                     llvm::Module* module,
                                     llvm::LLVMContext* context,
                                     const string& target,
                                     int opt_level = 0);
    
    #if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
        llvm_dynamic_dsp_factory_aux(const string& sha_key, const string& machine_code, const string& target)
        :llvm_dsp_factory_aux(sha_key, machine_code, target)
        {}
    #endif
    
        // Bitcode
        string writeDSPFactoryToBitcode();
        
        void writeDSPFactoryToBitcodeFile(const string& bit_code_path);
        
        // IR
        virtual string writeDSPFactoryToIR();
        
        virtual void writeDSPFactoryToIRFile(const string& ir_code_path);
    
};

#endif
