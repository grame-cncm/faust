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

#define _DNF_ 1

#include <iostream>
#include <map>
#include <sstream>
#include <utility>

#include "compile.hh"
#include "dcond.hh"
#include "graph_scheduling.hh"
#include "old_occurences.hh"
#include "ppsig.hh"
#include "property.hh"
#include "signalDependencies.hh"
#include "sigtyperules.hh"

////////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a scalar C++ class
 */
///////////////////////////////////////////////////////////////////////

class GraphCompiler : public Compiler {
    property<string>               fCompileProperty;
    property<string>               fSoundfileVariableProperty;  // variable associated to a soundfile
    property<pair<string, string>> fStaticInitProperty;         // property added to solve 20101208 kjetil bug
    property<pair<string, string>> fInstanceInitProperty;       // property added to solve 20101208 kjetil bug
    property<Tree>                 fTableInitExpression;        // init expression associated with each table ID
    property<int>                  fTableInitSize;              // init size associated with each table ID
    property<int>                  fTableInitNature;            // init nature associated with each table ID
    property<set<Tree>>            fTableInitInstructions;      // init expression associated with each table ID
    property<Scheduling>           fTableInitScheduling;        // instruction scheduling for each init expression
    digraph<Tree, multidep>        fTableInitGraph;             // Graph of table IDs

    map<Tree, Tree> fConditionProperty;  // used with the new X,Y:enable --> sigEnable(X*Y,Y>0) primitive

    static map<string, int, std::less<>> fIDCounters;
    Tree                                 fSharingKey;
    old_OccMarkup*                       fOccMarkup;
    bool                                 fHasIota;

   public:
    GraphCompiler(const string& name, const string& super, int numInputs, int numOutputs)
        : Compiler(name, super, numInputs, numOutputs, false)
    {
    }

    explicit GraphCompiler(Klass* k) : Compiler(k) {}

    void compileMultiSignal(Tree lsig) override;
    void compileSingleSignal(Tree lsig) override;
    // void compileMultiSignalVec(Tree L);  // experimental vector mode

   protected:
    virtual string CS(Tree sig);
    virtual string generateCode(Tree sig);

    void InstructionsToClass(const set<Tree>& I, Klass* K);
    void InstructionsToVectorClass(const set<Tree>& I, Klass* K);
    void InstructionsToMethod(const set<Tree>& I, Klass* K);
    void SchedulingToMethod(const Scheduling& S, Klass* K);
    void compileSingleInstruction(Tree instr, Klass* K);

    string getFreshID(const string& prefix) const;

    void       compilePreparedSignalList(Tree lsig);
    Tree       prepare(Tree L0) override;
    Tree       prepare2(Tree L0) override;
    Tree       prepare3(Tree L0);
    set<Tree>  ExpressionsListToInstructionsSet(Tree L3) const;
    set<Tree>  expression2Instructions(Tree L3);
    Scheduling schedule(const set<Tree>& Instr) const;
    void       tableDependenciesGraph(const set<Tree>& I);
    void       generateTime();
    bool       getCompiledExpression(Tree sig, string& name);
    string     setCompiledExpression(Tree sig, const string& name);

    int       getSharingCount(Tree t);
    void      setSharingCount(Tree t, int count);
    void      sharingAnalysis(Tree t);
    void      sharingAnnotation(int vctxt, Tree t);
    set<Tree> collectTableIDs(const set<Tree>& I);

    void   conditionAnnotation(Tree l);
    void   conditionAnnotation(Tree t, Tree nc);
    void   conditionStatistics(Tree l);
    string getConditionCode(Tree t);

    // signal drawing
    /*
    SL : 28/09/17 : deactivated for now
    void sigToGraph (Tree sig, ofstream& fout);
    void recdraw(Tree sig, set<Tree>& drawn, ofstream& fout);
    */

    // code generation

    string generateXtended(Tree sig);
    // virtual string generateFixDelay(Tree sig, Tree arg, Tree size);
    string generatePrefix(Tree sig, Tree x, Tree e);
    string generateIota(Tree sig, Tree arg);
    string generateBinOp(Tree sig, int opcode, Tree arg1, Tree arg2);

    string         generateFFun(Tree sig, Tree ff, Tree largs);
    virtual string generateWaveform(Tree sig);

    string generateInput(Tree sig, const string& idx);
    string generateOutput(Tree sig, const string& idx, const string& arg1);

    string generateTable(Tree sig, Tree tsize, Tree content);
    string generateStaticTable(Tree sig, Tree tsize, Tree content);
    string generateWRTbl(Tree sig, Tree tbl, Tree idx, Tree data);
    string generateRDTbl(Tree sig, Tree tbl, Tree idx);
    string generateStaticSigGen(Tree sig, Tree content);

    string generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2);
    string generateSelect3(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3);

    string generateRecProj(Tree sig, Tree exp, int i);
    void   generateRec(Tree sig, Tree var, Tree le);

    string generateIntCast(Tree sig, Tree x);
    string generateFloatCast(Tree sig, Tree x);

    string generateButton(Tree sig, Tree label);
    string generateCheckbox(Tree sig, Tree label);
    string generateVSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
    string generateHSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
    string generateNumEntry(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);

    string generateVBargraph(Tree sig, Tree label, Tree min, Tree max, const string& exp);
    string generateHBargraph(Tree sig, Tree label, Tree min, Tree max, const string& exp);
    string generateSoundfile(Tree sig, Tree path);

    string generateNumber(Tree sig, const string& exp);
    string generateFConst(Tree sig, const string& file, const string& name);
    string generateFVar(Tree sig, const string& file, const string& name);

    void getTypedNames(::Type t, const string& prefix, string& ctype, string& vname);
    int  pow2limit(int x) const;

    void declareWaveform(Tree sig, string& vname, int& size);

    virtual string generateEnable(Tree sig, Tree x, Tree y);

    string cnf2code(Tree cc);
    string or2code(Tree oc);

    string dnf2code(Tree cc);
    string and2code(Tree oc);
};
