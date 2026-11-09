/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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

#ifndef __XTENDED_CODEGEN__
#define __XTENDED_CODEGEN__

#include <cmath>
#include <sstream>
#include <string>
#include <vector>

#include "exception.hh"
#include "floats.hh"
#include "instructions.hh"
#include "klass.hh"
#include "lateq.hh"
#include "ppsig.hh"
#include "xtended.hh"

class CodeContainer;

/*
 Code generation layer of the math primitives: the concrete primitives of the
 compiler (the extended/...prim.hh files) derive from this class, which extends the
 signal-level interface xtended (signals/xtended.hh) with the code generation
 methods of the FIR, old CPP and documentation backends.
 */

class xtendedCodegen : public xtended {
   public:
    using xtended::xtended;

    // The real max and min of Faust are maximumNumber and minimumNumber of IEEE 754-2019 : a
    // NaN operand gives the other one (NaN when both are), and -0 < +0 ; the operation is
    // commutative (LES-NAN-DU-MAX-ET-DU-MIN). The C and C++ generators write each one in the
    // cheapest form that has this value, from what the interval of the program proves :
    //  - kMinMaxFree : the first operand proven not NaN, no tie between +0 and -0 possible :
    //    fmax (fmin) and the comparison (a < b) ? b : a ((b < a) ? b : a) have this value,
    //    each C++ compiler takes the form it compiles best ;
    //  - kMinMaxCompare : a tie of zeros possible, the literal zero that wins first (+0 of a
    //    max, -0 of a min) or the one that loses second : the comparison has this value ;
    //  - kMinMaxFull : otherwise, the comparison with the NaN test and the sign of the zeros.
    // swap tells to write the operands in the other order, a proven operand first. zero0 and
    // zero1 : +1 for a literal +0, -1 for a literal -0, 0 for anything else
    enum MinMaxForm { kMinMaxFree, kMinMaxCompare, kMinMaxFull };

    // the value : the constant folding and the interpreter of the signals
    static double maxNumber(double a, double b)
    {
        if (std::isnan(a)) return b;
        if (std::isnan(b)) return a;
        if (a == b) return std::signbit(a) ? b : a;
        return (a < b) ? b : a;
    }
    static double minNumber(double a, double b)
    {
        if (std::isnan(a)) return b;
        if (std::isnan(b)) return a;
        if (a == b) return std::signbit(a) ? a : b;
        return (b < a) ? b : a;
    }

    static MinMaxForm minMaxForm(bool isMax, ConstTypes types, int zero0, int zero1, bool& swap)
    {
        const interval a  = types[0]->getInterval();
        const interval b  = types[1]->getInterval();
        const bool     na = a.isEmpty() || a.mayBeInvalid();
        const bool     nb = b.isEmpty() || b.mayBeInvalid();
        swap              = na && !nb;
        if (na && nb) {
            return kMinMaxFull;
        }
        const bool tie = (a.isEmpty() || a.hasZero()) && (b.isEmpty() || b.hasZero());
        if (!tie) {
            return kMinMaxFree;
        }
        // the comparison gives its first operand on a tie of zeros : it is exact when that
        // operand is the result, the literal zero that wins (+0 of a max, -0 of a min) first,
        // or the literal zero that loses second (max(x, -0) = min(x, +0) = x for x = +-0)
        const int  wins   = isMax ? 1 : -1;
        const int  first  = swap ? zero1 : zero0;
        const int  second = swap ? zero0 : zero1;
        const bool nfirst = swap ? nb : na;  // false : first is not NaN
        const bool nsec   = swap ? na : nb;
        if (first == wins || (second == -wins && !nfirst)) {
            return kMinMaxCompare;
        }
        if (second == wins || (first == -wins && !nsec)) {
            // the other order : the winning literal first, or the losing one second
            swap = !swap;
            return kMinMaxCompare;
        }
        return kMinMaxFull;
    }

    // +1 for the literal +0, -1 for the literal -0, 0 otherwise : the FIR constants
    static int zeroLiteral(ValueInst* v);

    // the same for the text of the ocpp generator : 0, 0.0, 0.0f, 0.0L, -0.0f...
    static int zeroLiteral(const std::string& s)
    {
        size_t i = 0, n = s.size();
        bool   neg = false;
        if (i < n && s[i] == '-') {
            neg = true;
            i++;
        }
        if (n > i && (s[n - 1] == 'f' || s[n - 1] == 'L')) {
            n--;
        }
        bool zero = false, dot = false;
        for (; i < n; i++) {
            if (s[i] == '0') {
                zero = true;
            } else if (s[i] == '.' && !dot) {
                dot = true;
            } else {
                return 0;
            }
        }
        return zero ? (neg ? -1 : 1) : 0;
    }

    // the helper of a form, with the libm suffix of the program's real type (f, none, l)
    static std::string minMaxHelper(bool isMax, MinMaxForm form);

    // the helpers, in C and C++ : written once, before the classes, when a real max or min
    // was generated (fNeedMinMaxHelpers, cleared once written)
    static bool fNeedMinMaxHelpers;
    // byRef : the comparisons return a reference under clang, as the std::max cpp wrote (C++ only)
    static void printMinMaxHelpers(std::ostream& out, bool byRef = false);

    virtual std::string fname(int type) { return sname() + isuffix(); }

    // FIR backends
    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type rtype,
                                    ConstTypes types) = 0;
    // Old CPP backend
    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args,
                                     ConstTypes types) = 0;

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args,
                                      const std::vector< ::Type>& types) = 0;

    ValueInst* generateFun(CodeContainer* container, const std::string& fun_name,
                           const Values& args, ::Type rtype, ConstTypes types);
};

// Casting operations
inline ValueInst* promote2real(int type, ValueInst* val)
{
    return (type == kReal) ? val : IB::genCastRealInst(val);
}
inline ValueInst* promote2int(int type, ValueInst* val)
{
    return (type == kInt) ? val : IB::genCastInt32Inst(val);
}

inline ValueInst* cast2real(int type, ValueInst* val)
{
    return (type == kReal) ? IB::genCastRealInst(val) : val;
}
inline ValueInst* cast2int(int type, ValueInst* val)
{
    return (type == kInt) ? IB::genCastInt32Inst(val) : val;
}

#endif
