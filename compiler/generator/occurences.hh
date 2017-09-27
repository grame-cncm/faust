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

#ifndef __OCCURENCES__
#define __OCCURENCES__

#include "tlib.hh"
#include "garbageable.hh"

class Occurences : public virtual Garbageable
{
    const int 	fXVariability;		///< Extended Variability of the expression
    int         fOccurences[4];		///< Occurences count according to Contexts
    bool		fMultiOcc;			///< True when exp has multiple occ. or occ. in higher ctxt
    bool		fOutDelayOcc;		///< True when exp has at least one occ. outside a delay
    int			fMinDelay;			///< Minimal fix delay usage
    int			fMaxDelay;			///< Maximal fix delay usage
    
public:
    Occurences(int v, int r);
    
    Occurences* incOccurences(int v, int r, int d);	///< inc occurences in context v,r,d
    
    bool 		hasMultiOccurences() const;			///< true if multiple occurences or occ. in higher ctxt
    bool 		hasOutDelayOccurences() const;		///< true if has occurences outside a a delay
    int			getMaxDelay() const;				///< return the maximal delay collected
    int			getMinDelay() const;				///< return the minimal delay collected
};

/**
 * Occurences Markup of a root tree. First create an OccMarkup om,
 * second om.mark(root) then om.retrieve(subtree)
 */
class OccMarkup : public virtual Garbageable
{
    Tree 		fRootTree;								///< occurences computed within this tree
    Tree		fPropKey;								///< key used to store occurences property
    
    void 		incOcc (Tree env, int v, int r, int d, Tree t);	///< inc the occurence of t in context v,r
    Occurences* getOcc (Tree t);						///< get Occurences property of t or null
    void 		setOcc (Tree t, Occurences* occ);		///< set Occurences property of t
    
public:
    OccMarkup():fRootTree(NULL), fPropKey(NULL)
    {}
    void 		mark(Tree root);						///< start markup of root tree with new unique key
    Occurences* retrieve(Tree t);						///< occurences of subtree t within root tree
};

#endif
