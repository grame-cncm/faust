/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#pragma once

#include "code_container.hh"
#include "dsp_factory.hh"
#include "java_instructions.hh"

using namespace std;

class JAVACodeContainer : public virtual CodeContainer {
   protected:
    JAVAInstVisitor fCodeProducer;
    std::ostream*   fOut;
    string          fSuperKlassName;

   public:
    JAVACodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
        : fCodeProducer(out), fOut(out), fSuperKlassName(super)
    {
        initialize(numInputs, numOutputs);
        fKlassName = name;
    }
    ~JAVACodeContainer() override = default;

    void produceClass() override;
    virtual void generateCompute(int tab) = 0;
    void         produceInternal() override;

    dsp_factory_base* produceFactory() override;

    void printHeader() override { CodeContainer::printHeader(*fOut); }

    CodeContainer* createScalarContainer(const string& name, int sub_container_type) override;

    static CodeContainer* createContainer(const string& name, const string& super, int numInputs, int numOutputs,
                                          ostream* dst = new stringstream());
};

class JAVAScalarCodeContainer : public JAVACodeContainer {
   protected:
   public:
    JAVAScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out,
                            int sub_container_type);
    ~JAVAScalarCodeContainer() override;

    void generateCompute(int tab) override;
};
