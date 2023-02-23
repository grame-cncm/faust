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

#ifndef __OCCUR__
#define __OCCUR__

#include "garbageable.hh"
#include "tlib.hh"

/**
 * Count subtree occurrences
 * Count the number of occurrences of each subtree of a root tree.
 */

class Occur : public virtual Garbageable {
    Tree fKey;  // specific property key

   public:
    Occur(Tree root);     // count the occurrences of each subtree of root
    int getCount(Tree t);  // return the number of occurrences of t in root

   private:
    Tree specificKey(Tree root);    // specific key for occurrences counting in root
    void countOccurrences(Tree t);  // increment the occurrences of t and its subtrees
    void setCount(Tree t, int c);   // set the number of occurrences of t
};

#endif
