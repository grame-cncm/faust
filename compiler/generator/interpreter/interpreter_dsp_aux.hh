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
 
#ifndef interpreter_dsp_aux__h
#define interpreter_dsp_aux__h

#include "faust/audio/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "export.hh"
#include "fir_interpreter.hh"
#include "smartpointer.h"

template <class T>
class interpreter_dsp_aux : public dsp, public FIRInterpreter<T> {
	
    protected:
        
        int fNumInputs;
        int fNumOutputs;
         
        FIRUserInterfaceBlockInstruction<T>* fUserInterfaceBlock;
        FIRBlockInstruction<T>* fInitBlock;
        FIRBlockInstruction<T>* fComputeBlock;
        FIRBlockInstruction<T>* fComputeDSPBlock;
  	
    public:
      
        interpreter_dsp_aux(int inputs, int ouputs, 
                            int real_heap_size, int int_heap_size, 
                            FIRUserInterfaceBlockInstruction<T>* interface, 
                            FIRBlockInstruction<T>* init, 
                            FIRBlockInstruction<T>* compute_control,
                            FIRBlockInstruction<T>* compute_dsp) 
                            : FIRInterpreter<T>(real_heap_size, int_heap_size)
        {
            printf("interpreter_dsp_aux %d %d\n", inputs, ouputs);
            printf("interpreter_dsp_aux %d %d\n", real_heap_size, int_heap_size);
            printf("interpreter_dsp_aux %p  %p  %p\n", init, compute_control, compute_dsp); 
            fNumInputs = inputs;
            fNumOutputs = ouputs;
            this->fInputs = new FAUSTFLOAT*[inputs];
            this->fOutputs = new FAUSTFLOAT*[ouputs];
            fUserInterfaceBlock = interface;
            fInitBlock = init;
            fComputeBlock = compute_control;
            fComputeDSPBlock = compute_dsp;
        }
        
        virtual ~interpreter_dsp_aux()
        {
            delete [] this->fInputs;
            delete [] this->fOutputs;
            // Block fields are kept in factory and shared between all instances
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
            printf("instanceInit samplingFreq = %d\n", samplingFreq);
            //return;
            
            // Store samplingFreq in "fSamplingFreq" variable (at offset 0 in HEAP) 
            this->fRealHeap[0] = samplingFreq;
            
            int int_val;
            T real_val;
            
            printf("instanceInit %p \n", fInitBlock);
            
            // Execute init instructions 
            if (fInitBlock)
                this->ExecuteBlock(fInitBlock, int_val, real_val, true);
        }
        
        virtual void init(int samplingFreq) 
        {
            classInit(samplingFreq);
            instanceInit(samplingFreq);
        }
        
        virtual void buildUserInterface(UI* interface) 
        {
            printf("buildUserInterface\n");
            this->ExecuteBuildUserInterface(fUserInterfaceBlock, interface);
        }
        
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
        {
            //printf("compute count = %d\n", count);
            //return;
            
            // Prepare in/out buffers
            for (int i = 0; i < fNumInputs; i++) {
                this->fInputs[i] = inputs[i];
            }
            for (int i = 0; i < fNumInputs; i++) {
                this->fOutputs[i] = outputs[i];
            }
            
            // Executes the 'control' block
            if (fComputeBlock)
                this->ExecuteBlockReal(fComputeBlock);
                
            //this->PrintBlock(fComputeDSPBlock);
            
            // Executes the DSP loop
            FIRBasicInstruction<T>* loop = (fComputeDSPBlock->fInstructions[1]);
            //printf("loop %d %d %d\n", loop->fOpcode, loop->fOffset, count);
           
            assert(loop->fOpcode == FIRInstruction::kLoop);
            //this->PrintBlock(loop->fbranch1);
            this->ExecuteLoopBlock(loop->fbranch1, loop->fOffset, count);
       }
	
};

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

class EXPORT interpreter_dsp_factory {

    private:
    
        int fNumInputs;
        int fNumOutputs;
        
        int fRealHeapSize;
        int fIntHeapSize;
        
        FIRUserInterfaceBlockInstruction<float>* fUserInterfaceBlock;
        FIRBlockInstruction<float>* fInitBlock;
        FIRBlockInstruction<float>* fComputeBlock;
        FIRBlockInstruction<float>* fComputeDSPBlock;
        
        std::string fExpandedDSP;
        std::string fShaKey;
        std::string fName;

    public: 
    
        interpreter_dsp_factory(int inputs, int ouputs, 
                                int real_heap_size, int int_heap_size, 
                                FIRUserInterfaceBlockInstruction<float>* interface, 
                                FIRBlockInstruction<float>* init, 
                                FIRBlockInstruction<float>* compute_control,
                                FIRBlockInstruction<float>* compute_dsp)
            :fNumInputs(inputs),
            fNumOutputs(ouputs),
            fRealHeapSize(real_heap_size),
            fIntHeapSize(int_heap_size),
            fUserInterfaceBlock(interface),
            fInitBlock(init),
            fComputeBlock(compute_control),
            fComputeDSPBlock(compute_dsp)
        {
            printf("interpreter_dsp_factory %d %d\n", inputs, ouputs);
            printf("interpreter_dsp_factory %d %d\n", real_heap_size, int_heap_size);
        }
        
        virtual ~interpreter_dsp_factory()
        {
            // No more DSP instances, so delete
            delete fUserInterfaceBlock;
            delete fInitBlock;
            delete fComputeBlock;
            delete fComputeDSPBlock;
        }
        
        /* Return Factory name */
        std::string getName();
        
        /* Return Factory SHA key */
        std::string getSHAKey();
  
        /* Return Factory expanded DSP code */
        std::string getDSPCode();
        
        interpreter_dsp* createDSPInstance();
     
};

// Public C++ interface

EXPORT interpreter_dsp_factory* getDSPInterpreterFactoryFromSHAKey(const std::string& sha_key);

EXPORT interpreter_dsp_factory* createDSPInterpreterFactoryFromFile(const std::string& filename, 
                                                                  int argc, const char* argv[], 
                                                                  std::string& error_msg);

EXPORT interpreter_dsp_factory* createDSPInterpreterFactoryFromString(const std::string& name_app, const std::string& dsp_content, 
                                                                    int argc, const char* argv[], 
                                                                    std::string& error_msg);

EXPORT bool deleteDSPInterpreterFactory(interpreter_dsp_factory* factory);

EXPORT std::vector<std::string> getDSPInterpreterFactoryLibraryList(interpreter_dsp_factory* factory);

EXPORT std::vector<std::string> getAllDSPInterpreterFactories();

EXPORT void deleteAllDSPInterpreterFactories();

EXPORT interpreter_dsp* createDSPInterpreterInstance(interpreter_dsp_factory* factory);

EXPORT void deleteDSPInterpreterInstance(interpreter_dsp* dsp);

#endif