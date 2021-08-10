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

#ifndef _JULIA_CODE_CONTAINER_H
#define _JULIA_CODE_CONTAINER_H

#include "julia_instructions.hh"
#include "code_container.hh"
#include "dsp_factory.hh"
#include "omp_code_container.hh"
#include "vec_code_container.hh"
#include "wss_code_container.hh"

#ifdef WIN32
#pragma warning(disable : 4250)
#endif

class JuliaCodeContainer : public virtual CodeContainer {
   protected:
    static JuliaInstVisitor* gJuliaVisitor;
    std::ostream* fOut;

    virtual void produceClass();
    
    void produceMetadata(int tabs);
    
    // Not used
    virtual void produceInternal() {}

    void generateCompute(int n);

   public:
    JuliaCodeContainer()
    {}
    JuliaCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    
    virtual ~JuliaCodeContainer()
    {
        // fCodeProducer is a 'Garbageable'
    }
    
    virtual dsp_factory_base* produceFactory();

    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type);

    static CodeContainer* createContainer(const std::string& name, int numInputs, int numOutputs,
                                          std::ostream* dst = new std::stringstream());
};

class JuliaScalarCodeContainer : public JuliaCodeContainer {
   protected:
   
   public:
    JuliaScalarCodeContainer()
    {}
    JuliaScalarCodeContainer(const std::string& name,
                         int numInputs,
                         int numOutputs,
                         std::ostream* out,
                         int sub_container_type);
    virtual ~JuliaScalarCodeContainer()
    {}

};

class JuliaVectorCodeContainer : public VectorCodeContainer, public JuliaCodeContainer {
   protected:
    
   public:
    JuliaVectorCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    virtual ~JuliaVectorCodeContainer()
    {}

    void generateCompute(int tab);
};

#endif
