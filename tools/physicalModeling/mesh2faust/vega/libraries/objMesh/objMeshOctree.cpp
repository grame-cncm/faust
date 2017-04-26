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

//  Jernej Barbic, CMU
//  builds an octree on top of the geometry from a given obj file
//  Can be intersected with a sphere or a line segment. 

#include "triple.h"
#include "objMeshOctree.h"
using namespace std;

template<class TriangleClass>
const double ObjMeshOctree<TriangleClass>::bboxExpansionRatio = 1.05;

template<class TriangleClass>
ObjMeshOctree<TriangleClass>::ObjMeshOctree(const ObjMesh * objMeshIn, int maxNumTrianglesInLeafNode_, int maxTreeDepth_, int printInfo) : 
  maxNumTrianglesInLeafNode(maxNumTrianglesInLeafNode_), maxTreeDepth(maxTreeDepth_)
{
  // copy mesh
  ObjMesh * objMesh = new ObjMesh(*objMeshIn);

  cout << "Checking if mesh is triangular... ";
  if (!objMesh->isTriangularMesh())
  {
    cout << "mesh was not triangular: triangulating... ";
    objMesh->triangulate();
    cout << "done" << endl;
  }
  else
    cout << "yes" << endl;
 
  int triangleIndex = 0;
  triangles.clear();
  for(unsigned int i=0; i < objMesh->getNumGroups(); i++) // over all groups
    for (unsigned int j=0; j < (objMesh->getGroupHandle(i))->getNumFaces(); j++) // over all faces
    {
      Vec3d p0 = objMesh->getPosition(objMesh->getVertexIndex(i,j,0));
      Vec3d p1 = objMesh->getPosition(objMesh->getVertexIndex(i,j,1));
      Vec3d p2 = objMesh->getPosition(objMesh->getVertexIndex(i,j,2));
      TriangleClass triangle(p0,p1,p2);
      triangle.setIndex(triangleIndex); // 0-indexed
      triangleIndex++;
      triangles.push_back(triangle);
    }

  cout << "Total number of triangles is: " << triangles.size() << endl;

  // build the octree
  cout << "Building the octree data structure... " << endl;
  root = new Octree<TriangleClass>(maxTreeDepth); 
  root->setBuildPrintInfo(printInfo);
  root->build(triangles, maxNumTrianglesInLeafNode);

  if(printInfo == 1)
  {
    int numMaxDepthExceededCases;
    int numMaxTriInDepthExceededCases;
    root->getBuildInfo(&numMaxDepthExceededCases, &numMaxTriInDepthExceededCases);
    printf("Total number of cells with more than %d triangles: %d. Max triangles in such cells: %d.\n", maxNumTrianglesInLeafNode, numMaxDepthExceededCases, numMaxTriInDepthExceededCases);
  }

  triangles.clear(); // release memory
  delete(objMesh);
}

template<>
ObjMeshOctree<TriangleWithCollisionInfoAndPseudoNormals>::ObjMeshOctree(const ObjMesh * objMeshIn, int maxNumTrianglesInLeafNode_, int maxTreeDepth_, int printInfo) :
  maxNumTrianglesInLeafNode(maxNumTrianglesInLeafNode_), maxTreeDepth(maxTreeDepth_)
{
  // copy mesh
  ObjMesh * objMesh = new ObjMesh(*objMeshIn);

  cout << "Checking if mesh is triangular... ";
  if (!objMesh->isTriangularMesh())
  {
    cout << "mesh was not triangular: triangulating... ";
    objMesh->triangulate();
    cout << "done" << endl;
  }
  else
    cout << "yes" << endl;

  ObjMesh * pseudoNormalObjMesh = objMesh;
  int numZeroAreaFaces = pseudoNormalObjMesh->removeZeroAreaFaces();
  cout << "Encountered and removed " << numZeroAreaFaces << " faces with zero surface area." << endl;

  triangles.clear();

  pseudoNormalObjMesh->computePseudoNormals();
  pseudoNormalObjMesh->computeEdgePseudoNormals();

  // compute face pseudonormals
  Vec3d pseudoNormals[7];
  for(unsigned int i=0; i < pseudoNormalObjMesh->getNumGroups(); i++) // over all groups
  {
    for (unsigned int j=0; j < (pseudoNormalObjMesh->getGroupHandle(i))->getNumFaces(); j++) // over all faces
    {
      // vertices
      unsigned int index0 = pseudoNormalObjMesh->getVertexIndex(i, j, 0);
      unsigned int index1 = pseudoNormalObjMesh->getVertexIndex(i, j, 1);
      unsigned int index2 = pseudoNormalObjMesh->getVertexIndex(i, j, 2);

      pseudoNormals[0] = pseudoNormalObjMesh->getPseudoNormal(index0);
      pseudoNormals[1] = pseudoNormalObjMesh->getPseudoNormal(index1);
      pseudoNormals[2] = pseudoNormalObjMesh->getPseudoNormal(index2);

      // edge pseudo normal
      if (pseudoNormalObjMesh->getEdgePseudoNormal(index0, index1, &pseudoNormals[3]) != 0)
      {
        cout << "Error: encountered an edge without a pseudonormal. Degenerate face? Vertices: " << index0 << " " << index1 << endl;
        delete(objMesh);
        throw(1);
      }
      if (pseudoNormalObjMesh->getEdgePseudoNormal(index1, index2, &pseudoNormals[4]) != 0)
      {
        cout << "Error: encountered an edge without a pseudonormal. Degenerate face? Vertices: " << index1 << " " << index2 << endl;
        delete(objMesh);
        throw(1);
      }
      if (pseudoNormalObjMesh->getEdgePseudoNormal(index2, index0, &pseudoNormals[5]) != 0)
      {
        cout << "Error: encountered an edge without a pseudonormal. Degenerate face? Vertices: " << index2 << " " << index0 << endl;
        delete(objMesh);
        throw(1);
      }

      // face pseudo normal
      Vec3d p0 = pseudoNormalObjMesh->getPosition(index0);
      Vec3d p1 = pseudoNormalObjMesh->getPosition(index1);
      Vec3d p2 = pseudoNormalObjMesh->getPosition(index2);

      pseudoNormals[6] = norm(cross(p1-p0,p2-p0)); 

      for(int normali=0; normali < 7; normali++)
      {
        if (ObjMesh::isNaN(pseudoNormals[normali][0]) || 
            ObjMesh::isNaN(pseudoNormals[normali][1]) || 
            ObjMesh::isNaN(pseudoNormals[normali][2]))
        {
          cout << "Error: nan encountered: " << pseudoNormals[normali][0] << " " << pseudoNormals[normali][1] << " " << pseudoNormals[normali][2] << endl;
          cout << "Group: " << i << " Triangle: " << j << " " << endl;
          cout << "  vtx0: " << index0 << " vtx1: " << index1 << " vtx2: " << index2 << endl;
          cout << "  "  << p0 << endl;
          cout << "  "  << p1 << endl;
          cout << "  "  << p2 << endl;
          cout << "Feature: " << normali << endl;
          delete(objMesh);
          throw(1);
        }
      }

      TriangleWithCollisionInfoAndPseudoNormals triangle(p0,p1,p2,pseudoNormals);
      triangles.push_back(triangle);
    }
  }

  cout << "Total number of triangles is: " << triangles.size() << endl;
  
  // build the octree
  Vec3d bmin, bmax;
  objMesh->getCubicBoundingBox(1.0, &bmin, &bmax);

  cout << "The model tight-fitting cube-shaped bounding box is: " << endl;
  cout << "xmin: " << bmin[0] << " xmax: " << bmax[0] << endl;
  cout << "ymin: " << bmin[1] << " ymax: " << bmax[1] << endl;
  cout << "zmin: " << bmin[2] << " zmax: " << bmax[2] << endl;
    
  BoundingBox bboxOctree(bmin, bmax);
  bboxOctree.expand(bboxExpansionRatio);

  cout << "Starting the octree creation algorithm..." << endl;

  root = new Octree<TriangleWithCollisionInfoAndPseudoNormals>(maxTreeDepth); 
  root->setBuildPrintInfo(printInfo);
  root->build(triangles, bboxOctree, maxNumTrianglesInLeafNode);

  if(printInfo == 1)
  {
    int numMaxDepthExceededCases;
    int numMaxTriInDepthExceededCases;
    root->getBuildInfo(&numMaxDepthExceededCases, &numMaxTriInDepthExceededCases);
    printf("Total number of cells with more than %d triangles: %d. Max triangles in such cells: %d.\n", maxNumTrianglesInLeafNode, numMaxDepthExceededCases,
     numMaxTriInDepthExceededCases);
  }

  triangles.clear(); // release memory
  delete(objMesh);

  cout << "Octree creation completed successfully." << endl;
}

template ObjMeshOctree<TriangleBasic>::ObjMeshOctree(const ObjMesh * objMesh, int maxNumTrianglesInLeafNode_, int maxTreeDepth_, int printInfo);  
template ObjMeshOctree<TriangleWithCollisionInfo>::ObjMeshOctree(const ObjMesh * objMesh, int maxNumTrianglesInLeafNode_, int maxTreeDepth_, int printInfo);
#if defined(_WIN32) || defined(WIN32)  
  //template ObjMeshOctree<TriangleWithCollisionInfoAndPseudoNormals>::ObjMeshOctree( ObjMesh * objMesh, int maxNumTrianglesInLeafNode_, int maxTreeDepth_, int printInfo );  
#endif

