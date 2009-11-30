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
 
 
 
#ifndef _PROPAGATE_
#define _PROPAGATE_

#include <vector>
#include "boxes.hh"
#include "signals.hh"

////////////////////////////////////////////////////////////////////////
/**
 * boxPropagateSig : box listOfSignal-> listOfSignal'
 *
 * Propage une liste de signaux de l'entrÈe vers la sortie d'une boite
 * La boite ‡ ÈtÈ annotÈe aec son type
 */
///////////////////////////////////////////////////////////////////////
using namespace std;

typedef vector<Tree> siglist;

siglist makeSigInputList (int n);
Tree boxPropagateSig (Tree path, Tree box, const siglist& lsig);

//bool getSigListNickName (Tree t, Tree& id);
//void setSigListNickName (const siglist&  lsig, const string& nickname);


//siglist makeSigProjList (Tree t, int n);
//siglist lrepeat(int n, const siglist& l);
//siglist lmerge(int nbelems, int nblignes, Tree src);


/*
	exemple :
	Pour calculer 'lsig' la liste des signaux de sortie d'une boite 'box' 
	‡ n entrÈes on utilisera :
		lsig =  boxPropagateSig(box, makeSigInputList(n));
*/
#endif
