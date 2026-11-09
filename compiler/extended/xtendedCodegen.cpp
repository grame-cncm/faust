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

void xtendedCodegen::printMinMaxHelpers(std::ostream& out, bool byRef)
{
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
           "   faustmaxn, any operands. */\n";
    const char* types[]    = {"float", "double", "long double"};
    const char* suffixes[] = {"f", "", "l"};
    for (int i = 0; i < 3; i++) {
        const string t = types[i], x = suffixes[i];
        const string sig = "(" + t + " a, " + t + " b)";
        const string ref = "static inline const " + t + "& ";
        const string rsig = "(const " + t + "& a, const " + t + "& b)";
        out << "#if defined(__clang__)\n";
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
        out << "static inline " << t << " faustmaxn" << x << sig
            << " { return (a < b || a != a) ? b : (b < a) ? a : ((a == b && signbit(a)) ? b : a); }\n";
        out << "static inline " << t << " faustminn" << x << sig
            << " { return (b < a || a != a) ? b : (a < b) ? a : ((a == b && !signbit(a)) ? b : a); }\n";
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
