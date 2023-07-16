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
#include "xtended.hh"

/*
 When argument is kInt and exponent is kInt (or kReal without decimal part),
 an explicit mydsp_faustpowerXX_i(..) is generated.
 When argument is kReal and exponent is kInt (or kReal without decimal part),
 an explicit mydsp_faustpowerXX_f(..) is generated.
 Otherwise pow[f||l](argument,exponent) is generated.
 */

class PowPrim : public xtended {
   public:
    PowPrim() : xtended("pow") {}

    virtual unsigned int arity() { return 2; }

    virtual bool needCache() { return true; }

    virtual Type inferSigType(ConstTypes args)
    {
        faustassert(args.size() == arity());

        Type t = args[0];
        Type u = args[1];

        interval i = t->getInterval();
        interval j = u->getInterval();
        
        return castInterval(t | u, gAlgebra.Pow(i, j)); // maybe we should distinguish between real and integer exponents
    }

    virtual int inferSigOrder(const std::vector<int>& args)
    {
        faustassert(args.size() == arity());
        return std::max(args[0], args[1]);
    }
    
    // Fast integer based power, for positive exponent
    template <typename Type1, typename Type2>
    Type1 ipow(Type1 a, Type2 ex)
    {
        if (0 == ex) return 1;
        else {
            Type1 z = a;
            Type1 y = 1;
            while (true) {
                if (ex & 1) y *= z;
                ex /= 2;
                if (0 == ex) break;
                z *= z;
            }
            return y;
        }
    }

    virtual Tree computeSigOutput(const std::vector<Tree>& args)
    {
        num n, m;
        faustassert(args.size() == arity());
        if (isNum(args[0], n) && isNum(args[1], m)) {
            if (!isfloat(n) && !isfloat(m) && int(m) > 0) {
                return tree(ipow(int(n), int(m)));
            } else {
                return tree(pow(double(n), double(m)));
            }
        } else if (isNum(args[1], m)) {
            double exponent = double(m);
            if (exponent == 0.0) {
                // pow(x, 0) ==> 1
                return tree(1.0);
            } else if (exponent == 1.0) {
                // pow(x, 1) ==> x
                return args[0];
            } else if ((exponent == 10.) && gGlobal->gHasExp10) {
                // pow(x, 10) ==> exp10(x)
                return tree(::symbol("exp10"), args[0]);
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
    
    // Check that power argument is an integer or possibly represents an integer, up to 8
    bool isIntPowArg(::Type ty, ValueInst* val, int& pow_arg)
    {
        if (ty->nature() == kInt) {
            Int32NumInst* int_val = dynamic_cast<Int32NumInst*>(val);
            if (int_val) {
                pow_arg = int_val->fNum;
                return (pow_arg <= 8);
            } else {
                return false;
            }
        } else {
            FloatNumInst* float_val = dynamic_cast<FloatNumInst*>(val);
            DoubleNumInst* double_val = dynamic_cast<DoubleNumInst*>(val);
            if (float_val) {
                pow_arg = int(float_val->fNum);
                double intpart;
                return (std::modf(float_val->fNum, &intpart) == 0.) && (pow_arg >= 0) && (pow_arg <= 8);
            } else if (double_val) {
                pow_arg = int(double_val->fNum);
                double intpart;
                return (std::modf(double_val->fNum, &intpart) == 0.) && (pow_arg >= 0) && (pow_arg <= 8);
            } else {
                return false;
            }
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());
 
        ValuesIt it = args.begin(); it++;
        int pow_arg = 0;
    
        if (isIntPowArg(types[1], *it, pow_arg)
            && (types[1]->variability() == kKonst)
            && (types[1]->computability() == kComp)
            && (gGlobal->gNeedManualPow)) {
            
            Typed::VarType t0 = convert2FIRType(types[0]->nature());
            std::vector<Typed::VarType> atypes = { t0, Typed::kInt32 };
            Typed::VarType rtype = convert2FIRType(result->nature());
            
            // Expand the pow depending on the exponent argument
            BlockInst* block = InstBuilder::genBlockInst();
            std::string faust_power_name = container->getFaustPowerName() + std::to_string(pow_arg) + ((rtype == Typed::kInt32) ? "_i" : "_f");

            Names named_args;
            named_args.push_back(InstBuilder::genNamedTyped("value", InstBuilder::genBasicTyped(t0)));
            
            if (pow_arg == 0) {
                block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genTypedNum(t0, 1.0)));
            } else {
                ValueInst* res = InstBuilder::genLoadFunArgsVar("value");
                for (int i = 0; i < pow_arg - 1; i++) {
                    res = InstBuilder::genMul(res, InstBuilder::genLoadFunArgsVar("value"));
                }
                block->pushBackInst(InstBuilder::genRetInst(res));
            }
            
            container->pushGlobalDeclare(InstBuilder::genDeclareFunInst(faust_power_name,
                                                                        InstBuilder::genFunTyped(named_args, InstBuilder::genBasicTyped(rtype),
                                                                                                 FunTyped::kLocal), block));
            
            Values truncated_args;
            truncated_args.push_back((*args.begin()));
            return InstBuilder::genFunCallInst(faust_power_name, truncated_args);
      
        } else {
            
            // Both arguments forced to itfloat()
            std::vector<Typed::VarType> atypes = { itfloat(), itfloat() };
            
            Values cargs;
            ValuesIt it2 = args.begin();
            std::vector<::Type>::const_iterator it1;
            
            for (it1 = types.begin(); it1 != types.end(); it1++, it2++) {
                cargs.push_back(promote2real((*it1)->nature(), (*it2)));
            }
            
            return cast2int(result->nature(), container->pushFunction(subst("pow$0", isuffix()), itfloat(), atypes, cargs));
        }
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        if ((types[1]->nature() == kInt) && (types[1]->variability() == kKonst) &&
            (types[1]->computability() == kComp)) {
            klass->rememberNeedPowerDef();
            return subst("faustpower<$1>($0)", args[0], args[1]);
        } else {
            return subst("pow$2($0,$1)", args[0], args[1], isuffix());
        }
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("{$0}^{$1}", args[0], args[1]);
    }

    // power is now used as an infix binary operator, we return true to
    // indicate that we want ^(n) to be equivalent to _^n
    virtual bool isSpecialInfix() { return true; }

    Tree diff(const std::vector<Tree> &args) override
    {
        // (x^p)' = (x^p)(plog(x))' = x^{p-1}(p + xlog(x)(p)')
        auto d{sigMul(
                sigPow(args[0], sigSub(args[1], sigReal(1.0))),
                sigAdd(args[1], sigMul(args[0], sigMul(sigLog(args[0]), args[2])))
        )};

        return d;
    }
};
