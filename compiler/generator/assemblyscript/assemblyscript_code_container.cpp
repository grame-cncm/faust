/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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

#include "assemblyscript_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "fir_function_builder.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

map<string, bool>   AssemblyScriptInstVisitor::gFunctionSymbolTable;
map<string, string> AssemblyScriptInstVisitor::gMathLibTable;

dsp_factory_base* AssemblyScriptCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""),
        "");
}

AssemblyScriptCodeContainer::AssemblyScriptCodeContainer(const std::string& name, int numInputs,
                                                         int numOutputs, std::ostream* out)
{
    // Mandatory
    initialize(numInputs, numOutputs);
    fKlassName = name;
    fOut       = out;

    // Allocate one static visitor to be shared by main module and sub containers
    if (!gGlobal->gAssemblyScriptVisitor) {
        gGlobal->gAssemblyScriptVisitor = new AssemblyScriptInstVisitor(out, name);
    }
}

CodeContainer* AssemblyScriptCodeContainer::createScalarContainer(const string& name,
                                                                  int           sub_container_type)
{
    return new AssemblyScriptScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

/*
    The given template implements -scalar (= default) and -vec mode.
    For  options like -omp, -sch, the corresponding AssemblyScriptOpenMPCodeContainer
    and AssemblyScriptWorkStealingCodeContainer classes would have to be implemented
    and activated.
*/
CodeContainer* AssemblyScriptCodeContainer::createContainer(const string& name, int numInputs,
                                                            int numOutputs, ostream* dst)
{
    CodeContainer* container;

    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : -quad format not supported for AssemblyScript\n");
    }
    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for AssemblyScript\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for AssemblyScript\n");
    }

    // The backend currently exposes only the scalar code path; keep failures explicit so callers
    // do not assume partial vector/scheduler compatibility.
    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for AssemblyScript\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for AssemblyScript\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : Vector mode not supported for AssemblyScript\n");
    } else {
        container = new AssemblyScriptScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

// Used for subcontainers if 'inlining sub containers' model is not used
void AssemblyScriptCodeContainer::produceInternal()
{
    int                       n = 0;
    AssemblyScriptInstVisitor visitor(fOut, fKlassName);
    const string              root_class = gGlobal->gClassName;

    tab(n, *fOut);
    visitor.Tab(n);
    visitor.SetInClassScope(false);
    visitor.SetInClassFields(false);
    generateGlobalDeclarations(&visitor);

    tab(n, *fOut);
    *fOut << "class " << fKlassName << " {";

    tab(n + 1, *fOut);
    visitor.Tab(n + 1);
    visitor.SetInClassScope(true);
    visitor.SetInClassFields(true);
    generateDeclarations(&visitor);
    visitor.SetInClassFields(false);

    tab(n + 1, *fOut);
    produceInfoFunctions(n + 1, fKlassName, "this", true, FunTyped::kDefault, &visitor);

    tab(n + 1, *fOut);
    *fOut << "instanceInit" << fKlassName << "(sample_rate: i32): void {";
    tab(n + 2, *fOut);
    visitor.Tab(n + 2);
    generateInit(&visitor);
    generateResetUserInterface(&visitor);
    generateClear(&visitor);
    tab(n + 1, *fOut);
    *fOut << "}";

    string counter = "count";
    tab(n + 1, *fOut);
    if (fSubContainerType == kInt) {
        *fOut << "fill" << fKlassName << "(" << counter << ": i32, " << fTableName
              << ": StaticArray<i32>): void {";
    } else {
        *fOut << "fill" << fKlassName << "(" << counter << ": i32, " << fTableName << ": "
              << "StaticArray<" << ifloat() << ">): void {";
    }
    tab(n + 2, *fOut);
    visitor.Tab(n + 2);
    generateComputeBlock(&visitor);
    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    loop->accept(&visitor);
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n, *fOut);
    *fOut << "}";
    visitor.SetInClassScope(false);
    tab(n, *fOut);

    // Parent-generated FIR code manipulates subcontainer handles as `kObj` rooted on the top
    // DSP class type. Keep helper signatures on root_class and cast internally.
    tab(n, *fOut);
    *fOut << "function new" << fKlassName << "(): " << root_class << " {";
    tab(n + 1, *fOut);
    *fOut << "return changetype<" << root_class << ">(new " << fKlassName << "());";
    tab(n, *fOut);
    *fOut << "}";
    tab(n, *fOut);

    tab(n, *fOut);
    *fOut << "function delete" << fKlassName << "(dsp: " << root_class << "): void {";
    tab(n, *fOut);
    *fOut << "}";
    tab(n, *fOut);

    tab(n, *fOut);
    *fOut << "function instanceInit" << fKlassName << "(dsp: " << root_class
          << ", sample_rate: i32): void {";
    tab(n + 1, *fOut);
    *fOut << "changetype<" << fKlassName << ">(dsp).instanceInit" << fKlassName << "(sample_rate);";
    tab(n, *fOut);
    *fOut << "}";
    tab(n, *fOut);

    tab(n, *fOut);
    if (fSubContainerType == kInt) {
        *fOut << "function fill" << fKlassName << "(dsp: " << root_class << ", " << counter
              << ": i32, " << fTableName << ": StaticArray<i32>): void {";
    } else {
        *fOut << "function fill" << fKlassName << "(dsp: " << root_class << ", " << counter
              << ": i32, " << fTableName << ": " << "StaticArray<" << ifloat() << ">): void {";
    }
    tab(n + 1, *fOut);
    *fOut << "changetype<" << fKlassName << ">(dsp).fill" << fKlassName << "(" << counter << ", "
          << fTableName << ");";
    tab(n, *fOut);
    *fOut << "}";
    tab(n, *fOut);
}

void AssemblyScriptCodeContainer::produceClass()
{
    int n = 0;
    *fOut << "// Code generated with Faust version " << FAUSTVERSION;
    tab(n, *fOut);
    *fOut << "// Language: AssemblyScript (experimental)";
    tab(n, *fOut);

    // Generate module-level helper functions first.
    // In-class methods are emitted later in `export class <name>`.
    gGlobal->gAssemblyScriptVisitor->Tab(n);
    gGlobal->gAssemblyScriptVisitor->SetInClassScope(false);
    gGlobal->gAssemblyScriptVisitor->SetInClassFields(false);
    for (const auto& it : fGlobalDeclarationInstructions->fCode) {
        if (dynamic_cast<DeclareFunInst*>(it)) {
            it->accept(gGlobal->gAssemblyScriptVisitor);
        }
    }

    // Generate subcontainers when rdtable/rwtable are not inlined.
    generateSubContainers();

    tab(n, *fOut);
    *fOut << "export class " << fKlassName << " {";

    // Class fields: state arrays and scalar memory live as members, not as stack locals.
    tab(n + 1, *fOut);
    gGlobal->gAssemblyScriptVisitor->Tab(n + 1);
    gGlobal->gAssemblyScriptVisitor->SetInClassScope(true);
    gGlobal->gAssemblyScriptVisitor->SetInClassFields(true);
    generateDeclarations(gGlobal->gAssemblyScriptVisitor);
    for (const auto& it : fGlobalDeclarationInstructions->fCode) {
        if (dynamic_cast<DeclareVarInst*>(it)) {
            it->accept(gGlobal->gAssemblyScriptVisitor);
        }
    }
    gGlobal->gAssemblyScriptVisitor->SetInClassFields(false);

    // ABI choice: provide both metadata styles.
    // - metadata(m: Meta): declaration-style metadata API used by classic Faust runtimes
    // - getJSON(): string  : JSON snapshot used by current AssemblyScript impulse tooling
    produceMetadata(n + 1);

    // Emit info getters explicitly to keep AssemblyScript formatting stable.
    tab(n + 1, *fOut);
    *fOut << "getSampleRate(): i32 {";
    tab(n + 2, *fOut);
    *fOut << "return this.fSampleRate;";
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "getNumInputs(): i32 {";
    tab(n + 2, *fOut);
    *fOut << "return " << fNumInputs << ";";
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "getNumOutputs(): i32 {";
    tab(n + 2, *fOut);
    *fOut << "return " << fNumOutputs << ";";
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "static classInit(sample_rate: i32): void {";
    tab(n + 2, *fOut);
    gGlobal->gAssemblyScriptVisitor->Tab(n + 2);
    generateStaticInit(gGlobal->gAssemblyScriptVisitor);
    // `generateStaticInit` ends on an indented newline; back up one tab to avoid an extra blank
    // line before the closing brace.
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "instanceResetUserInterface(): void {";
    tab(n + 2, *fOut);
    generateResetUserInterface(gGlobal->gAssemblyScriptVisitor);
    // Same formatting adjustment as above for cleaner generated methods.
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "instanceClear(): void {";
    tab(n + 2, *fOut);
    generateClear(gGlobal->gAssemblyScriptVisitor);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "instanceConstants(sample_rate: i32): void {";
    tab(n + 2, *fOut);
    generateInit(gGlobal->gAssemblyScriptVisitor);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "instanceInit(sample_rate: i32): void {";
    tab(n + 2, *fOut);
    *fOut << "this.instanceConstants(sample_rate);";
    tab(n + 2, *fOut);
    *fOut << "this.instanceResetUserInterface();";
    tab(n + 2, *fOut);
    *fOut << "this.instanceClear();";
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    // No constructor is emitted in this backend: init sequence is explicit.
    // classInit handles static/global tables, instanceInit handles per-instance state.
    *fOut << "init(sample_rate: i32): void {";
    tab(n + 2, *fOut);
    *fOut << fKlassName << ".classInit(sample_rate);";
    tab(n + 2, *fOut);
    *fOut << "this.instanceInit(sample_rate);";
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    generateCompute(n + 1);

    tab(n, *fOut);
    *fOut << "}";
    gGlobal->gAssemblyScriptVisitor->SetInClassScope(false);
    tab(n, *fOut);
}

void AssemblyScriptCodeContainer::produceMetadata(int tabs)
{
    tab(tabs, *fOut);
    *fOut << "metadata(m: Meta): void {";
    tab(tabs + 1, *fOut);
    for (const auto& i : gGlobal->gMetaDataSet) {
        // Match legacy Faust behavior: first "author" stays author, additional authors are
        // lowered as contributors.
        if (i.first != tree("author")) {
            *fOut << "m.declare(\"" << *(i.first) << "\", " << **(i.second.begin()) << ");";
            tab(tabs + 1, *fOut);
        } else {
            for (set<Tree, treeorder>::iterator j = i.second.begin(); j != i.second.end(); j++) {
                if (j == i.second.begin()) {
                    *fOut << "m.declare(\"" << *(i.first) << "\", " << **j << ");";
                } else {
                    *fOut << "m.declare(\"contributor\", " << **j << ");";
                }
                tab(tabs + 1, *fOut);
            }
        }
    }
    tab(tabs, *fOut);
    *fOut << "}";
    tab(tabs, *fOut);

    // JSON metadata is kept for tooling compatibility (impulse runner/UI inspection).
    tab(tabs, *fOut);
    *fOut << "getJSON(): string {";
    tab(tabs + 1, *fOut);
    string json = flattenJSON(generateJSONAux());
    *fOut << "return \"" << json << "\";";
    tab(tabs, *fOut);
    *fOut << "}";
    tab(tabs, *fOut);
}

// Scalar
AssemblyScriptScalarCodeContainer::AssemblyScriptScalarCodeContainer(const string& name,
                                                                     int numInputs, int numOutputs,
                                                                     std::ostream* out,
                                                                     int sub_container_type)
    : AssemblyScriptCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

void AssemblyScriptScalarCodeContainer::generateCompute(int n)
{
    // AssemblyScript ABI currently uses nested channel arrays:
    // inputs[ch][frame], outputs[ch][frame].
    tab(n, *fOut);
    *fOut << "compute(count: i32, inputs: Array<Array<" << ifloat() << ">>, outputs: Array<Array<"
          << ifloat() << ">>): void {";
    tab(n + 1, *fOut);
    gGlobal->gAssemblyScriptVisitor->Tab(n + 1);

    // Local variables declaration and setup
    generateComputeBlock(gGlobal->gAssemblyScriptVisitor);

    // Generate one single scalar loop
    SimpleForLoopInst* loop = fCurLoop->generateSimpleScalarLoop(fFullCount);
    loop->accept(gGlobal->gAssemblyScriptVisitor);

    // Post compute code (for soundfile support and atomics where needed)
    generatePostComputeBlock(gGlobal->gAssemblyScriptVisitor);

    back(1, *fOut);
    *fOut << "}";
    tab(n, *fOut);
}
