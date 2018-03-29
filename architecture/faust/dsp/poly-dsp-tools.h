/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
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

#ifndef __poly_dsp_tools__
#define __poly_dsp_tools__

#include <string>
#include <iostream>
#include <fstream>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/dsp-combiner.h"
#include "faust/dsp/poly-dsp.h"

inline std::string pathToContent(const std::string& path)
{
    std::ifstream file(path.c_str(), std::ifstream::binary);
    
    file.seekg(0, file.end);
    int size = int(file.tellg());
    file.seekg(0, file.beg);
    
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size] = 0;
    string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}


/**
 * Polyphonic DSP with an integrated effect.
 */
class dsp_poly_effect : public dsp_poly {
    
    private:
    
        dsp_poly* fPolyDSP;
    
    public:
    
        dsp_poly_effect(dsp_poly* dsp1, dsp* dsp2)
            :dsp_poly(dsp2), fPolyDSP(dsp1) 
        {}
    
        virtual ~dsp_poly_effect() {}
        
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            return fPolyDSP->keyOn(channel, pitch, velocity);
        }
        void keyOff(int channel, int pitch, int velocity)
        {
            fPolyDSP->keyOff(channel, pitch, velocity);
        }
        void keyPress(int channel, int pitch, int press)
        {
            fPolyDSP->keyPress(channel, pitch, press);
        }
        void chanPress(int channel, int press)
        {
            fPolyDSP->chanPress(channel, press);
        }
        void ctrlChange(int channel, int ctrl, int value)
        {
            fPolyDSP->ctrlChange(channel, ctrl, value);
        }
        void ctrlChange14bits(int channel, int ctrl, int value)
        {
            fPolyDSP->ctrlChange14bits(channel, ctrl, value);
        }
        void pitchWheel(int channel, int wheel)
        {
            fPolyDSP->pitchWheel(channel, wheel);
        }
        void progChange(int channel, int pgm)
        {
            fPolyDSP->progChange(channel, pgm);
        }
};

/**
 * Polyphonic DSP factory class. Helper code to support polyphonic DSP source with an integrated effect.
 */

struct dsp_poly_factory : public dsp_factory {
    
    llvm_dsp_factory* fProcessFactory;
    llvm_dsp_factory* fEffectFactory;
    
    dsp_poly_factory(llvm_dsp_factory* process_factory,
                     llvm_dsp_factory* effect_factory)
        :fProcessFactory(process_factory),
        fEffectFactory(effect_factory)
    {}

    dsp_poly_factory(const std::string& name_app,
                     const std::string& dsp_content,
                     int argc, const char* argv[],
                     const std::string& target,
                     std::string& error_msg,
                     int opt_level = -1)
    {
        // Create 'effect' expression
        std::stringstream code_effect;
        code_effect << "adapt(1,1) = _; adapt(2,2) = _,_; adapt(1,2) = _ <: _,_; adapt(2,1) = _,_ :> _;";
        code_effect << "adaptor(F,G) = adapt(outputs(F),inputs(G)); dsp_code = environment{ " << dsp_content << " };";
        code_effect << "process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;";
        
        fProcessFactory = createDSPFactoryFromString(name_app, dsp_content, argc, argv, target, error_msg);
        if (fProcessFactory) {
            fEffectFactory = createDSPFactoryFromString(name_app, code_effect.str(), argc, argv, target, error_msg);
            if (!fEffectFactory) {
                // The error message is not really needed...
                error_msg = "";
            }
        } else {
            std::cerr << "dsp_poly_factory : " << error_msg << std::endl;
            throw std::bad_alloc();
        }
    }
    
    virtual ~dsp_poly_factory()
    {
        deleteDSPFactory(fProcessFactory);
        if (fEffectFactory) { deleteDSPFactory(fEffectFactory); }
    }
    
    virtual std::string getName() { return fProcessFactory->getName(); }
    virtual std::string getSHAKey() { return fProcessFactory->getSHAKey(); }
    virtual std::string getDSPCode() { return fProcessFactory->getDSPCode(); }
    
    virtual void setMemoryManager(dsp_memory_manager* manager)
    {
        fProcessFactory->setMemoryManager(manager);
        if (fEffectFactory) {
            fEffectFactory->setMemoryManager(manager);
        }
    }
    virtual dsp_memory_manager* getMemoryManager() { return fProcessFactory->getMemoryManager(); }
    
    /* Create a new polyphonic DSP instance with global effect, to be deleted with C++ 'delete'
     *
     * @param nvoices - number of polyphony voices
     * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler).
     *                If false all voices are always running.
     * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
     *                a given control on all voices, assuming GUI::updateAllGuis() is called.
     *                If false, all voices can be individually controlled.
     */
    dsp_poly* createPolyDSPInstance(int nvoices, bool control, bool group)
    {
        dsp_poly* dsp_poly = new mydsp_poly(fProcessFactory->createDSPInstance(), nvoices, control, group);
        if (fEffectFactory) {
            return new dsp_poly_effect(dsp_poly, new dsp_sequencer(dsp_poly, fEffectFactory->createDSPInstance()));
        } else {
            return new dsp_poly_effect(dsp_poly, dsp_poly);
        }
    }
    
     /* Create a new DSP instance, to be deleted with C++ 'delete' */
    dsp* createDSPInstance()
    {
        return fProcessFactory->createDSPInstance();
    }
    
};

/**
 * Create a Faust Polyphonic DSP factory from a DSP source code as a file.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions)
 *
 * @return a Polyphonic DSP factory on success, otherwise a null pointer.
 */
inline dsp_poly_factory* createPolyDSPFactoryFromString(const std::string& name_app,
                                                 const std::string& dsp_content,
                                                 int argc, const char* argv[],
                                                 const std::string& target,
                                                 std::string& error_msg,
                                                 int opt_level = -1)
{
    return new dsp_poly_factory(name_app, dsp_content, argc, argv, target, error_msg, opt_level);
}

/**
 * Create a Faust Polyphonic DSP factory from a DSP source code as a string.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions)
 *
 * @return a Polyphonic DSP factory on success, otherwise a null pointer.
 */
inline dsp_poly_factory* createPolyDSPFactoryFromFile(const std::string& filename,
                                               int argc, const char* argv[],
                                               const std::string& target,
                                               std::string& error_msg,
                                               int opt_level = -1)
{
    return createPolyDSPFactoryFromString("FaustDSP", pathToContent(filename), argc, argv, target, error_msg, opt_level);
}

/**
 * Create a Faust Polyphonic DSP factory from a LLVM bitcode file.
 *
 * @param bit_code_path - the LLVM bitcode file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions). A higher value than the one used when calling
 * createDSPFactory can possibly be used.
 *
 * @return the Polyphonic DSP factory on success, otherwise a null pointer.
 */
inline dsp_poly_factory* readPolyDSPFactoryFromBitcodeFile(const std::string& bit_code_path, const std::string& target, int opt_level = -1)
{
    std::string process_path = bit_code_path + "_bitcode_process";
    std::string effect_path = bit_code_path + "_bicode_effect";
    
    llvm_dsp_factory* process_factory = readDSPFactoryFromBitcodeFile(process_path, target, opt_level);
    llvm_dsp_factory* effect_factory = readDSPFactoryFromBitcodeFile(effect_path, target, opt_level);
    
    if (!process_factory && !effect_factory) {
        return nullptr;
    } else {
        return new dsp_poly_factory(process_factory, effect_factory);
    }
}

/**
 * Write a Faust Polyphonic DSP factory into a LLVM bitcode file.
 *
 * @param factory - the DSP factory
 * @param machine_code_path - the machine code file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings).
 *
 */
inline void writePolyDSPFactoryToBitcodeFile(dsp_poly_factory* factory, const std::string& bit_code_path)
{
    std::string process_path = bit_code_path + "_bitcode_process";
    writeDSPFactoryToBitcodeFile(factory->fProcessFactory, process_path);
    
    if (factory->fEffectFactory) {
        std::string effect_path = bit_code_path + "_bicode_effect";
        writeDSPFactoryToBitcodeFile(factory->fEffectFactory, effect_path);
    }
}

/**
 * Create a Faust Polyphonic DSP factory from a LLVM IR (textual) file.
 *
 * @param bit_code_path - the LLVM bitcode file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions). A higher value than the one used when calling
 * createDSPFactory can possibly be used.
 *
 * @return the Polyphonic DSP factory on success, otherwise a null pointer.
 */
inline dsp_poly_factory* readPolyDSPFactoryFromIRFile(const std::string& ir_code_path, const std::string& target, int opt_level = -1)
{
    std::string process_path = ir_code_path + "_ir_process";
    std::string effect_path = ir_code_path + "_ir_effect";
    
    llvm_dsp_factory* process_factory = readDSPFactoryFromIRFile(process_path, target, opt_level);
    llvm_dsp_factory* effect_factory = readDSPFactoryFromIRFile(effect_path, target, opt_level);
    
    if (!process_factory && !effect_factory) {
        return nullptr;
    } else {
        return new dsp_poly_factory(process_factory, effect_factory);
    }
}

/**
 * Write a Faust Polyphonic DSP factory into a LLVM IR (textual) file.
 *
 * @param factory - the DSP factory
 * @param machine_code_path - the machine code file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings).
 *
 */
inline void writePolyDSPFactoryToIRFile(dsp_poly_factory* factory, const std::string& ir_code_path)
{
    std::string process_path = ir_code_path + "_ir_process";
    writeDSPFactoryToIRFile(factory->fProcessFactory, process_path);
    
    if (factory->fEffectFactory) {
        std::string effect_path = ir_code_path + "_ir_effect";
        writeDSPFactoryToIRFile(factory->fEffectFactory, effect_path);
    }
}

/**
 * Create a Faust Polyphonic DSP factory from a machine code file.
 *
 * @param bit_code_path - the LLVM bitcode file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions). A higher value than the one used when calling
 * createDSPFactory can possibly be used.
 *
 * @return the Polyphonic DSP factory on success, otherwise a null pointer.
 */
inline dsp_poly_factory* readPolyDSPFactoryFromMachineFile(const std::string& machine_code_path, const std::string& target)
{
    std::string process_path = machine_code_path + "_machine_process";
    std::string effect_path = machine_code_path + "_machine_effect";
    
    llvm_dsp_factory* process_factory = readDSPFactoryFromMachineFile(process_path, target);
    llvm_dsp_factory* effect_factory = readDSPFactoryFromMachineFile(effect_path, target);
    
    if (!process_factory && !effect_factory) {
        return nullptr;
    } else {
        return new dsp_poly_factory(process_factory, effect_factory);
    }
}

/**
 * Write a Faust Polyphonic DSP factory into a machine code file.
 *
 * @param factory - the DSP factory
 * @param machine_code_path - the machine code file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings).
 *
 */
inline void writePolyDSPFactoryToMachineFile(dsp_poly_factory* factory, const std::string& machine_code_path, const std::string& target)
{
    std::string process_path = machine_code_path + "_machine_process";
    writeDSPFactoryToMachineFile(factory->fProcessFactory, process_path, target);
    
    if (factory->fEffectFactory) {
        std::string effect_path = machine_code_path + "_machine_effect";
        writeDSPFactoryToMachineFile(factory->fEffectFactory, effect_path, target);
    }
}

/**
 * Get the list of library dependancies of the Faust DSP factory.
 *
 * @param factory - the DSP factory
 *
 * @return the list as a vector of strings.
 */
inline std::vector<std::string> getDSPFactoryLibraryList(dsp_poly_factory* factory)
{
    return getDSPFactoryLibraryList(factory->fProcessFactory);
}

#endif // __poly_dsp_tools__
