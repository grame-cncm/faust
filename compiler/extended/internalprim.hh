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

#include "xtended.hh"
#include "simplify.hh"
#include "sigorderrules.hh"

enum InternalOp { kId, kRate, kLo, kHi };

class InternalPrim : public xtended {
    private:
	InternalOp fOp;
    public:
	InternalPrim(InternalOp op, const char *name) : xtended(name), fOp(op) {}

	virtual Tree computeSigOutput(const std::vector<Tree>& args)
	{
		Tree sig = simplify(args[0]);
		int ret = -1;

		switch (fOp) {
		case kId:
			ret = sig->serial();
			break;
		case kRate:
			ret = getSigOrder(sig);
			break;
		case kLo: case kHi: {
			typeAnnotation(sig, false);
			interval i = getCertifiedSigType(sig)->getInterval();
			return tree(fOp == kLo ? i.lo() : i.hi());
		}
		default:
			faustassert(false);
		}

		return tree(ret);
	}

	virtual unsigned int arity() { return 1; }

	virtual bool needCache() { return true; }

	virtual ::Type inferSigType(ConstTypes args)
	{
		faustassert(false); return 0;
	}
	virtual int inferSigOrder(const std::vector<int>& args)
	{
		faustassert(false); return 0;
	}
	virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result, ConstTypes types)
	{
		faustassert(false); return 0;
	}
	virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args, ConstTypes types)
	{
		faustassert(false); return 0;
	}
	virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args, ConstTypes types)
	{
		return "TODO";
	}
};

static Tree add_internal_def(Tree defs, InternalOp op, const char *d_n)
{
	Tree id = boxIdent(d_n);
	std::string x_n = std::string("internal.") + d_n;
	InternalPrim *internal = new InternalPrim(op, x_n.c_str());
	return cons(cons(id, internal->box()), defs);
}

static Tree mkInternalEnv()
{
	Tree defs = gGlobal->nil;

	defs = add_internal_def(defs, kId, "id");
	defs = add_internal_def(defs, kRate, "rate");
	defs = add_internal_def(defs, kLo, "lo");
	defs = add_internal_def(defs, kHi, "hi");

	return boxWithLocalDef(boxEnvironment(), defs);
}
