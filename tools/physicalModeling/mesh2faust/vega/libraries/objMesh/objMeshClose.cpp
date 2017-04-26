/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "objMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC        *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
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

//  Closes a manifold mesh

#include <set>
using namespace std;

#include "objMeshClose.h"
#include "objMeshOrientable.h"

int ObjMeshClose::Close(ObjMesh * objMesh)
{
  ObjMeshOrientable * objMeshOrientable = NULL;
  try
  {
    int * numOrientationFlips = NULL; 
    int verbose=0;
    objMeshOrientable = new ObjMeshOrientable(objMesh, 1, numOrientationFlips, verbose);
  }
  catch (int)
  {
    printf("Mesh is non-orientable.\n");
    return 1;
  }

  int numBoundaryEdges = (int)objMeshOrientable->numBoundaryEdges();
  set<int> boundaryEdges;
  for(int i=0; i<numBoundaryEdges; i++)
    boundaryEdges.insert(objMeshOrientable->boundaryEdge(i));

  while (boundaryEdges.size() > 0)
  {
    int firstEdge = *(boundaryEdges.begin());

    vector<int> boundaryVertices;

    // iterate around the boundary loop
    int edge = firstEdge;
    do
    {
      //printf("edge %d ", edge);
      // push vertices into "boundaryVertices", and erase edges from boundaryEdges
      ObjMeshOrientable::HalfEdge halfEdge = objMeshOrientable->halfEdge(edge);
      boundaryVertices.push_back(halfEdge.startVertex());
      boundaryEdges.erase(edge);

      // find the next boundary edge
      ObjMeshOrientable::HalfEdge nextHalfEdge = halfEdge;
      do
      {
        nextHalfEdge = objMeshOrientable->edgeNext(nextHalfEdge);
        if (nextHalfEdge.isBoundary())
          break;
        nextHalfEdge = objMeshOrientable->edgeOpposite(nextHalfEdge);
      }
      while (nextHalfEdge != halfEdge);

      if (nextHalfEdge == halfEdge)
      {
        printf("Mesh is non-orientable (cannot detect next edge along the hole).\n");
        return 2;
      }
      
      edge = nextHalfEdge.position();
    }
    while (edge != firstEdge);
    //printf("\n");

    // compute centroid
    Vec3d avg(0,0,0);
    for(unsigned int i=0; i<boundaryVertices.size(); i++)
      avg += objMesh->getPosition(boundaryVertices[i]);
    avg /= boundaryVertices.size();

    int numVertices = objMesh->getNumVertices();
    objMesh->addVertexPosition(avg);

    // find group containing edge "firstEdge"
    ObjMeshOrientable::HalfEdge firstHalfEdge = objMeshOrientable->halfEdge(firstEdge);
    unsigned int group = firstHalfEdge.groupID();
    ObjMesh::Group * groupHandle = (ObjMesh::Group*) objMesh->getGroupHandle(group);

    // add triangles to close the face (a "tent")
    //printf("Adding triangles:\n");
    for(unsigned int i=0; i<boundaryVertices.size(); i++)
    {
      int vtxIndex[3] = { numVertices, boundaryVertices[(i+1) % boundaryVertices.size()], boundaryVertices[i] };
      //printf("[%d %d %d] ", vtxIndex[0], vtxIndex[1], vtxIndex[2]);
      
      // compute flat normal
      Vec3d normal = norm(cross(objMesh->getPosition(vtxIndex[1]) - objMesh->getPosition(vtxIndex[0]), objMesh->getPosition(vtxIndex[2]) - objMesh->getPosition(vtxIndex[0]) ));

      // add the normal
      int numNormals = objMesh->getNumNormals();
      objMesh->addVertexNormal(normal);

      // create and add new face
      ObjMesh::Vertex vertex0(vtxIndex[0]);
      vertex0.setNormalIndex(numNormals);
      ObjMesh::Vertex vertex1(vtxIndex[1]);
      vertex1.setNormalIndex(numNormals);
      ObjMesh::Vertex vertex2(vtxIndex[2]);
      vertex2.setNormalIndex(numNormals);
      ObjMesh::Face face(vertex0, vertex1, vertex2);
      groupHandle->addFace(face);
    }
    //printf("\n");
  }

  return 0;
}

