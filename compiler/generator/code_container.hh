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

#ifndef _CODE_CONTAINER_H
#define _CODE_CONTAINER_H

#include <string>

#include "instructions.hh"
#include "sigtype.hh"
#include "tlib.hh"
#include "description.hh"
#include "floats.hh"
#include "Text.hh"
#include "property.hh"
#include "fir_function_builder.hh"
#include "code_loop.hh"
#include "garbageable.hh"
#include "json_instructions.hh"
#include "dsp_factory.hh"
#include "export.hh"

class TextInstVisitor;

class CodeContainer : public virtual Garbageable {

    protected:

        list <CodeContainer*> fSubContainers;
        CodeContainer* fParentContainer;     ///< Container in which this Container is embedded, null if toplevel Container

        int fNumInputs;
        int fNumOutputs;
    
        int fNumActives;       ///< number of active controls in the UI (sliders, buttons, etc.)
        int fNumPassives;      ///< number of passive widgets in the UI (bargraphs, etc.)
 
        string fKlassName;
    
        vector<int> fInputRates;
        vector<int> fOutputRates;

        // Declaration part
        BlockInst* fExtGlobalDeclarationInstructions;
        BlockInst* fGlobalDeclarationInstructions;
        BlockInst* fDeclarationInstructions;

        // Init method
        BlockInst* fInitInstructions;
        BlockInst* fResetUserInterfaceInstructions;
        BlockInst* fClearInstructions;
        BlockInst* fPostInitInstructions;

        // To be used in allocate method (or constructor)
        BlockInst* fAllocateInstructions;
        
        // To be used in delete method
        BlockInst* fDestroyInstructions;

        // Static init method
        BlockInst* fStaticInitInstructions;
        BlockInst* fPostStaticInitInstructions;
    
        // Static destroy method
        BlockInst* fStaticDestroyInstructions;

        // Compute method
        BlockInst* fComputeBlockInstructions;

        // Additionnal functions
        BlockInst* fComputeFunctions;

        // User interface
        BlockInst* fUserInterfaceInstructions;

        set<string>	fIncludeFileSet;
        set<string>	fLibrarySet;

        // DAG of loops
        CodeLoop* fCurLoop;

        property<CodeLoop*> fLoopProperty;     ///< loops used to compute some signals

        list<string> fUICode;
        list<string> fUIMacro;

        int fSubContainerType;
        string fFullCount;
        
        bool fGeneratedSR;
  
        void merge(set<string>& dst, set<string>& src)
        {
            set<string>::iterator i;
            for (i = src.begin(); i != src.end(); i++) dst.insert(*i);
        }

        void collectIncludeFile(set<string>& S)
        {
            list<CodeContainer* >::iterator k;
            for (k = fSubContainers.begin(); k != fSubContainers.end(); k++) (*k)->collectIncludeFile(S);
            merge(S, fIncludeFileSet);
        }

        void collectLibrary(set<string>& S)
        {
            list<CodeContainer* >::iterator k;
            for (k = fSubContainers.begin(); k != fSubContainers.end(); k++) (*k)->collectLibrary(S);
            merge(S, fLibrarySet);
        }

        void generateDAGLoopAux(CodeLoop* loop, BlockInst* loop_code, DeclareVarInst* count, int loop_num, bool omp = false);
        void generateDAGLoopInternal(CodeLoop* loop, BlockInst* block, DeclareVarInst* count, bool omp);

        void printHeader(ostream& dst)
        {
            // defines the metadata we want to print as comments at the begin of in the file
            set<Tree> selectedKeys;
            selectedKeys.insert(tree("name"));
            selectedKeys.insert(tree("author"));
            selectedKeys.insert(tree("copyright"));
            selectedKeys.insert(tree("license"));
            selectedKeys.insert(tree("version"));
            
            dst << "/* ------------------------------------------------------------" << endl;
            for (MetaDataSet::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
                if (selectedKeys.count(i->first)) {
                    dst << *(i->first);
                    const char* sep = ": ";
                    for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); ++j) {
                        dst << sep << **j;
                        sep = ", ";
                    }
                    dst << endl;
                }
            }
            
            dst << "Code generated with Faust " << FAUSTVERSION << " (https://faust.grame.fr)" << endl;
            dst << "Compilation options: ";
            gGlobal->printCompilationOptions(dst);
            dst << "\n------------------------------------------------------------ */" << endl;
        }
    
        virtual void generateSR()
        {
            if (!fGeneratedSR) {
                pushDeclare(InstBuilder::genDecStructVar("fSamplingFreq", InstBuilder::genBasicTyped(Typed::kInt32)));
            }
            pushFrontInitMethod(InstBuilder::genStoreStructVar("fSamplingFreq", InstBuilder::genLoadFunArgsVar("samplingFreq")));
        }
    
        BlockInst* inlineSubcontainersFunCalls(BlockInst* block);
    
    public:

        CodeContainer();
        void initializeCodeContainer(int numInputs, int numOutputs);
        virtual ~CodeContainer();

        CodeLoop* getCurLoop() { return fCurLoop; }
        
        void setParentContainers(CodeContainer* parent)  { fParentContainer = parent; }
        CodeContainer* getParentContainer()              { return fParentContainer; }
        CodeContainer* getTopParentContainer()           { return (fParentContainer != 0) ? fParentContainer->getTopParentContainer() : this; }
 
        // Returns the name of the class
        string getFullClassName()
        {
            return (fParentContainer != 0)
                    ? fParentContainer->getFullClassName() + "::" + getClassName()
                    : getClassName();
        }

        void setGeneratedSR()
        {
            fGeneratedSR = true;
        }
     
        void openLoop(string index_name, int size = 0);
        void openLoop(Tree recsymbol, string index_name, int size = 0);
        void closeLoop(Tree sig);

        int	inputs() 	{ return fNumInputs; }
        int outputs()	{ return fNumOutputs; }

        void setInputs(int inputs)      { fNumInputs = inputs; }
        void setOutputs(int outputs)    { fNumOutputs = outputs; }

        void setInputRate(int channel, int rate) { fInputRates[channel] = rate; }
        void setOutputRate(int channel, int rate) { fOutputRates[channel] = rate; }

        int getInputRate(int channel) { return fInputRates[channel]; }
        int getOutputRate(int channel) { return fOutputRates[channel]; }

        void addSubContainer(CodeContainer* container) { fSubContainers.push_back(container); }

        void addIncludeFile(const string& str)  { fIncludeFileSet.insert(str); }
        void addLibrary(const string& str)      { fLibrarySet.insert(str); }

        void printLibrary(ostream& fout);
        void printIncludeFile(ostream& fout);

        void setLoopProperty(Tree sig, CodeLoop* l);     ///< Store the loop used to compute a signal
        bool getLoopProperty(Tree sig, CodeLoop*& l);    ///< Returns the loop used to compute a signal

        void printGraphDotFormat(ostream& fout);

        void transformDAG(DispatchVisitor* visitor);
        void computeForwardDAG(lclgraph dag, int& loop_count, vector<int>& ready_loop);
        void sortDeepFirstDAG(CodeLoop* l, set<CodeLoop*>& visited, list<CodeLoop*>& result);

        void generateLocalInputs(BlockInst* loop_code, const string& index);
        void generateLocalOutputs(BlockInst* loop_code, const string& index);

        DeclareFunInst* generateGetIO(const string& name, const string& obj, int io, bool ismethod, bool isvirtual);
        DeclareFunInst* generateGetInputs(const string& name, const string& obj, bool ismethod, bool isvirtual);
        DeclareFunInst* generateGetOutputs(const string& name, const string& obj, bool ismethod, bool isvirtual);

        DeclareFunInst* generateGetIORate(const string& name, const string& obj, vector<int>& io, bool ismethod, bool isvirtual);
        DeclareFunInst* generateGetInputRate(const string& name, const string& obj, bool ismethod, bool isvirtual);
        DeclareFunInst* generateGetOutputRate(const string& name, const string& obj, bool ismethod, bool isvirtual);
    
        virtual DeclareFunInst* generateClassInit(const string& name) { faustassert(false); return nullptr; }
        virtual DeclareFunInst* generateInstanceClear(const string& name, const string& obj, bool ismethod, bool isvirtual) { faustassert(false); return nullptr; }
        virtual DeclareFunInst* generateInstanceConstants(const string& name, const string& obj, bool ismethod, bool isvirtual) { faustassert(false); return nullptr; }
        virtual DeclareFunInst* generateInstanceResetUserInterface(const string& name, const string& obj, bool ismethod, bool isvirtual) { faustassert(false); return nullptr; }
    
        virtual DeclareFunInst* generateStaticInitFun(const string& name, bool isstatic, bool addreturn = false);
        virtual DeclareFunInst* generateInstanceInitFun(const string& name, const string& obj, bool ismethod, bool isvirtual, bool addreturn = false);
        virtual DeclareFunInst* generateFillFun(const string& name, const string& obj, bool ismethod, bool isvirtual, bool addreturn = false);
    
        DeclareFunInst* generateInit(const string& obj, bool ismethod, bool isvirtual);
        DeclareFunInst* generateInstanceInit(const string& obj, bool ismethod, bool isvirtual);
        DeclareFunInst* generateGetSampleRate(const string& obj, bool ismethod, bool isvirtual);
   
        void produceInfoFunctions(int tabs, const string& classname, const string& obj, bool ismethod, bool isvirtual, TextInstVisitor* producer);
    
        void generateDAGLoop(BlockInst* loop_code, DeclareVarInst* count);
        
        void generateJSONFile();
        void generateMetaData(JSONUI* json);
        void generateJSON(JSONInstVisitor* visitor);
    
        /* can be overridden by subclasses to reorder the FIR before the actual code generation */
        virtual void processFIR(void);
        
        virtual BlockInst* flattenFIR(void);

        // Fill code for each method
        StatementInst* pushDeclare(StatementInst* inst)
        {
            fDeclarationInstructions->pushBackInst(inst);
            // TODO : add inter-loop vectors in current loop
            return inst;
        }

        StatementInst* pushGlobalDeclare(StatementInst* inst)
        {
            fGlobalDeclarationInstructions->pushBackInst(inst);
            return inst;
        }

        StatementInst* pushExtGlobalDeclare(StatementInst* inst)
        {
            fExtGlobalDeclarationInstructions->pushBackInst(inst);
            return inst;
        }

        ValueInst* pushFunction(const string& name, Typed::VarType result, vector<Typed::VarType>& types, const list<ValueInst*>& args);

        void generateExtGlobalDeclarations(InstVisitor* visitor)
        {
            if (fExtGlobalDeclarationInstructions->fCode.size() > 0) {
                fExtGlobalDeclarationInstructions->accept(visitor);
            }
        }

        void generateGlobalDeclarations(InstVisitor* visitor)
        {
            if (fGlobalDeclarationInstructions->fCode.size() > 0) {
                fGlobalDeclarationInstructions->accept(visitor);
            }
        }

        void generateDeclarations(InstVisitor* visitor)
        {
            if (fDeclarationInstructions->fCode.size() > 0) {
                fDeclarationInstructions->accept(visitor);
            }
        }
   
        void generateInit(InstVisitor* visitor)
        {
            if (fInitInstructions->fCode.size() > 0) {
                fInitInstructions->accept(visitor);
            }

            if (fPostInitInstructions->fCode.size() > 0) {
                fPostInitInstructions->accept(visitor);
            }
        }
    
        void generateResetUserInterface(InstVisitor* visitor)
        {
            if (fResetUserInterfaceInstructions->fCode.size() > 0) {
                fResetUserInterfaceInstructions->accept(visitor);
            }
        }
    
        void generateClear(InstVisitor* visitor)
        {
            if (fClearInstructions->fCode.size() > 0) {
                fClearInstructions->accept(visitor);
            }
        }

        void generateStaticInit(InstVisitor* visitor)
        {
            if (fStaticInitInstructions->fCode.size() > 0) {
                fStaticInitInstructions->accept(visitor);
            }

            if (fPostStaticInitInstructions->fCode.size() > 0) {
                fPostStaticInitInstructions->accept(visitor);
            }
        }
    
        void generateStaticDestroy(InstVisitor* visitor)
        {
            if (fStaticDestroyInstructions->fCode.size() > 0) {
                fStaticDestroyInstructions->accept(visitor);
            }
        }

        void generateUserInterface(InstVisitor* visitor)
        {
            if (fUserInterfaceInstructions->fCode.size() > 0) {
                fUserInterfaceInstructions->accept(visitor);
            }
        }

        void generateComputeFunctions(InstVisitor* visitor)
        {
            if (fComputeFunctions->fCode.size() > 0) {
                fComputeFunctions->accept(visitor);
            }
        }

        void generateComputeBlock(InstVisitor* visitor)
        {
            if (fComputeBlockInstructions->fCode.size() > 0) {
                fComputeBlockInstructions->accept(visitor);
            }
        }
    
        void generateAllocate(InstVisitor* visitor)
        {
            if (fAllocateInstructions->fCode.size() > 0) {
                fAllocateInstructions->accept(visitor);
            }
        }

        void generateDestroy(InstVisitor* visitor)
        {
            if (fDestroyInstructions->fCode.size() > 0) {
                fDestroyInstructions->accept(visitor);
            }
        }

        StatementInst* pushInitMethod(StatementInst* inst) { fInitInstructions->pushBackInst(inst); return inst; }
        StatementInst* pushClearMethod(StatementInst* inst) { fClearInstructions->pushBackInst(inst); return inst; }
        StatementInst* pushResetUIInstructions(StatementInst* inst) { fResetUserInterfaceInstructions->pushBackInst(inst); return inst; }
        StatementInst* pushPostInitMethod(StatementInst* inst) { fPostInitInstructions->pushBackInst(inst); return inst; }
        StatementInst* pushFrontInitMethod(StatementInst* inst) { fInitInstructions->pushFrontInst(inst); return inst; }
        StatementInst* pushAllocateMethod(StatementInst* inst) { fAllocateInstructions->pushBackInst(inst); return inst; }
        StatementInst* pushDestroyMethod(StatementInst* inst) { fDestroyInstructions->pushBackInst(inst); return inst; }
        StatementInst* pushStaticInitMethod(StatementInst* inst) { fStaticInitInstructions->pushBackInst(inst); return inst; }
        StatementInst* pushStaticDestroyMethod(StatementInst* inst) { fStaticDestroyInstructions->pushBackInst(inst); return inst; }
        StatementInst* pushPostStaticInitMethod(StatementInst* inst) { fPostStaticInitInstructions->pushBackInst(inst); return inst; }
        StatementInst* pushComputeBlockMethod(StatementInst* inst) { fComputeBlockInstructions->pushBackInst(inst); return inst; }
        StatementInst* pushUserInterfaceMethod(StatementInst* inst) { fUserInterfaceInstructions->pushBackInst(inst); return inst; }
        StatementInst* pushOtherComputeMethod(StatementInst* inst) { fComputeFunctions->pushBackInst(inst); return inst; }

        StatementInst* pushComputePreDSPMethod(StatementInst* inst)     { return fCurLoop->pushComputePreDSPMethod(inst); }
        StatementInst* pushComputeDSPMethod(StatementInst* inst)        { return fCurLoop->pushComputeDSPMethod(inst); }
        StatementInst* pushComputePostDSPMethod(StatementInst* inst)    { return fCurLoop->pushComputePostDSPMethod(inst); }

        void generateSubContainers()
        {
            list<CodeContainer*>::const_iterator it;
            for (it = fSubContainers.begin(); it != fSubContainers.end(); it++) {
                (*it)->produceInternal();
            }
        }
    
        // merge declaration part
        void mergeSubContainers()
        {
            list<CodeContainer*>::const_iterator it;
            for (it = fSubContainers.begin(); it != fSubContainers.end(); it++) {
                fExtGlobalDeclarationInstructions->merge((*it)->fExtGlobalDeclarationInstructions);
                fGlobalDeclarationInstructions->merge((*it)->fGlobalDeclarationInstructions);
                fDeclarationInstructions->merge((*it)->fDeclarationInstructions);
                (*it)->fGlobalDeclarationInstructions->fCode.clear();
                (*it)->fExtGlobalDeclarationInstructions->fCode.clear();
                (*it)->fDeclarationInstructions->fCode.clear();
            }
        }
        
        int getSubContainers() { return fSubContainers.size(); }

        const string& getClassName() { return fKlassName; }
        string getFaustPowerName() { return fKlassName + "_faustpower"; }

        // UI construction
        void addUIMacro(const string& str) { fUIMacro.push_back(str); }
        void addUICode(const string& str) { fUICode.push_back(str); }

        virtual CodeContainer* createScalarContainer(const string& name, int sub_container_type) = 0;

        virtual void produceInternal() = 0;
    
        virtual void printHeader() {}
        virtual void printFloatDef() {}
        virtual void printFooter() {}
        virtual void produceClass() {}
    
        virtual void dump(ostream* dst) {}
    
        void incUIActiveCount() { fNumActives++; }
        void incUIPassiveCount() { fNumPassives++; }
    
        virtual dsp_factory_base* produceFactory() { faustassert(false); return 0; }
    
};

inline bool isElement(const set<CodeLoop*>& S, CodeLoop* l)
{
	return S.find(l) != S.end();
}

#endif
