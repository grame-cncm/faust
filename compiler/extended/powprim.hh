/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include <math.h>
#include <cmath>

#include "Text.hh"
#include "floats.hh"
#include "global.hh"
#include "xtended.hh"

class PowPrim : public xtended {
   public:
    PowPrim() : xtended("pow") {}

    virtual unsigned int arity() { return 2; }

    virtual bool needCache() { return true; }

    virtual Type infereSigType(const vector<Type>& args)
    {
        faustassert(args.size() == arity());

        interval i = args[0]->getInterval();
        interval j = args[1]->getInterval();
        return castInterval(args[0] | args[1], pow(i, j));
    }

    virtual int infereSigOrder(const vector<int>& args)
    {
        faustassert(args.size() == arity());
        return max(args[0], args[1]);
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

    virtual Tree computeSigOutput(const vector<Tree>& args)
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
            if ((double(m) == 10.) && gGlobal->gHasExp10) {
                // pow(x, 10) ==> exp10(x)
                return tree(::symbol("exp10"), args[0]);
            } else if (double(m) == 0.5) {
                // pow(x, 0.5) ==> sqrt(x)
                return tree(::symbol("sqrt"), args[0]);
            } else if (double(m) == 0.25) {
                // pow(x, 0.25) ==> sqrt(sqrt(x))
                return tree(::symbol("sqrt"), tree(::symbol("sqrt"), args[0]));
            }
        }
        return tree(symbol(), args[0], args[1]);
    }
    
    // Check that power argument is an integer or possibly represents an integer, up to 32
    bool isIntPowArg(::Type ty, ValueInst* val_aux, int& pow_arg)
    {
        if (ty->nature() == kInt) {
            Int32NumInst* int_val = dynamic_cast<Int32NumInst*>(val_aux);
            if (int_val) {
                pow_arg = int_val->fNum;
                return (pow_arg <= 32);
            } else {
                return false;
            }
        } else {
            FloatNumInst* float_val = dynamic_cast<FloatNumInst*>(val_aux);
            DoubleNumInst* double_val = dynamic_cast<DoubleNumInst*>(val_aux);
            if (float_val) {
                pow_arg = int(float_val->fNum);
                double intpart;
                return (std::modf(float_val->fNum, &intpart) == 0.) && (pow_arg >= 0) && (pow_arg <= 32);
            } else if (double_val) {
                pow_arg = int(double_val->fNum);
                double intpart;
                return (std::modf(double_val->fNum, &intpart) == 0.) && (pow_arg >= 0) && (pow_arg <= 32);
            } else {
                return false;
            }
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result,
                                    vector<::Type> const& types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        vector<Typed::VarType> arg_types(2);
        Typed::VarType         result_type = (result->nature() == kInt) ? Typed::kInt32 : itfloat();

        ValuesIt it = args.begin();
        it++;
        Int32NumInst* arg1 = dynamic_cast<Int32NumInst*>(*it);

        if (arg1 && (types[1]->nature() == kInt) && (types[1]->variability() == kKonst)
            && (types[1]->computability() == kComp) && (gGlobal->gNeedManualPow)) {
            
            arg_types[0] = (types[0]->nature() == kInt) ? Typed::kInt32 : itfloat();
            arg_types[1] = Typed::kInt32;
            
            // Expand the pow depending of the exposant argument
            BlockInst* block = InstBuilder::genBlockInst();
            
            ValuesIt it1 = args.begin();
            it1++;
            
            Int32NumInst* arg2 = dynamic_cast<Int32NumInst*>(*it1);
            string faust_power_name = container->getFaustPowerName() + to_string(arg2->fNum) + ((result_type == Typed::kInt32) ? "_i" : "_f");
            
            Names named_args;
            named_args.push_back(InstBuilder::genNamedTyped("value", InstBuilder::genBasicTyped(arg_types[0])));
            
            if (arg2->fNum == 0) {
                block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genInt32NumInst(1)));
            } else {
                ValueInst* res = InstBuilder::genLoadFunArgsVar("value");
                for (int i = 0; i < arg2->fNum - 1; i++) {
                    res = InstBuilder::genMul(res, InstBuilder::genLoadFunArgsVar("value"));
                }
                block->pushBackInst(InstBuilder::genRetInst(res));
            }
            
            container->pushGlobalDeclare(InstBuilder::genDeclareFunInst(faust_power_name,
                                                                        InstBuilder::genFunTyped(named_args, InstBuilder::genBasicTyped(result_type),
                                                                                                 FunTyped::kLocal), block));
            
            Values truncated_args;
            truncated_args.push_back((*args.begin()));
            return InstBuilder::genFunCallInst(faust_power_name, truncated_args);
      
        } else {
            // Both arguments forced to itfloat()
            arg_types[0] = itfloat();
            arg_types[1] = itfloat();

            Values casted_args;
            ValuesIt it2 = args.begin();
            vector< ::Type>::const_iterator it1;
            
            for (it1 = types.begin(); it1 != types.end(); it1++, it2++) {
                casted_args.push_back(promote2real((*it1)->nature(), (*it2)));
            }

            return cast2int(result->nature(), container->pushFunction(subst("pow$0", isuffix()), itfloat(), arg_types, casted_args));
        }
    }

    virtual string generateCode(Klass* klass, const vector<string>& args, const vector<::Type>& types)
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

    virtual string generateLateq(Lateq* lateq, const vector<string>& args, const vector<::Type>& types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("{$0}^{$1}", args[0], args[1]);
    }

    // power is now used as an infix binary operator, we return true to
    // indicate that we want ^(n) to be equivalent to _^n
    virtual bool isSpecialInfix() { return true; }
};
