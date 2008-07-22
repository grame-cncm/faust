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



/*****************************************************************************
******************************************************************************
							FAUST SIGNAL COMPILER
						Y. Orlarey, (c) Grame 2002
------------------------------------------------------------------------------
Compile a list of FAUST signals into a C++ class .

 History :
 ---------
 	2002-02-08 : First version

******************************************************************************
*****************************************************************************/



#include <stdio.h>

#include "compile_vect.hh"
#include "compile_scal.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "sigprint.hh"



/*****************************************************************************
******************************************************************************

						   		SHARING ANALYSIS

******************************************************************************
*****************************************************************************/

//------------------------------------------------------------------------------
// Create a specific property key for the sharing count of subtrees of t
//------------------------------------------------------------------------------

int ScalarCompiler::getSharingCount(Tree sig)
{
	//cerr << "getSharingCount of : " << *sig << " = ";
	Tree c;
	if (getProperty(sig, fSharingKey, c)) {
		//cerr << c->node().getInt() << endl;
		return c->node().getInt();
	} else {
		//cerr << 0 << endl;
		return 0;
	}
}

void ScalarCompiler::setSharingCount(Tree sig, int count)
{
	//cerr << "setSharingCount of : " << *sig << " <- " << count << endl;
	setProperty(sig, fSharingKey, tree(count));
}



//------------------------------------------------------------------------------
// Create a specific property key for the sharing count of subtrees of t
//------------------------------------------------------------------------------


void ScalarCompiler::sharingAnalysis(Tree t)
{
	fSharingKey = shprkey(t);
	if (isList(t)) {
		while (isList(t)) {
			sharingAnnotation(kSamp, hd(t));
			t = tl(t);
		}
	} else {
		sharingAnnotation(kSamp, t);
	}
}



//------------------------------------------------------------------------------
// Create a specific property key for the sharing count of subtrees of t
//------------------------------------------------------------------------------
void ScalarCompiler::sharingAnnotation(int vctxt, Tree sig)
{
	//cerr << "START sharing annotation of " << *sig << endl;
	int count = getSharingCount(sig);

	if (count > 0) {
		// it is not our first visit
		setSharingCount(sig, count+1);

	} else {
		// it is our first visit,
		int v = getSigType(sig)->variability();

		// check "time sharing" cases
		if (v < vctxt) {
			setSharingCount(sig, 2); 	// time sharing occurence : slower expression in faster context
		} else {
			setSharingCount(sig, 1);	// regular occurence
		}

		// Annotate the sub signals
		vector<Tree> subsig;
		int n = getSubSignals(sig, subsig);
		if (n>0 && ! isSigGen(sig)) {
			for (int i=0; i<n; i++) sharingAnnotation(v, subsig[i]);
		}
	}
	//cerr << "END sharing annotation of " << *sig << endl;
}


#if 0

void VectorCompiler::sharingAnnotation(int vctxt, Tree t, int ctxt)
{
        Tree    tt;
// 	fprintf (stderr, "Start sharing annotation of ");
// 	printSignal (t, stderr);
// 	cerr << "in context " << vctxt << endl;

	int cVect = getSharingCount(t,kVect);
	int cScal = getSharingCount(t,kScal);
	int cTrueScal = getSharingCount(t,kTrueScal);


	int type=0;

	if ((cVect==0)&&(cScal==0)&&(cTrueScal==0)) {

	  if (getProperty(t, NULLENV, tt)) {


	    Type ty((AudioType*)tree2ptr(tt));

	  //Type ty = getSigType(t,NULLENV);

	    int v = ty->variability();
	    if (v < vctxt) {

	      cVect = 1;
	      cScal = 1;
	      if(ctxt==kVect) setProperty(t, fSharingKeyScal, tree(cScal+1));
	      else if(ctxt==kScal) setProperty(t, fSharingKeyVec, tree(cVect+1));

	      //c = 1;
	      vctxt = v;
	    }
	  }

	    int n = t->arity();
	    if (n>0 && ! isSigGen(t)) {

	      Tree x,y,ff,largs,id,z,label,le;

	      //int type;
	      if (getProperty(t, NULLENV, tt)) {
		Type ty = ((AudioType*)tree2ptr(tt));
		type = ty->vectorability();
	      }

	      if(vctxt<kSamp) for (int i=0; i<n; i++) sharingAnnotation(vctxt, t->branch(i),kTrueScal);
	      else if(isSigRDTbl(t,x,y)||isSigFFun(t,ff,largs)) for (int i=0; i<n; i++) sharingAnnotation(vctxt, t->branch(i),kTrueScal);
	      else if(isSigWRTbl(t,id,x,y,z)) { sharingAnnotation(vctxt, t->branch(0),kTrueScal); sharingAnnotation(vctxt, t->branch(1),kTrueScal); sharingAnnotation(vctxt, t->branch(2),kTrueScal); sharingAnnotation(vctxt, t->branch(3),kScal); }
	      else if(isRec(t,label,le)||isRef(t,label)) for (int i=0; i<n; i++) sharingAnnotation(vctxt, t->branch(i),kScal);

	      else if(ctxt==kTrueScal) for (int i=0; i<n; i++) sharingAnnotation(vctxt, t->branch(i),type); // et forcï¿½ment vctxt == kSamp
	      else for (int i=0; i<n; i++) sharingAnnotation(vctxt, t->branch(i),ctxt|type);



	      //for (int i=0; i<n; i++) sharingAnnotation(vctxt, t->branch(i),ctxt); // ATTENTION CHANGER ctxt SUIVANT LE SIGNAL

	    }




	}



	if((!getProperty(t, NULLENV, tt))||(ctxt==type)) {
	  if(ctxt==kVect) setProperty(t, fSharingKeyVec, tree(cVect+1));
	  else if(ctxt==kScal) setProperty(t, fSharingKeyScal, tree(cScal+1));
	  else setProperty(t, fSharingKeyTrueScal, tree(cTrueScal+1));
	} else {
	  if(ctxt==kVect) setProperty(t, fSharingKeyVec, tree(cVect+1));
	  else if(ctxt==kScal) setProperty(t, fSharingKeyScal, tree(cScal+1));
	  else setProperty(t, fSharingKeyTrueScal, tree(cTrueScal+1));

	  if(type==kVect) setProperty(t, fSharingKeyVec, tree(cVect+1));
	  else if(type==kScal) setProperty(t, fSharingKeyScal, tree(cScal+1));
	  //else setProperty(t, fSharingKeyTrueScal, tree(cTrueScal+1));
	}


	//if((!getProperty(t, NULLENV, tt))||(ctxt==type)) {
	//  if(ctxt==kVect) fprintf(stderr,"Sharing annotation: %d %d %d\n", cVect+1, cScal, cTrueScal );
	//  else if(ctxt==kScal) fprintf(stderr,"Sharing annotation: %d %d %d\n", cVect, cScal+1, cTrueScal );
	//  else fprintf(stderr,"Sharing annotation: %d %d %d\n", cVect, cScal, cTrueScal+1 );
	//  fprintf(stderr,"for signal: "); printSignal(t,stderr); fprintf(stderr,"\n\n");
	//} else {
	//  if((ctxt==kVect)&&(type==kScal)) fprintf(stderr,"Sharing annotation: %d %d %d\n", cVect+1, cScal+1, cTrueScal );
	//  else if((ctxt==kScal)&&(type==kVect)) fprintf(stderr,"Sharing annotation: %d %d %d\n", cVect+1, cScal+1, cTrueScal );
	//  else fprintf(stderr,"Sharing annotation: %d %d %d\n", cVect, cScal, cTrueScal+1 );
	//  fprintf(stderr,"for signal: "); printSignal(t,stderr); fprintf(stderr,"\n\n");
	//}
}


#endif
