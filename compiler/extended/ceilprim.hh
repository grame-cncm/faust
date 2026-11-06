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
#include "xtendedCodegen.hh"
#include "global.hh"

class CeilPrim : public xtendedCodegen {
   public:
    CeilPrim() : xtendedCodegen("ceil") {}

    virtual unsigned int arity() override { return 1; }

    virtual bool needCache() override { return true; }


    virtual Tree computeSigOutput(const std::vector<Tree>& args) override
    {
        num n;
        faustassert(args.size() == arity());
        if (isNum(args[0], n)) {
            return tree(ceil(double(n)));
        } else {
            // -mapp is applied by generateCode, see approxByTruncation
            return tree(symbol(), args[0]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result,
                                    std::vector< ::Type> const& types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        if (approxByTruncation(types[0])) {
            // r = T(int(n)); return (r == n) ? n : ((n >= 0) ? r + 1 : r);
            // n and r are used several times: each use gets its own copy
            BasicCloneVisitor cloner;
            ValueInst*        n     = promote2real(types[0]->nature(), args.front());
            ValueInst*        r     = IB::genCastRealInst(IB::genCastInt32Inst(n->clone(&cloner)));
            ValueInst*        n1    = n->clone(&cloner);
            ValueInst*        isint = IB::genEqual(r->clone(&cloner), n1);
            ValueInst*        n2    = n->clone(&cloner);
            ValueInst*        zero  = IB::genRealNumInst(itfloat(), 0.);
            ValueInst*        ispos = IB::genGreaterEqual(n2, zero);
            ValueInst*        one   = IB::genRealNumInst(itfloat(), 1.);
            ValueInst*        up    = IB::genAdd(r->clone(&cloner), one);
            ValueInst*        round = IB::genSelect2Inst(ispos, up, r);
            return IB::genSelect2Inst(isint, n, round);
        }
        return generateFun(container, subst("ceil$0", isuffix()), args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args,
                                     ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        if (approxByTruncation(types[0])) {
            // r = T(int(n)); return (r == n) ? n : ((n >= 0) ? r + 1 : r);
            std::string n =
                (types[0]->nature() == kInt) ? subst("$0($1)", ifloat(), args[0]) : args[0];
            std::string r = subst("$0(int($1))", ifloat(), n);
            return subst("(($1 == $0) ? $0 : (($0 >= 0) ? ($1 + 1) : $1))", n, r);
        }
        return subst("ceil$1($0)", args[0], isuffix());
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args,
                                      ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("\\left\\lceil $0 \\right\\rceil", args[0]);
    }

    double compute(const std::vector<Node>& args) override { return ceil(args[0].getDouble()); }
};
