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

#ifndef __OCCURRENCES__
#define __OCCURRENCES__

#include <map>

#include "garbageable.hh"
#include "tlib.hh"

class Occurrences : public virtual Garbageable {
    const int fXVariability;    ///< Extended Variability of the expression
    int       fOccurrences[4];  ///< Occurrences count according to Contexts
    bool      fMultiOcc;        ///< True when exp has multiple occ. or occ. in higher ctxt
    bool      fOutDelayOcc;     ///< True when exp has at least one occ. outside a delay
    int       fMinDelay;        ///< Minimal fix delay usage
    int       fMaxDelay;        ///< Maximal fix delay usage
    int       fCountDelay;      ///< number of times this sig occurs delay
    Tree      fExecCondition;   ///< When this expression must be computed

   public:
    Occurrences(int v, int r, Tree xc);
    Occurrences* incOccurrences(int v, int r, int d, Tree xc);  ///< inc occurrences in context v,r,d,xc

    bool hasMultiOccurrences() const;     ///< true if multiple occurrences or occ. in higher ctxt
    bool hasOutDelayOccurrences() const;  ///< true if has occurrences outside a a delay
    int  getMaxDelay() const;             ///< return the maximal delay collected
    int  getMinDelay() const;             ///< return the minimal delay collected
    int  getDelayCount() const;
    Tree getExecCondition() const;              ///< return the exec condition
    int  getOccurrence(int variability) const;  ///< return the number of occurrence by variability
};

/**
 * Occurrences Markup of a root tree. First create an OccMarkup om,
 * second om.mark(root) then om.retrieve(subtree)
 */
class OccMarkup : public virtual Garbageable {
    Tree                 fRootTree;    ///< occurrences computed within this tree
    Tree                 fPropKey;     ///< key used to store occurrences property
    std::map<Tree, Tree> fConditions;  ///< condition associated to each tree

    void         incOcc(Tree env, int v, int r, int d, Tree xc, Tree t);  ///< inc the occurrence of t in context v,r
    Occurrences* getOcc(Tree t);                                          ///< get Occurrences property of t or null
    void         setOcc(Tree t, Occurrences* occ);                        ///< set Occurrences property of t

   public:
    OccMarkup() : fRootTree(nullptr), fPropKey(nullptr) {}
    OccMarkup(std::map<Tree, Tree> conditions) : fRootTree(nullptr), fPropKey(nullptr), fConditions(conditions) {}

    void         mark(Tree root);   ///< start markup of root tree with new unique key
    Occurrences* retrieve(Tree t);  ///< occurrences of subtree t within root tree
};

#endif
