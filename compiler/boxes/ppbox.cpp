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
 
 
 
#include "list.hh"
#include "boxes.hh"
#include "ppbox.hh"
#include "signals.hh"
#include "prim2.hh"


char * prim0name(CTree *(*ptr) ())
{
	return "prim0???";
}

char * prim1name(CTree *(*ptr) (CTree *))
{
	if (ptr == sigDelay1) return "mem";
	if (ptr == sigIntCast) return "int";
	if (ptr == sigFloatCast) return "float";
	return "prim1???";
}

char * prim2name(CTree *(*ptr) (CTree *, CTree *))
{
	if (ptr == sigAdd) return "+";
	if (ptr == sigSub) return "-";
	if (ptr == sigMul) return "*";
	if (ptr == sigDiv) return "/";
	if (ptr == sigRem) return "%";
	
	if (ptr == sigAND) return "&";
	if (ptr == sigOR ) return "|";
	if (ptr == sigXOR) return "^";
	
	if (ptr == sigLeftShift ) return "<<";
	if (ptr == sigRightShift) return ">>";
	
	if (ptr == sigLT) return "<";
	if (ptr == sigLE) return "<=";
	if (ptr == sigGT) return ">";
	if (ptr == sigGE) return ">=";
	if (ptr == sigEQ) return "==";
	if (ptr == sigNE) return "!=";

	if (ptr == sigFixDelay) return "@";
	
	return "prim2???";
}

char * prim3name(CTree *(*ptr) (CTree *, CTree *, CTree *))
{
	if (ptr == sigReadOnlyTable) 	return "rdtable";
	if (ptr == sigSelect2) 			return "select2";	
	return "prim3???";
}

char * prim4name(CTree *(*ptr) (CTree *, CTree *, CTree *, CTree *))
{
	if (ptr == sigSelect3) 			return "select3";	
	return "prim4???";
}

char * prim5name(CTree *(*ptr) (CTree *, CTree *, CTree *, CTree *, CTree *))
{
	if (ptr == sigWriteReadTable) 			return "wrtable";	
	return "prim5???";
}


static void streambinop(ostream& fout, Tree t1, char* op, Tree t2, int curPriority, int upPriority)
{
	if (upPriority > curPriority) fout << '(';
	fout << boxpp(t1,curPriority) << op << boxpp(t2,curPriority);
	if (upPriority > curPriority) fout << ')';
}

/*****************************************************************************
	 affichage d'une expression box comme en entrée
*****************************************************************************/

ostream& boxpp::print (ostream& fout) const
{
	int		i;
	float	r;
	prim0	p0;
	prim1	p1;
	prim2	p2;
	prim3	p3;
	prim4	p4;
	prim5	p5;

	Tree	t1, t2, t3, ff, label, cur, min, max, step, type, name, file, arg, 
			body, fun, args, abstr, genv, vis, lenv;
	
	const char* str;
	
	
	// primitive elements
	     if (isBoxInt(box, &i))			fout << i; 
	else if (isBoxReal(box, &r))		fout << r; 
	else if (isBoxCut(box))				fout << '!'; 
	else if (isBoxWire(box))			fout << '_'; 
	else if (isBoxIdent(box, &str))		fout << str; 
	else if (isBoxPrim0(box, &p0))		fout << prim0name(p0);  
	else if (isBoxPrim1(box, &p1))		fout << prim1name(p1);  
	else if (isBoxPrim2(box, &p2))		fout << prim2name(p2);  
	else if (isBoxPrim3(box, &p3))		fout << prim3name(p3);  
	else if (isBoxPrim4(box, &p4))		fout << prim4name(p4);  
	else if (isBoxPrim5(box, &p5))		fout << prim5name(p5); 
	
	else if (isBoxAbstr(box, arg,body))	fout << "\\" << boxpp(arg) << ".(" << boxpp(body) << ")"; 
	else if (isBoxAppl(box, fun, args))	fout << boxpp(fun) << boxpp(args) ; 
	
	// foreign elements 
	else if (isBoxFFun(box, ff))		fout << "ffunction(" << ffname(ff) << ')'; 
	else if (isBoxFConst(box, type, name, file))		
										fout << "fconstant(" << tree2str(type) << tree2str(name) << ')'; 
	
	// block diagram binary operator 
	else if (isBoxSeq(box, t1, t2))		streambinop(fout, t1, ":", t2, 1, priority);
	else if (isBoxSplit(box, t1, t2))	streambinop(fout, t1, "<:", t2, 1, priority);
	else if (isBoxMerge(box, t1, t2)) 	streambinop(fout, t1, ":>", t2, 1, priority);
	else if (isBoxPar(box, t1, t2)) 	streambinop(fout, t1,",",t2, 2, priority);
	else if (isBoxRec(box, t1, t2)) 	streambinop(fout, t1,"~",t2, 4, priority);
	
	// iterative block diagram construction
	else if (isBoxIPar(box, t1, t2, t3)) 	fout << "par(" << boxpp(t1) << ", " << boxpp(t2) << ") {" << boxpp(t3) << "}";
	else if (isBoxISeq(box, t1, t2, t3)) 	fout << "seq(" << boxpp(t1) << ", " << boxpp(t2) << ") {" << boxpp(t3) << "}";
	else if (isBoxISum(box, t1, t2, t3)) 	fout << "sum(" << boxpp(t1) << ", " << boxpp(t2) << ") {" << boxpp(t3) << "}";
	else if (isBoxIProd(box, t1, t2, t3)) 	fout << "prod(" << boxpp(t1) << ", " << boxpp(t2) << ") {" << boxpp(t3) << "}";
	
	// user interface
	else if (isBoxButton(box, label))	fout << "button(" << tree2str(label) << ')';  
	else if (isBoxCheckbox(box, label))	fout << "checkbox(" << tree2str(label) << ')';  
	else if (isBoxVSlider(box, label, cur, min, max, step)) 	{ 
		fout << "vslider(" 
			 << tree2str(label) << ", "
			 << tree2float(cur) << ", "
			 << tree2float(min) << ", "
			 << tree2float(max) << ", "
			 << tree2float(step)<< ')';  
	}
	else if (isBoxHSlider(box, label, cur, min, max, step)) 	{ 
		fout << "hslider(" 
			 << tree2str(label) << ", "
			 << tree2float(cur) << ", "
			 << tree2float(min) << ", "
			 << tree2float(max) << ", "
			 << tree2float(step)<< ')';  
	}
	else if (isBoxVGroup(box, label, t1)) {
		fout << "vgroup(" << tree2str(label) << ", " << boxpp(t1, 0) << ')';
	}
	else if (isBoxHGroup(box, label, t1)) {
		fout << "hgroup(" << tree2str(label) << ", " << boxpp(t1, 0) << ')';
	}
	else if (isBoxTGroup(box, label, t1)) {
		fout << "tgroup(" << tree2str(label) << ", " << boxpp(t1, 0) << ')';
	}
	else if (isList(box)) {
		
		Tree l = box;
		char sep = '(';
		
		do {
			fout << sep << boxpp(hd(l)); 
			sep = ',';
			l = tl(l);
		} while (isList(l));
		
		fout << ')';
		
	}
	else if (isClosure(box, abstr, genv, vis, lenv)) {
		fout << "closure[" << boxpp(abstr) 
			<< ", genv = " << envpp(genv) 
			<< ", lenv = " << envpp(lenv)
			<< "]";
	}
	//a completer
	else {
		//fout << tree2str(box);
		fout << "not_a_box[[  " << *box << " ]]";
	}

	return fout;
}


/*****************************************************************************
	 affichage d'un environnement
*****************************************************************************/

ostream& envpp::print (ostream& fout) const
{
		char* 	sep = "";
		Tree 	l = fEnv;
		
		fout << '{';
		while (isList(l)) {
			fout << sep << boxpp(hd(hd(l))) << "=" << boxpp(tl(hd(l)));
			sep = ", ";
			l = tl(l);
		} 
		fout << '}';
	return fout;
}

