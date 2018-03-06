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
    
        llvm_dynamic_dsp_factory_aux(const std::string& sha_key,
                                     const std::vector<std::string>& pathname_list,
                                     llvm::Module* module,
                                     llvm::LLVMContext* context,
                                     const std::string& target,
                                     int opt_level = 0);
    
        llvm_dynamic_dsp_factory_aux(const std::string& sha_key,
                                     const std::string& machine_code,
                                     const std::string& target)
        :llvm_dsp_factory_aux(sha_key, machine_code, target)
        {}
    
        // Bitcode
        std::string writeDSPFactoryToBitcode();
        
        void writeDSPFactoryToBitcodeFile(const std::string& bit_code_path);
        
        // IR
        virtual std::string writeDSPFactoryToIR();
        
        virtual void writeDSPFactoryToIRFile(const std::string& ir_code_path);
    
};

#endif
