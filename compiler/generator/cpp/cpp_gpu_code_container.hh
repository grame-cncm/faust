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

#ifndef _CPP_GPU_CODE_CONTAINER_H
#define _CPP_GPU_CODE_CONTAINER_H

#include "cpp_code_container.hh"
#include "global.hh"

class CPPGPUCodeContainer : public CPPCodeContainer {

        void prepareFIR(void);

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
                *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << "&fHostControl->" << inst->fZone << ", " << checkReal(inst->fInit) << ", " << checkReal(inst->fMin) << ", " << checkReal(inst->fMax) << ", " << checkReal(inst->fStep) << ")";
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
                *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << "&fHostControl->" << inst->fZone << ", "<< checkReal(inst->fMin) << ", " << checkReal(inst->fMax) << ")";
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
                if (!isControl(inst->fAddress->getName())) {
                    tab(fTab, *fOut); *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName()) << ";";
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
                if (isControl(inst->fAddress->getName())) {
                    tab(fTab, *fOut); *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName()) << ";";
                }
            }

        };

        // Control fields are preceded with "control->"
        // Non-control fields are preceded with "dsp->"
        struct KernelInstVisitor : public CPPInstVisitor {
			
			using CPPInstVisitor::visit;

            map < string, string> fFunctionTable;
            KernelInstVisitor(std::ostream* out, int tab)
                :CPPInstVisitor(out, tab)
            {}

            virtual void visit(LoadVarInst* inst)
            {
                NamedAddress* named = dynamic_cast< NamedAddress*>(inst->fAddress);
                IndexedAddress* indexed = dynamic_cast< IndexedAddress*>(inst->fAddress);

                // Special treatment for "fSamplingFreq" variable
                if (named && named->getName() == "fSamplingFreq") {
                    named->setAccess(Address::kStruct);
                }

                if (named) {
                    if (named->getAccess() == Address::kStruct) {
                        *fOut << (isControl(named->getName()) ? "control->" : "dsp->") << named->getName();
                    } else {
                        *fOut << named->getName();
                    }
                } else {
                    if (indexed->getAccess() == Address::kStruct) {
                        *fOut << (isControl(indexed->getName()) ? "control->" : "dsp->") << indexed->getName() << "[";
                    } else {
                        *fOut << indexed->getName() << "[";
                    }
                    indexed->fIndex->accept(this);
                    *fOut << "]";
                }
            }

            virtual void visit(LoadVarAddressInst* inst)
            {
                NamedAddress* named = dynamic_cast< NamedAddress*>(inst->fAddress);
                IndexedAddress* indexed = dynamic_cast< IndexedAddress*>(inst->fAddress);

                // Special treatment for "fSamplingFreq" variable
                if (named && named->getName() == "fSamplingFreq") {
                    named->setAccess(Address::kStruct);
                }

                if (named) {
                    if (named->getAccess() == Address::kStruct) {
                        *fOut << (isControl(named->getName()) ? "&control->" : "&dsp->") << named->getName();
                    } else {
                        *fOut << "&" << named->getName();
                    }
                } else {
                    if (indexed->getAccess() == Address::kStruct) {
                        *fOut << (isControl(indexed->getName()) ? "&control->" : "&dsp->") << indexed->getName() << "[";
                    } else {
                        *fOut << "&" << indexed->getName() << "[";
                    }
                    indexed->fIndex->accept(this);
                    *fOut << "]";
                }
            }

            virtual void visit(StoreVarInst* inst)
            {
                NamedAddress* named = dynamic_cast< NamedAddress*>(inst->fAddress);
                IndexedAddress* indexed = dynamic_cast< IndexedAddress*>(inst->fAddress);

                // Special treatment for "fSamplingFreq" variable
                if (named && named->getName() == "fSamplingFreq") {
                    named->setAccess(Address::kStruct);
                }

                if (named) {
                    if (named->getAccess() == Address::kStruct) {
                        *fOut << (isControl(named->getName()) ? "control->" : "dsp->")  << named->getName() << " = ";
                    } else {
                        *fOut << named->getName() << " = ";
                    }
                } else {
                    if (indexed->getAccess() == Address::kStruct) {
                        *fOut << (isControl(indexed->getName()) ? "control->" : "dsp->") << indexed->getName() << "[";
                    } else {
                        *fOut << indexed->getName() << "[";
                    }
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
                    *fOut << "->" << ((fFunctionTable.find(inst->fName) != fFunctionTable.end()) ? fFunctionTable[inst->fName] : inst->fName) << "(";
                    list<ValueInst*>::const_iterator it1;
                    size_t size = inst->fArgs.size() - 1, i = 0;
                    for (it1 = ++it; it1 != inst->fArgs.end(); it1++, i++) {
                        // Compile argument
                        (*it1)->accept(this);
                        if (i < size - 1) *fOut << ", ";
                    }
                    *fOut << ")";
              } else {
                    *fOut << ((fFunctionTable.find(inst->fName) != fFunctionTable.end()) ? fFunctionTable[inst->fName] : inst->fName) << "(";
                    list<ValueInst*>::const_iterator it;
                    size_t size = inst->fArgs.size(), i = 0;
                    for (it = inst->fArgs.begin(); it != inst->fArgs.end(); it++, i++) {
                        // Compile argument
                        (*it)->accept(this);
                        if (i < size - 1) *fOut << ", ";
                    }
                    *fOut << ")";
                }
            }

            // C like cast
            virtual void visit(CastInst* inst)
            {
                *fOut << "(" << fTypeManager->generateType(inst->fType) << ")";
                inst->fInst->accept(this);
            }

        };

        KernelInstVisitor* fKernelCodeProducer;
        std::ostream* fGPUOut;

    public:

        CPPGPUCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
            :CPPCodeContainer(name, super, numInputs, numOutputs, out)
        {
            fNumInputs = numInputs;
            fNumOutputs = numOutputs;
            fInputRates.resize(numInputs);
            fOutputRates.resize(numOutputs);
        }

        virtual ~CPPGPUCodeContainer()
        {}

};

class CPPOpenCLCodeContainer : public CPPGPUCodeContainer {

      protected:

        struct OpenCLKernelInstVisitor : public KernelInstVisitor {

            // Code will be generated as a string
            virtual void tab1(int n, ostream& fout)
            {
                fout << "  \\n\"  \\\n";
                fout << "\"";
                while (n--) fout << '\t';
            }

            OpenCLKernelInstVisitor(std::ostream* out, int tab)
                :KernelInstVisitor(out, tab)
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
        };

        // To be used when generating GPU kernel string
        struct ControlOpenCLInstVisitor : public ControlInstVisitor {

            // Code will be generated as a string
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

            // Code will be generated as a string
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

        // Add __local keyword for stack variables
        struct BlockKernelInstVisitor : public KernelInstVisitor {
			using KernelInstVisitor::visit;

            // Code will be generated as a string
            virtual void tab1(int n, ostream& fout)
            {
                fout << "  \\n\"  \\\n";
                fout << "\"";
                while (n--) fout << '\t';
            }

            BlockKernelInstVisitor(std::ostream* out, int tab)
                :KernelInstVisitor(out, tab)
            {}

            virtual void visit(DeclareVarInst* inst)
            {
                /*
                if (inst->fAddress->getAccess() & Address::kGlobal) {
                    if (gGlobal->gSymbolGlobalsTable.find(inst->fAddress->getName()) == gGlobal->gSymbolGlobalsTable.end()) {
                        // If global is not defined
                        gGlobal->gSymbolGlobalsTable[inst->fAddress->getName()] = 1;
                    } else {
                        return;
                    }
                }
                */

                if (inst->fAddress->getAccess() & Address::kStaticStruct) {
                     *fOut << "static ";
                }

                if (inst->fAddress->getAccess() & Address::kVolatile) {
                     *fOut << "volatile ";
                }

                if (inst->fAddress->getAccess() & Address::kStack) {
                     *fOut << "__local ";
                }

                *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
                if (inst->fValue) {
                    *fOut << " = "; inst->fValue->accept(this);
                } 
                EndLine();
            }

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

        // Add __shared__ keyword for stack variables
        struct BlockKernelInstVisitor : public KernelInstVisitor {
			using KernelInstVisitor::visit;

            BlockKernelInstVisitor(std::ostream* out, int tab)
                :KernelInstVisitor(out, tab)
            {}

            virtual void visit(DeclareVarInst* inst)
            {
                if (inst->fAddress->getAccess() & Address::kStaticStruct) {
                    *fOut << "static ";
                }

                if (inst->fAddress->getAccess() & Address::kVolatile) {
                    *fOut << "volatile ";
                }

                if (inst->fAddress->getAccess() & Address::kStack) {
                    *fOut << "__shared__ ";
                }

                *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
                if (inst->fValue) {
                    *fOut << " = "; inst->fValue->accept(this);
                } 
                EndLine();
            }

        };

    public:

        CPPCUDACodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
             :CPPGPUCodeContainer(name, super, numInputs, numOutputs, out)
        {
            string filename = gGlobal->gOutputFile + ".cu";
            fGPUOut = new std::ofstream(filename.c_str());
            fKernelCodeProducer = new CUDAKernelInstVisitor(fGPUOut, 0);
            fNumInputs = numInputs;
            fNumOutputs = numOutputs;
            fInputRates.resize(numInputs);
            fOutputRates.resize(numOutputs);
        }
        virtual ~CPPCUDACodeContainer()
        {
            delete fGPUOut;
        }

        void produceClass();
        void generateCompute(int tab);
        void produceInternal();

        virtual void generateComputeKernelGlue(int n);
        virtual void generateInstanceInitKernelGlue(int n);
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

        void generateComputeKernelGlue(int n);
        void generateInstanceInitKernelGlue(int n);
        void generateComputeKernel(int n);

};

#endif
