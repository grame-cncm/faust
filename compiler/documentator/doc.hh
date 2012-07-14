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

#ifndef _DOC_
#define _DOC_

/*****************************************************************************
******************************************************************************
							FAUST DOCUMENTATOR
						K. Barkati & Y. Orlarey, (c) Grame 2009
------------------------------------------------------------------------------

 History :
 ---------
 	2009-07-19 : First version

******************************************************************************
*****************************************************************************/

#include "tlib.hh"
#include "eval.hh"

/*****************************************************************************
******************************************************************************

							    The Documentator

******************************************************************************
*****************************************************************************/




/*****************************************************************************
							  Doc Types Creation & Test
*****************************************************************************/

Tree docTxt   (const char*);
Tree docEqn   (Tree x);
Tree docDgm	  (Tree x);
Tree docNtc	  ();
Tree docLst	  ();
Tree docMtd	  (Tree x);

bool isDocTxt	(Tree t);
bool isDocTxt	(Tree t, const char**);
bool isDocEqn	(Tree t, Tree& x);
bool isDocDgm	(Tree t, Tree& x);
bool isDocNtc	(Tree t);
bool isDocLst	(Tree t);
bool isDocMtd	(Tree t);

/*****************************************************************************
							  Printing Public Function
*****************************************************************************/

void printDoc(const char* projname, const char* docdev, const char* faustversion);

#endif
