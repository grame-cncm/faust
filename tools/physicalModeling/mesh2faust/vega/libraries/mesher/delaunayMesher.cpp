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

#include <algorithm>
#include <queue>
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

#include "delaunayMesher.h"
#include "mat3d.h"
#include "windingNumber.h"
#include "verticesQueryFiltered.h"

static vector<bool> * processed;

DelaunayMesher::DelaunayMesher()
{
  //total = 0;
  query = NULL;
  computeVEdgeModification = false;
  queryType = Query::DOUBLE;
  boundaryMesh = NULL;
  boundaryOctree = NULL;
  nextBallLabel = 0;
}

DelaunayMesher::~DelaunayMesher()
{
  clear();
}

void DelaunayMesher::clear()
{
  for (BallIter itr = ballsToDelete.begin(); itr != ballsToDelete.end(); itr++)
    delete *itr;
  ballsToDelete.clear();
  for (BallIter itr = balls.begin(); itr != balls.end(); itr++)
    delete *itr;
  balls.clear();
  ballsAdded.clear(); // this is a subset of "balls", so no need to do a separate clearing for loop for it
  delete query;
  query = NULL;
  epsilon = 0.0;
  inputVertices.clear();
  queryType = Query::DOUBLE;
  vEdgeDeleted.clear();
  vEdgeAdded.clear();

  delete boundaryMesh;
  boundaryMesh = NULL;
  delete boundaryOctree;
  boundaryOctree = NULL;

  verticesSet.clear();
//  boundaryTriangles.clear();
}

//Warning: the first 4 vertices should not be coplanar to allow successful construction
bool DelaunayMesher::computeDelaunayTetrahedralization(const std::vector<Vec3d> & vertices, double ep, Query::Type qt)
{
  const bool useInfo = true;
  if (vertices.size() < 4 || ep < 0.0)
    return false;
  // clear internal data first
  clear();

  // remove duplicate vertices
  vector<Vec3d> uniqueVertices;
  for (size_t i = 0; i < vertices.size(); i++)
  {
    const Vec3d & v = vertices[i];
    if (verticesSet.find(v) == verticesSet.end())
    {
      verticesSet.insert(v);
      uniqueVertices.push_back(v);
    }
  }
  if (uniqueVertices.size() != vertices.size())
  {
    size_t num = vertices.size() - uniqueVertices.size();
    cout << "Remove " << num << " duplicate " << (num > 1 ? "vertices" : "vertex") << " in DelaunayMesher." << endl;
  }

  if (uniqueVertices.size() < 4)
  {
    cout << "Unique vertices < 4. Cannot generate Delaunay mesh." << endl;
    return false;
  }

  int numVertices = uniqueVertices.size();
  epsilon = ep;
  queryType = qt;

  inputVertices.resize(uniqueVertices.size());
  vertex2ball.resize(uniqueVertices.size());
  for (int i = 0; i < numVertices; i++)
    inputVertices[i] = uniqueVertices[i];

  buildQuery();

  VerticesQuery::Information info;
  if (useInfo)
  {
    query->getInformation(epsilon, info);
    if (info.dimension != 3)
    {
      cout << "Delaunay input dimension is not 3 but " << info.dimension << endl;
      return false;
    }
    if (!info.extremeCCW)
      swap(info.extreme[2], info.extreme[3]);
  }
  else
  {
  }
  // Insert the (nondegenerate) tetrahedron constructed by the call to
  // GetInformation. This is necessary for the circumsphere-visibility
  // algorithm to work correctly.
  if (initialize(info.extreme[0], info.extreme[1], info.extreme[2], info.extreme[3]) == false)
  {
    cout << "Failed to initialize Delaunay" << endl;
    return false;
  }

  // Incrementally update the tetrahedralization.  The set of processed
  // points is maintained to eliminate duplicates, either in the original
  // input points or in the points obtained by snap rounding.
  vector <bool> processed(numVertices, false);
  for (int i = 0; i < 4; ++i)
    processed[info.extreme[i]] = true;

  bool computeVEdge = computeVEdgeModification;
  computeVEdgeModification = false; // shut down VEdge computation in the loop below
  for (int i = 0; i < numVertices; ++i)
  {
    if (processed[i] == false)
    {
      for (BallIter itr = getBallToDeleteSetBegin(); itr != getBallToDeletelSetEnd(); itr++)
        delete *itr;
      ballsToDelete.clear();
      update(i);
      processed[i] = true;
    }
  }


  computeVEdgeModification = computeVEdge;
  if (computeVEdgeModification)
  {
    vEdgeAdded.clear();
    vEdgeDeleted.clear();
    for (BallIter it = balls.begin(); it != balls.end(); it++)
    {
      DelaunayBall * ball = *it;
      for (int j = 0; j < 4; j++)
      {
        UTriKey face = ball->uFaceKey(j);
        if (DelaunayBall::isFaceRegular(face) == false)
          continue; // we don't consider infinite face as Voronoi edge
        VEdgeIter vit = vEdgeAdded.find(face);
        if (vit == vEdgeAdded.end())
          vEdgeAdded[face] = ball->getVoronoiEdge(j);
      }
    }
  }

//  cout << balls.size() << " balls inside Delaunay"<< endl;

  return true;
}

bool DelaunayMesher::addOnePoint(const Vec3d & p)
{

  if (computeVEdgeModification)
  {
    vEdgeAdded.clear();
    vEdgeDeleted.clear();
  }

  for (BallIter itr = getBallToDeleteSetBegin(); itr != getBallToDeletelSetEnd(); itr++)
    delete *itr;
  ballsToDelete.clear();
  ballsAdded.clear();

  if (verticesSet.insert(p).second == false) // insertion failure. P is already in verticesSet
    return false;

  if (boundaryOctree && boundaryMesh)
  {
    // for CDT
    if (fabs(WindingNumber::computeWindingNumber(boundaryMesh, p)) < 0.5)
      return false;
  }

  int index = inputVertices.size();
  inputVertices.push_back(p);
  vertex2ball.push_back(NULL);

  query->addVertex(p);

  return update(index);
}

bool DelaunayMesher::update(int newVtxInd)
{
  // find balls containing the newly added point; these balls will be deleted
  if (ballsToDelete.empty())
  {
    if (boundaryOctree == NULL)
      getBallsContainingPoint(newVtxInd, ballsToDelete);
    else
    {
      Vec3d p = inputVertices[newVtxInd];
      for (BallIter it = balls.begin(); it != balls.end(); it++)
      {
        DelaunayBall * ball = *it;
        if (ball->isInfinite())
          continue; // infinite ball will never be erased in CDT
        if (ball->contain(p) <= 0 && ball->visibleTo(p)) // if the point is visible to the ball
          ballsToDelete.insert(ball);
      }
    }
  }

  if (ballsToDelete.empty())
    return false;

  // because some balls (tets) are deleted, some faces of their neighbors are exposed
  // those exposed faces form a polygon (the boundary of the "cavity")
  // build the exposed faces
  //faces are stored by giving the three integer indices of the vertices of the triangle, and the two neighboring balls (one is the deleted one, the other will not be deleted as it is outside of the cavity)
  vector<pair<OTriKey, pair<DelaunayBall *, DelaunayBall *> > > exposedFaces;
  // note: there is no particular reason for going backwards here
  for (BallSet::reverse_iterator iter = ballsToDelete.rbegin(); iter != ballsToDelete.rend(); iter++)
  {
    DelaunayBall * ball = *iter;
    //const int *v = ball.getVertex();
    //printf("Delete %d %d %d %d\n", v[0] + 1, v[1] + 1, v[2] + 1, v[3] + 1);
    for (int j = 0; j < 4; j++)
    {
      OTriKey face = ball->oFaceKey(j); // this face has orientation pointing outside the tet
      DelaunayBall * neighborBall = ball->nbr[j];
      if (ballsToDelete.find(neighborBall) == ballsToDelete.end()) // if neighbor is not in deleted balls
      {
        pair<OTriKey, pair<DelaunayBall *, DelaunayBall *> > exposedFace(face, pair<DelaunayBall *, DelaunayBall *>(neighborBall, ball));
        exposedFaces.push_back(exposedFace);
      }

      if (computeVEdgeModification && DelaunayBall::isFaceRegular(face))
      {
        UTriKey uface = ball->uFaceKey(j);
        if (vEdgeDeleted.find(uface) == vEdgeDeleted.end())
          vEdgeDeleted[uface] = ball->getVoronoiEdge(j);
      }
    }
    //ball.faces.clear();
  }

  //this map is used to assist finding neighbors for the new balls
  map<UTriKey, DelaunayBall *> neighboringStructure;

  ballsAdded.clear();
  // add new balls connecting the new point and the exposed faces
  for (size_t i = 0; i < exposedFaces.size(); i++)
  {
    OTriKey & face = exposedFaces[i].first; // this face points outside the deleted polyhedron
    DelaunayBall * neighborBall = exposedFaces[i].second.first;
    DelaunayBall * deletedBall = exposedFaces[i].second.second; // the deleted ball
//    printf("Patching %d %d %d\n", face.v[0], face.v[1], face.v[2]);
    // create the new ball, this ball has the correct orientation
    DelaunayBall * ball = createBall(newVtxInd, face[0], face[1], face[2]);
    
    if (ball->isRegular() == false) // an infinite ball. This means that face.third < 0, and face.first and face.second give the edge that is on the boundary of the cavity
    {
      const int * v = deletedBall->getInfiniteBallTriangle(); //The indices v[0],v[1],v[2] of an infinite ball give the triangle that this ball represents
      int otherVtx = v[0] ^ v[1] ^ v[2] ^ face[1] ^ face[2]; // xor
      //printf("Addition %d\n", otherVtx);
      if ((otherVtx != v[0]) && (otherVtx != v[1]) && (otherVtx != v[2]))
        // this should never happen
        return false;
//      assert (ball->contains(otherVtx) != 1); // a vtx of the deleted ball should not be inside the new ball. This means that the normal of the new ball is incorrect
    }
    else
    {
      vertex2ball[face[0]] = ball;
      vertex2ball[face[1]] = ball;
      vertex2ball[face[2]] = ball;
    }
    // build neighboring structure for the new ball
    UTriKey uface(face[0], face[1], face[2]);
    int nbrind = ball->getNeighborIndex(uface);
    assert(nbrind >= 0);
    ball->nbr[nbrind] = neighborBall;
    nbrind = neighborBall->getNeighborIndex(uface);
    assert(nbrind >= 0);
    neighborBall->nbr[nbrind] = ball;
    if (computeVEdgeModification && DelaunayBall::isFaceRegular(uface))
      vEdgeAdded[uface] = neighborBall->getVoronoiEdge(nbrind);

    buildNeighbor(newVtxInd, face[1], face[2], ball, neighboringStructure);
    buildNeighbor(newVtxInd, face[0], face[2], ball, neighboringStructure);
    buildNeighbor(newVtxInd, face[1], face[0], ball, neighboringStructure);

    //printf("Inserting ball: %d %d %d %d\n", ball->v[0], ball->v[1], ball->v[2], ball->v[3]);
//    cout << "inserting " << *ball << endl;
    balls.insert(ball);
    ballsAdded.insert(ball);
  }

  //int tail = balls.size();
  for (BallSet::iterator itr = ballsToDelete.begin(); itr != ballsToDelete.end(); itr++)
    balls.erase(*itr);

  vertex2ball[newVtxInd] = *ballsAdded.begin();
  if (neighboringStructure.size() != 0) //error here
  {
    printf("Neighbor structure error\n");
    return false;
  }
  return true;
}

void DelaunayMesher::getBallsContainingPoint(int vtx, BallSet & containingBalls)
{
  containingBalls.clear();
  // first, get one that contains the given point
  DelaunayBall * ball = getOneBallContainingPoint(vtx);
  BallSet unknown;
  if (ball)
  {
    // search for its neighboring tets to go over all the balls that contains the point
    BallSet candidates;
    candidates.insert(ball);
    while (candidates.size() > 0)
    {
      DelaunayBall * ball = *candidates.begin();
      candidates.erase(candidates.begin());

      for (int j = 0; j < 4; j++)
      {
        DelaunayBall * adj = ball->nbr[j];
        if (adj && candidates.find(adj) == candidates.end() && containingBalls.find(adj) == containingBalls.end())
        {
          int loc = adj->contains(vtx);
          if (loc < 0) // adj contains vtx
            candidates.insert(adj);
          else if (loc == 0)
          {
            assert(adj->isInfinite());
            unknown.insert(adj);
          }
        }
      }
      //if (ball->label == 120)
        //cout << ball->contains(vtx) << ball->getPosition(1) << ball->getPosition(2) << ball->getPosition(3) << endl;
      containingBalls.insert(ball);
    }
  }
  else
    cout << "Error: no balls contain the input point: " << vtx << " " << inputVertices[vtx] << endl;
  for (BallCIter itr = unknown.begin(); itr != unknown.end(); itr++)
    if (containingBalls.find((*itr)->nbr[0]) != containingBalls.end())
      containingBalls.insert(*itr);
  return;
}

DelaunayMesher::DelaunayBall * DelaunayMesher::getOneBallContainingPoint(int vtx)
{
  // find a regular ball to begin searching
  DelaunayBall * ball = *balls.begin();
  if (ball->isInfinite())
  {
    // infinite ball must have a regular neighbor
    for (int i = 0; i < 4; i++)
      if (ball->nbr[i]->isRegular())
      {
        ball = ball->nbr[i];
        break;
      }
  }

  size_t numTet = balls.size();
  for (size_t i = 0; i < numTet; i++)
  {
    assert(ball->isRegular());
    int j = 0;
    for (j = 0; j < 4; j++)
    {
      OTriKey face = ball->oFaceKey(j);
      if (query->toPlane(vtx, face[0], face[1], face[2]) > 0)
      {
        // vtx sees face <v0,v1,v2> from outside the tetrahedron.
        DelaunayBall * nbrBall = ball->nbr[j];
        ball = nbrBall;
        if (nbrBall->isRegular()) // tetra has adjacent tet on that face
          break;                  // Traverse to the tetrahedron sharing the face.
        else 
          return ball;            // We reached a surface face, so the point is outside the hull
      }
    }

    if (j == 4)
      return ball;   // The point is inside all four faces, so the point is inside a tetrahedron.
  }
  // this should never be reached
  return NULL;
}

// use neighboringStructure to connect ball with its neighbors
int DelaunayMesher::buildNeighbor(const UTriKey & face, DelaunayBall * ball, map<UTriKey, DelaunayBall *> & neighboringStructure)
{
  map<UTriKey, DelaunayBall *>::iterator itr = neighboringStructure.find(face);
  if (itr == neighboringStructure.end())
  {
    neighboringStructure[face] = ball;
    return 1;
  }
  else
  {
    DelaunayBall * nbrBall = itr->second;
    int nbrind = nbrBall->getNeighborIndex(face);
    assert(nbrind >= 0);
    nbrBall->nbr[nbrind] = ball;
    nbrind = ball->getNeighborIndex(face);
    ball->nbr[nbrind] = nbrBall;
    neighboringStructure.erase(itr);
    if (computeVEdgeModification && DelaunayBall::isFaceRegular(face))
      vEdgeAdded[face] = ball->getVoronoiEdge(nbrind);
    return 0;
  }
}

bool DelaunayMesher::initialize(int v0, int v1, int v2, int v3)
{
  Vec3d a = inputVertices[v0];
  Vec3d b = inputVertices[v1];
  Vec3d c = inputVertices[v2];
  Vec3d d = inputVertices[v3];
  double volume = dot(b - a, cross(c - a, d - a)); //compute volume
  if (volume <= 0)
    return false;
  
  DelaunayBall * ball0 = NULL, *ball1 = NULL, *ball2 = NULL, *ball3 = NULL, *ball4 = NULL;

  ball0 = createBall(v0, v1, v2, v3); // form a regular ball
  ball1 = createBall(-1, v0, v1, v2);
  ball2 = createBall(-1, v0, v3, v1);
  ball3 = createBall(-1, v0, v2, v3);
  ball4 = createBall(-1, v1, v3, v2);

  balls.insert(ball0);
  balls.insert(ball1);
  balls.insert(ball2);
  balls.insert(ball3);
  balls.insert(ball4);

  assert(ball0->getNeighborIndex(UTriKey(v0, v1, v2)) >= 0);

  // build neighboring structure
  #define ASSIGN_NEIGHBOR(a, b, v0, v1, v2) do { \
    a->nbr[a->getNeighborIndex(UTriKey(v0,v1,v2))] = b; \
    b->nbr[b->getNeighborIndex(UTriKey(v0,v1,v2))] = a; } while(0)

  ASSIGN_NEIGHBOR(ball0, ball1, v0, v1, v2);
//  ball0->nbr[ball0->getNeighborIndex(UTriKey(v0,v1,v2))] = ball1;
  ASSIGN_NEIGHBOR(ball0, ball2, v0, v3, v1);
  ASSIGN_NEIGHBOR(ball0, ball3, v0, v2, v3);
  ASSIGN_NEIGHBOR(ball0, ball4, v1, v3, v2);
  ASSIGN_NEIGHBOR(ball1, ball2, -1, v0, v1);
  ASSIGN_NEIGHBOR(ball1, ball3, -1, v0, v2);
  ASSIGN_NEIGHBOR(ball1, ball4, -1, v1, v2);
  ASSIGN_NEIGHBOR(ball2, ball3, -1, v0, v3);
  ASSIGN_NEIGHBOR(ball2, ball4, -1, v1, v3);
  ASSIGN_NEIGHBOR(ball3, ball4, -1, v2, v3);
  assert(ball0->nbr[0] != NULL);
  vertex2ball[v0] = ball0;
  vertex2ball[v1] = ball0;
  vertex2ball[v2] = ball0;
  vertex2ball[v3] = ball0;
  return true;
}

TetMesh * DelaunayMesher::getMesh() const
{
//  return NULL;
  vector<int> ele;
//  cout << "Building mesh: " << endl;
  for (set<DelaunayBall *, DelaunayBallCompare>::const_iterator i = balls.begin(); i != balls.end(); i++)
  {
    DelaunayBall * ball = *i;
    if (ball->isRegular())
    {
      const int * vtx = ball->v;
      for (int k = 0; k < 4; k++)
        ele.push_back(vtx[k]);
//      cout << *ball << endl;
    }
  }
  vector<double> vertices(3 * inputVertices.size());
  for (unsigned int i = 0; i < inputVertices.size(); i++)
    inputVertices[i].convertToArray(&vertices[i * 3]);
  //printf("%d\n", ele.size());
  return new TetMesh(inputVertices.size(), &vertices[0], ele.size() / 4, &ele[0]);
}

void DelaunayMesher::buildQuery()
{
  if (queryType != Query::RATIONAL && queryType != Query::FILTERED)
  {
    // No scaling for floating point.
    query = new VerticesQuery(inputVertices.size(), inputVertices.data());
    //cout << "Using floating point precision" << endl;
  }
  else if (queryType == Query::RATIONAL)
  {
    query = new VerticesQueryRational(inputVertices.size(), inputVertices.data());
    //cout << "Using exact precision" << endl;
  }
  else
  {
    query = new VerticesQueryFiltered(inputVertices.size(), inputVertices.data(), epsilon);
    //cout << "Using filtered precision with epsilon " << epsilon << endl;
  }
}

// Constructor assumes that the incoming vtx has correct orientation
// Regular ball: v3 is on the positive side of plane(v0, v1, v2)
// Infinite ball: Other vertices on the positive side of (v1, v2, v3)
DelaunayMesher::DelaunayBall::DelaunayBall(int v0, int v1, int v2, int v3, DelaunayMesher * p, label_t l)
    : OTetKey(v0, v1, v2, v3), parent(*p), label(l)
{
  // const double DEGENERATE_RADIUS = 1e10;

  memset(nbr, 0, sizeof(nbr));

  Vec3d p1 = parent.inputVertices[v[1]];
  Vec3d p2 = parent.inputVertices[v[2]];
  Vec3d p3 = parent.inputVertices[v[3]];

  if (v[0] >= 0)  //regular ball
  {
    Vec3d p0 = parent.inputVertices[v[0]];
    // double vol = TetMesh::getTetVolume(&p0,&p1,&p2,&p3);
    // if (vol < 1e-10) 
    //   cout << "problem: tet volume too small: " << vol << endl;

    center = parent.circumcenter(p0, p1, p2, p3);
  }
  else
  {
  }
}

int DelaunayMesher::DelaunayBall::getNeighborIndex(const UTriKey & key) const
{
  for (int i = 0; i < 4; i++)
  {
    UTriKey uface = uFaceKey(i);
    if (uface == key)
      return i;
  }
  return -1;
}

int DelaunayMesher::DelaunayBall::getNeighborIndex(const OTriKey & key) const
{
  for (int i = 0; i < 4; i++)
  {
    OTriKey oface = oFaceKey(i);
    if (oface == key)
      return i;
  }
  return -1;
}

void DelaunayMesher::DelaunayBall::setNeighbor(const UTriKey & key, DelaunayBall * nbrBall)
{
  int ind = getNeighborIndex(key);
  if (ind >= 0)
    nbr[ind] = nbrBall;
}

//return value: 
//1 means that the point is outside the ball
//0 means that the point is on the ball
//-1 means that the point is inside the ball
int DelaunayMesher::DelaunayBall::contains(int newVtx) const
{
  int result = 0;
  if (isRegular())
  {
    int query = parent.query->toCircumsphere(newVtx, v[0], v[1], v[2], v[3]);
    if (query)
      return query;
    int tmpVtx[5];
    memcpy(tmpVtx, v, sizeof(v[0]) * 4);
    tmpVtx[4] = newVtx;

    //Using buble sort
    int numSwaps = 0; // Record the total number of swaps.

    for (int i = 0; i < 5; i++)
      for (int j = 4; j > i; j--)
        if (tmpVtx[j] < tmpVtx[j - 1])
        {
          numSwaps++;
          swap(tmpVtx[j], tmpVtx[j - 1]);
        }

    int oriA = parent.query->toPlane(tmpVtx[4], tmpVtx[1], tmpVtx[2], tmpVtx[3]);
    if (oriA != 0)
      return (numSwaps & 1? oriA: -oriA);

    int oriB = -parent.query->toPlane(tmpVtx[4], tmpVtx[0], tmpVtx[2], tmpVtx[3]);
    // Flip the sign if there are odd number of swaps.
    if (!oriB)
    {
      cout << *this << newVtx << endl;
      cout << parent.inputVertices[v[0]] << parent.inputVertices[v[1]] << parent.inputVertices[v[2]] << parent.inputVertices[v[3]] << parent.inputVertices[newVtx] << endl;
      cout << query << " " << oriA << " " << oriB << endl;
      exit(-9);
    }
    return (numSwaps & 1? oriB: -oriB);
  }
  else
  {
    const int * vtx = getInfiniteBallTriangle();
    // ret = +1: point outside infinite ball
    // ret = -1: point inside infinite ball
    result = parent.query->toPlane(newVtx, vtx[0], vtx[1], vtx[2]);
    return result;
    if (result == 0)
    {
      // For infinite ball, the matters are more complicated when the point is on the plane of the boundary triangle
      // In this case, we further test whether the point is inside the circumcircle of the triangle on that plane
      result = parent.query->toCircumsphere(newVtx, vtx[0], vtx[1], vtx[2]);
      return result;
    }
  }
  return result;
}

int DelaunayMesher::DelaunayBall::contain(const Vec3d & p) const
{
  int result = 0;
  if (isRegular())
    return parent.query->toCircumsphere(p, v[0], v[1], v[2], v[3]);
  else
  {
    const int * vtx = getInfiniteBallTriangle();
    result = parent.query->toPlane(p, vtx[0], vtx[1], vtx[2]);
    if (!result)
      return result;  // Not on the plane
    // If on the plane, check whether it is inside the circumcircle
    return parent.query->toCircumsphere(p, vtx[0], vtx[1], vtx[2]);
  }
}

bool DelaunayMesher::DelaunayBall::visibleTo(const Vec3d & p) const
{
  if (parent.boundaryOctree == NULL)
    return true;
  vector<TriangleBasic*> triangles;
  if (isRegular())
  {
    for (unsigned int j = 0; j < 4; j++)
    {
      Vec3d vtx = parent.inputVertices[v[j]];
      parent.boundaryOctree->lineSegmentIntersection(triangles, p, vtx + (p - vtx) * 1e-10);
      if (triangles.empty() == false)
        return false;
    }
  }
  else // infinity ball case:
    return false;  //in CDT, the boundary can't be removed
  return true;
}

// vertices a, b, c, d have the same distance to circumcenter
// so the circumcenter lies on the perpendicular plane for each edge of the tet
// for edge (ab), the equation for this perpendicular plane is: dot((b - a), (x,y,z)) = dot((b - a), (a+b)/2)
// Form a 3x3 linear systemn with three equations for three edges (ab, ac, ad)
Vec3d DelaunayMesher::circumcenter(const Vec3d & a, const Vec3d & b, const Vec3d & c, const Vec3d & d)
{
  Vec3d n1 = b - a;
  Vec3d n2 = c - a;
  Vec3d n3 = d - a;

  #ifdef USE_MAT3D
    Mat3d mat(n1,n2,n3); //system matrix
    Vec3d rhs = Vec3d(dot(n1, (a + b)), dot(n2, (a + c)), dot(n3, (a + d))) / 2.;
    return inv(mat) * rhs;
  #else
  // Cramer rule for solving linear equations
    Vec3d rhs = Vec3d(dot(n1, (a + b)), dot(n2, (a + c)), dot(n3, (a + d)));
    Vec3d _a = Vec3d(n1[0], n2[0], n3[0]);
    Vec3d _b = Vec3d(n1[1], n2[1], n3[1]);
    Vec3d _c = Vec3d(n1[2], n2[2], n3[2]);

    double _w = det(_a, _b, _c) * 2;
    Vec3d ret = Vec3d(det(rhs, _b, _c), det(_a, rhs, _c), det(_a, _b, rhs)) / _w;
    return ret;
  #endif
}

bool DelaunayMesher::checkDelaunay() const
{
  cout << "Checking delaunay " << endl;
  for (BallIter it = balls.begin(); it != balls.end(); it++)
  {
//    cout << "check ball " << count << endl;
    DelaunayBall * ball = *it;
    for (size_t i = 0; i < inputVertices.size(); i++)
    {
      if (!processed->at(i)) continue;
      int j = i;
      const int * v = ball->getVertices();
      if (j == v[0] || j == v[1] || j == v[2] || j == v[3])
        continue;

      if (ball->contains(j) == -1) //point is inside the ball
      {
        cout << "point " << j << " " << inputVertices[j] << " is inside ball: ";
        if (ball->isRegular())
        {
          cout << " center: " << ball->center << ", r=" << len(ball->getPosition(v[0]) - ball->center) << " length from point to center: " << len(inputVertices[j] - ball->center) << endl;
          cout << "regular ball " << *ball << endl;
        }
        else
        {
          cout << "Infinite " << ball->v[1] << inputVertices[ball->v[1]] << " " << ball->v[2] << inputVertices[ball->v[2]] << " " << ball->v[3] << inputVertices[ball->v[3]] << endl;
        }
        return false;
      }
    }
  }
  return true;
}

Vec3d DelaunayMesher::getFaceNormal(const OTriKey & face) const
{
  const Vec3d & v0 = inputVertices[face[0]];
  const Vec3d & v1 = inputVertices[face[1]];
  const Vec3d v2 = inputVertices[face[2]];
  return norm(cross(v1 - v0, v2 - v0));
}

DelaunayMesher::VoronoiEdge::VoronoiEdge(bool isFinite, const Vec3d & s, const Vec3d & other) : finite(isFinite), start(s) 
{
  if (isFinite)
  {
    end = other;
    direction = Vec3d(0.0);
  }
  else
  {
    direction = other;
    end = Vec3d(0.0);
  }
}

DelaunayMesher::VoronoiEdge DelaunayMesher::DelaunayBall::getVoronoiEdge(int faceIndex) const
{
  VoronoiEdge vedge;
  UTriKey uface = uFaceKey(faceIndex);
  assert(isFaceRegular(uface));
  const DelaunayBall * nbrBall = nbr[faceIndex];
  assert(nbrBall);
  if (isRegular() && nbrBall->isRegular())
  {
    vedge.finite = true;
    vedge.start = center;
    vedge.end = nbrBall->center;
  }
  else
  {
    vedge.finite = false;
    OTriKey oface = oFaceKey(faceIndex);
    if (isRegular() == false)
    {
      assert(nbrBall->isRegular());
      vedge.start = nbrBall->center;
      vedge.direction = (-1) * parent.getFaceNormal(oface);
    }
    else
    {
      vedge.start = center;
      vedge.direction = parent.getFaceNormal(oface);
    }
  }
  //assert(vedge.end.hasNaN() == false);
  //assert(vedge.direction.hasNaN() == false);
  return vedge;
}

bool DelaunayMesher::initializeCDT(TetMesh * inputMesh, double ep, Query::Type qt)
{
  // clean previous data
  clear();
  TetMesh tetMesh(*inputMesh);
  tetMesh.orient();
  epsilon = ep;
  queryType = qt;
  if (tetMesh.getNumVertices() < 4)
    return false;

  // check whether tetMesh is face-manifold
  map<UTriKey, int> faceCount;
  for (int i = 0; i < tetMesh.getNumElements(); i++)
  {
    OTetKey tet(tetMesh.getVertexIndex(i, 0), tetMesh.getVertexIndex(i, 1), tetMesh.getVertexIndex(i, 2), tetMesh.getVertexIndex(i, 3));
    for (int j = 0; j < 4; j++)
    {
      UTriKey face = tet.uFaceKey(j);
      faceCount[face]++;
    }
  }
  for (map<UTriKey, int>::iterator it = faceCount.begin(); it != faceCount.end(); it++)
  {
    if (it->second > 2)
    {
      // non-manifold faces found
      return false;
    }
  }

  // add all points
  inputVertices.resize(tetMesh.getNumVertices());
  for (int i = 0; i < tetMesh.getNumVertices(); i++)
    inputVertices[i] = tetMesh.getVertex(i);
  buildQuery();

  for (int i = 0; i < tetMesh.getNumElements(); i++)
    balls.insert(createBall(tetMesh.getVertexIndex(i, 0), tetMesh.getVertexIndex(i, 1), tetMesh.getVertexIndex(i, 2), tetMesh.getVertexIndex(i, 3)));

  //this map is used to assist in finding neighbors for the new regular balls
  map<UTriKey, DelaunayBall *> neighboringStructure;
  for (BallIter it = balls.begin(); it != balls.end(); it++)
  {
    DelaunayBall * ball = *it;
    for (int j = 0; j < 4; j++)
    {
      UTriKey face = ball->uFaceKey(j);
      buildNeighbor(face, ball, neighboringStructure);
    }
  }

  int * edge = new int[neighboringStructure.size() * 3];
  int k = 0;
  map <UTriKey, DelaunayBall *> infiniteNeighboring; //assist finding neighbors for the new infinite balls

  // for all the surface triangles, we'll consturct its neighboring infinite balls
  for (map<UTriKey, DelaunayBall *>::iterator itr = neighboringStructure.begin(); itr != neighboringStructure.end(); itr++)
  {
    const UTriKey & face = itr->first;
    DelaunayBall * ball = itr->second;

    int faceind = ball->getNeighborIndex(face);
    OTriKey oface = ball->oFaceKey(faceind);

    // record the surface face of the tetMesh
    edge[k++] = oface[0];
    edge[k++] = oface[1];
    edge[k++] = oface[2];

    oface.reverse(); // reverse the oriented face to let it become the neighboring infinity ball's face

    DelaunayBall * newBall = createBall(-1, oface[0], oface[1], oface[2]);
    ball->setNeighbor(face, newBall);
    newBall->setNeighbor(face, ball);

    balls.insert(newBall);

    //build all the neighboring structure for new infinite balls
    const int * v = oface.indices();
    buildNeighbor(-1, v[0], v[1], newBall, infiniteNeighboring);
    buildNeighbor(-1, v[1], v[2], newBall, infiniteNeighboring);
    buildNeighbor(-1, v[0], v[2], newBall, infiniteNeighboring);
  }

  vector<double> vertices(3 * inputVertices.size());
  for (size_t i = 0; i < inputVertices.size(); i++)
    inputVertices[i].convertToArray(&vertices[i * 3]);

  boundaryMesh = new ObjMesh(inputVertices.size(), &vertices[0], neighboringStructure.size(), edge);
  //  boundaryMesh->save("boundary.obj");
  boundaryOctree = new ObjMeshOctree<TriangleBasic>(boundaryMesh, 5, 10, 0);
  printf("Octree built\n");
  delete [] edge;

  return true;
}

std::ostream & operator <<(std::ostream & o, const DelaunayMesher::DelaunayBall & ball)
{
  o << "(" << ball.v[0] << "," << ball.v[1] << "," << ball.v[2] << "," << ball.v[3] << ")";
  return o;
}

DelaunayMesher::DelaunayBall * DelaunayMesher::createBall(int v0, int v1, int v2, int v3)
{
  return new DelaunayBall(v0, v1, v2, v3, this, nextBallLabel++);
}

bool DelaunayMesher::isTetMeshFaceManifold(const TetMesh * tetMesh)
{
  map<UTriKey, int> faceCount;
  for(int i = 0; i < tetMesh->getNumElements(); i++) 
  {
    OTetKey tet(tetMesh->getVertexIndices(i));
    for(int j = 0; j < 4; j++) 
    {
      UTriKey face = tet.uFaceKey(j);
      faceCount[face]++;
    }
  }
  for(map<UTriKey, int>::iterator it = faceCount.begin(); it != faceCount.end(); it++) 
  {
    if(it->second > 2) 
      return false; // non-manifold faces found
  }
  return true;
}

// Remove a ball from the delaunay mesh
void DelaunayMesher::removeBall(DelaunayBall * ball)
{
  if (balls.find(ball) == balls.end())
    return;
  for (int i = 0; i < 4; i++)
  {
    UTriKey key = ball->uFaceKey(i);
    map<UTriKey, DelaunayBall *>::iterator itr = neighboringStructure.find(key);
    if (itr == neighboringStructure.end())	
    {
      neighboringStructure.insert(make_pair(key, ball->nbr[i]));        // A face loses its one neighbor, save it as a hanging face
      ball->nbr[i]->setNeighbor(key, NULL);
    }
    else
    {
      assert(itr->second == ball);
      neighboringStructure.erase(itr);        // A face has no neighbor, remove it
    }
  }
  balls.erase(ball);
  delete ball;
}

DelaunayMesher::DelaunayBall * DelaunayMesher::addBall(const int v0, const int v1, const int v2, const int v3)
{
  DelaunayBall * ball = createBall(v0, v1, v2, v3);
  if (v0 >= 0) 
    vertex2ball[v0] = ball;
  if (v1 >= 0) 
    vertex2ball[v1] = ball;
  if (v2 >= 0) 
    vertex2ball[v2] = ball;
  if (v3 >= 0) 
    vertex2ball[v3] = ball;
  if (balls.find(ball) != balls.end())
    return ball;
  balls.insert(ball);
  for (int i = 0; i < 4; i++)
  {
    UTriKey key = ball->uFaceKey(i);
    map<UTriKey, DelaunayBall *>::iterator itr = neighboringStructure.find(key);
    if (itr == neighboringStructure.end())
      neighboringStructure.insert(make_pair(key, ball)); // A face has only one neighbor, save it as a hanging face
    else // Build neighbor relationship
    {
      ball->nbr[i] = itr->second;
      itr->second->setNeighbor(key, ball);
      neighboringStructure.erase(itr);
    }
  }
  return ball;
}

DelaunayMesher::DelaunayBall * DelaunayMesher::addBall(const int* v)
{
  return addBall(v[0], v[1], v[2], v[3]);
}

int DelaunayMesher::buildCDT()
{
  map<UTriKey, DelaunayBall *>::iterator faceKey = neighboringStructure.begin();

  int * edge = (int*)malloc(neighboringStructure.size() * 3 * sizeof(int));

  int edgeSize = 0;
  // Building infinite ball and neighboring information
  while (faceKey != neighboringStructure.end())
  {
    // Create an infinite ball
    DelaunayBall * regularBall = faceKey->second;
    int faceIndex = regularBall->getNeighborIndex(faceKey->first);

    OTriKey okey = regularBall->oFaceKey(faceIndex);
    edge[edgeSize++] = okey[0];
    edge[edgeSize++] = okey[1];
    edge[edgeSize++] = okey[2];
    DelaunayBall * infiniteBall = createBall(-1, faceKey->first[0], faceKey->first[1], faceKey->first[2]);
    faceKey++;
    balls.insert(infiniteBall);
    for (int i = 0; i < 4; i++)
    {
      UTriKey key = infiniteBall->uFaceKey(i);
      map<UTriKey, DelaunayBall *>::iterator itr = neighboringStructure.find(key);
      if (itr == neighboringStructure.end())
        neighboringStructure.insert(make_pair(key, infiniteBall));
      else
      {
        infiniteBall->nbr[i] = itr->second;
        itr->second->setNeighbor(key, infiniteBall);
        neighboringStructure.erase(itr);
      }
    }
  }

  vector<double> vertices(3 * inputVertices.size());
  for (size_t i = 0; i < inputVertices.size(); i++)
    inputVertices[i].convertToArray(&vertices[i * 3]);

  boundaryMesh = new ObjMesh(inputVertices.size(), vertices.data(), edgeSize / 3, edge);

  boundaryOctree = new ObjMeshOctree<TriangleBasic>(boundaryMesh, 5, 10, 0);
  free(edge);
  return 0;
}

static const int SECT_FACE = 0;
static const int ON_FACE = 1;
static const int SECT_EDGE = 2;
static const int ON_EDGE = 3;
static const int SECT_VERTEX = 4;
static const int ON_VERTEX = 5;
static const int IN_TET = 6;

/*
 * Test whether seg(v0,v1) intersect face(f0,f1,f2), Assume that Volume(f0,f1,f2,v0) must be non-negative
 * 0: seg (f1, f2) causes unflippable
 * 1: seg (f2, f0) causes unflippable
 * 2: seg (f0, f1) causes unflippable
 * 3: flippable
 */

//Permute origin vtx table, first column of each row is the index of the origin
static const int permute[4][4] = { {0, 1, 2, 3}, {1, 2, 0, 3}, {2, 0, 1, 3}, {3, 1, 0, 2} };

static const int FLIPPABLE = 8;
static const int SEMI_FLIPPABLE = 4;

// test wheter seg(v0,v1) intersects face
// if intersect of the boundary of the face, return SEMI_FLIPPABLE + which edge of the face the segement intersects
static int flippable(VerticesQuery * query, const OTriKey &face, const int v0, const int v1)
{
  int onFace = FLIPPABLE;
  for (int i = 0; i < 3; i++)
  {
    OEdgeKey edge = face.oEdgeKey(i);
    int result = query->toPlane(v1, edge[0], edge[1], v0);
    if (result == 1)
      return i;
    else if (result == 0)
      onFace = i;
  }
  return (onFace == FLIPPABLE? FLIPPABLE: SEMI_FLIPPABLE + onFace);
}

// face is on ball1, the opposite face is on ball0
int DelaunayMesher::flip23(const OTriKey& face, DelaunayBall * ball0, DelaunayBall * ball1, int requestNewBallIdx, DelaunayBall ** newBallAroundEdge, int allowFlat)
{
  if (ball0->isInfinite() != ball1->isInfinite())
    return 1; // Can't flip boundary face
  UTriKey uface = UTriKey(face.indices());
  int n0 = ball0->getNeighborIndex(uface);
  int v0 = ball0->getVtx(n0);
  int n1 = ball1->getNeighborIndex(uface);
  int v1 = ball1->getVtx(n1);
  // v0 must on the positive side of face
  if (face[0] >= 0)
  { // a triangular face
    if (query->toPlane(v0, face[0], face[1], face[2]) == -1)
    {
      swap(v0, v1);
    }
    // test whether the face is flippable
    int flippableResult = flippable(query, face, v0, v1);
    if (flippableResult < SEMI_FLIPPABLE)
      return flippableResult;
    if (flippableResult != SEMI_FLIPPABLE + allowFlat && flippableResult != FLIPPABLE)
      return flippableResult;
    for (int i = 0; i < 4; i++)
      if (i != n0)
      {
        OTriKey f = ball0->oFaceKey(i);
        if (query->toPlane(v1, f[0], f[1], f[2]) == 1) // not flippable
          return i;
      }
  }
  else // a boundary edge
  {
  }

  // if it is flippable, remove 2 original tets and add 3 new tets
  removeBall(ball0);
  removeBall(ball1);
  DelaunayBall * newBall[3];
  for (int i = 0; i < 3; i++)
  {
    newBall[i] = addBall(face[OTriKey::triEdgeIndex[i][0]], face[OTriKey::triEdgeIndex[i][1]], v1, v0);
  }
  if (newBallAroundEdge)
    *newBallAroundEdge = newBall[requestNewBallIdx];

  return FLIPPABLE;
}

static void getOtherTwoIndices(const int a, const int b, int & c, int & d)
{
  if (a + b == 3)
  { //segment is (0,3) or (1,2)
    c = (a + 2) & 3;
    d = (b + 2) & 3;
  }
  else
  { // segment isn't (0,3) or (1,2)
    c = 3 - a;
    d = 3 - b;
  }
}

//Get a face number which contains the two vertices, the other vertex is accessed via transpose
static const int faceLookUpTableByTwoVertices[4][4] = { {-1, 2, 3, 1}, {3, -1, 0, 2}, {1, 3, -1, 0}, {2, 0, 1, -1} };

static map<int, int> eleCounter;

int DelaunayMesher::clearCounter(const DelaunayMesher::TetAroundEdge & tetsAroundEdge)
{
  for (DelaunayMesher::TetAroundEdge::const_iterator itr = tetsAroundEdge.begin(); itr != tetsAroundEdge.end(); itr++)
  {
    if (balls.find(itr->third) == balls.end())
      cout << "Missing " << *(itr->third) << endl;
    eleCounter[itr->third->label]--;
  }
  return 0;
}

int DelaunayMesher::getTetsAroundEdge(const OEdgeKey& edge, TetAroundEdge & tetsAroundEdge)
{
  if ((getOneBallBySegment(edge[0], edge[1]) & 255) != ON_VERTEX)
  {
    return 0;
  }

  // Store all Balls with this edge
  DelaunayBall *& ball = vertex2ball[edge[0]];

  // The initial ball, keep its neighbors
  int v0 = ball->getInd(edge[0]);
  int v1 = ball->getInd(edge[1]);
  int currentFaceNumber = faceLookUpTableByTwoVertices[v0][v1];
  int nextFaceNumber = faceLookUpTableByTwoVertices[v1][v0];
  tetsAroundEdge.push_back(make_triple(ball->getVtx(currentFaceNumber), ball->oFaceKey(nextFaceNumber), ball));
  //eleCounter[ball->label]++;
  DelaunayBall * firstBall = ball;
  while (true)
  {
    //cout << *ball << nextFaceNumber << endl;
    //DelaunayBall * pre = ball;
    ball = ball->nbr[nextFaceNumber];
    if (ball == firstBall)
      break; // All balls visited

    v0 = ball->getInd(edge[0]);
    v1 = ball->getInd(edge[1]);
    currentFaceNumber = faceLookUpTableByTwoVertices[v0][v1];
    nextFaceNumber = faceLookUpTableByTwoVertices[v1][v0];
    tetsAroundEdge.push_back(make_triple(ball->getVtx(currentFaceNumber), ball->oFaceKey(nextFaceNumber), ball));
    //eleCounter[ball->label]++;
  }
  return tetsAroundEdge.size();
}

int DelaunayMesher::flip32(const OEdgeKey& edge, const TetAroundEdge & tetsAroundEdge)
{
  vector <int> f;
  TetAroundEdge::const_iterator itr = tetsAroundEdge.begin();
  DelaunayBall * ball0 = itr->third;
  f.push_back((itr++)->first);
  DelaunayBall * ball1 = itr->third;
  f.push_back((itr++)->first);
  DelaunayBall * ball2 = itr->third;
  f.push_back((itr++)->first);

  int v0, v1;
  int flippableResult;

  v0 = edge[1]; v1 = edge[0];
  if (f[0] >= 0 && f[1] >= 0 && f[1] >= 0) // Regular face
  {
    swap(v0, v1);
  }

  flippableResult = flippable(query, OTriKey(f.data()), v0, v1);
  if (flippableResult != FLIPPABLE && flippableResult != SEMI_FLIPPABLE && flippableResult != SEMI_FLIPPABLE+1 && flippableResult != SEMI_FLIPPABLE+2)
    return flippableResult;

  // Remove 3 original tets and add 2 new tets
  removeBall(ball0);
  removeBall(ball1);
  removeBall(ball2);
  addBall(f[0], f[1], f[2], v0);
  addBall(f[0], f[2], f[1], v1);
  return FLIPPABLE;
}

int DelaunayMesher::getTwoBallsByFace(const OTriKey& face, std::pair<DelaunayBall*, DelaunayBall*> & twoBalls)
{
  DelaunayBall * ball = getOneBallByFace(face);
  if (!ball)
    return -1;
  int ind = ball->getNeighborIndex(face);
  if (ind == -1)
    return -2;
  twoBalls = make_pair(ball, ball->nbr[ind]);
  return 0;
}

DelaunayMesher::DelaunayBall* DelaunayMesher::getOneBallByFace(const OTriKey& face)
{
  // Find the segment
  int result = getOneBallBySegment(face[0], face[1]);
  DelaunayBall * & ball = vertex2ball[face[0]];

  if ((result & 255) != ON_VERTEX) // the end point must be on the ball
  {
    printf("Failed to find the segment (%d, %d) in tetmesh\n", face[0], face[1]);
    cout << *ball << endl;
    return NULL;
  }
  else
  {
    while (true)
    {
      // get the two indices of vertices in the ball
      int v0 = ball->getInd(face[0]);
      int v1 = ball->getInd(face[1]);
      int f0, f1;
      getOtherTwoIndices(v0, v1, f0, f1);
      OTriKey f = ball->oFaceKey(f0);
      if (query->toPlane(face[2], f[0], f[1], f[2]) > 0)
        ball = ball->nbr[f0];
      else
      {
        f = ball->oFaceKey(f1);
        if (query->toPlane(face[2], f[0], f[1], f[2]) > 0)
          ball = ball->nbr[f1];
        else
          return ball;
      }
    }
  }
}

/*
 0: intersect with face
 1: on a face
 2: intersect with edge
 3: on an edge
 4: intersect with vertex
 5: on a vertex
 6: in the tet
 */

int DelaunayMesher::getOneBallBySegment(const int start, const int end)
{
  if (start == end) // it's not a segment
    return -6;

  DelaunayBall *  & ball = vertex2ball[start];
  if (ball->isInfinite())
  {
    ball = ball->nbr[0];
  }
  int i;
  while (true)
  {
    if (!ball)
      cout << "Null pointer" << endl;
    int originInd = ball->getInd(start);
      if (ball->isInfinite())
      {
        printf("Infinite ball\n");
        return -2;
      }
      if (originInd == -1)
        return -1;

    //OFaceKey
    int sign[4];
    for (i = 1; i < 4; i++)
    {
      OTriKey face = ball->oFaceKey(permute[originInd][i]);
      if ((sign[i] = query->toPlane(end, face[0], face[1], face[2])) == 1)
        break;
    }
    if (i < 4)
    {
      ball = ball->nbr[permute[originInd][i]]; // go to its neighbor ball
    }
    else
    {
      OTriKey face = ball->oFaceKey(permute[originInd][0]);
      sign[0] = query->toPlane(end, face[0], face[1], face[2]);
      int sumSign = -(sign[1] + sign[2] + sign[3]);
      if (sign[0] == 1)
      {
        switch (sumSign)
        {
          case 1:
            return SECT_VERTEX;
          case 2:
            if (sign[1] == 0)
            {
              return (permute[originInd][2] << 8) | (permute[originInd][3] << 12) | SECT_EDGE;
            }
            else if (sign[2] == 0)
              return (permute[originInd][3] << 8) | (permute[originInd][1] << 12) | SECT_EDGE;
            else //if (sign[3] == 0)
              return (permute[originInd][1] << 8) | (permute[originInd][2] << 12) | SECT_EDGE;
          case 3:
            return SECT_FACE | (permute[originInd][0] << 8);
          default:
            return -3;
        }
      }
      else
      {
        sumSign -= sign[0];
        switch (sumSign)
        {
          //TODO: consider a degenerated tet
          case 1:
            return ON_VERTEX;
          case 2:
            return ON_EDGE;
          case 3:
            return ON_FACE;
          case 4:
            return IN_TET;
          default:
            return -4;
        }
      }
    }
  }
  return -5;
}

int DelaunayMesher::segmentRecoveryUsingFlip(const OEdgeKey & lineSegment, int depth)
{
  const int maxIterations = 100; // needed to avoid an infinite loop
  int iter = -1;
  while (true)
  {
    iter++;
    if (iter >= maxIterations)
      return -3;

    //printf("*"); fflush(NULL);
    OEdgeKey edgeToBeRemoved;
    // find a tet such that the vertex lineSegment[0] is a tet vertex, and the line segment goes through the tet
    // result stores how the line segment goes through the tet
    //    ON_VERTEX: the line segment goes down a tet edge and ends at another tet vertex
    //    SECT_EDGE: the line segment goes down an interior of a tet face, and exits through an edge
    //    SECT_FACE: the line segment goes through the interior of the tet, and exits through the opposite tet interior face
    int result = getOneBallBySegment(lineSegment[0], lineSegment[1]); 
    int locationType = result & 255;
    if (locationType == ON_VERTEX)
    {
      recoveredEdge.insert(UEdgeKey(lineSegment[0], lineSegment[1]));
      return 0; // this edge is already recovered; no more work needed
    }
    else if (locationType == SECT_FACE) 
    { 
      // line segment intersects the interior of the face, try flip23
      int originIdx = vertex2ball[lineSegment[0]]->getInd(lineSegment[0]);
      OTriKey face = vertex2ball[lineSegment[0]]->oFaceKey(originIdx);
      int flipResult = flip23(face, vertex2ball[lineSegment[0]]->nbr[originIdx], vertex2ball[lineSegment[0]]);
      if (flipResult == FLIPPABLE)
        continue; // successfully flipped, search for the next face
      else
      {
        // flip23 did not succeed
        if (flipResult >= SEMI_FLIPPABLE)
          flipResult -= SEMI_FLIPPABLE;
        edgeToBeRemoved = face.oEdgeKey(flipResult);
      }
    }
    else if (locationType == SECT_EDGE)
    {
      int v0 = vertex2ball[lineSegment[0]]->getVtx((result >> 8) & 15);
      int v1 = vertex2ball[lineSegment[0]]->getVtx((result >> 12) & 15);
      edgeToBeRemoved = OEdgeKey(v0, v1);
    }

    if (segmentRemovalUsingFlip(edgeToBeRemoved, depth) != 0)
    {
      // removal failed
      return -2;
    }
  }
  return -1;
}

ostream & operator << (ostream &out, const UTriKey & key)
{
  out << "(" << key[0] << ", " << key[1] << ", " << key[2] << ")";
  return out;
}

int DelaunayMesher::segmentRemovalUsingFlip(const OEdgeKey & edge, int depth)
{
  if (recoveredEdge.find(UEdgeKey(edge[0], edge[1])) != recoveredEdge.end())
    return -8; // a recovered edge can't be removed
  if (--depth < 0)
    return -9;

  TetAroundEdge tetsAroundEdge;
  if (getTetsAroundEdge(edge, tetsAroundEdge) < 3)
  {
    //assert(0);
    return -1;
  }
  for (TetAroundEdge::iterator itr = tetsAroundEdge.begin(); itr != tetsAroundEdge.end(); itr++)
    ++eleCounter[itr->third->label]; // add one reference of the tet

  size_t k = tetsAroundEdge.size() + 1;
  while (tetsAroundEdge.size() > 3)
  {
    if (tetsAroundEdge.size() >= k)
      return 5;
    k = tetsAroundEdge.size();
    TetAroundEdge::iterator itr;
    for (itr = tetsAroundEdge.begin(); itr != tetsAroundEdge.end(); itr++)
    {
      DelaunayBall * ball = itr->third;
      TetAroundEdge::iterator nextItr = itr;
      if (++nextItr == tetsAroundEdge.end())
        nextItr = tetsAroundEdge.begin();
      DelaunayBall * nextBall = nextItr->third;
      if (ball->isInfinite() != nextBall->isInfinite() || (tetsAroundEdge.size() > 4 && ball->isInfinite()))
        continue;
      if (eleCounter[ball->label] > 1 || eleCounter[nextBall->label] > 1)
        continue;
      OTriKey f = itr->second;

      int vIdx = f.getInd(itr->first);
      DelaunayBall * newBallAroundEdge;
      int allowFlat = -1;
      if (tetsAroundEdge.size() == 4)
      {
        allowFlat = vIdx;
      }
      if (flip23(f, nextBall, ball, vIdx, &newBallAroundEdge, allowFlat) == FLIPPABLE)
      {
        // Insert the new tet
        vIdx = 3 - nextItr->second.getInd(edge[0]) - nextItr->second.getInd(edge[1]);
        tetsAroundEdge.insert(itr, make_triple(nextItr->second[vIdx], nextItr->second, newBallAroundEdge));
        eleCounter[newBallAroundEdge->label]++;
        //cout << *newBallAroundEdge << endl;
        // Remove the old two tets
        tetsAroundEdge.erase(itr);
        tetsAroundEdge.erase(nextItr);

        break;
      }
    }
    if (itr == tetsAroundEdge.end())
    {
	// No face is flippable
      if (depth > 0)
      {
        // Try to remove an edge
        for (TetAroundEdge::iterator itr = tetsAroundEdge.begin(); itr != tetsAroundEdge.end(); itr++)
        {
          DelaunayBall * ball = itr->third;
          TetAroundEdge::iterator nextItr = itr;
          if (++nextItr == tetsAroundEdge.end())
            nextItr = tetsAroundEdge.begin();
          DelaunayBall * nextBall = nextItr->third;
          if (ball->isInfinite() || nextBall->isInfinite())
            continue;
          if (eleCounter[ball->label] > 1 || eleCounter[nextBall->label] > 1)
            continue;
          OTriKey f = itr->second;
          int flipResult = flip23(f, nextBall, ball);
          if (flipResult >= 4 && flipResult < 8)
            flipResult -= 4;
          if (flipResult >= 0 && flipResult < 3)
          {
            OEdgeKey e = f.oEdgeKey(flipResult);
            if (segmentRemovalUsingFlip(e, depth) == 0)
            {

              tetsAroundEdge.erase(itr);
              tetsAroundEdge.erase(nextItr);
              break;
            }
          }
        }
      }
      if (itr == tetsAroundEdge.end())
      {
        clearCounter(tetsAroundEdge);
        return -4;
      }
      else
      {
        return -5;
      }
    }
  }
  if ((flip32(edge, tetsAroundEdge)) == FLIPPABLE)
  {
    return 0;
  }
  else
  {
    clearCounter(tetsAroundEdge);
    cout << "FLIP32 fail" << endl;
    return -1;
  }
}

int DelaunayMesher::segmentRecoveryUsingSteinerPoint(const OEdgeKey& edge)
{
  int result = getOneBallBySegment(edge[0], edge[1]);
  int locationType = result & 255;

  OEdgeKey removalEdge;
  if (locationType != SECT_EDGE)
    return 200;
  if (locationType == SECT_EDGE)
  {
    int v0 = vertex2ball[edge[0]]->getVtx((result >> 8) & 15);
    int v1 = vertex2ball[edge[0]]->getVtx((result >> 12) & 15);
    removalEdge = OEdgeKey(v0, v1);
  }
  TetAroundEdge tetAroundEdge;
  vertex2ball[removalEdge[0]] = vertex2ball[edge[0]];
  DelaunayBall *& ball = vertex2ball[removalEdge[0]];
  if (ball->isInfinite())
    ball = ball->nbr[0];

  int v0 = ball->getInd(removalEdge[0]);
  int v1 = ball->getInd(removalEdge[1]);
  int currentFaceNumber = faceLookUpTableByTwoVertices[v0][v1];
  if (ball->getVtx(currentFaceNumber) != edge[0])
  {
    ball = ball->nbr[currentFaceNumber];
  }
  v0 = ball->getInd(removalEdge[0]);
  v1 = ball->getInd(removalEdge[1]);
  currentFaceNumber = faceLookUpTableByTwoVertices[v0][v1];
  assert( ball->getVtx(currentFaceNumber) == edge[0]);
  vertex2ball[removalEdge[0]] = ball;
  getTetsAroundEdge(removalEdge, tetAroundEdge);

  assert(tetAroundEdge.begin()->first == edge[0]);

  int idx = 0;
  int e = -1;
  int reverse = 0;
  assert(tetAroundEdge.size() >= 5);
  for (TetAroundEdge::const_iterator itr = tetAroundEdge.begin(); itr != tetAroundEdge.end(); itr++)
  {
    TetAroundEdge::const_iterator nextItr = itr;
    nextItr++;
    if (nextItr == tetAroundEdge.end())
      nextItr = tetAroundEdge.begin();
    if (itr->first == edge[1])
      e = idx;
    if (itr->first == -1 || nextItr->first == -1)
    {
      if (e != -1)
        reverse = 1;
      else
        reverse = -1;
      idx++;
      continue;
    }
    idx++;
  }
  if (reverse == 0)
  {
    if (e <= 2)
    {
      reverse = -1;
    }
    else
      reverse = 1;
  }

  TetAroundEdge::const_iterator itr = tetAroundEdge.begin();
  if (reverse == -1)
  {
    tetAroundEdge.push_back(*tetAroundEdge.begin());
    while (tetAroundEdge.begin()->first != edge[1])
      tetAroundEdge.pop_front();
  }
  else
  {
    while ((int)tetAroundEdge.size() != e + 1)
      tetAroundEdge.pop_back();
  }

  assert(tetAroundEdge.size() >= 4);

  itr = tetAroundEdge.begin();
  map<OTriKey, DelaunayBall *> cavityNeighbors;
  for (itr++ ; itr != tetAroundEdge.end(); itr++)
  {
    OTriKey face(itr->first, itr->third->getVtxOpposeFace(itr->second), removalEdge[1]);
    cavityNeighbors.insert(make_pair(face, itr->third->getNeighborByFace(face)));
    face = OTriKey(itr->first, removalEdge[0], itr->third->getVtxOpposeFace(itr->second));
    cavityNeighbors.insert(make_pair(face, itr->third->getNeighborByFace(face)));
  }

  tetAroundEdge.pop_front();
  if (reverse == 1)
  {
    OTriKey face(removalEdge[0], removalEdge[1], edge[0]);
    DelaunayBall * ball = (tetAroundEdge.begin())->third;
    assert(ball->getNeighborIndex(face) != -1);
    cavityNeighbors.insert(make_pair(face, ball->getNeighborByFace(face)));
    face = OTriKey(removalEdge[1], removalEdge[0], edge[1]);
    ball = (--tetAroundEdge.end())->third;
    assert(ball->getNeighborIndex(face) != -1);
    cavityNeighbors.insert(make_pair(face, ball->getNeighborByFace(face)));
  }
  else
  {
    OTriKey face(removalEdge[0], removalEdge[1], edge[1]);
    DelaunayBall * ball = (tetAroundEdge.begin())->third;
    assert(ball->getNeighborIndex(face) != -1);
    cavityNeighbors.insert(make_pair(face, ball->getNeighborByFace(face)));
    face = OTriKey(removalEdge[1], removalEdge[0], edge[0]);
    ball = (--tetAroundEdge.end())->third;
    assert(ball->getNeighborIndex(face) != -1);
    cavityNeighbors.insert(make_pair(face, ball->getNeighborByFace(face)));
  }

  //Calculate the gravity center

  Vec3d center(0, 0, 0);
  double volume = 0;
  for (itr = tetAroundEdge.begin(); itr != tetAroundEdge.end(); itr++)
  {
    DelaunayBall * ball = itr->third;
    Vec3d c = (ball->getPosition(0) + ball->getPosition(1) + ball->getPosition(2) + ball->getPosition(3)) / 4;
    double v = TetMesh::getTetVolume(ball->getPosition(0), ball->getPosition(1), ball->getPosition(2), ball->getPosition(3));
    assert(v > 0);
    center += c * v;
    volume += v;
  }
  center /= volume;

  //Check all volumes
  for (map<OTriKey, DelaunayBall *>::iterator itr = cavityNeighbors.begin(); itr != cavityNeighbors.end(); itr++)
  {
    OTriKey face = itr->first;
    assert (query->toPlane(center, face[0], face[1], face[2]) == -1);
  }

  // Add the Steiner point
  int newVtx = inputVertices.size();
  inputVertices.push_back(center);
  query->addVertex(center);
  vertex2ball.push_back(NULL);

  // Remove old balls

  for (itr = tetAroundEdge.begin(); itr != tetAroundEdge.end(); itr++)
  {
    DelaunayBall * ball = itr->third;
    balls.erase(ball);
    delete ball;
  }

  // Add new balls
  map<UTriKey, DelaunayBall *> hangingFaces;
  for (map<OTriKey, DelaunayBall *>::iterator itr = cavityNeighbors.begin(); itr != cavityNeighbors.end(); itr++)
  {

    OTriKey oface = itr->first;
    DelaunayBall * ball = createBall(oface[0], oface[2], oface[1], newVtx);
    balls.insert(ball);
    vertex2ball[oface[0]] = vertex2ball[oface[1]] = vertex2ball[oface[2]] = vertex2ball[newVtx] = ball;
    //set boundary neighbor
    UTriKey uface(oface[0], oface[1], oface[2]);
    assert(ball->getNeighborIndex(uface) != -1);
    ball->setNeighbor(uface, itr->second);
    itr->second->setNeighbor(uface, ball);
    assert(itr->second->getNeighborIndex(uface) != -1);

    //set inter neighbor
    for (int i = 0; i < 4; i++)
      if (ball->nbr[i] == NULL)
      {
        UTriKey uface = ball->uFaceKey(i);
        map<UTriKey, DelaunayBall *>::iterator iter = hangingFaces.find(uface);
        if (iter == hangingFaces.end())
          hangingFaces.insert(make_pair(uface, ball));
        else
        {
          ball->nbr[i] = iter->second;
          iter->second->setNeighbor(uface, ball);
          hangingFaces.erase(iter);
        }
      }
  }
 // assert(hangingFaces.empty());
  return 100;
}

