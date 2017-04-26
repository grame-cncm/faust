/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "mesher" library , Copyright (C) 2016 USC                             *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Danyong Zhao, Yijing Li, Jernej Barbic                  *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Funding: National Science Foundation                                  *
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

#include <limits.h>
#include <vector>
#include <cfloat>
#include <stack>

using namespace std;

#include "tetMesher.h"
#include "triangleTetIntersection.h"
#include "objMeshOrientable.h"
#include "windingNumber.h"
#include "performanceCounter.h"

#ifndef M_PI
  #define M_PI 3.1415926525897932384
#endif

DelaunayMesher::DelaunayBallCompare TetMesher::TetMeshWithRefineInfo::defaultComparor;

TetMesher::TetMesher() : resultTetMesh(delaunay)
{
  objMesh = NULL;
  numSteinerVertices = 0;
}

TetMesh * TetMesher::compute(ObjMesh * inputMesh, double refinementQuality, double alpha, double minDihedral, int maxSteinerVertices, double maxTimeSeconds)
{
  // clean previous data
  delete objMesh;
  objMesh = NULL;
  faceRecoveryDepth = 0;
  //hasMissing = false;
  numSteinerVertices = 0;

  // Deep copy the input objMesh
  objMesh = new ObjMesh(*inputMesh);
  objMesh->removeIsolatedVertices();

  // Merge all groups of the objMesh
  vector <int> gIdx;
  for (size_t i = 0; i < objMesh->getNumGroups(); i++)
    gIdx.push_back(i);
  objMesh->mergeGroups(gIdx);

  // make sure the first four vertices of the triangle mesh are not in the same plane
  if (renumberInitialVertices(objMesh) == false)
  {
    delete objMesh;
    objMesh = NULL;
    return NULL;
  }

  PerformanceCounter counter;
  counter.StartCounter();
  initializeCDT(false); // RM: no face recovery!
  counter.StopCounter();
  double cdtTime = counter.GetElapsedTime();

  if (maxSteinerVertices == -1)
    maxSteinerVertices = INT_MAX;

  if ((maxTimeSeconds >= 0) && (cdtTime >= maxTimeSeconds))
    return delaunay.getMesh();

  double maxRefinementTime = -1.0;
  if (maxTimeSeconds >= 0)
    maxRefinementTime = maxTimeSeconds - cdtTime;
  printf("Starting tet mesh refinement.\n");

  delaunay.buildCDT();

  // Enable the minimal dihedral angle refinement mechanism. If the minimal dihedral angle of a tet is smaller than a threshold, it needs refining.
  if (minDihedral > 0)
    resultTetMesh.enableAngleRefine();

  // Insert all tets (regular balls in the delaunay)
  for (BallCIter it = delaunay.getBallSetBegin(), end = delaunay.getBallSetEnd(); it != end; it++)
  {
    const DelaunayBall * ball = *it;

    if (ball->isInfinite())
      continue;
    resultTetMesh.insert(ball);
  }

  double averageEdgeLength = objMesh->computeAverageEdgeLength();

  //cout << "Average length: " << averageEdgeLength << endl;

  numSteinerVertices = 0;
  counter.StartCounter();
  //First we use edge refine rule (radius/minEdge)
  while ((refineEdge(refinementQuality, alpha * averageEdgeLength) == 0) && (numSteinerVertices < maxSteinerVertices))
  {
    printf("#"); fflush(NULL);
    counter.StopCounter();
    double elapsedTime = counter.GetElapsedTime();
    if ((maxRefinementTime >= 0) && (elapsedTime > maxRefinementTime))
      break;
  }
  printf("\n");

  //Use minimal dihedral angle refinement
  if (minDihedral > 0)
  {
    printf("Enforcing the minimum dihedral angle condition...\n");
    while (refineAngle(minDihedral, alpha * averageEdgeLength) == 0 && numSteinerVertices < maxSteinerVertices)
    {
      printf("#"); fflush(NULL);
      counter.StopCounter();
      double elapsedTime = counter.GetElapsedTime();
      if ((maxRefinementTime >= 0) && (elapsedTime > maxRefinementTime))
        break;
    }
  }

  printf("\n");
  cout << numSteinerVertices << " steiner points inserted." << endl;
  TetMesh * ret = resultTetMesh.getTetMesh();
  //ret->orient();
  return ret;
}

// Make sure the first four vertices of the triangle mesh are not on the same plane
bool TetMesher::renumberInitialVertices(ObjMesh * surfaceMesh)
{
  Vec3d p0 = surfaceMesh->getPosition(0);
  Vec3d p1 = Vec3d(0, 0, 0), p2 = Vec3d(0, 0, 0), p3 = Vec3d(0, 0, 0);
  int v1 = -1, v2 = -1, v3 = -1;
  double max_dis = 1e-10;
  /*The second vertex is different from the first vertex*/
  for (size_t i = 1; i < surfaceMesh->getNumVertices(); i++)
  {
    Vec3d d10 = surfaceMesh->getPosition(i) - p0;
    double dis = dot(d10, d10);
    if (dis > max_dis)
    {
      max_dis = dot(d10, d10);
      p1 = surfaceMesh->getPosition(i);
      v1 = i;
    }
  }
  if (v1 == -1)
    return false; //new TetMesh(0, (double*)NULL, 0, (int*)NULL);     /* The triangle mesh has only one position*/

  p1 = surfaceMesh->getPosition(v1);
  /*The first three vertices are not on the same straight line*/
  Vec3d p10 = p1 - p0;
  p10.normalize();
  max_dis = 0;
  for (size_t i = 1; i < surfaceMesh->getNumVertices(); i++)
  {
    if(i == (size_t)v1)
      continue;
    Vec3d normal = cross(p10, surfaceMesh->getPosition(i) - p0);
    if (dot(normal, normal) > 1e-10)
    {
      p2 = surfaceMesh->getPosition(i);
      double dis = min(len2(p2 - p0), len2(p2 - p1));
      if (dis > max_dis)
      {
        max_dis = dis;
        v2 = i;
      }
    }
  }
  if (v2 == -1)
    return false; // new TetMesh(0, (double*)NULL, 0, (int*)NULL);     /* The triangle mesh has only one line*/

  /*The first four vertices are not on the same plane*/
  p2 = surfaceMesh->getPosition(v2);
  Vec3d p20 = p2 - p0;
  p20.normalize();
  max_dis = 0;
  for (size_t i = 3; i < surfaceMesh->getNumVertices(); i++)
  {
    if (fabs(dot(p20, cross(p10, surfaceMesh->getPosition(i) - p0))) > 0)
    {
      p3 = surfaceMesh->getPosition(i);
      double dis = (std::min)(len2(p3 - p0), (std::min)(len2(p2 - p0), len2(p1 - p0)));
      if (dis > max_dis)
      {
        max_dis = dis;
        v3 = i;
      }
    }
  }
  if (v3 == -1)
    return false; // new TetMesh(0, (double*)NULL, 0, (int*)NULL);     /* The triangle mesh has only one plane*/

  // Sort the first four vertices so that the volume is positive
  p3 = surfaceMesh->getPosition(v3);
  if (dot(p20, cross(p10, p3 - p0)) < 0)
    swap(v2, v3);

  // Permute the objMesh
  vector<int> renumber;
  renumber.resize(surfaceMesh->getNumVertices());

  for (size_t i = 0; i < renumber.size(); i++)
    renumber[i] = i;
  swap(renumber[1], renumber[v1]);

  int overwrite = renumber[v2];
  renumber[v2] = 2;
  for (size_t i = 0; i < renumber.size(); i++)
    if (renumber[i] == 2)
    {
      renumber[i] = overwrite;
      break;
    }
  overwrite = renumber[v3];
  renumber[v3] = 3;
  for (size_t i = 0; i < renumber.size(); i++)
    if (renumber[i] == 3)
    {
      renumber[i] = overwrite;
      break;
    }
  surfaceMesh->renumberVertices(renumber);

  return true;
}

TetMesher::~TetMesher()
{
  delete objMesh;
}

int TetMesher::initializeCDT(bool recovery)
{
  //printf("Entering initializeCDT:\n"); fflush(NULL);
  unsigned nv;
  double *v = NULL;
  const ObjMesh::Group *group = objMesh->getGroupHandle(0);
  if (recovery)
  {
    //get all faces and build neighbors in the triangular mesh
    map<pair<int, int>, vector<int> > neighborBuffer;
    for (unsigned i = 0; i < group->getNumFaces(); i++)
    {
      const ObjMesh::Face face = group->getFace(i);
      int a = face.getVertex(0).getPositionIndex();
      int b = face.getVertex(1).getPositionIndex();
      int c = face.getVertex(2).getPositionIndex();
      pair<int, int> edge[3] = { (a < b ? make_pair(a, b) : make_pair(b, a)), (a < c ? make_pair(a, c) : make_pair(c, a)), (c < b ? make_pair(c, b) : make_pair(b, c)) };
      for (int j = 0; j < 3; j++)
        neighborBuffer[edge[j]].push_back(i);
    }

    neighborSurface.resize(group->getNumFaces());
    for (map<pair<int, int>, vector<int> >::const_iterator itr = neighborBuffer.begin(); itr != neighborBuffer.end(); itr++)
    {

      if (itr->second.size() != 2)
      {
        printf("The input mesh must be a 2-manifold mesh\n");
        exit(3);
      }

      for (size_t i = 0; i < itr->second.size(); i++)
        for (size_t j = i + 1; j < itr->second.size(); j++)
        {
          int t0 = itr->second.at(i);
          int t1 = itr->second.at(j);
          neighborSurface[t0].push_back(t1);
          neighborSurface[t1].push_back(t0);
        }
    }

    for (size_t i = 0; i < neighborSurface.size(); i++)
      if (neighborSurface[i].size() != 3)
      {
        printf("The input mesh must be a triagular mesh\n");
        exit(4);
      }
  }
  objMesh->exportGeometry((int *) &nv, &v);
  vector<Vec3d> objVertices;
  for(size_t i = 0; i < nv; i++)
    objVertices.push_back(&v[3*i]);
  //printf("Before computeDelaunayTetrahedralization:\n"); fflush(NULL);
  delaunay.computeDelaunayTetrahedralization(objVertices);
  //printf("After computeDelaunayTetrahedralization:\n"); fflush(NULL);
  free(v);
  trianglesInTet.clear();

  for (DelaunayMesher::BallCIter itr = delaunay.getBallSetBegin(); itr != delaunay.getBallSetEnd(); itr++)
  {
    const DelaunayMesher::DelaunayBall *ball = *itr;
    if (ball->isRegular())
      insertTet(ball->getVertices());
  }

  //printf("Before segmentRecovery:\n"); fflush(NULL);
  //segmentRecovery(); // TODO: this creates a segfault an we don't really know why...
  //printf("After segmentRecovery:\n"); fflush(NULL);
  flipSurface();

  lost.clear();
  for (unsigned i = 0; i < group->getNumFaces(); i++)
  {
    const ObjMesh::Face face = group->getFace(i);
    int a = face.getVertex(0).getPositionIndex();
    int b = face.getVertex(1).getPositionIndex();
    int c = face.getVertex(2).getPositionIndex();
    UTriKey key = UTriKey(a, b, c);
    if (trianglesInTet.find(key) == trianglesInTet.end())
    {
      lost.push_back(key);
      //printf("Lost face (%d, %d %d)\n", key[0], key[1], key[2]);
    }
  }

  //cout << "Lost size: " << lost.size() << endl;

  //printf("\n");
  if (!lost.empty() && recovery)
    faceRecovery();
  removeOutside();
  return lost.size();
}


int TetMesher::refineAngle(const double angleBound, const double minmimalDist)
{
  TetMeshWithRefineInfo::AngleRefineIterator itr;
  for ( itr = resultTetMesh.getAngleRefineBegin(); itr != resultTetMesh.getAngleRefineEnd(); itr++)
  {
    const DelaunayBallWithRefineInfo  * delaunayBallWithRefineInfo = *itr;
    if (delaunayBallWithRefineInfo->minDihedral > angleBound)
      return 2; // no bad tet to refine

    Vec3d r = delaunayBallWithRefineInfo->getCenter();
    if (delaunayBallWithRefineInfo->visibleTo(r) == false)
    {
      continue; //invisible, find a new bad tet to refine
    }

    if (isTooCloseToOtherVertices(r, minmimalDist))
    {
      //cout << "Too close vertices" << endl;
      continue; //too close to the other vertices, find a new bad tet to refine
    }

    int added = delaunay.addOnePoint(r);
    if (added) // one point added
    {
      for (DelaunayMesher::BallIter itr = delaunay.getBallToDeleteSetBegin(); itr != delaunay.getBallToDeletelSetEnd(); itr++)
        resultTetMesh.remove(*itr);
      for (DelaunayMesher::BallIter itr = delaunay.getBallAddedSetBegin(); itr != delaunay.getBallAddedSetEnd(); itr++)
        resultTetMesh.insert(*itr);
      numSteinerVertices++;
      return 0;
    }
  }

  //No tet to refine due to too sparse steiner points
  return 1;
}

/*
  Ret value
  0: refined
  1: No tet to refine due to enough steiner points
  2: No bad tet to refine
*/
int TetMesher::refineEdge(double refinementQuality, double minmimalDist)
{
//  maxSteinerVertices = 1000;

  TetMeshWithRefineInfo::EdgeRefineIterator itr;
  for ( itr = resultTetMesh.getEdgeRefineBegin(); itr != resultTetMesh.getEdgeRefineEnd(); itr++)
  {
    const DelaunayBallWithRefineInfo  * delaunayBallWithRefineInfo = *itr;
    if (delaunayBallWithRefineInfo->edgeQuality < refinementQuality)
    {
      cout << "All tets are good quality after refining." << endl;
      return 2;            //No bad tet to refine
    }

    Vec3d r = delaunayBallWithRefineInfo->getCenter();
    if (delaunayBallWithRefineInfo->contain(r) >= 0 || delaunayBallWithRefineInfo->visibleTo(r) == false)
      continue;     //invisible, find a new bad tet to refine

    if (isTooCloseToOtherVertices(r, minmimalDist))
      continue;     //too close to other vertices, find a new bad tet to refine

    int added = delaunay.addOnePoint(r);
    if (added)         //One point added
    {
      for (DelaunayMesher::BallIter itr = delaunay.getBallToDeleteSetBegin(); itr != delaunay.getBallToDeletelSetEnd(); itr++)
        resultTetMesh.remove(*itr);
      for (DelaunayMesher::BallIter itr = delaunay.getBallAddedSetBegin(); itr != delaunay.getBallAddedSetEnd(); itr++)
        resultTetMesh.insert(*itr);
      numSteinerVertices++;
      return 0;
    }
  }
  return 1;
}

int TetMesher::removeOutside()
{
  const ObjMesh::Group *group = objMesh->getGroupHandle(0);

  set <UTriKey> surfaceTri;
  for (unsigned i = 0; i < group->getNumFaces(); i++)
  {
    const ObjMesh::Face face = group->getFace(i);
    int a = face.getVertex(0).getPositionIndex();
    int b = face.getVertex(1).getPositionIndex();
    int c = face.getVertex(2).getPositionIndex();
    surfaceTri.insert(UTriKey(a, b, c));
  }
/*
  for (DelaunayMesher::BallCIter itr = delaunay.getBallSetBegin(); itr != delaunay.getBallSetEnd(); itr++)
  {
    if ((*itr)->isInfinite())
      continue;
    for (int j = 0; j < 4; j++)
      insertToFaceElementMap((*itr)->uFaceKey(j), *itr);
  }
  */
  set <DelaunayMesher::DelaunayBall*, DelaunayMesher::DelaunayBallCompare> removeSetCandidate;
  set <DelaunayMesher::DelaunayBall*, DelaunayMesher::DelaunayBallCompare> removeSet;

  for (DelaunayMesher::BallCIter itr = delaunay.getBallSetBegin(); itr != delaunay.getBallSetEnd(); itr++)
  {
    if ((*itr)->isInfinite())
    {
       removeSetCandidate.insert(*itr);
    }
  }

  while (!removeSetCandidate.empty())
  {
    DelaunayMesher::DelaunayBall * ball = *removeSetCandidate.begin();
    removeSetCandidate.erase(removeSetCandidate.begin());
    removeSet.insert(ball);
    if (!ball)
      continue;

    for (int i = 0; i < 4; i++)
    {
      DelaunayMesher::DelaunayBall * neighbor = ball->getNeighbor(i);
      if (surfaceTri.find(ball->uFaceKey(i)) == surfaceTri.end() && removeSet.find(neighbor) == removeSet.end() && removeSetCandidate.find(neighbor) == removeSetCandidate.end())
      {
        Vec3d center = (neighbor->getPosition(0) + neighbor->getPosition(1) + neighbor->getPosition(2) + neighbor->getPosition(3)) / 4;
        double windingNumber = fabs(WindingNumber::computeWindingNumber(objMesh, center));
        if (windingNumber > 0.5)
            continue;

        removeSetCandidate.insert(ball->getNeighbor(i));
      }
    }
  }

  for (DelaunayMesher::BallCIter itr = removeSet.begin(); itr != removeSet.end(); itr++)
    delaunay.removeBall(*itr);

  return removeSet.size();
}


void TetMesher::insertFace(int f1, int f2, int f3)
{
  UTriKey key = UTriKey(f1, f2, f3);
  map<UTriKey, unsigned>::iterator itr = trianglesInTet.find(key);
  if (itr == trianglesInTet.end())
  {
    trianglesInTet[key] = 1;
  }
  else
    itr->second++;
  insertEdge(f1, f2);
  insertEdge(f1, f3);
  insertEdge(f3, f2);
}

void TetMesher::removeFace(int f1, int f2, int f3)
{
  UTriKey key = UTriKey(f1, f2, f3);
  map<UTriKey, unsigned>::iterator itr = trianglesInTet.find(key);
  assert(itr != trianglesInTet.end());
  if (itr->second == 1)
    trianglesInTet.erase(itr);
  else
    itr->second--;
  removeEdge(f1, f2);
  removeEdge(f1, f3);
  removeEdge(f3, f2);
}

void TetMesher::insertEdge(int e1, int e2)
{
  UEdgeKey key(e1, e2);
  map<UEdgeKey, unsigned>::iterator itr = edgesInTet.find(key);
  if (itr == edgesInTet.end())
  {
    edgesInTet[key] = 1;
  }
  else
    itr->second++;
}

void TetMesher::removeEdge(int e1, int e2)
{
  UEdgeKey key(e1, e2);
  map<UEdgeKey, unsigned>::iterator itr = edgesInTet.find(key);
  if (itr->second == 1)
    edgesInTet.erase(itr);
  else
    itr->second--;
}

UEdgeKey find_intersect(UTriKey t1, UTriKey t2)
{
  bool found = false;
  pair<int, int> ret;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (t1[i] == t2[j])
      {
        if (!found)
        {
          found = true;
          ret.first = t1[i];
        }
        else
        {
          ret.second = t1[i];
          break;
        }
      }
  return UEdgeKey(ret.first, ret.second);
}
void TetMesher::formRegion(int face, set<int> &region)
{
  if (region.find(face) != region.end())      // The triangle is already in the region
    return;
  UTriKey vertexIndices = getFace(face);
  if (trianglesInTet.find(vertexIndices) != trianglesInTet.end())
    return;    // The triangle is not missing
  region.insert(face);
  for (unsigned i = 0; i < neighborSurface[face].size(); i++)
  {
    UTriKey neighborVertexIndices = getFace(neighborSurface[face][i]);
    UEdgeKey commonEdge = find_intersect(vertexIndices, neighborVertexIndices);
    if (edgesInTet.find(commonEdge) == edgesInTet.end()) // The common edge is not in the tet
      formRegion(neighborSurface[face][i], region);
  }
}

UTriKey TetMesher::getFace(int index)
{
  const ObjMesh::Face *face = objMesh->getGroupHandle(0)->getFaceHandle(index);
  return UTriKey(face->getVertexHandle(0)->getPositionIndex(), face->getVertexHandle(1)->getPositionIndex(), face->getVertexHandle(2)->getPositionIndex());
}

void TetMesher::faceRecovery()
{
  //printf("Patching\n");
  //tet->save("delaunay.veg");
  for (unsigned int face = 0; face < objMesh->getNumFaces(); face++)
  {
    if (trianglesInTet.find(getFace(face)) != trianglesInTet.end()) // This face is not missing
      continue;
    //printf("Missing\n");
    region.clear();
    formRegion(face, region); // Form a region that is connected missing triangles
    vector<vector<Vec3d> > regionVertices; // n*3 Vec3d array
    regionVertices.resize(region.size());
    int tail = 0;
    for (set<int>::const_iterator i = region.begin(); i != region.end(); i++)
    {
      regionVertices[tail].push_back(objMesh->getPosition(objMesh->getGroupHandle(0)->getFaceHandle(*i)->getVertex(0).getPositionIndex()));
      regionVertices[tail].push_back(objMesh->getPosition(objMesh->getGroupHandle(0)->getFaceHandle(*i)->getVertex(1).getPositionIndex()));
      regionVertices[tail].push_back(objMesh->getPosition(objMesh->getGroupHandle(0)->getFaceHandle(*i)->getVertex(2).getPositionIndex()));
      tail++;
    }

    vector <DelaunayMesher::DelaunayBall*> intersectTet;
    intersectTet.clear();

    // Find all tets that intersect this region
    for (DelaunayMesher::BallCIter itr = delaunay.getBallSetBegin(); itr != delaunay.getBallSetEnd(); itr++)
    {
      DelaunayMesher::DelaunayBall * ball = *itr;
      if (ball->isInfinite())
        continue; // No check for infinite ball
      Vec3d v0 = ball->getPosition(0);
      Vec3d v1 = ball->getPosition(1);
      Vec3d v2 = ball->getPosition(2);
      Vec3d v3 = ball->getPosition(3);
      for (unsigned j = 0; j < region.size(); j++)
      {
        if (TriangleTetIntersection::tetrahedronIntersectTriangle(v0, v1, v2, v3, regionVertices[j][0], regionVertices[j][1], regionVertices[j][2]))
        {
          intersectTet.push_back(ball);
          break;
        }
      }
    }
    //printf("\n");
    vector<UTriKey> boundaryFace;
    boundaryFace.clear();
    map<pair<int, int>, pair<int, int> > neighbor;
    set<pair<int, int> > missingBoundary;
    calculateTetBoundary(intersectTet, boundaryFace);
    calculateTriangleBoundary(region, missingBoundary);
    buildTriangleNeighbor(boundaryFace, neighbor);
    //bool patched = false;
    if (intersectTet.empty()) // Impossible
      continue;
    formTwoCavities(boundaryFace, missingBoundary, neighbor);
    for (unsigned i = 0; i < intersectTet.size(); i++)
    {
      const int * v = intersectTet[i]->getVertices();
      removeTet(v);
      delaunay.removeBall(intersectTet[i]);
    }
    for (unsigned i = 0; i < toAdd.size(); i++)
    {
      insertTet(toAdd[i].data());
      //tet->addElement(toAdd[i][0], toAdd[i][1], toAdd[i][2], toAdd[i][3]);
      delaunay.addBall(toAdd[i].data());
    }
  }
}

void TetMesher::calculateTetBoundary(std::vector<DelaunayMesher::DelaunayBall*>& intersectTet, std::vector<UTriKey>& faceVector)
{
  std::set<UTriKey> faceSet;
  faceSet.clear();
  for (unsigned i = 0; i < intersectTet.size(); i++)
  {
    const int * v = intersectTet[i]->getVertices();
    UTriKey face(v[0], v[1], v[2]);
    set<UTriKey>::iterator itr;
    itr = faceSet.find(face);
    if (itr == faceSet.end())
      faceSet.insert(face);
    else
      faceSet.erase(itr);
    face = UTriKey(v[3], v[1], v[2]);
    itr = faceSet.find(face);
    if (itr == faceSet.end())
      faceSet.insert(face);
    else
      faceSet.erase(itr);
    face = UTriKey(v[0], v[3], v[2]);
    itr = faceSet.find(face);
    if (itr == faceSet.end())
      faceSet.insert(face);
    else
      faceSet.erase(itr);
    face = UTriKey(v[0], v[1], v[3]);
    itr = faceSet.find(face);
    if (itr == faceSet.end())
      faceSet.insert(face);
    else
      faceSet.erase(itr);
  }
  faceVector.clear();
  for (std::set<UTriKey>::iterator i = faceSet.begin(); i != faceSet.end(); i++)
    faceVector.push_back(*i);
}

void TetMesher::calculateTriangleBoundary(set<int>& missingRegion, std::set<std::pair<int, int> >& boundary)
{
  boundary.clear();
  for (set<int>::iterator i = missingRegion.begin(); i != missingRegion.end(); i++)
  {
    int v[3];
    const ObjMesh::Face *face = objMesh->getGroupHandle(0)->getFaceHandle(*i);
    for (unsigned j = 0; j < 3; j++)
      v[j] = face->getVertexHandle(j)->getPositionIndex();
    std::pair<int, int> edge;
    set<std::pair<int, int> >::iterator itr;
    edge = make_pair(v[0], v[1]);
    if (edge.first > edge.second)
      std::swap(edge.first, edge.second);
    itr = boundary.find(edge);
    if (itr == boundary.end())
      boundary.insert(edge);
    else
      boundary.erase(itr);
    edge = make_pair(v[2], v[1]);
    if (edge.first > edge.second)
      std::swap(edge.first, edge.second);
    itr = boundary.find(edge);
    if (itr == boundary.end())
      boundary.insert(edge);
    else
      boundary.erase(itr);
    edge = make_pair(v[0], v[2]);
    if (edge.first > edge.second)
      std::swap(edge.first, edge.second);
    itr = boundary.find(edge);
    if (itr == boundary.end())
      boundary.insert(edge);
    else
      boundary.erase(itr);
  }
}

void TetMesher::buildTriangleNeighbor(std::vector<UTriKey>& mesh, std::map<std::pair<int, int>, std::pair<int, int> >& neighbor)
{
  neighbor.clear();
  for (unsigned i = 0; i < mesh.size(); i++)
  {
    int v[3];
    v[0] = mesh[i][0];
    v[1] = mesh[i][1];
    v[2] = mesh[i][2];
    std::sort(v, v + 3);
    pair<int, int> edge;
    map<pair<int, int>, pair<int, int> >::iterator itr;
    edge = make_pair(v[0], v[1]);
    itr = neighbor.find(edge);
    if (itr == neighbor.end())
      neighbor[edge].first = i;
    else
      neighbor[edge].second = i;
    edge = make_pair(v[1], v[2]);
    itr = neighbor.find(edge);
    if (itr == neighbor.end())
      neighbor[edge].first = i;
    else
      neighbor[edge].second = i;
    edge = make_pair(v[0], v[2]);
    itr = neighbor.find(edge);
    if (itr == neighbor.end())
      neighbor[edge].first = i;
    else
      neighbor[edge].second = i;
  }
}

bool TetMesher::formTwoCavities(std::vector<UTriKey>& faceSet, std::set<std::pair<int, int> >& boundary, std::map<std::pair<int, int>, std::pair<int, int> >& neighborMap)
{
  std::set<int> cavity1;
  std::set<int> cavity2;
  cavity1.clear();
  cavity2.clear();
  cavity1.insert(neighborMap[*boundary.begin()].first);
  toAdd.clear();
  queue<int> q;
  while (!q.empty())
    q.pop();       //q.clear()
  q.push(neighborMap[*boundary.begin()].first);
  while (!q.empty())
  {
    int i = q.front();
    q.pop();
    int v[3];
    v[0] = faceSet[i][0];
    v[1] = faceSet[i][1];
    v[2] = faceSet[i][2];
    std::sort(v, v + 3);
    pair<int, int> edge;
    pair<int, int> twoNeighbors;
    int neighbor;
    map<pair<int, int>, pair<int, int> >::iterator itr;
    edge = make_pair(v[0], v[1]);
    if (boundary.find(edge) == boundary.end())
    {
      twoNeighbors = neighborMap[edge];
      neighbor = (twoNeighbors.first == i ? twoNeighbors.second : twoNeighbors.first);
      if (cavity1.find(neighbor) == cavity1.end())
      {
        cavity1.insert(neighbor);
        q.push(neighbor);
      }
    }
    edge = make_pair(v[1], v[2]);
    if (boundary.find(edge) == boundary.end())
    {
      twoNeighbors = neighborMap[edge];
      neighbor = (twoNeighbors.first == i ? twoNeighbors.second : twoNeighbors.first);
      if (cavity1.find(neighbor) == cavity1.end())
      {
        cavity1.insert(neighbor);
        q.push(neighbor);
      }
    }
    edge = make_pair(v[0], v[2]);
    if (boundary.find(edge) == boundary.end())
    {
      twoNeighbors = neighborMap[edge];
      neighbor = (twoNeighbors.first == i ? twoNeighbors.second : twoNeighbors.first);
      if (cavity1.find(neighbor) == cavity1.end())
      {
        cavity1.insert(neighbor);
        q.push(neighbor);
      }
    }
  }
  cavity2.insert(neighborMap[*boundary.begin()].second);
  while (!q.empty())
    q.pop();       //q.clear()
  q.push(neighborMap[*boundary.begin()].second);
  while (!q.empty())
  {
    int i = q.front();
    q.pop();
    int v[3];
    v[0] = faceSet[i][0];
    v[1] = faceSet[i][1];
    v[2] = faceSet[i][2];
    std::sort(v, v + 3);
    pair<int, int> edge;
    pair<int, int> twoNeighbors;
    int neighbor;
    map<pair<int, int>, pair<int, int> >::iterator itr;
    edge = make_pair(v[0], v[1]);
    if (boundary.find(edge) == boundary.end())
    {
      twoNeighbors = neighborMap[edge];
      neighbor = (twoNeighbors.first == i ? twoNeighbors.second : twoNeighbors.first);
      if (cavity2.find(neighbor) == cavity2.end())
      {
        cavity2.insert(neighbor);
        q.push(neighbor);
      }
    }
    edge = make_pair(v[1], v[2]);
    if (boundary.find(edge) == boundary.end())
    {
      twoNeighbors = neighborMap[edge];
      neighbor = (twoNeighbors.first == i ? twoNeighbors.second : twoNeighbors.first);
      if (cavity2.find(neighbor) == cavity2.end())
      {
        cavity2.insert(neighbor);
        q.push(neighbor);
      }
    }
    edge = make_pair(v[0], v[2]);
    if (boundary.find(edge) == boundary.end())
    {
      twoNeighbors = neighborMap[edge];
      neighbor = (twoNeighbors.first == i ? twoNeighbors.second : twoNeighbors.first);
      if (cavity2.find(neighbor) == cavity2.end())
      {
        cavity2.insert(neighbor);
        q.push(neighbor);
      }
    }
  }
  vector<UTriKey> holeBoundary;
  holeBoundary.clear();
  for (set<int>::iterator i = cavity1.begin(); i != cavity1.end(); i++)
  {
    holeBoundary.push_back(faceSet[*i]);
  }
  bool ret = fillHole(holeBoundary);
  holeBoundary.clear();
  for (set<int>::iterator i = cavity2.begin(); i != cavity2.end(); i++)
  {
    holeBoundary.push_back(faceSet[*i]);
  }
  ret = ret && fillHole(holeBoundary);
  return ret;
}

bool TetMesher::fillHole(std::vector<UTriKey>& holeBoundary)
{
  vector<UTriKey> holeAndBottom;
  holeAndBottom.clear();
  for (set<int>::iterator i = region.begin(); i != region.end(); i++)
  {
    const ObjMesh::Face *face = objMesh->getGroupHandle(0)->getFaceHandle(*i);
    holeAndBottom.push_back(UTriKey(face->getVertexHandle(0)->getPositionIndex(), face->getVertexHandle(1)->getPositionIndex(), face->getVertexHandle(2)->getPositionIndex()));
  }
  for (vector<UTriKey>::iterator i = holeBoundary.begin(); i != holeBoundary.end(); i++)
  {
    holeAndBottom.push_back(UTriKey((*i)[0], (*i)[1], (*i)[2]));
  }

  map<int, int> vertexMap;
  vertexMap.clear();
  vector<int> vertex_reverse;
  vertex_reverse.clear();
  ObjMesh * mesh = new ObjMesh;
  mesh->addGroup("bottom");
  mesh->addGroup("hole");
  for (unsigned i = 0; i < holeAndBottom.size(); i++)
  {
    int v[3] = { holeAndBottom[i][0], holeAndBottom[i][1], holeAndBottom[i][2] };
    for (int j = 0; j < 3; j++)
    {
      if (vertexMap.find(v[j]) == vertexMap.end())
      {
        mesh->addVertexPosition(objMesh->getPosition(v[j]));
        vertexMap.insert(make_pair(v[j], vertexMap.size()));
        vertex_reverse.push_back(v[j]);
      }
      v[j] = vertexMap[v[j]];
    }
  }
  ObjMesh::Group * group = (ObjMesh::Group*) mesh->getGroupHandle(1);
  for (unsigned i = 0; i < holeBoundary.size(); i++)
  {
    int v[3] = { vertexMap[holeBoundary[i][0]], vertexMap[holeBoundary[i][1]], vertexMap[holeBoundary[i][2]] };
    ObjMesh::Face face;
    face.addVertex(ObjMesh::Vertex(v[0]));
    face.addVertex(ObjMesh::Vertex(v[1]));
    face.addVertex(ObjMesh::Vertex(v[2]));
    group->addFace(face);
  }
  group = (ObjMesh::Group*) mesh->getGroupHandle(0);
  for (set<int>::iterator i = region.begin(); i != region.end(); i++)
  {
    const ObjMesh::Face *face = objMesh->getGroupHandle(0)->getFaceHandle(*i);
    int v[3] = { vertexMap[face->getVertexHandle(0)->getPositionIndex()], vertexMap[face->getVertexHandle(1)->getPositionIndex()], vertexMap[face->getVertexHandle(2)->getPositionIndex()] };
    ObjMesh::Face _face;
    _face.addVertex(ObjMesh::Vertex(v[0]));
    _face.addVertex(ObjMesh::Vertex(v[1]));
    _face.addVertex(ObjMesh::Vertex(v[2]));
    group->addFace(_face);
  }
  vector<int> groupIndices;
  groupIndices.push_back(0), groupIndices.push_back(1);
  mesh->mergeGroups(groupIndices);

  ObjMeshOrientable * mesh_orient = NULL;
  try
  {
    mesh_orient = new ObjMeshOrientable(mesh, 1, NULL, 0);
  }
  catch (int)
  {
    delete mesh;
    delete mesh_orient;
    throw 1;
  }

  ObjMesh * meshToDelete = mesh;
  mesh = mesh_orient->GenerateOrientedMesh();

  delete mesh_orient;
  delete meshToDelete;

  group = (ObjMesh::Group*) mesh->getGroupHandle(0);
  if (mesh->computeVolume() < 0)
  {
    ObjMesh::Group group_2("hole");
    for (unsigned i = 0; i < group->getNumFaces(); i++)
    {
      const ObjMesh::Face *face = group->getFaceHandle(i);
      ObjMesh::Face face_2;
      face_2.addVertex(face->getVertex(0));
      face_2.addVertex(face->getVertex(2));
      face_2.addVertex(face->getVertex(1));
      group_2.addFace(face_2);
    }
    mesh->removeAllGroups();
    mesh->addGroup(group_2);
  }

  const int maxFaceRecoveryDepth = 10;
  if (faceRecoveryDepth < maxFaceRecoveryDepth)
  {
    TetMesher mesher;
    mesher.faceRecoveryDepth = faceRecoveryDepth + 1;
    mesher.objMesh = mesh;
    mesher.initializeCDT(false);
    for (DelaunayMesher::BallCIter itr = mesher.delaunay.getBallSetBegin(); itr != mesher.delaunay.getBallSetEnd(); itr++)
    {
      if ((*itr)->isInfinite())
        continue;
      vector<int> tetIndex;
      tetIndex.resize(4);
      for (int j = 0; j < 4; j++)
      {
        tetIndex[j] = vertex_reverse[(*itr)->getVtx(j)];
      }
      toAdd.push_back(tetIndex);
    }
    return true;
  }
  else
    return false;
}

TetMesher::DelaunayBallWithRefineInfo::DelaunayBallWithRefineInfo(const DelaunayMesher::DelaunayBall& parent)
: DelaunayMesher::DelaunayBall(parent)
{
  // compute minimal dihedral
  if (isRegular())
  {
    Vec3d v0 = this->parent.getVertex(v[0]);
    Vec3d v1 = this->parent.getVertex(v[1]);
    Vec3d v2 = this->parent.getVertex(v[2]);
    Vec3d v3 = this->parent.getVertex(v[3]);
    Vec3d p0 = v1 - v0;
    Vec3d p1 = v2 - v0;
    Vec3d p2 = v3 - v0;
    if (dot(cross(p0, p1), p2) < 0)
    {
      swap(v2, v3);
      swap(p1, p2);
    }
    Vec3d n0 = cross(p0, p1);
    Vec3d n1 = cross(p1, p2);
    Vec3d n2 = cross(p2, p0);

    Vec3d p3 = v3 - v1;
    Vec3d p4 = v2 - v1;
    Vec3d n3 = cross(p3, p4);
    n0.normalize();
    n1.normalize();
    n2.normalize();
    n3.normalize();
    double m = dot(n0, n1);
    m = min(m, dot(n0, n2));
    m = min(m, dot(n0, n3));
    m = min(m, dot(n1, n2));
    m = min(m, dot(n1, n3));
    m = min(m, dot(n2, n3));
    minDihedral = acos(-m) / M_PI * 180;

    double minEdge2 = (std::min)((std::min)(len2(p0), len2(p1)), len2(p2));
    minEdge2 = (std::min)((std::min)(len2(p3), len2(p4)), minEdge2);
    minEdge2 = (std::min)(len2(v3 - v2), minEdge2);
    edgeQuality = sqrt(len2(v0 - center) / minEdge2);
  }
  else
  {
    minDihedral = NAN;
    edgeQuality = NAN;
  }
}

bool TetMesher::isTooCloseToOtherVertices(const Vec3d& r, const double minimalDist) const
{
double minimalDist2 = minimalDist * minimalDist;
  for (unsigned int i = 0; i < delaunay.getNumVertices(); i++)
    if (len2(r - delaunay.getVertex(i)) < minimalDist2)
      return true;
  return false;
}


TetMesh * TetMesher::TetMeshWithRefineInfo::getTetMesh()
{
  TetMesh * tetMesh;        // The return tet mesh
  if (edgeRefineBalls.empty())      // No tets, almost impossible to trigger
    tetMesh = new TetMesh(0, (double*)NULL, 0, (int*)NULL);
  else
  {
    //const DelaunayMesher * delaunayMesher = &(*this->begin())->parent;
    int numVertices = delaunayMesher.getNumVertices();
    double * vertex = (double *)malloc(3 * sizeof(double) * numVertices);
    for (int i = 0; i < numVertices; i++)
      delaunayMesher.getVertex(i).convertToArray(vertex + 3 * i);
    int numElements = edgeRefineBalls.size();
    int * elements = (int *)malloc(4 * sizeof(int) * numElements);
    int i = 0;
    for (EdgeRefineIterator itr = edgeRefineBalls.begin(); itr != edgeRefineBalls.end(); itr++)
      memcpy(elements + 4 * (i++), (*itr)->getVertices(), 4 * sizeof(int));
    tetMesh = new TetMesh(numVertices, vertex, numElements, elements);
    free(vertex);
    free(elements);
  }
  return tetMesh;
}

TetMesher::TetMeshWithRefineInfo::TetMeshWithRefineInfo(const DelaunayMesher & delaunayMesher)
  : enabledAngleRefine(false), delaunayMesher(delaunayMesher) {}

TetMesher::TetMeshWithRefineInfo::~TetMeshWithRefineInfo()
{
  for (EdgeRefineIterator itr = edgeRefineBalls.begin(); itr != edgeRefineBalls.end(); itr++)
    delete *itr;
}

// Insert a tet during the refine process
void TetMesher::TetMeshWithRefineInfo::insert(const DelaunayMesher::DelaunayBall * delaunayBall)
{
  DelaunayBallWithRefineInfo * delaunayBallWithRefineInfo = new DelaunayBallWithRefineInfo(*delaunayBall);
  edgeRefineMap.insert(make_pair(delaunayBall, edgeRefineBalls.insert(delaunayBallWithRefineInfo).first));
  if (enabledAngleRefine) angleRefineMap.insert(make_pair(delaunayBall, angleRefineBalls.insert(delaunayBallWithRefineInfo).first));
}

// remove a tet during the refine process
void TetMesher::TetMeshWithRefineInfo::remove(const DelaunayMesher::DelaunayBall * delaunayBall)
{
  map<const DelaunayMesher::DelaunayBall *, EdgeRefineIterator, DelaunayMesher::DelaunayBallCompare>::iterator itr =  edgeRefineMap.find(delaunayBall);
  delete *(itr->second);
  edgeRefineBalls.erase(itr->second);
  edgeRefineMap.erase(itr);
  if (enabledAngleRefine)
  {
    itr = angleRefineMap.find(delaunayBall);
    angleRefineBalls.erase(itr->second);
    angleRefineMap.erase(itr);
  }
}

// Inser a tet
void TetMesher::insertTet(const int* v)
{
  insertFace(v[0], v[1], v[2]);
  insertFace(v[0], v[1], v[3]);
  insertFace(v[0], v[3], v[2]);
  insertFace(v[3], v[1], v[2]);
}

// Remove a tet
void TetMesher::removeTet(const int* v)
{
  removeFace(v[0], v[1], v[2]);
  removeFace(v[0], v[1], v[3]);
  removeFace(v[0], v[3], v[2]);
  removeFace(v[3], v[1], v[2]);
}

int TetMesher::segmentRecovery()
{
  vector <int> groupID;
  for (unsigned i = 0; i < objMesh->getNumGroups(); i++)
    groupID.push_back(i);
  objMesh->mergeGroups(groupID);

  // Insert all edges of the triangular surface to a queue;
  set <UEdgeKey> edgeSet;
  list <OEdgeKey> edgeStack;
  ObjMesh::Group & group = *objMesh->getGroupHandle(0);
  for (unsigned int i = 0; i < group.getNumFaces(); i++)
  {
    const ObjMesh::Face & face = group.getFace(i);
    int v0 = face.getVertex(0).getPositionIndex();
    int v1 = face.getVertex(1).getPositionIndex();
    int v2 = face.getVertex(2).getPositionIndex();

    // Insert three edges into the queu, no orientation
    assert(v0 != v1);
    assert(v2 != v1);
    assert(v0 != v2);
    if (edgeSet.find(UEdgeKey(v0, v1)) == edgeSet.end())
    {
      edgeSet.insert(UEdgeKey(v0, v1));
      edgeStack.push_front(OEdgeKey(v0, v1));
    }
    if (edgeSet.find(UEdgeKey(v1, v2)) == edgeSet.end())
    {
      edgeSet.insert(UEdgeKey(v1, v2));
      edgeStack.push_front(OEdgeKey(v1, v2));
    }
    if (edgeSet.find(UEdgeKey(v2, v0)) == edgeSet.end())
    {
      edgeSet.insert(UEdgeKey(v2, v0));
      edgeStack.push_front(OEdgeKey(v2, v0));
    }
  }

  int level = 2;

  while (true)
  {
    int sum = 0;
    int flipped = 0;
    list <OEdgeKey>::iterator itr = edgeStack.begin();
    while (itr != edgeStack.end())
    {
      OEdgeKey edge = *itr;
      int result;
      if (level < 1000)
      {
        result = delaunay.segmentRecoveryUsingFlip(OEdgeKey(edge[0], edge[1]), level);
        if (result != 0)
        {
          fflush(NULL);
          result = delaunay.segmentRecoveryUsingFlip(OEdgeKey(edge[1], edge[0]), level);
        }
      }
      else
      {
        result = delaunay.segmentRecoveryUsingSteinerPoint(OEdgeKey(edge[0], edge[1]));
        result = delaunay.segmentRecoveryUsingFlip(OEdgeKey(edge[0], edge[1]), level);
      }
      if (result )
      {
      }
      if (!result)
        flipped++;
      sum++;
      //cout << "Next edge" << " " << result << endl;
      //if (!result)
      if (!result)
        edgeStack.erase(itr++);
      else
        itr++;
      continue;
    }
    // No missing edges
    if (edgeStack.empty())
      break;

    // Increase the level of flipping edges
    if (level < 4)
      level++;
    // Using steiner points to recover the edges
    else if (level < 10000)
      level = 10000;
    // Fail to recover
    else
      break;
  }
  return 0;
}

bool TetMesher::TetMeshWithRefineInfo::DelaunayBallEdgeRefineCMP
::operator ()(const DelaunayBallWithRefineInfo* const & p1, const DelaunayBallWithRefineInfo* const & p2)
{
  if (p1->edgeQuality > p2->edgeQuality)
    return true;
  if (p1->edgeQuality < p2->edgeQuality)
    return false;
  return defaultComparor(p1, p2);
}

bool TetMesher::TetMeshWithRefineInfo::DelaunayBallAngleRefineCMP
::operator ()(const DelaunayBallWithRefineInfo* const & p1, const DelaunayBallWithRefineInfo* const & p2)
{
  if (p1->minDihedral < p2->minDihedral)
    return true;
  if (p1->minDihedral > p2->minDihedral)
    return false;
  return defaultComparor(p1, p2);
}

int TetMesher::flipSurface()
{
  //delaunay.getMesh()->save("beforeflipsurface.veg");
  edgesInTet.clear();
  trianglesInTet.clear();
  for (DelaunayMesher::BallCIter itr = delaunay.getBallSetBegin(); itr != delaunay.getBallSetEnd(); itr++)
    if ((*itr)->isRegular())
      insertTet((*itr)->getVertices());

  set <UEdgeKey> edgeQueue;
  ObjMesh::Group & group = *objMesh->getGroupHandle(0);
  for (unsigned int i = 0; i < group.getNumFaces(); i++)
  {
    const ObjMesh::Face & face = group.getFace(i);
    int v0 = face.getVertex(0).getPositionIndex();
    int v1 = face.getVertex(1).getPositionIndex();
    int v2 = face.getVertex(2).getPositionIndex();

    // Insert three edges into the queue, no orientation
    assert(v0 != v1);
    assert(v2 != v1);
    assert(v0 != v2);
    if (edgesInTet.find(UEdgeKey(v0, v1)) == edgesInTet.end())
    {
      edgeQueue.insert(UEdgeKey(v0, v1));
    }
    if (edgesInTet.find(UEdgeKey(v1, v2)) == edgesInTet.end())
      edgeQueue.insert(UEdgeKey(v1, v2));
    if (edgesInTet.find(UEdgeKey(v2, v0)) == edgesInTet.end())
      edgeQueue.insert(UEdgeKey(v2, v0));
  }
  while (true)
  {
    bool recover = false;
    set <UEdgeKey>::iterator itr = edgeQueue.begin();
    while (itr != edgeQueue.end())
    {
      UEdgeKey edge = *itr;
      int f0 = -1, f1 = -1;
      int v0 = -1, v1 = -1;
      for (int i = group.getNumFaces() - 1; i >= 0; i--)
      {
        const ObjMesh::Face & face = group.getFace(i);
        int p0 = face.getVertex(0).getPositionIndex(), p1 = face.getVertex(1).getPositionIndex(), p2 = face.getVertex(2).getPositionIndex();
        if (p0 == edge[0] && p1 == edge[1])
        {
          f0 = i; v0 = p2;
        }
        else if (p1 == edge[0] && p0 == edge[1])
        {
          f1 = i; v1 = p2;
        }
        else if (p1 == edge[0] && p2 == edge[1])
        {
          f0 = i; v0 = p0;
        }
        else if (p2 == edge[0] && p1 == edge[1])
        {
          f1 = i; v1 = p0;
        }
        else if (p2 == edge[0] && p0 == edge[1])
        {
          f0 = i; v0 = p1;
        }
        else if (p0 == edge[0] && p2 == edge[1])
        {
          f1 = i; v1 = p1;
        }
      }
      assert(f0 != -1 && f1 != -1);
      if (edgesInTet.find(UEdgeKey(v0, v1)) != edgesInTet.end())
      {
        //cout << "Flipping surface " << edge[0] << " " << edge[1] << endl;
        group.removeFace((std::max)(f0, f1));
        group.removeFace((std::min)(f0, f1));
        group.addFace(ObjMesh::Face(ObjMesh::Vertex(edge[0]), ObjMesh::Vertex(v1), ObjMesh::Vertex(v0)));
        group.addFace(ObjMesh::Face(ObjMesh::Vertex(edge[1]), ObjMesh::Vertex(v0), ObjMesh::Vertex(v1)));
        recover = true;
        edgeQueue.erase(itr++);
      }
      else
        itr++;

    }
    if (!recover)
    {
      return edgeQueue.size();
    }
  }
  return 0;

  //objMesh->removeAllGroups();
  //objMesh->addGroup(group);
  //objMesh->save("flipped.obj");
}
