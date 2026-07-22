/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

#ifndef _NNX_BASE_INSTRUCTIONS_H
#define _NNX_BASE_INSTRUCTIONS_H

#include <cstdio>
#include <initializer_list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "struct_manager.hh"
#include "text_instructions.hh"

// Foreign functions dispatched to the architecture's RNG helpers. An explicit
// set, not a name-prefix match: the architectures implement exactly these.
inline bool isNNXRandomFunction(const std::string& name)
{
    return name == "random_uniform" || name == "random_normal" || name == "random_exponential" ||
           name == "random_bernoulli" || name == "random_beta";
}

/**
 * Analysis pass that finds small struct arrays accessed only through constant
 * indices — Faust's copy-delay pattern (the z^-1/z^-2 states of recursive
 * filters). In the generated Python these arrays live in the scan carry and
 * every per-sample update compiles to a `.at[k].set(...)` dynamic-update-slice;
 * a handful of such arrays in the scan body makes XLA's while-loop fall off its
 * in-place-update path (measured ~1000x slower per step on CPU). Arrays
 * identified here are emitted as individual scalar carry entries
 * ("fRec0_0", "fRec0_1", ...) with plain assignments instead.
 *
 * An array qualifies when it is a struct-level ArrayTyped declaration of size
 * <= kMaxSize with no initializer, and every access anywhere in the emitted
 * code is a single constant index. Any bare (whole-array) reference — e.g. the
 * jnp.roll shift strategy or an IOTA-indexed circular buffer — disqualifies it.
 */
struct NNXScalarizeAnalysis : public DispatchVisitor {
    static const int kMaxSize = 4;

    std::map<std::string, int> fCandidates;  // array name -> size
    std::set<std::string>      fExcluded;

    using DispatchVisitor::visit;

    void visit(DeclareVarInst* inst) override
    {
        ArrayTyped* array_type = dynamic_cast<ArrayTyped*>(inst->fType);
        if (array_type && (inst->fAddress->isStruct() || inst->fAddress->isStaticStruct())) {
            if (!inst->fValue && array_type->fSize > 0 && int(array_type->fSize) <= kMaxSize) {
                fCandidates[inst->fAddress->getName()] = int(array_type->fSize);
            } else {
                fExcluded.insert(inst->fAddress->getName());
            }
            // The declaration itself is not an access: skip the address, but
            // still analyse the initializer value if present.
            if (inst->fValue) {
                inst->fValue->accept(this);
            }
            return;
        }
        DispatchVisitor::visit(inst);
    }

    void visit(IndexedAddress* indexed) override
    {
        NamedAddress* named = dynamic_cast<NamedAddress*>(indexed->fAddress);
        if (named) {
            bool constant_single_index =
                (indexed->fIndices.size() == 1) && dynamic_cast<Int32NumInst*>(indexed->getIndex());
            if (!constant_single_index) {
                fExcluded.insert(named->fName);
            }
        } else {
            // Multi-dimensional or otherwise nested addressing
            indexed->fAddress->accept(this);
        }
        for (const auto& it : indexed->fIndices) {
            it->accept(this);
        }
    }

    // A bare (non-indexed) reference to a name: whole-array access
    void visit(NamedAddress* named) override { fExcluded.insert(named->fName); }

    std::map<std::string, int> scalarized() const
    {
        std::map<std::string, int> result;
        for (const auto& it : fCandidates) {
            if (fExcluded.find(it.first) == fExcluded.end()) {
                result.insert(it);
            }
        }
        return result;
    }
};

/**
 * Run NNXScalarizeAnalysis over every code block that will be emitted.
 */
inline std::map<std::string, int> nnxComputeScalarizedArrays(
    std::initializer_list<BlockInst*> blocks)
{
    NNXScalarizeAnalysis analysis;
    for (BlockInst* block : blocks) {
        if (block) {
            block->accept(&analysis);
        }
    }
    return analysis.scalarized();
}

/**
 * Base visitor for initializing array fields into the DSP structure during _initialize_carry().
 * Subclasses (NNX and Linen) override visit(NamedAddress*) for params/state routing.
 */
struct NNXBaseInitFieldsVisitor : public DispatchVisitor {
    std::ostream* fOut;
    int           fTab;

    // Small copy-delay arrays emitted as scalar carry entries (name -> size)
    std::map<std::string, int> fScalarizedArrays;

    NNXBaseInitFieldsVisitor(std::ostream* out, int tab = 0) : fOut(out), fTab(tab) {}

    void setScalarizedArrays(const std::map<std::string, int>& arrays)
    {
        fScalarizedArrays = arrays;
    }

    virtual void visit(DeclareVarInst* inst)
    {
        ArrayTyped* array_type = dynamic_cast<ArrayTyped*>(inst->fType);
        if (array_type) {
            auto scalarized = fScalarizedArrays.find(inst->fAddress->getName());
            if (scalarized != fScalarizedArrays.end()) {
                // Emitted as one scalar state entry per element (never a UI
                // param, so "state" routing is correct for NNX and Linen)
                for (int i = 0; i < scalarized->second; i++) {
                    tab(fTab, *fOut);
                    *fOut << "state[\"" << scalarized->first << "_" << i << "\"] = ";
                    ScalarZeroInitializer(fOut, inst->fType);
                }
                return;
            }
            tab(fTab, *fOut);
            inst->fAddress->accept(this);
            *fOut << " = ";
            if (inst->fValue) {
                inst->fValue->accept(this);
            } else {
                ZeroInitializer(fOut, inst->fType);
            }
        }
    }

    // Pure virtual: subclasses route to params/state differently
    virtual void visit(NamedAddress* named) = 0;

    // Real-typed buffers follow the runtime `faust_float` constructor argument
    // (this code is emitted inside _initialize_carry, where `self` is in scope),
    // so passing faust_float=jnp.float64 yields a coherent float64 carry.
    static void ZeroInitializer(std::ostream* fOut, Typed* typed)
    {
        ArrayTyped* array_type = dynamic_cast<ArrayTyped*>(typed);
        faustassert(array_type);
        if (isIntPtrType(typed->getType())) {
            *fOut << "np.zeros((" << array_type->fSize << ",), dtype=np.int32)";
        } else {
            *fOut << "np.zeros((" << array_type->fSize << ",), dtype=self.faust_float)";
        }
    }

    // 0-dim variant with the same dtype rules as ZeroInitializer, so a
    // scalarized array element gets exactly the dtype its array would have had
    static void ScalarZeroInitializer(std::ostream* fOut, Typed* typed)
    {
        if (isIntPtrType(typed->getType())) {
            *fOut << "np.zeros((), dtype=np.int32)";
        } else {
            *fOut << "np.zeros((), dtype=self.faust_float)";
        }
    }

    // Needed for waveforms
    virtual void visit(Int32ArrayNumInst* inst)
    {
        *fOut << "np.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << inst->fNumTable[i];
            sep = ',';
        }
        *fOut << "], dtype=np.int32)";
    }

    virtual void visit(FloatArrayNumInst* inst)
    {
        *fOut << "np.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkFloat(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << "], dtype=self.faust_float)";
    }

    virtual void visit(DoubleArrayNumInst* inst)
    {
        *fOut << "np.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkDouble(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << "], dtype=self.faust_float)";
    }
};

/**
 * Collects a human-readable summary of the UI widgets (path, type, range,
 * default, scale) from the user-interface instructions. Used by the NNX and
 * Linen containers to emit the generated class docstring.
 */
struct NNXUIDocVisitor : public DispatchVisitor {
    std::vector<std::string> fParams;     // input widgets (sliders, nentries, buttons, ...)
    std::vector<std::string> fBargraphs;  // output-only widgets
    std::vector<std::string> fSoundfiles;
    std::vector<std::string> fPath;
    std::set<std::string>    fLogSet;
    std::set<std::string>    fExpSet;

    // Strip "[key:value]" metadata and a leading "[N] " ordering prefix from a label.
    static std::string cleanLabel(const std::string& label)
    {
        std::string out;
        size_t      i = 0;
        while (i < label.size()) {
            if (label[i] == '[') {
                size_t close = label.find(']', i);
                if (close != std::string::npos) {
                    i = close + 1;
                    continue;
                }
            }
            out += label[i++];
        }
        // Trim surrounding whitespace left over from removed brackets
        size_t begin = out.find_first_not_of(" \t");
        size_t end   = out.find_last_not_of(" \t");
        return (begin == std::string::npos) ? "" : out.substr(begin, end - begin + 1);
    }

    static std::string num(double v)
    {
        char buf[32];
        snprintf(buf, sizeof(buf), "%g", v);
        return buf;
    }

    std::string fullLabel(const std::string& label)
    {
        std::string out;
        for (const auto& part : fPath) {
            out += part + "/";
        }
        return out + cleanLabel(label);
    }

    void visit(AddMetaDeclareInst* inst) override
    {
        if (inst->fKey == "scale") {
            if (inst->fValue == "exp") {
                fExpSet.emplace(inst->fZone);
            } else if (inst->fValue == "log") {
                fLogSet.emplace(inst->fZone);
            }
        }
    }

    void visit(OpenboxInst* inst) override { fPath.push_back(cleanLabel(inst->fName)); }

    void visit(CloseboxInst* inst) override { fPath.pop_back(); }

    void visit(AddButtonInst* inst) override
    {
        const char* type = (inst->fType == AddButtonInst::kCheckButton) ? "checkbox" : "button";
        fParams.push_back(fullLabel(inst->fLabel) + " (" + type + ")");
    }

    void visit(AddSliderInst* inst) override
    {
        std::string type;
        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                type = "hslider";
                break;
            case AddSliderInst::kVertical:
                type = "vslider";
                break;
            case AddSliderInst::kNumEntry:
                type = "nentry";
                break;
        }
        std::string scale = fExpSet.count(inst->fZone)   ? ", exp scale"
                            : fLogSet.count(inst->fZone) ? ", log scale"
                                                         : "";
        fParams.push_back(fullLabel(inst->fLabel) + " (" + type + " in [" + num(inst->fMin) + ", " +
                          num(inst->fMax) + "], default " + num(inst->fInit) + scale + ")");
    }

    void visit(AddBargraphInst* inst) override
    {
        const char* type = (inst->fType == AddBargraphInst::kVertical) ? "vbargraph" : "hbargraph";
        fBargraphs.push_back(fullLabel(inst->fLabel) + " (" + type + " in [" + num(inst->fMin) +
                             ", " + num(inst->fMax) + "])");
    }

    void visit(AddSoundfileInst* inst) override { fSoundfiles.push_back(fullLabel(inst->fLabel)); }
};

/**
 * Emit the generated class docstring: DSP identity, audio I/O, and the UI
 * parameter table collected by NNXUIDocVisitor. Shared by the NNX and Linen
 * containers (`flavor` names the target module system).
 */
inline void nnxEmitClassDocstring(std::ostream* fOut, int n, const std::string& klass,
                                  const char* flavor, int numInputs, int numOutputs,
                                  const NNXUIDocVisitor& doc)
{
    tab(n + 1, *fOut);
    *fOut << "\"\"\"" << klass << ": Faust DSP compiled to a " << flavor << " module.";
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "Audio I/O: " << numInputs << " in, " << numOutputs << " out.";
    tab(n + 1, *fOut);
    if (doc.fParams.empty()) {
        tab(n + 1, *fOut);
        *fOut << "This DSP has no input UI parameters.";
        tab(n + 1, *fOut);
    } else {
        tab(n + 1, *fOut);
        *fOut << "UI parameters (parameter dicts accept these full label paths, their";
        tab(n + 1, *fOut);
        *fOut << "Faust shortnames, or the internal zone names as keys):";
        for (const auto& line : doc.fParams) {
            tab(n + 1, *fOut);
            *fOut << "- " << line;
        }
        tab(n + 1, *fOut);
    }
    if (!doc.fBargraphs.empty()) {
        tab(n + 1, *fOut);
        *fOut << "Output-only bargraphs:";
        for (const auto& line : doc.fBargraphs) {
            tab(n + 1, *fOut);
            *fOut << "- " << line;
        }
        tab(n + 1, *fOut);
    }
    if (!doc.fSoundfiles.empty()) {
        tab(n + 1, *fOut);
        *fOut << "Soundfiles:";
        for (const auto& line : doc.fSoundfiles) {
            tab(n + 1, *fOut);
            *fOut << "- " << line;
        }
        tab(n + 1, *fOut);
    }
    *fOut << "\"\"\"";
    tab(n + 1, *fOut);
}

/**
 * Base instruction visitor for NNX/Linen code generation.
 *
 * Contains all shared visit methods for both NNX and Linen backends.
 * Subclasses override only visit(NamedAddress*) for different routing.
 */
class NNXBaseInstVisitor : public TextInstVisitor {
   protected:
    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated as most once in the module.
     */
    inline static std::map<std::string, bool> gFunctionSymbolTable;

    // Polymorphic math functions
    std::map<std::string, std::string> gPolyMathLibTable;

    // bool for "is storing left-hand-side".
    bool fIsStoringLhs = false;

    // bool for "will set array" (JAX .at[X].set(Y) pattern).
    bool fWillSetArray = false;

    // bool for "the current store targets a scalarized array element", so the
    // value must be cast to the carry entry's dtype (see visit(StoreVarInst*)).
    bool fIsScalarizedStore = false;

    // Used so that we don't cast to integers in the condition of a while (cond) loop.
    bool fIsDoingWhile = false;

    std::set<std::string> fLogSet;  // set of widget zone having a log UI scale
    std::set<std::string> fExpSet;  // set of widget zone having an exp UI scale

    // All [key:value] widget metadata declared per zone, forwarded to the
    // generated add_nentry/add_soundfile calls as a Python dict. Labels stay
    // clean (metadata-free) so the shared JSON/user-interface instructions are
    // unaffected.
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> fMetaMap;

   public:
    // Set when a random_* foreign function call is emitted; the containers use it
    // to emit the class-level `is_stochastic` flag, which lets the architecture
    // skip per-sample RNG key threading for deterministic DSPs.
    bool fUsesRandom = false;

   protected:
    // Emit a Python double-quoted string literal with proper escaping. Faust UI
    // labels/URLs (and their embedded metadata, e.g. "[style:menu{...}]") may
    // contain characters that are special inside a Python string ("\\", '"', ...);
    // plain quote() would produce broken source, so escape them here.
    static std::string pyStr(const std::string& s)
    {
        std::string out = "\"";
        for (char c : s) {
            switch (c) {
                case '\\':
                    out += "\\\\";
                    break;
                case '"':
                    out += "\\\"";
                    break;
                case '\n':
                    out += "\\n";
                    break;
                case '\r':
                    out += "\\r";
                    break;
                case '\t':
                    out += "\\t";
                    break;
                default:
                    out += c;
                    break;
            }
        }
        out += "\"";
        return out;
    }

    // Emit `, metadata={...}` for the zone's declared [key:value] metadata, or
    // nothing when the zone has none.
    void emitMetadataArg(const std::string& zone)
    {
        auto it = fMetaMap.find(zone);
        if (it == fMetaMap.end() || it->second.empty()) {
            return;
        }
        *fOut << ", metadata={";
        const char* sep = "";
        for (const auto& kv : it->second) {
            *fOut << sep << pyStr(kv.first) << ": " << pyStr(kv.second);
            sep = ", ";
        }
        *fOut << "}";
    }

   public:
    using TextInstVisitor::visit;

    // Use numpy functions (prefix "np.") when true, jax.numpy "jnp." when false.
    bool fUseNumpy = true;

    // Small copy-delay arrays emitted as scalar carry entries (name -> size),
    // computed by NNXScalarizeAnalysis over all emitted blocks.
    std::map<std::string, int> fScalarizedArrays;

    void setScalarizedArrays(const std::map<std::string, int>& arrays)
    {
        fScalarizedArrays = arrays;
    }

    NNXBaseInstVisitor(std::ostream* out, const std::string& struct_name, int tab = 0)
        : TextInstVisitor(out, ".", new JAXStringTypeManager(xfloat(), "*", struct_name), tab)
    {
        // Mark all math.h functions as generated...
        gFunctionSymbolTable["abs"] = true;

        gFunctionSymbolTable["max_i"] = true;
        gFunctionSymbolTable["min_i"] = true;

        gFunctionSymbolTable["max_f"] = true;
        gFunctionSymbolTable["min_f"] = true;

        gFunctionSymbolTable["max_"] = true;
        gFunctionSymbolTable["min_"] = true;

        gFunctionSymbolTable["max_l"] = true;
        gFunctionSymbolTable["min_l"] = true;

        // Float version
        gFunctionSymbolTable["fabsf"]      = true;
        gFunctionSymbolTable["acosf"]      = true;
        gFunctionSymbolTable["asinf"]      = true;
        gFunctionSymbolTable["atanf"]      = true;
        gFunctionSymbolTable["atan2f"]     = true;
        gFunctionSymbolTable["ceilf"]      = true;
        gFunctionSymbolTable["cosf"]       = true;
        gFunctionSymbolTable["expf"]       = true;
        gFunctionSymbolTable["exp10f"]     = false;
        gFunctionSymbolTable["floorf"]     = true;
        gFunctionSymbolTable["fmodf"]      = true;
        gFunctionSymbolTable["logf"]       = true;
        gFunctionSymbolTable["log10f"]     = true;
        gFunctionSymbolTable["powf"]       = true;
        gFunctionSymbolTable["remainderf"] = true;
        gFunctionSymbolTable["rintf"]      = true;
        gFunctionSymbolTable["roundf"]     = true;
        gFunctionSymbolTable["sinf"]       = true;
        gFunctionSymbolTable["sqrtf"]      = true;
        gFunctionSymbolTable["tanf"]       = true;

        // Hyperbolic
        gFunctionSymbolTable["acoshf"] = true;
        gFunctionSymbolTable["asinhf"] = true;
        gFunctionSymbolTable["atanhf"] = true;
        gFunctionSymbolTable["coshf"]  = true;
        gFunctionSymbolTable["sinhf"]  = true;
        gFunctionSymbolTable["tanhf"]  = true;

        // Double version
        gFunctionSymbolTable["fabs"]      = true;
        gFunctionSymbolTable["acos"]      = true;
        gFunctionSymbolTable["asin"]      = true;
        gFunctionSymbolTable["atan"]      = true;
        gFunctionSymbolTable["atan2"]     = true;
        gFunctionSymbolTable["ceil"]      = true;
        gFunctionSymbolTable["cos"]       = true;
        gFunctionSymbolTable["exp"]       = true;
        gFunctionSymbolTable["exp10"]     = false;
        gFunctionSymbolTable["floor"]     = true;
        gFunctionSymbolTable["fmod"]      = true;
        gFunctionSymbolTable["log"]       = true;
        gFunctionSymbolTable["log10"]     = true;
        gFunctionSymbolTable["pow"]       = true;
        gFunctionSymbolTable["remainder"] = true;
        gFunctionSymbolTable["rint"]      = true;
        gFunctionSymbolTable["round"]     = true;
        gFunctionSymbolTable["sin"]       = true;
        gFunctionSymbolTable["sqrt"]      = true;
        gFunctionSymbolTable["tan"]       = true;

        // Hyperbolic
        gFunctionSymbolTable["acosh"] = true;
        gFunctionSymbolTable["asinh"] = true;
        gFunctionSymbolTable["atanh"] = true;
        gFunctionSymbolTable["coshf"] = true;
        gFunctionSymbolTable["sinh"]  = true;
        gFunctionSymbolTable["tanh"]  = true;

        // Quad version
        gFunctionSymbolTable["fabsl"]      = true;
        gFunctionSymbolTable["acosl"]      = true;
        gFunctionSymbolTable["asinl"]      = true;
        gFunctionSymbolTable["atanl"]      = true;
        gFunctionSymbolTable["atan2l"]     = true;
        gFunctionSymbolTable["ceill"]      = true;
        gFunctionSymbolTable["cosl"]       = true;
        gFunctionSymbolTable["expl"]       = true;
        gFunctionSymbolTable["exp10l"]     = false;
        gFunctionSymbolTable["floorl"]     = true;
        gFunctionSymbolTable["fmodl"]      = true;
        gFunctionSymbolTable["logl"]       = true;
        gFunctionSymbolTable["log10l"]     = true;
        gFunctionSymbolTable["powl"]       = true;
        gFunctionSymbolTable["remainderl"] = true;
        gFunctionSymbolTable["rintl"]      = true;
        gFunctionSymbolTable["roundl"]     = true;
        gFunctionSymbolTable["sinl"]       = true;
        gFunctionSymbolTable["sqrtl"]      = true;
        gFunctionSymbolTable["tanl"]       = true;

        // Hyperbolic
        gFunctionSymbolTable["acoshl"] = true;
        gFunctionSymbolTable["asinhl"] = true;
        gFunctionSymbolTable["atanhl"] = true;
        gFunctionSymbolTable["coshl"]  = true;
        gFunctionSymbolTable["sinhl"]  = true;
        gFunctionSymbolTable["tanhl"]  = true;

        // Polymath mapping int version
        gPolyMathLibTable["abs"]   = "jnp.abs";
        gPolyMathLibTable["max_i"] = "jnp.maximum";
        gPolyMathLibTable["min_i"] = "jnp.minimum";

        // Polymath mapping float version
        gPolyMathLibTable["max_f"] = "jnp.maximum";
        gPolyMathLibTable["min_f"] = "jnp.minimum";

        gPolyMathLibTable["fabsf"]  = "jnp.abs";
        gPolyMathLibTable["acosf"]  = "jnp.arccos";
        gPolyMathLibTable["asinf"]  = "jnp.arcsin";
        gPolyMathLibTable["atanf"]  = "jnp.arctan";
        gPolyMathLibTable["atan2f"] = "jnp.arctan2";
        gPolyMathLibTable["ceilf"]  = "jnp.ceil";
        gPolyMathLibTable["cosf"]   = "jnp.cos";
        gPolyMathLibTable["expf"]   = "jnp.exp";
        gPolyMathLibTable["exp2f"]  = "jnp.exp2";
        gPolyMathLibTable["exp10f"] = "jnp.exp10f";
        gPolyMathLibTable["floorf"] = "jnp.floor";
        // jnp.fmod follows C fmodf (sign of the dividend); jnp.mod is Python's
        // floored modulo and diverges for negative operands.
        gPolyMathLibTable["fmodf"]  = "jnp.fmod";
        gPolyMathLibTable["logf"]   = "jnp.log";
        gPolyMathLibTable["log2f"]  = "jnp.log2";
        gPolyMathLibTable["log10f"] = "jnp.log10";
        gPolyMathLibTable["powf"]   = "jnp.power";
        // Do NOT change to jnp.remainder: that is floored modulo (sign of the
        // divisor, same as jnp.mod / Python %). C's remainder() rounds the
        // quotient to nearest (ties to even), so the code container emits a
        // custom remainder(x, y) = x - round(x/y)*y that matches the reference.
        gPolyMathLibTable["remainderf"] = "remainder";
        gPolyMathLibTable["rintf"]      = "jnp.rint";
        gPolyMathLibTable["roundf"]     = "jnp.round";
        gPolyMathLibTable["sinf"]       = "jnp.sin";
        gPolyMathLibTable["sqrtf"]      = "jnp.sqrt";
        gPolyMathLibTable["tanf"]       = "jnp.tan";

        // Hyperbolic
        gPolyMathLibTable["acoshf"] = "jnp.arccosh";
        gPolyMathLibTable["asinhf"] = "jnp.arcsinh";
        gPolyMathLibTable["atanhf"] = "jnp.arctanh";
        gPolyMathLibTable["coshf"]  = "jnp.cosh";
        gPolyMathLibTable["sinhf"]  = "jnp.sinh";
        gPolyMathLibTable["tanhf"]  = "jnp.tanh";

        gPolyMathLibTable["isnanf"]    = "jnp.isnan";
        gPolyMathLibTable["isinff"]    = "jnp.isinf";
        gPolyMathLibTable["copysignf"] = "jnp.copysign";

        // Polymath mapping double version
        gPolyMathLibTable["max_"] = "jnp.maximum";
        gPolyMathLibTable["min_"] = "jnp.minimum";

        gPolyMathLibTable["fabs"]  = "jnp.abs";
        gPolyMathLibTable["acos"]  = "jnp.arccos";
        gPolyMathLibTable["asin"]  = "jnp.arcsin";
        gPolyMathLibTable["atan"]  = "jnp.arctan";
        gPolyMathLibTable["atan2"] = "jnp.arctan2";
        gPolyMathLibTable["ceil"]  = "jnp.ceil";
        gPolyMathLibTable["cos"]   = "jnp.cos";
        gPolyMathLibTable["exp"]   = "jnp.exp";
        gPolyMathLibTable["exp2"]  = "jnp.exp2";
        gPolyMathLibTable["exp10"] = "jnp.exp10";
        gPolyMathLibTable["floor"] = "jnp.floor";
        // jnp.fmod follows C fmod (sign of the dividend); see the float version above.
        gPolyMathLibTable["fmod"]  = "jnp.fmod";
        gPolyMathLibTable["log"]   = "jnp.log";
        gPolyMathLibTable["log2"]  = "jnp.log2";
        gPolyMathLibTable["log10"] = "jnp.log10";
        gPolyMathLibTable["pow"]   = "jnp.power";
        // Do NOT change to jnp.remainder: see the remainderf note above.
        gPolyMathLibTable["remainder"] = "remainder";
        gPolyMathLibTable["rint"]      = "jnp.rint";
        gPolyMathLibTable["round"]     = "jnp.round";
        gPolyMathLibTable["sin"]       = "jnp.sin";
        gPolyMathLibTable["sqrt"]      = "jnp.sqrt";
        gPolyMathLibTable["tan"]       = "jnp.tan";

        // Hyperbolic
        gPolyMathLibTable["acosh"] = "jnp.arccosh";
        gPolyMathLibTable["asinh"] = "jnp.arcsinh";
        gPolyMathLibTable["atanh"] = "jnp.arctanh";
        gPolyMathLibTable["cosh"]  = "jnp.cosh";
        gPolyMathLibTable["sinh"]  = "jnp.sinh";
        gPolyMathLibTable["tanh"]  = "jnp.tanh";

        gPolyMathLibTable["isnan"]    = "jnp.isnan";
        gPolyMathLibTable["isinf"]    = "jnp.isinf";
        gPolyMathLibTable["copysign"] = "jnp.copysign";
    }

    virtual ~NNXBaseInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst)
    {
        fMetaMap[inst->fZone].push_back({inst->fKey, inst->fValue});
        if (inst->fKey == "scale") {
            if (inst->fValue == "exp") {
                fExpSet.emplace(inst->fZone);
            } else if (inst->fValue == "log") {
                fLogSet.emplace(inst->fZone);
            } else {
                // it's linear by default
            }
        }
    }

    virtual void visit(OpenboxInst* inst)
    {
        *fOut << "ui_path.append(" << pyStr(inst->fName) << ")";
        EndLine(' ');
    }

    virtual void visit(CloseboxInst* inst)
    {
        *fOut << "ui_path.pop()";
        tab(fTab, *fOut);
    }

    virtual void visit(AddButtonInst* inst)
    {
        const char* method =
            (inst->fType == AddButtonInst::kCheckButton) ? "add_checkbox" : "add_button";
        *fOut << "self." << method << "(" << quote(inst->fZone) << ", ui_path, "
              << pyStr(inst->fLabel) << ", unnorm_funcs)";
        EndLine(' ');
    }

    virtual void visit(AddSliderInst* inst)
    {
        std::string scaleMode = "";
        if (fExpSet.count(inst->fZone)) {
            scaleMode = "\"exp\"";
        } else if (fLogSet.count(inst->fZone)) {
            scaleMode = "\"log\"";
        } else {
            scaleMode = "\"linear\"";
        }

        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                // clang-format off
                *fOut << "self.add_hslider("
                    << quote(inst->fZone) << ", ui_path, "
                    << pyStr(inst->fLabel) << ", "
                    << checkReal(inst->fInit) << ", "
                    << checkReal(inst->fMin) << ", "
                    << checkReal(inst->fMax) << ", "
                    << checkReal(inst->fStep) << ", unnorm_funcs, "
                    << scaleMode << ")";
                break;
                // clang-format on
            case AddSliderInst::kVertical:
                // clang-format off
                *fOut << "self.add_vslider("
                    << quote(inst->fZone) << ", ui_path, "
                    << pyStr(inst->fLabel) << ", "
                    << checkReal(inst->fInit) << ", "
                    << checkReal(inst->fMin) << ", "
                    << checkReal(inst->fMax) << ", "
                    << checkReal(inst->fStep) << ", unnorm_funcs, "
                    << scaleMode << ")";
                break;
                // clang-format on
            case AddSliderInst::kNumEntry:
                // clang-format off
                *fOut << "self.add_nentry("
                    << quote(inst->fZone) << ", ui_path, "
                    << pyStr(inst->fLabel) << ", "
                    << checkReal(inst->fInit) << ", "
                    << checkReal(inst->fMin) << ", "
                    << checkReal(inst->fMax) << ", "
                    << checkReal(inst->fStep) << ", unnorm_funcs, "
                    << scaleMode;
                // clang-format on
                emitMetadataArg(inst->fZone);
                *fOut << ")";
                break;
        }
        EndLine(' ');
    }

    virtual void visit(AddBargraphInst* inst)
    {
        const char* method =
            (inst->fType == AddBargraphInst::kVertical) ? "add_vbargraph" : "add_hbargraph";
        *fOut << "self." << method << "(" << quote(inst->fZone) << ", ui_path, "
              << pyStr(inst->fLabel) << ", " << checkReal(inst->fMin) << ", "
              << checkReal(inst->fMax) << ", unnorm_funcs)";
        EndLine(' ');
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        *fOut << "self.add_soundfile(" << quote(inst->fSFZone) << ", ui_path, "
              << pyStr(inst->fLabel) << ", " << pyStr(inst->fURL) << ", unnorm_funcs";
        emitMetadataArg(inst->fSFZone);
        *fOut << ")";
        EndLine(' ');
    }

    virtual void visit(Int32NumInst* inst) { *fOut << inst->fNum; }

    virtual void visit(Int64NumInst* inst) { *fOut << inst->fNum; }

    virtual void visit(Int32ArrayNumInst* inst)
    {
        *fOut << "jnp.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << inst->fNumTable[i];
            sep = ',';
        }
        *fOut << "], dtype=jnp.int32)";
    }

    // Real-typed array literals follow the runtime `faust_float` constructor
    // argument (emitted inside methods where `self` is in scope), matching the
    // state buffers created in _initialize_carry.
    virtual void visit(FloatArrayNumInst* inst)
    {
        *fOut << "jnp.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkFloat(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << "], dtype=self.faust_float)";
    }

    virtual void visit(DoubleArrayNumInst* inst)
    {
        *fOut << "jnp.array(";
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkDouble(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << "], dtype=self.faust_float)";
    }

    virtual void visit(BinopInst* inst)
    {
        if (inst->fOpcode == kXOR) {
            *fOut << "(";
            inst->fInst1->accept(this);
            *fOut << " ^ ";
            inst->fInst2->accept(this);
            *fOut << ")";
        } else if (inst->fOpcode == kRem) {
            // Python's % is floored modulo; C's integer % truncates toward zero
            // (sign of the dividend). fmod implements the C semantics.
            *fOut << (fUseNumpy ? "np" : "jnp") << ".fmod(";
            inst->fInst1->accept(this);
            *fOut << ", ";
            inst->fInst2->accept(this);
            *fOut << ")";
        } else {
            *fOut << "(";
            inst->fInst1->accept(this);
            *fOut << " ";
            *fOut << gBinOpTable[inst->fOpcode]->fName;
            *fOut << " ";
            inst->fInst2->accept(this);
            *fOut << ")";

            bool opCodeIsBoolean = inst->fOpcode >= kGT && inst->fOpcode <= kXOR;
            if (opCodeIsBoolean && !fIsDoingWhile) {
                *fOut << ".astype(jnp.int32)";
            }
        }
    }

    virtual void visit(DeclareVarInst* inst)
    {
        if (inst->fAddress->isStaticStruct()) {
            *fOut << fTypeManager->generateType(inst->fType, inst->getName());
            // Allocation is actually done in NNXBaseInitFieldsVisitor
        } else {
            *fOut << fTypeManager->generateType(inst->fType, inst->getName());
            if (inst->fValue) {
                *fOut << " = ";
                inst->fValue->accept(this);
            }
        }
        EndLine(' ');
    }

    virtual void visitAux(RetInst* inst, bool gen_empty)
    {
        if (inst->fResult) {
            *fOut << "return ";
            inst->fResult->accept(this);
            EndLine(' ');
        } else if (gen_empty) {
            *fOut << "return";
            EndLine(' ');
        }
    }

    virtual void visit(DropInst* inst)
    {
        if (inst->fResult) {
            inst->fResult->accept(this);
            EndLine(' ');
        }
    }

    virtual void visit(DeclareFunInst* inst)
    {
        // Already generated
        if (gFunctionSymbolTable.find(inst->fName) != gFunctionSymbolTable.end()) {
            return;
        } else {
            gFunctionSymbolTable[inst->fName] = true;
        }

        *fOut << "def " << inst->fName;
        generateFunDefArgs(inst);
        generateFunDefBody(inst);
    }

    virtual void visit(DeclareBufferIterators* inst)
    {
        // Don't generate if no channels
        if (inst->fChannels == 0) {
            return;
        }

        for (int i = 0; i < inst->fChannels; ++i) {
            *fOut << inst->fBufferName1 << i << " = " << inst->fBufferName2 << "[ " << i << ":"
                  << i + 1 << ",:]";
            tab(fTab, *fOut);
        }
    }

    virtual void generateFunDefBody(DeclareFunInst* inst)
    {
        if (inst->fCode->fCode.size() == 0) {
            *fOut << "):";
            fTab++;
            tab(fTab, *fOut);
            *fOut << "pass";
            fTab--;
            tab(fTab, *fOut);
            tab(fTab, *fOut);
        } else {
            // Function body
            *fOut << "):";
            fTab++;
            tab(fTab, *fOut);
            inst->fCode->accept(this);
            fTab--;
            back(1, *fOut);
            tab(fTab, *fOut);
        }
    }

    // Pure virtual: subclasses route to params/state differently
    virtual void visit(NamedAddress* named) = 0;

    /*
    Indexed address can actually be values in an array or fields in a struct type
    */
    virtual void visit(IndexedAddress* indexed)
    {
        // Scalarized copy-delay array: access element i as the scalar state
        // entry "name_i" with a plain assignment (no .at[].set()). The
        // analysis guarantees every access uses a single constant index.
        {
            NamedAddress* named = dynamic_cast<NamedAddress*>(indexed->fAddress);
            if (named && fScalarizedArrays.find(named->fName) != fScalarizedArrays.end()) {
                Int32NumInst* field_index = dynamic_cast<Int32NumInst*>(indexed->getIndex());
                faustassert(field_index);
                *fOut << "state[\"" << named->fName << "_" << field_index->fNum << "\"]";
                fWillSetArray = false;
                if (fIsStoringLhs) {
                    fIsScalarizedStore = true;
                }
                return;
            }
        }

        if (fUseNumpy) {
            indexed->fAddress->accept(this);
            DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
            if (struct_type) {
                Int32NumInst* field_index = static_cast<Int32NumInst*>(indexed->getIndex());
                *fOut << "[\"" << struct_type->fType->getName(field_index->fNum) << "\"]";
            } else {
                Int32NumInst* field_index = dynamic_cast<Int32NumInst*>(indexed->getIndex());
                if (field_index) {
                    *fOut << "[" << field_index->fNum << "]";
                } else {
                    *fOut << "[";
                    indexed->getIndex()->accept(this);
                    *fOut << "]";
                }
            }

        } else {
            indexed->fAddress->accept(this);
            DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
            if (struct_type) {
                Int32NumInst* field_index = static_cast<Int32NumInst*>(indexed->getIndex());
                *fOut << "[\"" << struct_type->fType->getName(field_index->fNum) << "\"]";
            } else {
                if (fIsStoringLhs) {
                    fWillSetArray = true;
                    return;
                }

                if (fWillSetArray) {
                    *fOut << ".at";
                    fWillSetArray = false;
                }

                Int32NumInst* field_index = dynamic_cast<Int32NumInst*>(indexed->getIndex());
                if (field_index) {
                    *fOut << "[" << field_index->fNum << "]";
                } else {
                    *fOut << "[";
                    indexed->getIndex()->accept(this);
                    *fOut << "]";
                }
            }
        }
    }

    virtual void visit(LoadVarAddressInst* inst) { faustassert(false); }

    virtual void visit(StoreVarInst* inst)
    {
        // Check if this is a cache variable assignment (ends with "ca")
        NamedAddress* named      = dynamic_cast<NamedAddress*>(inst->fAddress);
        bool          isCacheVar = false;
        if (named) {
            std::string name = named->fName;
            isCacheVar       = (name.length() > 2 && name.substr(name.length() - 2) == "ca");
        }

        if (isCacheVar) {
            // For cache variables, create a local variable instead of storing to state
            *fOut << named->fName << " = ";
            inst->fValue->accept(this);
        } else {
            fIsStoringLhs = true;
            inst->fAddress->accept(this);
            fIsStoringLhs = false;
            *fOut << " = ";

            if (fWillSetArray) {
                inst->fAddress->accept(this);
                *fOut << ".set(";
                inst->fValue->accept(this);
                *fOut << ")";
            } else if (fIsScalarizedStore) {
                // Match .at[].set() semantics: coerce the value to the carry
                // entry's dtype (e.g. a bare Python int literal would
                // otherwise become int64 under jax_enable_x64 and change the
                // carry pytree between scan iterations). A same-dtype astype
                // is elided by XLA, so this costs nothing once compiled.
                fIsScalarizedStore = false;
                *fOut << (fUseNumpy ? "np" : "jnp") << ".asarray(";
                inst->fValue->accept(this);
                *fOut << ").astype(";
                inst->fAddress->accept(this);
                *fOut << ".dtype)";
            } else {
                inst->fValue->accept(this);
            }
        }

        EndLine(' ');
    }

    virtual void visit(::CastInst* inst)
    {
        if (isIntType(inst->fType->getType())) {
            *fOut << (fUseNumpy ? "np.int32(" : "jnp.int32(");
            inst->fInst->accept(this);
            *fOut << ")";
        } else {
            // JAXStringTypeManager maps real types to "", so the cast must be
            // spelled out here. In tick (jnp mode) follow the runtime
            // `faust_float` dtype like the carry buffers do; in the numpy init
            // code use the compiled precision directly, since a per-element
            // self.faust_float() call inside a table-fill loop would create a
            // JAX array on every iteration.
            if (fUseNumpy) {
                *fOut << ((itfloat() == Typed::kDouble) ? "np.float64(" : "np.float32(");
            } else {
                *fOut << "self.faust_float(";
            }
            inst->fInst->accept(this);
            *fOut << ")";
        }
    }

    virtual void visit(BitcastInst* inst) { faustassert(false); }

    virtual void visitCond(ValueInst* cond)
    {
        *fOut << "(";
        cond->accept(this);
        *fOut << " != 0)";
    }

    virtual void visit(Select2Inst* inst)
    {
        *fOut << "jnp.where(";
        visitCond(inst->fCond);
        *fOut << ", ";
        inst->fThen->accept(this);
        *fOut << ", ";
        inst->fElse->accept(this);
        *fOut << ")";
    }

    // Generate standard funcall (not 'method' like funcall...)
    virtual void visit(FunCallInst* inst)
    {
        // Random foreign functions are dispatched to self.<name>() helpers with an
        // RNG key injected as the first argument. Forward ALL DSP-provided arguments
        // unchanged (rate, p, a/b, ...) rather than dropping them on unexpected arity:
        // a wrong arity then fails loudly at runtime instead of silently using defaults.
        if (isNNXRandomFunction(inst->fName)) {
            fUsesRandom = true;
            *fOut << "self." << inst->fName << "(rngs()";
            if (inst->fArgs.size() > 0) {
                *fOut << ", ";
                generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
            }
            *fOut << ")";
            return;
        }

        std::string name = (gPolyMathLibTable.find(inst->fName) != gPolyMathLibTable.end())
                               ? gPolyMathLibTable[inst->fName]
                               : inst->fName;
        if (fUseNumpy && name.rfind("jnp.") == 0) {
            // turn "jnp." into "np."
            name = name.substr(1, name.size() - 1);
        }
        *fOut << name << "(";
        // Compile parameters
        generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
        *fOut << ")";
    }

    virtual void visit(IfInst* inst)
    {
        *fOut << "if ";
        visitCond(inst->fCond);
        *fOut << ":";
        fTab++;
        tab(fTab, *fOut);
        inst->fThen->accept(this);
        fTab--;
        back(1, *fOut);
        if (inst->fElse->fCode.size() > 0) {
            *fOut << "else:";
            fTab++;
            tab(fTab, *fOut);
            inst->fElse->accept(this);
            fTab--;
            back(1, *fOut);
        }
        tab(fTab, *fOut);
    }

    virtual void visit(ForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) {
            return;
        }

        fIsDoingWhile = true;

        fFinishLine = false;
        inst->fInit->accept(this);
        tab(fTab, *fOut);
        *fOut << "while ";
        inst->fEnd->accept(this);
        fIsDoingWhile = false;
        *fOut << ":";
        tab(fTab, *fOut);
        fFinishLine = true;
        fTab++;
        tab(fTab, *fOut);
        inst->fCode->accept(this);
        tab(fTab, *fOut);
        inst->fIncrement->accept(this);
        fTab--;
        back(1, *fOut);
        tab(fTab, *fOut);
    }

    virtual void visit(SimpleForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) {
            return;
        }
        *fOut << "for " << inst->getName() << " in ";

        if (inst->fReverse) {
            // todo:
            *fOut << "reverse(";
            Int32NumInst* lower_bound = dynamic_cast<Int32NumInst*>(inst->fLowerBound);
            faustassert(lower_bound);
            *fOut << lower_bound->fNum << ":";
            Int32NumInst* upper_bound = dynamic_cast<Int32NumInst*>(inst->fUpperBound);
            if (upper_bound) {
                *fOut << upper_bound->fNum;
            } else {
                inst->fUpperBound->accept(this);
            }
            *fOut << ")";
        } else {
            Int32NumInst* lower_bound = dynamic_cast<Int32NumInst*>(inst->fLowerBound);
            faustassert(lower_bound);
            Int32NumInst* upper_bound = dynamic_cast<Int32NumInst*>(inst->fUpperBound);
            if (upper_bound) {
                *fOut << "range(" << lower_bound->fNum << ", " << upper_bound->fNum;
                if (upper_bound->fNum <= lower_bound->fNum) {
                    *fOut << ", -1";
                }
            } else {
                *fOut << "range(" << lower_bound->fNum << ", ";
                inst->fUpperBound->accept(this);
            }
            *fOut << "):";
        }

        fTab++;
        tab(fTab, *fOut);
        inst->fCode->accept(this);
        fTab--;
        back(1, *fOut);
        tab(fTab, *fOut);
    }

    static void cleanup() { gFunctionSymbolTable.clear(); }
};

#endif
