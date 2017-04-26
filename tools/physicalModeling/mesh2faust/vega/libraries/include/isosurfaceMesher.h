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
  Compute a quality triangular mesh of a distance field isosurface (level set),
  using the following paper:

  Steve Oudot, Laurent Rineau, Mariette Yvinec:
  Meshing Volumes Bounded by Smooth Surfaces
  Proceedings of the 14th International Meshing Roundtable 2005, pp 203-219
*/

#ifndef _ISOSURFACEMESHER_H_
#define _ISOSURFACEMESHER_H_

#include <time.h>
#include <vector>
#include <map>
#include <set>

#include "distanceFieldBase.h"
#include "objMesh.h"
#include "tetMesh.h"
#include "triple.h"
#include "triangle.h"
#include "delaunayMesher.h"

class IsosurfaceMesher
{
public:

  // initialize the mesher
  // the mesher will mesh an isosurface of the distance field "field"
  IsosurfaceMesher(DistanceFieldBase * distanceField);
  virtual ~IsosurfaceMesher();

  // calculate the isosurface
  // isovalue: the isovalue of the distance field to be meshed
  // angularBound: the angles of the triangle on the isosurface mesh should not be larger than angularBound
  //               the angular bound is passed in radians
  // radialBound: the largest circumcircle of the triangle on the isosurface mesh should not be larger than "radialBound"
  // numInitialSamples: number of points generated in the first step of the algorithm (internal initial mesh)
  // Query::Type: choice of precision used in the Delaunay mesher
  //              DOUBLE: double precision  
  //              RATIONAL: high-precision arithmetics  
  //              FILTERED: trade-off between DOUBLE and RATIONAL
  // epsilon: internal accuracy parameter for queryType=FILTERED, on [0,1]
  //          the larger the value, the more computation will be done in high-precision arithmetics
  //          epsilon == 0: all computation in double precision
  //          epsilon == 1: all computation in high-precision
  // maxNumberOfIterations: the routine will terminate if this number of iterations is exceeded. < 0 means no limitation
  // maxTimeSeconds: the routine will terminate if this computation time (in seconds) is exceeded. < 0 means no limitation
  // return value: true if timeout occurred, false otherwise
  bool compute(double isovalue, double angularBound, double radialBound,
               int numInitialSamples = 20, double epsilon = 1e-6,
               Query::Type queryType = Query::FILTERED,
               int maxNumberOfIterations = -1, double maxTimeSeconds = -1.0);

  // get the result of compute()
  ObjMesh * getMesh(bool enforceManifold = true);

  // =========== advanced routines ===================

  // pass a mesh representing the zero isosurface, to be remeshed via compute()
  // only isovalue=0 is supported in this mode
  IsosurfaceMesher(ObjMesh * detailedSurfaceMesh);

  // =========== debugging =================

  void saveMarchingCubesMesh(bool save = true) { saveMarchingCubesObj = save; }
  void checkDelaunayAfterComputation(bool check = true) { checkDelaunay = check; }
  const ObjMesh * getMarchingCubesMesh() const { return marchingCubesMesh; }

  // stepping functions
  void setStepping(double isovalue, double angularBound, double radialBound, size_t numInitialSamples = 20, double epsilon = 1e-6, Query::Type queryType = Query::FILTERED);
  void doOneStep();
  bool endStepping() const;

  const DelaunayMesher & getCurrentDelaunay() const { return delaunay; }

  // if keepAllDelaunayVtx is false, only vertices that belong to at least one triangle are kept
  // otherwise, all vertices in the Delaunay mesh are added to the resulting obj mesh
  ObjMesh * buildCurrentSurfaceMesh(bool keepAllDelaunayVtx = false) const;

  // remove non-manifold faces and edges, orient faces
  static bool enforceManifoldnessAndOrientNormals(ObjMesh * &objMesh);
protected:
  IsosurfaceMesher(const IsosurfaceMesher &);

  // represent a face on the isosurface mesh
  struct IsoFace
  {
    Vec3d isopoint;   // a point on the isosurface near this face. This point is also the center of a circumsphere of the triangle face
    double radius;   // radius of the circumsphere centered at isopoint
    double maxCosAngle; // max cosine of the angles of this triangle
    UTriKey tri;     // the triangle vtx index of this face
    IsoFace() {}
    IsoFace(const UTriKey & tri, const Vec3d & v0, const Vec3d & v1, const Vec3d & v2, const Vec3d & isopoint);
  };
  // compare the radius of two IsoFace, used in a set to find the face with largest circumcircle radius
  struct IsoFaceRadiusCompare
  {
    bool operator() (const IsoFace & a, const IsoFace & b) const;
  };
  // compare the radius of two IsoFace, used in a set to find the face with largest maxCosAngle
  struct IsoFaceAngleCompare
  {
    bool operator() (const IsoFace & a, const IsoFace & b) const;
  };

  // the set that compares IsoFace circumcircle radius, used to find the face with largest circumcircle radius
  typedef std::set<IsoFace, IsoFaceRadiusCompare> IsoFaceRadiusSet;
  // the set that compares IsoFace maxCosAngle, used to find the face with largest maxCosAngle
  typedef std::set<IsoFace, IsoFaceAngleCompare> IsoFaceAngleSet;

  typedef IsoFaceRadiusSet::iterator RadiusIter;
  typedef IsoFaceAngleSet::iterator AngleIter;
  typedef std::pair<RadiusIter, AngleIter> IterPair;
  typedef std::map<UTriKey, IterPair> IterPairMap;

  // DelaunayMesher related typedefs for easy interaction with DelaunayMesher
  typedef DelaunayMesher::VoronoiEdge VoronoiEdge;
  typedef DelaunayMesher::VoronoiEdgeMap VoronoiEdgeMap;
  typedef DelaunayMesher::VEdgeIter VEdgeIter;
  typedef DelaunayMesher::VEdgeCIter VEdgeCIter;

  // void intersection(const std::vector<TriangleBasic*> & triangles, const Vec3d & v, const Vec3d & direction, bool isRay, std::vector<double> & t);

  bool intersectionUsingOctree(const Vec3d & v, const Vec3d & direction, bool isRay, Vec3d & intersectionPoint);

  static void generateInitialPointSetByDiscrepancy(const ObjMesh * objMesh, std::vector<Vec3d> & point, const unsigned int numInitialSamples);

  ObjMesh * computeOneMesh(ObjMesh * objMesh, int & maxNumberOfIterations, double & maxTimeSeconds, bool & timeout);
  bool initializeOneMesh(ObjMesh * objMesh);
  bool addOneTriangle(double * targetRadius = NULL); // return true if it won't stop

  DistanceFieldBase * field;
  ObjMesh * detailedSurfaceMesh;
  double isovalue;
  double angularBound, cosAngularBound, radialBound;
  size_t numInitialSamples;
  DelaunayMesher delaunay;
  Query::Type queryType;
  double epsilon;

  ObjMesh * splitIsosurfaceMesh;
  std::vector<ObjMesh *> splitComponent;
  double fieldDiagonal;
  ObjMeshOctree<TriangleBasic> * objMeshOctree;

  // index for stepping
  size_t splitComponentIndex;
  int oneMeshLoopIndex;

  IsoFaceRadiusSet radiusSet;  // a set stores the faces for the isosurface to be generated and order according to its circumcircle radius
  IsoFaceAngleSet angleSet;    // a set stores the faces and order according to its max cosine angle
  IterPairMap faceIters;       // map of UTriKey -> two iterators pointing to the face locations in radiusSet and angleSet

  ObjMesh * isoMesh;

  // StopWatch delaunayUpdateCounter;
  // StopWatch octreeCounter;
  // StopWatch intersectionCounter;
  bool checkDelaunay;
  bool saveMarchingCubesObj;

  ObjMesh * marchingCubesMesh;

  double ignoredSplitComponentVtxRatio;

  int globalLoopIndex;
};

#endif

