/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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

#ifndef _SOUL_CODE_CONTAINER_H
#define _SOUL_CODE_CONTAINER_H

#include "code_container.hh"
#include "omp_code_container.hh"
#include "soul_instructions.hh"
#include "vec_code_container.hh"
#include "wss_code_container.hh"

#ifdef WIN32
#pragma warning(disable : 4250)
#endif

// Look for the "fillXXX" function call and keep the size of the third 'table' argument
struct TableSizeVisitor : public DispatchVisitor {
    map<string, int> fSizeTable;

    virtual void visit(FunCallInst* inst)
    {
        if (startWith(inst->fName, "fill")) {
            list<ValueInst*>::const_iterator it = inst->fArgs.begin();
            it++;
            Int32NumInst* size = dynamic_cast<Int32NumInst*>(*it);
            faustassert(size);
            it++;
            LoadVarInst* table = dynamic_cast<LoadVarInst*>(*it);
            faustassert(table);
            fSizeTable[inst->fName + "_" + to_string(size->fNum)] = size->fNum;
        }
    }
};

// Look for the "fillXXX" function call and rename it
struct TableSizeCloneVisitor : public BasicCloneVisitor {
    virtual ValueInst* visit(FunCallInst* inst)
    {
        if (startWith(inst->fName, "fill")) {
            list<ValueInst*>::const_iterator it = inst->fArgs.begin();
            it++;
            Int32NumInst* size = dynamic_cast<Int32NumInst*>(*it);
            faustassert(size);
            it++;
            LoadVarInst* table = dynamic_cast<LoadVarInst*>(*it);
            faustassert(table);
            list<ValueInst*> cloned_args;
            for (auto& it1 : inst->fArgs) {
                cloned_args.push_back(it1->clone(this));
            }
            return new FunCallInst(inst->fName + "_" + to_string(size->fNum), cloned_args, inst->fMethod);
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

    BlockInst* getCode(BlockInst* src) { return static_cast<BlockInst*>(src->clone(this)); }
};

class SOULCodeContainer : public virtual CodeContainer {
   protected:
    SOULInstVisitor fCodeProducer;
    SOULInstUIVisitor fUIVisitor;
    std::ostream*   fOut;

    void produceInit(int tabs);

    virtual void printHeader() { CodeContainer::printHeader(*fOut); }

   protected:
    SOULCodeContainer(const string& name, int numInputs, int numOutputs, ostream* out) : fCodeProducer(out), fOut(out)
    {
        initialize(numInputs, numOutputs);
        fKlassName = name;

        if (!gGlobal->gTableSizeVisitor) {
            gGlobal->gTableSizeVisitor = new TableSizeVisitor();
        }
    }
   
    CodeContainer* createScalarContainer(const string& name, int sub_container_type);
    void           produceInternal();
    void           produceClass();
    virtual void   generateCompute(int tab) = 0;

    virtual dsp_factory_base* produceFactory();

   public:
    static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs, ostream* dst);
};

class SOULScalarCodeContainer : public SOULCodeContainer {
   private:
   public:
    SOULScalarCodeContainer(const string& name, int numInputs, int numOutputs, int sub_container_type, ostream* dst)
        : SOULCodeContainer(name, numInputs, numOutputs, dst)
    {
        fSubContainerType = sub_container_type;
    }

    void generateCompute(int tab);
};

class SOULVectorCodeContainer : public VectorCodeContainer, public SOULCodeContainer {
   private:
   public:
    SOULVectorCodeContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
        : VectorCodeContainer(numInputs, numOutputs), SOULCodeContainer(name, numInputs, numOutputs, dst)
    {
    }

    void generateCompute(int tab);
};

#endif
