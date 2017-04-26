/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "distance field" library , Copyright (C) 2007 CMU, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Yijing Li, Hongyi Xu, Jernej Barbic                     *
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
  This is a "master" class to compute unsigned or signed distance fields.
  The specific algorithm is controlled using "SignedFieldCreationMode" (below).
*/

#ifndef _DISTANCEFIELD_CREATOR_H_
#define _DISTANCEFIELD_CREATOR_H_

#include <vector>
#include "distanceField.h"
#include "distanceFieldMT.h"
#include "distanceFieldNarrowBand.h"
#include "closestPointField.h"
#include "objMesh.h"

class DistanceFieldCreator
{
public:
  // if useCubicBox=0, the bounding box will not be a cube, but the aspect ratios of the bounding box will be set so that voxels are cubes, by following the resolutionX, resolutionY, resolutionZ parameters in the Compute* routines below
  // if useCubicBox=1, the bounding box will be a cube, but the voxels will not necessarily be cubes
  DistanceFieldCreator(ObjMesh * objMesh, double expansionRatio = 1.5, bool useCubicBox = true, const Vec3d * bbmin = NULL, const Vec3d * bbmax = NULL);
  virtual ~DistanceFieldCreator() {}

  enum SignedFieldCreationMode
  {
    BASIC,       // assumes the input obj mesh is manifold and self-intersection-free
    POLYGONSOUP, // handles non-manifold and/or self-intersecting meshes, using the SignedDistanceFieldFromPolygonSoup pipeline,
                 // as published in:
                 // Hongyi Xu, Jernej Barbic: 
                 // Signed Distance Fields for Polygon Soup Meshes, Graphics Interface 2014, Montreal, Canada
    AUTO         // uses BASIC if mesh is manifold, otherwise POLYGONSOUP
  };

  // Compute a distance field from objmesh
  // If calculateSignedField=0, an unsigned field will be computed.
  // If calculateSignedField=1, a signed field will be computed.
  // computeVoronoiDiagram: whether to compute a Voronoi diagram (stored in DistanceField)
  // closestPointFlag: whether to return a ClosestPointField or not
  DistanceField * ComputeDistanceField(int resolutionX, int resolutionY, int resolutionZ, int calculateSignedField, SignedFieldCreationMode mode,
    double sigma, int subtractSigma = 1, int numThreads = 0, bool computeVoronoiDiagram = false, int maxTriCount = 15, int maxDepth = 10, int closestPointFlag = 0,
    const char * precomputedUnsignedFieldFilename = NULL);

  // Compute a distance field in a narrow band
  DistanceFieldNarrowBand * ComputeDistanceFieldNarrowBand(int resolutionX, int resolutionY, int resolutionZ, double bandWidth, int calculateSignedField,
    SignedFieldCreationMode mode, double sigma, int subtractSigma = 1, int maxTriCount = 15, int maxDepth = 10,
    const char * precomputedUnsignedFieldFilename = NULL);

protected:

  ObjMesh * objMesh;

  double expansionRatio;
  bool useCubicBox;
  bool autoBoundingBox;
  Vec3d bbmin, bbmax;

  void setBoundingBox(DistanceFieldBase* field, int resolutionX, int resolutionY, int resolutionZ);
};

#endif

