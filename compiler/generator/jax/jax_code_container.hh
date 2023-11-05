/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

#ifndef _JAX_CODE_CONTAINER_H
#define _JAX_CODE_CONTAINER_H

#include "jax_instructions.hh"
#include "code_container.hh"
#include "dsp_factory.hh"
#include "omp_code_container.hh"
#include "vec_code_container.hh"
#include "wss_code_container.hh"

#ifdef WIN32
#pragma warning(disable : 4250)
#endif

class JAXCodeContainer : public virtual CodeContainer {
   protected:
    static JAXInstVisitor* gJAXVisitor;
    std::ostream* fOut;

    virtual void produceClass();
        
    // Not used
    virtual void produceInternal() {}

    void generateCompute(int n);

    virtual void generateSR();

   public:
    JAXCodeContainer()
    {}
    JAXCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    
    virtual ~JAXCodeContainer()
    {
        // fCodeProducer is a 'Garbageable'
    }
    
    virtual dsp_factory_base* produceFactory();

    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type);

    static CodeContainer* createContainer(const std::string& name, int numInputs, int numOutputs,
                                          std::ostream* dst = new std::stringstream());

    BlockInst* get_fComputeBlockInstructions() { return fComputeBlockInstructions; }
};

class JAXScalarCodeContainer : public JAXCodeContainer {
   protected:
   
   public:
    JAXScalarCodeContainer()
    {}
    JAXScalarCodeContainer(const std::string& name,
                         int numInputs,
                         int numOutputs,
                         std::ostream* out,
                         int sub_container_type);
    virtual ~JAXScalarCodeContainer()
    {}

};

#endif
