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
#include "sigtyperules.hh"
#include "xtended.hh"

/********************************************************************************************

FTZ is a special primitive injected in recursive signals when the -ftz option is on.
The injected code allows to flush to zero denormalized number. This option should be used only
when it is not available on the CPU.

*********************************************************************************************/

const char* FTZPattern[4][3] = {
    // not a float
    {"???", "???", "???"},
    // float  (1)
    {"$0", "((fabsf($0)> FLT_MIN) ? $0 : 0.0f)", "((*(int*)&$0) & 0x7F800000) ? $0 : 0.0f"},
    // double (2)
    {"$0", "((fabs($0)> DBL_MIN) ? $0 : 0.0 )", "((*(long int*)&$0) & 0x7FF0000000000000) ? $0 : 0.0"},
    // quad   (3)
    {"$0", "((fabsl($0)> LDBL_MIN) ? $0 : 0.0L)", "((fabsl($0)>LDBL_MIN) ? $0 : 0.0L)"}
};

class FtzPrim : public xtended {
   private:
    static int freshnum;  // counter for fTempFTZxxx fresh variables

   public:
    FtzPrim() : xtended("ftz") {}

    virtual unsigned int arity() { return 1; }

    virtual bool needCache() { return true; }

    virtual Type infereSigType(ConstTypes types)
    {
        faustassert(types.size() == arity());
        return types[0];
    }

    virtual int infereSigOrder(const std::vector<int>& args)
    {
        faustassert(args.size() == arity());
        return args[0];
    }

    virtual Tree computeSigOutput(const std::vector<Tree>& args)
    {
        int    i;
        double r;

        faustassert(args.size() == arity());

        if (isSigInt(args[0], &i)) {
            return args[0];
        } else if (isSigReal(args[0], &r)) {
            return args[0];
        } else {
            return tree(symbol(), args[0]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        Type t = infereSigType(types);
        if ((t->nature() == kReal) && (gGlobal->gFTZMode > 0)) {
            switch (gGlobal->gFTZMode) {
                case 1: {
                    // "fabs" function has to be declared
                    Names args_types;
                    args_types.push_back(InstBuilder::genNamedTyped("dummy", InstBuilder::genItFloatTyped()));
                    FunTyped* fun_type = InstBuilder::genFunTyped(args_types, InstBuilder::genItFloatTyped());
                    container->pushGlobalDeclare(InstBuilder::genDeclareFunInst(subst("fabs$0", isuffix()), fun_type));

                    // we need to create a temporary variable to store the expression
                    std::string vname = gGlobal->getFreshID("fTempFTZ");
                    container->addIncludeFile("<float.h>");
                    container->pushComputeDSPMethod(
                        InstBuilder::genDecStackVar(vname, InstBuilder::genItFloatTyped(), *args.begin()));
                    ValueInst* real_min;
                    if (gGlobal->gFloatSize == 1) {
                        real_min = InstBuilder::genFloatNumInst(inummin());
                    } else {
                        real_min = InstBuilder::genDoubleNumInst(inummin());
                    }

                    Values args_value;
                    args_value.push_back(InstBuilder::genLoadStackVar(vname));
                    return InstBuilder::genSelect2Inst(
                        InstBuilder::genGreaterThan(InstBuilder::genFunCallInst(subst("fabs$0", isuffix()), args_value),
                                                    real_min),
                        InstBuilder::genLoadStackVar(vname), InstBuilder::genTypedZero(itfloat()));
                } break;

                case 2: {
                    // Bitcast based solution
                    std::string vname = gGlobal->getFreshID("fTempFTZ");
                    container->pushComputeDSPMethod(
                        InstBuilder::genDecStackVar(vname, InstBuilder::genItFloatTyped(), *args.begin()));
                    switch (gGlobal->gFloatSize) {
                        case 1:
                            return InstBuilder::genSelect2Inst(
                                InstBuilder::genAnd(InstBuilder::genBitcastInst(InstBuilder::genLoadStackVar(vname),
                                                                                InstBuilder::genInt32Typed()),
                                                    InstBuilder::genInt32NumInst(0x7F800000)),
                                InstBuilder::genLoadStackVar(vname), InstBuilder::genTypedZero(itfloat()));
                        case 2:
                            return InstBuilder::genSelect2Inst(
                                InstBuilder::genAnd(
                                    InstBuilder::genBitcastInst(InstBuilder::genLoadStackVar(vname),
                                                                InstBuilder::genBasicTyped(Typed::kInt64)),
                                    InstBuilder::genInt64NumInst(0x7FF0000000000000)),
                                InstBuilder::genLoadStackVar(vname), InstBuilder::genTypedZero(itfloat()));
                        default:
                            faustassert(false);
                            return *args.begin();
                    }
                } break;

                default:
                    faustassert(false);
                    return *args.begin();
            }

        } else {
            // No ftz code for integer signals
            return *args.begin();
        }
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        Type t = infereSigType(types);
        if ((t->nature() == kReal) && (gGlobal->gFTZMode > 0)) {
            // we need to create a temporary variable to store the expression
            std::string vname = subst("fTempFTZ$0", T(++freshnum));
            klass->addIncludeFile("<float.h>");
            klass->addExecCode(Statement("", subst("$0 $1 = $2;", ifloat(), vname, args[0])));
            return subst(FTZPattern[gGlobal->gFloatSize][gGlobal->gFTZMode], vname);
        } else {
            // No ftz code for integer signals
            return args[0];
        }
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());
        return args[0];
    }
};

int FtzPrim::freshnum = 0;
