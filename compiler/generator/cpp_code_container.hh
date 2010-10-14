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

class CPPGPUCodeContainer : public CPPCodeContainer {

    protected:
    
        static bool isControl(string name)
        {
            return (name.find("fbutton") != string::npos
                || name.find("fcheckbox") != string::npos
                || name.find("fvbargraph") != string::npos
                || name.find("fhbargraph") != string::npos
                || name.find("fvslider") != string::npos
                || name.find("fhslider") != string::npos
                || name.find("fentry") != string::npos);
        }
        
        // To access control inside fControl field
        struct UIInstVisitor : public CPPInstVisitor {
    
            UIInstVisitor(std::ostream* out, int tab)
                :CPPInstVisitor(out, tab)
            {}
            
            virtual void visit(AddMetaDeclareInst* inst) 
            {
                *fOut << "interface->declare(" << "&fHostControl->" << inst->fZone <<", " << "\"" <<inst->fKey << "\"" << ", " <<  "\"" << inst->fValue << "\"" << ")"; EndLine();
            }
            
            virtual void visit(AddButtonInst* inst) 
            {
                if (inst->fType == AddButtonInst::kDefaultButton) {
                    *fOut << "interface->addButton(" << "\"" << inst->fLabel << "\"" << "," << "&fHostControl->" << inst->fZone << ")"; EndLine();
                } else {
                    *fOut << "interface->addCheckButton(" << "\"" << inst->fLabel << "\"" << "," << "&fHostControl->" << inst->fZone << ")"; EndLine();
                }
            }

            virtual void visit(AddSliderInst* inst) 
            {
                string name;
                switch (inst->fType) {
                    case AddSliderInst::kHorizontal:
                        name = "interface->addHorizontalSlider"; break;
                    case AddSliderInst::kVertical:
                        name = "interface->addVerticalSlider"; break;
                    case AddSliderInst::kNumEntry:
                        name = "interface->addNumEntry"; break;
                } 
                if (strcmp(ifloat(), "float") == 0)    
                    *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << "&fHostControl->" << inst->fZone << ", " << checkFloat(inst->fInit) << ", " << checkFloat(inst->fMin) << ", " << checkFloat(inst->fMax) << ", " << checkFloat(inst->fStep) << ")";
                else
                    *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << "&fHostControl->" << inst->fZone << ", " << inst->fInit << ", " << inst->fMin << ", " << inst->fMax << ", " << inst->fStep << ")";
                EndLine();  
            }
            
            virtual void visit(AddBargraphInst* inst) 
            {
                string name;
                switch (inst->fType) {
                    case AddBargraphInst::kHorizontal:
                        name = "interface->addHorizontalBargraph"; break;
                    case AddBargraphInst::kVertical:
                        name = "interface->addVerticalBargraph"; break;
                }     
                if (strcmp(ifloat(), "float") == 0)
                    *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << "&fHostControl->" << inst->fZone << ", "<< checkFloat(inst->fMin) << ", " << checkFloat(inst->fMax) << ")"; 
                else
                    *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << "&fHostControl->" << inst->fZone << ", "<< inst->fMin << ", " << inst->fMax << ")"; 
                EndLine();       
            }                    
        };

        // Visitor that only generates non-control fields
        struct DSPInstVisitor : public CPPInstVisitor {
           
            DSPInstVisitor(std::ostream* out, int tab)
                :CPPInstVisitor(out, tab)
            {}
         
            virtual void visit(DeclareVarInst* inst) 
            {
                if (!isControl(inst->fName)) {
                    tab1(fTab, *fOut); *fOut << generateType(inst->fTyped, inst->fName) << ";";
                }
            }
        };
        
        // Visitor that only generates control fields
        struct ControlInstVisitor : public CPPInstVisitor {
            
            ControlInstVisitor(std::ostream* out, int tab)
                :CPPInstVisitor(out, tab)
            {}
      
            virtual void visit(DeclareVarInst* inst) 
            {
                if (isControl(inst->fName)) {                    
                    tab1(fTab, *fOut); *fOut << generateType(inst->fTyped, inst->fName) << ";";
                }
            }
            
        };
        

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
                fFunctionTable["floorf"] = "floor";
                fFunctionTable["fmodf"] = "fmod";
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
                        *fOut << (isControl(named->getName()) ? "control->" : "dsp->") << named->getName();
                    else
                        *fOut << named->getName();
                } else {
                    if (indexed->getAccess() == Address::kStruct)
                        *fOut << (isControl(indexed->getName()) ? "control->" : "dsp->") << indexed->getName() << "[";
                    else
                        *fOut << indexed->getName() << "[";
                    indexed->fIndex->accept(this);
                    *fOut << "]"; 
                }
            }
            
            virtual void visit(LoadVarAddressInst* inst) 
            {
                NamedAddress* named = dynamic_cast< NamedAddress*>(inst->fAddress);
                IndexedAddress* indexed = dynamic_cast< IndexedAddress*>(inst->fAddress);
                
                // Special treatment for "fSamplingFreq" variable
                if (named && named->getName() == "fSamplingFreq")
                    named->setAccess(Address::kStruct);
                
                if (named) {
                    if (named->getAccess() == Address::kStruct)
                        *fOut << (isControl(named->getName()) ? "&control->" : "&dsp->") << named->getName();
                    else
                        *fOut << "&" << named->getName();
                } else {
                    if (indexed->getAccess() == Address::kStruct)
                        *fOut << (isControl(indexed->getName()) ? "&control->" : "&dsp->") << indexed->getName() << "[";
                    else
                        *fOut << "&" << indexed->getName() << "[";
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
                        *fOut << (isControl(named->getName()) ? "control->" : "dsp->")  << named->getName() << " = ";
                    else
                        *fOut << named->getName() << " = ";
                } else {
                    if (indexed->getAccess() == Address::kStruct)
                        *fOut << (isControl(indexed->getName()) ? "control->" : "dsp->") << indexed->getName() << "[";
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
    
        // Add __local keyword for stack variables
        struct BlockKernelInstVisitor : public KernelInstVisitor {
        
            BlockKernelInstVisitor(std::ostream* out, int tab)
                :KernelInstVisitor(out, tab)
            {}
            
            virtual void visit(DeclareVarInst* inst) 
            {   
                if (inst->fAccess & Address::kGlobal) {
                    if (fGlobalTable.find(inst->fName) == fGlobalTable.end()) {
                        // If global is not defined
                        fGlobalTable[inst->fName] = 1;
                    } else {
                        return;
                    }
                }
                
                if (inst->fAccess & Address::kStaticStruct) {
                     *fOut << "static ";
                }
                
                if (inst->fAccess & Address::kVolatile) {
                     *fOut << "volatile ";
                }
                
                if (inst->fAccess & Address::kStack) {
                     *fOut << "__local ";
                }
                
                if (inst->fValue) {
                    *fOut << generateType(inst->fTyped, inst->fName) << " = "; inst->fValue->accept(this); EndLine();
                } else {
                    *fOut << generateType(inst->fTyped, inst->fName); EndLine();
                }
            }

        };
        
        KernelInstVisitor* fKernelCodeProducer;
        std::ostringstream* fGPUOut;
        
    public:
    
        CPPGPUCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
            :CPPCodeContainer(name, super, numInputs, numOutputs, out)
        {}
        
        virtual ~CPPGPUCodeContainer()
        {}
 
};

class CPPOpenCLCodeContainer : public CPPGPUCodeContainer {

      protected:
      
        struct OpenCLKernelInstVisitor : public KernelInstVisitor {
        
            virtual void tab1(int n, ostream& fout)
            {
                fout << "  \\n\"  \\\n";
                fout << "\"";
                while (n--) fout << '\t';
            }
            
            OpenCLKernelInstVisitor(std::ostream* out, int tab)
                :KernelInstVisitor(out, tab)
            {}
        };
        
        // To be used when generating GPU kernel string
        struct ControlOpenCLInstVisitor : public ControlInstVisitor {
        
            virtual void tab1(int n, ostream& fout)
            {
                fout << "  \\n\"  \\\n";
                fout << "\"";
                while (n--) fout << '\t';
            }
            
            ControlOpenCLInstVisitor(std::ostream* out, int tab)
                :ControlInstVisitor(out, tab)
            {}
        };
         
        // To be used when generating GPU kernel string
        struct DSPOpenCLInstVisitor : public DSPInstVisitor {
        
            virtual void tab1(int n, ostream& fout)
            {
                fout << "  \\n\"  \\\n";
                fout << "\"";
                while (n--) fout << '\t';
            }
            
            DSPOpenCLInstVisitor(std::ostream* out, int tab)
                :DSPInstVisitor(out, tab)
            {}
        };
        
    public:
    
        CPPOpenCLCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
            :CPPGPUCodeContainer(name, super, numInputs, numOutputs, out)
        {
            fGPUOut = new std::ostringstream();
            fKernelCodeProducer = new OpenCLKernelInstVisitor(fGPUOut, 0);
        }
        virtual ~CPPOpenCLCodeContainer()
        {
            delete fGPUOut;
            delete fKernelCodeProducer;
        }
        
        void produceClass();
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

class CPPCUDACodeContainer : public CPPGPUCodeContainer {

    protected:

        struct CUDAKernelInstVisitor : public KernelInstVisitor {
        
            CUDAKernelInstVisitor(std::ostream* out, int tab)
                :KernelInstVisitor(out, tab)
            {}

        };

    public:

        CPPCUDACodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
             :CPPGPUCodeContainer(name, super, numInputs, numOutputs, out)
        {
            fGPUOut = new std::ostringstream();
            fKernelCodeProducer = new CUDAKernelInstVisitor(fGPUOut, 0);
        }
        virtual ~CPPCUDACodeContainer()
        {
            delete fGPUOut;
            delete fKernelCodeProducer;
        }
     
        void produceClass();
        void generateCompute(int tab);
        void produceInternal();
        
        virtual void generateComputeKernel(int n);

};

class CPPCUDAVectorCodeContainer : public CPPCUDACodeContainer {

    protected:


    public:

        CPPCUDAVectorCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
             :CPPCUDACodeContainer(name, super, numInputs, numOutputs, out)
        {}
        virtual ~CPPCUDAVectorCodeContainer()
        {}
     
        void produceClass() {}
        void generateCompute(int tab) {}
        void produceInternal() {}
        
        void generateComputeKernel(int n) {}

};



#endif
