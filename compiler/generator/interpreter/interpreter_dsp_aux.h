/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
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
 
#include "faust/audio/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "export.hh"
#include "fir_interpreter.h"
#include "smartpointer.h"

template <class T>
class interpreter_dsp_aux : public FIRInterpreter<T> {
	
    protected:
        
        int fSamplingFreq;
        
        int fNumInputs;
        int fNumOutputs;
        
        T** fInputs;
        T** fOutputs;
        
        FIRBlockInstruction<T>* fInitBlock;
        FIRBlockInstruction<T>* fComputeBlock;
        FIRBlockInstruction<T>* fComputeDSPBlock;
  	
    public:
      
        interpreter_dsp_aux(int inputs, int ouputs, 
            int real_heap_size, int int_heap_size, 
            FIRBlockInstruction<T>* init, 
            FIRBlockInstruction<T>* compute_control,
            FIRBlockInstruction<T>* compute_dsp) 
            : FIRInterpreter<T>(real_heap_size, int_heap_size)
        {
             
            fInputs = new T*[inputs];
            fOutputs = new T*[ouputs];
            fInitBlock = init;
            fComputeBlock = compute_control;
            fComputeDSPBlock = compute_dsp;
        }
        
        virtual ~interpreter_dsp_aux()
        {
            // Nothing (since garbageable)
        }
        
        interpreter_dsp_aux<T>* createDSPInstance()
        {
            return new interpreter_dsp_aux<T>(fNumInputs, fNumOutputs, 
                                            this->fRealHeapSize, this->fIntHeapSize,
                                            fInitBlock, fComputeBlock, fComputeDSPBlock);
        }
        
        void static metadata(Meta* m) 
        { 
            
        }

        virtual int getNumInputs() 
        {
            return fNumInputs;
        }
        
        virtual int getNumOutputs() 
        {
            return fNumOutputs;
        }
        
        virtual int getInputRate(int channel) 
        {
            return -1;
        }
        
        virtual int getOutputRate(int channel) 
        {
            return -1;
        }
        
        static void classInit(int samplingFreq) 
        {}
        
        virtual void instanceInit(int samplingFreq) 
        {
            fSamplingFreq = samplingFreq;
            
            int int_val;
            T real_val;
            
            // Execute init instructions 
            this->ExecuteBlock(fInitBlock, int_val, real_val, true);
        }
        
        virtual void init(int samplingFreq) 
        {
            classInit(samplingFreq);
            instanceInit(samplingFreq);
        }
        
        virtual void buildUserInterface(UI* interface) 
        {
        
        }
        
        virtual void compute(int count, T** inputs, T** outputs) 
        {
            // Prepare in/out buffers
            for (int i = 0; i < fNumInputs; i++) {
                fInputs[i] = inputs[i];
            }
            for (int i = 0; i < fNumInputs; i++) {
                fOutputs[i] = outputs[i];
            }
            
            // Executes the 'control' block
            this->ExecuteBlockReal(fComputeBlock);
            
            // Executes the DSP block
            for (int i = 0; i < count; i++) {
                this->ExecuteBlockReal(fComputeDSPBlock);
            }
       }
	
};

// Public C++ interface

class interpreter_dsp_factory : public smartable {

};


EXPORT interpreter_dsp_factory* getDSPInterpreterFactoryFromSHAKey(const std::string& sha_key);

EXPORT interpreter_dsp_factory* createDSPInterpreterFactoryFromFile(const std::string& filename, 
                                                          int argc, const char* argv[], 
                                                          const std::string& target, 
                                                          std::string& error_msg, int opt_level = -1);

EXPORT interpreter_dsp_factory* createDSPInterpreterFactoryFromString(const std::string& name_app, const std::string& dsp_content, 
                                                            int argc, const char* argv[], 
                                                            const std::string& target, 
                                                            std::string& error_msg, int opt_level = -1);

EXPORT bool deleteDSPInterpreterFactory(interpreter_dsp_factory* factory);

EXPORT std::vector<std::string> getDSPInterpreterFactoryLibraryList(interpreter_dsp_factory* factory);

EXPORT std::vector<std::string> getAllDSPInterpreterFactories();

EXPORT void deleteAllDSPInterpreterFactories();

class EXPORT interpreter_dsp : public dsp {
                
    public:
    
        void metadata(Meta* m);
     
        int getNumInputs();
        int getNumOutputs();
    
        void init(int samplingFreq);
      
        void buildUserInterface(UI* ui_interface);
        
        void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
        
        interpreter_dsp* copy();
     
};

EXPORT interpreter_dsp* createDSPInterpreterInstance(interpreter_dsp_factory* factory);

EXPORT void deleteDSPInterpreterInstance(interpreter_dsp* dsp);

