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

#include <set>
#include <cfloat>
#include <limits.h>
#include <algorithm>
#include <fstream>

using namespace std;

#include "matrixIO.h"
#include "isosurfaceMesher.h"
#include "marchingCubes.h"
#include "delaunayMesher.h"
#include "objMeshOrientable.h"
#include "performanceCounter.h"

#ifndef M_PI
  #define M_PI 3.1415926525897932384
#endif

IsosurfaceMesher::IsosurfaceMesher(DistanceFieldBase * f)
    : field(f), detailedSurfaceMesh(NULL), isovalue(0.0), angularBound(30.0), radialBound(1.), numInitialSamples(200), splitIsosurfaceMesh(NULL), fieldDiagonal(0), objMeshOctree(NULL), isoMesh(NULL), globalLoopIndex(0)
{
  delaunay.computeVoronoiEdgeModification(true);
  checkDelaunay = saveMarchingCubesObj = false;
  ignoredSplitComponentVtxRatio = 0.01;
  cosAngularBound = 0.5;
  splitComponentIndex = oneMeshLoopIndex = 0;
  marchingCubesMesh = NULL;
}

IsosurfaceMesher::IsosurfaceMesher(ObjMesh * d)
    : field(NULL), detailedSurfaceMesh(d), isovalue(0.0), angularBound(30.0), radialBound(1.), numInitialSamples(200), splitIsosurfaceMesh(NULL), fieldDiagonal(0), objMeshOctree(NULL), isoMesh(NULL), globalLoopIndex(0)
{
  delaunay.computeVoronoiEdgeModification(true);
  checkDelaunay = saveMarchingCubesObj = false;
  ignoredSplitComponentVtxRatio = 0.01;
  cosAngularBound = 0.5;
  splitComponentIndex = oneMeshLoopIndex = 0;
  marchingCubesMesh = NULL;
}

IsosurfaceMesher::~IsosurfaceMesher()
{
  delete isoMesh;
  delete objMeshOctree;
  delete marchingCubesMesh;
}

void IsosurfaceMesher::setStepping(double iso, double a, double r, size_t nis, double ep, Query::Type qt)
{
  queryType = qt;
  epsilon = ep;
  assert(epsilon >= 0 && epsilon <= 1);
  isovalue = iso;
  angularBound = a;
  radialBound = r;
  numInitialSamples = nis;

  //clamp angle bound
  cosAngularBound = cos(angularBound * (M_PI / 180.0));
  if (cosAngularBound < sqrt(3.) / 2.)
    cosAngularBound = sqrt(3.) / 2.;

  if (detailedSurfaceMesh == NULL)
  {
    PerformanceCounter pc;
    pc.StartCounter();
    marchingCubesMesh = MarchingCubes::compute(field, isovalue, 0);
    assert(marchingCubesMesh);
    pc.StopCounter();
    cout << "Finished marching cubes: " << pc.GetElapsedTime() << endl;
    //regroup the marching cubes mesh according to connected components
    splitIsosurfaceMesh = marchingCubesMesh->splitIntoConnectedComponents(0, 0);

    if (saveMarchingCubesObj == false)
    {
      delete marchingCubesMesh;
      marchingCubesMesh = NULL;
    }
  }
  else
    splitIsosurfaceMesh = detailedSurfaceMesh->splitIntoConnectedComponents(0, 0);
  assert(splitIsosurfaceMesh);

  delete isoMesh;
  isoMesh = new ObjMesh;

  if (field)
    fieldDiagonal = field->diagonal();
  else
  {
    Vec3d bmin, bmax;
    detailedSurfaceMesh->getBoundingBox(1.0, &bmin, &bmax);
    fieldDiagonal = len(bmax - bmin);
  }

  splitComponent.resize(splitIsosurfaceMesh->getNumGroups(), NULL);
  for (unsigned int i = 0; i < splitIsosurfaceMesh->getNumGroups(); i++)
  {
    // get one connected component and extract an isosurface from it
    ObjMesh * singleMesh = splitIsosurfaceMesh->extractGroup(i);
    splitComponent[i] = singleMesh;
    assert(singleMesh);
  }

  splitComponentIndex = 0;
}

bool IsosurfaceMesher::endStepping() const
{
  return splitComponentIndex == splitComponent.size();
}

void IsosurfaceMesher::doOneStep()
{
  if (splitComponentIndex == splitComponent.size())
    return;
  ObjMesh * objMesh = splitComponent[splitComponentIndex];
  if (oneMeshLoopIndex == 0)
  {
    initializeOneMesh(objMesh);
  }

  if (addOneTriangle() == false) // return false if it stops
  {
    ObjMesh * mesh = buildCurrentSurfaceMesh();
    if (mesh != NULL)
      isoMesh->appendMesh(mesh);
    splitComponentIndex++;
    oneMeshLoopIndex = 0;
  }
  else
    oneMeshLoopIndex++;
}

bool IsosurfaceMesher::initializeOneMesh(ObjMesh * objMesh)
{
  // create initial samples (run marching cubes, then do low-discrepancy sampling)
  delaunay.clear();

  int maxNumTrianglesInLeafNode = 5;
  int maxTreeDepth = 10;

  //octreeCounter.start();
  delete objMeshOctree;
  objMeshOctree = new ObjMeshOctree<TriangleBasic>(objMesh, maxNumTrianglesInLeafNode, maxTreeDepth);
  //octreeCounter.stop();
  vector<Vec3d> points;
  generateInitialPointSetByDiscrepancy(objMesh, points, numInitialSamples);

  bool success = delaunay.computeDelaunayTetrahedralization(points, epsilon, queryType);

  if (success == false)
  {
    return false;
  }

  // initialize containers to store and query IsoFaces
  radiusSet.clear();
  angleSet.clear();
  faceIters.clear();
  return true;
}

bool IsosurfaceMesher::compute(double o, double a, double r, int nis, double ep, Query::Type qt, int maxNumberOfIterations, double maxTimeSeconds)
{
  cout << "Running isosurfaceMesher" << endl;
  setStepping(o, a, r, nis, ep, qt);

//  marchingCubesMesh->save("MarchingCubes.obj");
//  delaunayUpdateCounter.reset();
//  octreeCounter.reset();
//  intersectionCounter.reset();

  bool timeout = false;
  if (maxTimeSeconds < 0)
    maxTimeSeconds = DBL_MAX;

  if (maxNumberOfIterations < 0)
    maxNumberOfIterations = INT_MAX;
  for (size_t i = 0; i < splitComponent.size(); i++)
  {
    // get one connected component and extract an isosurface from it
    ObjMesh * singleMesh = splitComponent[i];
    if (singleMesh->getNumVertices() < splitIsosurfaceMesh->getNumVertices() * ignoredSplitComponentVtxRatio)
      continue;

    ObjMesh * mesh = computeOneMesh(singleMesh, maxNumberOfIterations, maxTimeSeconds, timeout);

    if (mesh)
    {
      isoMesh->appendMesh(mesh);
      delete mesh;
    }

    if (timeout || maxNumberOfIterations <= 0 || maxTimeSeconds <= 0.0)
      break;
  }

  // clean intermediate vars
  delete splitIsosurfaceMesh;
  splitIsosurfaceMesh = NULL;
  for (size_t i = 0; i < splitComponent.size(); i++)
    delete splitComponent[i];
  splitComponent.clear();

  return timeout;
}

bool IsosurfaceMesher::addOneTriangle(double * targetRadius)
{
  // remove faces deleted in delaunay mesh from radiusSet, angleSet and faceIters
  const VoronoiEdgeMap & deletedVEdges = delaunay.getDeletedVoronoiEdges();
  for (VEdgeCIter it = deletedVEdges.begin(); it != deletedVEdges.end(); it++)
  {
    const UTriKey & tri = it->first;
    IterPairMap::iterator it2 = faceIters.find(tri);
    if (it2 != faceIters.end())
    { // a deleted face is inside face
      // cout << "erase isosurface: " << it2->first.v[0] << " " << it2->first.v[1] << " " << it2->first.v[2] << endl;
      RadiusIter rit = it2->second.first;
      AngleIter ait = it2->second.second;
      radiusSet.erase(rit);
      angleSet.erase(ait);
      faceIters.erase(it2);
    }
  }

  // test whether new faces in delaunay should be added to radiusSet, angleSet and faceIters
  const VoronoiEdgeMap & addedVEdges = delaunay.getAddedVoronoiEdges();

  // cout << numIter << ": added VE Edges: " << addedVEdges.size() << ": ";
  for (VEdgeCIter it = addedVEdges.begin(); it != addedVEdges.end(); it++)
  {
    const UTriKey & tri = it->first;
    const VoronoiEdge & vedge = it->second;
    // build a Voronoi edge from the center of one ball to the center of the other ball, or to infinity
    // test intersection of octree with this Voronoi edge. If yes, the tet face of this Voronoi edge should be one of the IsoFaces
    Vec3d start, dir, isopoint(0.0); // isopoint is the intersection point
    bool isRay = false;
    if (vedge.isFinite())
    {
      start = vedge.start;
      dir = vedge.end - start;
      isRay = false;
    }
    else
    {
      isRay = true;
      start = vedge.start;
      dir = vedge.direction;
    }
    // intersectionCounter.start();

    bool onIsosurface = false;
    {
      Vec3d segmentEnd;
      Vec3d segmentStart = start;

      double minT = DBL_MAX;
      Vec3d direction = dir;
      if (isRay)
      {
        direction *= 1.1 * fieldDiagonal * 100.0;
        segmentEnd = segmentStart + direction; // this line will be long enough to determine intersection
      }
      else
        segmentEnd = segmentStart + direction;

      // Too large value at segmentStart may cause precison problems in the octree. So we swap them if needed.
      if (len2(segmentStart) > len2(segmentEnd))
      {
        Vec3d tmp = segmentStart;
        segmentStart = segmentEnd;
        segmentEnd = tmp;
      }
      double length2 = len2(segmentEnd - segmentStart);
      std::vector<int> triangleList;
      std::vector<Vec3d> intersectionList;

      std::vector<TriangleBasic*> tlist;
      objMeshOctree->lineSegmentIntersection(tlist, segmentStart, segmentEnd, &intersectionList);
      for (size_t i = 0; i < tlist.size(); i++)
        triangleList.push_back(tlist[i]->index());

      for (unsigned i = 0; i < triangleList.size(); i++)
      {
        double t2 = len2(intersectionList[i] - segmentStart) / length2;
        if (t2 < minT)
        {
          minT = t2;
          isopoint = intersectionList[i];
          onIsosurface = true;
        }
      }
    }

    if (onIsosurface)
    {
      IsoFace isoface(tri, delaunay.getVertex(tri[0]), delaunay.getVertex(tri[1]), delaunay.getVertex(tri[2]), isopoint);
      RadiusIter rit = (radiusSet.insert(isoface)).first;
      AngleIter ait = (angleSet.insert(isoface)).first;
      faceIters[tri] = IterPair(rit, ait);
    }
  }

  // compute maximum radius among the surface faces
  if (radiusSet.size() == 0 || angleSet.size() == 0)
  {
    // strange, no iso faces now
    if (targetRadius)
      *targetRadius = 0.;
    return false;
  }

  //cout << radiusSet.size() << endl;

  for (IsoFaceRadiusSet::iterator itr = radiusSet.begin(); itr != radiusSet.end(); itr++)
  {
    IsoFaceRadiusSet::iterator::value_type targetRadiusFace = *itr;
    if (targetRadius)
      *targetRadius = targetRadiusFace.radius;
    if (targetRadiusFace.radius <= radialBound) // requirement fulfilled
    {
      //printf("Fulfilled\n");
      break;
    }

    if (delaunay.addOnePoint(targetRadiusFace.isopoint))
      return true;
    //else
      //cout << targetRadiusFace.isopoint  << endl;
  }

  for (IsoFaceRadiusSet::iterator itr = angleSet.begin(); itr != angleSet.end(); itr++)
  {
    IsoFaceRadiusSet::iterator::value_type targetAngleFace = *itr;
    if (targetRadius)
      *targetRadius = targetAngleFace.radius;
    if (targetAngleFace.maxCosAngle <= cosAngularBound) // requirement fulfilled
    {
      //printf("Fulfilled\n");
      break;
    }

    if (delaunay.addOnePoint(targetAngleFace.isopoint))
      return true;
    //else
      //cout << targetRadiusFace.isopoint  << endl;
  }

  return false;
}

ObjMesh * IsosurfaceMesher::computeOneMesh(ObjMesh * objMesh, int & maxNumberOfIterations, double & maxTimeSeconds, bool & timeout)
{
  // repeat:
  // build Delaunay mesh
  // determine faces intersected by the Voronoi diagram edges
  // check all the faces for the splitting condition (angularBound, radialBound)
  // split the worst face
  timeout = false;
  if (initializeOneMesh(objMesh) == false)
    return NULL;

  oneMeshLoopIndex = 0;
  bool done = false;
  PerformanceCounter loopTimeCounter; // measure elapsed time in the following loop
  loopTimeCounter.StartCounter();
  while (!done)
  {
    // return true if it won't stop
    double targetRadius = 0;
    if (addOneTriangle(&targetRadius) == false)
      break;

    oneMeshLoopIndex++;
    if (oneMeshLoopIndex >= maxNumberOfIterations)
      break;
    loopTimeCounter.StopCounter();
    double timeElapsed = loopTimeCounter.GetElapsedTime();
    if (timeElapsed >= maxTimeSeconds)
    {
      timeout = true;
      break;
    }

    if (oneMeshLoopIndex % 1000 == 0)
      printf("Itr %d: radius=%.5f\n", oneMeshLoopIndex, targetRadius);
  }

  maxNumberOfIterations -= oneMeshLoopIndex;
  loopTimeCounter.StopCounter();
  maxTimeSeconds -= loopTimeCounter.GetElapsedTime();
  cout << "Time spent in refining isosurface: " << loopTimeCounter.GetElapsedTime() << endl;

  if (checkDelaunay)
  {
    cout << "Begin Delaunay check in IsosurfaceMesher: " << endl;
    PerformanceCounter pc;
    bool ret = delaunay.checkDelaunay();
    pc.StopCounter();
    cout << "Time in check: " << pc.GetElapsedTime() << ",  ";
    cout << "Check: " << ret << endl;
  }
  return buildCurrentSurfaceMesh();
}

ObjMesh * IsosurfaceMesher::buildCurrentSurfaceMesh(bool keepAllDelaunayVtx) const
{
  vector<double> vertices;
  vector<int> faces;
  if (keepAllDelaunayVtx)
  {
    vertices.resize(3 * delaunay.getNumVertices());
    for (size_t i = 0; i < delaunay.getNumVertices(); i++)
    {
      Vec3d pos = delaunay.getVertex(i);
      pos.convertToArray(&vertices[3 * i]);
    }
    faces.resize(faceIters.size() * 3);
    int k = 0;
    for (IterPairMap::const_iterator it = faceIters.begin(); it != faceIters.end(); it++, k++)
      memcpy(&faces[3 * k], it->first.indices(), sizeof(int) * 3);
  }
  else
  {
    map<int, int> vertexMap; // vertex delaunay ID -> new surface mesh vtx ID
    // go through all the triangles
    for (IterPairMap::const_iterator it = faceIters.begin(); it != faceIters.end(); it++)
      for (int j = 0; j < 3; j++)
      {
        int vtx = it->first[j]; // one vtx on one triangle
        map<int, int>::iterator itr = vertexMap.find(vtx);
        if (itr == vertexMap.end())
        { // this is a new vtx in vertexMap
          vertexMap[vtx] = vertices.size() / 3;
          Vec3d pos = delaunay.getVertex(vtx);
          for (int i = 0; i < 3; i++)
            vertices.push_back(pos[i]);
        }
        faces.push_back(vertexMap[vtx]);
      }
  }
  return new ObjMesh(vertices.size() / 3, &vertices[0], faces.size() / 3, &faces[0]);
}

// choose some points from objMesh into points. These points should be as far away from each other as possible.
// The number of the points required is numInitialSamples
void IsosurfaceMesher::generateInitialPointSetByDiscrepancy(const ObjMesh * objMesh, std::vector<Vec3d> & points, unsigned int numInitialSamples)
{
  srand(6);
  int numVertices = 0;
  double * vertices = NULL;
  objMesh->exportGeometry(&numVertices, &vertices);
  vector<bool> selected(numVertices, false);

  // select the first vertex
  int p = rand() % numVertices;

  points.clear();
  // put first vertex into points
  points.push_back(vertices + 3 * p);
  selected[p] = true;
  vector<int> selectedInd;
  selectedInd.push_back(p);

  while (points.size() < numInitialSamples)
  {
    double max_distance = 0;
    p = -1;
    for (int i = 0; i < numVertices; i++)
    {
      if (selected[i] == false)
      {
        double cur_distance = DBL_MAX;
        for (size_t j = 0; j < selectedInd.size(); j++)
        {
          Vec3d d;
          for (int k = 0; k < 3; k++)
            d[k] = vertices[3 * selectedInd[j] + k] - vertices[3 * i + k];
          double distance = len2(d);
          if (distance < cur_distance)
            cur_distance = distance;
        }
        if (cur_distance > max_distance)
        {
          max_distance = cur_distance;
          p = i;
        }
      }
    }

    if (p >= 0)
    {
      //new point is found
      points.push_back(vertices + 3 * p);
      selected[p] = true;
      selectedInd.push_back(p);
    }
    else
    {
      numInitialSamples = points.size();
      break;
    }
  }

  // points.push_back(Vec3d(0.0));
  free(vertices);
}

// check intersection of a ray and an octree
// v = segmentStart
// if isRay == true, send a ray starting at v and points toward direction
// else, send a line segment from v to (v + direction)
// store the intersection distance (from v along the line to the intersection point) in intersectionDistance
bool IsosurfaceMesher::intersectionUsingOctree(const Vec3d & segmentStart, const Vec3d & dir, bool isRay, Vec3d & intersectionPoint)
{
  Vec3d segmentEnd;

  double minT = DBL_MAX;

  Vec3d direction = dir;
  if (isRay)
  {
    direction *= 1.1 * fieldDiagonal * 100.0;
    segmentEnd = segmentStart + direction; // this line will be long enough to determine intersection
  }
  else
    segmentEnd = segmentStart + direction;

  double length = len(segmentEnd - segmentStart);

  std::vector<int> triangleList;
  std::vector<Vec3d> intersectionList;
  vector<TriangleBasic*> tlist;
  objMeshOctree->lineSegmentIntersection(tlist, segmentStart, segmentEnd, &intersectionList);
  for (size_t i = 0; i < tlist.size(); i++)
    triangleList.push_back(tlist[i]->index());

  for (unsigned i = 0; i < triangleList.size(); i++)
  {
    double t = len(intersectionList[i] - segmentStart) / length;
    if (t < minT)
    {
      minT = t;
      intersectionPoint = intersectionList[i];
    }
  }

  return minT != DBL_MAX;
}

bool IsosurfaceMesher::enforceManifoldnessAndOrientNormals(ObjMesh* &objMesh)
{
  bool flag1 = false, flag2 = false;
  //remove non-manifold faces and edges
  do
  {
    flag1 = false;
    int removeHangingFaceNum = 0;
    do
    {
      removeHangingFaceNum = objMesh->removeHangingFaces();
      if (removeHangingFaceNum > 0)
        flag1 = true;
    }
    while (removeHangingFaceNum > 0);

    int removeEdge = 0;
    flag2 = false;
    do
    {
      removeEdge = objMesh->removeNonManifoldEdges();
      if (removeEdge > 0)
        flag2 = true;
    }
    while (removeEdge > 0);
  }
  while (flag1 || flag2);

  // process each connected component
  ObjMesh * connectedComponentMesh = objMesh->splitIntoConnectedComponents();
  delete objMesh;
  objMesh = new ObjMesh;

  // for each connected component
  for (unsigned int i = 0; i < connectedComponentMesh->getNumGroups(); i++)
  {
    ObjMesh * component = connectedComponentMesh->extractGroup(i);

    // convert to oriented mesh
    ObjMeshOrientable objMeshOrientable(component, 1, NULL, 0);
    ObjMesh * singleMesh = objMeshOrientable.GenerateOrientedMesh();
    delete component;

    vector<int> group;
    for (unsigned int i = 0; i < singleMesh->getNumGroups(); i++)
      group.push_back(i);
    singleMesh->mergeGroups(group);

    // flip all face normals if orientation is incorrect
    if (singleMesh->computeVolume() < 0)
      for (unsigned int i = 0; i < singleMesh->getNumGroups(); i++)
      {
        ObjMesh::Group * group = (ObjMesh::Group*)singleMesh->getGroupHandle(i);
        for (unsigned int j = 0; j < group->getNumFaces(); j++)
        {
          ObjMesh::Face * face = (ObjMesh::Face*)group->getFaceHandle(j);
          face->reverseVertices();
        }
      }

    objMesh->appendMesh(singleMesh);
    delete singleMesh;
  }

  delete connectedComponentMesh;
  return true;
}

IsosurfaceMesher::IsoFace::IsoFace(const UTriKey & t, const Vec3d & v0, const Vec3d & v1, const Vec3d & v2, const Vec3d & c) : tri(t)
{
  isopoint = c;
  radius = (len(v0 - c) + len(v1 - c) + len(v2 - c)) / 3;
  Vec3d base1 = v1 - v0, base2 = v2 - v0;
  Vec3d base3 = base2 - base1; // = v2 - v1
  base1.normalize();
  base2.normalize();
  base3.normalize();
  double cosAngle[3] = { dot(base1, base2), dot(base1, base3), dot(base2, base3) };
  maxCosAngle = max(cosAngle[0], max(cosAngle[1], cosAngle[2]));
}

bool IsosurfaceMesher::IsoFaceRadiusCompare::operator() (const IsoFace & a, const IsoFace & b) const
{
  if (a.radius > b.radius)
    return true;
  if (a.radius < b.radius)
    return false;
  return a.tri < b.tri;
}

bool IsosurfaceMesher::IsoFaceAngleCompare::operator() (const IsoFace & a, const IsoFace & b) const
{
  if (a.maxCosAngle > b.maxCosAngle)
    return true;
  if (a.maxCosAngle < b.maxCosAngle)
    return false;
  return a.tri < b.tri;
}

ObjMesh * IsosurfaceMesher::getMesh(bool enforceManifold)
{
//  cout << "delaunay update time: " << delaunayUpdateCounter.getElapsedTime() << endl;
//  cout << "octree time: " << octreeCounter.getElapsedTime() << endl;
//  cout << "intersection time: " << intersectionCounter.getElapsedTime() << endl;

  if (enforceManifold)
  {
    // outputMesh->save("non-manifold.obj");
    enforceManifoldnessAndOrientNormals(isoMesh);
  }
  else if (field)
  {
    // orient faces consistently with the distance field gradient
    // iterate over all groups and faces
    for (unsigned int groupIndex = 0; groupIndex < isoMesh->getNumGroups(); groupIndex++)
    {
      const ObjMesh::Group * groupHandle = isoMesh->getGroupHandle(groupIndex);
      for (unsigned int faceIndex = 0; faceIndex < groupHandle->getNumFaces(); faceIndex++)
      {
        ObjMesh::Face * faceHandle = (ObjMesh::Face*) groupHandle->getFaceHandle(faceIndex);
        if (faceHandle->getNumVertices() < 3)
          cout << "Warning: encountered a face (group=" << groupIndex << ",face=" << faceIndex << ") with fewer than 3 vertices." << endl;

        // compute face centroid
        Vec3d centroid(0, 0, 0);
        for (unsigned int vertexIndex = 0; vertexIndex < faceHandle->getNumVertices(); vertexIndex++)
        {
          const ObjMesh::Vertex * vertexHandle = faceHandle->getVertexHandle(vertexIndex);
          Vec3d vertexPos = isoMesh->getPosition(vertexHandle->getPositionIndex());
          centroid += vertexPos;

        }
        if (faceHandle->getNumVertices() > 0)
          centroid *= 1.0 / faceHandle->getNumVertices();

        // reverse face if normal is in the opposite direction to the distance field gradient
        Vec3d normal = isoMesh->computeFaceNormal(*faceHandle);
        Vec3d gradient = field->gradient(centroid);
        if (dot(normal, gradient) < 0)
          faceHandle->reverseVertices();
      }
    }
  }
  return new ObjMesh(*isoMesh);
}

