/************************** BEGIN wasm-dsp-imp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef wasm_dsp_imp_H
#define wasm_dsp_imp_H

#include <string>
#include <vector>
#include <assert.h>

#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/JSONUIDecoder.h"

// Generic wasm_dsp_factory class than keeps the JSON decoder.

class wasm_dsp_factory_imp : public dsp_factory {
    
    public:
    
        wasm_dsp_factory_imp():fDecoder(nullptr) {}
        virtual ~wasm_dsp_factory_imp()
        {
            delete fDecoder;
        }
    
        JSONUITemplatedDecoder* fDecoder;
    
        std::string getName() { return fDecoder->getName(); }
    
        virtual std::string getSHAKey() { return ""; }
    
        virtual std::string getDSPCode() { return ""; }
    
        std::string getCompileOptions() { return fDecoder->getCompileOptions(); }
    
        std::vector<std::string> getLibraryList() { return fDecoder->getLibraryList(); }
    
        std::vector<std::string> getIncludePathnames() { return fDecoder->getIncludePathnames(); }
    
        virtual dsp* createDSPInstance() {}
    
        virtual void setMemoryManager(dsp_memory_manager* manager) {}
    
        virtual dsp_memory_manager* getMemoryManager() { return nullptr; }
};

// Generic wasm_dsp class than creates and use the JSON decoder, and manage DSP and audio memory.

class wasm_dsp_imp : public dsp {
    
    protected:
    
        wasm_dsp_factory_imp* fFactory;
    
        char* fMemory;          // Wasm memory
    
        int fWasmInputs;        // Index in wasm memory
        int fWasmOutputs;       // Index in wasm memory
    
        FAUSTFLOAT** fInputs;   // Wasm memory mapped to audio pointers
        FAUSTFLOAT** fOutputs;  // Wasm memory mapped to audio pointers
    
        // Assuming fFactory and fMemory are set
        void initDecoder()
        {
            assert(fFactory);
            assert(fMemory);
            
            if (!fFactory->fDecoder) {
                std::string json = std::string(fMemory);
                std::cout << "JSON " << json <<  std::endl;
                fFactory->fDecoder = createJSONUIDecoder(json);
            }
            
            std::cout << "Libfaust version: " << fFactory->fDecoder->getLibVersion() << std::endl;
            std::cout << "Compilation options: " << fFactory->fDecoder->getCompileOptions() << std::endl;
            
            int ptr_size = sizeof(FAUSTFLOAT*);
            int sample_size = sizeof(FAUSTFLOAT);
            int buffer_size = 4096; // Max
            
            fInputs = new FAUSTFLOAT*[fFactory->fDecoder->getNumInputs()];
            fOutputs = new FAUSTFLOAT*[fFactory->fDecoder->getNumOutputs()];
            
            // DSP is placed first with index 0. Audio buffer start at the end of DSP
            int audio_heap_ptr = fFactory->fDecoder->getDSPSize();
            
            // Setup pointers offset
            int audio_heap_ptr_inputs = audio_heap_ptr;
            int audio_heap_ptr_outputs = audio_heap_ptr_inputs + (fFactory->fDecoder->getNumInputs() * ptr_size);
            
            // Setup buffer offset
            int audio_heap_inputs = audio_heap_ptr_outputs + (fFactory->fDecoder->getNumOutputs() * ptr_size);
            int audio_heap_outputs = audio_heap_inputs + (fFactory->fDecoder->getNumInputs() * buffer_size * sample_size);
            
            if (fFactory->fDecoder->getNumInputs() > 0) {
                
                fWasmInputs = audio_heap_ptr_inputs;
                int* HEAP32 = reinterpret_cast<int*>(fMemory + audio_heap_ptr_inputs);
                FAUSTFLOAT* HEAPF32 = reinterpret_cast<FAUSTFLOAT*>(fMemory + audio_heap_inputs);
                
                for (int i = 0; i < fFactory->fDecoder->getNumInputs(); i++) {
                    // Setup input buffer indexes for wasm side
                    HEAP32[i] = audio_heap_inputs + (buffer_size * sample_size * i);
                    // Setup input buffer pointers for runtime side
                    fInputs[i] = HEAPF32 + (buffer_size * i);
                }
            }
            
            if (fFactory->fDecoder->getNumOutputs() > 0) {
                
                fWasmOutputs = audio_heap_ptr_outputs;
                int* HEAP32 = reinterpret_cast<int*>(fMemory + audio_heap_ptr_outputs);
                FAUSTFLOAT* HEAPF32 = reinterpret_cast<FAUSTFLOAT*>(fMemory + audio_heap_outputs);
                
                for (int i = 0; i < fFactory->fDecoder->getNumOutputs(); i++) {
                    // Setup output buffer indexes for wasm side
                    HEAP32[i] = audio_heap_outputs + (buffer_size * sample_size * i);
                    // Setup output buffer pointers for runtime side
                    fOutputs[i] = HEAPF32 + (buffer_size * i);
                }
            }
        }
  
    public:
    
        wasm_dsp_imp(wasm_dsp_factory_imp* factory, char* memory = nullptr):
        fFactory(factory),
        fMemory(memory),
        fInputs(nullptr),
        fOutputs(nullptr),
        fWasmInputs(0),
        fWasmOutputs(0)
        {}
    
        virtual ~wasm_dsp_imp()
        {
            delete [] fInputs;
            delete [] fOutputs;
        }
    
        virtual int getNumInputs() { return -1; }
        virtual int getNumOutputs() { return -1; ; }
        virtual void buildUserInterface(UI* ui_interface)
        {
            fFactory->fDecoder->buildUserInterface(ui_interface, fMemory);
        }
        virtual int getSampleRate() { return -1; }
        virtual void init(int sample_rate) {}
        virtual void instanceInit(int sample_rate) {}
        virtual void instanceConstants(int sample_rate) {}
        virtual void instanceResetUserInterface() {}
        virtual void instanceClear() {}
        virtual wasm_dsp_imp* clone() { return nullptr; }
        virtual void metadata(Meta* m)
        {
            fFactory->fDecoder->metadata(m);
        }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
};

#endif
/**************************  END  wasm-dsp-imp.h **************************/
