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

#ifndef _OBJMESHOCTREE_H_
#define _OBJMESHOCTREE_H_

//  Jernej Barbic, CMU
//  builds an octree on top of the geometry from a given obj file
//  Can be intersected with a sphere or a line segment. 

#include "octree.h"
#include "objMesh.h"

template<class TriangleClass>
class ObjMeshOctree 
{
public:
  // builds an octree on top of the objMesh
  // maxNumTrianglesInLeafNode = max number of triangles in an octree leaf node
  // maxTreeDepth = max tree depth
  // (if tree depth were to exceed maxTreeDepth, a leaf node may have more than maxNumTrianglesInLeafNode triangles)
  ObjMeshOctree(const ObjMesh * objMesh, int maxNumTrianglesInLeafNode, int maxTreeDepth, int printInfo = 0);
  ~ObjMeshOctree() { delete(root); }

  // sphere-triangles query
  // retrieves all triangles intersected by the sphere 
  // (can potentially return the same triangle several times; call <TriangleClass>::makeUniqueList to make the list unique if needed)
  void rangeQuery(std::vector< TriangleClass* > & triangleList, const SimpleSphere & simpleSphere)
    { root->buildCollisionList(triangleList, simpleSphere); }

  // line segment-triangles query
  // retrieves all triangles intersected by the line segment
  // (can potentially return the same triangle several times; call <TriangleClass>::makeUniqueList to make the list unique if needed)
  void lineSegmentIntersection(std::vector< TriangleClass* > & triangleList, const Vec3d & segmentStart, const Vec3d & segmentEnd, std::vector<Vec3d> * intersectionList = NULL)
    { root->buildCollisionList(triangleList, segmentStart, segmentEnd, intersectionList); }

  void renderOctree() { root->render(); }
  void renderOctree(int level) { root->render(level); }
  void renderOctree(int level, int boxIndex) { root->render(level, boxIndex); }
  void setPrintOctreeInfo(int info) { root->setRenderInfo(info); }

  BoundingBox boundingBox() { return (root->getBoundingBox()) ; }

protected:
  std::vector<TriangleClass> triangles;

  Octree<TriangleClass> * root;
  int maxNumTrianglesInLeafNode; // max number of triangles in an octree leaf node
  int maxTreeDepth; // max tree depth
  
  static const double bboxExpansionRatio;
};

#endif

