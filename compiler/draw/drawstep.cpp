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

/**
 * @file drawstep.cpp
 * Steppable SVG diagrams (-sst <n>), see drawstep.hh.
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <functional>
#include <map>
#include <set>
#include <sstream>
#include <tuple>
#include <utility>
#include <vector>

#include "signalRenderer.hh"

#include "SVGDev.h"
#include "description.hh"
#include "drawstep.hh"
#include "exception.hh"
#include "global.hh"
#include "labels.hh"
#include "normalform.hh"
#include "propagate.hh"
#include "recSchema.h"
#include "schema.h"
#include "sigIdentity.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"

using namespace std;

// Sample rate used to compute the values (ma.SR)
static const int kStepSampleRate = 44100;

//------------------------- recorded schemas ----------------------------

struct StepRecord {
    schema*     fSchema;
    siglist     fIns;
    siglist     fOuts;
    Tree        fRecs;
    StepKind    fKind;
    std::string fName;
    bool        fIsRec;    // a recursion : fDelayed are the inputs of its feedback diagram
    siglist     fDelayed;  // ... expressed inside the recursion (fDelayRecs)
    Tree        fDelayRecs;
};

static std::vector<StepRecord>  gStepRecords;  // schemas of the file being generated
static std::vector<std::string> gStepLinks;    // targets of its folded blocks, by number

// Values of a closed signal for samples 0 to n-1, cached for the whole drawing
struct StepValues {
    bool                fOK    = false;
    bool                fIsInt = false;
    std::vector<double> fValues;
};
static std::map<Tree, StepValues> gStepValues;

// -ssc : a control set to a value from a sample on
struct StepControlChange {
    std::string fLabel;
    double      fValue;
    int         fSample;
};
static std::vector<StepControlChange> gStepControlChanges;

// The label of a widget as SignalRenderer knows it : the last element of its normalized
// path, without metadata
static std::string widgetLabel(Tree label)
{
    return removeMetadata(tree2str(hd(normalizePath(cons(label, gGlobal->nil)))));
}

static void collectControlLabels(Tree t, std::set<Tree>& seen, std::set<std::string>& labels)
{
    if (!seen.insert(t).second) {
        return;
    }
    Tree label, cur, min, max, step;
    if (isBoxButton(t, label) || isBoxCheckbox(t, label) ||
        isBoxVSlider(t, label, cur, min, max, step) ||
        isBoxHSlider(t, label, cur, min, max, step) ||
        isBoxNumEntry(t, label, cur, min, max, step)) {
        labels.insert(widgetLabel(label));
        return;
    }
    for (Tree b : t->branches()) {
        collectControlLabels(b, seen, labels);
    }
}

void stepCheckControls(Tree process)
{
    gStepControlChanges.clear();
    if (gGlobal->gSVGStepControls.empty()) {
        return;
    }
    std::set<Tree>        seen;
    std::set<std::string> labels;
    collectControlLabels(process, seen, labels);
    for (const std::string& spec : gGlobal->gSVGStepControls) {
        size_t      eq = spec.rfind('=');
        size_t      at = spec.rfind('@');
        std::string label, value, sample = "0";
        if (eq != std::string::npos && eq > 0) {
            label = spec.substr(0, eq);
            value = (at != std::string::npos && at > eq) ? spec.substr(eq + 1, at - eq - 1)
                                                         : spec.substr(eq + 1);
            if (at != std::string::npos && at > eq) {
                sample = spec.substr(at + 1);
            }
        }
        char*  end1 = nullptr;
        char*  end2 = nullptr;
        double v    = value.empty() ? 0 : strtod(value.c_str(), &end1);
        long   n    = sample.empty() ? -1 : strtol(sample.c_str(), &end2, 10);
        if (label.empty() || value.empty() || *end1 != 0 || sample.empty() || *end2 != 0 || n < 0) {
            stringstream error;
            error << "ERROR : -ssc (--svg-step-control) expects label=value or label=value@n, "
                     "got '"
                  << spec << "'" << endl;
            throw faustexception(error.str());
        }
        if (labels.find(label) == labels.end()) {
            stringstream error;
            error << "ERROR : -ssc (--svg-step-control) '" << spec << "' : no control labelled '"
                  << label << "' in process";
            if (!labels.empty()) {
                error << " (controls :";
                for (const std::string& l : labels) {
                    error << " '" << l << "'";
                }
                error << ")";
            }
            error << endl;
            throw faustexception(error.str());
        }
        gStepControlChanges.push_back({label, v, int(n)});
    }
    std::stable_sort(gStepControlChanges.begin(), gStepControlChanges.end(),
                     [](const StepControlChange& a, const StepControlChange& b) {
                         return a.fSample < b.fSample;
                     });
}

void stepBeginFile()
{
    gStepRecords.clear();
    gStepLinks.clear();
}

int stepAddLink(const std::string& target)
{
    gStepLinks.push_back(target);
    return int(gStepLinks.size()) - 1;
}

void stepRecord(schema* s, const StepContext& ctx, const siglist& outs, StepKind kind,
                const std::string& name)
{
    StepRecord r{s, ctx.fIns, outs, ctx.fRecs, kind, name, false, {}, nullptr};
    gStepRecords.push_back(r);
}

void stepRecordDelays(schema* rec, const siglist& delayed, Tree recs)
{
    StepRecord r{rec, {}, {}, gGlobal->nil, kStepWiring, "", true, delayed, recs};
    gStepRecords.push_back(r);
}

siglist stepOutputs(Tree t, const StepContext& ctx)
{
    Tree a, b;
    if (isBoxMetadata(t, a, b)) {
        return stepOutputs(a, ctx);
    }
    return propagate(ctx.fSlotEnv, ctx.fPath, t, ctx.fIns);
}

//------------------------- closing open signals ------------------------

// Inside A ~ B, propagate() builds the signals with de Bruijn references: ref(1)
// is the recursive group of the innermost enclosing recursion. To compute the
// value of a wire, its signal is closed by substituting every reference by its
// group, from the innermost recursion outward.

typedef std::map<std::pair<Tree, int>, Tree> InstMemo;

// Replace in t, under d binders, the references to the group (ref(d+1)) by g, whose
// free references are relative to the level of the group, and lower the deeper free
// references by one : the result is expressed at the level of g.
static Tree instantiate(Tree t, int d, Tree g, InstMemo& memo)
{
    if (t->aperture() <= d) {
        return t;
    }
    std::pair<Tree, int> key(t, d);
    auto                 it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }
    Tree r, body;
    int  k;
    if (isRef(t, k)) {
        if (k == d + 1) {
            r = g;
            for (int i = 0; i < d; i++) {
                r = lift(r);
            }
        } else if (k > d + 1) {
            r = ref(k - 1);
        } else {
            r = t;
        }
    } else if (isRec(t, body)) {
        r = rec(instantiate(body, d + 1, g, memo));
    } else {
        tvec br;
        for (Tree x : t->branches()) {
            br.push_back(instantiate(x, d, g, memo));
        }
        r = tree(t->node(), br);
    }
    memo[key] = r;
    return r;
}

static std::map<std::pair<Tree, Tree>, Tree> gClosed;

static Tree closeSignal(Tree sig, Tree recs)
{
    if (isNil(recs) || sig->aperture() <= 0) {
        return sig;
    }
    std::pair<Tree, Tree> key(sig, recs);
    auto                  it = gClosed.find(key);
    if (it != gClosed.end()) {
        return it->second;
    }
    Tree s = sig;
    for (Tree l = recs; !isNil(l); l = tl(l)) {
        InstMemo memo;
        s = instantiate(s, 0, hd(l), memo);
    }
    faustassert(s->aperture() <= 0);
    gClosed[key] = s;
    return s;
}

//------------------------- computing the values ------------------------

// As in createSignalDSPFactoryFromString : prefix(x, y) is rendered as prefix(x, mem(y))
class StepSignalPrefix : public SignalIdentity {
   protected:
    virtual Tree transformation(Tree sig)
    {
        Tree x, y;
        if (isSigPrefix(sig, x, y)) {
            return sigPrefix(self(x), sigDelay1(self(y)));
        } else {
            return SignalIdentity::transformation(sig);
        }
    }
};

// Signals the renderer cannot compute from the program alone
struct StepChecker : public SignalVisitor {
    void visit(Tree sig) override
    {
        Tree x, y;
        if (isSigSoundfile(sig, x) || isSigSoundfileLength(sig, x, y) ||
            isSigSoundfileRate(sig, x, y)) {
            throw faustexception("soundfile");
        }
        SignalVisitor::visit(sig);
    }
};

// Renders samples [offset, offset + count) of the signals : the samples before offset are
// computed in chunks and dropped, and the computation is cut at each control change (-ssc).
template <class REAL>
static void renderList(const tvec& sigs, int count, std::vector<std::vector<FAUSTFLOAT>>& out)
{
    const int            kChunk = 4096;
    int                  offset = gGlobal->gSVGStepOffset;
    int                  ns     = int(sigs.size());
    signal_dsp_aux<REAL> dsp(0, ns, listConvert(sigs));
    dsp.init(kStepSampleRate);
    out.assign(ns, std::vector<FAUSTFLOAT>(count, 0));
    std::vector<std::vector<FAUSTFLOAT>> scratch(ns, std::vector<FAUSTFLOAT>(kChunk, 0));
    std::vector<FAUSTFLOAT*>             ptrs(ns);

    std::vector<int> cuts{0, offset, offset + count};
    for (const StepControlChange& c : gStepControlChanges) {
        if (c.fSample < offset + count) {
            cuts.push_back(c.fSample);
        }
    }
    std::sort(cuts.begin(), cuts.end());
    cuts.erase(std::unique(cuts.begin(), cuts.end()), cuts.end());

    for (size_t s = 0; s + 1 < cuts.size(); s++) {
        int a = cuts[s], b = cuts[s + 1];
        for (const StepControlChange& c : gStepControlChanges) {
            if (c.fSample == a) {
                for (auto& it : dsp.fRenderer.fInputControls) {
                    if (it.second.fLabel == c.fLabel) {
                        it.second.fZone = FAUSTFLOAT(c.fValue);
                    }
                }
            }
        }
        for (int t = a; t < b; t += kChunk) {
            int len = std::min(kChunk, b - t);
            for (int k = 0; k < ns; k++) {
                ptrs[k] = (t >= offset) ? out[k].data() + (t - offset) : scratch[k].data();
            }
            dsp.compute(len, nullptr, ptrs.data());
        }
    }
}

// Compute the values of closed signals, throws faustexception on failure
static void renderBatch(const std::vector<Tree>& sigs)
{
    int              count = gGlobal->gSVGStepSamples;
    Tree             norm  = simplifyToNormalForm(listConvert(sigs));
    StepSignalPrefix prefix;
    norm = prefix.mapself(norm);
    typeAnnotation(norm, gGlobal->gLocalCausalityCheck);
    tvec ns = treeConvert(norm);
    if (ns.size() != sigs.size()) {
        throw faustexception("ERROR : -sst, unexpected normal form\n");
    }

    // keep the signals the renderer can compute
    tvec             good;
    std::vector<int> where(ns.size(), -1);
    for (size_t i = 0; i < ns.size(); i++) {
        try {
            Tree one = cons(ns[i], gGlobal->nil);  // visitRoot walks a list
            signal_dsp_factory::SignalChecker c1;
            c1.visitRoot(one);
            StepChecker c2;
            c2.visitRoot(one);
            where[i] = int(good.size());
            good.push_back(ns[i]);
        } catch (faustexception&) {
        }
    }

    std::vector<std::vector<FAUSTFLOAT>> out;
    if (!good.empty()) {
        if (gGlobal->gFloatSize == 1) {
            renderList<float>(good, count, out);
        } else {
            renderList<double>(good, count, out);
        }
    }
    for (size_t i = 0; i < ns.size(); i++) {
        StepValues v;
        if (where[i] >= 0) {
            v.fOK    = true;
            v.fIsInt = getCertifiedSigType(ns[i])->nature() == kInt;
            v.fValues.assign(out[where[i]].begin(), out[where[i]].end());
        }
        gStepValues[sigs[i]] = v;
    }
}

static void computeValues(const std::vector<Tree>& sigs)
{
    std::vector<Tree> todo;
    for (Tree s : sigs) {
        if (gStepValues.find(s) == gStepValues.end()) {
            todo.push_back(s);
        }
    }
    if (todo.empty()) {
        return;
    }
    try {
        renderBatch(todo);
    } catch (faustexception&) {
        // one signal spoils the batch : compute them one by one
        for (Tree s : todo) {
            try {
                renderBatch(std::vector<Tree>(1, s));
            } catch (faustexception&) {
                gStepValues[s] = StepValues();
            }
        }
    }
}

static void clearStepFiles();

siglist stepInputSignals(Tree inputBox, int numInputs)
{
    gStepValues.clear();
    gClosed.clear();
    clearStepFiles();
    siglist ins;
    if (numInputs == 0) {
        return ins;
    }
    int bins, bouts;
    if (!getBoxType(inputBox, &bins, &bouts) || bins != 0 || (bouts != 1 && bouts != numInputs)) {
        stringstream error;
        error << "ERROR : the test signal of -ssi (--svg-step-input) '" << gGlobal->gSVGStepInput
              << "' must have no input and "
              << ((numInputs == 1) ? std::string("1 output")
                                   : "1 or " + std::to_string(numInputs) + " outputs")
              << " (the inputs of process), here it has " << bins << " input(s) and " << bouts
              << " output(s)" << endl;
        throw faustexception(error.str());
    }
    siglist outs = propagate(gGlobal->nil, gGlobal->nil, inputBox, siglist());
    for (int i = 0; i < numInputs; i++) {
        // the inputs of a Faust program are float signals
        ins.push_back(sigFloatCast(outs[(bouts == 1) ? 0 : i]));
    }
    return ins;
}

//------------------------- writing the SVG ------------------------------

// A value label
struct StepLabel {
    double fX, fY;
    char   fAnchor;  // a: start above the wire, b: end below, r: start centered, l: end centered
    int    fSig;
    std::string fClass;   // "", "d" (delay) or "io"
    std::string fPrefix;  // shown before the value (in0:, out0:)
};

static std::string xmlEscape(const std::string& s)
{
    std::string r;
    for (char c : s) {
        switch (c) {
            case '<':
                r += "&lt;";
                break;
            case '>':
                r += "&gt;";
                break;
            case '&':
                r += "&amp;";
                break;
            case '"':
                r += "&quot;";
                break;
            default:
                r += c;
        }
    }
    return r;
}

static std::string jsonString(const std::string& s)
{
    std::string r = "\"";
    for (unsigned char c : s) {
        if (c == '"' || c == '\\') {
            r += '\\';
            r += char(c);
        } else if (c == '<' || c == '>' || c == '&' || c < 0x20) {
            char buf[8];
            snprintf(buf, sizeof(buf), "\\u%04x", c);
            r += buf;
        } else {
            r += char(c);
        }
    }
    return r + "\"";
}

static std::string jsNumber(double v, bool isInt)
{
    // JSON has no NaN or infinities : they are written as strings, read back by the player
    if (std::isnan(v)) {
        return "\"NaN\"";
    } else if (std::isinf(v)) {
        return (v > 0) ? "\"Infinity\"" : "\"-Infinity\"";
    }
    char buf[64];
    if (isInt) {
        snprintf(buf, sizeof(buf), "%.0f", v);
    } else {
        snprintf(buf, sizeof(buf), "%.9g", v);
    }
    return buf;
}

extern const char* gStepPlayerCSS;
extern const char* gStepPlayerJS1;
extern const char* gStepPlayerJS2;
extern const char* gStepPlayerJS3;

// A file of the drawing, prepared : the values of all the files are computed in one batch
// once every file is prepared (computing them file by file recomputes the shared upstream
// signals in each batch), then the files are written.
struct StepFile {
    std::string               fPath;
    int                       fUse;    // the index of this use among the uses of the box
    std::string               fBack;   // the back link of this use : parent file and use
    std::vector<std::string>  fLinks;  // the targets of its folded blocks, by number
    schema*                   fTop;
    collector*                fTraits;
    std::vector<Tree>         fSigs;   // closed signals, indexed as in the SVG
    std::vector<std::string>  fDescs;  // their descriptions
    std::vector<StepLabel>    fLabels;
    std::vector<const trait*> fWires;  // the visible wires
    std::vector<int>          fTags;   // the signal of each visible wire, or -1
    std::vector<int>          fIns, fOuts, fDelays, fControls;
};
static std::vector<StepFile> gStepFiles;

// The uses (contexts) of each folded box : key (box and context) -> index of the use
static std::map<Tree, int> gUseIndex;
static std::map<Tree, int> gUseCount;

int stepContextIndex(Tree box, Tree key)
{
    auto it = gUseIndex.find(key);
    if (it != gUseIndex.end()) {
        return it->second;
    }
    int k          = gUseCount[box]++;
    gUseIndex[key] = k;
    return k;
}

static void clearStepFiles()
{
    gStepFiles.clear();
    gUseIndex.clear();
    gUseCount.clear();
}

static void prepareFile(StepFile& f)
{
    collector&                c        = *f.fTraits;
    std::vector<Tree>&        sigs     = f.fSigs;
    std::vector<std::string>& descs    = f.fDescs;
    std::vector<StepLabel>&   labels   = f.fLabels;
    std::vector<int>&         ioIns    = f.fIns;
    std::vector<int>&         ioOuts   = f.fOuts;
    std::vector<int>&         delays   = f.fDelays;
    std::vector<int>&         controls = f.fControls;
    std::map<Tree, int>       index;
    std::map<point, int>      known;

    // 1) the signals of the file, closed, and the points they leave from

    auto intern = [&](Tree sig, Tree recs, const std::string& desc) -> int {
        Tree closed = closeSignal(sig, recs);
        auto it     = index.find(closed);
        if (it != index.end()) {
            if (descs[it->second].empty()) {
                descs[it->second] = desc;
            }
            return it->second;
        }
        int k         = int(sigs.size());
        index[closed] = k;
        sigs.push_back(closed);
        descs.push_back(desc);
        return k;
    };
    auto setPoint = [&](const point& p, int k) {
        if (known.find(p) == known.end()) {
            known[p] = k;
        }
    };

    for (const StepRecord& r : gStepRecords) {
        schema* s = r.fSchema;
        if (r.fIsRec) {
            recSchema* rs = dynamic_cast<recSchema*>(s);
            faustassert(rs);
            for (unsigned int i = 0; i < rs->feedbacks() && i < r.fDelayed.size(); i++) {
                point from, to;
                rs->feedbackLine(i, from, to);
                int k = intern(r.fDelayed[i], r.fDelayRecs,
                               "one-sample delay of the recursion: the fed-back value at n-1");
                setPoint(from, k);
                delays.push_back(k);
                bool lr = s->orientation() == kLeftRight;
                labels.push_back(
                    {from.x + (lr ? 1.2 : -1.2), (from.y + to.y) / 2, lr ? 'r' : 'l', k, "d", ""});
            }
            continue;
        }
        bool lr = s->orientation() == kLeftRight;
        for (unsigned int i = 0; i < s->inputs() && i < r.fIns.size(); i++) {
            std::string desc = (r.fKind == kStepIO) ? "input " + std::to_string(i) : "";
            int         k    = intern(r.fIns[i], r.fRecs, desc);
            point       p    = s->inputPoint(i);
            setPoint(p, k);
            if (r.fKind == kStepIO) {
                labels.push_back({p.x - 1.5, p.y, 'l', k, "io", "in" + std::to_string(i) + ": "});
                ioIns.push_back(k);
            }
        }
        for (unsigned int i = 0; i < s->outputs() && i < r.fOuts.size(); i++) {
            std::string desc;
            if (r.fKind == kStepBlock || r.fKind == kStepControl || r.fKind == kStepLiteral) {
                desc = r.fName;
                if (s->outputs() > 1) {
                    desc += " (output " + std::to_string(i) + ")";
                }
            } else if (r.fKind == kStepIO) {
                desc = "output " + std::to_string(i);
            }
            int   k = intern(r.fOuts[i], r.fRecs, desc);
            point p = s->outputPoint(i);
            setPoint(p, k);
            if (r.fKind == kStepControl) {
                controls.push_back(k);
            }
            if (r.fKind == kStepBlock || r.fKind == kStepControl) {
                // at the edge of the block, on its output wire
                if (lr) {
                    labels.push_back({p.x - dHorz + 1.2, p.y - 1.3, 'a', k, "", ""});
                } else {
                    labels.push_back({p.x + dHorz - 1.2, p.y + 1.3, 'b', k, "", ""});
                }
            } else if (r.fKind == kStepIO) {
                labels.push_back({p.x + 4.5, p.y, 'r', k, "io", "out" + std::to_string(i) + ": "});
                ioOuts.push_back(k);
            }
        }
    }

    // 2) the signal of each visible wire : the one of the point it leaves from (or else
    // of the point it reaches), propagated along the wire
    c.computeVisibleTraits();
    std::vector<const trait*>& wires = f.fWires;
    for (const trait& t : c.fTraits) {
        if (c.isVisible(t)) {
            wires.push_back(&t);
        }
    }
    std::vector<int>& tag = f.fTags;
    tag.assign(wires.size(), -1);
    for (bool changed = true; changed;) {
        changed = false;
        for (bool forward = true; forward;) {
            forward = false;
            for (size_t i = 0; i < wires.size(); i++) {
                if (tag[i] < 0) {
                    auto it = known.find(wires[i]->start);
                    if (it != known.end()) {
                        tag[i] = it->second;
                        setPoint(wires[i]->end, tag[i]);
                        forward = changed = true;
                    }
                }
            }
        }
        for (size_t i = 0; i < wires.size(); i++) {
            if (tag[i] < 0) {
                auto it = known.find(wires[i]->end);
                if (it != known.end()) {
                    tag[i] = it->second;
                    setPoint(wires[i]->start, tag[i]);
                    changed = true;
                }
            }
        }
    }
}

// "freeverb-123.svg#c=1" -> "freeverb (use 2)" : how a use names the diagram it comes from
static std::string useOrigin(const std::string& back)
{
    if (back.empty()) {
        return "";
    }
    std::string file = back.substr(0, back.find('#'));
    std::string name = file.substr(0, file.rfind('.'));
    size_t      dash = name.rfind('-');
    if (dash != std::string::npos && dash > 0 &&
        name.find_first_not_of("0123456789", dash + 1) == std::string::npos) {
        name = name.substr(0, dash);
    }
    size_t c = back.find("#c=");
    if (c != std::string::npos && back.substr(c + 3) != "0") {
        name += " (use " + std::to_string(std::atoi(back.c_str() + c + 3) + 1) + ")";
    }
    return name;
}

// Writes the uses of a box in one file : the drawing of the first use, and for each use its
// values. A wire or a label is a slot : the slots are the distinct tuples of the signals the
// element carries in each use, so that each use gives every slot its own value.
static void emitUses(SVGDev& dev, const std::vector<const StepFile*>& uses)
{
    const StepFile& f0 = *uses[0];
    size_t          nu = uses.size();
    for (const StepFile* f : uses) {
        faustassert(f->fWires.size() == f0.fWires.size() &&
                    f->fLabels.size() == f0.fLabels.size() && f->fIns.size() == f0.fIns.size() &&
                    f->fOuts.size() == f0.fOuts.size() && f->fDelays.size() == f0.fDelays.size() &&
                    f->fControls.size() == f0.fControls.size());
    }
    std::map<std::vector<int>, int> slotOf;
    std::vector<std::vector<int>>   slots;  // slot -> the signal it carries in each use
    auto                            slot = [&](std::function<int(const StepFile&)> sig) -> int {
        std::vector<int> t;
        bool             any = false;
        for (const StepFile* f : uses) {
            t.push_back(sig(*f));
            any = any || t.back() >= 0;
        }
        if (!any) {
            return -1;
        }
        auto it = slotOf.find(t);
        if (it != slotOf.end()) {
            return it->second;
        }
        int k     = int(slots.size());
        slotOf[t] = k;
        slots.push_back(t);
        return k;
    };
    std::vector<int> wireSlot, labelSlot;
    for (size_t i = 0; i < f0.fWires.size(); i++) {
        wireSlot.push_back(slot([i](const StepFile& f) { return f.fTags[i]; }));
    }
    for (size_t i = 0; i < f0.fLabels.size(); i++) {
        labelSlot.push_back(slot([i](const StepFile& f) { return f.fLabels[i].fSig; }));
    }
    auto slotList = [&](std::function<const std::vector<int>&(const StepFile&)> list) {
        std::vector<int> r;
        for (size_t i = 0; i < list(f0).size(); i++) {
            r.push_back(slot([&, i](const StepFile& f) { return list(f)[i]; }));
        }
        return r;
    };
    std::vector<int> ins =
        slotList([](const StepFile& f) -> const std::vector<int>& { return f.fIns; });
    std::vector<int> outs =
        slotList([](const StepFile& f) -> const std::vector<int>& { return f.fOuts; });
    std::vector<int> delays =
        slotList([](const StepFile& f) -> const std::vector<int>& { return f.fDelays; });
    std::vector<int> controls =
        slotList([](const StepFile& f) -> const std::vector<int>& { return f.fControls; });

    // 4) the wires, then invisible wider copies to hover them, then the value labels
    stringstream out;
    out << "<g class=\"fsw\">\n";
    for (size_t i = 0; i < f0.fWires.size(); i++) {
        const trait* t = f0.fWires[i];
        char         buf[512];
        snprintf(buf, sizeof(buf),
                 "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"  style=\"stroke:black; "
                 "stroke-linecap:round; stroke-width:0.25;\"",
                 t->start.x, t->start.y, t->end.x, t->end.y);
        out << buf;
        if (wireSlot[i] >= 0) {
            out << " data-s=\"" << wireSlot[i] << "\"";
        }
        out << "/>\n";
    }
    out << "</g>\n<g class=\"fsh\">\n";
    for (size_t i = 0; i < f0.fWires.size(); i++) {
        if (wireSlot[i] >= 0) {
            const trait* t = f0.fWires[i];
            char         buf[256];
            snprintf(buf, sizeof(buf), "<line x1=\"%.3f\" y1=\"%.3f\" x2=\"%.3f\" y2=\"%.3f\"",
                     t->start.x, t->start.y, t->end.x, t->end.y);
            out << buf << " data-s=\"" << wireSlot[i] << "\"/>\n";
        }
    }
    out << "</g>\n<g class=\"fsv\">\n";
    for (size_t i = 0; i < f0.fLabels.size(); i++) {
        const StepLabel& l = f0.fLabels[i];
        if (labelSlot[i] < 0) {
            continue;
        }
        char buf[128];
        snprintf(buf, sizeof(buf), "translate(%.3f,%.3f)", l.fX, l.fY);
        out << "<g class=\"v" << (l.fClass.empty() ? "" : " " + l.fClass) << "\" data-s=\""
            << labelSlot[i] << "\" data-a=\"" << l.fAnchor << "\"";
        if (!l.fPrefix.empty()) {
            out << " data-p=\"" << xmlEscape(l.fPrefix) << "\"";
        }
        out << " transform=\"" << buf << "\"><rect/><text/></g>\n";
    }
    out << "</g>\n";

    // 5) the values of each use and the player
    out << "<style type=\"text/css\"><![CDATA[" << gStepPlayerCSS << "]]></style>\n";
    // the data, which no browser runs, then the player (see stepWriteFiles for the contract)
    out << "<script type=\"application/json\" class=\"faust-svg-step-data\">{\"n\":"
        << gGlobal->gSVGStepSamples << ",\"input\":" << jsonString(gGlobal->gSVGStepInput)
        << ",\"sr\":" << kStepSampleRate << ",\"o\":" << gGlobal->gSVGStepOffset;
    std::string ctl;
    for (const std::string& c : gGlobal->gSVGStepControls) {
        ctl += (ctl.empty() ? "" : ", ") + c;
    }
    out << ",\"ctl\":" << jsonString(ctl) << ",\"ctx\":[";
    auto indices = [&](const char* key, const std::vector<int>& v) {
        out << ",\"" << key << "\":[";
        for (size_t k = 0; k < v.size(); k++) {
            out << (k ? "," : "") << v[k];
        }
        out << "]";
    };
    for (size_t u = 0; u < nu; u++) {
        const StepFile& f = *uses[u];
        out << (u ? ",\n" : "\n") << "{\"back\":" << jsonString(f.fBack)
            << ",\"from\":" << jsonString(useOrigin(f.fBack)) << ",\"links\":[";
        for (size_t k = 0; k < f.fLinks.size(); k++) {
            out << (k ? "," : "") << jsonString(f.fLinks[k]);
        }
        out << "]";
        indices("in", ins);
        indices("out", outs);
        indices("z", delays);
        indices("c", controls);
        out << ",\"s\":[\n";
        for (size_t k = 0; k < slots.size(); k++) {
            int sig = slots[k][u];
            out << (k ? ",\n" : "");
            if (sig < 0) {
                out << "{\"d\":\"\"}";
                continue;
            }
            Tree              closed = f.fSigs[sig];
            const StepValues& v      = gStepValues[closed];
            out << "{\"d\":" << jsonString(f.fDescs[sig]);
            int    iv;
            double rv;
            if (isSigInt(closed, &iv) || isSigReal(closed, &rv)) {
                out << ",\"k\":1";  // a literal number : given, never guessed
            }
            if (v.fOK) {
                out << ",\"i\":" << (v.fIsInt ? 1 : 0) << ",\"v\":[";
                for (size_t j = 0; j < v.fValues.size(); j++) {
                    out << (j ? "," : "") << jsNumber(v.fValues[j], v.fIsInt);
                }
                out << "]";
            }
            out << "}";
        }
        out << "]}";
    }
    out << "]}</script>\n<script type=\"text/javascript\" class=\"faust-svg-step\"><![CDATA["
        << gStepPlayerJS1 << gStepPlayerJS2 << gStepPlayerJS3 << "]]></script>\n";
    dev.raw(out.str());
}

void stepDeferFile(const std::string& path, int use, const std::string& back, schema* top,
                   collector* traits)
{
    gStepFiles.push_back(StepFile());
    StepFile& f = gStepFiles.back();
    f.fPath     = path;
    f.fUse      = use;
    f.fBack     = back;
    f.fLinks    = gStepLinks;
    f.fTop      = top;
    f.fTraits   = traits;
    prepareFile(f);
}

void stepWriteFiles()
{
    // 3) the values of all the files, in one batch
    std::vector<Tree> all;
    std::set<Tree>    seen;
    for (const StepFile& f : gStepFiles) {
        for (Tree s : f.fSigs) {
            if (seen.insert(s).second) {
                all.push_back(s);
            }
        }
    }
    computeValues(all);

    // the uses of each box, in the order of their index, in one file
    std::vector<std::string>                            order;
    std::map<std::string, std::vector<const StepFile*>> files;
    for (const StepFile& f : gStepFiles) {
        if (files.find(f.fPath) == files.end()) {
            order.push_back(f.fPath);
        }
        files[f.fPath].push_back(&f);
    }
    for (const std::string& path : order) {
        std::vector<const StepFile*>& uses = files[path];
        std::stable_sort(uses.begin(), uses.end(),
                         [](const StepFile* a, const StepFile* b) { return a->fUse < b->fUse; });
        const StepFile& f0  = *uses[0];
        double          top = kStepTopBand + ((uses.size() > 1) ? kStepUseBand : 0);
        SVGDev          dev(path.c_str(), f0.fTop->width(), f0.fTop->height(), top, kStepMinWidth);
        f0.fTop->draw(dev);
        emitUses(dev, uses);
    }
    gStepFiles.clear();
}

//------------------------- the player ------------------------------------

// Each SVG carries its data in <script type="application/json" class="faust-svg-step-data">,
// which no browser runs, and the player in <script class="faust-svg-step">. The player defines
// window.FaustSvgStep(svg, options) and starts it on the document when the SVG is opened
// alone. A page that inserts the SVG in its own document (innerHTML runs no script) evaluates
// the player once, then calls, on the inserted <svg> element :
//
//     FaustSvgStep(svg, { use, n, onNavigate({ file, use, n }), onState({ use, n }) })
//
// use and n (absolute sample number) are where to start, from the link that led to this file
// (file.svg#c=use) ; onNavigate is called on a click on a link to another diagram, with the
// file name without its hash, for the page to load it ; onState is called on each change. In a
// page, the player only acts on its <svg> : keys when it has the focus (a click gives it),
// never the page address. FaustSvgStep returns { go(n), use(u), state() }.

// Kept in pieces under 16 KB each (MSVC limit on string literals).

const char* gStepPlayerCSS = R"CSS(
.fsh line { stroke: transparent; stroke-width: 3; cursor: pointer; }
.fsw line.hl { stroke: #e0007a !important; stroke-width: 0.8 !important; }
.fsv .v { cursor: pointer; }
.fsv .v rect { fill: #ffffff; stroke: #9aa5a8; stroke-width: 0.3; }
.fsv .v text { font: 600 4.8px ui-monospace, Menlo, Consolas, "DejaVu Sans Mono", monospace; fill: #16323d; text-anchor: middle; }
.fsv .v.d rect { stroke: #6c4fb3; stroke-width: 0.45; fill: #f3eefc; }
.fsv .v.d text { fill: #4a2f8f; }
.fsv .v.io rect { stroke: #268bd2; stroke-width: 0.45; fill: #eaf4fb; }
.fsv .v.na text { fill: #8a8a8a; }
.fsv .v.hl rect { stroke: #e0007a; stroke-width: 0.7; }
.fsv .v.chg rect { animation: fsflash 0.7s ease-out; }
@keyframes fsflash { from { fill: #ffe066; } }
@media (prefers-reduced-motion: reduce) { .fsv .v.chg rect { animation: none; } }
.fst text { font: 7px Arial, sans-serif; fill: #222222; }
.fst .fsn { font: 700 7.5px ui-monospace, Menlo, Consolas, monospace; }
.fst .fsk { fill: #666666; font-size: 5.5px; }
.fsb { cursor: pointer; }
.fsb rect { fill: #f4f4f4; stroke: #9a9a9a; stroke-width: 0.4; }
.fsb:hover rect { stroke: #268bd2; stroke-width: 0.7; }
.fsb.on rect { fill: #268bd2; stroke: #268bd2; }
.fsb.on text { fill: #ffffff; }
.fsb text { text-anchor: middle; font-size: 6.5px; }
.fstip { pointer-events: none; }
.fstip rect { fill: #1f2b30; opacity: 0.94; }
.fstip text { fill: #f4f1e8; font: 4.6px Arial, sans-serif; }
.fstip .b { font: 700 4.6px ui-monospace, Menlo, Consolas, monospace; }
.fstab text { font: 4.6px ui-monospace, Menlo, Consolas, "DejaVu Sans Mono", monospace; fill: #16323d; }
.fstab .fsth { font: 5px Arial, sans-serif; fill: #666666; }
.fstab .frame { fill: #ffffff; stroke: #cfd6d8; stroke-width: 0.3; }
.fstab .sep { stroke: #cfd6d8; stroke-width: 0.4; }
.fstab .hd { cursor: pointer; }
.fstab .hd text { font-weight: 700; font-family: Arial, sans-serif; }
.fstab .hbg { fill: #ffffff; }
.fstab .hd:hover .hbg { fill: #f2f6f8; }
.fstab .row { cursor: pointer; }
.fstab .row rect { fill: transparent; }
.fstab .row:hover rect { fill: #f2f6f8; }
.fstab .row.cur rect { fill: #fff1c2; }
.fstab .row.cur text { font-weight: 700; }
.fstab .nc, .fstab .na { fill: #8a8a8a; }
.fstab .qm { fill: #b58900; font-weight: 700; cursor: pointer; }
.fstab .track { fill: #eef1f2; }
.fstab .thumb { fill: #b9c3c7; cursor: grab; }
.fstab .thumb:hover { fill: #268bd2; }
.fstab .grip { fill: transparent; cursor: ns-resize; }
.fstab .grip:hover { fill: #268bd2; opacity: 0.35; }
.fsv .v.guess rect { fill: #fff7d6; stroke: #b58900; stroke-dasharray: 1 0.6; }
.fsv .v.guess text { fill: #8a6600; }
)CSS";

const char* gStepPlayerJS1 = R"JS(
(function () {
'use strict';
var NS = 'http://www.w3.org/2000/svg', XL = 'http://www.w3.org/1999/xlink';
// FaustSvgStep(svg, options) starts the player of a steppable diagram (faust -sst) on its <svg>
// element. A standalone SVG document starts itself ; a page that inserts the SVG calls it.
function FaustSvgStep(svg, opts) {
opts = opts || {};
if (svg.__faustSvgStep) return svg.__faustSvgStep;
var dataEl = svg.querySelector('script.faust-svg-step-data');
if (!dataEl) return null;
var standalone = !!opts.standalone;
// the values JSON cannot write (NaN, Infinity) come as strings
var D = JSON.parse(dataEl.textContent, function (k, v) {
  return (Array.isArray(this) && (v === 'NaN' || v === 'Infinity' || v === '-Infinity')) ? Number(v) : v;
});
// the uses of this diagram (one per place it is drawn from) and the one shown
var CTX = D.ctx, U = 0;
function setUse(u) {
  U = u;
  D.s = CTX[u].s; D['in'] = CTX[u]['in']; D.out = CTX[u].out; D.z = CTX[u].z; D.c = CTX[u].c;
}
var mu = standalone ? /c=(\d+)/.exec(location.hash) : null;
setUse(Math.max(0, Math.min(CTX.length - 1, mu ? parseInt(mu[1], 10) : (opts.use | 0))));
var N = D.n, n = 0, timer = null, prevN = -1;
var O = D.o || 0, guess = false, revealed = {};  // offset of sample 0, guess mode
var FONT = 4.8, CHAR_W = FONT * 0.6, PILL_H = 6;

function el(name, attrs, parent) {
  var e = document.createElementNS(NS, name);
  for (var k in attrs) e.setAttribute(k, attrs[k]);
  if (parent) parent.appendChild(e);
  return e;
}
function fmt(k, i, full) {
  var s = D.s[k];
  if (!s || !s.v) return '\u2014';
  var v = s.v[i];
  if (v === undefined) return '';
  if (v !== v) return 'nan';
  if (v === Infinity) return 'inf';
  if (v === -Infinity) return '-inf';
  if (s.i) return String(v);
  var t = String(parseFloat(v.toPrecision(full ? 9 : 6)));
  return /[.e]/.test(t) ? t : t + '.0';
}
function same(k, i, j) {
  var s = D.s[k];
  if (!s || !s.v) return true;
  var a = s.v[i], b = s.v[j];
  return a === b || (a !== a && b !== b);
}

// guess mode : the values of the current sample are hidden, except the given ones
// (inputs, controls, numbers), until revealed
function given(k) {
  var s = D.s[k];
  return !s || !s.v || !!s.k || D['in'].indexOf(k) >= 0 || (D.c || []).indexOf(k) >= 0;
}
function guessing(k) { return guess && !given(k) && !revealed[k]; }
function shown(k, i, full) { return (i === n && guessing(k)) ? '?' : fmt(k, i, full); }

// value labels
var pills = Array.prototype.slice.call(svg.querySelectorAll('.fsv .v'));
function layout(g, text) {
  var t = g.lastChild, r = g.firstChild;
  t.textContent = text;
  var w = text.length * CHAR_W + 2.6, a = g.getAttribute('data-a'), x, y;
  if (a === 'a') { x = 0; y = -PILL_H; }
  else if (a === 'b') { x = -w; y = 0; }
  else if (a === 'r') { x = 0; y = -PILL_H / 2; }
  else { x = -w; y = -PILL_H / 2; }
  r.setAttribute('x', x.toFixed(2)); r.setAttribute('y', y.toFixed(2));
  r.setAttribute('width', w.toFixed(2)); r.setAttribute('height', PILL_H); r.setAttribute('rx', 1.4);
  t.setAttribute('x', (x + w / 2).toFixed(2)); t.setAttribute('y', (y + PILL_H / 2 + FONT * 0.36).toFixed(2));
}

// controls, in the band above the diagram
var vb = svg.viewBox.baseVal;
var bar = el('g', { 'class': 'fst', transform: 'translate(' + (vb.x + 4) + ',' + (vb.y + 4) + ')' }, svg);
var bx = 0;
function button(label, title, fn) {
  var g = el('g', { 'class': 'fsb', transform: 'translate(' + bx + ',0)' }, bar);
  el('title', {}, g).textContent = title;
  el('rect', { width: 13, height: 11, rx: 2 }, g);
  var t = el('text', { x: 6.5, y: 8 }, g);
  t.textContent = label;
  g.addEventListener('click', function (e) { e.stopPropagation(); fn(); });
  bx += 15;
  return g;
}
button('\u23EE', 'First sample (Home)', function () { go(0); });
button('\u25C0', 'Previous sample (\u2190)', function () { go(n - 1); });
button('\u25B6', 'Next sample (\u2192)', function () { go(n + 1); });
button('\u23ED', 'Last sample (End)', function () { go(N - 1); });
var playB = button('\u23EF', 'Play / pause (Space)', togglePlay);
var tableB = button('\u25A4', 'Show / hide the values table (T)', function () { toggleTable(); });
var guessB = button('?', 'Guess mode (G): hide the values of the current sample, click a ? to reveal it',
                    function () { toggleGuess(); });
var nText = el('text', { 'class': 'fsn', x: bx + 3, y: 8 }, bar);
var hint = el('text', { 'class': 'fsk', x: bx + 3, y: 16.5 }, bar);
hint.textContent = '\u2190 \u2192 Home End \u00B7 Space play \u00B7 T table \u00B7 G guess \u00B7 input: ' + D.input +
  (D.ctl ? ' \u00B7 controls: ' + D.ctl : '') + ' \u00B7 ma.SR = ' + D.sr;
)JS";

const char* gStepPlayerJS2 = R"JS(
// tooltip
var tip = el('g', { 'class': 'fstip', visibility: 'hidden' }, svg);
var tipR = el('rect', { rx: 1.5 }, tip);
var tipT = el('text', {}, tip);
var tipK = -1, tipEvt = null;
function line(text, x, y, bold) {
  var t = el('tspan', { x: x, y: y }, tipT);
  if (bold) t.setAttribute('class', 'b');
  t.textContent = text;
  return text.length;
}
function showTip(k, e) {
  tipK = k; tipEvt = e;
  while (tipT.firstChild) tipT.removeChild(tipT.firstChild);
  var s = D.s[k], w = 0, y = 5.5;
  var d = (s && s.d) ? s.d : 'wire';
  w = Math.max(w, line(d + (s && s.v ? (s.i ? ' (int)' : ' (float)') : ''), 2, y)); y += 5.5;
  if (!s || !s.v) { w = Math.max(w, line('value not computable here', 2, y)); y += 5.5; }
  else {
    w = Math.max(w, line('n = ' + (O + n) + ': ' + shown(k, n, true), 2, y, true)); y += 5.5;
    if (n > 0) { w = Math.max(w, line('n = ' + (O + n - 1) + ': ' + fmt(k, n - 1, true), 2, y)); y += 5.5; }
  }
  if (typeof showTable !== 'undefined' && showTable) {
    var on = cols.some(function (c) { return c.k === k; });
    w = Math.max(w, line(guessing(k) ? 'click the ? label to reveal it' :
                         on ? 'click: remove from the table' : 'click: add to the table', 2, y)); y += 5.5;
  }
  var W = w * 4.6 * 0.55 + 4, H = y - 3;
  tipR.setAttribute('width', W.toFixed(2)); tipR.setAttribute('height', H.toFixed(2));
  var pt = svg.createSVGPoint(); pt.x = e.clientX; pt.y = e.clientY;
  var m = svg.getScreenCTM();
  if (m) pt = pt.matrixTransform(m.inverse());
  var x = pt.x + 4, yy = pt.y + 4;
  if (x + W > vb.x + vb.width) x = Math.max(vb.x, pt.x - W - 4);
  if (yy + H > vb.y + vb.height) yy = Math.max(vb.y, pt.y - H - 4);
  tip.setAttribute('transform', 'translate(' + x.toFixed(2) + ',' + yy.toFixed(2) + ')');
  tip.setAttribute('visibility', 'visible');
}
function hideTip() { tipK = -1; tip.setAttribute('visibility', 'hidden'); }
function highlight(k, on) {
  var l = svg.querySelectorAll('.fsw line[data-s="' + k + '"], .fsv .v[data-s="' + k + '"]');
  for (var i = 0; i < l.length; i++) l[i].classList.toggle('hl', on);
}
var hl = -1;
svg.addEventListener('mousemove', function (e) {
  var t = e.target.closest ? e.target.closest('[data-s]') : null;
  if (t && (t.closest('.fsh') || t.closest('.fsv') || t.closest('.fstab'))) {
    var k = +t.getAttribute('data-s');
    if (hl !== k) { if (hl >= 0) highlight(hl, false); highlight(k, true); hl = k; }
    showTip(k, e);
  } else {
    if (hl >= 0) { highlight(hl, false); hl = -1; }
    hideTip();
  }
});
svg.addEventListener('mouseleave', function () { if (hl >= 0) { highlight(hl, false); hl = -1; } hideTip(); });

// stepping
function update() {
  nText.textContent = 'n = ' + (O + n) + '   (' + O + ' \u2026 ' + (O + N - 1) + ')';
  for (var i = 0; i < pills.length; i++) {
    var g = pills[i], k = +g.getAttribute('data-s'), p = g.getAttribute('data-p') || '';
    layout(g, p + shown(k, n, false));
    var s = D.s[k], q = guessing(k);
    g.classList.toggle('na', !s || !s.v);
    g.classList.toggle('guess', q);
    g.classList.remove('chg');
    if (!q && n > 0 && prevN !== n && !same(k, n, n - 1)) { void g.getBBox(); g.classList.add('chg'); }
  }
  prevN = n;
  playB.classList.toggle('on', !!timer);
  guessB.classList.toggle('on', guess);
  renderTable();
  if (tipK >= 0 && tipEvt) showTip(tipK, tipEvt);
  if (standalone) {
    try { history.replaceState(null, '', '#' + (CTX.length > 1 ? 'c=' + U + '&' : '') + 'n=' + (O + n)); }
    catch (e) { /* ignore */ }
  } else if (opts.onState) {
    opts.onState({ use: U, n: O + n });
  }
}
function go(k) {
  k = Math.max(0, Math.min(N - 1, Math.floor(k) || 0));
  if (k === n && prevN >= 0) return;
  if (k !== n) { revealed = {}; topRow = null; }
  n = k;
  update();
}
function togglePlay() {
  if (timer) { clearInterval(timer); timer = null; update(); return; }
  if (n >= N - 1) n = 0;
  timer = setInterval(function () {
    if (n >= N - 1) { clearInterval(timer); timer = null; update(); return; }
    go(n + 1);
  }, 400);
  update();
}
// keys : on the page for a standalone diagram, on the diagram (focused by a click) in a page
if (!standalone) {
  svg.setAttribute('tabindex', '0');
  svg.style.outline = 'none';
  svg.addEventListener('mousedown', function () {
    try { svg.focus({ preventScroll: true }); } catch (e) { svg.focus(); }
  });
}
(standalone ? document : svg).addEventListener('keydown', function (e) {
  if (e.ctrlKey || e.metaKey || e.altKey) return;
  if (e.key === 'ArrowRight') { e.preventDefault(); go(n + 1); }
  else if (e.key === 'ArrowLeft') { e.preventDefault(); go(n - 1); }
  else if (e.key === 'Home') { e.preventDefault(); go(0); }
  else if (e.key === 'End') { e.preventDefault(); go(N - 1); }
  else if (e.key === ' ') { e.preventDefault(); togglePlay(); }
  else if (e.key === 't' || e.key === 'T') { e.preventDefault(); toggleTable(); }
  else if (e.key === 'g' || e.key === 'G') { e.preventDefault(); toggleGuess(); }
  else if (e.key === '[') { e.preventDefault(); switchUse(U - 1); }
  else if (e.key === ']') { e.preventDefault(); switchUse(U + 1); }
});

// links to the other diagrams keep the current sample ; the link names the use of the target
// diagram (#c=). In a page, the page loads the target : options.onNavigate({ file, use, n })
var links = svg.querySelectorAll('a');
for (var i = 0; i < links.length; i++) {
  links[i].addEventListener('click', function (e) {
    var h = this.getAttributeNS(XL, 'href') || this.getAttribute('href');
    if (!h) return;
    var parts = h.split('#'), cm = /c=(\d+)/.exec(parts[1] || ''), use = cm ? parseInt(cm[1], 10) : 0;
    if (standalone) {
      e.preventDefault();
      location.href = parts[0] + '#' + (cm ? 'c=' + use + '&' : '') + 'n=' + (O + n);
    } else if (opts.onNavigate) {
      e.preventDefault();
      e.stopPropagation();
      opts.onNavigate({ file: parts[0], use: use, n: O + n });
    }
  });
}

)JS";

const char* gStepPlayerJS3 = R"JS(
// values table, as in faust-stepper : one row per sample up to n, one column per watched wire
var PAL = ['#d33682', '#2aa198', '#b58900', '#6c71c4', '#cb4b16', '#859900', '#268bd2', '#dc322f'];
var RH = 6, TCW = 4.6 * 0.6;
// rows shown (the bottom edge drags), and the first one (null : follow the current sample)
var rowsShown = Math.min(N, 10), topRow = null;
var base = { x: vb.x, y: vb.y, w: vb.width, h: vb.height };
var wAttr = svg.getAttribute('width') || '', hAttr = svg.getAttribute('height') || '';
var inMM = /mm$/.test(wAttr) && /mm$/.test(hAttr);
var mmPerUnit = inMM ? parseFloat(wAttr) / base.w : 0;
var tab = el('g', { 'class': 'fstab' }, svg);
svg.appendChild(tip);  // the tooltip stays on top
var cols = [], showTable = true, names = {}, usedNames = {};
var Z = D.z || [], C = D.c || [];

function colName(k) {
  if (names[k]) return names[k];
  var b, io = D.out.indexOf(k), ii = D['in'].indexOf(k), zi = Z.indexOf(k);
  if (io >= 0) b = 'out' + io;
  else if (ii >= 0) b = 'in' + ii;
  else if (zi >= 0) b = Z.length > 1 ? 'z\u207B\u00B9 #' + (zi + 1) : 'z\u207B\u00B9';
  else {
    var d = (D.s[k] && D.s[k].d) || 'wire', m = /^\w+\(([^,)]*)/.exec(d);
    b = (C.indexOf(k) >= 0 && m) ? m[1] : d.replace(/ \(output (\d+)\)$/, ':$1');
    if (b.length > 14) b = b.slice(0, 13) + '\u2026';
  }
  var b0 = b, c = 2;
  while (usedNames[b]) b = b0 + ' (' + (c++) + ')';
  usedNames[b] = true;
  names[k] = b;
  return b;
}
function colWidth(k) {
  var w = colName(k).length + 3, s = D.s[k];
  if (s && s.v) for (var i = 0; i < N; i++) w = Math.max(w, fmt(k, i, false).length + 1);
  return w * TCW + 3;
}
function addCol(k) {
  var used = {}, color = PAL[cols.length % PAL.length];
  cols.forEach(function (c) { used[c.color] = 1; });
  for (var j = 0; j < PAL.length; j++) if (!used[PAL[j]]) { color = PAL[j]; break; }
  cols.push({ k: k, color: color, w: colWidth(k) });
}
function toggleCol(k) {
  var i = cols.findIndex(function (c) { return c.k === k; });
  if (i >= 0) cols.splice(i, 1); else addCol(k);
  paint();
  renderTable();
}
function paint() {
  var map = {};
  if (showTable) cols.forEach(function (c) { map[c.k] = c.color; });
  var ls = svg.querySelectorAll('.fsw line[data-s]');
  for (var i = 0; i < ls.length; i++) {
    var c = map[ls[i].getAttribute('data-s')];
    ls[i].style.stroke = c || 'black';
    ls[i].style.strokeWidth = c ? '0.6' : '0.25';
  }
  for (i = 0; i < pills.length; i++) {
    var c2 = map[pills[i].getAttribute('data-s')], r = pills[i].firstChild;
    r.style.stroke = c2 || '';
    r.style.strokeWidth = c2 ? '0.6' : '';
  }
}
function resizeTo(tw, th) {
  vb.width = Math.max(base.w, tw + 8);
  vb.height = base.h + th;
  if (inMM) {
    svg.setAttribute('width', (vb.width * mmPerUnit).toFixed(3) + 'mm');
    svg.setAttribute('height', (vb.height * mmPerUnit).toFixed(3) + 'mm');
  }
}
function text(parent, x, y, str, attrs) {
  var t = el('text', attrs || {}, parent);
  t.setAttribute('x', x.toFixed(2)); t.setAttribute('y', y.toFixed(2));
  t.textContent = str;
  return t;
}
function firstRow() {
  var last = Math.max(0, n - rowsShown + 1);
  return (topRow === null) ? last : Math.max(0, Math.min(last, topRow));
}
function renderTable() {
  while (tab.firstChild) tab.removeChild(tab.firstChild);
  tableB.classList.toggle('on', showTable);
  if (!showTable) { resizeTo(0, 0); return; }
  var x0 = base.x + 4, y0 = base.y + base.h + 3, i, x;
  var nw = (String(O + N - 1).length + 2) * TCW + 2, tw = nw;
  for (i = 0; i < cols.length; i++) tw += cols[i].w;
  text(tab, x0, y0 + 4, cols.length
    ? 'Values over time \u00B7 click a wire to add a column, a header to remove it, a row to go to its sample' +
      ' \u00B7 wheel to scroll, drag the bottom edge to resize'
    : 'Values over time \u00B7 click a wire to add a column', { 'class': 'fsth' });
  var y = y0 + 7, bodyH = rowsShown * RH;
  el('rect', { 'class': 'frame', x: x0, y: y, width: tw, height: RH + 1 + bodyH + 1 }, tab);
  var hd = el('g', { 'class': 'hd' }, tab);
  text(hd, x0 + nw - 2, y + RH - 1.2, 'n', { 'text-anchor': 'end' });
  for (i = 0, x = x0 + nw; i < cols.length; x += cols[i].w, i++) {
    var c = cols[i], g = el('g', { 'class': 'hd', 'data-col': c.k, 'data-s': c.k }, tab);
    el('rect', { 'class': 'hbg', x: x, y: y, width: c.w, height: RH + 1 }, g);
    var ht = text(g, x + c.w - 2, y + RH - 1.2, colName(c.k), { 'text-anchor': 'end' }), tl;
    try { tl = ht.getComputedTextLength(); } catch (err) { tl = 0; }
    if (!tl) tl = colName(c.k).length * TCW;
    el('rect', { x: x + c.w - 2 - tl - 3.6, y: y + 2, width: 2.6, height: 2.6, rx: 0.5, fill: c.color }, g);
  }
  y += RH + 1;
  el('line', { 'class': 'sep', x1: x0, y1: y, x2: x0 + tw, y2: y }, tab);
  var bodyY = y, r0 = firstRow();
  for (var r = r0; r <= n && r < r0 + rowsShown; r++, y += RH) {
    var row = el('g', { 'class': 'row' + (r === n ? ' cur' : ''), 'data-row': r }, tab);
    el('rect', { x: x0, y: y, width: tw, height: RH }, row);
    text(row, x0 + nw - 2, y + RH - 1.5, String(O + r), { 'text-anchor': 'end', 'class': 'nc' });
    for (i = 0, x = x0 + nw; i < cols.length; x += cols[i].w, i++) {
      var k = cols[i].k, s = D.s[k], q = (r === n && guessing(k));
      var cell = text(row, x + cols[i].w - 2, y + RH - 1.5, shown(k, r, false),
                      { 'text-anchor': 'end', 'class': q ? 'qm' : (s && s.v) ? '' : 'na' });
      if (q) cell.setAttribute('data-reveal', k);
    }
  }
  // scroll bar, when the rows up to n do not all fit
  if (n + 1 > rowsShown) {
    el('rect', { 'class': 'track', x: x0 + tw + 1, y: bodyY, width: 2.4, height: bodyH, rx: 1.2 }, tab);
    var th = Math.max(3, bodyH * rowsShown / (n + 1)), ty = bodyY + (bodyH - th) * r0 / (n + 1 - rowsShown);
    var thumb = el('rect', { 'class': 'thumb', x: x0 + tw + 1, y: ty, width: 2.4, height: th, rx: 1.2 }, tab);
    thumb.addEventListener('mousedown', function (e) {
      drag(e, r0, function (start, dy) {
        topRow = Math.round(start + dy * (n + 1 - rowsShown) / Math.max(1, bodyH - th));
        if (topRow >= n + 1 - rowsShown) topRow = null;
      });
    });
  }
  // bottom edge : drag to show more or fewer rows
  var grip = el('rect', { 'class': 'grip', x: x0, y: bodyY + bodyH - 0.5, width: tw, height: 2.5 }, tab);
  el('title', {}, grip).textContent = 'Drag to show more or fewer rows';
  grip.addEventListener('mousedown', function (e) {
    drag(e, rowsShown, function (start, dy) { rowsShown = Math.max(3, Math.min(Math.max(3, N), Math.round(start + dy / RH))); });
  });
  resizeTo(tw + 4, 7 + RH + 1 + bodyH + 1 + 4);
}
// drags with the mouse : f(start, dy) with dy in diagram units
function drag(e, start, f) {
  e.preventDefault(); e.stopPropagation();
  var m = svg.getScreenCTM(), scale = m ? m.d : 1, y0 = e.clientY;
  function move(ev) { f(start, (ev.clientY - y0) / scale); renderTable(); }
  function up() { document.removeEventListener('mousemove', move); document.removeEventListener('mouseup', up); }
  document.addEventListener('mousemove', move);
  document.addEventListener('mouseup', up);
}
tab.addEventListener('wheel', function (e) {
  if (n + 1 <= rowsShown) return;
  e.preventDefault();
  var step = (e.deltaY > 0 ? 1 : -1) * (Math.abs(e.deltaY) > 40 ? 3 : 1), last = n + 1 - rowsShown;
  topRow = Math.max(0, Math.min(last, firstRow() + step));
  if (topRow >= last) topRow = null;
  renderTable();
}, { passive: false });
function toggleGuess() {
  guess = !guess;
  revealed = {};
  update();
}
function toggleTable() {
  showTable = !showTable;
  paint();
  renderTable();
}
svg.addEventListener('click', function (e) {
  var t = e.target.closest ? e.target.closest('[data-reveal],[data-row],[data-col],[data-s]') : null;
  if (!t) return;
  var ks = t.getAttribute('data-s');
  if (t.hasAttribute('data-reveal')) { revealed[t.getAttribute('data-reveal')] = true; update(); }
  else if (ks !== null && t.closest('.fsv') && guessing(+ks)) { revealed[ks] = true; update(); }
  else if (t.hasAttribute('data-row')) go(+t.getAttribute('data-row'));
  else if (t.hasAttribute('data-col')) toggleCol(+t.getAttribute('data-col'));
  else if (showTable && (t.closest('.fsh') || t.closest('.fsv'))) toggleCol(+t.getAttribute('data-s'));
});

// default columns : inputs, controls, recursion delays, outputs (at most 10)
// switching between the uses of this diagram
var backLinks = [], useText = null;
(function () {
  var as = svg.querySelectorAll('a');
  for (var i = 0; i < as.length; i++) {
    if (CTX[0].back && as[i].getAttributeNS(XL, 'href') === CTX[0].back) backLinks.push(as[i]);
  }
})();
if (CTX.length > 1) {
  var uy = 19.5, ux = 0;
  [['\u2039', 'Previous use of this diagram ([)', -1], ['\u203A', 'Next use of this diagram (])', 1]]
    .forEach(function (b) {
      var g = el('g', { 'class': 'fsb', transform: 'translate(' + ux + ',' + uy + ')' }, bar);
      el('title', {}, g).textContent = b[1];
      el('rect', { width: 9, height: 7, rx: 1.5 }, g);
      text(g, 4.5, 5.6, b[0]);
      g.addEventListener('click', function (e) { e.stopPropagation(); switchUse(U + b[2]); });
      ux += 11;
    });
  useText = text(bar, ux + 2, uy + 5.4, '', { 'class': 'fsk' });
}
function showUse() {
  if (!useText) return;
  useText.textContent = 'use ' + (U + 1) + ' of ' + CTX.length +
    (CTX[U].from ? ' \u00B7 from ' + CTX[U].from : '') + ' \u00B7 [ ] switch';
  for (var i = 0; i < backLinks.length; i++) backLinks[i].setAttributeNS(XL, 'xlink:href', CTX[U].back);
}
// the links to sub-diagrams (numbered by &b=) go to the uses the shown use leads to
function pointLinks() {
  var as = svg.querySelectorAll('a'), L = CTX[U].links || [];
  for (var i = 0; i < as.length; i++) {
    var mb = /[#&]b=(\d+)/.exec(as[i].getAttributeNS(XL, 'href') || '');
    if (mb && L[+mb[1]]) as[i].setAttributeNS(XL, 'xlink:href', L[+mb[1]] + '&b=' + mb[1]);
  }
}
function switchUse(u) {
  if (CTX.length < 2) return;
  setUse((u + CTX.length) % CTX.length);
  pointLinks();
  Z = D.z || []; C = D.c || [];
  names = {}; usedNames = {};
  cols.forEach(function (c) { c.w = colWidth(c.k); });
  revealed = {};
  showUse();
  paint();
  prevN = n;  // no change flash
  update();
}

var seen = {};
[D['in'], C, Z, D.out].forEach(function (l) {
  (l || []).forEach(function (k) {
    if (!seen[k] && cols.length < 10) { seen[k] = 1; addCol(k); }
  });
});

var m = standalone ? /n=(\d+)/.exec(location.hash) : null;
n = Math.max(0, Math.min(N - 1, (m ? parseInt(m[1], 10) : (opts.n != null ? +opts.n : O)) - O));
showUse();
pointLinks();
paint();
update();
// to drive the player from the page : go to a sample, switch use, read the state
var api = {
  go: function (k) { go(k - O); },
  use: function (u) { switchUse(u); },
  state: function () { return { use: U, n: O + n }; }
};
svg.__faustSvgStep = api;
return api;
}
FaustSvgStep.version = 1;
if (!(window.FaustSvgStep && window.FaustSvgStep.version >= FaustSvgStep.version)) window.FaustSvgStep = FaustSvgStep;
var root = document.documentElement;
if (root && root.namespaceURI === NS && root.querySelector('script.faust-svg-step-data')) {
  window.FaustSvgStep(root, { standalone: true });
}
})();
)JS";
