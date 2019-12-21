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

    virtual void sigVisit(Tree sig, sigvisitor* visitor) {}

    virtual int infereSigOrder(const vector<int>& args)
    {
        faustassert(args.size() == arity());
        return max(args[0], args[1]);
    }

    virtual Tree computeSigOutput(const vector<Tree>& args)
    {
        num n, m;
        faustassert(args.size() == arity());
        if (isNum(args[0], n) && isNum(args[1], m)) {
            return tree(pow(double(n), double(m)));
        } else if (isNum(args[0], n) && (double(n) == 10.) && gGlobal->gHasExp10) {
            // pow(10, x) ==> exp10(x)
            return tree(::symbol("exp10"), args[1]);
        } else {
            return tree(symbol(), args[0], args[1]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result,
                                    vector<::Type> const& types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        vector<Typed::VarType>          arg_types(2);
        Typed::VarType                  result_type = (result->nature() == kInt) ? Typed::kInt32 : itfloat();

        list<ValueInst*>::const_iterator it = args.begin();
        it++;
        Int32NumInst* arg1 = dynamic_cast<Int32NumInst*>(*it);

        if (arg1 && (types[1]->nature() == kInt) && (types[1]->variability() == kKonst)
            && (types[1]->computability() == kComp) && (gGlobal->gNeedManualPow)) {
            
            arg_types[0] = (types[0]->nature() == kInt) ? Typed::kInt32 : itfloat();
            arg_types[1] = Typed::kInt32;
            
            // Expand the pow depending of the exposant argument
            BlockInst* block = InstBuilder::genBlockInst();
            
            list<ValueInst*>::const_iterator it = args.begin();
            it++;
            
            Int32NumInst* arg1             = dynamic_cast<Int32NumInst*>(*it);
            string        faust_power_name = container->getFaustPowerName() + to_string(arg1->fNum) + ((result_type == Typed::kInt32) ? "_i" : "_f");
            
            list<NamedTyped*> named_args;
            named_args.push_back(InstBuilder::genNamedTyped("value", InstBuilder::genBasicTyped(arg_types[0])));
            
            if (arg1->fNum == 0) {
                block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genInt32NumInst(1)));
            } else {
                ValueInst* res = InstBuilder::genLoadFunArgsVar("value");
                for (int i = 0; i < arg1->fNum - 1; i++) {
                    res = InstBuilder::genMul(res, InstBuilder::genLoadFunArgsVar("value"));
                }
                block->pushBackInst(InstBuilder::genRetInst(res));
            }
            
            container->pushGlobalDeclare(InstBuilder::genDeclareFunInst(faust_power_name,
                                                                        InstBuilder::genFunTyped(named_args, InstBuilder::genBasicTyped(result_type),
                                                                                                 FunTyped::kLocal), block));
            
            list<ValueInst*> truncated_args;
            truncated_args.push_back((*args.begin()));
            return InstBuilder::genFunCallInst(faust_power_name, truncated_args);
      
        } else {
            // Both arguments forced to itfloat()
            arg_types[0] = itfloat();
            arg_types[1] = itfloat();

            list<ValueInst*> casted_args;
            list<ValueInst*>::const_iterator it2 = args.begin();
            vector< ::Type>::const_iterator it1;
            
            for (it1 = types.begin(); it1 != types.end(); it1++, it2++) {
                casted_args.push_back(promote2real((*it1)->nature(), (*it2)));
            }

            return cast2int(result->nature(), container->pushFunction(subst("pow$0", isuffix()), itfloat(), arg_types, casted_args));
        }
    }

    virtual string old_generateCode(Klass* klass, const vector<string>& args, const vector<::Type>& types)
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
