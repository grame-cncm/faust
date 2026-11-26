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

#include <cmath>

#include "xtendedCodegen.hh"
#include "Text.hh"
#include "code_container.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

int xtendedCodegen::zeroLiteral(ValueInst* v)
{
    long double x = 1;
    if (FloatNumInst* f = dynamic_cast<FloatNumInst*>(v)) {
        x = f->fNum;
    } else if (DoubleNumInst* d = dynamic_cast<DoubleNumInst*>(v)) {
        x = d->fNum;
    } else if (QuadNumInst* q = dynamic_cast<QuadNumInst*>(v)) {
        x = q->fNum;
    }
    return (x == 0) ? (std::signbit(x) ? -1 : 1) : 0;
}

bool xtendedCodegen::fNeedMinMaxHelpers = false;
bool xtendedCodegen::fNeedFmodHelpers   = false;
bool xtendedCodegen::fNeedMemoHelpers   = false;

bool xtendedCodegen::fNeedInlineMath[xtendedCodegen::kInlineMathCount] = {};

// the name of a version carries the function, the domain and the precision
static const char* kInlineMathNames[xtendedCodegen::kInlineMathCount] = {"faustsin17f", "fausttanhf"};

// the interval within [-b, b], by its permanent bounds : a bound that holds over the horizon of the
// analysis only is read as absent
static bool heldWithin(const interval& i, double b)
{
    return !i.isEmpty() && !i.loMoves() && !i.hiMoves() && (-b <= i.lo()) && (i.hi() <= b);
}

int xtendedCodegen::inlineMathVersion(const std::string& fun, ConstTypes types)
{
    const std::string& lang = gGlobal->gOutputLang;
    if (!gGlobal->gInlineMath || (gGlobal->gFloatSize != 1) || ((lang != "cpp") && (lang != "c") && (lang != "ocpp"))) {
        return -1;
    }
    // a function that -fm replaces is the choice of the user
    if (gGlobal->getMathFunction(fun + "f") != fun + "f") {
        return -1;
    }
    if (fun == "sin") {
        const interval i = types[0]->getInterval();
        return heldWithin(i, 0x1p17) ? kInlineSin17 : -1;
    }
    if (fun == "tanh") {
        return kInlineTanh;
    }
    return -1;
}

std::string xtendedCodegen::inlineMathFunction(const std::string& fun, ConstTypes types)
{
    const int v = inlineMathVersion(fun, types);
    if (v < 0) {
        return "";
    }
    fNeedInlineMath[v] = true;
    return kInlineMathNames[v];
}

ValueInst* xtendedCodegen::generateInlineMath(CodeContainer* container, const std::string& fun, const Values& args,
                                              ConstTypes types)
{
    const std::string name = inlineMathFunction(fun, types);
    if (name.empty()) {
        return nullptr;
    }
    Values cargs;
    cargs.push_back(promote2real(types[0]->nature(), *args.begin()));
    std::vector<Typed::VarType> atypes = {itfloat()};
    return container->pushFunction(name, itfloat(), atypes, cargs);
}

// The texts are C, valid in C++ : the bits of a float are read and written by memcpy, and the
// constants are decimal (a hexadecimal one is not C++ before C++17), with the nine digits that
// give back the float. Every multiply-add of a text is written fmaf : nothing is left for the C++
// compiler to contract or not, and the text gives the same bits on every machine, vectorized or
// not. The preprocessor compiles it where fmaf is an instruction ; any other target keeps the call
// of the libm : a text is compiled only where it was measured
static const char* kInlineTarget =
    "defined(__GNUC__) && !defined(__INTEL_COMPILER) && (defined(__aarch64__) || (defined(__x86_64__) && defined(__FMA__)))";

// sin : n the multiple of pi nearest to a = |x|, r = a - n * pi in three parts, an odd
// polynomial of degree 9 on [-pi/2, pi/2]. The polynomial is computed on q, r without its third part
// of pi, which joins at the last multiply-add : the same bits, and the chain of the result is one
// multiply-add shorter. The sign is taken from r, not from the result, so that it is ready before
// the polynomial, and the parity of n from the bits of n + 2^23 : no float is converted to an
// integer, so that no argument, even far from the domain or a NaN, meets an undefined conversion.
// Conforms for |x| <= 2^17
static const char* kSin = R"(static inline float $0(float x)
{
    const float a = fabsf(x);
    const float n = rintf(a * 0.318309873f);
    const float q = fmaf(-n, -8.74227766e-08f, fmaf(-n, 3.14159274f, a));
    const float r = fmaf(-n, -3.43024902e-15f, q);
    /* the polynomial on the argument less its third part of pi, which changes it by less than 2^-32 */
    const float q2 = q * q;
    float p = fmaf(2.61059586e-06f, q2, -0.000198119946f);
    p = fmaf(p, q2, 0.0083331028f);
    p = fmaf(p, q2, -0.166666612f);
    const float y0 = fmaf(p, q2 * q, r);
    /* next to pi/2 the polynomial may round above 1 : the magnitude is held to 1 (a NaN stays) */
    const float ya = fabsf(y0);
    const float yc = 1.0f < ya ? 1.0f : ya;
    /* the parity of n : the low bit of n + 2^23, a sum that is exact for n < 2^23 ; no conversion to an integer */
    const float np = n + 8388608.0f;
    uint32_t bx, br, bn;
    float t;
    memcpy(&bx, &x, 4);
    memcpy(&br, &r, 4);
    memcpy(&bn, &np, 4);
    /* the sign of the result : that of r, which the polynomial keeps, the parity of n and the sign of x */
    br ^= (bn << 31) ^ (bx & 0x80000000u);
    memcpy(&t, &br, 4);
    return copysignf(yc, t);
}
)";

// tanh : two regimes on a = |x|, chosen by a mask. Below 0.55, an odd polynomial of degree
// 11 ; above, 1 - 2 u / (1 + u) with u = e^(-2 a), the argument of the exponential held in
// [-24, 0], 2^n written in the bits of the exponent. The exponential is written for its latency :
// n is computed beside z, ln 2 is in one part, and the polynomial is in three pairs. The exponent
// is read in the bits of n + 127 + 2^23 : no float is converted to an integer, since the hold of a
// may be compiled as a minimum that lets a signalling NaN through. Conforms for every float
static const char* kTanh = R"(static inline float $0(float x)
{
    const float a = fabsf(x);
    const float a2 = a * a;
    float p = fmaf(a2, -0.00627423823f, 0.021071678f);
    p = fmaf(p, a2, -0.0538523085f);
    p = fmaf(p, a2, 0.13332586f);
    p = fmaf(p, a2, -0.333333164f);
    const float ys = fmaf(p, a2 * a, a);
    /* a held to 12, where tanh is 1 ; z = -2 a. Whatever the hold makes of a NaN, x is given back at the end */
    const float ac = a < 12.0f ? a : 12.0f;
    const float z = -2.0f * ac;
    /* e^z : z = n ln 2 + r, e^r by its Taylor polynomial of degree 7, 2^n by the bits of the exponent */
    const float n = rintf(ac * -2.88539004f);
    /* ln 2 in one part : what it leaves, less than 2^-23 of e^z, is less than 2^-4 ulp of the result */
    const float r = fmaf(-n, 0.693147182f, z);
    const float r2 = r * r;
    const float e76 = fmaf(r, 0.000198412701f, 0.00138888892f);
    const float e54 = fmaf(r, 0.00833333377f, 0.0416666679f);
    const float e32 = fmaf(r, 0.166666672f, 0.5f);
    const float eh = fmaf(e76, r2, e54);
    const float el = fmaf(e32, r2, r + 1.0f);
    const float e = fmaf(eh, r2 * r2, el);
    /* 2^n : n + 127 is in the low bits of n + 127 + 2^23, a sum that is exact ; no conversion to an integer */
    const float nb = n + 8388735.0f;
    uint32_t be;
    float w, y;
    memcpy(&be, &nb, 4);
    be <<= 23;
    memcpy(&w, &be, 4);
    const float u = e * w;
    const float yl = 1.0f - 2.0f * u / (1.0f + u);
    /* the two regimes, the sign of x, then the NaN, selected by masks of bits */
    const uint32_t ms = -(uint32_t)(a < 0.55f), mn = -(uint32_t)(x != x);
    uint32_t bs, bl, bx, b;
    memcpy(&bs, &ys, 4);
    memcpy(&bl, &yl, 4);
    memcpy(&bx, &x, 4);
    b = ((bs & ms) | (bl & ~ms)) | (bx & 0x80000000u);
    b = (bx & mn) | (b & ~mn);
    memcpy(&y, &b, 4);
    return y;
}
)";

// a version : its guard, which lets an architecture file give its own definition, as FAUST_FMOD ;
// what it is ; its text ; the call of the libm, kept where the text is not compiled
static void printInlineVersion(std::ostream& out, const char* name, const char* guard, const char* what,
                               const char* text, const char* libm)
{
    out << "#ifndef " << guard << "\n";
    out << "#define " << guard << "\n";
    out << "#include <math.h>\n";
    out << "#include <stdint.h>\n";
    out << "#include <string.h>\n";
    out << what;
    out << "#if " << kInlineTarget << "\n";
    out << subst(text, name);
    out << "#else\n";
    out << "static inline float " << name << "(float x) { return " << libm << "(x); }\n";
    out << "#endif\n";
    out << "#endif\n";
}

void xtendedCodegen::printInlineMath(std::ostream& out)
{
    // where the text is compiled, said in the emitted code
    static const char* where =
        "   Without a branch, defined for every float ; the same bits on every machine. Compiled where a fused\n"
        "   multiply-add is an instruction ; any other target keeps the call.";
    if (fNeedInlineMath[kInlineSin17]) {
        fNeedInlineMath[kInlineSin17] = false;
        // the coefficients of the polynomial of the sine and its parts of pi are those of a published
        // library : the text names it, the holder of its rights and its licence
        const std::string what =
            std::string("/* The sine of a float in [-131072, 131072], within 2 ulps, without a call of the libm.\n") + where +
            " The coefficients of the\n"
            "   polynomial and the parts of pi are those of the AdvSIMD sinf of Arm Optimized Routines,\n"
            "   Copyright (c) 2019-2026, Arm Limited, SPDX-License-Identifier: MIT OR Apache-2.0 WITH LLVM-exception. */\n";
        printInlineVersion(out, kInlineMathNames[kInlineSin17], "FAUST_SIN17F", what.c_str(), kSin, "sinf");
    }
    if (fNeedInlineMath[kInlineTanh]) {
        fNeedInlineMath[kInlineTanh] = false;
        const std::string what =
            std::string("/* The hyperbolic tangent of a float, within 2 ulps, without a call of the libm.\n") + where + " */\n";
        printInlineVersion(out, kInlineMathNames[kInlineTanh], "FAUST_TANHF", what.c_str(), kTanh, "tanhf");
    }
}

void xtendedCodegen::printMinMaxHelpers(std::ostream& out, bool byRef)
{
    printInlineMath(out);
    if (fNeedMemoHelpers) {
        fNeedMemoHelpers = false;
        out << "#ifndef FAUST_MEMO\n";
        out << "#define FAUST_MEMO\n";
        out << "#include <string.h>\n";
        out << "/* An argument changed since the previous call : compared bit for bit, so that -0 and +0\n"
               "   differ and a NaN is never the same. */\n";
        const char* types[]    = {"float", "double", "long double"};
        const char* suffixes[] = {"f", "", "l"};
        for (int i = 0; i < 3; i++) {
            const string t = types[i], x = suffixes[i];
            out << "static inline int faustdiff" << x << "(" << t << " a, " << t << " b) { return memcmp(&a, &b, sizeof(a)) != 0; }\n";
        }
        out << "static inline int faustdiffi(int a, int b) { return a != b; }\n";
        out << "#endif\n";
    }
    if (fNeedFmodHelpers) {
        fNeedFmodHelpers = false;
        out << "#ifndef FAUST_FMOD\n";
        out << "#define FAUST_FMOD\n";
        out << "#include <math.h>\n";
        out << "/* The real fmod of Faust : fmod, without the call when a is in [0, 2 * w) : a itself below w,\n"
               "   a - w from w on, exact (Sterbenz : w <= a <= 2 * w). Every other operand, NaN and\n"
               "   infinities included, goes to fmod. */\n";
        const char* types[]    = {"float", "double", "long double"};
        const char* suffixes[] = {"f", "", "l"};
        for (int i = 0; i < 3; i++) {
            const string t = types[i], x = suffixes[i];
            out << "static inline " << t << " faustfmod" << x << "(" << t << " a, " << t << " w) { if (a >= 0) { if (a < w) return a; if (a < 2 * w) return a - w; } return fmod" << x << "(a, w); }\n";
        }
        out << "#endif\n";
    }
    if (!fNeedMinMaxHelpers) {
        return;
    }
    fNeedMinMaxHelpers = false;
    out << "#ifndef FAUST_MINMAX\n";
    out << "#define FAUST_MINMAX\n";
    out << "#include <math.h>\n";
    out << "/* The real max and min of Faust : maximumNumber and minimumNumber of IEEE 754-2019 (a NaN\n"
           "   operand gives the other one, -0 < +0). The compiler writes the cheapest of these forms\n"
           "   that has this value, from what the interval of the program proves :\n"
           "   faustmax, the comparison, where a tie of zeros gives its first operand ; faustmaxk, the\n"
           "   first operand not NaN and no tie of zeros, in the form each compiler compiles best ;\n"
           "   faustmaxn, any operands. On arm64, fmax and fmin are fmaxnm and fminnm, this value\n"
           "   for any operands in one instruction : every form is written with them. */\n";
    const char* types[]    = {"float", "double", "long double"};
    const char* suffixes[] = {"f", "", "l"};
    for (int i = 0; i < 3; i++) {
        const string t = types[i], x = suffixes[i];
        const string sig = "(" + t + " a, " + t + " b)";
        const string ref = "static inline const " + t + "& ";
        const string rsig = "(const " + t + "& a, const " + t + "& b)";
        // arm64 : the comparison is fcmp and fcsel, where fmax is one fmaxnm (virtualAnalog in
        // cpp, single, clang : 12 % faster)
        out << "#if defined(__aarch64__)\n";
        for (const char* k : {"", "k", "n"}) {
            out << "static inline " << t << " faustmax" << k << x << sig << " { return fmax" << x << "(a, b); }\n";
            out << "static inline " << t << " faustmin" << k << x << sig << " { return fmin" << x << "(a, b); }\n";
        }
        out << "#elif defined(__clang__)\n";
        if (byRef) {
            // cpp : a reference, as std::max (clang : dx7 in cpp 321 ns per sample against 350)
            for (const char* k : {"", "k"}) {
                out << ref << "faustmax" << k << x << rsig << " { return (a < b) ? b : a; }\n";
                out << ref << "faustmin" << k << x << rsig << " { return (b < a) ? b : a; }\n";
            }
        } else {
            // ocpp and C : fmax for the free form (clang : vocoder in ocpp, 10 % faster)
            out << "static inline " << t << " faustmax" << x << sig << " { return (a < b) ? b : a; }\n";
            out << "static inline " << t << " faustmin" << x << sig << " { return (b < a) ? b : a; }\n";
            out << "static inline " << t << " faustmaxk" << x << sig << " { return fmax" << x << "(a, b); }\n";
            out << "static inline " << t << " faustmink" << x << sig << " { return fmin" << x << "(a, b); }\n";
        }
        out << "#else\n";
        // the other compilers : a value (g++ : englishBell in cpp, 54 ns per sample against 94
        // with the reference of std::max)
        for (const char* k : {"", "k"}) {
            out << "static inline " << t << " faustmax" << k << x << sig << " { return (a < b) ? b : a; }\n";
            out << "static inline " << t << " faustmin" << k << x << sig << " { return (b < a) ? b : a; }\n";
        }
        out << "#endif\n";
        out << "#if !defined(__aarch64__)\n";
        out << "static inline " << t << " faustmaxn" << x << sig
            << " { return (a < b || a != a) ? b : (b < a) ? a : ((a == b && signbit(a)) ? b : a); }\n";
        out << "static inline " << t << " faustminn" << x << sig
            << " { return (b < a || a != a) ? b : (a < b) ? a : ((a == b && !signbit(a)) ? b : a); }\n";
        out << "#endif\n";
    }
    out << "#endif\n";
}

string xtendedCodegen::minMaxHelper(bool isMax, MinMaxForm form)
{
    string base = isMax ? "faustmax" : "faustmin";
    if (form == kMinMaxFree) {
        base += "k";
    } else if (form == kMinMaxFull) {
        base += "n";
    }
    // the libm suffix : f for float, none for double, l for quad
    return base + ((gGlobal->gFloatSize == 1) ? "f" : (gGlobal->gFloatSize == 3) ? "l" : "");
}

ValueInst* xtendedCodegen::generateFun(CodeContainer* container, const string& fun_name,
                                const Values& args, ::Type result, ConstTypes types)
{
    Typed::VarType         rtype = convert2FIRType(result->nature());
    vector<Typed::VarType> atypes;
    for (size_t i = 0; i < types.size(); i++) {
        atypes.push_back(convert2FIRType(types[i]->nature()));
    }
    return container->pushFunction(fun_name, rtype, atypes, args);
}

ValueInst* xtendedCodegen::generateMinMaxNumber(CodeContainer* container, const string& fun_name,
                                                const Values& args, ::Type result,
                                                ConstTypes types)
{
    ValueInst* r = generateFun(container, fun_name, args, result, types);
    if (result->nature() != kReal) {
        return r;
    }
    // an operand may be NaN when it is real and its interval is empty or may be invalid :
    // the rule of the intervals under minMaxNumber() (validity.hh, minMaxInvalid)
    auto mayBeNaN = [&](size_t i) {
        const interval itv = types[i]->getInterval();
        return types[i]->nature() == kReal && (itv.isEmpty() || itv.mayBeInvalid());
    };
    BasicCloneVisitor cloner;
    ValueInst*        a = *args.begin();
    ValueInst*        b = *std::next(args.begin(), 1);
    // b NaN : a ; then a NaN : b (NaN when both are)
    if (mayBeNaN(1)) {
        r = IB::genSelect2Inst(IB::genEqual(b->clone(&cloner), b->clone(&cloner)), r,
                               promote2real(types[0]->nature(), a->clone(&cloner)));
    }
    if (mayBeNaN(0)) {
        r = IB::genSelect2Inst(IB::genEqual(a->clone(&cloner), a->clone(&cloner)), r,
                               promote2real(types[1]->nature(), b->clone(&cloner)));
    }
    return r;
}
