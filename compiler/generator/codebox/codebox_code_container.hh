/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2023 GRAME, Centre National de Creation Musicale
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

#ifndef _CODEBOX_CODE_CONTAINER_H
#define _CODEBOX_CODE_CONTAINER_H

#include "codebox_instructions.hh"
#include "code_container.hh"
#include "dsp_factory.hh"

#ifdef WIN32
#pragma warning(disable : 4250)
#endif

// Base class for all backend code generation options (-scalar, -vec, -omp, -sch)
class CodeboxCodeContainer : public virtual CodeContainer {
   protected:
    static CodeboxInstVisitor* gCodeboxVisitor;
    std::ostream* fOut;
    CodeboxBargraphVisitor fBargraph;
    
    // Not used since subcontainers are inlined
    virtual void produceInternal()
    {};

    virtual void produceClass();
   
   public:
    CodeboxCodeContainer()
    {}
    CodeboxCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    
    virtual ~CodeboxCodeContainer()
    {
        // fCodeProducer is a 'Garbageable', so nothing to delete
    }
    
    virtual void generateCompute(int tab) = 0;
    
    virtual dsp_factory_base* produceFactory();

    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type);

    static CodeContainer* createContainer(const std::string& name, int numInputs, int numOutputs,
                                          std::ostream* dst = new std::stringstream());
};

// Used in -scalar (= default) mode
class CodeboxScalarCodeContainer : public CodeboxCodeContainer {
   protected:
  
   public:
    CodeboxScalarCodeContainer()
    {}
    CodeboxScalarCodeContainer(const std::string& name,
                             int numInputs,
                             int numOutputs,
                             std::ostream* out,
                             int sub_container_type);
    virtual ~CodeboxScalarCodeContainer()
    {}

    void generateCompute(int n);
};

#endif
