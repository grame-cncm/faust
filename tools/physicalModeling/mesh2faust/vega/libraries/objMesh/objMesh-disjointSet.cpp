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

#include <stdio.h>
#include <stdlib.h>
#include "objMesh-disjointSet.h"

DisjointSet::DisjointSet(int num):disjointSetParent(NULL),size(0)
{
  Resize(num);
}

DisjointSet::~DisjointSet(void)
{
  Destroy();
}

void DisjointSet::MakeSet(void)
{
  for(int i=0; i<size; i++)
    disjointSetParent[i] = -1;  // each object is initially a root of a tree
}

void DisjointSet::Resize(int num)
{
  if (num < 0)
  {
    printf("Error in DisjointSet::Resize(int num): problem scale cannot be negtive.\n");
    exit(0);
  }
  if (size >= num)
    return;

  if (size != 0)
    free(disjointSetParent);
  size = num;
  disjointSetParent = (int *) malloc (sizeof(int) * size);
}

void DisjointSet::Destroy(void)
{
  if (size == 0)
    return;
  size = 0;
  free(disjointSetParent);
  disjointSetParent = NULL;
}

int DisjointSet::FindSet(int x)
{
  if (x < 0 || x >= size)
  {
    printf("Error in DisjointSet::FindSet(int x): the x value is illegal.\n");
    exit(0);
  }
  int ancestor = x;
  while(disjointSetParent[ancestor] >= 0) 
    ancestor = disjointSetParent[ancestor];  // backtrack the ancestor
  //path compression
  while(x != ancestor)
  {
    int temp = disjointSetParent[x];
    disjointSetParent[x] = ancestor;
    x = temp;
  }
  return ancestor;  // here ancestor should be >=0
}

void DisjointSet::UnionSet(int x, int y)
{
  if (x < 0 || x >= size)
  {
    printf("Error in DisjointSet::UnionSet(int x, int y): the x value is illegal.\n");
    exit(0);
  }
  if (y < 0 || y >= size)
  {
    printf("Error in DisjointSet::UnionSet(int x, int y): the y value is illegal.\n");
    exit(0);
  }
  int ancestor1 = FindSet(x);
  int ancestor2 = FindSet(y);
  if (ancestor1 == ancestor2)
    return; // they are already in the same set

  if (disjointSetParent[ancestor1] < disjointSetParent[ancestor2]) // size of set 1 is larger
  {
    disjointSetParent[ancestor1] += disjointSetParent[ancestor2];
    disjointSetParent[ancestor2] = ancestor1;
  }
  else  // size of set 2 is larger or equal to the size of set 1
  {
    disjointSetParent[ancestor2] += disjointSetParent[ancestor1];
    disjointSetParent[ancestor1] = ancestor2;
  }
}

