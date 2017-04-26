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


#ifndef _SIGNEDDISTANCEFIELDFROMPOLYGONSOUP_H_
#define _SIGNEDDISTANCEFIELDFROMPOLYGONSOUP_H_

#include <vector>
#include "distanceField.h"
#include "distanceFieldMT.h"
#include "distanceFieldNarrowBand.h"
#include "closestPointField.h"
#include "objMesh.h"

class SignedDistanceFieldFromPolygonSoup
{
public:
  // if useCubicBox=0, the bounding box will not be a cube, but the aspect ratios of the bounding box will be set so that voxels are cubes, by following the resolutionX, resolutionY, resolutionZ parameters in the Compute* routines below
  // if useCubicBox=1, the bounding box will be a cube, but the voxels will not necessarily be cubes
  SignedDistanceFieldFromPolygonSoup(ObjMesh * objMesh, double expansionRatio = 1.5, bool useCubicBox = 1,
      Vec3d * bbmin = NULL, Vec3d * bbmax = NULL);
  ~SignedDistanceFieldFromPolygonSoup() {}

  // Compute a signed distance field from polygon soup geometry, as described in:
  // Hongyi Xu, Jernej Barbic: 
  // Signed Distance Fields for Polygon Soup Meshes, Graphics Interface 2014, Montreal, Canada
  // 
  // An unsigned field will be created first (or loaded from precomputedUnsignedFieldFilename if not NULL). 
  // Then, a new mesh is created around the sigma isosurface. Next, a signed field is computed based on this new mesh. Finally, this signed field is offset by -sigma, to approximate the isosurface at the original mesh.
  // "sigma" is given in absolute units (not grid units)
  // subtractSigma: whether to subtract sigma from the computed signed distance field (to match the "zero" isosurface) 
  // computeVoronoiDiagram: whether to compute Voronoi diagram (stored in DistanceField)
  // closestPointFlag: whether to return a ClosestPointField or not (default: return DistanceField)
  DistanceField * ComputeDistanceField(int resolutionX, int resolutionY, int resolutionZ, double sigma, int subtractSigma = 1,
      int numThreads = 0, bool computeVoronoiDiagram = false, int maxTriCount = 15, int maxDepth = 10, int closestPointFlag = 0,
      const char * precomputedUnsignedFieldFilename = NULL);

  // Compute a distance field in a narrow band around the geometry
  // bandwidth: the width of the band (in either direction) around the geometry where the distance field is computed
  // "bandwidth" and "sigma" are given in absolute units (not grid units)
  DistanceFieldNarrowBand * ComputeDistanceFieldNarrowBand(int resolutionX, int resolutionY, int resolutionZ, double bandwidth,
      double sigma, int subtractSigma = 1, int maxTriCount = 15, int maxDepth = 10, const char * precomputedUnsignedFieldFilename = NULL);

protected:
  ObjMesh * objMesh;

  double expansionRatio;
  bool useCubicBox;
  Vec3d bbmin, bbmax;
  bool autoBoundingBox;

  //remove the interior components inside the isosurface 
  ObjMesh * RemoveInteriorComponents(ObjMesh * isoMesh);

  //construct the pseudo-normal for each component for pseudo-normal test
  bool ConstructPseudoNormalComponents(ObjMesh * isoMesh, std::vector<TriangleWithCollisionInfoAndPseudoNormals*>* triangleList);

  //pseudo-normal test to determine the relation between two components
  bool CheckInAndOutViaNormalTest(std::vector<TriangleWithCollisionInfoAndPseudoNormals*>* triangleList, int compIndex1, int compIndex2);

  //pre-removal via bounding box test. If a bounding box is completely inside another bounding box, the smaller one can be removed.
  bool CheckInAndOutViaBoundingBox(std::vector<Vec3d> & bmin, std::vector<Vec3d> & bmax, int compIndex1, int compIndex2);

  //extract isosurface using marching cubes from unsigned distance field. 
  ObjMesh * ComputeIsosurface(DistanceFieldBase * distanceField, double sigma);

  bool setBoundingBox(DistanceFieldBase* field, int resolutionX, int resolutionY, int resolutionZ);
};

#endif

