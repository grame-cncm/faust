/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "objMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC        *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Christopher Twigg, Daniel Schroeder      *
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

#ifndef _OCTREE_H_
#define _OCTREE_H_

//  An octree storing triangles. Can be intersected with a sphere or a line segment. 
//  Jernej Barbic, CMU

#include <vector>
#include "minivector.h"
#include "boundingBox.h"
#include "triangle.h"
#include "simpleSphere.h"

template<class TriangleClass> 
class Octree 
{
public:
  // make empty octree
  // maxDepth = maximum tree depth allowed
  // depth = how deep in the hierarchy is this octree (for recursion) (you should use depth=0 when using this class; non-zero values are only passed internally)
  Octree(int maxDepth=10, int depth=0);
  ~Octree() { deallocate(); }

  bool build(std::vector<TriangleClass> & triangleList, BoundingBox & parentCube, int maxNumTriangles);

  // will construct a bounding box automatically:
  bool build(std::vector<TriangleClass> & triangleList, int maxNumTriangles);
  void setBuildPrintInfo(int info); // controls what gets printed out during construction: 0 = nothing, 1 = up to five warnings, 2 = all warnings
  void getBuildInfo(int * numMaxDepthExceededCases, int * numMaxTriInDepthExceededCases);

  // note: these two routines might return the same colliding triangle several times; call <TriangleClass>::makeUniqueList to make the list unique if needed
  void buildCollisionList(std::vector<TriangleClass*> & triangleList, const SimpleSphere & simpleSphere);
  void buildCollisionList(std::vector<TriangleClass*> & triangleList, const Vec3d & segmentStartPoint, const Vec3d & segmentEndPoint, std::vector<Vec3d> * intersectionList = NULL);

  void render(); // openGL rendering
  void render(int level); // only render leaf boxes at depth level 'level'
  void render(int level, int boxIndex); // only render leaf boxes number "boxIndex" at depth level 'level'
  void setRenderInfo(int info) { printRenderInfo = info; }

  int getDepth(); // compute tree depth
  BoundingBox getBoundingBox() { return boundingBox; }

protected:

  void deallocate(); // free the memory
  void createChildCubes(BoundingBox * childCubeBoxes);

  BoundingBox boundingBox;
  Octree * childrenNodes[8];

  int maxDepth; // max depth allowed
  int depth; // how deep in the hierarchy is this octree

  void renderHelper(int level, int boxIndex); // only render leaf boxes number "boxIndex" at depth level 'level'
  static int renderCounter; // for rendering
  static int printRenderInfo;

  std::vector<TriangleClass> triangles;

  static int buildPrintInfo;
  static int numMaxDepthExceededCases;
  static int numMaxTriInDepthExceededCases;
};

template<class TriangleClass>
inline void Octree<TriangleClass>::getBuildInfo(int * numMaxDepthExceededCases, int * numMaxTriInDepthExceededCases)
{
  *numMaxDepthExceededCases = this->numMaxDepthExceededCases;
  *numMaxTriInDepthExceededCases = this->numMaxTriInDepthExceededCases;
}

template<class TriangleClass>
inline void Octree<TriangleClass>::setBuildPrintInfo(int info)
{
  buildPrintInfo = info;
  if (info == 1)
  {
    numMaxDepthExceededCases = 0;
    numMaxTriInDepthExceededCases = 0;
  }
}

#endif

