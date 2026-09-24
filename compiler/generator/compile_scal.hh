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
#include <functional>
#include <unordered_map>
#include <utility>

#include "DirectedGraph.hh"
#include "compile.hh"
#include "dcond.hh"
#include "occurrences.hh"
#include "property.hh"
#include "sigtyperules.hh"

// helpers shared by compile_scal.cpp and compile_fam.cpp (the family form)
std::string realLiteral(double r);
void        callWithLargeStack(std::function<void()>& function);
bool        famReadsGroupNow(Tree n, Tree group);

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
    bool cacheWouldStore(Tree sig);  // -xtemp : the cache's rule as a predicate on the annotated tree
    bool passCoversKind(Tree sig);   // -xtemp : the kinds whose storage the pass decides
    Tree placeExplicitTemps(Tree L2, Tree Lx, std::function<void(Tree)> reanalyse);  // -xtemp : the pass
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
    // The display frontier (spec SIGNAUX-ATTACHES) : bargraph stores and
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
    void        emitDisplayWidgets();
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
    // spec LE-SELECTN : side table, no tree surgery -- a certified root
    // keeps its select2 spelling (every downstream walker intact) ; only
    // conditionAnnotation (saturating atoms) and compileSignal (multiplex
    // emission) consult the table. The spine below a root is never
    // compiled from it (dead), unless shared externally (normal path).
    struct SelectNLeaf {
        Tree branch;              // leaf signal for this entry
        std::vector<Tree> atoms;  // dispatch condition, a CONJUNCTION of atoms :
                                  // V1 saturating entries carry one (sel<=0 / sel==k /
                                  // sel>=N-1) ; the V1.2 eq-chain default carries the
                                  // negations (sel!=k0, sel!=k1, ...)
    };
    struct SelectNInfo {
        Tree                     selEff;  // effective INTEGER selector (cast built in real mode)
        std::vector<SelectNLeaf> leaves;  // index order 0..N-1, repeated leaves allowed
    };
    std::map<Tree, SelectNInfo> fSelectNInfo;
    void                        computeSelectNInfo(Tree L);
    std::string                 generateSelectN(Tree sig, const SelectNInfo& info);

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
    std::string         coefCode(Tree coef);
    std::map<Tree, std::string, treeorder> fHoistedCoef;  // kernel coefficients stored at their rate
    std::string         generateIIR(Tree sig, const tvec& coefs);
    std::string         generateSum(Tree sig, const tvec& subs);
    // the family form (-fam, LA-FORME-FAMILLE) : an isomorphic family of sum
    // operands emitted as one inner loop over structure-of-arrays members
    struct FamCtx;
    struct FamPlan {
        std::vector<int>               members;   // candidate indices (operands of the sum, or output channels)
        std::vector<Tree>              trees;     // the members themselves, in the same order, grouped by host
        Tree                           tmpl = nullptr;  // the template member : trees[0] unless a leaf it shares is not shared by the others
        std::vector<std::vector<Tree>> slots;     // [member][slot] coefficient tree
        std::vector<Tree>              leaves;    // the template's slot leaves
        std::vector<std::vector<Tree>> aslots;    // [member][audio slot] the input read by the member
        std::vector<Tree>              aleaves;   // the template's audio slot leaves
        std::set<Tree>                 commons;   // common inputs
        std::set<Tree>                 priv;      // private nodes of every member
        std::vector<Tree>              hosts;     // the sums the members feed (nullptr : the outputs)
        std::vector<int>               memberHost;  // member -> index in hosts
        // a cellular automaton (LES-AUTOMATES) : the members are definitions of
        // one recursive group, the audio slots its projections read at delay >= 1
        Tree                           group = nullptr;   // the host group
        int                            groupSize = 0;     // its number of definitions
        std::vector<int>               memberDef;         // member -> its definition index
        std::vector<int>               aslotBase;         // audio slot -> the projection read is member's definition + base (INT_MIN : a table)
        int                            groupDepth = 0;    // the deepest delay read on the group
        std::vector<std::pair<int, int>> runs;           // the members in runs of contiguous definitions [lo, hi)
        std::vector<std::pair<Tree, std::string>> regs;  // the projections' expressions, registered when the automaton is emitted
        std::vector<Tree>              borderInputs;      // what the definitions computed before the loop read from outside the group (order check)
        Tree                           ktemplate = nullptr;  // -fam -fir : the template with its kernels formed once for the family (famKernelizeTemplate)
        std::unordered_map<Tree, Tree> thaw;                 // its opaque leaves -> the template's slot leaves and commons
        std::vector<int>               defsBefore;        // the other definitions computed before the loop (read by the cells at the current step), in dependency order
        std::vector<int>               defsAfter;         // and after it
        int                            id = -1;           // fixed at plan time for an automaton (its expressions are registered then)
        bool                           emitted = false;
        std::string                    outName;   // the array of results, once emitted
        std::vector<std::string>       hostExpr;  // per host, the reduction of its members, once emitted
    };
    std::vector<FamPlan>           fFamilies;    // the families planned before the schedule, by shape class
    std::map<Tree, int>            fFamHost;     // host sum -> family index
    std::map<Tree, int>            fFamGroup;    // host group of an automaton -> family index
    std::set<Tree>                 fFamPrivate;  // nodes compiled by a family loop, never on their own
    void                           planFamilies();
    void                           planFamilyClasses(Tree root, std::vector<FamPlan>& out, bool typed);
    bool                           planFamilyClass(const std::vector<Tree>& nodes, FamPlan& plan, bool typed, std::string& why,
                                                   const std::set<Tree>* holes = nullptr, void* shapes = nullptr);
    void                           checkFamilyOrder();
    void                           famScheduleEdges(digraph<Tree>& G);
    bool                           famAutoRead(Tree exp, int delay, std::string& out);  // an automaton's projection read at a constant delay : its arrays  // before the schedule : every input of a family before its first host
    bool                           emitFamilyLoop(FamPlan& plan, bool reduce, std::string& name, std::string& why,
                                                  const std::vector<std::pair<int, int>>* ranges = nullptr);
    void                           emitFamily(FamPlan& plan);  // the loop and the per-host reductions, once
    std::set<Tree>                 famKeepSums(Tree L);  // the sums lowerSums must leave n-ary
    // families first, kernels after (LES-AUTOMATES §9) : the families' subtrees
    // are frozen into opaque leaves while the kernel passes run on the rest of
    // the tree, and each family's template gets its kernels formed once, alone
    bool                           fFamPlanned = false;  // the plan was made in prepare (the -fam -fir order)
    Tree                           famFreeze(Tree root, const std::set<Tree>& frozen, std::unordered_map<Tree, Tree>& back, bool typed);
    Tree                           famThaw(Tree root, const std::unordered_map<Tree, Tree>& back);
    std::set<Tree>                 famFrozenSet(Tree L2);
    Tree                           famAround(Tree L2, const std::function<Tree(Tree)>& pass);  // a rewrite with the families frozen
    void                           emitFamAlignContract();
    Tree                           famKernelizeOutside(Tree L2);
    void                           famKernelizeTemplate(FamPlan& plan);
    std::string                    famSlowCode(FamCtx& g, Tree t, int m, bool& ok, bool& perMember);  // a slow subtree of the kernelized template, for member m
    void                           famCheckPlanned(Tree L2);  // after the harvest : the planned families' nodes must still be the tree's
    void                           famEmitterStructures();    // the hosts, groups, private nodes and registrations, keyed by the tree's nodes
    std::string                    generateFamilySum(Tree sig, const tvec& subs, bool& ok);
    std::string                    famExpr(FamCtx& g, Tree t);
    std::string                    famHist(FamCtx& g, Tree x, int k);
    bool                           famPrivateOnly(const std::set<Tree>& priv, const std::set<Tree>& hosts, bool outputs, Tree group = nullptr);
    Tree                           fFamRoot = nullptr;
    // -fam alone : the plan is made on a VIEW of the tree (its audio sums
    // revealed n-ary, built at plan time), the code is emitted from the tree
    // itself, so that -fam changes nothing outside its families ; a view
    // node's origin is the tree node it stands for (revealSum records them),
    // itself when it was not rebuilt
    std::unordered_map<Tree, Tree> fFamOrigin;
    std::unordered_map<Tree, std::vector<Tree>> fFamConsumed;  // a view sum -> the tree's binary sums it absorbed (skipped with it)
    std::set<Tree>                 fFamComputed;  // the tree's nodes whose expression a family registered (members stored in arrays, an automaton's projections)
    Tree                           famOrig(Tree t) const
    {
        auto it = fFamOrigin.find(t);
        return it == fFamOrigin.end() ? t : it->second;
    }
    std::string famCS(Tree t);    // the code of what a family reads : the tree's node, or a form the view made
    std::string famCoef(Tree t);  // the same for a slow coefficient (coefCode)
    std::map<Tree, std::set<Tree>> fFamParents;
    std::map<Tree, std::pair<Tree, int>> fFamDefCell;  // a cell of a group's definition list -> (group, definition index)
    bool                           fFamParentsBuilt = false;
    int                            fFamCount        = 0;
    bool                           fFamAlignContract = false;  // -fam-align : the contract check is emitted once per class
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
};

#endif
