/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef _CODE_CONTAINER_H
#define _CODE_CONTAINER_H

#include <string>

#include "Text.hh"
#include "code_loop.hh"
#include "description.hh"
#include "dsp_factory.hh"
#include "floats.hh"
#include "garbageable.hh"
#include "instructions.hh"
#include "instructions_complexity.hh"
#include "json_instructions.hh"
#include "property.hh"
#include "sigtype.hh"
#include "struct_manager.hh"
#include "tlib.hh"

#ifdef WIN32
#pragma warning(disable : 4250)
#endif

// The name of 'count' parameter
#define fFullCount std::string("count")

#define fTableName std::string("table")

class TextInstVisitor;

// Look for the name of a given subcontainer.
struct SearchSubcontainer : public DispatchVisitor {
    std::string fClassName;
    bool        fFound = false;

    SearchSubcontainer(const std::string& class_name) : fClassName(class_name) {}

    virtual void visit(NamedTyped* typed) { fFound |= (fClassName == typed->getName()); }
};

// DSP or field name, type, size, size-in-bytes, reads, writes
typedef std::vector<MemoryLayoutItem> MemoryLayoutType;

class CodeContainer : public virtual Garbageable {
   protected:
    std::list<CodeContainer*> fSubContainers;
    CodeContainer* fParentContainer;  ///< Container in which this Container is embedded, null if
                                      ///< toplevel Container

    int fNumInputs;
    int fNumOutputs;

    int fNumActives;   ///< number of active controls in the UI (sliders, buttons, etc.)
    int fNumPassives;  ///< number of passive widgets in the UI (bargraphs, etc.)

    int  fSubContainerType;
    bool fGeneratedSR;

    MemoryLayoutType fMemoryLayout;
    std::string      fKlassName;

    // Declaration part
    BlockInst* fExtGlobalDeclarationInstructions;
    BlockInst* fGlobalDeclarationInstructions;

    // For DSP Struct
    BlockInst* fDeclarationInstructions;

    // For control() function
    BlockInst* fControlDeclarationInstructions;

    // Init method
    BlockInst* fInitInstructions;
    BlockInst* fConstantFromMem;
    BlockInst* fConstantToMem;
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
    BlockInst* fComputeBlockInstructions;      // Before DSP loop
    BlockInst* fPostComputeBlockInstructions;  // After DSP loop

    // Additional functions generated in -fun mode
    BlockInst* fComputeFunctions;

    // User interface
    BlockInst* fUserInterfaceInstructions;

    std::set<std::string> fIncludeFileSet;
    std::set<std::string> fLibrarySet;

    // DAG of loops
    CodeLoop* fCurLoop;

    property<CodeLoop*> fLoopProperty;  ///< loops used to compute some signals

    // UI handling
    std::list<std::string> fUICode;
    std::list<std::string> fUIMacro;
    std::list<std::string> fUIMacroActives;
    std::list<std::string> fUIMacroPassives;

    void merge(std::set<std::string>& dst, std::set<std::string>& src)
    {
        for (const auto& i : src) {
            dst.insert(i);
        }
    }

    void collectIncludeFile(std::set<std::string>& S)
    {
        for (const auto& k : fSubContainers) {
            k->collectIncludeFile(S);
        }
        merge(S, fIncludeFileSet);
    }

    void collectLibrary(std::set<std::string>& S)
    {
        for (const auto& k : fSubContainers) {
            k->collectLibrary(S);
        }
        merge(S, fLibrarySet);
    }

    void generateDAGLoopAux(CodeLoop* loop, BlockInst* loop_code, ValueInst* count, int loop_num,
                            bool omp = false);
    void generateDAGLoopInternal(CodeLoop* loop, BlockInst* block, ValueInst* count, bool omp);

    void includeFastMath()
    {
        if (gGlobal->gFastMathLib == "def") {
            addIncludeFile("\"faust/dsp/fastmath.cpp\"");
        } else if (gGlobal->gFastMathLib == "arch") {
            // Nothing
        } else {
            addIncludeFile("\"" + gGlobal->gFastMathLib + "\"");
        }
    }

    void printHeader(std::ostream& dst)
    {
        // defines the metadata we want to print as comments at the begin of in the file
        std::set<Tree> selectedKeys;
        selectedKeys.insert(tree("name"));
        selectedKeys.insert(tree("author"));
        selectedKeys.insert(tree("copyright"));
        selectedKeys.insert(tree("license"));
        selectedKeys.insert(tree("version"));

        dst << "/* ------------------------------------------------------------" << std::endl;
        for (const auto& i : gGlobal->gMetaDataSet) {
            if (selectedKeys.count(i.first)) {
                dst << *(i.first);
                const char* sep = ": ";
                for (const auto& j : i.second) {
                    dst << sep << *j;
                    sep = ", ";
                }
                dst << std::endl;
            }
        }

        dst << "Code generated with Faust " << FAUSTVERSION << " (https://faust.grame.fr)"
            << std::endl;
        dst << "Compilation options: ";
        dst << gGlobal->printCompilationOptions1();
        dst << "\n------------------------------------------------------------ */" << std::endl;
    }

    virtual void generateSR()
    {
        if (!fGeneratedSR) {
            pushDeclare(IB::genDecStructVar("fSampleRate", IB::genInt32Typed()));
        }
        pushPreInitMethod(
            IB::genStoreStructVar("fSampleRate", IB::genLoadFunArgsVar("sample_rate")));
    }

    BlockInst* inlineSubcontainersFunCalls(BlockInst* block);

    Names genMethod(const std::string& obj, bool ismethod)
    {
        Names args;
        if (!ismethod) {
            args.push_back(IB::genNamedTyped(obj, Typed::kObj_ptr));
        }
        return args;
    }

    Values genObjArg(const std::string& obj, bool ismethod)
    {
        Values args;
        if (!ismethod) {
            args.push_back(IB::genLoadFunArgsVar(obj));
        }
        return args;
    }

    void createMemoryLayout();
    void rewriteInZones();

   public:
    CodeContainer();
    void initialize(int numInputs, int numOutputs);
    virtual ~CodeContainer();

    void printMacros(std::ostream& fout, int n);

    CodeLoop* getCurLoop() { return fCurLoop; }

    void           setParentContainers(CodeContainer* parent) { fParentContainer = parent; }
    CodeContainer* getParentContainer() { return fParentContainer; }
    CodeContainer* getTopParentContainer()
    {
        return (fParentContainer) ? fParentContainer->getTopParentContainer() : this;
    }

    // Returns the name of the class
    std::string getFullClassName()
    {
        return (fParentContainer) ? (fParentContainer->getFullClassName() + "::" + getClassName())
                                  : getClassName();
    }

    void setGeneratedSR() { fGeneratedSR = true; }

    void openLoop(const std::string& index_name, int size = 0);
    void openLoop(Tree recsymbol, const std::string& index_name, int size = 0);
    void closeLoop(Tree sig);

    int inputs() { return fNumInputs; }
    int outputs() { return fNumOutputs; }

    void setInputs(int inputs) { fNumInputs = inputs; }
    void setOutputs(int outputs) { fNumOutputs = outputs; }

    void addSubContainer(CodeContainer* container) { fSubContainers.push_back(container); }

    void addIncludeFile(const std::string& str) { fIncludeFileSet.insert(str); }
    void addLibrary(const std::string& str) { fLibrarySet.insert(str); }

    void printLibrary(std::ostream& fout);
    void printIncludeFile(std::ostream& fout);

    void setLoopProperty(Tree sig, CodeLoop* l);   ///< Store the loop used to compute a signal
    bool getLoopProperty(Tree sig, CodeLoop*& l);  ///< Returns the loop used to compute a signal
    void listAllLoopProperties(
        Tree            sig, std::set<CodeLoop*>&,
        std::set<Tree>& visited);  ///< Returns all the loop used to compute a signal

    void printGraphDotFormat(std::ostream& fout);

    void transformDAG(DispatchVisitor* visitor);
    void computeForwardDAG(lclgraph dag, int& loop_count, std::vector<int>& ready_loop);
    void sortDeepFirstDAG(CodeLoop* l, std::set<CodeLoop*>& visited, std::list<CodeLoop*>& result);

    // Should be implemented in subclasses
    virtual void generateLocalInputs(BlockInst* loop_code, const std::string& index)
    {
        faustassert(false);
    }
    virtual void generateLocalOutputs(BlockInst* loop_code, const std::string& index)
    {
        faustassert(false);
    }

    virtual DeclareFunInst* generateAllocate(const std::string& name, const std::string& obj,
                                             bool ismethod, bool isvirtual);
    virtual DeclareFunInst* generateDestroy(const std::string& name, const std::string& obj,
                                            bool ismethod, bool isvirtual);

    DeclareFunInst* generateGetIO(const std::string& name, const std::string& obj, int io,
                                  bool ismethod, FunTyped::FunAttribute funtype);
    DeclareFunInst* generateGetInputs(const std::string& name, const std::string& obj,
                                      bool ismethod, FunTyped::FunAttribute funtype);
    DeclareFunInst* generateGetOutputs(const std::string& name, const std::string& obj,
                                       bool ismethod, FunTyped::FunAttribute funtype);

    DeclareFunInst* generateGetIORate(const std::string& name, const std::string& obj,
                                      std::vector<int>& io, bool ismethod, bool isvirtual);

    virtual DeclareFunInst* generateClassInit(const std::string& name)
    {
        faustassert(false);
        return nullptr;
    }
    virtual DeclareFunInst* generateInstanceClear(const std::string& name, const std::string& obj,
                                                  bool ismethod, bool isvirtual);

    virtual DeclareFunInst* generateInstanceConstants(const std::string& name,
                                                      const std::string& obj, bool ismethod,
                                                      bool isvirtual);

    virtual DeclareFunInst* generateInstanceResetUserInterface(const std::string& name,
                                                               const std::string& obj,
                                                               bool ismethod, bool isvirtual)
    {
        faustassert(false);
        return nullptr;
    }

    virtual DeclareFunInst* generateComputeFun(const std::string& name, const std::string& obj,
                                               bool ismethod, bool isvirtual);

    virtual BlockInst* generateComputeAux()
    {
        faustassert(false);
        return nullptr;
    }

    virtual DeclareFunInst* generateStaticInitFun(const std::string& name, bool isstatic);
    virtual DeclareFunInst* generateInstanceInitFun(const std::string& name, const std::string& obj,
                                                    bool ismethod, bool isvirtual);
    virtual DeclareFunInst* generateFillFun(const std::string& name, const std::string& obj,
                                            bool ismethod, bool isvirtual);

    DeclareFunInst* generateInit(const std::string& name, const std::string& obj, bool ismethod,
                                 bool isvirtual);
    DeclareFunInst* generateInstanceInit(const std::string& name, const std::string& obj,
                                         bool ismethod, bool isvirtual);
    DeclareFunInst* generateGetSampleRate(const std::string& name, const std::string& obj,
                                          bool ismethod, bool isvirtual);

    DeclareFunInst* generateCalloc();
    DeclareFunInst* generateFree();

    DeclareFunInst* generateNewDsp(const std::string& name, int size);
    DeclareFunInst* generateDeleteDsp(const std::string& name, const std::string& obj);

    void produceInfoFunctions(int tabs, const std::string& classname, const std::string& obj,
                              bool ismethod, FunTyped::FunAttribute funtype,
                              TextInstVisitor* producer, const std::string& in_fun = "getNumInputs",
                              const std::string& out_fun = "getNumOutputs");

    void generateDAGLoop(BlockInst* loop_code, ValueInst* count);

    template <typename REAL>
    void generateMetaData(JSONUIReal<REAL>* json)
    {
        // Add global metadata
        for (const auto& i : gGlobal->gMetaDataSet) {
            if (i.first != tree("author")) {
                std::stringstream str1, str2;
                str1 << *(i.first);
                str2 << **(i.second.begin());
                std::string res1 = str1.str();
                std::string res2 = unquote(str2.str());
                json->declare(res1.c_str(), res2.c_str());
            } else {
                for (std::set<Tree>::iterator j = i.second.begin(); j != i.second.end(); j++) {
                    if (j == i.second.begin()) {
                        std::stringstream str1, str2;
                        str1 << *(i.first);
                        str2 << **j;
                        std::string res1 = str1.str();
                        std::string res2 = unquote(str2.str());
                        json->declare(res1.c_str(), res2.c_str());
                    } else {
                        std::stringstream str2;
                        str2 << **j;
                        std::string res2 = unquote(str2.str());
                        json->declare("contributor", res2.c_str());
                    }
                }
            }
        }
    }

    template <typename REAL>
    void generateJSONFile()
    {
        JSONInstVisitor<REAL> visitor;
        generateJSON(&visitor);
        std::ofstream xout(subst("$0.json", gGlobal->makeDrawPath()).c_str());
        xout << visitor.JSON();
    }

    template <typename REAL>
    void generateJSON(JSONInstVisitor<REAL>* visitor)
    {
        // Prepare instructions complexity
        ForLoopInst*          loop = fCurLoop->generateScalarLoop("count");
        InstComplexityVisitor complexity;
        loop->accept(&complexity);

        // Get the DSP size
        StructInstVisitor struct_visitor;
        fDeclarationInstructions->accept(&struct_visitor);

        // "name", "filename" found in medata
        visitor->init("", "", fNumInputs, fNumOutputs, -1, "", "", FAUSTVERSION,
                      gGlobal->printCompilationOptions1(), gGlobal->gReader.listLibraryFiles(),
                      gGlobal->gImportDirList, struct_visitor.getStructSize(), PathTableType(),
                      fMemoryLayout, complexity.getInstComplexity());
        generateUserInterface(visitor);
        generateMetaData(visitor);
    }

    template <typename REAL>
    std::string generateJSON()
    {
        JSONInstVisitor<REAL> visitor;
        generateJSON(&visitor);
        return visitor.JSON(true);
    }

    std::string generateJSONAux()
    {
        if (gGlobal->gFloatSize == 1) {
            return generateJSON<float>();
        } else {
            return generateJSON<double>();
        }
    }

    /* Can be overridden by subclasses to transform the FIR before the actual code generation */
    virtual void processFIR(void);

    /* Create a single block containing all FIR */
    virtual BlockInst* flattenFIR(void);

    // Fill code for each method
    StatementInst* pushDeclare(StatementInst* inst)
    {
        faustassert(inst);
        fDeclarationInstructions->pushBackInst(inst);
        // TODO : add inter-loop vectors in current loop
        return inst;
    }

    StatementInst* pushGlobalDeclare(StatementInst* inst)
    {
        faustassert(inst);
        fGlobalDeclarationInstructions->pushBackInst(inst);
        return inst;
    }

    StatementInst* pushExtGlobalDeclare(StatementInst* inst)
    {
        faustassert(inst);
        fExtGlobalDeclarationInstructions->pushBackInst(inst);
        return inst;
    }

    StatementInst* pushControlDeclare(StatementInst* inst)
    {
        faustassert(inst);
        fControlDeclarationInstructions->pushBackInst(inst);
        return inst;
    }

    ValueInst* pushFunction(const std::string& name, Typed::VarType result,
                            std::vector<Typed::VarType>& types, const Values& args);

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

    void generateControlDeclarations(InstVisitor* visitor)
    {
        if (fControlDeclarationInstructions->fCode.size() > 0) {
            fControlDeclarationInstructions->accept(visitor);
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

    void generatePostComputeBlock(InstVisitor* visitor)
    {
        if (fPostComputeBlockInstructions->fCode.size() > 0) {
            fPostComputeBlockInstructions->accept(visitor);
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

    StatementInst* pushInitMethod(StatementInst* inst)
    {
        faustassert(inst);
        fInitInstructions->pushBackInst(inst);
        return inst;
    }
    StatementInst* pushClearMethod(StatementInst* inst)
    {
        faustassert(inst);
        fClearInstructions->pushBackInst(inst);
        return inst;
    }
    StatementInst* pushResetUIInstructions(StatementInst* inst)
    {
        faustassert(inst);
        fResetUserInterfaceInstructions->pushBackInst(inst);
        return inst;
    }
    StatementInst* pushPostInitMethod(StatementInst* inst)
    {
        faustassert(inst);
        fPostInitInstructions->pushBackInst(inst);
        return inst;
    }
    StatementInst* pushPreInitMethod(StatementInst* inst)
    {
        faustassert(inst);
        fInitInstructions->pushFrontInst(inst);
        return inst;
    }

    StatementInst* pushUserInterfaceMethod(StatementInst* inst)
    {
        faustassert(inst);
        fUserInterfaceInstructions->pushBackInst(inst);
        return inst;
    }

    StatementInst* pushAllocateMethod(StatementInst* inst)
    {
        faustassert(inst);
        fAllocateInstructions->pushBackInst(inst);
        return inst;
    }
    StatementInst* pushDestroyMethod(StatementInst* inst)
    {
        faustassert(inst);
        fDestroyInstructions->pushBackInst(inst);
        return inst;
    }

    StatementInst* pushStaticInitMethod(StatementInst* inst)
    {
        faustassert(inst);
        fStaticInitInstructions->pushBackInst(inst);
        return inst;
    }
    StatementInst* pushStaticDestroyMethod(StatementInst* inst)
    {
        faustassert(inst);
        fStaticDestroyInstructions->pushBackInst(inst);
        return inst;
    }
    StatementInst* pushPostStaticInitMethod(StatementInst* inst)
    {
        faustassert(inst);
        fPostStaticInitInstructions->pushBackInst(inst);
        return inst;
    }

    StatementInst* pushComputeBlockMethod(StatementInst* inst)
    {
        faustassert(inst);
        fComputeBlockInstructions->pushBackInst(inst);
        return inst;
    }
    StatementInst* pushPostComputeBlockMethod(StatementInst* inst)
    {
        faustassert(inst);
        fPostComputeBlockInstructions->pushBackInst(inst);
        return inst;
    }

    StatementInst* pushOtherComputeMethod(StatementInst* inst)
    {
        faustassert(inst);
        fComputeFunctions->pushBackInst(inst);
        return inst;
    }

    StatementInst* pushPreComputeDSPMethod(StatementInst* inst)
    {
        faustassert(inst);
        return fCurLoop->pushPreComputeDSPMethod(inst);
    }
    StatementInst* pushComputeDSPMethod(StatementInst* inst)
    {
        faustassert(inst);
        return fCurLoop->pushComputeDSPMethod(inst);
    }
    StatementInst* pushPostComputeDSPMethod(StatementInst* inst)
    {
        faustassert(inst);
        return fCurLoop->pushPostComputeDSPMethod(inst);
    }

    void generateSubContainers()
    {
        for (const auto& it : fSubContainers) {
            it->produceInternal();
        }
    }

    // merge declaration part
    void mergeSubContainers();

    size_t getSubContainers() { return fSubContainers.size(); }

    const std::string getTableName() { return fTableName; }
    const std::string getClassName() { return fKlassName; }
    const std::string getFaustPowerName() { return fKlassName + "_faustpower"; }

    // UI construction
    void addUIMacro(const std::string& str) { fUIMacro.push_back(str); }
    void addUIMacroActives(const std::string& str) { fUIMacroActives.push_back(str); }
    void addUIMacroPassives(const std::string& str) { fUIMacroPassives.push_back(str); }
    void addUICode(const std::string& str) { fUICode.push_back(str); }

    void incUIActiveCount() { fNumActives++; }
    void incUIPassiveCount() { fNumPassives++; }

    virtual CodeContainer* createScalarContainer(const std::string& name,
                                                 int                sub_container_type) = 0;

    virtual void produceInternal() = 0;

    virtual void printHeader() {}
    virtual void printFloatDef() {}
    virtual void printFooter() {}
    virtual void produceClass() {}

    virtual void dump(std::ostream* dst) {}

    virtual dsp_factory_base* produceFactory()
    {
        faustassert(false);
        return nullptr;
    }

    void generateJSONFile();

    // Used in -ec mode
    ControlArray* fIntControl;   // array of 'int32' intermediate control values
    ControlArray* fRealControl;  // array of 'real' intermediate control values
};

inline bool isElement(const std::set<CodeLoop*>& S, CodeLoop* l)
{
    return S.find(l) != S.end();
}

#endif
