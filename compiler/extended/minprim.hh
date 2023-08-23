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

class MinPrim : public xtended {
   public:
    MinPrim() : xtended("min") {}

    virtual unsigned int arity() { return 2; }

    virtual bool needCache() { return true; }

    virtual ::Type inferSigType(ConstTypes args)
    {
        faustassert(args.size() == arity());
        interval i = args[0]->getInterval();
        interval j = args[1]->getInterval();
        // Use 'min' on intervals here...
        return castInterval(args[0] | args[1], gAlgebra.Min(i, j));
    }

    virtual int inferSigOrder(const std::vector<int>& args)
    {
        faustassert(args.size() == arity());
        return std::max(args[0], args[1]);
    }

    virtual Tree computeSigOutput(const std::vector<Tree>& args)
    {
        double f, g;
        int    i, j;

        faustassert(args.size() == arity());

        if (isDouble(args[0]->node(), &f)) {
            if (isDouble(args[1]->node(), &g)) {
                return tree(std::min(f, g));
            } else if (isInt(args[1]->node(), &j)) {
                return tree(std::min(f, double(j)));
            } else {
                return tree(symbol(), args[0], args[1]);
            }

        } else if (isInt(args[0]->node(), &i)) {
            if (isDouble(args[1]->node(), &g)) {
                return tree(std::min(double(i), g));
            } else if (isInt(args[1]->node(), &j)) {
                return tree(std::min(i, j));
            } else {
                return tree(symbol(), args[0], args[1]);
            }

        } else {
            return tree(symbol(), args[0], args[1]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        /*
         04/25/22 : this optimisation cannot be done because interval computation is buggy: like no.noise interval
         [O..inf] !
         */

        /*
            // Min of disjoint intervals returns one of them
            interval i1 = types[0]->getInterval();
            interval i2 = types[1]->getInterval();

            if (i1.isValid() && i2.isValid()) {
                if (i1.hi() <= i2.lo()) {
                    return *args.begin();
                } else if (i2.hi() <= i1.lo()) {
                    return *(std::next(args.begin(), 1));
                }
            }
         */

        std::string fun_name = (result->nature() == kInt) ? "min_i" : subst("min_$0", isuffix());
        return generateFun(container, fun_name, args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        // generates code compatible with overloaded min
        int n0 = types[0]->nature();
        int n1 = types[1]->nature();
        if (n0 == kReal) {
            if (n1 == kReal) {
                // both are floats, no need to cast
                return subst("min($0, $1)", args[0], args[1]);
            } else {
                faustassert(n1 == kInt);  // second argument is not float, cast it to float
                return subst("min($0, $2($1))", args[0], args[1], icast());
            }
        } else if (n1 == kReal) {
            faustassert(n0 == kInt);  // first not float but second is, cast first to float
            return subst("min($2($0), $1)", args[0], args[1], icast());
        } else {
            faustassert(n0 == kInt);
            faustassert(n1 == kInt);  // both are integers, check for booleans
            int b0 = types[0]->boolean();
            int b1 = types[1]->boolean();
            if (b0 == kNum) {
                if (b1 == kNum) {
                    // both are integers, no need to cast
                    return subst("min($0, $1)", args[0], args[1]);
                } else {
                    faustassert(b1 == kBool);  // second is boolean, cast to int
                    return subst("min($0, int($1))", args[0], args[1]);
                }
            } else if (b1 == kNum) {
                faustassert(b0 == kBool);  // first is boolean, cast to int
                return subst("min(int($0), $1)", args[0], args[1], icast());
            } else {
                // both are booleans, theoretically no need to cast, but we still do it to be sure 'true' is actually
                // '1' and 'false' is actually '0' (which is not the case if compiled in SSE mode)
                faustassert(b0 == kBool);
                faustassert(b1 == kBool);
                return subst("min(int($0), int($1))", args[0], args[1]);
            }
        }
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        ::Type t = inferSigType(types);
        return subst("\\min\\left( $0, $1 \\right)", args[0], args[1]);
    }
    
    Tree diff(const std::vector<Tree> &args) override
    {
        /*                /
         *                | f', f < g
         * (min(f, g))' = {
         *                | g', otherwise
         *                \
         */
        return sigSelect2(sigLT(args[0], args[1]), args[2], args[3]);
    }
};
