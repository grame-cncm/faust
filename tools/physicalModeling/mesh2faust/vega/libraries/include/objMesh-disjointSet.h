/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "objMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC        *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Yili Zhao, Jernej Barbic                                *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Research: Jernej Barbic, Fun Shing Sin, Daniel Schroeder,             *
 *           Doug L. James, Jovan Popovic                                *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
 *          Singapore-MIT GAMBIT Game Lab,                               *
 *          Zumberge Research and Innovation Fund at USC                 *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of the BSD-style license that is            *
 * included with this library in the file LICENSE.txt                    *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the file     *
 * LICENSE.TXT for more details.                                         *
 *                                                                       *
 *************************************************************************/

/*
  "Disjoint set", a union-find data structure 
  that keeps track of a set of elements partitioned into a number of disjoint (non-overlapping) subsets.

  Operations:
  1) MakeSet: Make each set containing only a given element.
  2) Find: Determine which set a particular element is in. Also useful for determining if two elements are in the same set.
  3) Union: Combine or merge two sets into a single set.

  Heuristics such as path compression etc. have been implemented.
*/

#ifndef _DISJOINT_SET_H_
#define _DISJOINT_SET_H_

class DisjointSet
{
public:

  // constructor
  DisjointSet(int num=0); // 'num' is the total number of elements

  // destructor
  ~DisjointSet();

  // resizes the data structure to have size 'num'
  void Resize(int num);

  // makes each element be its own set (usually the first operation after the constructor)
  void MakeSet(); 

  // returns the representative of the set that x belongs to (path compression is implemented in this function as well)
  int FindSet(int x);

  // merge two sets (the smaller one will be absorbed by the larger one)
  // x and y can be arbitrary elements, they need not be representatives
  void UnionSet(int x, int y);

protected:
  int * disjointSetParent;
  int size;

  enum {NO_SUCCESSOR = -1};

  // destroys the data structure
  void Destroy();
};

#endif

