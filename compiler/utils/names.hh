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
 
#ifndef __NAMES__
#define __NAMES__
 
#include "tlib.hh"
#include "propagate.hh"
#include <string>

using namespace std;

/** 						
 * \file names.hh 
 *
 * Interface for names management.
 *
 **/
 
/**
 * Indicates the identifier (if any) the expression was a definition of.
 * @param t the expression 
 * @param id reference to the identifier 
 * @return true if the expression t was a definition of id
 **/
 
bool 	getDefNameProperty(Tree t, Tree& id);

void 	setDefNameProperty(Tree t, Tree id);
void 	setDefNameProperty(Tree t, const string& name);

//bool getSigListNickName (Tree t, Tree& id);
//void setSigListNickName (const siglist&  lsig, const string& nickname);

void setSigListNickName (Tree lsig, const string& nickname);

void setSigNickname(Tree t, const string& id);
bool getSigNickname(Tree t, Tree& id);


/**
 * Push a new layer and add a single definition.
 * @param id the symbol id to be defined
 * @param def the definition to be binded to the symbol id
 * @param lenv the environment where to push the layer and add the definition
 * @return the new environment
 */
Tree pushValueDef(Tree id, Tree def, Tree lenv);

/* numeric simplification of pattern arguments */
Tree simplifyPattern (Tree pattern);

#endif
