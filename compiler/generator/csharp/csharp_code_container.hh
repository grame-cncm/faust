/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2021 GRAME, Centre National de Creation Musicale
    Modified to C# from Java by Mike Oliphant
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

#ifndef _CSHARP_CODE_CONTAINER_H
#define _CSHARP_CODE_CONTAINER_H

#include "code_container.hh"
#include "dsp_factory.hh"
#include "csharp_instructions.hh"

class CSharpCodeContainer : public virtual CodeContainer {
   protected:
    CSharpInstVisitor fCodeProducer;
    std::ostream*   fOut;
    std::string     fSuperKlassName;

   public:
    CSharpCodeContainer(const std::string& name, const std::string& super, int numInputs, int numOutputs, std::ostream* out)
        : fCodeProducer(out), fOut(out), fSuperKlassName(super)
    {
        initialize(numInputs, numOutputs);
        fKlassName = name;
    }
    virtual ~CSharpCodeContainer() {}

    virtual void produceClass();
    virtual void produceInfoFunctions(int tabs, const std::string& classname, const std::string& obj, bool ismethod, FunTyped::FunAttribute funtype, TextInstVisitor* producer);
    virtual void generateCompute(int tab) = 0;
    void         produceInternal();

    virtual dsp_factory_base* produceFactory();

    virtual void printHeader() { CodeContainer::printHeader(*fOut); }

    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type);

    static CodeContainer* createContainer(const std::string& name, const std::string& super, int numInputs, int numOutputs, std::ostream* dst = new std::stringstream());
};

class CSharpScalarCodeContainer : public CSharpCodeContainer {
   protected:
   public:
    CSharpScalarCodeContainer(const std::string& name, const std::string& super, int numInputs, int numOutputs, std::ostream* out,
                            int sub_container_type);
    virtual ~CSharpScalarCodeContainer();

    void generateCompute(int tab);
};

#endif
