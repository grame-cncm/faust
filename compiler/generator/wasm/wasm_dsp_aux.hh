/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
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

#ifndef WASM_DSP_AUX_H
#define WASM_DSP_AUX_H

#include <cstdlib>
#include <string>
#include <vector>

#include "dsp_aux.hh"
#include "dsp_factory.hh"
#include "export.hh"
#include "wasm_binary.hh"

class wasm_dsp_factory;
struct JSONUIDecoder;

/*
 Read the wasm binary module, extract the JSON, define a new end for the module (without the last 'data segment'
 section).
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
        if (!more()) throw faustexception("unexpected end of input");
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
        if (x != y) throw faustexception("WasmBinaryReader : surprising value");
    }

    void verifyInt16(int16_t x)
    {
        int16_t y = getInt16();
        if (x != y) throw faustexception("WasmBinaryReader : surprising value");
    }

    void verifyInt32(int32_t x)
    {
        int32_t y = getInt32();
        if (x != y) throw faustexception("WasmBinaryReader : surprising value");
    }

    void read()
    {
        readHeader();

        // read sections until the end
        while (more()) {
            size_t   sectionCode_start = pos;
            uint32_t sectionCode       = getU32LEB();
            uint32_t payloadLen        = getU32LEB();
            if (pos + payloadLen > size) faustexception("Section extends beyond end of input");
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
                faustexception("bad memory index, must be 0");
            }

            // Offset defined as an 'initializer expression' is 0 (see WASMInstVisitor::generateJSON)
            // *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(0) << int8_t(BinaryConsts::End);
            pos += 3;  // move 3 int8_t

            // read JSON size
            auto size = getU32LEB();

            // read JSON
            for (size_t j = 0; j < size; j++) {
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

class EXPORT wasm_dsp : public dsp {
   private:
    wasm_dsp_factory* fFactory;
    int               fIndex;  // Index of Wasm DSP instance
    int               fDSP;    // Index of Wasm DSP memory

   public:
    wasm_dsp() : fFactory(nullptr), fIndex(-1), fDSP(-1) {}
    wasm_dsp(wasm_dsp_factory* factory, int index);
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

    virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);

    virtual void computeJS(int count, uintptr_t input, uintptr_t output);

    virtual void computeJSTest(int count);
};

typedef class faust_smartptr<wasm_dsp_factory> SDsp_factory;

class EXPORT wasm_dsp_factory : public dsp_factory, public faust_smartable {
   protected:
    dsp_factory_base* fFactory;
    JSONUIDecoder*    fDecoder;
    int               fModule;  // Index of Wasm DSP module
    std::string       fJSON;

   public:
    wasm_dsp_factory() {}
    wasm_dsp_factory(dsp_factory_base* factory);

    virtual ~wasm_dsp_factory();

    std::string getName();

    std::string getSHAKey();
    void        setSHAKey(std::string sha_key);

    std::string getDSPCode();
    void        setDSPCode(std::string code);

    std::string              getCompileOptions();
    std::vector<std::string> getLibraryList();
    std::vector<std::string> getIncludePathnames();

    JSONUIDecoder* getDecoder() { return fDecoder; }

    std::string getJSON() { return fJSON; }

    wasm_dsp* createDSPInstance();

    void                setMemoryManager(dsp_memory_manager* manager);
    dsp_memory_manager* getMemoryManager();

    void write(std::ostream* out, bool binary, bool smallflag = false);
    void writeAux(std::ostream* out, bool binary, bool smallflag = false);

    std::string getBinaryCode();

    void createModuleFromString();

    static wasm_dsp_factory* readWasmDSPFactoryFromMachineFile2(const std::string& machine_code_path);

    static wasm_dsp_factory* readWasmDSPFactoryFromMachine2(const std::string& machine_code);

    // Audio buffer management
    static uintptr_t createJSAudioBuffers(int chan, int frames);
    static void      deleteJSAudioBuffers(uintptr_t js_buffers, int chan);

    static FAUSTFLOAT** createAudioBuffers(int chan, int frames);
    static void         deleteAudioBuffers(FAUSTFLOAT** buffers, int chan);

    static void copyJSAudioBuffer(uintptr_t js_buffers, uintptr_t js_buffer, int chan, int frames);
    static void copyAudioBuffer(FAUSTFLOAT** js_buffers, FAUSTFLOAT* js_buffer, int chan, int frames);

    static std::string gErrorMessage;

    static const std::string& getErrorMessage();

    static dsp_factory_table<SDsp_factory> gWasmFactoryTable;
};

EXPORT bool deleteWasmDSPFactory(wasm_dsp_factory* factory);

EXPORT void deleteAllWasmDSPFactories();

EXPORT wasm_dsp_factory* readWasmDSPFactoryFromMachine(const std::string& machine_code);

EXPORT std::string writeWasmDSPFactoryToMachine(wasm_dsp_factory* factory);

EXPORT wasm_dsp_factory* readWasmDSPFactoryFromMachineFile(const std::string& machine_code_path);

EXPORT void writeWasmDSPFactoryToMachineFile(wasm_dsp_factory* factory, const std::string& machine_code_path);

#endif
