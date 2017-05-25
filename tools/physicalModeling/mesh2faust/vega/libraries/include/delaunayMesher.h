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

/*
  Compute 3D Delaunay tetrahedralization of a set of input points in 3D.
  The tetrahedralization can be updated incrementally by adding new points.
*/

#ifndef _DELAUNAYMESHER_H_
#define _DELAUNAYMESHER_H_

#include <stddef.h>
#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include "objMeshOctree.h"
#include "vec3d.h"
#include "vegalong.h"
#include "triangle.h"
#include "triple.h"
#include "tetMesh.h"
#include "query.h"
#include "tetKey.h"
#include "triKey.h"

class TetMesh;
class VerticesQuery;

class DelaunayMesher
{
public:
  DelaunayMesher();
  virtual ~DelaunayMesher();

  /***************************************************************************
   *              Basic Functions for Delaunay Tetrahedralization            *
   ***************************************************************************/
  // compute Delaunay tetrahedralization of a set of input points
  // must have points.size() >= 4
  // Query::Type: choice of precision used in the Delaunay mesher
  //              DOUBLE: double precision  
  //              RATIONAL: high-precision arithmetics  
  //              FILTERED: trade-off between DOUBLE and RATIONAL
  // epsilon: internal accuracy parameter for queryType=FILTERED, on [0,1]
  //          the larger the value, the more computation will be done in high-precision arithmetics
  //          epsilon == 0: all computation in double precision
  //          epsilon == 1: all computation in high-precision
  // returns true upon success, and false upon failure (degeneracy)
  // use getMesh() to get the result
  bool computeDelaunayTetrahedralization(const std::vector<Vec3d> & points,
    double epsilon = 1e-9, Query::Type queryType = Query::FILTERED);

  // return the current Delaunay mesh
  TetMesh * getMesh() const;

  // after computeDelaunayTetrahedralization, insert one additional point into the tetrahedralization
  bool addOnePoint(const Vec3d & p);
  size_t getNumVertices() const { return inputVertices.size(); } // get the total number of input vertices 
  const Vec3d & getVertex(int index) const { return inputVertices[index]; } // get the position of an input vertex

  // clear the mesh to empty (one can then call computeDelaunayTetrahedralization on a new input)
  void clear();

  // **********************************************************************************
  // All functionality below here mostly exists to support our isomesher and tetMesher
  // We do not expect functions below here to be of general-purpose use
  // **********************************************************************************

  /***************************************************************************
   *  Functions for CDT (Constrained Delaunay Tetrahedralization)            *
   *                                                                         *
   ***************************************************************************/

  // initialize the Constrained Delaunay Tetrahedralization algorithm; to conform to the surface faces of "mesh"
  // the tet mesh "mesh" must be manifold and free of self-intersections
  // further calls to this->addOnePoint() will incrementally rebuild the tetrahedralization while preserving the constrained Delaunay property
  bool initializeCDT(TetMesh * mesh, double epsilon = 1e-6, Query::Type queryType = Query::DOUBLE);

  // Must do remove outside and all infite balls first
  int buildCDT();
  // get the surface mesh of the tet mesh "mesh" passed to initializeCDT (used in the Constrained Delaunay Tetrahedralization)
  inline const ObjMesh * getCDTBoundaryMesh() const { return boundaryMesh; }

  /***************************************************************************
   *                      Voronoi Edge Query Functions                       *
   ***************************************************************************/

  // if input is true, DelaunayMesher will record Voronoi Edge update information for each subsequent operation (computeDelaunayTetrahedralization or addOnePoint)
  // get last Voronoi Edge update by calling getDeletedVoronoiEdges() and getAddedVoronoiEdges
  void computeVoronoiEdgeModification(bool compute = true) { computeVEdgeModification = compute; }

  // A struct for Voronoi Edge
  // A Voronoi Edge is the line connecting two adjacent tet centers in Delaunay, or an infinite line starting at one border tet center,
  // and pointing outside perpendicular to a border face on this tet
  struct VoronoiEdge
  {
    bool finite; //whether this edge has finite length
    Vec3d start; // start point of the edge
    Vec3d end;   // end point if it's not infinite, otherwise undefined
    Vec3d direction; // direction of the edge if it's infinite, otherwise undefined
    VoronoiEdge() : finite(true), start(0.0), end(0.0), direction(0.0) {}
    VoronoiEdge(bool isFinite, const Vec3d & start, const Vec3d & other);
    bool isFinite() const { return finite; }
  };

  typedef std::map<UTriKey, VoronoiEdge> VoronoiEdgeMap;
  typedef VoronoiEdgeMap::iterator VEdgeIter;
  typedef VoronoiEdgeMap::const_iterator VEdgeCIter;

  // vEdgeDeleted and vEdgeAdded will hold Voronoi edges only for last operation on Delaunay
  // e.g. when addOnePoint() is called, vEdgeDeleted is reset and only stores the edges deleted by the last addOnePoint() call
  const VoronoiEdgeMap & getDeletedVoronoiEdges() const { return vEdgeDeleted; }
  const VoronoiEdgeMap & getAddedVoronoiEdges() const { return vEdgeAdded; }

  /***************************************************************************
   *                     Delaunay Ball Query Functions                       *
   ***************************************************************************/

  // Delaunay Balls are used for representing Delaunay
  typedef vegaunsignedlong label_t;
  struct DelaunayBall;
  struct DelaunayBallCompare
  {
    bool operator() (const DelaunayBall * const & p1, const DelaunayBall * const & p2) const { return p1->label < p2->label; }
  };

  typedef std::set<DelaunayBall *, DelaunayBallCompare> BallSet;
  typedef BallSet::iterator BallIter;
  typedef BallSet::const_iterator BallCIter;

  // used to traverse all the balls
  inline BallCIter getBallSetBegin() const { return balls.begin(); }
  inline BallCIter getBallSetEnd() const { return balls.end(); }

  // used to traverse all the ballsToDelete
  inline BallCIter getBallToDeleteSetBegin() const { return ballsToDelete.begin(); }
  inline BallCIter getBallToDeletelSetEnd() const { return ballsToDelete.end(); }

  // used to traverse all the ballsAdded
  inline BallCIter getBallAddedSetBegin() const { return ballsAdded.begin(); }
  inline BallCIter getBallAddedSetEnd() const { return ballsAdded.end(); }

  // There're two kinds of Delaunay Balls: regular and infinite
  // Regular ball (constructor input parameter v0 >= 0) is built by four vertices and represent a tetrahedron.
  // Infinite ball (constructor input parameter v0 < 0) is a ball with infinite radius representing the half space separated by a border face of the Delaunay
  // the other three vtx indices of one infinite ball give the border face triangle on the convex hull, their orientation points inside the convex hull
  // Infinite ball's center is at infinity, on a line perpendicular to the border face and intersecting the face at its circumcenter
  // In short, regular ball represents the space inside one tetrahedron, infinite ball represents the empty space outside one border face on the convex hull
  struct DelaunayBall : public OTetKey
  {
    // get vertex of this ball
    // if it's infinite ball, getVtx(0) returns -1
    inline int getVtx(int ind) const { return v[ind]; }
    // get the array stores the 4 vtx indices
    inline const int * getVertices() const {return v;}
    // get the position of vertices
    inline Vec3d getPosition(int ind) const { return parent.getVertex(v[ind]); }

    inline bool isRegular() const { return v[0] >= 0; }
    inline bool isInfinite() const { return v[0] < 0; }

    // get ball center if it's regular ball
    inline const Vec3d & getCenter() const { return center; }

    // for regular ball, return >0 for outside, ==0 for on the ball, <0 for inside
    // for infinite ball, return >0 for on the inner side of the border face (or the plane the face lies on), ==0 for on the plane, <0 for on the outside of the border face
    int contain(const Vec3d & p) const;
    // Used only in CDT. Always return false for infinite ball
    // For regular ball, if atleast one of the four ball vtx cannot be seen from p because the CDT boundary mesh obscures the sight, return false. Otherwise return true
    // This can be tested by creating a line segment from p to one ball vtx and test intersection of this line segment with boundary mesh
    // Notice that if the ball vtx is a mesh vtx of the boundary mesh, this does not counted as one valid intersection in this case
    bool visibleTo(const Vec3d & p) const;
    inline DelaunayBall * getNeighbor(const int ind) const { return nbr[ind]; }

  protected:

    // ==================== Member Vars =================================

    const DelaunayMesher & parent; // pointer to DelaunayMesher

    Vec3d center; //for regular ball, the center

    // neighboring balls to this ball; there are always four neighbors
    // regular ball: for every face of this tet, there is a neighboring tet across that face (may be an infinite ball)
    // infinite ball: the border face (triangle) has three neighbors, one for each face edge; neighbors of the ball are the regular ball across the triangle, and the three infintie balls corresponding to the convex hull neighboring triangles
    DelaunayBall * nbr[4];

    label_t label; //label unique to every Delaunay Ball

    // ==================== End Member Vars =============================

    DelaunayBall(int v0, int v1, int v2, int v3, DelaunayMesher * parent, label_t label);

    //return value:
    //1 means point is outside the ball
    //0 means point is on the ball
    //-1 means point is inside the ball
    int contains(int vtx) const;

    // A regular face is one face in Delaunay. Two Delaunay Balls (regular vs. regular, or regular vs. infinite) share one regular face
    // An irregular face is one line segment (f.v[1], f.v[2]) on a face.
    // Two infinite balls share an irregular face. This is actually two border faces share one triangle edge.
    inline static bool isFaceRegular(const UTriKey & f) { return f[0] >= 0; }
    inline static bool isFaceRegular(const OTriKey & f) { return f[0] >= 0; }

    // get the indices forming the infinite ball border face triangle
    const int * getInfiniteBallTriangle() const { assert(!isRegular()); return v+1; }

    // if uface[i] == key, return i, otherwise return -1
    int getNeighborIndex(const UTriKey & key) const;
    // if oface[i] == key, return i, otherwise return -1
    int getNeighborIndex(const OTriKey & key) const;

    inline int getVtxOpposeFace(const OTriKey & key) const { return v[getNeighborIndex(key)]; }
    DelaunayBall * getNeighborByFace(const OTriKey & key) const { return nbr[getNeighborIndex(key)]; }
    // if uface[i] == key, set DelaunayBall::nbr[i] to be nbr
    void setNeighbor(const UTriKey & key, DelaunayBall * nbr);

    // get the Voronoi Edge connecting this Delaunay ball and one neighbor ball at nbr[nbrIndex]
    VoronoiEdge getVoronoiEdge(int nbrIndex) const;

    friend class DelaunayMesher;

    friend std::ostream & operator << (std::ostream & o, const DelaunayBall & ball);

  };

  // recover an edge by flipping, level means the maximal levels of recursion the recover process can have
  int segmentRecoveryUsingFlip(const OEdgeKey & edge, int level);
  // recover an edge by adding steiner points
  int segmentRecoveryUsingSteinerPoint(const OEdgeKey & edge);

  // simply add a ball for the delaunayMesher, we won't check whether it is still a delaunay mesh
  // v is an array of the four indices of the vertices in the delaunay mesh
  DelaunayMesher::DelaunayBall * addBall(const int * v);
  // simply remove a ball for the delaunayMesher, a hole may exist
  void removeBall(DelaunayBall * ball);

  /***************************************************************************
   *                          Debugging Functions                            *
   ***************************************************************************/

  // check whether each tet satisfyies the Delaunay criterion by looping over every tet-vtx pair
  // It's slow. For debugging purpose.
  bool checkDelaunay() const;

protected:
  // First, the apex of the tet, second, the shared face of the tet, third, the pointer to the tet
  typedef std::list<triple <int, OTriKey, DelaunayBall*> > TetAroundEdge;

  // Fliping a face, the face is shared by ball0 and ball1
  // ball0 and ball1 will be removed and three new balls will be added to the delaunay mesh
  // It can return one of the three added balls by setting requestNewBallIdx and newBallAroundEdge
  // By setting allowFlat, sometimes the three added balls may be flat and then removed by the next flip32.
  int flip23(const OTriKey & face, DelaunayBall * ball0, DelaunayBall * ball1, int requestNewBallIdx = -1, DelaunayBall ** newBallAroundEdge = NULL, int allowFlat = -1);
  // Fliping a edge, there must be 3 tets around the edge
  int flip32(const OEdgeKey & edge, const TetAroundEdge & tetsAroundEdge);

  // remove an edge by flipping, level means the maximal levels of recursion
  int segmentRemovalUsingFlip(const OEdgeKey & edge, int level = 1);


  // Find two delaunay balls that have the face
  int getTwoBallsByFace(const OTriKey & face, std::pair<DelaunayBall*, DelaunayBall *> & twoBalls);


  // Find one delaunay ball that has the face
  DelaunayBall * getOneBallByFace(const OTriKey & face);

  // Find tets that have the edge
  int getTetsAroundEdge(const OEdgeKey & edge, TetAroundEdge & tetsAroundEdge);

  // Clear the counter of some tets
  int clearCounter(const DelaunayMesher::TetAroundEdge & tetsAroundEdge);

  // The origin of the return ball should be start
  int getOneBallBySegment(const int start, const int end);

  //void debug() const;

//  double getCheckContainingTime() const { return checkContainingWatch.getElapsedTime(); }
//  double getUpdateTime() const { return updateWatch.getElapsedTime(); }

  DelaunayMesher::DelaunayBall * addBall(const int v0, const int v1, const int v2, const int v3);
  //build geometry query object
  void buildQuery();

  // compute circumcenter of a tet
  static Vec3d circumcenter(const Vec3d & a, const Vec3d & b, const Vec3d & c, const Vec3d & d);

  // get all the Delaunay balls containing the point getDelaunayVtx(i)
  void getBallsContainingPoint(int i, BallSet & balls);
  
  // used to construct neighboring information for new Delaunay balls
  // search face in neighboringStructure. If face is found, ball is neighbor to neighboringStructure[face], build related neighboring data
  int buildNeighbor(const UTriKey & face, DelaunayBall * ball, std::map<UTriKey, DelaunayBall *> & neighboringStructure);
  inline int buildNeighbor(int v0, int v1, int v2, DelaunayBall * ball, std::map<UTriKey, DelaunayBall *> & neighboringStructure)  {return buildNeighbor(UTriKey(v0, v1, v2), ball, neighboringStructure);}

  // get only one ball containing the point getDelaunayVtx(i)
  DelaunayBall * getOneBallContainingPoint(int i);

  DelaunayBall * createBall(int v0, int v1, int v2, int v3);

  //DelaunayMesher(const DelaunayMesher &);

  // initialize the first four vertices for Delaunay 
  // return false if failed 
  bool initialize(int a, int b, int c, int d);

  bool update(int i); // update Delaunay for the new point at index i

  Vec3d getFaceNormal(const OTriKey & face) const;

  static inline double det(const Vec3d & a, const Vec3d & b, const Vec3d & c) { return dot(a, cross(b, c)); }

  static bool isTetMeshFaceManifold(const TetMesh * tetMesh); // check whether any tet mesh face is at most shared by two tets

  double epsilon;
  Query::Type queryType;
  std::vector<Vec3d> inputVertices;
  std::set<Vec3d> verticesSet;

  BallSet balls;
  BallSet ballsToDelete;
  BallSet ballsAdded;

  VerticesQuery * query;


  std::map<UTriKey, DelaunayBall *> neighboringStructure; // Used for modifying balls

  // Look up by the index of the vertex, only return one of the balls that contains the vertex
  std::vector <DelaunayBall*> vertex2ball;

  std::set <UEdgeKey> recoveredEdge;

  // ============ DEBUG CODE ====================
//  typedef std::map<label_t, DelaunayBall *> BallMap;
//  typedef BallMap::iterator BallMapIter;
//  typedef BallMap::const_iterator BallMapCIter;
//  BallMap ballMap;
////  std::map<label_t, label_t> ballConnections;
//
//  struct Operation {
//    std::vector<label_t> deletedBalls;
//    std::vector<label_t> addedBalls;
//  };
//
//  std::vector<Operation> opStack;
//  TetMeshManifold tetManifold;
  // ============ END DEBUG CODE ==================

  bool computeVEdgeModification;
  VoronoiEdgeMap vEdgeDeleted;
  VoronoiEdgeMap vEdgeAdded;

  // data for CDT
  ObjMesh * boundaryMesh;
  //std::vector<UTriKey> boundaryTriangles;
  ObjMeshOctree<TriangleBasic> * boundaryOctree;

  label_t nextBallLabel;
};

#endif

