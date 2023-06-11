/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef _WASM_CODE_CONTAINER_H
#define _WASM_CODE_CONTAINER_H

#include "code_container.hh"
#include "dsp_factory.hh"
#include "fir_to_fir.hh"
#include "vec_code_container.hh"
#include "wasm_instructions.hh"
#include "json_instructions.hh"
#include "rn_base64.h"

class WASMCodeContainer : public virtual CodeContainer {
   protected:
    std::ostream*          fOut;
    BufferWithRandomAccess fBinaryOut;
    std::stringstream      fHelper;
    int                    fInternalMemory;  // Whether memory is allocated inside wasm module or JS

    DeclareFunInst* generateInstanceInitFun(const std::string& name, const std::string& obj, bool ismethod, bool isvirtual);
    DeclareFunInst* generateClassInit(const std::string& name);
    DeclareFunInst* generateInstanceClear(const std::string& name, const std::string& obj, bool ismethod, bool isvirtual);
    DeclareFunInst* generateInstanceConstants(const std::string& name, const std::string& obj, bool ismethod, bool isvirtual);
    DeclareFunInst* generateInstanceResetUserInterface(const std::string& name, const std::string& obj, bool ismethod,
                                                       bool isvirtual);

    void generateComputeAux(BlockInst* compute_block);
    
    template <typename REAL>
    std::string generateJSON()
    {
        // JSON generation
        JSONInstVisitor<REAL> json_visitor1;
        generateUserInterface(&json_visitor1);

        PathTableType path_index_table;
        std::map<std::string, MemoryDesc>& fieldTable1 = gGlobal->gWASMVisitor->getFieldTable();
        for (const auto& it : json_visitor1.fPathTable) {
            // Get field index
            MemoryDesc tmp              = fieldTable1[it.first];
            path_index_table[it.second] = tmp.fOffset;
        }

        // "name", "filename" found in metadata
        std::string dsp_code = (gGlobal->gInputString.size() > 0) ? gGlobal->gInputString : pathToContent(gGlobal->gMasterDocument);
        JSONInstVisitor<REAL> json_visitor2("", "", fNumInputs, fNumOutputs,
                                            -1, "", base64_encode(dsp_code), FAUSTVERSION, gGlobal->printCompilationOptions1(),
                                            gGlobal->gReader.listLibraryFiles(), gGlobal->gImportDirList,
                                            gGlobal->gWASMVisitor->getStructSize(), path_index_table, MemoryLayoutType());
        generateUserInterface(&json_visitor2);
        generateMetaData(&json_visitor2);

        return json_visitor2.JSON(true);
    }

   public:
    WASMCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out,
                      bool internal_memory = true);
    virtual ~WASMCodeContainer() {}

    virtual void produceClass();
    virtual void generateCompute() = 0;

    void                      produceInternal() {}
    virtual dsp_factory_base* produceFactory();

    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type);
    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type, bool internal_memory = true);

    static CodeContainer* createContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* dst,
                                          bool internal_memory);
};

class WASMScalarCodeContainer : public WASMCodeContainer {
   protected:
   public:
    WASMScalarCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out,
                            int sub_container_type, bool internal_memory);
    virtual ~WASMScalarCodeContainer() {}

    void generateCompute();
};

class WASMVectorCodeContainer : public VectorCodeContainer, public WASMCodeContainer {
   protected:
   public:
    WASMVectorCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out, bool internal_memory);
    virtual ~WASMVectorCodeContainer() {}

    void generateCompute();
};

#endif
