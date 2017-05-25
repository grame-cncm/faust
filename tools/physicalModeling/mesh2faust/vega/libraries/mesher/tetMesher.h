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
  Implements a constrained 3D Delaunay tet mesher with refinement,
  using the methods from:

  Hang Si. Adaptive tetrahedral mesh generation by constrained Delaunay refinement. 
  International Journal for Numerical Methods in Engineering, 75:856–880, 2008.

  Hang Si and Klaus Gartner. 3d boundary recovery by constrained delaunay tetrahedralization. 
  International Journal for Numerical Methods in Engineering, 85(11):1341–1364, 2011.

  The input is a manifold and self-intersection-free triangle mesh,
  and the output is a quality tet mesh of the volume enclosed by the input mesh
  that conforms to the input mesh.
  This mesh is generated using constrained Delaunay tetrahedralization,
  and by inserting new vertices (``Steiner vertices'') into the mesh as needed
  to satisy the quality conditions.

  Note: The tet mesher is experimental. It may generate sliver tets with some inputs.
*/

#ifndef _TETMESHER_H_
#define _TETMESHER_H_

#include <vector>
#include <set>
#include <queue>

#include "vec3d.h"
#include "objMesh.h"
#include "tetMesh.h"
#include "delaunayMesher.h"

class TetMesher
{
public:

  TetMesher();
  virtual ~TetMesher();

  // compute the tet mesh, using constrained 3D Delaunay tetrahedralization, with refinement
  // refinementQuality is a scalar; one must use refinementQuality >= 1
  // the smaller the value, the more the mesh will be refined
  // minDihedralAngle: the minimal dihedral angle in a tet on the result tet mesh should not be larger than "minDihedralAngle"
  // maxSteinerVertices controls how many vertices are added in the refinement process. < 0 means no limitation.
  // alpha: the smallest distance between a new Steiner vertex and the existing vertices should be larger than alpha times 
  // the average edge length of the input mesh
  // maxTimeSeconds: the routine will terminate if this computation time (in seconds) is exceeded. < 0 means no limitation.
  TetMesh * compute(ObjMesh * surfaceMesh, double refinementQuality = 1.1, double alpha = 2.0, double minDihedralAngle = 0.0, 
      int maxSteinerVertices = -1, double maxTimeSeconds = -1.0);

  inline int getNumAddedSteinerVertices() const { return numSteinerVertices; }

protected:

  typedef DelaunayMesher::DelaunayBall DelaunayBall;
  typedef DelaunayMesher::BallCIter BallCIter;


  // Delaunay ball with information of radius/minEdge and minimal dihedral angle
  struct DelaunayBallWithRefineInfo : public DelaunayBall
  {
    double minDihedral;       // Not valid for infinite ball. The minimal dihedral angel of the tetrahedral. Lazy compute
    double edgeQuality;       // Not valid for infinite ball. Square of the minimal edge of the tetrahedral. Lazy compute
    DelaunayBallWithRefineInfo(const DelaunayBall & parent);
  protected:
    DelaunayBallWithRefineInfo(const DelaunayBallWithRefineInfo &);
  };

  // A set of delaunay balls with information of radius/minEdge and minimal dihedral angle
  struct TetMeshWithRefineInfo
  {
    static DelaunayMesher::DelaunayBallCompare defaultComparor;
    TetMeshWithRefineInfo(const DelaunayMesher & delaunayMesher);
    ~TetMeshWithRefineInfo();

    struct DelaunayBallEdgeRefineCMP           // sort radius/minEdge descend
    {
      bool operator () (const DelaunayBallWithRefineInfo * const & p1, const DelaunayBallWithRefineInfo * const & p2);
    };


    struct DelaunayBallAngleRefineCMP         // sort dihedral angel ascend
    {
      bool operator () (const DelaunayBallWithRefineInfo * const & p1, const DelaunayBallWithRefineInfo * const & p2);
    };

    typedef std::set<const DelaunayBallWithRefineInfo *, DelaunayBallEdgeRefineCMP>::const_iterator EdgeRefineIterator;
    typedef std::set<const DelaunayBallWithRefineInfo *, DelaunayBallAngleRefineCMP>::const_iterator AngleRefineIterator;
    inline EdgeRefineIterator getEdgeRefineBegin() { return edgeRefineBalls.begin(); }
    inline EdgeRefineIterator getEdgeRefineEnd() { return edgeRefineBalls.end(); }
    inline EdgeRefineIterator getAngleRefineBegin() { return angleRefineBalls.begin(); }
    inline EdgeRefineIterator getAngleRefineEnd() { return angleRefineBalls.end(); }

    // Get Tetmesh from the set of delaunayBall.
    // Callee will alloc the memory and caller is responsible to free the memory
    TetMesh * getTetMesh();

    // Compute the refine information such as edge quality and dihedral angle
    // Alloc memory and deep copy inside, free memory in deconstruc function and remove function
    void insert(const DelaunayMesher::DelaunayBall * delaunayBall);

    // Remove the delaunay ball that is removed in the last refinement. Free memory inside
    void remove(const DelaunayMesher::DelaunayBall * delaunayBall);

    // Enable the minimal dihedral angle refinement
    inline void enableAngleRefine() { enabledAngleRefine = true; }
    //friend class TetMesher;
  protected:

    bool enabledAngleRefine; // Whether the angle refinement is enabled
    const DelaunayMesher & delaunayMesher; // Reference to the delaunayMesher, used to get the positions of vertices
    std::set<const DelaunayBallWithRefineInfo *, DelaunayBallEdgeRefineCMP> edgeRefineBalls; // Sort the current delaunay ball by radius/minEdge descendingly
    std::set<const DelaunayBallWithRefineInfo *, DelaunayBallAngleRefineCMP> angleRefineBalls; // Sort the current delaunay ball by diheral angle  aescendingly
    std::map<const DelaunayMesher::DelaunayBall *, EdgeRefineIterator, DelaunayMesher::DelaunayBallCompare> edgeRefineMap; // Look up the iterator in edgeRefineSet by pointer
    std::map<const DelaunayMesher::DelaunayBall *, AngleRefineIterator, DelaunayMesher::DelaunayBallCompare> angleRefineMap;     // Look up the iterator in angleRefineSet by pointer
  } resultTetMesh;

  // construct a constrained delaunay mesh, if recovery is true, the face recovery process will be done
  int initializeCDT(bool recovery = true);
  // refine a constrained delaunay mesh

  /*
    Refine one tet with bad edge quality, radius/minEdge
    Ret value
    0: refined
    1: No tet to refine due to enough steiner points
    2: No bad tet to refine
  */
  int refineEdge(double refinementQuality, const double minmimalDist);

  /*
    Refine one tet with bad dihedral angle, too small dihedral angle
    Ret value
    0: refined
    1: No tet to refine due to enough steiner points
    2: No bad tet to refine
  */
  int refineAngle(const double angleBound, const double minmimalDist);

  // Make sure the first four vertices of the triangle mesh are not on the same plane
  static bool renumberInitialVertices(ObjMesh * surfaceMesh);

  //remove all tetrahedrons that are outside the constrained delaunay mesh
  int removeOutside();

  // insert a tet into the tetmesh
  void insertTet(const int * v);
  // remove a tet from the tetmesh
  void removeTet(const int * v);

  // insert a face into the tetmesh
  void insertFace(int f1, int f2, int f3);
  // remove a face from the tetmesh
  void removeFace(int f1, int f2, int f3);
  // insert an edge into the tetmesh
  void insertEdge(int e1, int e2);
  // remove an edge from the tetmesh
  void removeEdge(int e1, int e2);

  // get a face from the input triangular mesh
  UTriKey getFace(int index);

  // Do face recovery process
  void faceRecovery();

  // form a missing region by one face, the boundary of the missing face is on the current tet, the triangles in the region are all missing
  void formRegion(int face, std::set<int> &region);
  // calculate the boundary of a tet mesh, triangles that has only one neighbor tetrahedron
  void calculateTetBoundary(std::vector<DelaunayMesher::DelaunayBall*> &tet, std::vector<UTriKey> &boundary);
  // calculate the boundary of a missing region, the region consists of connected triangles, boundary is a set of edges that have only one neighbor triangle
  void calculateTriangleBoundary(std::set<int> &missingRegion, std::set<std::pair<int, int> > &boundary);
  // build a map for triangular mesh, which two triangles are the neigbhor of an edge
  void buildTriangleNeighbor(std::vector<UTriKey> &mesh, std::map<std::pair<int, int>, std::pair<int, int> > &neighbor);
  // insert the missing region into the cavity formed by removing all tetrahedrons that intersect the missing region, and then form two cavities
  bool formTwoCavities(std::vector<UTriKey> &missingRegion, std::set<std::pair<int, int> >& boundary, std::map<std::pair<int, int>, std::pair<int, int> > &neighbor);
  // fill a hole defined by a set of boundary triangles, compute what tetrahedrons need adding
  bool fillHole(std::vector<UTriKey> &holeBoundary);

  // determine whether the point is too close to any existent vertices in the current mesh
  bool isTooCloseToOtherVertices(const Vec3d & r, const double minimalDist) const;

  // Get the steiner point in segement recovery.
  Vec3d getSteinerPoint(const UEdgeKey & edge, const bool isAcute1, const bool isAcute2, const double lfs1, const double lfs2, const double c = 2) const;

  // segment recovery
  int segmentRecovery();

  // Used to compute delaunay mesh
  DelaunayMesher delaunay;
  // the input triangular mesh
  ObjMesh * objMesh;

  // the set of triangles that are in the input triangular mesh but not in the volumetric mesh
  std::vector<UTriKey> lost;
  // the indices of triangles that are in a missing region
  std::set<int> region;

  // for the input triangular mesh, which three triangles are the neigbhors of a triangle. All triangles are described by their indices
  std::vector<std::vector<int> > neighborSurface;

  // Tetradedrons added into the tet mesh to fill a hole
  std::vector <std::vector<int> > toAdd;

  // Triangles in the volumetric mesh, key is the triangle and value is how many tets are associated with the triangle
  std::map<UTriKey, unsigned> trianglesInTet;

  // flip the input objmesh to fit the delaunay mesh in case failure in the segment recovery
  int flipSurface();

  // edges in the volumetric mesh, key is the edge and value is how many tets are associated with the edge
  std::map<UEdgeKey, unsigned> edgesInTet;

  // the number of steiner points inserted (refinement)
  int numSteinerVertices;

  // recursion depth for face recovery;
  int faceRecoveryDepth;
};

#endif /* TETMESHER_H_ */

