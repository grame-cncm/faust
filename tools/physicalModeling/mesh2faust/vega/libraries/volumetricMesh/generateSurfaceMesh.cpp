/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "volumetricMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Yijing Li                                *
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

#include <float.h>
#include "objMesh.h"
#include "generateSurfaceMesh.h"
#include "cubicMesh.h"
using namespace std;

// classes to disambiguate and sort faces

class TopologicalFaceI
{
public:
  inline TopologicalFaceI(int p1, int p2, int p3, int p4)
  {
    vertices[0] = p1;
    vertices[1] = p2;
    vertices[2] = p3;
    vertices[3] = p4;
    size = 4;
    sortVertices();
  }

  inline TopologicalFaceI(int p1, int p2, int p3)
  {
    vertices[0] = p1;
    vertices[1] = p2;
    vertices[2] = p3;
    size = 3;
    sortVertices();
  }
    
  //accessor
  int vertex(int i) const { return vertices[i];} 
  int sortedVertex(int i) const { return sortedVertices[i]; }
  int faceDegree() const { return size; } 
  const int * index() const { return vertices; }

  TopologicalFaceI(const TopologicalFaceI & face)
  {
    size = face.size;
    memcpy(vertices, face.vertices, sizeof(int) * size);
    memcpy(sortedVertices, face.sortedVertices, sizeof(int) * size);
  }

  TopologicalFaceI & operator = (const TopologicalFaceI & face)
  {
    if (&face == this) 
      return *this;
    size = face.size;
    memcpy(vertices, face.vertices, sizeof(int) * size);
    memcpy(sortedVertices, face.sortedVertices, sizeof(int) * size);
    return *this;
  }

protected:

  inline void sortVertices() 
  { 
    memcpy(sortedVertices, vertices, sizeof(int) * size);
    sort(sortedVertices, sortedVertices + size);
  }

  int size;
  int vertices[4];
  int sortedVertices[4];
  //std::vector<int> vertices_;
};

class FaceOrder
{
public:
  bool operator()(const TopologicalFaceI & x, const TopologicalFaceI & y) const;
};

bool FaceOrder::operator()(const TopologicalFaceI & x, const TopologicalFaceI & y) const
{
  int degx = x.faceDegree();
  int degy = y.faceDegree();
  int mindeg = (degx < degy) ? degx : degy;

  for (int i = 0; i < mindeg; i++)
  {
    int x1 = x.sortedVertex(i);
    int y1 = y.sortedVertex(i);

    if (x1 < y1)
      return true;
    if (y1 < x1)
      return false;
  }

  return false;
}

// the main routine
ObjMesh * GenerateSurfaceMesh::ComputeMesh(const VolumetricMesh * mesh, bool triangulateOutputMesh)
{
  // create an empty surface mesh
  ObjMesh * objMesh = new ObjMesh();

  // create default group
  objMesh->addGroup("Default");

  // add all vertices
  for(int i=0; i<mesh->getNumVertices(); i++)
  {
    const Vec3d & pos = mesh->getVertex(i);
    objMesh->addVertexPosition(pos);
  }

  set<TopologicalFaceI,FaceOrder> surfaceFaces;
  //set<TopologicalFaceI,FaceOrder> interiorFaces; // not needed

  //interiorFaces.clear();

  int numElementVertices = mesh->getNumElementVertices();
  int faceDegree = 0;

  if (numElementVertices == 4)
  {
    faceDegree = 3;
    triangulateOutputMesh = false;
  }

  if (numElementVertices == 8)
    faceDegree = 4;

  if (faceDegree == 0)
  {
    printf("Error: unsupported mesh type encountered.\n");
    return NULL;
  }  

  // build unique list of all surface faces

  if (numElementVertices == 4) // tet mesh
  {
    for (int i=0; i<mesh->getNumElements(); i++)
    {
      // compute determinant to establish orientation
      double det = dot(mesh->getVertex(i, 1) - mesh->getVertex(i, 0), cross(mesh->getVertex(i, 2) - mesh->getVertex(i, 0), mesh->getVertex(i, 3) - mesh->getVertex(i, 0)));

        //surfaceFaces.erase(*face);
        //interiorFaces.insert(*face);
  
      #define PROCESS_FACE3(q0,q1,q2) \
          { \
            TopologicalFaceI face(mesh->getVertexIndex(i,q0),mesh->getVertexIndex(i,q1),mesh->getVertexIndex(i,q2)); \
            if (surfaceFaces.find(face) != surfaceFaces.end()) \
              surfaceFaces.erase(face); \
            else \
              surfaceFaces.insert(face); \
          }
          
  
      if (det >= 0)
      {
        PROCESS_FACE3(1,2,3)
        PROCESS_FACE3(2,0,3)
        PROCESS_FACE3(3,0,1)
        PROCESS_FACE3(1,0,2)
      }
      else
      {
        PROCESS_FACE3(3,2,1)
        PROCESS_FACE3(3,0,2)
        PROCESS_FACE3(1,0,3)
        PROCESS_FACE3(2,0,1)
      }

      #undef PROCESS_FACE3
    }
  }

  if (numElementVertices == 8) // cubic mesh
  {
    for (int i = 0; i < mesh->getNumElements(); i++)
    {
  
      #define PROCESS_FACE4(q0,q1,q2,q3) \
          { \
            TopologicalFaceI face(mesh->getVertexIndex(i,q0),mesh->getVertexIndex(i,q1),mesh->getVertexIndex(i,q2),mesh->getVertexIndex(i,q3)); \
          if (surfaceFaces.find(face) != surfaceFaces.end()) \
            surfaceFaces.erase(face); \
          else \
            surfaceFaces.insert(face); \
          }
  
      PROCESS_FACE4(0,3,2,1)
      PROCESS_FACE4(4,5,6,7)
      PROCESS_FACE4(0,1,5,4)
      PROCESS_FACE4(3,7,6,2)
      PROCESS_FACE4(1,2,6,5)
      PROCESS_FACE4(0,4,7,3)

      #undef PROCESS_FACE4
    }
  }

  // now, surfaceFaces contains a unique list of all surface faces
  // add all faces to the surface mesh 
  //int * index = (int*) malloc (sizeof(int) * faceDegree);
  set<TopologicalFaceI,FaceOrder>::iterator face;
  for (face = surfaceFaces.begin(); face != surfaceFaces.end(); ++face) // all surface faces
  {
    //for (int i = 0; i < faceDegree; i++)
    //  index[i] = face->vertex(i);
    const int * index = face->index();

    std::pair< bool, unsigned int > texPos(false,0); // no textures
    std::pair< bool, unsigned int > normal(false,0); // no normals

    if (triangulateOutputMesh)
    {
      // triangulate the face into two triangles
      ObjMesh::Face newFace1;
      newFace1.addVertex( ObjMesh::Vertex( index[0], texPos, normal ) );
      newFace1.addVertex( ObjMesh::Vertex( index[1], texPos, normal ) );
      newFace1.addVertex( ObjMesh::Vertex( index[2], texPos, normal ) );

      ObjMesh::Face newFace2;
      newFace2.addVertex( ObjMesh::Vertex( index[2], texPos, normal ) );
      newFace2.addVertex( ObjMesh::Vertex( index[3], texPos, normal ) );
      newFace2.addVertex( ObjMesh::Vertex( index[0], texPos, normal ) );
 
      objMesh->addFaceToGroup(newFace1,0);
      objMesh->addFaceToGroup(newFace2,0);
    }
    else
    {
      ObjMesh::Face newFace1;
      for(int i=0; i<faceDegree; i++)
        newFace1.addVertex( ObjMesh::Vertex( index[i], texPos, normal ) );
      objMesh->addFaceToGroup(newFace1, 0);
    }
  }

  //free(index);

  if (mesh->getElementType() == CubicMesh::elementType())
  {
    // cubic mesh
    objMesh->setNormalsToFaceNormals();
  }
  else
  {
    // other types of meshes (e.g., tet)
    objMesh->computePseudoNormals();
    objMesh->setNormalsToPseudoNormals();
  }

  objMesh->setSingleMaterial(ObjMesh::Material());

  return objMesh;
}

// advanced routine, not used very often
ObjMesh * GenerateSurfaceMesh::ComputeMesh(const VolumetricMesh * mesh, const ObjMesh * superMesh, bool triangulateOutputMesh)
{
  // for each volumetric mesh vertex, find the nearest obj file vertex
  int * closestObjVertex = (int*) malloc (sizeof(int) * mesh->getNumVertices());
  for(int i=0; i<mesh->getNumVertices(); i++)
  {
    const Vec3d & pos = mesh->getVertex(i);
    double dist;
    closestObjVertex[i] = superMesh->getClosestVertex(pos, &dist);
  }

  // build the list of triangles
  set<TopologicalFaceI,FaceOrder> superMeshFaces;
  for(unsigned int i=0; i < superMesh->getNumGroups(); i++)
  {
    const ObjMesh::Group * groupHandle = superMesh->getGroupHandle(i);
    for(unsigned int iFace = 0; iFace < groupHandle->getNumFaces(); iFace++)
    {
      const ObjMesh::Face * faceHandle = groupHandle->getFaceHandle(iFace);
      if (faceHandle->getNumVertices() != 3)
      {
        printf("Error: input superMesh is not triangulated.\n");
        free(closestObjVertex);
        return NULL;
      }

      superMeshFaces.insert(TopologicalFaceI(faceHandle->getVertexHandle(0)->getPositionIndex(), faceHandle->getVertexHandle(1)->getPositionIndex(), faceHandle->getVertexHandle(2)->getPositionIndex()));
    }
  }

  // create empty surface mesh
  ObjMesh * objMesh = new ObjMesh();

  // create default group
  objMesh->addGroup("Default");

  // add all vertices
  for(int i=0; i<mesh->getNumVertices(); i++)
  {
    const Vec3d & posm = mesh->getVertex(i);
    Vec3d pos;
    pos[0] = posm[0]; 
    pos[1] = posm[1]; 
    pos[2] = posm[2];
    objMesh->addVertexPosition(pos);
  }

  set<TopologicalFaceI,FaceOrder> surfaceFaces;
  //set<TopologicalFaceI,FaceOrder> interiorFaces;

  // create a unique list of faces
  surfaceFaces.clear();
  //interiorFaces.clear();

  int numElementVertices = mesh->getNumElementVertices();
  int faceDegree = 0;

  if (numElementVertices == 4)
  {
    faceDegree = 3;
    triangulateOutputMesh = false;
  }

  if (numElementVertices == 8)
    faceDegree = 4;

  if (faceDegree == 0)
  {
    printf("Error: unsupported mesh type encountered.\n");
    free(closestObjVertex);
    return NULL;
  }  

  // build unique list of all surface faces

  if (numElementVertices == 4)
  {
    for (int i=0; i<mesh->getNumElements(); i++)
    {
      // compute determinant to establish orientation
      double det = dot(mesh->getVertex(i, 1) - mesh->getVertex(i, 0), cross(mesh->getVertex(i, 2) - mesh->getVertex(i, 0), mesh->getVertex(i, 3) - mesh->getVertex(i, 0)));

        //surfaceFaces.erase(*face);
        //interiorFaces.insert(*face);
  
      #define PROCESS_FACE3(q0,q1,q2) \
          { \
            TopologicalFaceI face(mesh->getVertexIndex(i,q0),mesh->getVertexIndex(i,q1),mesh->getVertexIndex(i,q2)); \
            if (surfaceFaces.find(face) != surfaceFaces.end()) \
              surfaceFaces.erase(face);\
            else \
              surfaceFaces.insert(face); \
          }
  
      if (det >= 0)
      {
        PROCESS_FACE3(1,2,3)
        PROCESS_FACE3(2,0,3)
        PROCESS_FACE3(3,0,1)
        PROCESS_FACE3(1,0,2)
      }
      else
      {
        PROCESS_FACE3(3,2,1)
        PROCESS_FACE3(3,0,2)
        PROCESS_FACE3(1,0,3)
        PROCESS_FACE3(2,0,1)
      }

      #undef PROCESS_FACE3
    }
  }

  if (numElementVertices == 8)
  {
    for (int i=0; i<mesh->getNumElements(); i++)
    {
        //surfaceFaces.erase(*face);
        //interiorFaces.insert(*face);
  
      #define PROCESS_FACE4(q0,q1,q2,q3) \
          { \
            TopologicalFaceI face(mesh->getVertexIndex(i,q0),mesh->getVertexIndex(i,q1),mesh->getVertexIndex(i,q2),mesh->getVertexIndex(i,q3)); \
            if (surfaceFaces.find(face) != surfaceFaces.end()) \
              surfaceFaces.erase(face); \
            else \
              surfaceFaces.insert(face); \
          }
  
      PROCESS_FACE4(0,3,2,1)
      PROCESS_FACE4(4,5,6,7)
      PROCESS_FACE4(0,1,5,4)
      PROCESS_FACE4(3,7,6,2)
      PROCESS_FACE4(1,2,6,5)
      PROCESS_FACE4(0,4,7,3)

      #undef PROCESS_FACE4
    }
  }

  // now, surfaceFaces contains a unique list of all surface faces
  // erase any faces that are not also superMesh faces
  set<TopologicalFaceI,FaceOrder> trueSurfaceFaces;
  for(set<TopologicalFaceI,FaceOrder> :: iterator iter = surfaceFaces.begin(); iter != surfaceFaces.end(); iter++)
  {
    int vtx0 = closestObjVertex[iter->vertex(0)];
    int vtx1 = closestObjVertex[iter->vertex(1)];
    int vtx2 = closestObjVertex[iter->vertex(2)];
    if (superMeshFaces.find(TopologicalFaceI(vtx0, vtx1, vtx2)) != superMeshFaces.end())
      trueSurfaceFaces.insert(*iter);
  }

  surfaceFaces = trueSurfaceFaces;

  // add all faces to the surface obj mesh of the voxel mesh
  int * index = (int*) malloc (sizeof(int) * faceDegree);
  set<TopologicalFaceI,FaceOrder>::iterator face;
  for (face = surfaceFaces.begin(); face != surfaceFaces.end(); ++face) // all surface faces
  {
    for (int i=0; i<faceDegree; i++)
      index[i] = face->vertex(i);

    std::pair< bool, unsigned int > texPos(false,0); // no textures
    std::pair< bool, unsigned int > normal(false,0); // no normals

    if (triangulateOutputMesh)
    {
      // triangulate the face into two triangles
      ObjMesh::Face newFace1;
      newFace1.addVertex( ObjMesh::Vertex( index[0], texPos, normal ) );
      newFace1.addVertex( ObjMesh::Vertex( index[1], texPos, normal ) );
      newFace1.addVertex( ObjMesh::Vertex( index[2], texPos, normal ) );

      ObjMesh::Face newFace2;
      newFace2.addVertex( ObjMesh::Vertex( index[2], texPos, normal ) );
      newFace2.addVertex( ObjMesh::Vertex( index[3], texPos, normal ) );
      newFace2.addVertex( ObjMesh::Vertex( index[0], texPos, normal ) );
 
      objMesh->addFaceToGroup(newFace1,0);
      objMesh->addFaceToGroup(newFace2,0);
    }
    else
    {
      ObjMesh::Face newFace1;
      for(int i=0; i<faceDegree; i++)
        newFace1.addVertex( ObjMesh::Vertex( index[i], texPos, normal ) );
      objMesh->addFaceToGroup(newFace1, 0);
    }
  }

  free(index);

  if (mesh->getElementType() == CubicMesh::elementType())
  {
    // cubic mesh
    objMesh->setNormalsToFaceNormals();
  }
  else
  {
    // other types of meshes (e.g., tet)
    objMesh->computePseudoNormals();
    objMesh->setNormalsToPseudoNormals();
  }

  free(closestObjVertex);

  objMesh->setSingleMaterial(ObjMesh::Material());

  return objMesh;
}

