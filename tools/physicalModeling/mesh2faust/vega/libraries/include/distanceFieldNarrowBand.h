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
  Narrowband distance field computation.
*/

#ifndef _DISTANCEFIELDNARROWBAND_H_
#define _DISTANCEFIELDNARROWBAND_H_

#include "objMesh.h"
#include "triple.h"
#include "distanceFieldBase.h"
#include "vegalong.h"
#include <map>
#include <float.h>

class DistanceFieldNarrowBand : public DistanceFieldBase
{
public:

  DistanceFieldNarrowBand();
  virtual ~DistanceFieldNarrowBand();

  // computes unsigned distance field in a narrow band
  // filename is the obj filename
  // bandWidth is given in absolute units
  virtual int computeUnsignedField(ObjMesh * objMesh, int resolutionX, int resolutionY, int resolutionZ, double bandWidth, int maxTriCount=15, int maxDepth=10);

  // computes signed distance field in a narrow band
  // filename is the obj filename
  // offset is given in absolute units
  virtual int computeSignedField(ObjMesh * objMesh, int resolutionX, int resolutionY, int resolutionZ, double bandWidth, int maxTriCount=15, int maxDepth=10);

  virtual void offsetDistanceField(double sigma); // add sigma to all the distance field values
  // computes the signed distance field, in the interior region (bounded by the zero isosurface), in a narrow band
  // must call computeUnsignedField using the same objMesh and same resolution first
  // also, you should first offset the unsigned distance field by a proper 'sigma' (typically, by passing -sigma, where sigma > 0)
  virtual int computeInteriorSignedField(ObjMesh * objMesh, int resolutionX, int resolutionY, int resolutionZ, double bandWidth, int maxTriCount=15, int maxDepth=10);

  // loads a previously computed distance field from a disk file
  virtual int load(const std::string& filename); // returns 0 on success

  // saves the current distance field to a disk file (e.g. after computing it once, for later fast reloading) 
  virtual int save(const std::string& filename, bool doublePrecision); // saves in a compressed format (saves the computed grid points only)
  virtual int saveToText(const std::string& filename);
  int saveToDistanceField(const std::string& filename, bool doublePrecision); // saves in full format (FLT_MAX or -FLT_MAX are stored for uncomputed grid points)

  // return distance field value at grid vertex (i,j,k)
  // each of i,j,k must be an integer from {0, ..., resolution{X,Y,Z}}
  virtual inline float distance(int i, int j, int k);
  // computes distance and gradient at arbitrary position
  virtual float distance(Vec3d pos, int constrainToBox=0);
  // alters the distance at a particular grid vertex (i,j,k)
  virtual inline void setDistance(int i, int j, int k, float value);

  virtual Vec3d gradient(const Vec3d & pos);

  virtual bool sanityCheck(); // checks if distance for any two adjacent voxels is less than voxel grid spacing apart (which it must be by triangle inequality, for both signed and unsigned fields)

  virtual float maxValue();
  virtual float minValue();
  virtual void  maxMinValue(float* maxValue, float* minValue);

  virtual float maxAbsValue();
  virtual float maxAbsValue(float threshold); // only abs values up to threshold
  virtual float maxNonInftyAbsValue();

  virtual int breadthFirstTraversalSigned(void * objMeshOctree, float offset, int zLo, int zHi, int asterisk=0);
  virtual int breadthFirstTraversalUnsigned(void * objMeshOctree, float offset, int zLo, int zHi, int asterisk=0);
  virtual int breadthFirstTraversalInteriorSigned(void * objMeshOctree, float offset, int zLo, int zHi, int asterisk=0);

  void freeMemory();
  
  void findSurfaceGridPoints(ObjMesh* objMeshIn);

  typedef triple<int,int,int> gridPoint;
  std::map<gridPoint, float> * getDistanceData() {return &distanceData;};
  
protected:
  int maxTriCount;
  int maxDepth;

  void finalizeGridPointStatus();
  enum { COMPUTED, EXTERIOR_UNCOMPUTED, INTERIOR_UNCOMPUTED };
  char * gridPointStatus; // needed for the sign on uncomputed grid points; unsigned field only has two values: COMPUTED, EXTERIOR_UNCOMPUTED

  int signFieldFlooded;
  //float * fieldData;
  std::map<gridPoint, float> distanceData;

  vegalong GetFilesize(const char *filename);
  
  std::vector<vegalong> surfaceGridPoints;
};

inline float DistanceFieldNarrowBand::distance(int i, int j, int k)
{
  vegalong index = (k * (resolutionY+1) + j) * (resolutionX + 1) + i;

  std::map<gridPoint, float>::iterator it = distanceData.find(gridPoint(i,j,k));

  if (it == distanceData.end())
  {
    if (gridPointStatus[index] == DistanceFieldNarrowBand::INTERIOR_UNCOMPUTED)
      return -FLT_MAX;
    else 
      return FLT_MAX;
  }
  else
    return it->second;
}

inline void DistanceFieldNarrowBand::setDistance(int i, int j, int k, float value)
{
  std::map<gridPoint, float>::iterator it = distanceData.find(gridPoint(i,j,k));
  
  if (it == distanceData.end())
    distanceData.insert(std::pair<gridPoint, float>(gridPoint(i,j,k), value));
  else
    it->second = value;
}

#endif

