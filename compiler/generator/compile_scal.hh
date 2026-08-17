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

#ifndef _COMPILE_SCAL_
#define _COMPILE_SCAL_

#define _DNF_ 1

#include <map>
#include <utility>

#include "compile.hh"
#include "dcond.hh"
#include "occurrences.hh"
#include "property.hh"
#include "sigtyperules.hh"

////////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a scalar C++ class
 */
///////////////////////////////////////////////////////////////////////

class ScalarCompiler : public Compiler {
    friend class LoopSplitEmitter;  // -ls experimental loop-split emission

   protected:
    property<std::string> fCompileProperty;
    property<std::string> fSoundfileVariableProperty;  // variable associated to a soundfile
    property<std::string> fVectorProperty;
    property<std::pair<std::string, std::string> >
        fStaticInitProperty;  // property added to solve 20101208 kjetil bug
    property<std::pair<std::string, std::string> >
        fInstanceInitProperty;  // property added to solve 20101208 kjetil bug

    std::map<Tree, Tree, treeorder>
        fConditionProperty;  // used with the new X,Y:enable --> sigControl(X*Y,Y>0) primitive

    static std::map<std::string, int>  fIDCounters;
    Tree                               fSharingKey;
    std::vector<std::string> fSingleDelayScalarCandidates;  // [2]-vectors, schedule-verified demotion
    // A-priori mono election, stage 3 (readers first). The soft-edge block
    // records its promise per writer x of a delayed read : kept = every edge
    // x -> reader was added ; sacrificed = at least one was dropped to break
    // a preference cycle. The schedule positions are the FACT the election
    // asserts against (promise to elect, fact to witness).
    std::set<Tree>                 fRFKeptWriters;
    std::set<Tree>                 fRFSacrificedWriters;
    // Writers actually elected at stage 3. The election is granted ONLY
    // when the schedule places the LAST consumer of the old-value read
    // before the write (an inlined read is emitted at its consumer's
    // slot) ; otherwise the type falls back to kSingleDelay, whose
    // [2]-vector is order-robust by distinct cells. A forced capture at
    // the read's slot was tried instead and measurably costs (brassMIDI
    // +30%, flute +14% : it hoists a live range across the whole body).
    std::set<Tree>                 fRFStage3Elected;
    std::unordered_map<Tree, int>  fConsumerMaxPos;  // delayed-read node -> last consumer slot
    std::unordered_map<Tree, int>  fSchedPos;
    OccMarkup*                         fOccMarkup;
    int                                fMaxIota;
    std::map<std::string, std::string> fIotaCache;
    // FAUST_SS_DISPLAYBLOCK (spec SIGNAUX-ATTACHES) : bargraph stores and
    // their stateless tails evaluate ONCE PER BLOCK. fDisplayList holds
    // the harvested bargraph nodes (D) ; fDisplayStateful their stateful
    // sub-signals (S, compiled at audio rate as extra roots) ; capture
    // points map to end-of-loop capture variables read by the block-rate
    // tail.
    Tree                                   fDisplayList = nullptr;
    std::set<Tree>                         fDisplayPreserved;  // widgets of harvested cones
    std::vector<Tree>                      fDisplayStateful;
    std::vector<Tree>                      fDisplayCapturePoints;
    std::map<Tree, std::string, treeorder> fDisplayCaptures;
    Tree        harvestDisplay(Tree L);
    void        computeDisplayFrontier();
    std::string displayExpr(Tree t);
    void        emitDisplayList();
    // iota caches hoisted to the head of the loop body (ring-preload) :
    // only an index whose delay amount is sub-sample-rate may hoist, and
    // only a ring access through a hoisted index may preload
    std::set<std::string> fIotaHeadNames;
    // adjacent-pair collapse (spec PAIRE-ADJACENTE) : a ring read at d,
    // when the same ring is also read at d-1, carries the previous
    // iteration's d-1 value in a scalar instead of loading -- the same
    // cell, the same bits (the damp+tap pattern of every damped comb).
    struct AdjHigh {
        Tree        exp;   // the delayed writer
        int         d;     // the collapsed delay
        std::string name;  // the carried scalar
    };
    struct AdjLow {
        Tree        exp;
        int         d;
        std::string var;  // cached variable of the real read at d
    };
    bool fHasEnableControl  = false;  // program uses enable/control : the dup
                                      // inline cache stays off (dying
                                      // primitives, dcond interactions not
                                      // worth debugging -- ondemand replaces)
    bool fMainCompilePhase = false;  // true after prepare : the lazy inline
                                     // duplication must never register strings
                                     // built during prepare's condition-atom
                                     // compilation (names not yet final)
    std::map<Tree, std::set<int>, treeorder> fAdjDelaySets;
    std::vector<AdjHigh>                     fAdjHighs;
    std::vector<AdjLow>                      fAdjLows;
    void censusAdjacentReads(Tree L);
    void emitAdjacentUpdates();
    std::map<Tree, int, treeorder>                fScheduleOrder;
    // -fir bridge : recognized FIR kernels, keyed by their SOURCE tree
    // (the signal whose delay line the kernel reads). value = (read span
    // maxtaps, nonzero coefficient count) -- consumers : delay-line
    // implementation policy, fusion oracle.
    std::map<Tree, std::pair<int, int>, treeorder> fFirFacts;

   public:
    ScalarCompiler(const std::string& name, const std::string& super, int numInputs, int numOutputs)
        : Compiler(name, super, numInputs, numOutputs, false),
          fSharingKey(nullptr),
          fOccMarkup(nullptr),
          fMaxIota(-1)
    {
    }

    ScalarCompiler(Klass* k) : Compiler(k), fSharingKey(nullptr), fOccMarkup(nullptr), fMaxIota(-1)
    {
    }

    virtual void compileMultiSignal(Tree lsig);
    void         compileMultiSignalAux(Tree lsig);
    virtual void compileSingleSignal(Tree lsig);

   protected:
    virtual std::string CS(Tree sig);
    virtual std::string generateCode(Tree sig);
    virtual std::string generateCacheCode(Tree sig, const std::string& exp);
    virtual std::string generateIotaCache(const std::string& exp, bool headSafe = false);
    virtual std::string forceCacheCode(Tree sig, const std::string& exp);
    virtual std::string generateVariableStore(Tree sig, const std::string& exp);

    std::string getFreshID(const std::string& prefix);

    void compilePreparedSignalList(Tree lsig);
    Tree prepare(Tree L0);
    Tree prepare2(Tree L0);

    bool        getCompiledExpression(Tree sig, std::string& name);
    std::string setCompiledExpression(Tree sig, const std::string& name);

    void        setVectorNameProperty(Tree sig, const std::string& vecname);
    bool        getVectorNameProperty(Tree sig, std::string& vecname);
    std::string ensureVectorNameProperty(const std::string altname, Tree sig);

    void        conditionAnnotation(Tree l);
    void        conditionAnnotation(Tree t, Tree nc);
    void        conditionStatistics(Tree l);
    std::string getConditionCode(Tree t);

    // code generation
    std::string         generateXtended(Tree sig);
    virtual std::string generateDelayAccess(Tree sig, Tree arg, Tree size);
    std::string         generateDelayAccessRaw(Tree sig, Tree exp, const std::string& delayidx);
    std::string         generateDelayAccessRaw(Tree sig, Tree exp, int delay);
    std::string         generateFIR(Tree sig, const tvec& coefs);
    std::string         generateIIR(Tree sig, const tvec& coefs);
    std::string         generateSum(Tree sig, const tvec& subs);
    std::string         generatePrefix(Tree sig, Tree x, Tree e);
    std::string         generateBinOp(Tree sig, int opcode, Tree arg1, Tree arg2);

    std::string         generateFFun(Tree sig, Tree ff, Tree largs);
    virtual std::string generateWaveform(Tree sig);

    std::string generateInput(Tree sig, const std::string& idx);
    std::string generateOutput(Tree sig, const std::string& idx, const std::string& arg1);

    std::string generateTable(Tree sig, Tree tsize, Tree content);
    std::string generateStaticTable(Tree sig, Tree tsize, Tree content);
    std::string generateWRTbl(Tree sig, Tree size, Tree gen, Tree wi, Tree ws);
    std::string generateRDTbl(Tree sig, Tree tbl, Tree ri);
    std::string generateSigGen(Tree sig, Tree content);
    std::string generateStaticSigGen(Tree sig, Tree content);

    std::string generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2);

    bool        isSigSimpleRec(Tree sig);
    std::string generateRecProj(Tree sig, Tree exp, int i);
    void        generateRec(Tree sig, Tree var, Tree le);

    std::string generateIntCast(Tree sig, Tree x);
    std::string generateBitCast(Tree sig, Tree x);
    std::string generateFloatCast(Tree sig, Tree x);

    std::string generateButton(Tree sig, Tree label);
    std::string generateCheckbox(Tree sig, Tree label);
    std::string generateVSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
    std::string generateHSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
    std::string generateNumEntry(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);

    std::string generateVBargraph(Tree sig, Tree label, Tree min, Tree max, const std::string& exp);
    std::string generateHBargraph(Tree sig, Tree label, Tree min, Tree max, const std::string& exp);
    std::string generateSoundfile(Tree sig, Tree path);

    std::string generateNumber(Tree sig, const std::string& exp);
    std::string generateFConst(Tree sig, const std::string& file, const std::string& name);
    std::string generateFVar(Tree sig, const std::string& file, const std::string& name);

    virtual std::string generateDelayVec(Tree sig, const std::string& exp, const std::string& ctype,
                                         const std::string& vname, int mxd, int count);
    std::string generateDelayVecNoTemp(Tree sig, const std::string& exp, const std::string& ctype,
                                       const std::string& vname, int mxd, int count);
    virtual std::string generateDelayLine(DelayType dt, const std::string& ctype,
                                          const std::string& vname, int mxd, int count, bool mono,
                                          const std::string& exp, const std::string& ccs);

    void getTypedNames(::Type t, const std::string& prefix, std::string& ctype, std::string& vname);
    void ensureIotaCode();

    void declareWaveform(Tree sig, std::string& vname, int& size);

    virtual std::string generateControl(Tree sig, Tree x, Tree y);

    std::string cnf2code(Tree cc);
    std::string or2code(Tree oc);

    std::string dnf2code(Tree cc);
    std::string and2code(Tree oc);

    virtual DelayType analyzeDelayType(Tree sig);
    DelayType         analyzeDelayTypeAux(Tree sig);
    std::set<Tree>    fResidenceSeen;  // probe dedup (FAUST_SS_RESIDENCE)
};

#endif
