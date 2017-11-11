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

#ifndef __SIGVISITOR__
#define __SIGVISITOR__

#include "signals.hh"

struct sigvisitor 
{
	// predefined visit scheme
	void visit(Tree sig);
	
	// Unrecognized signal (default handler)
	virtual void visitError(Tree sig);
	
	virtual ~sigvisitor() {}
	
	//---------------abstract methods---------------
	// numbers
	virtual void visitInt		(Tree sig, int i) = 0;
	virtual void visitReal		(Tree sig, double r) = 0;
	
	// audio inputs-outputs
	virtual void visitInput		(Tree sig, int i) = 0;
	virtual void visitOutput	(Tree sig, int i, Tree s) = 0;
	
	// fixed size delays
	virtual void visitDelay1	(Tree sig, Tree s) = 0;
	virtual void visitPrefix	(Tree sig, Tree s1, Tree s2) = 0;
	virtual void visitFixDelay	(Tree sig, Tree s1, Tree s2) = 0;
	
	// numerical operations	
	virtual void visitBinOp		(Tree sig, int opcode, Tree s1, Tree s2) = 0;
	virtual void visitIntCast	(Tree sig, Tree s) = 0;
	virtual void visitFloatCast	(Tree sig, Tree s) = 0;
	virtual void visitFFun		(Tree sig, Tree ff, Tree ls) = 0;
    virtual void visitFConst    (Tree sig, Tree type, Tree name, Tree file) = 0;
    virtual void visitFVar      (Tree sig, Tree type, Tree name, Tree file) = 0;
	
	// user interface
	virtual void visitButton 	(Tree sig, Tree label) = 0;
	virtual void visitCheckbox 	(Tree sig, Tree label) = 0;
	virtual void visitVSlider	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step) = 0;
	virtual void visitHSlider	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step) = 0;
	virtual void visitNumEntry	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step) = 0;
	virtual void visitVBargraph	(Tree sig, Tree label, Tree min, Tree max, Tree s1) = 0;
	virtual void visitHBargraph	(Tree sig, Tree label, Tree min, Tree max, Tree s1) = 0;
    virtual void visitAttach	(Tree sig, Tree s1, Tree s2) = 0;
    virtual void visitEnable    (Tree sig, Tree s1, Tree s2) = 0;
    virtual void visitControl   (Tree sig, Tree s1, Tree s2) = 0;

	// recursive
	virtual void visitRec 		(Tree sig, Tree var, Tree body) = 0;
 	virtual void visitRef 		(Tree sig, Tree var) = 0; 
 	virtual void visitProj		(Tree sig, int i, Tree s1) = 0;
	
	// Tables
	virtual void visitTable		(Tree sig, Tree id, Tree s1, Tree s2) = 0;
	virtual void visitWRTbl		(Tree sig, Tree id, Tree s1, Tree s2, Tree s3) = 0;
	virtual void visitRDTbl		(Tree sig, Tree s1, Tree s2) = 0;  
	virtual void visitGen		(Tree sig, Tree s1) = 0;

    virtual void visitDocConstantTbl	(Tree sig, Tree s1, Tree s2) = 0;
    virtual void visitDocWriteTbl		(Tree sig, Tree s1, Tree s2, Tree s3, Tree s4) = 0;
    virtual void visitDocAccessTbl		(Tree sig, Tree s1, Tree s2) = 0;

	// Selectors
	virtual void visitSelect2	(Tree sig, Tree sel, Tree s1, Tree s2) = 0; 
	virtual void visitSelect3	(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3) = 0; 

	// Tuples
	virtual void visitTuple			(Tree sig, int mod, Tree ls) = 0; 
	virtual void visitTupleAccess	(Tree sig, Tree ts, Tree idx) = 0; 
	
	// List of signals
	virtual void visitList		(Tree lsig) = 0;
};

struct fullvisitor : sigvisitor
{
	// numbers
	virtual void visitInt		(Tree sig, int i) 								{}
	virtual void visitReal		(Tree sig, double r) 							{}
	
	// audio inputs-outputs
	virtual void visitInput		(Tree sig, int i)								{}
	virtual void visitOutput	(Tree sig, int i, Tree s) 						{ visit(s);}
	
	// fixed size delays
	virtual void visitDelay1	(Tree sig, Tree s)  							{ visit(s);}
	virtual void visitPrefix	(Tree sig, Tree s1, Tree s2)					{ visit(s1); visit(s2); }
	virtual void visitFixDelay	(Tree sig, Tree s1, Tree s2)  					{ visit(s1); visit(s2); }
	
	// numerical operations	
	virtual void visitIntCast	(Tree sig, Tree s) 								{ visit(s);}
	virtual void visitFloatCast	(Tree sig, Tree s) 								{ visit(s);}
	virtual void visitBinOp		(Tree sig, int op, Tree s1, Tree s2) 			{ visit(s1); visit(s2); }
	virtual void visitFFun		(Tree sig, Tree ff, Tree ls) 					{ visit(ls); }
    virtual void visitFConst    (Tree sig, Tree type, Tree name, Tree file)     {}
    virtual void visitFVar      (Tree sig, Tree type, Tree name, Tree file)     {}
	
	// user interface
	virtual void visitButton 	(Tree sig, Tree label) 							{}
	virtual void visitCheckbox 	(Tree sig, Tree label) 							{}
	virtual void visitVSlider	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step) {}
	virtual void visitHSlider	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step) {}
	virtual void visitNumEntry	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step) {}
	virtual void visitVBargraph	(Tree sig, Tree label, Tree min, Tree max, Tree s) { visit(s);}
	virtual void visitHBargraph	(Tree sig, Tree label, Tree min, Tree max, Tree s) { visit(s);}
	virtual void visitAttach	(Tree sig, Tree s1, Tree s2) 					{ visit(s1); visit(s2); }
	
	// recursive
	virtual void visitRec 		(Tree sig, Tree var, Tree body) 				{ visit(body); }
 	virtual void visitRef 		(Tree sig, Tree var) 							{} 
 	virtual void visitProj		(Tree sig, int i, Tree s) 						{ visit(s); }
	
	// Tables
	virtual void visitTable		(Tree sig, Tree id, Tree s1, Tree s2) 			{ visit(s1); visit(s2); }
	virtual void visitWRTbl		(Tree sig, Tree id, Tree s1, Tree s2, Tree s3) 	{ visit(s1); visit(s2); visit(s3); }
	virtual void visitRDTbl		(Tree sig, Tree s1, Tree s2) 					{ visit(s1); visit(s2); }  
	virtual void visitGen		(Tree sig, Tree s1) 							{ visit(s1); }
	
	// Selectors
	virtual void visitSelect2	(Tree sig, Tree sel, Tree s1, Tree s2) 			{ visit(sel); visit(s1); visit(s2); } 
	virtual void visitSelect3	(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3) { visit(sel); visit(s1); visit(s2); visit(s3); } 

	// Tuples
	virtual void visitTuple			(Tree sig, int mod, Tree ls)				{ visit(ls); }
	virtual void visitTupleAccess	(Tree sig, Tree ts, Tree idx)				{ visit(ts); visit(idx); }

	// List of signals
	virtual void visitList		(Tree lsig) 									{ while (!isNil(lsig)) { visit(hd(lsig)); lsig=tl(lsig); }}
};

#endif
