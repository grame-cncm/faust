/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

#ifndef _CPP_CODE_CONTAINER_H
#define _CPP_CODE_CONTAINER_H

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
#include "code_container.hh"
#include "cpp_instructions.hh"
#include "opencl_instructions.hh"

using namespace std;

class CPPCodeContainer : public CodeContainer {

    protected:

        CPPInstVisitor fCodeProducer;
        std::ostream* fOut;
        string fKlassName;
        string fSuperKlassName;

    public:

        CPPCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
            :CodeContainer(numInputs, numOutputs), fCodeProducer(out), fOut(out), fKlassName(name), fSuperKlassName(super)
        {}
        virtual ~CPPCodeContainer()
        {}

        virtual void produceClass();
        virtual void generateCompute(int tab) = 0;
        virtual void produceInternal();

        CodeContainer* createScalarContainer(const string& name);

};

class CPPScalarCodeContainer : public CPPCodeContainer {

    protected:


    public:

        CPPScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
        virtual ~CPPScalarCodeContainer();

        void generateCompute(int tab);

};

class CPPVectorCodeContainer : public CPPCodeContainer {

    protected:


    public:

        CPPVectorCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
        virtual ~CPPVectorCodeContainer();

        void generateCompute(int tab);

};


class CPPOpenMPCodeContainer : public CPPCodeContainer {

    protected:


    public:

        CPPOpenMPCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
        virtual ~CPPOpenMPCodeContainer();

        void generateCompute(int tab);

};

class CPPWorkStealingCodeContainer : public CPPCodeContainer {

    protected:


    public:

        CPPWorkStealingCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
        virtual ~CPPWorkStealingCodeContainer();

        void produceClass();
        void generateCompute(int tab);

};

class CPPOpenCLCodeContainer : public CPPCodeContainer {

    protected:
    
        // Control fields are preceded with "control->"
        // Non-confrol fields are preceded with "dsp->"
        struct KernelInstVisitor : public CPPInstVisitor {

            map < string, string> fFunctionTable;
            KernelInstVisitor(std::ostream* out, int tab)
                :CPPInstVisitor(out, tab)
            {
                fFunctionTable["sin"] = "native_sin";
                fFunctionTable["sinf"] = "native_sin";
                fFunctionTable["cos"] = "native_cos";
                fFunctionTable["cosf"] = "native_cos";
                fFunctionTable["tan"] = "native_tan";
                fFunctionTable["tanf"] = "native_tan";
                fFunctionTable["log"] = "native_log";
                fFunctionTable["logf"] = "native_log";
                fFunctionTable["log10"] = "native_log10";
                fFunctionTable["log10f"] = "native_log10";
                fFunctionTable["log2"] = "native_log2";
                fFunctionTable["log2f"] = "native_log2";
                fFunctionTable["exp"] = "native_exp";
                fFunctionTable["expf"] = "native_exp";
                fFunctionTable["powf"] = "native_powr";
                fFunctionTable["sqrt"] = "native_sqrt";
                fFunctionTable["sqrtf"] = "native_sqrt";
                fFunctionTable["fabsf"] = "fabs";
            }
            
            virtual void tab1(int n, ostream& fout)
            {
                fout << "  \\n\"  \\\n";
                fout << "\"";
                while (n--) fout << '\t';
            }
            
            bool IsControl(NamedAddress* named)
            {
                return (named->getName().find("fbutton") != string::npos
                    || named->getName().find("fcheckbox") != string::npos
                    || named->getName().find("fvbargraph") != string::npos
                    || named->getName().find("fhbargraph") != string::npos
                    || named->getName().find("fvslider") != string::npos
                    || named->getName().find("fhslider") != string::npos
                    || named->getName().find("fentry") != string::npos);
            }
            
            bool IsControl(IndexedAddress* indexed)
            {
                return (indexed->getName().find("fbutton") != string::npos
                    || indexed->getName().find("fvbargraph") != string::npos
                    || indexed->getName().find("fhbargraph") != string::npos
                    || indexed->getName().find("fcheckbox") != string::npos
                    || indexed->getName().find("fvslider") != string::npos
                    || indexed->getName().find("fhslider") != string::npos
                    || indexed->getName().find("fentry") != string::npos);
            }

            virtual void visit(LoadVarInst* inst) 
            {
                NamedAddress* named = dynamic_cast< NamedAddress*>(inst->fAddress);
                IndexedAddress* indexed = dynamic_cast< IndexedAddress*>(inst->fAddress);
                
                // Special treatment for "fSamplingFreq" variable
                if (named && named->getName() == "fSamplingFreq")
                    named->setAccess(Address::kStruct);
                
                if (named) {
                    if (named->getAccess() == Address::kStruct)
                        *fOut << (IsControl(named) ? "control->" : "dsp->") << named->getName();
                    else
                        *fOut << named->getName();
                } else {
                    if (indexed->getAccess() == Address::kStruct)
                        *fOut << (IsControl(indexed) ? "control->" : "dsp->") << indexed->getName() << "[";
                    else
                        *fOut << indexed->getName() << "[";
                    indexed->fIndex->accept(this);
                    *fOut << "]"; 
                }
            }

            virtual void visit(StoreVarInst* inst)
            {   
                NamedAddress* named = dynamic_cast< NamedAddress*>(inst->fAddress);
                IndexedAddress* indexed = dynamic_cast< IndexedAddress*>(inst->fAddress);
                
                // Special treatment for "fSamplingFreq" variable
                if (named && named->getName() == "fSamplingFreq")
                    named->setAccess(Address::kStruct);
                
                if (named) {
                    if (named->getAccess() == Address::kStruct)
                        *fOut << (IsControl(named) ? "control->" : "dsp->")  << named->getName() << " = ";
                    else
                        *fOut << named->getName() << " = ";
                } else {
                    if (indexed->getAccess() == Address::kStruct)
                        *fOut << (IsControl(indexed) ? "control->" : "dsp->") << indexed->getName() << "[";
                    else
                        *fOut << indexed->getName() << "[";
                    indexed->fIndex->accept(this);
                    *fOut << "] = "; 
                }
                inst->fValue->accept(this);
                EndLine();
            }
            
            virtual void visit(FunCallInst* inst)
            {
                if (inst->fMethod) {
                    list<ValueInst*>::const_iterator it =  inst->fArgs.begin();
                    // Compile object arg
                    (*it)->accept(this); 
                    *fOut << "->" << ((fFunctionTable.find(inst->fName) != fFunctionTable.end()) ? fFunctionTable[inst->fName]: inst->fName) << "(";
                    list<ValueInst*>::const_iterator it1; 
                    int size = inst->fArgs.size() - 1, i = 0;
                    for (it1 = ++it; it1 != inst->fArgs.end(); it1++, i++) {
                        // Compile argument
                        (*it1)->accept(this); 
                        if (i < size - 1) *fOut << ", ";
                    }
                    *fOut << ")";
              } else {
                    *fOut << ((fFunctionTable.find(inst->fName) != fFunctionTable.end()) ? fFunctionTable[inst->fName] : inst->fName) << "(";
                    list<ValueInst*>::const_iterator it;
                    int size = inst->fArgs.size(), i = 0;
                    for (it = inst->fArgs.begin(); it != inst->fArgs.end(); it++, i++) {
                        // Compile argument
                        (*it)->accept(this); 
                        if (i < size - 1) *fOut << ", ";
                    }
                    *fOut << ")";
                }
            }
          
        };
    
        KernelInstVisitor* fKernelCodeProducer;
        std::ostringstream* fGPUOut;
     
    public:
    
        CPPOpenCLCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
            :CPPCodeContainer(name, super, numInputs, numOutputs, out)
        {
            fGPUOut = new std::ostringstream();
            fKernelCodeProducer = new KernelInstVisitor(fGPUOut, 0);
        }
        virtual ~CPPOpenCLCodeContainer()
        {
            delete fGPUOut;
            delete fKernelCodeProducer;
        }
        
        virtual void produceClass();
        void produceInternal();
        
        void generateCompute(int n);
        virtual void generateComputeKernel(int n);
             
};

class CPPOpenCLVectorCodeContainer : public CPPOpenCLCodeContainer {

    public:
    
        CPPOpenCLVectorCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
            :CPPOpenCLCodeContainer(name, super, numInputs, numOutputs, out)
        {}
        
        void generateComputeKernel(int n);
};

#endif
