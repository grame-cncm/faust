/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

#include "Text.hh"
#include "ppsig.hh"
#include "binop.hh"
#include "prim2.hh"
#include "xtended.hh"
#include "recursivness.hh"
#include "exception.hh"
#include "global.hh"

ppsig::ppsig(Tree s) : sig(s), fEnv(gGlobal->nil), fPriority(0), fHideRecursion(false)  {}

ostream& ppsig::printinfix(ostream& fout, const string& opname, int priority, Tree x, Tree y) const
{
	if (fPriority > priority) fout << "(";
	fout << ppsig(x,fEnv,priority) << opname << ppsig(y,fEnv,priority);
	if (fPriority > priority) fout << ")";
	return fout;
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x) const
{
	return fout << funame << '(' << ppsig(x,fEnv) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y) const
{
	return fout << funame << '(' << ppsig(x,fEnv) << ',' << ppsig(y,fEnv) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z) const
{
	return fout << funame << '(' << ppsig(x,fEnv) << ',' << ppsig(y,fEnv) << ',' << ppsig(z,fEnv) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree zz) const
{
    return fout << funame << '(' << ppsig(x,fEnv) << ',' << ppsig(y,fEnv) << ',' << ppsig(z,fEnv) << ',' << ppsig(zz,fEnv) << ')';
}

ostream& ppsig::printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree z2, Tree z3) const
{
    return fout << funame << '(' << ppsig(x,fEnv) << ',' << ppsig(y,fEnv) << ',' << ppsig(z,fEnv) << ',' << ppsig(z2,fEnv) << ',' << ppsig(z3,fEnv) << ')';
}

ostream& ppsig::printui(ostream& fout, const string& funame, Tree label) const
{
	fout << funame << '(';
	printlabel(fout, label);
	return fout << ')';
}

ostream& ppsig::printui(ostream& fout, const string& funame, Tree label, Tree lo, Tree hi, Tree step) const
{
	fout << funame << '(';
	printlabel(fout, label);
	return fout 	
			<< ',' << ppsig(lo,fEnv) 
			<< ',' << ppsig(hi,fEnv) 
			<< ',' << ppsig(step,fEnv) 
			<< ')';
}

ostream& ppsig::printui(ostream& fout, const string& funame, Tree label, Tree cur, Tree lo, Tree hi, Tree step) const
{
	fout << funame << '(';
	printlabel(fout, label);
	return fout 	
			<< ',' << ppsig(cur,fEnv) 
			<< ',' << ppsig(lo,fEnv) 
			<< ',' << ppsig(hi,fEnv) 
			<< ',' << ppsig(step,fEnv) 
			<< ')';
}

ostream& ppsig::printout (ostream& fout, int i, Tree x) const
{
	if (fPriority > 0) fout << "(";
	fout << "OUT" << i << " = " << ppsig(x, fEnv, 0);	
	if (fPriority > 0) fout << ")";
	return fout;
}

ostream& ppsig::printlabel(ostream& fout, Tree pathname) const
{
	fout << *hd(pathname); 
	pathname = tl(pathname);
	while (!isNil(pathname)) { 
		fout << '/' << *tl(hd(pathname)); 
		pathname = tl(pathname);
	}
	return fout;
}

ostream& ppsig::printlist(ostream& fout, Tree largs) const
{
	string sep = "";
	fout << '('; 
	while (!isNil(largs)) { 
		fout << sep << ppsig(hd(largs), fEnv); 
		sep = ", ";
		largs = tl(largs);
	}
	fout << ')';
	return fout;
}

ostream& ppsig::printff(ostream& fout, Tree ff, Tree largs) const
{
	fout << ffname(ff); printlist(fout, largs);
	return fout;
}

ostream& ppsig::printFixDelay(ostream& fout, Tree exp, Tree delay) const
{
	int 	d;
	
	if (isSigInt(delay, &d) && (d==1)) {
		fout << ppsig(exp,fEnv,8) << "'";
	} else {
		printinfix(fout, "@", 8, exp, delay); 
	}
	return fout;
}

//	else if ( isSigFixDelay(sig, x, y) ) 			{ printinfix(fout, "@", 8, x, y); 	}

ostream& ppsig::printrec(ostream& fout, Tree var, Tree lexp, bool hide) const
{
	if (isElement(var, fEnv) ) {
		fout << *var;
	} else if (hide) {
		fout << *var;
	} else {
		fout << "letrec(" << *var << " = " << ppsig(lexp, addElement(var, fEnv)) << ")";
	}
	return fout;
}

ostream& ppsig::printrec(ostream& fout, Tree lexp, bool hide) const
{
	fout << "debruijn(" << ppsig(lexp,fEnv) << ")";
	return fout;
}

ostream& ppsig::printextended(ostream& fout, Tree sig) const
{
	string 		sep = "";
	xtended* 	p = (xtended*) getUserData(sig);
	
	fout << p->name() << '(';
	for (int i = 0; i < sig->arity(); i++) {
		fout << sep << ppsig(sig->branch(i), fEnv);
		sep = ", ";
	}
	fout << ')';
	return fout;
}
		
ostream& ppsig::print(ostream& fout) const
{
	int 	i;
	double	r;
    Tree 	c, sel, x, y, z, u, var, le, label, id, ff, largs, type, name, file, sf;

		  if ( isList(sig) ) 						{ printlist(fout, sig); }
	else if ( isProj(sig, &i, x) ) 					{ fout << "proj" << i << '(' << ppsig(x, fEnv) << ')';	}
	else if ( isRec(sig, var, le) )					{ printrec(fout, var, le, fHideRecursion /*&& (getRecursivness(sig)==0)*/ ); }

	// debruinj notation
	else if ( isRec(sig, le) )						{ printrec(fout, le, fHideRecursion ); }
	else if ( isRef(sig, i) )						{ fout << "REF[" << i << "]"; }
	
	else if ( getUserData(sig) ) 					{ printextended(fout, sig); }
	else if ( isSigInt(sig, &i) ) 					{ fout << i; }
    else if ( isSigReal(sig, &r) ) 					{ fout << T(r); }
    else if ( isSigWaveform(sig) )                  { fout << "waveform{...}"; }
    else if ( isSigInput(sig, &i) ) 				{ fout << "IN[" << i << "]"; }
	else if ( isSigOutput(sig, &i, x) ) 			{ printout(fout, i, x) ; }
	
	else if ( isSigDelay1(sig, x) ) 				{ fout << ppsig(x, fEnv, 9) << "'"; }
	//else if ( isSigFixDelay(sig, x, y) ) 			{ printinfix(fout, "@", 8, x, y); 	}
	else if ( isSigFixDelay(sig, x, y) ) 			{ printFixDelay(fout, x, y); 	}
	else if ( isSigPrefix(sig, x, y) ) 				{ printfun(fout, "prefix", x, y); }
	else if ( isSigIota(sig, x) ) 					{ printfun(fout, "iota", x); }
	else if ( isSigBinOp(sig, &i, x, y) )			{ printinfix(fout, gBinOpTable[i]->fName, gBinOpTable[i]->fPriority, x, y);  }
	else if ( isSigFFun(sig, ff, largs) )			{ printff(fout, ff, largs); }
    else if ( isSigFConst(sig, type, name, file) )  { fout << tree2str(name); }
    else if ( isSigFVar(sig, type, name, file) )    { fout << tree2str(name); }
	
	else if ( isSigTable(sig, id, x, y) ) 			{ printfun(fout, "TABLE", x, y); 		}
	else if ( isSigWRTbl(sig, id, x, y, z) )		{ printfun(fout, "write", x, y, z);	}
	else if ( isSigRDTbl(sig, x, y) )				{ printfun(fout, "read", x, y);	}
	else if ( isSigGen(sig, x) ) 					{ fout << ppsig(x, fEnv, fPriority); }

    else if ( isSigDocConstantTbl(sig, x, y) )      { printfun(fout, "docConstantTbl", x, y);	}
    else if ( isSigDocWriteTbl(sig, x, y, z, u) )   { printfun(fout, "docWriteTbl", x, y, z, u);	}
    else if ( isSigDocAccessTbl(sig, x, y) )        { printfun(fout, "docAccessTbl", x, y);	}

	else if ( isSigSelect2(sig, sel, x, y) ) 		{ printfun(fout, "select2", sel, x, y); }
	else if ( isSigSelect3(sig, sel, x, y, z) ) 	{ printfun(fout, "select3", sel, x, y, z); }
	
	else if ( isSigIntCast(sig, x) ) 				{ printfun(fout, "int", x); }
	else if ( isSigFloatCast(sig, x) )				{ printfun(fout, "float", x);  }
	
	else if ( isSigButton(sig, label) ) 			{ printui(fout, "button", label); }
	else if ( isSigCheckbox(sig, label) ) 			{ printui(fout, "checkbox", label);  }
	else if ( isSigVSlider(sig, label,c,x,y,z) )	{ printui(fout, "vslider", label, c, x, y, z); }
	else if ( isSigHSlider(sig, label,c,x,y,z) )	{ printui(fout, "hslider", label, c, x, y, z); }
	else if ( isSigNumEntry(sig, label,c,x,y,z) )	{ printui(fout, "nentry", label, c, x, y, z); }
	else if ( isSigVBargraph(sig, label,x,y,z) )	{ printui(fout, "vbargraph", label, x, y, z); }
	else if ( isSigHBargraph(sig, label,x,y,z) )	{ printui(fout, "hbargraph", label, x, y, z); }

    else if (isSigSoundfile(sig, label) )			{ printui(fout, "soundfile", label); }
    else if (isSigSoundfileLength(sig, sf) )		{ printfun(fout, "length", sf); }
    else if (isSigSoundfileRate(sig, sf) )	    	{ printfun(fout, "rate", sf); }
    else if (isSigSoundfileChannels(sig, sf))       { printfun(fout, "channels", sf); }
    else if (isSigSoundfileBuffer(sig,sf,x,y))      { printfun(fout, "buffer", sf, x, y); }

	else if ( isSigAttach(sig, x, y) )				{ printfun(fout, "attach", x, y); }
    else if ( isSigEnable(sig, x, y) )				{ printfun(fout, "enable", x, y); }
    else if ( isSigControl(sig, x, y) )				{ printfun(fout, "control", x, y); }

	else {
        stringstream error;
        error << "ERROR  in ppsig::print, not a signal : " << *sig << endl;
        throw faustexception(error.str());
	}
	return fout;
}

