/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "distance field" library , Copyright (C) 2007 CMU, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Hongyi Xu, Jernej Barbic                                *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Research: Jernej Barbic, Hongyi Xu, Doug L. James                     *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
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
  This class computes a signed distance field from polygon soup geometry, as described in:

  Hongyi Xu, Jernej Barbic: 
  Signed Distance Fields for Polygon Soup Meshes, Graphics Interface 2014, Montreal, Canada
*/

#include <stdio.h>
#include "signedDistanceFieldFromPolygonSoup.h"
#include "marchingCubes.h"
using namespace::std;

SignedDistanceFieldFromPolygonSoup::SignedDistanceFieldFromPolygonSoup(ObjMesh * objMesh_, double expansionRatio_, bool useCubicBox_,
    Vec3d * bbmin_, Vec3d * bbmax_):
objMesh(objMesh_), expansionRatio(expansionRatio_), useCubicBox(useCubicBox_)
{
  if(bbmin_ != NULL)
    bbmin = *bbmin_;
  else
    bbmin = Vec3d(0.0);

  if(bbmax_ != NULL)
    bbmax = *bbmax_;
  else
    bbmax = Vec3d(1.0);


  if(bbmin_ == NULL || bbmax_ == NULL)
    autoBoundingBox = true;
  else
    autoBoundingBox = false;
}

// construct TriangleWithCollisionInfoAndPseudoNormals for each triangle in the mesh
bool SignedDistanceFieldFromPolygonSoup::ConstructPseudoNormalComponents(ObjMesh* isoMesh, vector<TriangleWithCollisionInfoAndPseudoNormals*>* triangleList)
{
  printf("*************** Computing PseudoNormals *****************\n");
  ObjMesh* pseudoNormalObjMesh = isoMesh;
  int numZeroAreaFaces = pseudoNormalObjMesh->removeZeroAreaFaces();
  printf("Encountered and removed %d faces with zero surface area.\n", numZeroAreaFaces);

  //printf("here:%d %d\n", removedFaces[0].first, removedFaces[0].second);

  pseudoNormalObjMesh->computePseudoNormals();
  pseudoNormalObjMesh->computeEdgePseudoNormals();

  Vec3d pseudoNormals[7];
  for (unsigned int i=0; i<pseudoNormalObjMesh->getNumGroups(); ++i)
  {
    triangleList[i].clear();
    for (unsigned int j=0; j<(pseudoNormalObjMesh->getGroupHandle(i))->getNumFaces(); ++j)
    {
      unsigned int index0 = pseudoNormalObjMesh->getVertexIndex(i, j, 0);
      unsigned int index1 = pseudoNormalObjMesh->getVertexIndex(i, j, 1);
      unsigned int index2 = pseudoNormalObjMesh->getVertexIndex(i, j, 2);

      pseudoNormals[0] = pseudoNormalObjMesh->getPseudoNormal(index0);
      pseudoNormals[1] = pseudoNormalObjMesh->getPseudoNormal(index1);
      pseudoNormals[2] = pseudoNormalObjMesh->getPseudoNormal(index2);

      if (pseudoNormalObjMesh->getEdgePseudoNormal(index0, index1, &pseudoNormals[3]) != 0)
      {
        printf("Error: encountered an edge without a pseudonormal. Degenerate face? Vertices: %d %d\n", index0, index1);
        return false;
      }

      if (pseudoNormalObjMesh->getEdgePseudoNormal(index1, index2, &pseudoNormals[4]) != 0)
      {
        printf("Error: encountered an edge without a pseudonormal. Degenerate face? Vertices: %d %d\n", index1, index2);
        return false;
      }

      if (pseudoNormalObjMesh->getEdgePseudoNormal(index2, index0, &pseudoNormals[5]) != 0)
      {
        printf("Error: encountered an edge without a pseudonormal. Degenerate face? Vertices: %d %d.\n", index2, index0);
        return false;
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
          printf("Error: pseudonormal nan encountered: %lf %lf %lf\n", pseudoNormals[normali][0], pseudoNormals[normali][1], pseudoNormals[normali][2]);
          printf("Group: %d | Triangle: %d\n", i, j);
          printf("vtx0: %d | vtx1: %d | vtx2: %d\n",index0, index1, index2);
          return false;
        }
      }
      TriangleWithCollisionInfoAndPseudoNormals * triangle = new TriangleWithCollisionInfoAndPseudoNormals(p0, p1, p2, pseudoNormals);
      triangleList[i].push_back(triangle);
    }
  }

  return true;
}

// check whether comp1 is strictly inside comp2 using bounding box
bool SignedDistanceFieldFromPolygonSoup::CheckInAndOutViaBoundingBox(vector<Vec3d> & bmin, vector<Vec3d> & bmax, int compIndex1, int compIndex2)
{
  if (bmin[compIndex1][0]>=bmin[compIndex2][0] && bmin[compIndex1][1]>=bmin[compIndex2][1] && bmin[compIndex1][2] >= bmin[compIndex2][2]&& bmax[compIndex1][0]<=bmax[compIndex2][0] && bmax[compIndex1][1]<=bmax[compIndex2][1] && bmax[compIndex1][2] <= bmax[compIndex2][2])
      return true;

  return false;
}

// check whether comp2's normal points toward opposite direction as comp1's position
// this is to prevent the case that comp1's bounding box is inside comp2's, but comp1 is outside comp2
bool SignedDistanceFieldFromPolygonSoup::CheckInAndOutViaNormalTest(vector<TriangleWithCollisionInfoAndPseudoNormals*>* triangleList, int compIndex1, int compIndex2)
{
  if (triangleList[compIndex1].size() == 0)
    return true;

  Vec3d testPoint = triangleList[compIndex1][0]->first();

  int closestFeature = -1;
  int closestTriangle = -1;
  //int indexClosestTriangle = -1;
  double closestDistance2 = DBL_MAX;

  for (size_t i=0; i<triangleList[compIndex2].size(); ++i)
  {
    int closestLocalFeature = -1;
    double d2 = triangleList[compIndex2][i]->distanceToPoint2(testPoint, &closestLocalFeature);
    if( d2 < closestDistance2)
    {
      closestDistance2 = d2;
      closestFeature = closestLocalFeature;
      closestTriangle = (int)i;
    }
  }

  Vec3d pseudoNormal = triangleList[compIndex2][closestTriangle]->pseudoNormal(closestFeature);
  Vec3d pseudoClosestPosition = triangleList[compIndex2][closestTriangle]->pseudoClosestPosition(closestFeature);
  Vec3d pointVec = testPoint - pseudoClosestPosition;

  if(dot(pseudoNormal,pointVec) < 0)
  // if (pseudoNormal[0]*pointVec[0]+pseudoNormal[1]*pointVec[1]+pseudoNormal[2]*pointVec[2]<0)
    return true;

  return false;
}

ObjMesh * SignedDistanceFieldFromPolygonSoup::RemoveInteriorComponents(ObjMesh * isoMesh)
{
  int numGroups = (int) isoMesh->getNumGroups();

  if(numGroups == 1)
    return isoMesh;

  //building bounding box for each group;
  vector<Vec3d> bmin(numGroups);
  vector<Vec3d> bmax(numGroups);

  vector<std::pair<int, int> >groupFaceList;

  for (int i=0; i<numGroups; ++i)
  {
    const ObjMesh::Group * group = isoMesh->getGroupHandle(i);

    bmin[i][0] = bmin[i][1] = bmin[i][2] = DBL_MAX;
    bmax[i][0] = bmax[i][1] = bmax[i][2] = -DBL_MAX;

    for (unsigned int j=0; j<group->getNumFaces(); ++j)
    {
      const ObjMesh::Face * face = group->getFaceHandle(j);

      groupFaceList.push_back(std::make_pair(i, j));
      for (unsigned int v=0; v<face->getNumVertices(); ++v)
      {
        const ObjMesh::Vertex * vertex = face->getVertexHandle(v);
        Vec3d pos = isoMesh->getPosition(vertex->getPositionIndex());

        if(pos[0]<bmin[i][0])
          bmin[i][0] = pos[0];
        else if(pos[0]>bmax[i][0])
          bmax[i][0] = pos[0];

        if(pos[1]<bmin[i][1])
          bmin[i][1] = pos[1];
        else if(pos[1]>bmax[i][1])
          bmax[i][1] = pos[1];

        if(pos[2]<bmin[i][2])
          bmin[i][2] = pos[2];
        else if(pos[2]>bmax[i][2])
          bmax[i][2] = pos[2];
      }
    }
  }

  ObjMesh * cloneMesh = isoMesh->clone(groupFaceList, 0);

  // judge the position relation
  vector<double> bbVolume(numGroups);

  for(int i = 0; i < numGroups; ++i)
  {
    bbVolume[i] = (bmax[i][0] - bmin[i][0]) * (bmax[i][1]- bmin[i][1]) * (bmax[i][2]- bmin[i][2]);
  }

  vector<int> componentOrder(numGroups);
  vector<int> tag(numGroups);
  

  for(int i=0; i<numGroups; i++)
    tag[i] = numGroups;

  // sort each group according to bounding box volume
  // tag[groudp id] = rank in bounding box size (0: smallest)
  for(int i=0; i<numGroups; ++i)
  {
    double minValue = DBL_MAX;
    int minIndex = -1;
    for(int j=0; j<numGroups; ++j)
    {
      if(tag[j]>i && bbVolume[j]<minValue)
      {
        minValue = bbVolume[j];
        minIndex = j;
      }
    }
    tag[minIndex] = i;
  }

  for(int i=0; i<numGroups; ++i)
  {
    componentOrder[tag[i]] = i;
  }

  vector<int> removedList;

  //order the bbVolume
  vector<TriangleWithCollisionInfoAndPseudoNormals*>* triangleList = new vector<TriangleWithCollisionInfoAndPseudoNormals*>[numGroups];
  vector<std::pair<int, int> >removedFaces;
  if (ConstructPseudoNormalComponents(isoMesh, triangleList) == false)
  {
    for(int i=0; i<numGroups; ++i)
    {
      for(size_t j = 0; j < triangleList[i].size(); j++)
        delete triangleList[i][j];
    }
    delete [] triangleList;
    
    delete isoMesh;
    return NULL;
  }

  for(int i = 0; i < numGroups-1; ++i)
  {
    int compIndex = componentOrder[i];
    for(int j = numGroups-1; j > i; --j)
    { 
      int compIndex2 = componentOrder[j];
      if(!CheckInAndOutViaBoundingBox(bmin, bmax, compIndex, compIndex2))
        continue;
      if(CheckInAndOutViaNormalTest(triangleList, compIndex, compIndex2))
      {
        printf("removing group %d from group %d\n", compIndex, compIndex2);
        removedList.push_back(compIndex);
        break;
      }
    }
  }

  printf("Removed %d interior groups: ", (int)removedList.size());

  //Add back the zero area face
  delete isoMesh;
  isoMesh = cloneMesh;
  // sort the list because we have to remove groups in a descending order
  // otherwise ObjMesh::removeGroup will modify mesh group index order
  std::sort(removedList.begin(), removedList.end());

  for(int i=(int) removedList.size() - 1; i>=0; --i)
  {
    printf("%d ", removedList[i]);
    isoMesh->removeGroup(removedList[i]);
  }
  printf("\n");

  for(int i=0; i<numGroups; ++i)
  {
    for(size_t j = 0; j < triangleList[i].size(); j++)
      delete triangleList[i][j];
  }
  delete [] triangleList;

  return isoMesh;
}

ObjMesh * SignedDistanceFieldFromPolygonSoup::ComputeIsosurface(DistanceFieldBase * distanceField, double sigma)
{
  printf("Computing the isosurface using marching cubes. Iso-level: %f .\n", sigma);
  ObjMesh * marchingCubesResult = MarchingCubes::compute(distanceField, sigma);
  printf("Finishing marching cubes...\n");

  printf("Removing interior components...\n");
  ObjMesh * outputMesh = marchingCubesResult->splitIntoConnectedComponents(0);
  printf("Detected %d groups in the isoMesh.\n", (int)outputMesh->getNumGroups());
  outputMesh = RemoveInteriorComponents(outputMesh);

  delete(marchingCubesResult);

  return outputMesh;
}

bool SignedDistanceFieldFromPolygonSoup::setBoundingBox(DistanceFieldBase* field, int resolutionX, int resolutionY, int resolutionZ)
{
  if (autoBoundingBox)
  {
    if (useCubicBox)
      printf("Forcing a cube-sized bounding box.\n");
    field->setAutomaticBoundingBox(useCubicBox, expansionRatio);
    field->computeBoundingBox(objMesh, resolutionX, resolutionY, resolutionZ);
  }
  else
  {
    if ((bbmin[0] >= bbmax[0]) || (bbmin[1] >= bbmax[1]) || (bbmin[2] >= bbmax[2]))
    {
      printf("Invalid bounding box.\n");
      return false;
    }
    field->setBoundingBox(bbmin,bbmax);
  }
  return true;
}

DistanceField * SignedDistanceFieldFromPolygonSoup::ComputeDistanceField(int resolutionX, int resolutionY, int resolutionZ,
    double sigma, int subtractSigma, int numThreads, bool computeVoronoiDiagram, int maxTriCount, int maxDepth,
    int closestPointFlag, const char* precomputedUnsignedFieldFilename)
{
  DistanceField * field = NULL;

  if (!closestPointFlag)
  {
    if (numThreads == 0)
      field = new DistanceField();
    else
      field = new DistanceFieldMT(numThreads);
  }
  else
    field = new ClosestPointField();

  field->enableVoronoiDiagramComputation(computeVoronoiDiagram);

  bool ret = setBoundingBox(field, resolutionX, resolutionY, resolutionZ);
  if (ret == false)
  {
    delete field;
    return NULL;
  }

  int code = 0;

  if (precomputedUnsignedFieldFilename == NULL)
  {
    printf("********* Computing unsigned distance field (%d x %d x %d) *************\n", resolutionX, resolutionY, resolutionZ); fflush(NULL);
    code = field->computeUnsignedField(objMesh, resolutionX, resolutionY, resolutionZ, maxTriCount, maxDepth);

    if(code !=0)
    {
      printf("Error computing unsigned distance field.\n");
      delete field;
      return NULL;
    }
  }
  else
    field->load(precomputedUnsignedFieldFilename);

  ObjMesh * isoMesh = ComputeIsosurface(field, sigma);
  printf("********* Recomputing signed distance field (%d x %d x %d) *************\n", resolutionX, resolutionY, resolutionZ); fflush(NULL);
  field->offsetDistanceField(-sigma);
  code = field->computeFloodFillSignedField(isoMesh, resolutionX, resolutionY, resolutionZ, maxTriCount, maxDepth);
  delete isoMesh;

  if (code != 0)
  {
    printf("Error recomputing signed distance field.\n");
    delete field;
    return NULL;
  }

  if (subtractSigma)
    field->offsetDistanceField(sigma);

  return field;
}

DistanceFieldNarrowBand * SignedDistanceFieldFromPolygonSoup::ComputeDistanceFieldNarrowBand(int resolutionX, int resolutionY, int resolutionZ, double bandwidth, 
  double sigma, int subtractSigma, int maxTriCount, int maxDepth, const char * precomputedUnsignedFieldFilename)
{
  DistanceFieldNarrowBand * field = new DistanceFieldNarrowBand();

  bool ret = setBoundingBox(field, resolutionX, resolutionY, resolutionZ);
  if (ret == false)
  {
    delete field;
    return NULL;
  }

  int code = 0;

  if (sigma >= bandwidth)
  {
    printf("Error: sigma is not smaller than the offset.\n");
    delete field;
    return NULL;
  }

  if (precomputedUnsignedFieldFilename == NULL)
  {
    printf("********* Computing unsigned distance field (%d x %d x %d) *************\n", resolutionX, resolutionY, resolutionZ); fflush(NULL);
    code = field->computeUnsignedField(objMesh, resolutionX, resolutionY, resolutionZ, (float) bandwidth, maxTriCount, maxDepth);

    if (code !=0)
    {
      printf("Error computing unsigned distance field.\n");
      delete field;
      return NULL;
    }

    //printf("Computation completed. Performing sanity check...\n");
    //field->sanityCheck();
  }
  else
  {
    code = field->load(precomputedUnsignedFieldFilename);
    if(code != 0)
    {
      printf("Failed to load precomputed unsigned distance field.\n");
      delete field;
      return NULL;
    }
  }

  ObjMesh * isoMesh = ComputeIsosurface(field, sigma);
  printf("********* Computing signed distance field (%d x %d x %d) *************\n", resolutionX, resolutionY, resolutionZ); fflush(NULL);
  field->offsetDistanceField(-sigma); // shift the computed signed distance field
  code = field->computeInteriorSignedField(isoMesh, resolutionX, resolutionY, resolutionZ, (float) (bandwidth + sigma), maxTriCount, maxDepth);
  delete isoMesh;

  if (code != 0)
  {
    printf("Error recomputing signed distance field.\n");
    delete field;
    return NULL;
  }

  if (subtractSigma)
    field->offsetDistanceField(sigma);

  return field;
}

