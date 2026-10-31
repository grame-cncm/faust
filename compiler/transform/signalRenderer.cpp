/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2024 GRAME, Centre National de Creation Musicale
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

#include "signalRenderer.hh"
#include "lowerNormalForm.hh"
#include "compatibility.hh"  // For basename, pathToContent
#include "xtended.hh"

#include <cmath>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "global.hh"

using namespace std;

//-------------------------SignalRenderer-------------------------------
//
// SignalRenderer is designed to directly render signals, bypassing the traditional
// compilation phase.
//
// Execution Flow. The interpretation process is divided into two main stages:
//
// 1) Preparation Stage (SignalBuilder). The SignalBuilder class traverses all output signal trees
// to:
//      - Allocate delay lines (both integer and REAL types) for sample-accurate delays and
//      recursive constructs.
//      - Allocate tables (both integer and real types) required for table-based signal generation.
//      - Collect and configure input and output control signals (e.g., sliders, buttons,
//      bargraphs).
//
// 2) Rendering Stage (SignalRenderer). The SignalRenderer class:
//      - Traverses all output signal trees.
//      - Computes the value of each output signal sample by recursively interpreting the expression
//      tree.
//      - Uses a value stack to manage intermediate results.
//
// Table Initialization:
//
// After SignalBuilder has prepared the signal trees, the tables are precomputed once during
// the initialization phase via the `initTables` method. This ensures efficient table lookup during
// rendering.
//
// Sample Computation. For each audio sample:
//      - The interpreter starts from the output signal tree and recursively traverses the
//        graph back to its inputs (audio inputs and control signals).
//      - Recursion is handled once per sample using the fVisited variable to prevent cycles.
//
// Integration with DSP Factory:
//
// The SignalRenderer class is wrapped by `signal_dsp_factory` and `signal_dsp` classes,
// enabling integration with the existing DSP backends used in Faust (e.g., LLVM or Interp).
// This allows seamless reuse of user interfaces and other DSP features.
//----------------------------------------------------------------------

template <class REAL>
int signal_dsp_aux<REAL>::getNumInputs()
{
    return fRenderer.fNumInputs;
}

template <class REAL>
int signal_dsp_aux<REAL>::getNumOutputs()
{
    return fRenderer.fNumOutputs;
}

template <class REAL>
void signal_dsp_aux<REAL>::compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
{
    fRenderer.compute(count, inputs, outputs);
}

/**
 * @brief Computes and renders audio samples for a block of output signals.
 *
 * This method performs the rendering loop of the signal interpreter.
 * It processes a block of audio samples by traversing the output signal tree,
 * computing each sample value recursively, and writing the result to the
 * appropriate output channel.
 *
 * Core steps:
 * 1. Sets the input pointer (`fInputs`) for use during recursive evaluation.
 * 2. Iterates over each sample in the block (sample index `fSample`).
 * 3. For each output signal, recursively evaluates the expression tree
 *    using `self()`, retrieving the computed value from the stack.
 * 4. Determines whether the result is an integer or a real value
 *    and writes it to the correct output channel.
 * 5. Increments the shared index counter (`fIOTA`) used for delay lines
 *    and waveforms.
 *
 * Implementation details:
 * - Clears the `fVisited` map at the start of each sample to ensure correct
 *   handling of recursive signals and avoid cyclic evaluations.
 * - Supports both integer and REAL output signals, allowing mixed-type
 *   outputs depending on the signal graph.
 *
 * @param count The number of samples to process in the current block.
 * @param inputs The input signal buffers (audio and control signals).
 * @param outputs The output signal buffers.
 */
template <class REAL>
void SignalRenderer<REAL>::compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
{
    fInputs = inputs;

    for (fSample = 0; fSample < count; fSample++) {
        int  chan        = 0;
        Tree output_list = fOutputSig;

        startSample();  // Clear visited and memoized values for each sample

        while (!isNil(output_list)) {
            // Render each output in 'chan'
            Tree out_sig = hd(output_list);
            self(out_sig);
            // Get the result which can contain an integer or REAL value
            Node res = popRes();
            int  int_val;
            if (isInt(res, &int_val)) {
                outputs[chan++][fSample] = static_cast<FAUSTFLOAT>(res.getInt());
            } else {
                outputs[chan++][fSample] = static_cast<FAUSTFLOAT>(res.getDouble());
            }
            // Render next output
            output_list = tl(output_list);
        }

        // Increment the delay lines and waveforms shared index
        fIOTA++;
    }
}

/**
 * @brief Visits a signal tree node and recursively evaluates its value.
 *
 * This method implements the core interpreter logic for rendering the
 * signal graph. It uses a recursive traversal to process each node type,
 * evaluates its sub-expressions, and computes the resulting value. The
 * intermediate results are stored on a value stack (`fValueStack`).
 *
 * The method supports a wide variety of Faust signal constructs, including:
 * - Constants (integer, real)
 * - Inputs and outputs
 * - Delay lines and feedback structures
 * - Control structures (sliders, buttons, bargraphs)
 * - Mathematical operations (binary operators, conditional expressions)
 * - Table-based operations (read/write table)
 * - Recursive signals and projections
 *
 * Key implementation notes:
 * - For each recognized node type, it performs the appropriate evaluation logic
 *   and pushes the result onto the value stack.
 * - For recursive signals (e.g., projections), it uses the `fVisited` map to
 *   detect cycles and avoid infinite recursion.
 * - It handles the evaluation of user interface controls by reading values
 *   from `fInputControls` and updating `fOutputControls`.
 * - For unimplemented or unrecognized nodes, it triggers an assertion failure
 *   to ensure correctness.
 *
 * @param sig The signal tree node to evaluate.
 */
template <class REAL>
void SignalRenderer<REAL>::visit(Tree sig)
{
    // Per-sample memoization (see fSampleCache)
    auto it = fSampleCache.find(sig);
    if (it != fSampleCache.end()) {
        pushRes(it->second);
        return;
    }
    size_t depth = fValueStack.size();
    int    stale = fStaleReads;
    visitNode(sig);
    if (fStaleReads == stale && fValueStack.size() == depth + 1) {
        fSampleCache.emplace(sig, fValueStack.top());
    }
}

// The foreign functions of the C math library declared by the Faust libraries, by C name. Each
// precision has its name (ffunction(float tanhf|tanh|tanhl (float), ...)), and each name is
// computed with that C function, in its precision, as the compiled code computes it.
namespace {

using FFunArgs = std::vector<double>;
using FFunImpl = double (*)(const FFunArgs&);

// clang-format off
// float F(float), in the three precisions (also int F(float) : the result is converted to the
// declared type by the caller)
#define FFUN_REAL1(F)                                                                   \
    {#F "f", [](const FFunArgs& a) { return double(F##f(float(a[0]))); }},              \
    {#F,     [](const FFunArgs& a) { return double(F(a[0])); }},                        \
    {#F "l", [](const FFunArgs& a) { return double(F##l((long double)(a[0]))); }}

// float F(float, float)
#define FFUN_REAL2(F)                                                                   \
    {#F "f", [](const FFunArgs& a) { return double(F##f(float(a[0]), float(a[1]))); }}, \
    {#F,     [](const FFunArgs& a) { return double(F(a[0], a[1])); }},                  \
    {#F "l", [](const FFunArgs& a) {                                                    \
        return double(F##l((long double)(a[0]), (long double)(a[1]))); }}

// float F(float, int)
#define FFUN_REAL_INT(F)                                                                \
    {#F "f", [](const FFunArgs& a) { return double(F##f(float(a[0]), int(a[1]))); }},   \
    {#F,     [](const FFunArgs& a) { return double(F(a[0], int(a[1]))); }},             \
    {#F "l", [](const FFunArgs& a) { return double(F##l((long double)(a[0]), int(a[1]))); }}

const std::map<std::string, FFunImpl>& mathFFuns()
{
    static const std::map<std::string, FFunImpl> table = {
        FFUN_REAL1(acosh), FFUN_REAL1(asinh), FFUN_REAL1(atanh), FFUN_REAL1(cbrt),
        FFUN_REAL1(cosh),  FFUN_REAL1(erfc),  FFUN_REAL1(erf),   FFUN_REAL1(lgamma),
        FFUN_REAL1(logb),  FFUN_REAL1(sinh),  FFUN_REAL1(tanh),  FFUN_REAL1(tgamma),
        FFUN_REAL1(ilogb),
        FFUN_REAL2(copysign), FFUN_REAL2(hypot),
        FFUN_REAL_INT(ldexp), FFUN_REAL_INT(scalbn),
        // isnan and isinf are macros in C : the three names test the value in its precision
        {"isnanf", [](const FFunArgs& a) { return double(std::isnan(float(a[0]))); }},
        {"isnan",  [](const FFunArgs& a) { return double(std::isnan(a[0])); }},
        {"isnanl", [](const FFunArgs& a) { return double(std::isnan((long double)(a[0]))); }},
        {"isinff", [](const FFunArgs& a) { return double(std::isinf(float(a[0]))); }},
        {"isinf",  [](const FFunArgs& a) { return double(std::isinf(a[0])); }},
        {"isinfl", [](const FFunArgs& a) { return double(std::isinf((long double)(a[0]))); }},
#ifndef _WIN32
        // the Bessel functions of POSIX, declared with one name, computed in double
        {"j0", [](const FFunArgs& a) { return j0(a[0]); }},
        {"j1", [](const FFunArgs& a) { return j1(a[0]); }},
        {"jn", [](const FFunArgs& a) { return jn(int(a[0]), a[1]); }},
        {"y0", [](const FFunArgs& a) { return y0(a[0]); }},
        {"y1", [](const FFunArgs& a) { return y1(a[0]); }},
        {"yn", [](const FFunArgs& a) { return yn(int(a[0]), a[1]); }},
#endif
    };
    return table;
}

#undef FFUN_REAL1
#undef FFUN_REAL2
#undef FFUN_REAL_INT
// clang-format on

// The value of a Node as a double, whatever its kind
double nodeValue(const Node& n)
{
    switch (n.type()) {
        case kIntNode:
            return double(n.getInt());
        case kInt64Node:
            return double(n.getInt64());
        default:
            return n.getDouble();
    }
}

}  // namespace

bool isRenderedFFun(Tree ff)
{
    return mathFFuns().count(ffname(ff)) > 0;
}

double computeRenderedFFun(Tree ff, const std::vector<double>& args)
{
    auto it = mathFFuns().find(ffname(ff));
    faustassert(it != mathFFuns().end());
    return it->second(args);
}

template <class REAL>
void SignalRenderer<REAL>::visitNode(Tree sig)
{
    int     i_val;
    int64_t i64_val;
    double  r_val;
    Tree    size_tree, gen_tree, wi_tree, ws_tree, tbl_tree, ri_tree;
    Tree    c_tree, x_tree, y_tree, z_tree;
    Tree    label_tree, type_tree, name_tree, file_tree, sf_tree, sel;
    Tree    rec_vars, rec_exprs, ff_tree, ff_args;
    int     opt_op;
    int     proj_idx;  // For isProj

    /*
    if (global::isDebug("SIG_RENDERER")) {
        std::cout << "SignalRenderer : " << ppsig(sig, 64) << std::endl;
        std::cout << "SignalRenderer : fIOTA " << fIOTA << std::endl;
    }
    */

    if (xtended* xt = (xtended*)sigXtendedData(sig)) {
        vector<Node> args;
        // Interpret all arguments then call the function
        for (Tree b : sig->branches()) {
            self(b);
            args.push_back(popRes());
        }
        Node res = xt->compute(args);
        //  HACK: for 'min/max' res may actually be of type kInt
        int ty = getCertifiedSigType(sig)->nature();
        if (ty == kInt) {
            // an int result wraps around to 32 bits, as in the compiled code (pow(int, 2) is
            // computed with int multiplications), instead of saturating
            double d = res.getDouble();
            pushRes((std::fabs(d) < 9.2e18) ? Node(int(int32_t(uint32_t(int64_t(d)))))
                                            : Node(int(d)));
        } else {
            pushRes(realValue(res.getDouble()));
        }
    } else if (isSigInt(sig, &i_val)) {
        pushRes(i_val);
    } else if (isSigInt64(sig, &i64_val)) {
        pushRes(i64_val);
    } else if (isSigReal(sig, &r_val)) {
        pushRes(realValue(r_val));
    } else if (isSigInput(sig, &i_val)) {
        pushRes(realValue(fInputs[i_val][fSample]));
    } else if (isSigOutput(sig, &i_val, x_tree)) {
        self(x_tree);  // Evaluate the expression connected to the output
    } else if (isSigDelay1(sig, x_tree)) {
        self(x_tree);
        Node v1  = popRes();
        Node one = Node(1);
        pushRes(writeReadDelay(x_tree, v1, one));

    } else if (isSigDelay(sig, x_tree, y_tree)) {
        if (isZeroDelay(y_tree)) {
            self(x_tree);
        } else {
            self(x_tree);
            Node v1 = popRes();
            self(y_tree);
            Node v2 = popRes();
            pushRes(writeReadDelay(x_tree, v1, v2));
        }
    } else if (isSigSelect2(sig, sel, x_tree, y_tree)) {
        // Interpret the condition and both branches
        self(sel);
        Node sel_val = popRes();
        self(x_tree);
        Node x_val = popRes();
        self(y_tree);
        Node y_val = popRes();
        // Inverted
        if (sel_val.getInt()) {
            pushRes(y_val);
        } else {
            pushRes(x_val);
        }
    } else if (isSigPrefix(sig, x_tree, y_tree)) {
        self(y_tree);
        if (fIOTA == 0) {
            self(x_tree);
        }
    } else if (isSigBinOp(sig, &opt_op, x_tree, y_tree)) {
        self(x_tree);
        Node v1 = popRes();
        self(y_tree);
        Node v2 = popRes();

        Type x_type = getCertifiedSigType(x_tree);
        Type y_type = getCertifiedSigType(y_tree);

        // Integer binop when both arguments are integer
        if (x_type->nature() == kInt && y_type->nature() == kInt) {
            int a = v1.getInt(), b = v2.getInt();
            if (opt_op == kAdd || opt_op == kSub || opt_op == kMul) {
                // int32 arithmetic wraps around, as in the compiled code (Node arithmetic
                // would turn an overflow into a double)
                uint32_t ua = uint32_t(a), ub = uint32_t(b);
                uint32_t r = (opt_op == kAdd) ? ua + ub : (opt_op == kSub) ? ua - ub : ua * ub;
                pushRes(Node(int(int32_t(r))));
            } else {
                pushRes(gBinOpTable[opt_op]->compute(a, b));
            }
        } else if (opt_op == kDiv) {
            // the division of the run time : x / 0 is an infinity or NaN, not the refusal of
            // the folding of constants
            pushRes(realValue(v1.getDouble() / v2.getDouble()));
        } else if (opt_op == kRem) {
            pushRes(realValue(std::fmod(v1.getDouble(), v2.getDouble())));
        } else {
            // Otherwise REAL binop
            Node res = gBinOpTable[opt_op]->compute(v1.getDouble(), v2.getDouble());
            pushRes(isInt(res) ? res : realValue(res.getDouble()));
        }
    } else if (isSigFFun(sig, ff_tree, ff_args)) {
        // a function of the C math library (isRenderedFFun, checked by the factory) : the
        // arguments are converted to the declared types, as in the compiled call. The signature
        // keeps the argument types in reverse order (see sigPromotion).
        vector<double> args;
        int            last = ffarity(ff_tree) - 1;
        int            i    = 0;
        for (Tree l = ff_args; !isNil(l); l = tl(l), i++) {
            self(hd(l));
            double v    = nodeValue(popRes());
            int    type = ffargtype(ff_tree, last - i);
            args.push_back((type == kInt) ? double(int(v)) : (type == kReal) ? double(REAL(v)) : v);
        }
        double res = computeRenderedFFun(ff_tree, args);
        pushRes((ffrestype(ff_tree) == kInt) ? Node(int(res)) : realValue(res));
    } else if (isSigFConst(sig, type_tree, name_tree, file_tree)) {
        // Special case for SR constant
        if (string(tree2str(name_tree)) == "fSamplingFreq") {
            pushRes(fSampleRate);
        } else {
            // TODO
            faustassert(false);
            pushRes(Node(0));
        }
    } else if (isSigWRTbl(sig, size_tree, gen_tree, wi_tree, ws_tree)) {
        if (isNil(wi_tree)) {
            // Nothing
        } else {
            // Interpret write signal
            self(wi_tree);
            // Then read its content
            Node write_idx = popRes();
            self(ws_tree);
            Node val_node = popRes();
            writeTable(sig, write_idx, val_node);
        }
    } else if (isSigRDTbl(sig, tbl_tree, ri_tree)) {
        // Interpret table
        self(tbl_tree);
        // Then read its content
        self(ri_tree);
        Node read_idx = popRes();
        pushRes(readTable(tbl_tree, read_idx));
    } else if (isSigGen(sig, x_tree)) {
        if (fVisitGen) {
            self(x_tree);
        } else {
            pushRes(Node(0));
        }
    } else if (isSigWaveform(sig)) {
        // Modulo based access in the waveform
        int size  = sig->arity();
        int index = fIOTA % size;
        self(sig->branch(index));
    } else if (isProj(sig, &proj_idx, x_tree) && isRec(x_tree, rec_vars, rec_exprs)) {
        // First visit of the recursive signal
        if (fVisited.find(sig) == fVisited.end()) {
            faustassert(isRec(x_tree, rec_vars, rec_exprs));
            fVisited[sig]++;
            fInProgress.insert(sig);
            int ownStale = fStaleBy[sig];
            // Render the actual projection
            self(nth(rec_exprs, proj_idx));
            fInProgress.erase(sig);
            // its own stale reads are resolved now that it is computed
            fStaleReads -= fStaleBy[sig] - ownStale;
            fStaleBy[sig] = ownStale;
            Node res      = popRes();
            /*
            if (global::isDebug("SIG_RENDERER")) {
                std::cout << "Proj : " << res << "\n";
            }
            */
            Node zero = Node(0);
            pushRes(writeReadDelay(sig, res, zero));
            fSampleCache.emplace(sig, topRes());

        } else {
            if (fInProgress.count(sig)) {
                // read while being computed : the previous content of its delay line
                fStaleBy[sig]++;
                fStaleReads++;
            }
            /*
            if (global::isDebug("SIG_RENDERER")) {
                std::cout << "SignalRenderer : next visit of the recursive signal\n";
            }
            */
            Node zero = Node(0);
            pushRes(readDelay(sig, zero));
        }
    } else if (isSigIntCast(sig, x_tree)) {
        self(x_tree);
        Node cur = popRes();
        pushRes(static_cast<int>(cur.getDouble()));
    } else if (isSigBitCast(sig, x_tree)) {
        // Bitcast is complex. For a simple renderer, it might be an identity if types are
        // "close enough" or a reinterpretation of bits (e.g., float bits as int). This renderer
        // doesn't have type info readily on Node to do a true bitcast. Assuming it's a numeric
        // pass-through for now.
        self(x_tree);
    } else if (isSigFloatCast(sig, x_tree)) {
        self(x_tree);
        Node cur = popRes();
        pushRes(static_cast<REAL>(cur.getInt()));
    } else if (isSigButton(sig, label_tree)) {
        pushRes(realValue(fInputControls[sig].getValue()));
    } else if (isSigCheckbox(sig, label_tree)) {
        pushRes(realValue(fInputControls[sig].getValue()));
    } else if (isSigVSlider(sig, label_tree, c_tree, x_tree, y_tree, z_tree)) {
        pushRes(realValue(fInputControls[sig].getValue()));
    } else if (isSigHSlider(sig, label_tree, c_tree, x_tree, y_tree, z_tree)) {
        pushRes(realValue(fInputControls[sig].getValue()));
    } else if (isSigNumEntry(sig, label_tree, c_tree, x_tree, y_tree, z_tree)) {
        pushRes(realValue(fInputControls[sig].getValue()));
    } else if (isSigVBargraph(sig, label_tree, x_tree, y_tree, z_tree)) {
        self(z_tree);
        Node val = topRes();
        fOutputControls[sig].setValue(val.getDouble());
    } else if (isSigHBargraph(sig, label_tree, x_tree, y_tree, z_tree)) {
        self(z_tree);
        Node val = topRes();
        fOutputControls[sig].setValue(val.getDouble());
    } else if (isSigSoundfile(sig, label_tree)) {
        // TODO: Implement soundfile reading. Requires state management for file handlers,
        // position, etc.
        pushRes(Node(0));
    } else if (isSigSoundfileLength(sig, sf_tree, x_tree)) {
        // TODO
        self(sf_tree);
        popRes();
        self(x_tree);
        popRes();
        pushRes(Node(0));
    } else if (isSigSoundfileRate(sig, sf_tree, x_tree)) {
        // TODO
        self(sf_tree);
        popRes();
        self(x_tree);
        popRes();
        pushRes(Node(0));
    } else if (isSigSoundfileBuffer(sig, sf_tree, x_tree, y_tree, z_tree)) {
        // TODO
        self(sf_tree);
        popRes();
        self(x_tree);
        popRes();
        self(y_tree);
        popRes();
        self(z_tree);
        popRes();
        pushRes(Node(0));
    } else if (isSigAttach(sig, x_tree, y_tree)) {
        // Interpret second arg then drop it
        self(y_tree);
        popRes();
        // And return the first one
        self(x_tree);
    } else if (isSigEnable(sig, x_tree, y_tree)) {  // x_tree is condition, y_tree is signal
        self(x_tree);
        Node enable = popRes();
        if (enable.getInt() != 0) {
            self(y_tree);
        } else {
            pushRes(Node(0));
        }
    } else if (isSigControl(sig, x_tree, y_tree)) {  // x_tree is the signal, y_tree the condition
        // The signal is computed only when the condition is not zero ; otherwise it keeps
        // its previous value, as in the compiled code, which skips its computation
        self(y_tree);
        Node cond = popRes();
        auto it   = fControlHold.find(sig);
        if (cond.getInt() != 0) {
            self(x_tree);
            if (it != fControlHold.end()) {
                it->second = topRes();
            } else {
                fControlHold.emplace(sig, topRes());
            }
        } else {
            pushRes((it != fControlHold.end()) ? it->second : Node(0));
        }
    } else {
        // Default case and recursion
        SignalVisitor::visit(sig);
    }
}

// Needed functions
Tree DSPToBoxes(const string& name_app, const string& dsp_content, int argc, const char* argv[],
                int* inputs, int* outputs, string& error_msg);

tvec boxesToSignals(Tree box, string& error_msg);

extern "C" void createLibContext();
extern "C" void destroyLibContext();

// Explicit template instantiations
template struct SignalRenderer<float>;
template struct SignalRenderer<double>;
template struct signal_dsp_aux<float>;
template struct signal_dsp_aux<double>;

// External API

/*
 Since the compilation/interpretation context is global, a UNIQUE factory can be created.
 The context has to be be kept until the factory destroys it in deleteSignalDSPFactory.
 */
signal_dsp_factory* createSignalDSPFactoryFromString(const string& name_app,
                                                     const string& dsp_content, int argc,
                                                     const char* argv[], string& error_msg)
{
    createLibContext();

    class SignalPrefix : public SignalIdentity {
       public:
        SignalPrefix() : SignalIdentity() {}

       protected:
        virtual Tree transformation(Tree sig)
        {
            Tree x, y;
            if (isSigPrefix(sig, x, y)) {
                return sigPrefix(self(x), sigDelay1(self(y)));
            } else {
                // Other cases => identity transformation
                return SignalIdentity::transformation(sig);
            }
        }
    };

    try {
        // Using the DSP to Box API
        int  inputs = 0, outputs = 0;
        Tree box = DSPToBoxes(name_app, dsp_content, argc, argv, &inputs, &outputs, error_msg);
        if (!box) {
            goto error;
        }
        // Then the Box to Signal API
        tvec signals = boxesToSignals(box, error_msg);
        if (signals.empty()) {
            goto error;
        }

        // The interpreter knows the binary operations : the nodes of the normal form (Sum,
        // Prod, Neg, FIR, IIR, IRM, Mix, Frac, Cfrac, Tpt, Phase, Bpf) lowered to them
        Tree res = lowerNormalForm(listConvert(signals));
        // Rewrite prefix trees
        SignalPrefix SP;
        res = SP.mapself(res);
        typeAnnotation(res, gGlobal->gLocalCausalityCheck);

        // Context has to be kept until destroyed in deleteSignalDSPFactory
        return new signal_dsp_factory(inputs, outputs, res, argc, argv);
    } catch (faustexception& e) {
        error_msg = e.Message();
    }

error:
    destroyLibContext();
    return nullptr;
}

signal_dsp_factory* createSignalDSPFactoryFromFile(const string& filename, int argc,
                                                   const char* argv[], string& error_msg)
{
    string base = basename((char*)filename.c_str());
    size_t pos  = filename.find(".dsp");

    if (pos != string::npos) {
        return createSignalDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), argc,
                                                argv, error_msg);
    } else {
        error_msg = "ERROR : file extension is not the one expected (.dsp expected)\n";
        return nullptr;
    }
}

bool deleteSignalDSPFactory(signal_dsp_factory* factory)
{
    delete factory;
    // Context is destroyed, a new factory can possibly be created...
    destroyLibContext();
    return true;
}
