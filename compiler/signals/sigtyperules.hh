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



#ifndef _SIGTYPERULES_
#define _SIGTYPERULES_

#include "signals.hh"
#include "sigtype.hh"


//--------------------------------------------------------------------------
// NULLENV : empty type environment (also property key for closed term type)

extern Tree NULLENV;
extern bool gVectorSwitch;


//--------------------------------------------------------------------------
// addEnv : add a new binding to a type environment

Tree addEnv(Tree var, ::Type tp, Tree env);


//--------------------------------------------------------------------------
// searchEnv : search var binding in env

::Type searchEnv(Tree env, Tree var);


//--------------------------------------------------------------------------
//	getSigType : return or infere the type of a term

::Type getSigType(Tree term);


//--------------------------------------------------------------------------
//	typeAnnotation : annotate a term with type information

void typeAnnotation(Tree term);


//--------------------------------------------------------------------------
//	sigType : return the type information of a term

//Type sigType(Tree term);

#endif

