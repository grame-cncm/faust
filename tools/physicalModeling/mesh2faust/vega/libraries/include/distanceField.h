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

#ifndef _DISTANCEFIELD_H_
#define _DISTANCEFIELD_H_

#include "objMesh.h"
#include "objMeshOrientable.h"
#include "objMeshOctree.h"
#include "distanceFieldBase.h"
#include "vegalong.h"

class DistanceField : public DistanceFieldBase
{
public:

  DistanceField();
  virtual ~DistanceField();

  DistanceField(int resolutionX, int resolutionY, int resolutionZ);

  // computes unsigned distance field
  virtual int computeUnsignedField(ObjMesh * objMesh, int resolutionX, int resolutionY, int resolutionZ,int maxTriCount=15, int maxDepth=10, int zMin = -1, int zMax = -1);

  // computes signed distance field
  virtual int computeSignedField(ObjMesh * objMesh, int resolutionX, int resolutionY, int resolutionZ, int maxTriCount=15, int maxDepth=10, int zMin = -1, int zMax = -1);

  // computes signed distance field using flood fill
  // must call computeUnsignedField for the same objMesh and same resolution first
  virtual int computeFloodFillSignedField(ObjMesh * objMesh, int resolutionX, int resolutionY, int resolutionZ, int maxTriCount=15, int maxDepth=10, int zMin = -1, int zMax = -1);

  void enableVoronoiDiagramComputation(bool computeVoronoiDiagram);

  // loads a previously computed distance field from a disk file
  virtual int load(const std::string& filename); // returns 0 on success

  // opens the distance field for stream processing
  // this is advanced routine, don't use in normal circumstances; use "load" instead
  int openStreamDistanceField(const std::string& filename, Vec3d * bmin, Vec3d * bmax, int * resolutionX, int * resolutionY, int * resolutionZ, bool * floatData, std::ifstream & fin);
  void retrieveZSlice(std::ifstream & fin, bool floatData, int resolutionX, int resolutionY, int resolutionZ, float * slice);

  // saves the current distance field to a disk file (e.g. after computing it once, for later fast reloading) 
  virtual int save(const std::string& filename, bool doublePrecision);
  int saveVoronoiDiagram(const std::string& filename);

  // exports the distance field to a file, in text format
  virtual int saveToText(const std::string& filename);

  // sets the distance field to the given external data
  virtual void set(int resolutionX, int resolutionY, int resolutionZ, Vec3d bmin_, Vec3d bmax_, float * distanceData);

  // Is data from the given file in single or double precision?
  // note: this class uses single precision everywhere, but some older code
  // used double precision, so routines were necessary to load binary distance field files computed using old versions
  int isDoublePrecision(const std::string & filename, bool & doublePrecision);

  // return distance field value at grid vertex (i,j,k)
  // each of i,j,k must be an integer from {0, ..., resolution{X,Y,Z}}
  virtual inline float distance(int i, int j, int k) { return distanceData[(k * (resolutionY + 1) + j ) * (resolutionX + 1) + i]; }
  // computes distance and gradient at arbitrary position
  virtual float distance(Vec3d pos, int constrainToBox=0);

  // alters the distance at a particular grid vertex (i,j,k)
  virtual inline void setDistance(int i, int j, int k, float value) { distanceData[(k * (resolutionY + 1) + j ) * (resolutionX + 1) + i] = value; }

  // gradient is computed with respect to trilinear interpolation
  // note: gradient is discontinuous at the cell boundaries
  virtual Vec3d gradient(const Vec3d& pos);

  virtual bool sanityCheck(); // checks if distance for any two adjacent voxels is less than voxel grid spacing apart (which it must be by triangle inequality, for both signed and unsigned fields)

  virtual float maxValue();
  virtual float minValue();
  virtual void  maxMinValue(float* maxValue, float* minValue);

  virtual float maxAbsValue();
  virtual float maxAbsValue(float threshold); // only abs values up to threshold
  virtual float maxNonInftyAbsValue();

  float minBoundaryValue(); // minimum distance value on the surface of the bounding box
  float getMinBoundaryValue() { return minBoundaryDistance;}

  // returns the entire distance data, by allocating the buffer and copying the distance data into it 
  virtual void getDistanceData(float ** floatBuffer);

  // returns the pointer to the internally allocated data
  float * getDistanceDatap() { return distanceData; }

  // Is voxel with indices (i,j,k) intersecting the zero-isocontour? (only applies to signed distance fields)
  bool isSurfaceVoxel(int i, int j, int k); 
  // total number of such voxels
  int numSurfaceVoxels(float levelSetValue = 0.0); 
  // If distance field were resampled to customResolution, is voxel with indices (i,j,k) intersecting the isocontour with value levelSetValue ?
  bool isSurfaceVoxel(int customResolutionX, int customResolutionY, int customResolutionZ, int i, int j, int k, float levelSetValue);
  // total number of such voxels
  int numSurfaceVoxels(int customResolutionX, int customResolutionY, int customResolutionZ, float levelSetValue); 

  // sets the computation range for the z-coordinate (by default, the entire z-range will be computed)
  inline void setComputationZRange(int zMin, int zMax);

  virtual void print();

  virtual int ZigZagSigned(void * objMeshOctree, void * meshGraph); // will be redefined in MT subclasses
  virtual int ZigZagUnsigned(void * objMeshOctree, void * meshGraph); // will be redefined in MT subclasses
  virtual int ZigZagFloodFillSigned(void * objMeshOctree, void * meshGraph);

  virtual int ZigZagSigned(void * objMeshOctree, void * meshGraph, int zLo, int zHi, int asterisk=0);
  virtual int ZigZagUnsigned(void * objMeshOctree, void * meshGraph, int zLo, int zHi, int asterisk=0);
  virtual int ZigZagFloodFillSigned(void * objMeshOctree, void * meshGraph, int zLo, int zHi, int asterisk=0);

  void computeFloodFillTag(ObjMesh* objMesh);
  void freeMemory(){free(distanceData); distanceData = NULL;};

 // returns earliest contact time assuming point travels with constant velocity
  // returns -1.0 if there is no contact
  double pointCCD(Vec3d startPos, Vec3d endPos);

  virtual void offsetDistanceField(double offset);
protected:
  int maxTriCount;
  int maxDepth;
 
  float * distanceData; // the raw distance data
  float * pseudoData; // for debug

  char * floodFillTag;
  int * voronoiDiagram; 
  bool computeVoronoiDiagram;

  int zMin, zMax;
  //ObjMeshOctree<TriangleWithCollisionInfo> * objMeshOctree;
  //ObjMeshOctree<TriangleWithCollisionInfoAndPseudoNormals> * objMeshOrientedOctree;
  float minBoundaryDistance;
  vegalong GetFilesize(const char *filename);
};

inline void DistanceField::setComputationZRange(int zMin, int zMax)
{
  this->zMin = zMin;
  this->zMax = zMax;
}

#endif

