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

#ifndef _CLANG_CODE_CONTAINER_H
#define _CLANG_CODE_CONTAINER_H

#include <fstream>
#include <iostream>
#include <sstream>

#include "c_code_container.hh"
#include "cpp_code_container.hh"
#include "dag_instructions_compiler.hh"

struct LLVMResult;

class ClangCodeContainer : public virtual CodeContainer {
   protected:
    InstructionsCompiler* fCompiler;
    CodeContainer*        fContainer;
    std::ofstream*        fOut;
    std::string           fTmpFile;

    const char* getTempName()
    {
        /*
        if (fTmpFile == "") {
            char path[256];
            fTmpFile = string(tmpnam(path)) + ".c";
        }
        return fTmpFile.c_str();
        */
        // TODO
        return "";
    }

   public:
    ClangCodeContainer(const std::string& name, int numInputs, int numOutputs);
    virtual ~ClangCodeContainer();

    virtual LLVMResult* produceModule(Tree signals, const std::string& filename);

    virtual void produceInternal() { fContainer->produceInternal(); }

    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type)
    {
        faustassert(false);
        return nullptr;
    }  // Not used

    static CodeContainer* createContainer(const std::string& name, int numInputs, int numOutputs);
};

#endif
