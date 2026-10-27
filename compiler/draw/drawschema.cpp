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

/**
 * @file drawschema.cpp
 * Implement block-diagram schema generation in svg or postscript format.
 * The result is a folder containing one or more schema files in svg or
 * ps format. Complex block-diagrams are automatically splitted.
 */

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <map>
#include <ostream>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "blockSchema.h"
#include "boxcomplexity.hh"
#include "boxes.hh"
#include "compatibility.hh"
#include "description.hh"
#include "devLib.h"
#include "drawschema.hh"
#include "drawstep.hh"
#include "exception.hh"
#include "files.hh"
#include "global.hh"
#include "names.hh"
#include "occur.hh"
#include "occurrences.hh"
#include "ppbox.hh"
#include "prim2.hh"
#include "propagate.hh"
#include "property.hh"
#include "routeSchema.h"
#include "schema.h"
#include "Text.hh"
#include "xtended.hh"

#if 0
#define linkcolor "#b3d1dc"
#define normalcolor "#ffeaa2"
#define uicolor "#F1CFA1"
#define slotcolor "#ffffd7"
#define numcolor "#ffffff"
#endif

#if 0
#define linkcolor "#F57900"
#define normalcolor "#4B71A1"
#define uicolor "#47945E"
#define slotcolor "#EDD400"
#define numcolor "#4B71A1"
#endif

#if 0
#define linkcolor "#47945E"
#define normalcolor "#4B71A1"
#define uicolor "#f44800"
#define slotcolor "#EDD400"
#define numcolor "#f44800"
#endif

#if 0
#define linkcolor "#47945E"
#define normalcolor "#4B71A1"
#define uicolor "#816647"
#define slotcolor "#EDD400"
#define numcolor "#f44800"
#endif

#if 0
#define linkcolor "#003366"
#define normalcolor "#4B71A1"
#define uicolor "#816647"
#define slotcolor "#EDD400"
#define numcolor "#f44800"
#endif

#if 0
#define linkcolor "#003366"
#define normalcolor "#4B71A1"
#define uicolor "#477881"
#define slotcolor "#816647"
#define numcolor "#f44800"
#endif

#if 1
#define linkcolor "#003366"
#define normalcolor "#4B71A1"
#define uicolor "#477881"
#define slotcolor "#47945E"
#define numcolor "#f44800"
#define invcolor "#ffffff"
#endif

using namespace std;

// prototypes of internal functions
static void    writeSchemaFile(Tree bd, bool root);
static schema* generateDiagramSchema(Tree bd, const StepContext* ctx = nullptr);
static schema* generateInsideSchema(Tree t, const StepContext* ctx = nullptr);
static void    scheduleDrawing(Tree t);
static bool    pendingDrawing(Tree& t);
static schema* generateAbstractionSchema(Tree slot, Tree t, const StepContext* ctx);
static schema* generateOutputSlotSchema(Tree a);
static schema* generateInputSlotSchema(Tree a);
static schema* generateBargraphSchema(Tree t);
static schema* generateUserInterfaceSchema(Tree t);
static string  userInterfaceDescription(Tree box);
static string  slotName(Tree a);
static schema* generateSoundfileSchema(Tree t);
static char*   legalFileName(Tree t, int n, char* dst);

static schema* addSchemaInputs(int ins, schema* x);
static schema* addSchemaOutputs(int outs, schema* x);

// Sets gGlobal->gOccurrences for the duration of a scope and restores the
// previous value on exit, including when drawing throws (writeSchemaFile can
// throw faustexception). The Occur itself is owned by the caller.
struct ScopedOccurrences {
    Occur* fSaved;
    explicit ScopedOccurrences(Occur* occur) : fSaved(gGlobal->gOccurrences)
    {
        gGlobal->gOccurrences = occur;
    }
    ~ScopedOccurrences() { gGlobal->gOccurrences = fSaved; }
};

//------------------- -sst : steppable diagrams ------------------
//
// In step mode, each box is drawn with the signals on its inputs (a StepContext,
// see drawstep.hh), and a folded diagram is drawn once per context : what is
// scheduled is a key made of the box and its context, not the box alone.

static bool gStepDrawing = false;  // true while drawSchema draws in step mode

struct ScopedStepDrawing {
    explicit ScopedStepDrawing(bool on) { gStepDrawing = on; }
    ~ScopedStepDrawing() { gStepDrawing = false; }
};

static Tree stepKey(Tree t, const StepContext& ctx)
{
    return cons(t, cons(ctx.fSlotEnv, cons(ctx.fPath, cons(ctx.fRecs, listConvert(ctx.fIns)))));
}

static Tree stepKeyBox(Tree key)
{
    return hd(key);
}

static StepContext stepKeyContext(Tree key)
{
    StepContext ctx;
    Tree        l = tl(key);
    ctx.fSlotEnv  = hd(l);
    l             = tl(l);
    ctx.fPath     = hd(l);
    l             = tl(l);
    ctx.fRecs     = hd(l);
    ctx.fIns      = treeConvert(tl(l));
    return ctx;
}

// Records schema s of box t with its signals (in step mode), returns s
static schema* stepped(schema* s, Tree t, const StepContext* ctx, StepKind kind,
                       const string& name = "")
{
    if (ctx) {
        stepRecord(s, *ctx, stepOutputs(t, *ctx), kind, name);
    }
    return s;
}

/**
 *The entry point to generate from a block diagram as a set of
 *svg files stored in the directory "<projname>-svg/" or
 *"<projname>-ps/" depending of <dev>.
 */
void drawSchema(Tree bd, const char* projname, const char* dev, Tree stepInput)
{
    gGlobal->gDevSuffix   = dev;  // .svg or .ps used to choose output device
    gGlobal->gFoldingFlag = boxComplexity(bd) > gGlobal->gFoldThreshold;

    // Each call draws a complete set of files in its own directory: forget what
    // a previous call drew (-ps then -svg, the documentator diagrams, or a
    // previous compilation in the same libfaust context), otherwise its nodes
    // are seen as already drawn and are not written again, and the back links
    // point to its files.
    gGlobal->gDrawnExp.clear();
    gGlobal->gBackLink.clear();
    gGlobal->gPendingExp = std::stack<Tree>();
    gGlobal->gSchemaFileName.clear();

    // Count how many parents each node has in the hash-consed DAG (linear in
    // the number of distinct nodes), so shared nodes can be folded instead of
    // expanded (see generateDiagramSchema). The counts are only needed by this
    // drawing pass, so the Occur is scoped here instead of being left to
    // tlib::cleanup() (one would be orphaned per -svg/-ps compilation with a
    // long-lived createLibContext context, where global::reset() only clears
    // the pointer).
    Occur             occur(bd);
    ScopedOccurrences scoped(&occur);

    // -sst : the root is drawn with the test signal on its inputs
    ScopedStepDrawing step(stepInput != nullptr && strcmp(dev, "svg") == 0);
    Tree              root = bd;
    if (gStepDrawing) {
        int ins, outs;
        getBoxType(bd, &ins, &outs);
        stepCheckControls(bd);
        StepContext ctx{gGlobal->nil, gGlobal->nil, gGlobal->nil, stepInputSignals(stepInput, ins)};
        root = stepKey(bd, ctx);
    }

    mkchDir(projname);  // create a directory to store files

    scheduleDrawing(root);  // schedule the initial drawing

    Tree t;
    while (pendingDrawing(t)) {
        writeSchemaFile(t, t == root);  // generate all the pending drawing
    }
    if (gStepDrawing) {
        stepWriteFiles();  // -sst : the values of all the files in one batch, then the files
    }

    choldDir();  // return to current directory
}

/************************************************************************
 ************************************************************************
                            IMPLEMENTATION
 ************************************************************************
 ************************************************************************/

// Collect the leaf numbers of tree l into vector v.
// return true if l a number or a parallel tree of numbers.
static bool isIntTree(Tree l, vector<int>& v)
{
    int    n;
    double r;
    Tree   x, y;

    if (isBoxInt(l, &n)) {
        v.push_back(n);
        return true;

    } else if (isBoxReal(l, &r)) {
        v.push_back(int(r));
        return true;

    } else if (isBoxPar(l, x, y)) {
        return isIntTree(x, v) && isIntTree(y, v);

    } else {
        stringstream error;
        error << "ERROR : file " << __FILE__ << ':' << __LINE__
              << ", not a valid list of numbers : " << boxpp(l) << endl;
        throw faustexception(error.str());
    }
}

//------------------- to schedule and retreive drawing ------------------

/**
 * Schedule a makeBlockSchema diagram to be drawn.
 */
static void scheduleDrawing(Tree t)
{
    if (gGlobal->gDrawnExp.find(t) == gGlobal->gDrawnExp.end()) {
        gGlobal->gDrawnExp.insert(t);
        gGlobal->gBackLink.insert(
            make_pair(t, gGlobal->gSchemaFileName));  // remember the enclosing filename
        gGlobal->gPendingExp.push(t);
    }
}

/**
 * Retrieve next block diagram that must be drawn.
 */
static bool pendingDrawing(Tree& t)
{
    if (gGlobal->gPendingExp.empty()) {
        return false;
    }
    t = gGlobal->gPendingExp.top();
    gGlobal->gPendingExp.pop();
    return true;
}

//------------------------ dealing with files -------------------------

/**
 * Write a top level diagram. A top level diagram
 * is decorated with its definition name property
 * and is drawn in an individual file. The <root> diagram
 * of the drawing is written to kSchemaRootName.
 */
static void writeSchemaFile(Tree bd, bool root)
{
    Tree    id;
    schema* ts;
    int     ins, outs;

    char temp[1024];

    // in step mode, what was scheduled is a key : the box and its context
    Tree        key = bd;
    StepContext ctx;
    if (gStepDrawing) {
        ctx = stepKeyContext(key);
        bd  = stepKeyBox(key);
        stepBeginFile();
    }

    getBoxType(bd, &ins, &outs);

    bool hasname = getDefNameProperty(bd, id);

    // faustassert(hasname);
    if (!hasname) {
        // create an arbitrary name
        id = tree(Node(unique("diagram_")));
    }

    // generate legal file name for the schema : the root is not named after
    // its definition, which is not process with -pn. No link names the
    // root's file : a node is not one of its own descendants.
    stringstream s1;
    s1 << (root ? kSchemaRootName : legalFileName(bd, 1024, temp)) << "." << gGlobal->gDevSuffix;
    string res1              = s1.str();
    gGlobal->gSchemaFileName = res1;

    // generate the label of the schema
    string link = gGlobal->gBackLink[key];
    if (gStepDrawing) {
        // the back links of the diagrams drawn from this one name this use
        int use                  = stepContextIndex(bd, key);
        gGlobal->gSchemaFileName = res1 + "#c=" + std::to_string(use);
        schema* io = addSchemaOutputs(outs, addSchemaInputs(ins, generateInsideSchema(bd, &ctx)));
        stepRecord(io, ctx, stepOutputs(bd, ctx), kStepIO, "");
        ts = makeTopSchema(io, kStepMargin, tree2str(id), link);
        ts->place(0, 0, kLeftRight);
        collector* c = new collector();
        ts->collectTraits(*c);
        stepDeferFile(res1, use, link, ts, c);  // written by stepWriteFiles
        return;
    }
    ts = makeTopSchema(addSchemaOutputs(outs, addSchemaInputs(ins, generateInsideSchema(bd))), 20,
                       tree2str(id), link);
    // draw to the device defined by gDevSuffix
    if (strcmp(gGlobal->gDevSuffix, "svg") == 0) {
        SVGDev dev(res1.c_str(), ts->width(), ts->height());
        ts->place(0, 0, kLeftRight);
        ts->draw(dev);
        {
            collector c;
            ts->collectTraits(c);
            c.draw(dev);
        }
    } else {
        PSDev dev(res1.c_str(), ts->width(), ts->height());
        ts->place(0, 0, kLeftRight);
        ts->draw(dev);
        {
            collector c;
            ts->collectTraits(c);
            c.draw(dev);
        }
    }
}

/**
 * Transform the definition name property of tree <t> into a
 * legal file name.  The resulting file name is stored in
 * <dst> a table of at least <n> chars. Returns the <dst> pointer
 * for convenience.
 */
static char* legalFileName(Tree t, int n, char* dst)
{
    Tree id;
    int  i = 0;
    if (getDefNameProperty(t, id)) {
        const char* src = tree2str(id);
        for (i = 0; isalnum(src[i]) && i < 16; i++) {
            dst[i] = src[i];
        }
    }
    if (i == 0 || !isalpha(dst[0])) {
        // a name that does not start with a letter (`_tanhalf(...)`, or no
        // name at all) would give `-111553.svg`, which reads as an option,
        // or `0-23908.svg`
        snprintf(dst, n, "diagram");
        i = int(strlen(dst));
    }
    dst[i] = 0;
    // add the node's serial number to make the name unique -- and the same
    // from one run to the next, which an address is not (the whole set of
    // files, and the links between them, are then reproducible). A node
    // named process gets one too : it is not the root here (the entry point
    // of -pn can use process, a component can redefine it), and would
    // otherwise overwrite the root's file.
    snprintf(&dst[i], n - i, "-%zu", (size_t)t->serial());
    return dst;
}

//------------------------ generating the schema -------------------------

/**
 * isInverter(t) returns true if t == '*(-1)'. This test is used
 * to simplify diagram by using a special symbol for inverters.
 */
static bool isInverter(Tree t)
{
    // cerr << "isInverter " << t << '$' << boxpp(t) << endl;
    for (int i = 0; i < 6; i++) {
        if (t == gGlobal->gInverter[i]) {
            return true;
        }
    }
    return false;
}

/**
 * Compute the Pure Routing property, that is expressions
 * only made of cut, wires and slots. No labels will be
 * dispayed for pure routing expressions.
 */

static bool isPureRouting(Tree t)
{
    bool r;
    int  ID;
    Tree x, y;

    if (gGlobal->gPureRoutingProperty->get(t, r)) {
        return r;
    } else if (isBoxCut(t) || isBoxWire(t) || isInverter(t) || isBoxSlot(t, &ID) ||
               (isBoxPar(t, x, y) && isPureRouting(x) && isPureRouting(y)) ||
               (isBoxSeq(t, x, y) && isPureRouting(x) && isPureRouting(y)) ||
               (isBoxSplit(t, x, y) && isPureRouting(x) && isPureRouting(y)) ||
               (isBoxMerge(t, x, y) && isPureRouting(x) && isPureRouting(y))) {
        gGlobal->gPureRoutingProperty->set(t, true);
        return true;
    } else {
        gGlobal->gPureRoutingProperty->set(t, false);
        return false;
    }
}

/**
 * Generate an appropriate schema according to
 * the type of block diagram. When folding is required,
 * instead of going down block-diagrams with a name,
 * schedule them for an individual file.
 */
static schema* generateDiagramSchema(Tree t, const StepContext* ctx)
{
    Tree id;
    int  ins, outs;

    // cerr << t << " generateDiagramSchema " << boxpp(t)<< endl;

    if (getDefNameProperty(t, id)) {
        stringstream s;
        s << tree2str(id);
        // cerr << t << "\tNAMED : " << s.str() << endl;
    }

    bool named = getDefNameProperty(t, id);
    // A shared node (more than one parent in the hash-consed DAG) must be
    // folded even when it has no definition name, otherwise the drawing
    // expands the shared graph as a tree and grows exponentially
    // (observed: 6 GB of SVG for ma.chebychev(30)).
    bool shared = (gGlobal->gOccurrences != nullptr) && (gGlobal->gOccurrences->getCount(t) > 1);

    if (gGlobal->gFoldingFlag && (boxComplexity(t) >= gGlobal->gFoldComplexity) &&
        (named || shared)) {
        if (!named) {
            // Synthesize a name for the reference label and the scheduled file.
            id = tree(Node(unique("diagram_")));
            setDefNameProperty(t, id);
        }
        char temp[1024];
        getBoxType(t, &ins, &outs);
        stringstream l;
        if (ctx) {
            // step mode : the folded diagram is computed once per context (its use) and the
            // uses of a box share its file ; the link names the use
            // the link names the use ; &b= numbers the folded blocks of the file, so that
            // the player can point them at the targets of the use it shows
            Tree         key = stepKey(t, *ctx);
            stringstream target;
            target << legalFileName(t, 1024, temp) << "." << gGlobal->gDevSuffix
                   << "#c=" << stepContextIndex(t, key);
            l << target.str() << "&b=" << stepAddLink(target.str());
            scheduleDrawing(key);
            return stepped(makeBlockSchema(ins, outs, tree2str(id), linkcolor, l.str()), t, ctx,
                           kStepBlock, tree2str(id));
        }
        l << legalFileName(t, 1024, temp) << "." << gGlobal->gDevSuffix;
        scheduleDrawing(t);
        return makeBlockSchema(ins, outs, tree2str(id), linkcolor, l.str());

    } else if (named && !isPureRouting(t)) {
        // named case : not a slot, with a name
        // draw a line around the object with its name
        return stepped(makeDecorateSchema(generateInsideSchema(t, ctx), 10, tree2str(id)), t, ctx,
                       kStepWiring);

    } else {
        // normal case
        return generateInsideSchema(t, ctx);
    }
}

/**
 * Generate the inside schema of a block diagram
 * according to its type.
 */
static schema* generateInsideSchema(Tree t, const StepContext* ctx)
{
    Tree   a, b, c, ff, l, type, name, file;
    int    i;
    double r;
    prim0  p0;
    prim1  p1;
    prim2  p2;
    prim3  p3;
    prim4  p4;
    prim5  p5;

    xtended* xt = (xtended*)getUserData(t);

    // ctx (step mode only) : the signals on the inputs of t ; each schema is then
    // recorded with them (stepped), and the context of each child is computed as
    // propagate() does

    if (xt) {
        return stepped(makeBlockSchema(xt->arity(), 1, xt->name(), normalcolor, ""), t, ctx,
                       kStepBlock, xt->name());
    }

    else if (isInverter(t)) {
        return stepped(makeInverterSchema(invcolor), t, ctx, kStepBlock, "*(-1)");
    }

    else if (isBoxInt(t, &i)) {
        stringstream s;
        s << i;
        return stepped(makeBlockSchema(0, 1, s.str(), numcolor, ""), t, ctx, kStepLiteral, s.str());
    } else if (isBoxReal(t, &r)) {
        stringstream s;
        s << boxpp(t);
        return stepped(makeBlockSchema(0, 1, s.str(), numcolor, ""), t, ctx, kStepLiteral, s.str());
    } else if (isBoxWaveform(t)) {
        return stepped(makeBlockSchema(0, 2, "waveform{...}", normalcolor, ""), t, ctx, kStepBlock,
                       "waveform{...}");
    } else if (isBoxWire(t)) {
        return stepped(makeCableSchema(), t, ctx, kStepWiring);
    } else if (isBoxCut(t)) {
        return stepped(makeCutSchema(), t, ctx, kStepWiring);
    }

    else if (isBoxPrim0(t, &p0)) {
        return stepped(makeBlockSchema(0, 1, prim0name(p0), normalcolor, ""), t, ctx, kStepBlock,
                       prim0name(p0));
    } else if (isBoxPrim1(t, &p1)) {
        return stepped(makeBlockSchema(1, 1, prim1name(p1), normalcolor, ""), t, ctx, kStepBlock,
                       prim1name(p1));
    } else if (isBoxPrim2(t, &p2)) {
        return stepped(makeBlockSchema(2, 1, prim2name(p2), normalcolor, ""), t, ctx, kStepBlock,
                       prim2name(p2));
    } else if (isBoxPrim3(t, &p3)) {
        return stepped(makeBlockSchema(3, 1, prim3name(p3), normalcolor, ""), t, ctx, kStepBlock,
                       prim3name(p3));
    } else if (isBoxPrim4(t, &p4)) {
        return stepped(makeBlockSchema(4, 1, prim4name(p4), normalcolor, ""), t, ctx, kStepBlock,
                       prim4name(p4));
    } else if (isBoxPrim5(t, &p5)) {
        return stepped(makeBlockSchema(5, 1, prim5name(p5), normalcolor, ""), t, ctx, kStepBlock,
                       prim5name(p5));
    }

    else if (isBoxFFun(t, ff)) {
        int         arity = ffarity(ff);
        std::string fname = ffname(ff);
        return stepped(makeBlockSchema(arity, 1, fname, normalcolor, ""), t, ctx, kStepBlock,
                       fname);
    } else if (isBoxFConst(t, type, name, file)) {
        return stepped(makeBlockSchema(0, 1, tree2str(name), normalcolor, ""), t, ctx, kStepBlock,
                       tree2str(name));
    } else if (isBoxFVar(t, type, name, file)) {
        return stepped(makeBlockSchema(0, 1, tree2str(name), normalcolor, ""), t, ctx, kStepBlock,
                       tree2str(name));
    }

    else if (isBoxButton(t) || isBoxCheckbox(t) || isBoxVSlider(t) || isBoxHSlider(t) ||
             isBoxNumEntry(t)) {
        return stepped(generateUserInterfaceSchema(t), t, ctx, kStepControl,
                       userInterfaceDescription(t));
    } else if (isBoxVBargraph(t) || isBoxHBargraph(t)) {
        return stepped(generateBargraphSchema(t), t, ctx, kStepControl,
                       userInterfaceDescription(t));
    } else if (isBoxSoundfile(t)) {
        return stepped(generateSoundfileSchema(t), t, ctx, kStepBlock, userInterfaceDescription(t));
    }

    else if (isBoxMetadata(t, a, b)) {
        return generateDiagramSchema(a, ctx);
    }

    // don't draw group rectangle when labels are empty (ie "")
    else if (isBoxVGroup(t, l, a) || isBoxHGroup(t, l, a) || isBoxTGroup(t, l, a)) {
        int          kind = isBoxVGroup(t, l, a) ? 0 : (isBoxHGroup(t, l, a) ? 1 : 2);
        stringstream s;
        s << ((kind == 0)   ? "vgroup("
              : (kind == 1) ? "hgroup("
                            : "tgroup(")
          << extractName(l) << ")";
        StepContext ca;
        if (ctx) {
            // as in propagate : the group is added to the path of the widgets
            ca       = *ctx;
            ca.fPath = cons(cons(tree(kind), l), ctx->fPath);
        }
        schema* s1 = generateDiagramSchema(a, ctx ? &ca : nullptr);
        return stepped(makeDecorateSchema(s1, 10, s.str()), t, ctx, kStepWiring);
    }

    else if (isBoxSeq(t, a, b) || isBoxPar(t, a, b) || isBoxSplit(t, a, b) || isBoxMerge(t, a, b)) {
        StepContext ca, cb;
        if (ctx) {
            ca = cb = *ctx;
            int in1, out1, in2, out2;
            getBoxType(a, &in1, &out1);
            getBoxType(b, &in2, &out2);
            if (isBoxPar(t, a, b)) {
                ca.fIns = siglist(ctx->fIns.begin(), ctx->fIns.begin() + in1);
                cb.fIns = siglist(ctx->fIns.begin() + in1, ctx->fIns.begin() + in1 + in2);
            } else {
                siglist l1 = stepOutputs(a, ca);
                int     n1 = int(l1.size());
                if (isBoxSeq(t, a, b)) {
                    cb.fIns = l1;
                } else if (isBoxSplit(t, a, b)) {
                    // as split() in propagate.cpp
                    cb.fIns = siglist(in2);
                    for (int k = 0; k < in2; k++) {
                        cb.fIns[k] = l1[k % n1];
                    }
                } else {
                    // as mix() in propagate.cpp
                    cb.fIns = siglist(in2);
                    for (int k = 0; k < in2; k++) {
                        Tree x = (k < n1) ? l1[k] : sigInt(0);
                        for (int j = k + in2; j < n1; j += in2) {
                            x = sigAdd(x, l1[j]);
                        }
                        cb.fIns[k] = x;
                    }
                }
            }
        }
        schema* sa = generateDiagramSchema(a, ctx ? &ca : nullptr);
        schema* sb = generateDiagramSchema(b, ctx ? &cb : nullptr);
        schema* s  = isBoxSeq(t, a, b)     ? makeSeqSchema(sa, sb)
                     : isBoxPar(t, a, b)   ? makeParSchema(sa, sb)
                     : isBoxSplit(t, a, b) ? makeSplitSchema(sa, sb)
                                           : makeMergeSchema(sa, sb);
        return stepped(s, t, ctx, kStepWiring);
    } else if (isBoxRec(t, a, b)) {
        StepContext ca, cb;
        if (ctx) {
            // as in propagate : B receives the delayed outputs of A, and A receives the
            // outputs of B then the inputs ; both inside the recursive group g
            int in1, out1, in2, out2;
            getBoxType(a, &in1, &out1);
            getBoxType(b, &in2, &out2);
            Tree    slotenv2 = lift(ctx->fSlotEnv);
            siglist l0(in2);
            for (int k = 0; k < in2; k++) {
                l0[k] = sigDelay1(sigProj(k, ref(1)));
            }
            siglist l1 = propagate(slotenv2, ctx->fPath, b, l0);
            siglist la = l1;
            for (Tree x : ctx->fIns) {
                la.push_back(lift(x));
            }
            siglist l2   = propagate(slotenv2, ctx->fPath, a, la);
            Tree    g    = rec(listConvert(l2));
            Tree    recs = cons(g, ctx->fRecs);
            ca           = StepContext{slotenv2, ctx->fPath, recs, la};
            cb           = StepContext{slotenv2, ctx->fPath, recs, l0};
        }
        schema* sa = generateDiagramSchema(a, ctx ? &ca : nullptr);
        schema* sb = generateDiagramSchema(b, ctx ? &cb : nullptr);
        schema* s  = makeRecSchema(sa, sb);
        if (ctx) {
            stepRecordDelays(s, cb.fIns, cb.fRecs);
        }
        return stepped(s, t, ctx, kStepWiring);
    }

    else if (isBoxSlot(t, &i)) {
        return stepped(generateOutputSlotSchema(t), t, ctx, kStepBlock, slotName(t));
    } else if (isBoxSymbolic(t, a, b)) {
        Tree id;
        if (getDefNameProperty(t, id)) {
            return stepped(generateAbstractionSchema(a, b, ctx), t, ctx, kStepWiring);
        } else {
            return stepped(
                makeDecorateSchema(generateAbstractionSchema(a, b, ctx), 10, "Abstraction"), t, ctx,
                kStepWiring);
        }

    } else if (isBoxEnvironment(t)) {
        return stepped(makeBlockSchema(0, 0, "environment{...}", normalcolor, ""), t, ctx,
                       kStepBlock, "environment{...}");

    } else if (isBoxRoute(t, a, b, c)) {
        int         ins, outs;
        vector<int> route;
        // cerr << "TRACE: drawing a box route " << boxpp(t) << endl;
        if (isBoxInt(a, &ins) && isBoxInt(b, &outs) && isIntTree(c, route)) {
            return stepped(makeRouteSchema(ins, outs, route), t, ctx, kStepWiring);
        } else {
            stringstream error;
            error << "ERROR : file " << __FILE__ << ':' << __LINE__
                  << ", invalid route expression : " << boxpp(t) << endl;
            throw faustexception(error.str());
        }
    } else {
        stringstream error;
        error << "ERROR in generateInsideSchema, box expression not recognized : ";
        t->print(error);
        error << endl;
        throw faustexception(error.str());
    }
}

/**
 * Convert User interface element into a textual representation
 */
static string userInterfaceDescription(Tree box)
{
    Tree         t1, label, cur, min, max, step, chan;
    stringstream fout;
    // user interface
    if (isBoxButton(box, label)) {
        fout << "button(" << extractName(label) << ')';
    } else if (isBoxCheckbox(box, label)) {
        fout << "checkbox(" << extractName(label) << ')';
    } else if (isBoxVSlider(box, label, cur, min, max, step)) {
        fout << "vslider(" << extractName(label) << ", " << boxpp(cur) << ", " << boxpp(min) << ", "
             << boxpp(max) << ", " << boxpp(step) << ')';
    } else if (isBoxHSlider(box, label, cur, min, max, step)) {
        fout << "hslider(" << extractName(label) << ", " << boxpp(cur) << ", " << boxpp(min) << ", "
             << boxpp(max) << ", " << boxpp(step) << ')';
    } else if (isBoxVGroup(box, label, t1)) {
        fout << "vgroup(" << extractName(label) << ", " << boxpp(t1, 0) << ')';
    } else if (isBoxHGroup(box, label, t1)) {
        fout << "hgroup(" << extractName(label) << ", " << boxpp(t1, 0) << ')';
    } else if (isBoxTGroup(box, label, t1)) {
        fout << "tgroup(" << extractName(label) << ", " << boxpp(t1, 0) << ')';
    } else if (isBoxHBargraph(box, label, min, max)) {
        fout << "hbargraph(" << extractName(label) << ", " << boxpp(min) << ", " << boxpp(max)
             << ')';
    } else if (isBoxVBargraph(box, label, min, max)) {
        fout << "vbargraph(" << extractName(label) << ", " << boxpp(min) << ", " << boxpp(max)
             << ')';
    } else if (isBoxNumEntry(box, label, cur, min, max, step)) {
        fout << "nentry(" << extractName(label) << ", " << boxpp(cur) << ", " << boxpp(min) << ", "
             << boxpp(max) << ", " << boxpp(step) << ')';
    } else if (isBoxSoundfile(box, label, chan)) {
        fout << "soundfile(" << extractName(label) << ", " << boxpp(chan) << ')';
    } else {
        throw faustexception("ERROR : unknown user interface element\n");
    }
    return fout.str();
}

/**
 * Generate a 0->1 block schema for a user interface element.
 */
static schema* generateUserInterfaceSchema(Tree t)
{
    return makeBlockSchema(0, 1, userInterfaceDescription(t), uicolor, "");
}

/**
 * Generate a 1->1 block schema for a user interface bargraph.
 */
static schema* generateBargraphSchema(Tree t)
{
    return makeBlockSchema(1, 1, userInterfaceDescription(t), uicolor, "");
}

/**
 * Generate a 2->3+c block schema for soundfile("toto",c).
 */
static schema* generateSoundfileSchema(Tree t)
{
    Tree label, chan;
    if (isBoxSoundfile(t, label, chan)) {
        int n = tree2int(chan);
        return makeBlockSchema(2, 2 + n, userInterfaceDescription(t), uicolor, "");
    } else {
        throw faustexception("ERROR : soundfile\n");
    }
}

/**
 * Generate a 1->0 block schema for an input slot.
 */
static string slotName(Tree a)
{
    int i;
    faustassert(isBoxSlot(a, &i));
    Tree id;
    faustassert(getDefNameProperty(a, id));
    return subst("[$0] $1", T(i), tree2str(id));
}

static schema* generateInputSlotSchema(Tree a)
{
    int i;
    faustassert(isBoxSlot(a, &i));
    Tree id;
    faustassert(getDefNameProperty(a, id));
    string name = subst("[$0] $1", T(i), tree2str(id));
    return makeBlockSchema(1, 0, name, slotcolor, "");
}

/**
 * Generate a 0->1 block schema for an output slot.
 */
static schema* generateOutputSlotSchema(Tree a)
{
    int i;
    faustassert(isBoxSlot(a, &i));
    Tree id;
    faustassert(getDefNameProperty(a, id));
    string name = subst("[$0] $1", T(i), tree2str(id));
    return makeBlockSchema(0, 1, name, slotcolor, "");
}

/**
 * Generate an abstraction schema by placing in sequence
 * the input slots and the body.
 */
static schema* generateAbstractionSchema(Tree slot, Tree t, const StepContext* ctx)
{
    Tree a, b;

    // step mode : as in propagate, each slot is bound to the next input signal, and the
    // body receives the remaining ones
    StepContext body;
    size_t      k        = 0;
    auto        bindSlot = [&](schema* s, Tree sl) {
        if (ctx) {
            faustassert(k < ctx->fIns.size());
            StepContext cs = body;
            cs.fIns        = siglist(1, ctx->fIns[k]);
            stepRecord(s, cs, siglist(), kStepWiring, "");
            body.fSlotEnv = pushEnv(sl, ctx->fIns[k], body.fSlotEnv);
            k++;
        }
        return s;
    };
    if (ctx) {
        body = *ctx;
    }

    schema* x = bindSlot(generateInputSlotSchema(slot), slot);
    while (isBoxSymbolic(t, a, b)) {
        x = makeParSchema(x, bindSlot(generateInputSlotSchema(a), a));
        t = b;
    }
    if (ctx) {
        body.fIns = siglist(ctx->fIns.begin() + k, ctx->fIns.end());
    }
    return makeSeqSchema(x, generateDiagramSchema(t, ctx ? &body : nullptr));
}

static schema* addSchemaInputs(int ins, schema* x)
{
    if (ins == 0) {
        return x;
    } else {
        schema* y = 0;
        do {
            schema* z = makeConnectorSchema();
            if (y != 0) {
                y = makeParSchema(y, z);
            } else {
                y = z;
            }
        } while (--ins);
        return makeSeqSchema(y, x);
    }
}

static schema* addSchemaOutputs(int outs, schema* x)
{
    if (outs == 0) {
        return x;
    } else {
        schema* y = 0;
        do {
            schema* z = makeConnectorSchema();
            if (y != 0) {
                y = makeParSchema(y, z);
            } else {
                y = z;
            }
        } while (--outs);
        return makeSeqSchema(x, y);
    }
}
