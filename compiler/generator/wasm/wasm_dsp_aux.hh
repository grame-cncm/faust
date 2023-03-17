/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
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

#ifndef WASM_DSP_AUX_H
#define WASM_DSP_AUX_H

#include <cstdlib>
#include <string>
#include <vector>

#include "faust/gui/MapUI.h"
#include "faust/gui/JSONControl.h"
#include "faust/export.h"

#include "dsp_aux.hh"
#include "dsp_factory.hh"
#include "wasm_binary.hh"

class wasm_dsp_factory;
struct JSONUIDecoderBase;

/*
 Read the wasm binary module, extract the JSON, define a new end for the module
 (without the last 'data segment' section).
 */

struct WasmBinaryReader {
    size_t      pos, size, data_segment_pos;
    uint8_t*    input;
    bool        debug;
    std::string json;

    WasmBinaryReader(const std::string& code) : pos(0), debug(false)
    {
        input = (uint8_t*)malloc(code.size());
        memcpy(input, code.c_str(), code.size());
        size             = code.size();
        data_segment_pos = -1;
        if (debug) std::cerr << "WasmBinaryReader size : " << size << std::endl;
    }
    
    ~WasmBinaryReader() { free(input); }

    bool more() { return pos < size; }

    uint8_t getInt8()
    {
        if (!more()) throw faustexception("ERROR : WasmBinaryReader, unexpected end of input\n");
        return input[pos++];
    }

    uint16_t getInt16()
    {
        auto ret = uint16_t(getInt8());
        ret |= uint16_t(getInt8()) << 8;
        return ret;
    }

    uint32_t getInt32()
    {
        auto ret = uint32_t(getInt16());
        ret |= uint32_t(getInt16()) << 16;
        return ret;
    }

    uint64_t getInt64()
    {
        auto ret = uint64_t(getInt32());
        ret |= uint64_t(getInt32()) << 32;
        return ret;
    }

    uint32_t getU32LEB()
    {
        if (debug) std::cerr << "<==" << std::endl;
        U32LEB ret;
        ret.read([&]() { return getInt8(); });
        if (debug) std::cerr << "getU32LEB: " << ret.value << " ==>" << std::endl;
        return ret.value;
    }

    void verifyInt8(int8_t x)
    {
        int8_t y = getInt8();
        if (x != y) throw faustexception("ERROR : WasmBinaryReader, surprising value\n");
    }

    void verifyInt16(int16_t x)
    {
        int16_t y = getInt16();
        if (x != y) throw faustexception("ERROR : WasmBinaryReader, surprising value\n");
    }

    void verifyInt32(int32_t x)
    {
        int32_t y = getInt32();
        if (x != y) throw faustexception("ERROR : WasmBinaryReader, surprising value\n");
    }

    void read()
    {
        readHeader();

        // read sections until the end
        while (more()) {
            size_t   sectionCode_start = pos;
            uint32_t sectionCode       = getU32LEB();
            uint32_t payloadLen        = getU32LEB();
            if (pos + payloadLen > size) faustexception("ERROR : WasmBinaryReader, section extends beyond end of input\n");
            auto oldPos = pos;

            switch (sectionCode) {
                case BinaryConsts::Section::Start:
                    readStart();
                    break;
                case BinaryConsts::Section::Memory:
                    readMemory();
                    break;
                case BinaryConsts::Section::Type:
                    readSignatures();
                    break;
                case BinaryConsts::Section::Import:
                    readImports();
                    break;
                case BinaryConsts::Section::Function:
                    readFunctionSignatures();
                    break;
                case BinaryConsts::Section::Code:
                    readFunctions();
                    break;
                case BinaryConsts::Section::Export:
                    readExports();
                    break;
                case BinaryConsts::Section::Element:
                    readTableElements();
                    break;
                case BinaryConsts::Section::Global:
                    readGlobals();
                    break;
                case BinaryConsts::Section::Data: {
                    readDataSegments();
                    // Keep 'data_segment_pos' with is actually the new module end (so remove the last 'data segment'
                    // section)
                    data_segment_pos = sectionCode_start;
                    break;
                }
                case BinaryConsts::Section::Table:
                    readFunctionTableDeclaration();
                    break;
                default:
                    break;
            }

            // move pos (without checking coherency...)
            pos = oldPos + payloadLen;
        }
    }

    void readHeader()
    {
        if (debug) std::cerr << "== readHeader" << std::endl;
        verifyInt32(BinaryConsts::Magic);
        verifyInt32(BinaryConsts::Version);
    }

    void readStart()
    {
        if (debug) std::cerr << "== readStart" << std::endl;
    }

    void readMemory()
    {
        if (debug) std::cerr << "== readMemory" << std::endl;
    }

    void readSignatures()
    {
        if (debug) std::cerr << "== readSignatures" << std::endl;
    }

    void readImports()
    {
        if (debug) std::cerr << "== readImports" << std::endl;
    }

    void readFunctionSignatures()
    {
        if (debug) std::cerr << "== readFunctionSignatures" << std::endl;
    }

    void readFunctions()
    {
        if (debug) std::cerr << "== readFunctions" << std::endl;
    }

    void readExports()
    {
        if (debug) std::cerr << "== readExports" << std::endl;
    }

    void readTableElements()
    {
        if (debug) std::cerr << "== readTableElements" << std::endl;
    }

    void readGlobals()
    {
        if (debug) std::cerr << "== readGlobals" << std::endl;
    }

    void readDataSegments()
    {
        if (debug) std::cerr << "== readDataSegments" << std::endl;
        auto num = getU32LEB();
        for (size_t i = 0; i < num; i++) {
            auto memoryIndex = getU32LEB();
            if (memoryIndex != 0) {
                faustexception("ERROR : WasmBinaryReader, bad memory index, must be 0\n");
            }

            // Offset defined as an 'initializer expression' is 0 (see WASMInstVisitor::generateJSON)
            // *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(0) << int8_t(BinaryConsts::End);
            pos += 3;  // move 3 int8_t

            // read JSON size
            auto jsize = getU32LEB();

            // read JSON
            for (size_t j = 0; j < jsize; j++) {
                json += char(getInt8());
            }
            if (debug) std::cerr << "JSON : " << json << std::endl;
        }
    }

    void readFunctionTableDeclaration()
    {
        if (debug) std::cerr << "== readFunctionTableDeclaration" << std::endl;
    }

    void readUserSection(size_t payloadLen)
    {
        if (debug) std::cerr << "== readUserSection" << std::endl;
    }
};

// The C++ side version of compiled wasm code

class SoundUI;
class MidiUI;

class LIBFAUST_API wasm_dsp : public dsp, public JSONControl {
   private:
    wasm_dsp_factory* fFactory;
   public:
    wasm_dsp() : fFactory(nullptr) {}
    wasm_dsp(wasm_dsp_factory* factory);
    virtual ~wasm_dsp();

    virtual int getNumInputs();

    virtual int getNumOutputs();

    virtual void buildUserInterface(UI* ui_interface);

    virtual int getSampleRate();

    virtual void init(int sample_rate);

    virtual void instanceInit(int sample_rate);

    virtual void instanceConstants(int sample_rate);

    virtual void instanceResetUserInterface();

    virtual void instanceClear();

    virtual wasm_dsp* clone();

    virtual void metadata(Meta* m);

    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);

    virtual void computeJS(int count, uintptr_t inputs, uintptr_t outputs);
    
    virtual void setParamValue(const std::string& path, FAUSTFLOAT value);
    
    virtual FAUSTFLOAT getParamValue(const std::string& path);

};

typedef class faust_smartptr<wasm_dsp_factory> SDsp_factory;

class LIBFAUST_API wasm_dsp_factory : public dsp_factory, public faust_smartable {
    friend class wasm_dsp;
   protected:
    dsp_factory_base*   fFactory;
    JSONUIDecoderBase*  fDecoder;
    int                 fInstance; // Index of wasm DSP instance
    MapUI               fMapUI;
   
/*
#ifdef EMCC
    SoundUI* fSoundUI;
#endif
*/

   public:
    wasm_dsp_factory():fFactory(nullptr), fDecoder(nullptr), fInstance(0)
    {}
    wasm_dsp_factory(dsp_factory_base* factory);
    wasm_dsp_factory(int instance, const std::string& json);

    virtual ~wasm_dsp_factory();

    std::string getName();

    std::string getSHAKey();
    void        setSHAKey(const std::string& sha_key);

    std::string getDSPCode();
    void        setDSPCode(const std::string& code);

    std::string              getCompileOptions();
    std::vector<std::string> getLibraryList();
    std::vector<std::string> getIncludePathnames();
    
    std::vector<std::string> getWarningMessages();

    JSONUIDecoderBase* getDecoder() { return fDecoder; }

    wasm_dsp* createDSPInstance();
    void deleteDSPInstance(wasm_dsp* dsp);
  
    void                setMemoryManager(dsp_memory_manager* manager);
    dsp_memory_manager* getMemoryManager();

    void write(std::ostream* out, bool binary, bool smallflag = false);
    void writeHelper(std::ostream* out, bool binary, bool smallflag = false);

    std::string getBinaryCode();

    static wasm_dsp_factory* readWasmDSPFactoryFromMachineFile2(const std::string& machine_code_path);

    static wasm_dsp_factory* readWasmDSPFactoryFromMachine2(const std::string& machine_code);
    
    static wasm_dsp_factory* createWasmDSPFactory(int instance, const std::string& json);
    
    static bool deleteWasmDSPFactory2(wasm_dsp_factory* factory);
    
    static std::string extractJSON(const std::string& code);
   
    static std::string gErrorMessage;

    static const std::string& getErrorMessage();

    static dsp_factory_table<SDsp_factory> gWasmFactoryTable;
};

LIBFAUST_API bool deleteWasmDSPFactory(wasm_dsp_factory* factory);

LIBFAUST_API void deleteAllWasmDSPFactories();

LIBFAUST_API wasm_dsp_factory* readWasmDSPFactoryFromMachine(const std::string& machine_code, std::string& error_msg);

LIBFAUST_API std::string writeWasmDSPFactoryToMachine(wasm_dsp_factory* factory);

LIBFAUST_API wasm_dsp_factory* readWasmDSPFactoryFromMachineFile(const std::string& machine_code_path, std::string& error_msg);

LIBFAUST_API void writeWasmDSPFactoryToMachineFile(wasm_dsp_factory* factory, const std::string& machine_code_path);

#endif
