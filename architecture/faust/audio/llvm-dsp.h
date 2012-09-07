/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2012 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/

#ifndef LLVM_DSP_H
#define LLVM_DSP_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <string>
#include "faust/audio/dsp.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct llvm_dsp_factory {};

// Factory

llvm_dsp_factory* createDSPFactory(int argc, char *argv[], 
                        const std::string& library_path, const std::string& draw_path, const std::string& name, 
                        const std::string& input, const std::string& target, 
                        char* error_msg, int opt_level = 3);
                                    
void deleteDSPFactory(llvm_dsp_factory* factory);
          
// Bitcode <==> string                                      
llvm_dsp_factory* readDSPFactoryFromBitcode(const std::string& bit_code, const std::string& target, int opt_level = 0);
 
std::string writeDSPFactoryToBitcode(llvm_dsp_factory* factory);

// Bitcode <==> file
llvm_dsp_factory* readDSPFactoryFromBitcodeFile(const std::string& bit_code_path, const std::string& target, int opt_level = 0);

void writeDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const std::string& bit_code_path);

// IR <==> string
llvm_dsp_factory* readDSPFactoryFromIR(const std::string& ir_code, const std::string& target, int opt_level = 0);

std::string writeDSPFactoryToIR(llvm_dsp_factory* factory);

// IR <==> file
llvm_dsp_factory* readDSPFactoryFromIRFile(const std::string& ir_code_path, const std::string& target, int opt_level = 0);

void writeDSPFactoryToIRFile(llvm_dsp_factory* factory, const std::string& ir_code_path);

// Instance class

class llvm_dsp : public dsp {
               
    public:
      
        virtual int getNumInputs();
        virtual int getNumOutputs();

        void classInit(int samplingFreq);
        virtual void instanceInit(int samplingFreq);
        virtual void init(int samplingFreq);

        virtual void buildUserInterface(UI* interface);
        virtual std::string buildJSON();

        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
     
};

llvm_dsp* createDSPInstance(llvm_dsp_factory* factory);

void deleteDSPInstance(llvm_dsp* dsp);

#ifdef __cplusplus
}
#endif

#endif