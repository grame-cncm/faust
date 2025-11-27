/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2025 GRAME, Centre National de Creation Musicale
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

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include <emscripten.h>
#include <emscripten/bind.h>

#include "adapter.h"
#include "faust/dsp/libfaust-box.h"
#include "faust/dsp/libfaust-signal.h"

using namespace emscripten;

/*
 * WebAssembly embind surface for libfaust.
 *
 * - Exposes libFaustWasm plus the full Box/Signal APIs from libfaust-box.h/libfaust-signal.h.
 * - Functions that normally return values through out-parameters are wrapped to return a JS object
 *   shaped as { result: bool, <fields> }, with C++ pointer outputs encoded as integers
 *   (reinterpret_cast<uintptr_t>). These pointer integers must be passed back unchanged to other
 *   bindings when composing calls.
 * - createLibContext/destroyLibContext must bracket libfaust usage, matching the native API.
 */

namespace {

template <typename Ptr>
uintptr_t ptrValue(Ptr ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

std::vector<const char*> toArgv(const std::vector<std::string>& args)
{
    std::vector<const char*> argv;
    argv.reserve(args.size());
    for (const auto& arg : args) {
        argv.push_back(arg.c_str());
    }
    return argv;
}

template <typename T>
std::pair<const char*, T> resultField(const char* name, T value)
{
    return {name, value};
}

template <typename... Fields>
val makeResult(bool ok, Fields... fields)
{
    val res = val::object();
    res.set("result", ok);
    int dummy[] = {0, (res.set(fields.first, fields.second), 0)...};
    (void)dummy;
    return res;
}

/*
 * Wrapper result payloads (in addition to "result"):
 *  - wrapGetDefNameProperty: id
 *  - wrapDSPToBoxes: box, inputs, outputs, error
 *  - wrapGetBoxType: inputs, outputs
 *  - wrapBoxesToSignals / wrapBoxesToSignals2: signals, error
 *  - wrapCreateSourceFromBoxes / wrapCreateSourceFromSignals: source, error
 *
 *  Box inspectors:
 *    wrapIsBoxAccess{exp,id}, wrapIsBoxComponent{filename}, wrapIsBoxLibrary{filename},
 *    wrapIsBoxMetadata{exp,metadata}, wrapIsBoxRoute{n,m,r}, wrapIsBoxWithLocalDef{body,local},
 *    wrapIsBoxIdent{name}, wrapIsBoxInt{value}, wrapIsBoxReal{value}, wrapIsBoxSlot{id},
 *    wrapIsBoxInputs{inputs}, wrapIsBoxOutputs{outputs}, wrapIsBoxPar{x,y}, wrapIsBoxSeq{x,y},
 *    wrapIsBoxRec{x,y}, wrapIsBoxMerge{x,y},
 *    wrapIsBoxIPar / wrapIsBoxIProd / wrapIsBoxISeq / wrapIsBoxISum{x,y,z}.
 *
 *  Signal inspectors:
 *    wrapIsSig[Int|Int64|Real]{value}, wrapIsSigInput{index}, wrapIsSigOutput{index,signal},
 *    wrapIsSigDelay1{signal}, wrapIsSigDelay{signal,delay}, wrapIsSigPrefix{head,tail},
 *    wrapIsSigRDTbl{table,index}, wrapIsSigWRTbl{id,table,index,signal},
 *    wrapIsSigGen{signal}, wrapIsSigDocConstantTbl{size,signal},
 *    wrapIsSigDocWriteTbl{size,signal,writeIndex,writeSignal},
 *    wrapIsSigDocAccessTbl{table,index},
 *    wrapIsSigSelect2{selector,s1,s2}, wrapIsSigAssertBounds{signal,low,high},
 *    wrapIsSigHighest{signal}, wrapIsSigLowest{signal},
 *    wrapIsSigBinOp{op,x,y}, wrapIsSigFFun{function,args},
 *    wrapIsSigFConst{type,name,file}, wrapIsSigFVar{type,name,file},
 *    wrapIsProj{index,signal}, wrapIsRec{var,body},
 *    wrapIsSigIntCast{signal}, wrapIsSigFloatCast{signal},
 *    wrapIsSigButton / wrapIsSigCheckbox{label},
 *    wrapIsSigHSlider / wrapIsSigVSlider / wrapIsSigNumEntry{label,init,min,max,step},
 *    wrapIsSigHBargraph / wrapIsSigVBargraph{label,min,max,signal},
 *    wrapIsSigAttach{signal,attached}, wrapIsSigEnable{signal,enable},
 *    wrapIsSigControl{signal,control}, wrapIsSigSoundfile{label},
 *    wrapIsSigSoundfileLength{soundfile,part}, wrapIsSigSoundfileRate{soundfile,part},
 *    wrapIsSigSoundfileBuffer{soundfile,channel,part,index}.
 */

val wrapGetDefNameProperty(Box b)
{
    Box id  = nullptr;
    bool ok = getDefNameProperty(b, id);

    val res = val::object();
    res.set("result", ok);
    res.set("id", ptrValue(id));
    return res;
}

val wrapDSPToBoxes(const std::string& name_app, const std::string& dsp_content,
                   const std::vector<std::string>& args)
{
    auto         argv = toArgv(args);
    int          inputs = 0;
    int          outputs = 0;
    std::string  error_msg;
    Box          box = DSPToBoxes(name_app, dsp_content, argv.size(), argv.data(), &inputs,
                         &outputs, error_msg);
    val          res = val::object();
    res.set("box", ptrValue(box));
    res.set("inputs", inputs);
    res.set("outputs", outputs);
    res.set("error", error_msg);
    return res;
}

val wrapGetBoxType(Box box)
{
    int  inputs  = 0;
    int  outputs = 0;
    bool ok      = getBoxType(box, &inputs, &outputs);

    val res = val::object();
    res.set("result", ok);
    res.set("inputs", inputs);
    res.set("outputs", outputs);
    return res;
}

val wrapBoxesToSignals(Box box)
{
    std::string error_msg;
    tvec        signals = boxesToSignals(box, error_msg);

    val res = val::object();
    res.set("signals", signals);
    res.set("error", error_msg);
    return res;
}

val wrapBoxesToSignals2(Box box)
{
    std::string error_msg;
    tvec        signals = boxesToSignals2(box, error_msg);

    val res = val::object();
    res.set("signals", signals);
    res.set("error", error_msg);
    return res;
}

val wrapCreateSourceFromBoxes(const std::string& name_app, Box box, const std::string& lang,
                              const std::vector<std::string>& args)
{
    auto        argv = toArgv(args);
    std::string error_msg;
    std::string source =
        createSourceFromBoxes(name_app, box, lang, argv.size(), argv.data(), error_msg);

    val res = val::object();
    res.set("source", source);
    res.set("error", error_msg);
    return res;
}

val wrapCreateSourceFromSignals(const std::string& name_app, tvec osigs, const std::string& lang,
                                const std::vector<std::string>& args)
{
    auto        argv = toArgv(args);
    std::string error_msg;
    std::string source =
        createSourceFromSignals(name_app, osigs, lang, argv.size(), argv.data(), error_msg);

    val res = val::object();
    res.set("source", source);
    res.set("error", error_msg);
    return res;
}

val wrapIsBoxAccess(Box t)
{
    Box exp = nullptr;
    Box id  = nullptr;
    return makeResult(isBoxAccess(t, exp, id), resultField("exp", ptrValue(exp)),
                      resultField("id", ptrValue(id)));
}

val wrapIsBoxComponent(Box b)
{
    Box filename = nullptr;
    return makeResult(isBoxComponent(b, filename), resultField("filename", ptrValue(filename)));
}

val wrapIsBoxLibrary(Box b)
{
    Box filename = nullptr;
    return makeResult(isBoxLibrary(b, filename), resultField("filename", ptrValue(filename)));
}

val wrapIsBoxMetadata(Box b)
{
    Box exp = nullptr;
    Box md  = nullptr;
    return makeResult(isBoxMetadata(b, exp, md), resultField("exp", ptrValue(exp)),
                      resultField("metadata", ptrValue(md)));
}

val wrapIsBoxRoute(Box b)
{
    Box n = nullptr;
    Box m = nullptr;
    Box r = nullptr;
    return makeResult(isBoxRoute(b, n, m, r), resultField("n", ptrValue(n)),
                      resultField("m", ptrValue(m)), resultField("r", ptrValue(r)));
}

val wrapIsBoxWithLocalDef(Box t)
{
    Box body = nullptr;
    Box ldef = nullptr;
    return makeResult(isBoxWithLocalDef(t, body, ldef), resultField("body", ptrValue(body)),
                      resultField("local", ptrValue(ldef)));
}

val wrapIsBoxIdent(Box t)
{
    const char* name = nullptr;
    return makeResult(isBoxIdent(t, &name),
                      resultField("name", std::string(name ? name : "")));
}

val wrapIsBoxInt(Box t)
{
    int value = 0;
    return makeResult(isBoxInt(t, &value), resultField("value", value));
}

val wrapIsBoxReal(Box t)
{
    double value = 0;
    return makeResult(isBoxReal(t, &value), resultField("value", value));
}

val wrapIsBoxSlot(Box t)
{
    int id = 0;
    return makeResult(isBoxSlot(t, &id), resultField("id", id));
}

val wrapIsBoxInputs(Box t)
{
    Box x = nullptr;
    return makeResult(isBoxInputs(t, x), resultField("inputs", ptrValue(x)));
}

val wrapIsBoxIPar(Box t)
{
    Box x = nullptr;
    Box y = nullptr;
    Box z = nullptr;
    return makeResult(isBoxIPar(t, x, y, z), resultField("x", ptrValue(x)),
                      resultField("y", ptrValue(y)), resultField("z", ptrValue(z)));
}

val wrapIsBoxIProd(Box t)
{
    Box x = nullptr;
    Box y = nullptr;
    Box z = nullptr;
    return makeResult(isBoxIProd(t, x, y, z), resultField("x", ptrValue(x)),
                      resultField("y", ptrValue(y)), resultField("z", ptrValue(z)));
}

val wrapIsBoxISeq(Box t)
{
    Box x = nullptr;
    Box y = nullptr;
    Box z = nullptr;
    return makeResult(isBoxISeq(t, x, y, z), resultField("x", ptrValue(x)),
                      resultField("y", ptrValue(y)), resultField("z", ptrValue(z)));
}

val wrapIsBoxISum(Box t)
{
    Box x = nullptr;
    Box y = nullptr;
    Box z = nullptr;
    return makeResult(isBoxISum(t, x, y, z), resultField("x", ptrValue(x)),
                      resultField("y", ptrValue(y)), resultField("z", ptrValue(z)));
}

val wrapIsBoxMerge(Box t)
{
    Box x = nullptr;
    Box y = nullptr;
    return makeResult(isBoxMerge(t, x, y), resultField("x", ptrValue(x)),
                      resultField("y", ptrValue(y)));
}

val wrapIsBoxOutputs(Box t)
{
    Box x = nullptr;
    return makeResult(isBoxOutputs(t, x), resultField("outputs", ptrValue(x)));
}

val wrapIsBoxPar(Box t)
{
    Box x = nullptr;
    Box y = nullptr;
    return makeResult(isBoxPar(t, x, y), resultField("x", ptrValue(x)),
                      resultField("y", ptrValue(y)));
}

val wrapIsBoxRec(Box t)
{
    Box x = nullptr;
    Box y = nullptr;
    return makeResult(isBoxRec(t, x, y), resultField("x", ptrValue(x)),
                      resultField("y", ptrValue(y)));
}

val wrapIsBoxSeq(Box t)
{
    Box x = nullptr;
    Box y = nullptr;
    return makeResult(isBoxSeq(t, x, y), resultField("x", ptrValue(x)),
                      resultField("y", ptrValue(y)));
}

val wrapIsSigInt(Signal t)
{
    int value = 0;
    return makeResult(isSigInt(t, &value), resultField("value", value));
}

val wrapIsSigInt64(Signal t)
{
    int64_t value = 0;
    return makeResult(isSigInt64(t, &value), resultField("value", value));
}

val wrapIsSigReal(Signal t)
{
    double value = 0;
    return makeResult(isSigReal(t, &value), resultField("value", value));
}

val wrapIsSigInput(Signal t)
{
    int index = 0;
    return makeResult(isSigInput(t, &index), resultField("index", index));
}

val wrapIsSigOutput(Signal t)
{
    int    index = 0;
    Signal sig   = nullptr;
    return makeResult(isSigOutput(t, &index, sig), resultField("index", index),
                      resultField("signal", ptrValue(sig)));
}

val wrapIsSigDelay1(Signal t)
{
    Signal base = nullptr;
    return makeResult(isSigDelay1(t, base), resultField("signal", ptrValue(base)));
}

val wrapIsSigDelay(Signal t)
{
    Signal base = nullptr;
    Signal del  = nullptr;
    return makeResult(isSigDelay(t, base, del), resultField("signal", ptrValue(base)),
                      resultField("delay", ptrValue(del)));
}

val wrapIsSigPrefix(Signal t)
{
    Signal s0 = nullptr;
    Signal s1 = nullptr;
    return makeResult(isSigPrefix(t, s0, s1), resultField("head", ptrValue(s0)),
                      resultField("tail", ptrValue(s1)));
}

val wrapIsSigRDTbl(Signal s)
{
    Signal t = nullptr;
    Signal i = nullptr;
    return makeResult(isSigRDTbl(s, t, i), resultField("table", ptrValue(t)),
                      resultField("index", ptrValue(i)));
}

val wrapIsSigWRTbl(Signal u)
{
    Signal id = nullptr;
    Signal t  = nullptr;
    Signal i  = nullptr;
    Signal s  = nullptr;
    return makeResult(isSigWRTbl(u, id, t, i, s), resultField("id", ptrValue(id)),
                      resultField("table", ptrValue(t)), resultField("index", ptrValue(i)),
                      resultField("signal", ptrValue(s)));
}

val wrapIsSigGen(Signal t)
{
    Signal x = nullptr;
    return makeResult(isSigGen(t, x), resultField("signal", ptrValue(x)));
}

val wrapIsSigDocConstantTbl(Signal t)
{
    Signal n   = nullptr;
    Signal sig = nullptr;
    return makeResult(isSigDocConstantTbl(t, n, sig), resultField("size", ptrValue(n)),
                      resultField("signal", ptrValue(sig)));
}

val wrapIsSigDocWriteTbl(Signal t)
{
    Signal n    = nullptr;
    Signal sig  = nullptr;
    Signal widx = nullptr;
    Signal wsig = nullptr;
    return makeResult(isSigDocWriteTbl(t, n, sig, widx, wsig), resultField("size", ptrValue(n)),
                      resultField("signal", ptrValue(sig)), resultField("writeIndex", ptrValue(widx)),
                      resultField("writeSignal", ptrValue(wsig)));
}

val wrapIsSigDocAccessTbl(Signal t)
{
    Signal tbl  = nullptr;
    Signal ridx = nullptr;
    return makeResult(isSigDocAccessTbl(t, tbl, ridx), resultField("table", ptrValue(tbl)),
                      resultField("index", ptrValue(ridx)));
}

val wrapIsSigSelect2(Signal t)
{
    Signal selector = nullptr;
    Signal s1       = nullptr;
    Signal s2       = nullptr;
    return makeResult(isSigSelect2(t, selector, s1, s2),
                      resultField("selector", ptrValue(selector)), resultField("s1", ptrValue(s1)),
                      resultField("s2", ptrValue(s2)));
}

val wrapIsSigAssertBounds(Signal t)
{
    Signal s1 = nullptr;
    Signal s2 = nullptr;
    Signal s3 = nullptr;
    return makeResult(isSigAssertBounds(t, s1, s2, s3), resultField("signal", ptrValue(s1)),
                      resultField("low", ptrValue(s2)), resultField("high", ptrValue(s3)));
}

val wrapIsSigHighest(Signal t)
{
    Signal s = nullptr;
    return makeResult(isSigHighest(t, s), resultField("signal", ptrValue(s)));
}

val wrapIsSigLowest(Signal t)
{
    Signal s = nullptr;
    return makeResult(isSigLowest(t, s), resultField("signal", ptrValue(s)));
}

val wrapIsSigBinOp(Signal s)
{
    int    op = 0;
    Signal x  = nullptr;
    Signal y  = nullptr;
    return makeResult(isSigBinOp(s, &op, x, y), resultField("op", op),
                      resultField("x", ptrValue(x)), resultField("y", ptrValue(y)));
}

val wrapIsSigFFun(Signal s)
{
    Signal ff    = nullptr;
    Signal largs = nullptr;
    return makeResult(isSigFFun(s, ff, largs), resultField("function", ptrValue(ff)),
                      resultField("args", ptrValue(largs)));
}

val wrapIsSigFConst(Signal s)
{
    Signal type = nullptr;
    Signal name = nullptr;
    Signal file = nullptr;
    return makeResult(isSigFConst(s, type, name, file), resultField("type", ptrValue(type)),
                      resultField("name", ptrValue(name)), resultField("file", ptrValue(file)));
}

val wrapIsSigFVar(Signal s)
{
    Signal type = nullptr;
    Signal name = nullptr;
    Signal file = nullptr;
    return makeResult(isSigFVar(s, type, name, file), resultField("type", ptrValue(type)),
                      resultField("name", ptrValue(name)), resultField("file", ptrValue(file)));
}

val wrapIsProj(Signal s)
{
    int    i      = 0;
    Signal rgroup = nullptr;
    return makeResult(isProj(s, &i, rgroup), resultField("index", i),
                      resultField("signal", ptrValue(rgroup)));
}

val wrapIsRec(Signal s)
{
    Signal var  = nullptr;
    Signal body = nullptr;
    return makeResult(isRec(s, var, body), resultField("var", ptrValue(var)),
                      resultField("body", ptrValue(body)));
}

val wrapIsSigIntCast(Signal s)
{
    Signal x = nullptr;
    return makeResult(isSigIntCast(s, x), resultField("signal", ptrValue(x)));
}

val wrapIsSigFloatCast(Signal s)
{
    Signal x = nullptr;
    return makeResult(isSigFloatCast(s, x), resultField("signal", ptrValue(x)));
}

val wrapIsSigButton(Signal s)
{
    Signal lbl = nullptr;
    return makeResult(isSigButton(s, lbl), resultField("label", ptrValue(lbl)));
}

val wrapIsSigCheckbox(Signal s)
{
    Signal lbl = nullptr;
    return makeResult(isSigCheckbox(s, lbl), resultField("label", ptrValue(lbl)));
}

val wrapIsSigHSlider(Signal s)
{
    Signal lbl  = nullptr;
    Signal init = nullptr;
    Signal min  = nullptr;
    Signal max  = nullptr;
    Signal step = nullptr;
    return makeResult(isSigHSlider(s, lbl, init, min, max, step),
                      resultField("label", ptrValue(lbl)), resultField("init", ptrValue(init)),
                      resultField("min", ptrValue(min)), resultField("max", ptrValue(max)),
                      resultField("step", ptrValue(step)));
}

val wrapIsSigVSlider(Signal s)
{
    Signal lbl  = nullptr;
    Signal init = nullptr;
    Signal min  = nullptr;
    Signal max  = nullptr;
    Signal step = nullptr;
    return makeResult(isSigVSlider(s, lbl, init, min, max, step),
                      resultField("label", ptrValue(lbl)), resultField("init", ptrValue(init)),
                      resultField("min", ptrValue(min)), resultField("max", ptrValue(max)),
                      resultField("step", ptrValue(step)));
}

val wrapIsSigNumEntry(Signal s)
{
    Signal lbl  = nullptr;
    Signal init = nullptr;
    Signal min  = nullptr;
    Signal max  = nullptr;
    Signal step = nullptr;
    return makeResult(isSigNumEntry(s, lbl, init, min, max, step),
                      resultField("label", ptrValue(lbl)), resultField("init", ptrValue(init)),
                      resultField("min", ptrValue(min)), resultField("max", ptrValue(max)),
                      resultField("step", ptrValue(step)));
}

val wrapIsSigHBargraph(Signal s)
{
    Signal lbl = nullptr;
    Signal min = nullptr;
    Signal max = nullptr;
    Signal x   = nullptr;
    return makeResult(isSigHBargraph(s, lbl, min, max, x), resultField("label", ptrValue(lbl)),
                      resultField("min", ptrValue(min)), resultField("max", ptrValue(max)),
                      resultField("signal", ptrValue(x)));
}

val wrapIsSigVBargraph(Signal s)
{
    Signal lbl = nullptr;
    Signal min = nullptr;
    Signal max = nullptr;
    Signal x   = nullptr;
    return makeResult(isSigVBargraph(s, lbl, min, max, x), resultField("label", ptrValue(lbl)),
                      resultField("min", ptrValue(min)), resultField("max", ptrValue(max)),
                      resultField("signal", ptrValue(x)));
}

val wrapIsSigAttach(Signal s)
{
    Signal s0 = nullptr;
    Signal s1 = nullptr;
    return makeResult(isSigAttach(s, s0, s1), resultField("signal", ptrValue(s0)),
                      resultField("attached", ptrValue(s1)));
}

val wrapIsSigEnable(Signal s)
{
    Signal s0 = nullptr;
    Signal s1 = nullptr;
    return makeResult(isSigEnable(s, s0, s1), resultField("signal", ptrValue(s0)),
                      resultField("enable", ptrValue(s1)));
}

val wrapIsSigControl(Signal s)
{
    Signal s0 = nullptr;
    Signal s1 = nullptr;
    return makeResult(isSigControl(s, s0, s1), resultField("signal", ptrValue(s0)),
                      resultField("control", ptrValue(s1)));
}

val wrapIsSigSoundfile(Signal s)
{
    Signal lbl = nullptr;
    return makeResult(isSigSoundfile(s, lbl), resultField("label", ptrValue(lbl)));
}

val wrapIsSigSoundfileLength(Signal s)
{
    Signal sf   = nullptr;
    Signal part = nullptr;
    return makeResult(isSigSoundfileLength(s, sf, part), resultField("soundfile", ptrValue(sf)),
                      resultField("part", ptrValue(part)));
}

val wrapIsSigSoundfileRate(Signal s)
{
    Signal sf   = nullptr;
    Signal part = nullptr;
    return makeResult(isSigSoundfileRate(s, sf, part), resultField("soundfile", ptrValue(sf)),
                      resultField("part", ptrValue(part)));
}

val wrapIsSigSoundfileBuffer(Signal s)
{
    Signal sf   = nullptr;
    Signal chan = nullptr;
    Signal part = nullptr;
    Signal ridx = nullptr;
    return makeResult(isSigSoundfileBuffer(s, sf, chan, part, ridx),
                      resultField("soundfile", ptrValue(sf)), resultField("channel", ptrValue(chan)),
                      resultField("part", ptrValue(part)), resultField("index", ptrValue(ridx)));
}

struct SplitResult {
    bool ok;
    Box left;
    Box right;
};

SplitResult isBoxSplit_wrap(Box in)
{
    Box left = nullptr;
    Box right = nullptr;
    bool ok = isBoxSplit(in, left, right);
    return { ok, left, right };
}

Box getLeft(const SplitResult& s) { return s.left; }
Box getRight(const SplitResult& s) { return s.right; }
bool getOk(const SplitResult& s) { return s.ok; }

}  // namespace

EMSCRIPTEN_BINDINGS(CStruct)
{
    value_object<FaustWasm>("FaustWasm")
        .field("cfactory", &FaustWasm::cfactory)
        .field("data", &FaustWasm::data)
        .field("json", &FaustWasm::json);
    
    class_<SplitResult>("SplitResult")
        .constructor<>()
        .function("ok", &getOk)
        .function("left", &getLeft, allow_raw_pointers())
        .function("right", &getRight, allow_raw_pointers()); 
}

EMSCRIPTEN_BINDINGS(FaustModule)
{
    emscripten::class_<libFaustWasm>("libFaustWasm")
        .constructor<>()
        .function("version", &libFaustWasm::version, allow_raw_pointers())

        .function("createDSPFactory", &libFaustWasm::createDSPFactory, allow_raw_pointers())
        .function("createDSPFactoryFromSignals", &libFaustWasm::createDSPFactoryFromSignals,
                  allow_raw_pointers())
        .function("createDSPFactoryFromBoxes", &libFaustWasm::createDSPFactoryFromBoxes,
                  allow_raw_pointers())
        .function("deleteDSPFactory", &libFaustWasm::deleteDSPFactory, allow_raw_pointers())
        .function("deleteAllDSPFactories", &libFaustWasm::deleteAllDSPFactories)

        .function("expandDSP", &libFaustWasm::expandDSP, allow_raw_pointers())
        .function("generateAuxFiles", &libFaustWasm::generateAuxFiles, allow_raw_pointers())

        .function("cleanupAfterException", &libFaustWasm::cleanupAfterException)
        .function("getErrorAfterException", &libFaustWasm::getErrorAfterException,
                  allow_raw_pointers())

        .function("getInfos", &libFaustWasm::getInfos, allow_raw_pointers());

    register_vector<int>("vector<int>");
}

EMSCRIPTEN_BINDINGS(FaustBoxSignal)
{
    enum_<SType>("SType")
        .value("kSInt", kSInt)
        .value("kSReal", kSReal);

    enum_<SOperator>("SOperator")
        .value("kAdd", kAdd)
        .value("kSub", kSub)
        .value("kMul", kMul)
        .value("kDiv", kDiv)
        .value("kRem", kRem)
        .value("kLsh", kLsh)
        .value("kARsh", kARsh)
        .value("kLRsh", kLRsh)
        .value("kGT", kGT)
        .value("kLT", kLT)
        .value("kGE", kGE)
        .value("kLE", kLE)
        .value("kEQ", kEQ)
        .value("kNE", kNE)
        .value("kAND", kAND)
        .value("kOR", kOR)
        .value("kXOR", kXOR);

    
    class_<Interval>("Interval")
        .constructor<int>()             // matches Interval(int lsb)
        .property("fLo",  &Interval::fLo)
        .property("fHi",  &Interval::fHi)
        .property("fLSB", &Interval::fLSB);
    
    class_<CTree>("CTree");  // ensures CTree* is a known embind type

    register_vector<CTree*>("vector<CTree*>");
    register_vector<std::string>("vector<string>");
    register_vector<SType>("vector<SType>");

    function("prim0name", &prim0name, allow_raw_pointers());
    function("prim1name", &prim1name, allow_raw_pointers());
    function("prim2name", &prim2name, allow_raw_pointers());
    function("prim3name", &prim3name, allow_raw_pointers());
    function("prim4name", &prim4name, allow_raw_pointers());
    function("prim5name", &prim5name, allow_raw_pointers());

    function("ffname", &ffname, allow_raw_pointers());
    function("ffarity", &ffarity, allow_raw_pointers());

    function("createLibContext", &createLibContext);
    function("destroyLibContext", &destroyLibContext);

    function("printBox", &printBox, allow_raw_pointers());
    function("printSignal", &printSignal, allow_raw_pointers());

    function("extractName", &extractName, allow_raw_pointers());
    function("getDefNameProperty", &wrapGetDefNameProperty, allow_raw_pointers());

    function("isNil", select_overload<bool(Tree)>(&isNil), allow_raw_pointers());
    function("tree2str", select_overload<const char*(Box)>(&tree2str), allow_raw_pointers());
    function("tree2str", select_overload<const char*(Signal)>(&tree2str), allow_raw_pointers());
    function("tree2int", &tree2int, allow_raw_pointers());

    function("getUserData", select_overload<void*(Box)>(&getUserData), allow_raw_pointers());
    function("getUserData", select_overload<void*(Signal)>(&getUserData), allow_raw_pointers());

    function("boxInt", &boxInt, allow_raw_pointers());
    function("boxReal", &boxReal, allow_raw_pointers());
    function("boxWire", &boxWire, allow_raw_pointers());
    function("boxCut", &boxCut, allow_raw_pointers());
    function("boxSeq", &boxSeq, allow_raw_pointers());
    function("boxPar", &boxPar, allow_raw_pointers());
    function("boxPar3", &boxPar3, allow_raw_pointers());
    function("boxPar4", &boxPar4, allow_raw_pointers());
    function("boxPar5", &boxPar5, allow_raw_pointers());
    function("boxSplit", &boxSplit, allow_raw_pointers());
    function("boxMerge", &boxMerge, allow_raw_pointers());
    function("boxRec", &boxRec, allow_raw_pointers());
    function("boxRoute", &boxRoute, allow_raw_pointers());
    function("boxDelay", select_overload<Box(Box, Box)>(&boxDelay), allow_raw_pointers());
    function("boxDelay", select_overload<Box()>(&boxDelay), allow_raw_pointers());
    function("boxIntCast", select_overload<Box()>(&boxIntCast), allow_raw_pointers());
    function("boxIntCast", select_overload<Box(Box)>(&boxIntCast), allow_raw_pointers());
    function("boxFloatCast", select_overload<Box()>(&boxFloatCast), allow_raw_pointers());
    function("boxFloatCast", select_overload<Box(Box)>(&boxFloatCast), allow_raw_pointers());
    function("boxReadOnlyTable", select_overload<Box()>(&boxReadOnlyTable), allow_raw_pointers());
    function("boxReadOnlyTable", select_overload<Box(Box, Box, Box)>(&boxReadOnlyTable),
             allow_raw_pointers());
    function("boxWriteReadTable", select_overload<Box()>(&boxWriteReadTable),
             allow_raw_pointers());
    function("boxWriteReadTable", select_overload<Box(Box, Box, Box, Box, Box)>(&boxWriteReadTable),
             allow_raw_pointers());
    function("boxWaveform", &boxWaveform, allow_raw_pointers());
    function("boxSoundfile", select_overload<Box(const std::string&, Box)>(&boxSoundfile),
             allow_raw_pointers());
    function("boxSoundfile", select_overload<Box(const std::string&, Box, Box, Box)>(&boxSoundfile),
             allow_raw_pointers());
    function("boxSelect2", select_overload<Box()>(&boxSelect2), allow_raw_pointers());
    function("boxSelect2", select_overload<Box(Box, Box, Box)>(&boxSelect2), allow_raw_pointers());
    function("boxSelect3", select_overload<Box()>(&boxSelect3), allow_raw_pointers());
    function("boxSelect3", select_overload<Box(Box, Box, Box, Box)>(&boxSelect3),
             allow_raw_pointers());
    function("boxFFun", &boxFFun, allow_raw_pointers());
    function("boxFConst", &boxFConst, allow_raw_pointers());
    function("boxFVar", &boxFVar, allow_raw_pointers());
    function("boxBinOp", select_overload<Box(SOperator)>(&boxBinOp), allow_raw_pointers());
    function("boxBinOp", select_overload<Box(SOperator, Box, Box)>(&boxBinOp), allow_raw_pointers());
    function("boxAdd", select_overload<Box()>(&boxAdd), allow_raw_pointers());
    function("boxAdd", select_overload<Box(Box, Box)>(&boxAdd), allow_raw_pointers());
    function("boxSub", select_overload<Box()>(&boxSub), allow_raw_pointers());
    function("boxSub", select_overload<Box(Box, Box)>(&boxSub), allow_raw_pointers());
    function("boxMul", select_overload<Box()>(&boxMul), allow_raw_pointers());
    function("boxMul", select_overload<Box(Box, Box)>(&boxMul), allow_raw_pointers());
    function("boxDiv", select_overload<Box()>(&boxDiv), allow_raw_pointers());
    function("boxDiv", select_overload<Box(Box, Box)>(&boxDiv), allow_raw_pointers());
    function("boxRem", select_overload<Box()>(&boxRem), allow_raw_pointers());
    function("boxRem", select_overload<Box(Box, Box)>(&boxRem), allow_raw_pointers());
    function("boxLeftShift", select_overload<Box()>(&boxLeftShift), allow_raw_pointers());
    function("boxLeftShift", select_overload<Box(Box, Box)>(&boxLeftShift), allow_raw_pointers());
    function("boxLRightShift", select_overload<Box()>(&boxLRightShift), allow_raw_pointers());
    function("boxLRightShift", select_overload<Box(Box, Box)>(&boxLRightShift),
             allow_raw_pointers());
    function("boxARightShift", select_overload<Box()>(&boxARightShift), allow_raw_pointers());
    function("boxARightShift", select_overload<Box(Box, Box)>(&boxARightShift),
             allow_raw_pointers());
    function("boxGT", select_overload<Box()>(&boxGT), allow_raw_pointers());
    function("boxGT", select_overload<Box(Box, Box)>(&boxGT), allow_raw_pointers());
    function("boxLT", select_overload<Box()>(&boxLT), allow_raw_pointers());
    function("boxLT", select_overload<Box(Box, Box)>(&boxLT), allow_raw_pointers());
    function("boxGE", select_overload<Box()>(&boxGE), allow_raw_pointers());
    function("boxGE", select_overload<Box(Box, Box)>(&boxGE), allow_raw_pointers());
    function("boxLE", select_overload<Box()>(&boxLE), allow_raw_pointers());
    function("boxLE", select_overload<Box(Box, Box)>(&boxLE), allow_raw_pointers());
    function("boxEQ", select_overload<Box()>(&boxEQ), allow_raw_pointers());
    function("boxEQ", select_overload<Box(Box, Box)>(&boxEQ), allow_raw_pointers());
    function("boxNE", select_overload<Box()>(&boxNE), allow_raw_pointers());
    function("boxNE", select_overload<Box(Box, Box)>(&boxNE), allow_raw_pointers());
    function("boxAND", select_overload<Box()>(&boxAND), allow_raw_pointers());
    function("boxAND", select_overload<Box(Box, Box)>(&boxAND), allow_raw_pointers());
    function("boxOR", select_overload<Box()>(&boxOR), allow_raw_pointers());
    function("boxOR", select_overload<Box(Box, Box)>(&boxOR), allow_raw_pointers());
    function("boxXOR", select_overload<Box()>(&boxXOR), allow_raw_pointers());
    function("boxXOR", select_overload<Box(Box, Box)>(&boxXOR), allow_raw_pointers());

    function("boxAbs", select_overload<Box()>(&boxAbs), allow_raw_pointers());
    function("boxAbs", select_overload<Box(Box)>(&boxAbs), allow_raw_pointers());
    function("boxAcos", select_overload<Box()>(&boxAcos), allow_raw_pointers());
    function("boxAcos", select_overload<Box(Box)>(&boxAcos), allow_raw_pointers());
    function("boxTan", select_overload<Box()>(&boxTan), allow_raw_pointers());
    function("boxTan", select_overload<Box(Box)>(&boxTan), allow_raw_pointers());
    function("boxSqrt", select_overload<Box()>(&boxSqrt), allow_raw_pointers());
    function("boxSqrt", select_overload<Box(Box)>(&boxSqrt), allow_raw_pointers());
    function("boxSin", select_overload<Box()>(&boxSin), allow_raw_pointers());
    function("boxSin", select_overload<Box(Box)>(&boxSin), allow_raw_pointers());
    function("boxRint", select_overload<Box()>(&boxRint), allow_raw_pointers());
    function("boxRint", select_overload<Box(Box)>(&boxRint), allow_raw_pointers());
    function("boxRound", select_overload<Box()>(&boxRound), allow_raw_pointers());
    function("boxRound", select_overload<Box(Box)>(&boxRound), allow_raw_pointers());
    function("boxLog", select_overload<Box()>(&boxLog), allow_raw_pointers());
    function("boxLog", select_overload<Box(Box)>(&boxLog), allow_raw_pointers());
    function("boxLog10", select_overload<Box()>(&boxLog10), allow_raw_pointers());
    function("boxLog10", select_overload<Box(Box)>(&boxLog10), allow_raw_pointers());
    function("boxFloor", select_overload<Box()>(&boxFloor), allow_raw_pointers());
    function("boxFloor", select_overload<Box(Box)>(&boxFloor), allow_raw_pointers());
    function("boxExp", select_overload<Box()>(&boxExp), allow_raw_pointers());
    function("boxExp", select_overload<Box(Box)>(&boxExp), allow_raw_pointers());
    function("boxExp10", select_overload<Box()>(&boxExp10), allow_raw_pointers());
    function("boxExp10", select_overload<Box(Box)>(&boxExp10), allow_raw_pointers());
    function("boxCos", select_overload<Box()>(&boxCos), allow_raw_pointers());
    function("boxCos", select_overload<Box(Box)>(&boxCos), allow_raw_pointers());
    function("boxCeil", select_overload<Box()>(&boxCeil), allow_raw_pointers());
    function("boxCeil", select_overload<Box(Box)>(&boxCeil), allow_raw_pointers());
    function("boxAtan", select_overload<Box()>(&boxAtan), allow_raw_pointers());
    function("boxAtan", select_overload<Box(Box)>(&boxAtan), allow_raw_pointers());
    function("boxAsin", select_overload<Box()>(&boxAsin), allow_raw_pointers());
    function("boxAsin", select_overload<Box(Box)>(&boxAsin), allow_raw_pointers());

    function("boxRemainder", select_overload<Box()>(&boxRemainder), allow_raw_pointers());
    function("boxRemainder", select_overload<Box(Box, Box)>(&boxRemainder), allow_raw_pointers());
    function("boxPow", select_overload<Box()>(&boxPow), allow_raw_pointers());
    function("boxPow", select_overload<Box(Box, Box)>(&boxPow), allow_raw_pointers());
    function("boxMin", select_overload<Box()>(&boxMin), allow_raw_pointers());
    function("boxMin", select_overload<Box(Box, Box)>(&boxMin), allow_raw_pointers());
    function("boxMax", select_overload<Box()>(&boxMax), allow_raw_pointers());
    function("boxMax", select_overload<Box(Box, Box)>(&boxMax), allow_raw_pointers());
    function("boxFmod", select_overload<Box()>(&boxFmod), allow_raw_pointers());
    function("boxFmod", select_overload<Box(Box, Box)>(&boxFmod), allow_raw_pointers());
    function("boxAtan2", select_overload<Box()>(&boxAtan2), allow_raw_pointers());
    function("boxAtan2", select_overload<Box(Box, Box)>(&boxAtan2), allow_raw_pointers());

    function("boxButton", &boxButton, allow_raw_pointers());
    function("boxCheckbox", &boxCheckbox, allow_raw_pointers());
    function("boxVSlider", &boxVSlider, allow_raw_pointers());
    function("boxHSlider", &boxHSlider, allow_raw_pointers());
    function("boxNumEntry", &boxNumEntry, allow_raw_pointers());
    function("boxVBargraph", select_overload<Box(const std::string&, Box, Box)>(&boxVBargraph),
             allow_raw_pointers());
    function("boxVBargraph",
             select_overload<Box(const std::string&, Box, Box, Box)>(&boxVBargraph),
             allow_raw_pointers());
    function("boxHBargraph", select_overload<Box(const std::string&, Box, Box)>(&boxHBargraph),
             allow_raw_pointers());
    function("boxHBargraph",
             select_overload<Box(const std::string&, Box, Box, Box)>(&boxHBargraph),
             allow_raw_pointers());
    function("boxVGroup", &boxVGroup, allow_raw_pointers());
    function("boxHGroup", &boxHGroup, allow_raw_pointers());
    function("boxTGroup", &boxTGroup, allow_raw_pointers());
    function("boxAttach", select_overload<Box()>(&boxAttach), allow_raw_pointers());
    function("boxAttach", select_overload<Box(Box, Box)>(&boxAttach), allow_raw_pointers());
    function("boxPrim2", &boxPrim2, allow_raw_pointers());

    function("isBoxAbstr", select_overload<bool(Box)>(&isBoxAbstr), allow_raw_pointers());
    function("isBoxAppl", select_overload<bool(Box)>(&isBoxAppl), allow_raw_pointers());
    function("isBoxButton", select_overload<bool(Box)>(&isBoxButton), allow_raw_pointers());
    function("isBoxCase", select_overload<bool(Box)>(&isBoxCase), allow_raw_pointers());
    function("isBoxCheckbox", select_overload<bool(Box)>(&isBoxCheckbox), allow_raw_pointers());
    function("isBoxCut", select_overload<bool(Box)>(&isBoxCut), allow_raw_pointers());
    function("isBoxEnvironment", select_overload<bool(Box)>(&isBoxEnvironment),
             allow_raw_pointers());
    function("isBoxError", select_overload<bool(Box)>(&isBoxError), allow_raw_pointers());
    function("isBoxFConst", select_overload<bool(Box)>(&isBoxFConst), allow_raw_pointers());
    function("isBoxFFun", select_overload<bool(Box)>(&isBoxFFun), allow_raw_pointers());
    function("isBoxFVar", select_overload<bool(Box)>(&isBoxFVar), allow_raw_pointers());
    function("isBoxHBargraph", select_overload<bool(Box)>(&isBoxHBargraph), allow_raw_pointers());
    function("isBoxHGroup", select_overload<bool(Box)>(&isBoxHGroup), allow_raw_pointers());
    function("isBoxHSlider", select_overload<bool(Box)>(&isBoxHSlider), allow_raw_pointers());
    function("isBoxInt", &wrapIsBoxInt, allow_raw_pointers());
    function("isBoxNumEntry", select_overload<bool(Box)>(&isBoxNumEntry), allow_raw_pointers());
    function("isBoxPrim0", select_overload<bool(Box)>(&isBoxPrim0), allow_raw_pointers());
    function("isBoxPrim1", select_overload<bool(Box)>(&isBoxPrim1), allow_raw_pointers());
    function("isBoxPrim2", select_overload<bool(Box)>(&isBoxPrim2), allow_raw_pointers());
    function("isBoxPrim3", select_overload<bool(Box)>(&isBoxPrim3), allow_raw_pointers());
    function("isBoxPrim4", select_overload<bool(Box)>(&isBoxPrim4), allow_raw_pointers());
    function("isBoxPrim5", select_overload<bool(Box)>(&isBoxPrim5), allow_raw_pointers());
    function("isBoxSoundfile", select_overload<bool(Box)>(&isBoxSoundfile), allow_raw_pointers());
    function("isBoxSplit", &isBoxSplit_wrap, allow_raw_pointers());
    function("isBoxSymbolic", select_overload<bool(Box)>(&isBoxSymbolic), allow_raw_pointers());
    function("isBoxTGroup", select_overload<bool(Box)>(&isBoxTGroup), allow_raw_pointers());
    function("isBoxVBargraph", select_overload<bool(Box)>(&isBoxVBargraph), allow_raw_pointers());
    function("isBoxVGroup", select_overload<bool(Box)>(&isBoxVGroup), allow_raw_pointers());
    function("isBoxVSlider", select_overload<bool(Box)>(&isBoxVSlider), allow_raw_pointers());
    function("isBoxWaveform", select_overload<bool(Box)>(&isBoxWaveform), allow_raw_pointers());
    function("isBoxWire", select_overload<bool(Box)>(&isBoxWire), allow_raw_pointers());
    function("isBoxAccess", &wrapIsBoxAccess, allow_raw_pointers());
    function("isBoxComponent", &wrapIsBoxComponent, allow_raw_pointers());
    function("isBoxLibrary", &wrapIsBoxLibrary, allow_raw_pointers());
    function("isBoxMetadata", &wrapIsBoxMetadata, allow_raw_pointers());
    function("isBoxRoute", &wrapIsBoxRoute, allow_raw_pointers());
    function("isBoxWithLocalDef", &wrapIsBoxWithLocalDef, allow_raw_pointers());
    function("isBoxIdent", &wrapIsBoxIdent, allow_raw_pointers());
    function("isBoxInputs", &wrapIsBoxInputs, allow_raw_pointers());
    function("isBoxIPar", &wrapIsBoxIPar, allow_raw_pointers());
    function("isBoxIProd", &wrapIsBoxIProd, allow_raw_pointers());
    function("isBoxISeq", &wrapIsBoxISeq, allow_raw_pointers());
    function("isBoxISum", &wrapIsBoxISum, allow_raw_pointers());
    function("isBoxMerge", &wrapIsBoxMerge, allow_raw_pointers());
    function("isBoxOutputs", &wrapIsBoxOutputs, allow_raw_pointers());
    function("isBoxPar", &wrapIsBoxPar, allow_raw_pointers());
    function("isBoxRec", &wrapIsBoxRec, allow_raw_pointers());
    function("isBoxSeq", &wrapIsBoxSeq, allow_raw_pointers());
    function("isBoxReal", &wrapIsBoxReal, allow_raw_pointers());
    function("isBoxSlot", &wrapIsBoxSlot, allow_raw_pointers());

    function("DSPToBoxes", &wrapDSPToBoxes, allow_raw_pointers());
    function("getBoxType", &wrapGetBoxType, allow_raw_pointers());
    function("boxesToSignals", &wrapBoxesToSignals, allow_raw_pointers());
    function("boxesToSignals2", &wrapBoxesToSignals2, allow_raw_pointers());
    function("createSourceFromBoxes", &wrapCreateSourceFromBoxes, allow_raw_pointers());

    function("getSigInterval", &getSigInterval, allow_raw_pointers());
    function("setSigInterval", &setSigInterval, allow_raw_pointers());
    function("xtendedArity", &xtendedArity, allow_raw_pointers());
    function("xtendedName", &xtendedName, allow_raw_pointers());

    function("isSigInt", &wrapIsSigInt, allow_raw_pointers());
    function("isSigInt64", &wrapIsSigInt64, allow_raw_pointers());
    function("isSigReal", &wrapIsSigReal, allow_raw_pointers());
    function("isSigInput", &wrapIsSigInput, allow_raw_pointers());
    function("isSigOutput", &wrapIsSigOutput, allow_raw_pointers());
    function("isSigDelay1", &wrapIsSigDelay1, allow_raw_pointers());
    function("isSigDelay", &wrapIsSigDelay, allow_raw_pointers());
    function("isSigPrefix", &wrapIsSigPrefix, allow_raw_pointers());
    function("isSigRDTbl", &wrapIsSigRDTbl, allow_raw_pointers());
    function("isSigWRTbl", &wrapIsSigWRTbl, allow_raw_pointers());
    function("isSigGen", &wrapIsSigGen, allow_raw_pointers());
    function("isSigDocConstantTbl", &wrapIsSigDocConstantTbl, allow_raw_pointers());
    function("isSigDocWriteTbl", &wrapIsSigDocWriteTbl, allow_raw_pointers());
    function("isSigDocAccessTbl", &wrapIsSigDocAccessTbl, allow_raw_pointers());
    function("isSigSelect2", &wrapIsSigSelect2, allow_raw_pointers());
    function("isSigAssertBounds", &wrapIsSigAssertBounds, allow_raw_pointers());
    function("isSigHighest", &wrapIsSigHighest, allow_raw_pointers());
    function("isSigLowest", &wrapIsSigLowest, allow_raw_pointers());
    function("isSigBinOp", &wrapIsSigBinOp, allow_raw_pointers());
    function("isSigFFun", &wrapIsSigFFun, allow_raw_pointers());
    function("isSigFConst", &wrapIsSigFConst, allow_raw_pointers());
    function("isSigFVar", &wrapIsSigFVar, allow_raw_pointers());
    function("isProj", &wrapIsProj, allow_raw_pointers());
    function("isRec", &wrapIsRec, allow_raw_pointers());
    function("isSigIntCast", &wrapIsSigIntCast, allow_raw_pointers());
    function("isSigFloatCast", &wrapIsSigFloatCast, allow_raw_pointers());
    function("isSigButton", &wrapIsSigButton, allow_raw_pointers());
    function("isSigCheckbox", &wrapIsSigCheckbox, allow_raw_pointers());
    function("isSigWaveform", &isSigWaveform, allow_raw_pointers());
    function("isSigHSlider", &wrapIsSigHSlider, allow_raw_pointers());
    function("isSigVSlider", &wrapIsSigVSlider, allow_raw_pointers());
    function("isSigNumEntry", &wrapIsSigNumEntry, allow_raw_pointers());
    function("isSigHBargraph", &wrapIsSigHBargraph, allow_raw_pointers());
    function("isSigVBargraph", &wrapIsSigVBargraph, allow_raw_pointers());
    function("isSigAttach", &wrapIsSigAttach, allow_raw_pointers());
    function("isSigEnable", &wrapIsSigEnable, allow_raw_pointers());
    function("isSigControl", &wrapIsSigControl, allow_raw_pointers());
    function("isSigSoundfile", &wrapIsSigSoundfile, allow_raw_pointers());
    function("isSigSoundfileLength", &wrapIsSigSoundfileLength, allow_raw_pointers());
    function("isSigSoundfileRate", &wrapIsSigSoundfileRate, allow_raw_pointers());
    function("isSigSoundfileBuffer", &wrapIsSigSoundfileBuffer, allow_raw_pointers());

    function("sigInt", &sigInt, allow_raw_pointers());
    function("sigInt64", &sigInt64, allow_raw_pointers());
    function("sigReal", &sigReal, allow_raw_pointers());
    function("sigInput", &sigInput, allow_raw_pointers());
    function("sigDelay", &sigDelay, allow_raw_pointers());
    function("sigDelay1", &sigDelay1, allow_raw_pointers());
    function("sigIntCast", &sigIntCast, allow_raw_pointers());
    function("sigFloatCast", &sigFloatCast, allow_raw_pointers());
    function("sigReadOnlyTable", &sigReadOnlyTable, allow_raw_pointers());
    function("sigWriteReadTable", &sigWriteReadTable, allow_raw_pointers());
    function("sigWaveform", &sigWaveform, allow_raw_pointers());
    function("sigSoundfile", &sigSoundfile, allow_raw_pointers());
    function("sigSoundfileLength", &sigSoundfileLength, allow_raw_pointers());
    function("sigSoundfileRate", &sigSoundfileRate, allow_raw_pointers());
    function("sigSoundfileBuffer", &sigSoundfileBuffer, allow_raw_pointers());
    function("sigSelect2", &sigSelect2, allow_raw_pointers());
    function("sigSelect3", &sigSelect3, allow_raw_pointers());
    function("sigFFun", &sigFFun, allow_raw_pointers());
    function("sigFConst", &sigFConst, allow_raw_pointers());
    function("sigFVar", &sigFVar, allow_raw_pointers());
    function("sigBinOp", &sigBinOp, allow_raw_pointers());
    function("sigAdd", &sigAdd, allow_raw_pointers());
    function("sigSub", &sigSub, allow_raw_pointers());
    function("sigMul", &sigMul, allow_raw_pointers());
    function("sigDiv", &sigDiv, allow_raw_pointers());
    function("sigRem", &sigRem, allow_raw_pointers());
    function("sigLeftShift", &sigLeftShift, allow_raw_pointers());
    function("sigLRightShift", &sigLRightShift, allow_raw_pointers());
    function("sigARightShift", &sigARightShift, allow_raw_pointers());
    function("sigGT", &sigGT, allow_raw_pointers());
    function("sigLT", &sigLT, allow_raw_pointers());
    function("sigGE", &sigGE, allow_raw_pointers());
    function("sigLE", &sigLE, allow_raw_pointers());
    function("sigEQ", &sigEQ, allow_raw_pointers());
    function("sigNE", &sigNE, allow_raw_pointers());
    function("sigAND", &sigAND, allow_raw_pointers());
    function("sigOR", &sigOR, allow_raw_pointers());
    function("sigXOR", &sigXOR, allow_raw_pointers());
    function("sigAbs", &sigAbs, allow_raw_pointers());
    function("sigAcos", &sigAcos, allow_raw_pointers());
    function("sigTan", &sigTan, allow_raw_pointers());
    function("sigSqrt", &sigSqrt, allow_raw_pointers());
    function("sigSin", &sigSin, allow_raw_pointers());
    function("sigRint", &sigRint, allow_raw_pointers());
    function("sigLog", &sigLog, allow_raw_pointers());
    function("sigLog10", &sigLog10, allow_raw_pointers());
    function("sigFloor", &sigFloor, allow_raw_pointers());
    function("sigExp", &sigExp, allow_raw_pointers());
    function("sigExp10", &sigExp10, allow_raw_pointers());
    function("sigCos", &sigCos, allow_raw_pointers());
    function("sigCeil", &sigCeil, allow_raw_pointers());
    function("sigAtan", &sigAtan, allow_raw_pointers());
    function("sigAsin", &sigAsin, allow_raw_pointers());
    function("sigRemainder", &sigRemainder, allow_raw_pointers());
    function("sigPow", &sigPow, allow_raw_pointers());
    function("sigMin", &sigMin, allow_raw_pointers());
    function("sigMax", &sigMax, allow_raw_pointers());
    function("sigFmod", &sigFmod, allow_raw_pointers());
    function("sigAtan2", &sigAtan2, allow_raw_pointers());
    function("sigSelf", &sigSelf, allow_raw_pointers());
    function("sigRecursion", &sigRecursion, allow_raw_pointers());
    function("sigSelfN", &sigSelfN, allow_raw_pointers());
    function("sigRecursionN", &sigRecursionN, allow_raw_pointers());
    function("sigButton", &sigButton, allow_raw_pointers());
    function("sigCheckbox", &sigCheckbox, allow_raw_pointers());
    function("sigVSlider", &sigVSlider, allow_raw_pointers());
    function("sigHSlider", &sigHSlider, allow_raw_pointers());
    function("sigNumEntry", &sigNumEntry, allow_raw_pointers());
    function("sigVBargraph", &sigVBargraph, allow_raw_pointers());
    function("sigHBargraph", &sigHBargraph, allow_raw_pointers());
    function("sigAttach", &sigAttach, allow_raw_pointers());
    function("simplifyToNormalForm", &simplifyToNormalForm, allow_raw_pointers());
    function("simplifyToNormalForm2", &simplifyToNormalForm2, allow_raw_pointers());
    function("createSourceFromSignals", &wrapCreateSourceFromSignals, allow_raw_pointers());
}
