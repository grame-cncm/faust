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

#include <math.h>

#include "Text.hh"
#include "floats.hh"
#include "global.hh"
#include "xtendedCodegen.hh"

/*
 A power of two integers never reaches the code : the normal form writes it as its products
 by squaring, which wrap on 32 bits (signalIntegerPowerPromote), for every backend.
 When argument is kReal and exponent is kInt (or kReal without decimal part),
 an explicit mydsp_faustpowerXX_f(..) is generated.
 Otherwise pow[f||l](argument,exponent) is generated.
 */

class PowPrim : public xtendedCodegen {
   public:
    PowPrim() : xtendedCodegen("pow") {}

    virtual unsigned int arity() override { return 2; }

    virtual bool needCache() override { return true; }


    // The power by squaring, for an exponent >= 0 ; on uint32_t, the product wrapped on 32 bits
    template <typename Type1, typename Type2>
    Type1 ipow(Type1 a, Type2 ex)
    {
        if (0 == ex) {
            return 1;
        } else {
            Type1 z = a;
            Type1 y = 1;
            while (true) {
                if (ex & 1) {
                    y *= z;
                }
                ex /= 2;
                if (0 == ex) {
                    break;
                }
                z *= z;
            }
            return y;
        }
    }

    // A power of two constants, folded as the code computes it : two integers give the
    // product of |k| factors wrapped on 32 bits, an integer for k >= 0, the inverse of the
    // product, a real in the precision of the program, for k < 0 ; a base or an exponent
    // real gives the real power. A base variable keeps the forms whose nature the folding
    // cannot tell : pow(x, 0) is the integer 1, written by the multiplicative algebra, and
    // pow(x, 1.0) a real, x or float(x).
    virtual Tree computeSigOutput(const std::vector<Tree>& args) override
    {
        num n, m;
        faustassert(args.size() == arity());
        if (isNum(args[0], n) && isNum(args[1], m)) {
            // 0 to a negative power is 1 / 0^|k| : a certain division by 0, refused as the
            // constant division it stands for, not folded to an infinity
            if (double(n) == 0.0 && double(m) < 0.0) {
                throw faustexception(divisionByZero(args));
            }
            if (!isfloat(n) && !isfloat(m)) {
                int64_t  k = int(m);
                uint32_t p = ipow(uint32_t(int(n)), uint64_t(k < 0 ? -k : k));
                if (k >= 0) {
                    return tree(int(int32_t(p)));
                }
                // a wrapped product of 0 (2^32, for pow(2, -32)) is the same division by 0
                if (p == 0) {
                    throw faustexception(divisionByZero(args));
                }
                return tree((gGlobal->gFloatSize == 1) ? double(1.0f / float(int32_t(p)))
                                                       : 1.0 / double(int32_t(p)));
            }
            return tree(pow(double(n), double(m)));
        } else if (isNum(args[0], n)) {
            // pow(10, x) ==> exp10(x), a real power : the base 10 of an integer is decided
            // with the nature of its exponent (signalPowerNaturePromote)
            if (isfloat(n) && (double(n) == 10.) && gGlobal->gHasExp10) {
                return tree(::symbol("exp10"), args[1]);
            }
        } else if (isNum(args[1], m)) {
            double exponent = double(m);
            if (isfloat(m) && exponent == 0.0) {
                // pow(x, 0.0) ==> 1.0
                return tree(1.0);
            } else if (!isfloat(m) && int(m) == 1) {
                // pow(x, 1) ==> x
                return args[0];
            } else if (exponent == 0.5) {
                // pow(x, 0.5) ==> sqrt(x)
                return tree(::symbol("sqrt"), args[0]);
            } else if (exponent == 0.25) {
                // pow(x, 0.25) ==> sqrt(sqrt(x))
                return tree(::symbol("sqrt"), tree(::symbol("sqrt"), args[0]));
            }
        }
        return tree(symbol(), args[0], args[1]);
    }

    static std::string divisionByZero(const std::vector<Tree>& args)
    {
        std::stringstream error;
        error << "ERROR : division by 0 in pow(" << ppsig(args[0], MAX_ERROR_SIZE) << ", "
              << ppsig(args[1], MAX_ERROR_SIZE) << ")" << std::endl;
        return error.str();
    }

    // Check that power argument is an integer or possibly represents an integer, in [0, 8] :
    // a negative constant (left by the constant propagation, after the normal form that
    // writes negative powers as divisions) takes the general path
    bool isIntPowArg(::Type ty, ValueInst* val, int& pow_arg)
    {
        if (ty->nature() == kInt) {
            Int32NumInst* int_val = dynamic_cast<Int32NumInst*>(val);
            if (int_val) {
                pow_arg = int_val->fNum;
                return (pow_arg >= 0) && (pow_arg <= 8);
            } else {
                return false;
            }
        } else {
            FloatNumInst*  float_val  = dynamic_cast<FloatNumInst*>(val);
            DoubleNumInst* double_val = dynamic_cast<DoubleNumInst*>(val);
            if (float_val) {
                pow_arg = int(float_val->fNum);
                double intpart;
                return (std::modf(float_val->fNum, &intpart) == 0.) && (pow_arg >= 0) &&
                       (pow_arg <= 8);
            } else if (double_val) {
                pow_arg = int(double_val->fNum);
                double intpart;
                return (std::modf(double_val->fNum, &intpart) == 0.) && (pow_arg >= 0) &&
                       (pow_arg <= 8);
            } else {
                return false;
            }
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result,
                                    ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        // a power of integers is written as its products before the code (signalIntegerPowerPromote)
        faustassert(result->nature() != kInt);

        ValuesIt it = args.begin();
        it++;
        int pow_arg = 0;

        if (isIntPowArg(types[1], *it, pow_arg) && (types[1]->variability() == kKonst) &&
            (types[1]->computability() == kComp) && (gGlobal->gNeedManualPow)) {
            Typed::VarType              t0     = convert2FIRType(types[0]->nature());
            std::vector<Typed::VarType> atypes = {t0, Typed::kInt32};
            Typed::VarType              rtype  = convert2FIRType(result->nature());

            // Expand the pow depending on the exponent argument
            BlockInst*  block            = IB::genBlockInst();
            std::string faust_power_name = container->getFaustPowerName() +
                                           std::to_string(pow_arg) +
                                           ((rtype == Typed::kInt32) ? "_i" : "_f");

            // The argument's name carries its type. Variable types are kept in
            // one global table keyed by NAME, so an int and a float helper that
            // both called their argument "value" shared one entry: whichever
            // was declared last decided, and the C backend then rendered the
            // float helper's multiply as the int32 faust_wrap_mul(), truncating
            // every float x*x to an integer square.
            std::string arg_name = (t0 == Typed::kInt32) ? "value_i" : (t0 == Typed::kInt64) ? "value_l" : "value_f";
            Names named_args;
            named_args.push_back(IB::genNamedTyped(arg_name, IB::genBasicTyped(t0)));

            if (pow_arg == 0) {
                block->pushBackInst(IB::genRetInst(IB::genTypedNum(t0, 1.0)));
            } else {
                ValueInst* res = IB::genLoadFunArgsVar(arg_name);
                for (int i = 0; i < pow_arg - 1; i++) {
                    res = IB::genMul(res, IB::genLoadFunArgsVar(arg_name));
                }
                block->pushBackInst(IB::genRetInst(res));
            }

            container->pushGlobalDeclare(IB::genDeclareFunInst(
                faust_power_name,
                IB::genFunTyped(named_args, IB::genBasicTyped(rtype), FunTyped::kLocal), block));

            Values truncated_args;
            truncated_args.push_back((*args.begin()));
            return IB::genFunCallInst(faust_power_name, truncated_args);

        } else {
            // Both arguments forced to itfloat()
            std::vector<Typed::VarType> atypes = {itfloat(), itfloat()};

            Values                              cargs;
            ValuesIt                            it2 = args.begin();
            std::vector<::Type>::const_iterator it1;

            for (it1 = types.begin(); it1 != types.end(); it1++, it2++) {
                cargs.push_back(promote2real((*it1)->nature(), (*it2)));
            }

            if (isTwoBase(args.front()) && hasExp2()) {
                // pow(2, x) ==> exp2(x) : the same real power, within the 2 ulps of the libm
                // (g++ keeps pow when it may not change the rounding ; dx7 : 35 % faster)
                std::vector<Typed::VarType> etypes = {itfloat()};
                Values                      eargs  = {cargs.back()};
                return cast2int(result->nature(),
                                container->pushFunction(subst("exp2$0", isuffix()), itfloat(),
                                                        etypes, eargs));
            }
            return cast2int(result->nature(), container->pushFunction(subst("pow$0", isuffix()),
                                                                      itfloat(), atypes, cargs));
        }
    }

    // A literal of integer value in [0, 8], written as an integer (3) or as a real (3.0, 3.,
    // 3.0f) : the promotion gives the exponent of a real power the real nature of the power
    static bool isSmallIntegerValueLiteral(const std::string& s, int& value)
    {
        size_t n = s.size();
        if (n > 0 && s[n - 1] == 'f') {
            n--;
        }
        if (n == 0 || s[0] < '0' || s[0] > '8') {
            return false;
        }
        if (n > 1) {
            if (s[1] != '.') {
                return false;
            }
            for (size_t i = 2; i < n; i++) {
                if (s[i] != '0') {
                    return false;
                }
            }
        }
        value = s[0] - '0';
        return true;
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args,
                                     ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        // faustpower<N> recurses on N/2 and N - N/2 : a nonnegative literal only (a negative
        // one, left by the constant propagation, would never reach its base cases)
        int  exponent = -1;
        bool konst    = (types[1]->variability() == kKonst) && (types[1]->computability() == kComp);
        // a power of integers is written as its products before the code (signalIntegerPowerPromote)
        faustassert(!((types[0]->nature() == kInt) && (types[1]->nature() == kInt)));
        if (konst && (types[0]->nature() == kReal) &&
                   ((gGlobal->gFloatSize == 1) || (gGlobal->gFloatSize == 2)) &&
                   isSmallIntegerValueLiteral(args[1], exponent)) {
            // x^k, x real and k from 0 to 8 : the k - 1 products of the cpp generator
            // (isIntPowArg) and of the interval model, which widens such a power by k ulps
            // (interval_algebra.cpp, numericPow) ; beyond 8, the 2 ulps of the libm pow. The
            // base converted to the program's real type, as pow converts it, picks the
            // faustpower of that type
            klass->rememberNeedPowerDef();
            return subst("faustpower<$1>($2($0))", args[0], T(exponent), ifloat());
        } else if (isTwoLiteral(args[0]) && hasExp2()) {
            // pow(2, x) ==> exp2(x), as the cpp generator writes it
            return subst("exp2$1($0)", args[1], isuffix());
        } else {
            return subst("pow$2($0,$1)", args[0], args[1], isuffix());
        }
    }

    // exp2 in the C and C++ libm, for the real types of the program (not fixed point)
    static bool hasExp2()
    {
        return (gGlobal->gOutputLang == "cpp" || gGlobal->gOutputLang == "c" ||
                gGlobal->gOutputLang == "ocpp") &&
               (gGlobal->gFloatSize >= 1) && (gGlobal->gFloatSize <= 3);
    }

    // the constant 2, integer or real
    static bool isTwoBase(ValueInst* val)
    {
        if (Int32NumInst* i = dynamic_cast<Int32NumInst*>(val)) {
            return i->fNum == 2;
        } else if (FloatNumInst* f = dynamic_cast<FloatNumInst*>(val)) {
            return f->fNum == 2.f;
        } else if (DoubleNumInst* d = dynamic_cast<DoubleNumInst*>(val)) {
            return d->fNum == 2.;
        }
        return false;
    }

    // a literal of value 2 : 2, 2., 2.0, 2.0f, 2.0L
    static bool isTwoLiteral(const std::string& s)
    {
        std::string t = s;
        if (!t.empty() && (t.back() == 'f' || t.back() == 'L')) {
            t.pop_back();
        }
        if (t.empty() || t.find_first_not_of("0123456789.") != std::string::npos) {
            return false;
        }
        return std::strtod(t.c_str(), nullptr) == 2.0;
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args,
                                      ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("{$0}^{$1}", args[0], args[1]);
    }

    // power is now used as an infix binary operator, we return true to
    // indicate that we want ^(n) to be equivalent to _^n
    virtual bool isSpecialInfix() override { return true; }

    // The power the code computes, for the interpreter of the signals (signalRenderer) : two
    // integers give the product wrapped on 32 bits, computed unsigned, for k >= 0 ; for k < 0
    // (a control out of its contract : a negative exponent is otherwise decided real) the
    // integer power of the C and C++ helper, 1/x^|k| truncated toward 0. std::pow in double
    // then converted to int was undefined beyond the integers, and inexact beyond 2^53.
    double compute(const std::vector<Node>& args) override
    {
        if (isInt(args[0]) && isInt(args[1])) {
            int x = args[0].getInt();
            int k = args[1].getInt();
            if (k < 0) {
                return (x == 1) ? 1 : (x == -1) ? ((k & 1) ? -1 : 1) : 0;
            }
            return int32_t(ipow(uint32_t(x), uint32_t(k)));
        } else {
            return pow(args[0].getDouble(), args[1].getDouble());
        }
    }
};
