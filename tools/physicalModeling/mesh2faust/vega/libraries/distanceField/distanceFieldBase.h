/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "distance field" library , Copyright (C) 2007 CMU, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Hongyi Xu, Yijing Li                     *
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
  This code generates a distance filed, either signed or unsigned, 
  to the given triangle mesh.

  The distance field can be loaded/saved to a file.
  You can also lookup the field (once computed or loaded) at arbitrary 
  locations inside the field, using trilinear interpolation.

  Input mesh need not have triangle faces (e.g., can have quads; 
  they will be triangulated).

  For signed field generation, the input mesh must be a closed manifold mesh.

  Input mesh must be given in the .obj format:
  http://www.royriggs.com/obj.html

  By default, the bounding box will be a cube, obtained by fitting the  
  smallest cube to the geometry, and then expanded (scaled) from its 
  center by a factor of 1.5. You can provide your own bounding boxes. 
  However, note: (1) the provided bounding box must cover all the geometry, 
  and (2) bounding boxes that are not cubes were not (yet) tested.

  The bounding box will be divided into a "resolution" number of 
  cubes ("voxels") along each axis. The distance field will be computed at the 
  vertices of these voxels. So, if resolution is 256, the bounding box 
  will get divided into 256 x 256 x 256 voxels, and the distance field 
  will be computed on the resulting 257 x 257 x 257 grid of voxel vertices. 
  Note that when indexing voxels, the indices (i,j,k) will run from 0 to 255 
  inclusive, whereas when indexing voxel vertices (also called "grid vertices"), 
  they will run from 0 to 256 inclusive.

  Distance field data is stored at voxel vertices. 
  In memory, distance field value at voxel vertex (i,j,k) is stored 
  at location k * (resolutionX+1)*(resolutionY+1) + j * (resolutionX+1) + i .

  Internally, the code builds an octree on top of the triangle mesh. 
  There are two parameters that control this process (you can keep them 
  at default values, which worked well in practice for us) :
  the max depth of the octree is "maxDepth", and
  the max number of triangles intersecting an octree cell is "maxTriCount".
  Note: once max depth level is reached, the maxTriCount bound is not imposed any more.
*/

#ifndef _DISTANCEFIELDBASE_H_
#define _DISTANCEFIELDBASE_H_

#include "objMesh.h"

class DistanceFieldBase
{
public:

  DistanceFieldBase();
  virtual ~DistanceFieldBase() {};

  DistanceFieldBase(int resolutionX, int resolutionY, int resolutionZ);

  // sets the bounding box within which the distance field will be computed
  // set it before calling computeSigned/UnsignedField
  void setBoundingBox(const Vec3d & bmin, const Vec3d & bmax);
  void getBoundingBox(Vec3d & bmin, Vec3d & bmax);
  // set a tight-fitting bounding box around the model, and expand it by the expansion ratio given
  // note: if you don't set any bounding boxes, you get an automaticBoundingBox with 1.5 expansion ratio by default
  void setAutomaticBoundingBox(bool allBoxSidesEqual=true, double expansionRatio=1.5);
  
  // compute bounding box with uniform cube voxels, of the specified resolution
  // this routine uses the parameters set by the "setAutomaticBoundingBox" 
  // if allBoxSidesEqual=true, the voxels will not necessarily be cubes
  void computeBoundingBox(ObjMesh * objMesh, int resolutionX, int resolutionY, int resolutionZ);

  // loads a previously computed distance field from a disk file
  virtual int load(const std::string& filename) = 0; // returns 0 on success

  // saves the current distance field to a disk file (e.g. after computing it once, for later fast reloading) 
  virtual int save(const std::string& filename, bool doublePrecision) = 0;

  // exports the distance field to a file, in text format
  virtual int saveToText(const std::string& filename) = 0;

  // return distance field value at grid vertex (i,j,k)
  // each of i,j,k must be an integer from {0, ..., resolution{X,Y,Z}}
  virtual float distance(int i, int j, int k) = 0;
  // computes distance and gradient at arbitrary position
  virtual float distance(Vec3d pos, int constrainToBox=0) = 0;
  // alters the distance at a particular grid vertex (i,j,k)
  virtual void setDistance(int i, int j, int k, float value) = 0;
  
  // gradient is computed with respect to trilinear interpolation
  // note: gradient is discontinuous at the cell boundaries
  virtual Vec3d gradient(const Vec3d& pos) = 0;

  // pack/unpack index
  inline int packedVoxelIndex(int i, int j, int k); // returns a 32-bit unique voxel index
  inline int packedVoxelIndex(const Vec3d & pos); // returns a 32-bit unique voxel index, for voxel constaining pos
  inline void unpackVoxelIndex(int packedIndex, int & i, int & j, int & k);
  
  inline void voxelIndices(const Vec3d & pos, int * i, int * j, int * k); // returns indices of voxel containing pos

  inline bool validGridIndex(int i, int j, int k); // tells whether the grid index is valid: 0<=i<=resolutionX, 0<=j<=resolutionY, 0<=z<=resolutionZ
  inline bool validVoxelIndex(int i, int j, int k);// tells whether the voxel index is valid: 0<=i<resolutionX, 0<=j<resolutionY, 0<=z<resolutionZ

  inline bool insideBox(const Vec3d & pos); // tells whether the pos is inside box or not

  // returns the world-coordinate position of the grid vertex with indices (i,j,k)
  // must have: 0 <= i,j,k <= resolution{X,Y,Z}   (i,j,k of course not necessarily sorted)
  inline Vec3d getGridPosition(int i, int j, int k);

  // /set/get distance field resolution
  inline void setResolution(int resolutionX, int resolutionY, int resolutionZ) { this->resolutionX = resolutionX; this->resolutionY = resolutionY; this->resolutionZ = resolutionZ; setGridParameters(); }
  inline int getResolutionX() const { return resolutionX; }
  inline int getResolutionY() const { return resolutionY; }
  inline int getResolutionZ() const { return resolutionZ; }

  // get the diagonal of the bounding box
  inline double diagonal() const { return len(bmax_-bmin_);}

  // get the lower-left-front corner of bounding box
  inline const Vec3d & bmin() const { return bmin_; }
  // get the upper-right-back corner of bounding box
  inline const Vec3d & bmax() const { return bmax_; }
  // alternative interface to bmin, bmax functions above
  inline void bmin(float * bmin) const { bmin[0] = (float) bmin_[0]; bmin[1] = (float) bmin_[1]; bmin[2] = (float) bmin_[2]; }
  inline void bmax(float * bmax) const { bmax[0] = (float) bmax_[0]; bmax[1] = (float) bmax_[1]; bmax[2] = (float) bmax_[2]; }
  inline void bmin(double * bmin) const { bmin[0] = bmin_[0]; bmin[1] = bmin_[1]; bmin[2] = bmin_[2]; }
  inline void bmax(double * bmax) const { bmax[0] = bmax_[0]; bmax[1] = bmax_[1]; bmax[2] = bmax_[2]; }

  // returns the spatial dimensions of the voxels
  // i.e., this is the spatial distance between consecutive grid vertices along the three dimensions
  void getGridSpacing(double * gridX, double * gridY, double * gridZ);
  void getInvGridSpacing(double * invGridX, double * invGridY, double * invGridZ);

  // conversion between absolute units to grid units
  double absoluteUnitsToGridUnits(double absoluteUnits) const;
  double gridUnitsToAbsoluteUnits(double gridUnits) const;

  virtual bool sanityCheck() = 0; // checks if distance for any two adjacent voxels is less than voxel grid spacing apart (which it must be by triangle inequality, for both signed and unsigned fields)

  virtual float maxValue() = 0;
  virtual float minValue() = 0;

  virtual float maxAbsValue() = 0;
  virtual float maxAbsValue(float threshold) = 0; // only abs values up to threshold
  virtual float maxNonInftyAbsValue() = 0;

  //virtual void print() = 0;

  virtual void offsetDistanceField(double offset) = 0;

protected:
  // set side, gridX, girdY, gridZ, invGridX, invGridY, invGridZ
  void setGridParameters();

  int resolutionX, resolutionY, resolutionZ;
  Vec3d bmin_, bmax_;
  Vec3d side;
  double gridX, gridY, gridZ;           // spatial distance between consecutive grid vertices along the three dimensions
  double invGridX, invGridY, invGridZ;  // inverse of gridX/Y/Z

  bool useAutomaticBox;
  double expansionRatio;
  bool allBoxSidesEqual;

  bool bboxComputed;
  //float minBoundaryDistance;
};


inline void DistanceFieldBase::getBoundingBox(Vec3d & bmin, Vec3d & bmax)
{
  bmin = bmin_;
  bmax = bmax_;
}

inline void DistanceFieldBase::setBoundingBox(const Vec3d& bmin, const Vec3d& bmax)
{
  useAutomaticBox = false;
  bmin_ = bmin;
  bmax_ = bmax;
  setGridParameters();
}

inline void DistanceFieldBase::setGridParameters() 
{
  side = bmax_ - bmin_;
  gridX = side[0] / resolutionX;
  gridY = side[1] / resolutionY;
  gridZ = side[2] / resolutionZ;
  invGridX = 1.0 / gridX;
  invGridY = 1.0 / gridY;
  invGridZ = 1.0 / gridZ;
}

inline void DistanceFieldBase::setAutomaticBoundingBox(bool allBoxSidesEqual, double expansionRatio)
{
  useAutomaticBox = true;
  this->expansionRatio = expansionRatio;
  this->allBoxSidesEqual = allBoxSidesEqual;
}

inline void DistanceFieldBase::getGridSpacing(double * gridX, double * gridY, double * gridZ)
{
  *gridX = this->gridX;
  *gridY = this->gridY;
  *gridZ = this->gridZ;
}

inline void DistanceFieldBase::getInvGridSpacing(double * invGridX, double * invGridY, double * invGridZ)
{
  *invGridX = this->invGridX;
  *invGridY = this->invGridY;
  *invGridZ = this->invGridZ;
}

inline Vec3d DistanceFieldBase::getGridPosition(int i, int j, int k)
{
 return Vec3d (bmin_[0] + i * gridX, bmin_[1] + j * gridY, bmin_[2] + k * gridZ);
}


inline void DistanceFieldBase::voxelIndices(const Vec3d& pos, int * i, int * j, int * k) // returns indices of voxel containing pos
{
  *i = (int)((pos[0] - bmin_[0]) * invGridX);
  *j = (int)((pos[1] - bmin_[1]) * invGridY);
  *k = (int)((pos[2] - bmin_[2]) * invGridZ);
}


inline bool DistanceFieldBase::insideBox(const Vec3d& pos)
{
  int i = (int)((pos[0] - bmin_[0]) * invGridX);
  int j = (int)((pos[1] - bmin_[1]) * invGridY);
  int k = (int)((pos[2] - bmin_[2]) * invGridZ);

  return ((i >= 0) && (i < resolutionX) && (j >= 0) && (j < resolutionY) && (k >= 0) && (k < resolutionZ));
}

inline bool DistanceFieldBase::validGridIndex(int i, int j, int k)
{
  return ((i >= 0) && (i <= resolutionX) && (j >= 0) && (j <= resolutionY) && (k >= 0) && (k <= resolutionZ));
}

inline bool DistanceFieldBase::validVoxelIndex(int i, int j, int k)
{
  return ((i >= 0) && (i < resolutionX) && (j >= 0) && (j < resolutionY) && (k >= 0) && (k < resolutionZ));
}

inline int DistanceFieldBase::packedVoxelIndex(const Vec3d& pos)
{
  // get the indices
  int i = (int)((pos[0] - bmin_[0]) * invGridX);
  int j = (int)((pos[1] - bmin_[1]) * invGridY);
  int k = (int)((pos[2] - bmin_[2]) * invGridZ);

  return (k * resolutionY + j ) * resolutionX + i;
}

inline int DistanceFieldBase::packedVoxelIndex(int i, int j, int k)
{
  return (k * resolutionY + j ) * resolutionX + i;
}

inline void DistanceFieldBase::unpackVoxelIndex(int packedIndex, int & i, int & j, int & k)
{
  i = packedIndex % resolutionX;
  packedIndex = packedIndex / resolutionX;
  j = packedIndex % resolutionY;
  k = packedIndex / resolutionY;
}

inline double DistanceFieldBase::absoluteUnitsToGridUnits(double absoluteUnits) const
{
  double invGridSize = std::min(std::min(invGridX, invGridY), invGridZ);
  return absoluteUnits * invGridSize;
}

inline double DistanceFieldBase::gridUnitsToAbsoluteUnits(double gridUnits) const
{
  double gridSize = std::max(std::max(gridX, gridY), gridZ);
  return gridUnits * gridSize;
}


#endif

