/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "objMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC        *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Christopher Twigg, Daniel Schroeder      *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Research: Jernej Barbic, Fun Shing Sin, Daniel Schroeder,             *
 *           Doug L. James, Jovan Popovic                                *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
 *          Singapore-MIT GAMBIT Game Lab,                               *
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

#ifndef _OBJMESHOFFSETVOXELS_H_
#define _OBJMESHOFFSETVOXELS_H_

/*
  Author: Jernej Barbic, 2003
  Voxelizes the given triangular geometry.
*/

#include <set>
#include "triangle.h"
#include "simpleSphere.h"
#include "objMesh.h"
#include "triple.h"
#include "boundingBox.h"
#include "minivector.h"

class ObjMeshOffsetVoxels 
{
public:
  // voxelizes the given triangular geometry
  // resolution is the grid resolution in xyz
  // "depth" means that the output includes voxels that are grown a "depth" number of layers away from the originally interesecting voxels (good default: 0)
  // note: cubic mesh means voxel mesh in this class
  ObjMeshOffsetVoxels(ObjMesh * objMesh, int resolution[3], int depth=0, double expansionFactor=1.2); // cube box; size is computed by expanding the tight-fitting cube by the given expansion ratio
  ObjMeshOffsetVoxels(ObjMesh * objMesh, int resolution[3], int depth, Vec3d boxbmin, Vec3d boxbmax); // explicitly provide the bounding box

  // flood-fills the space outward from the voxel containing seed, until hitting existing voxels
  void floodFill(Vec3d seed);
  void floodFill(std::vector<Vec3d> & seeds);
  // finds all empty components in the voxel structure, and gives seeds and sizes for each of them
  void emptyComponents(std::vector<Vec3d> & componentSeeds, std::vector<int> & componentSize, bool interiorOnly = true);

  size_t numVoxels() { return voxels.size(); }
  double voxelSpacing() { return inc[0]; }

  // generates the voxel mesh vertices, the voxel elements, the interpolation structure to interpolate quantities from the voxel mesh to the 
  void generateCubicMesh(
    int * numVertices, double ** vertices, 
    int * numElements, int ** elements,
    int ** interpolationVertices, 
    double ** interpolationWeights, ObjMesh ** surfaceMesh);

  // generates the surface mesh of the computed voxel mesh
  ObjMesh * surfaceOffsetMesh();

  // writes the voxel mesh file to disk, as well as the interpolation file and the surface mesh file
  void generateCubicMesh(const std::string & filenameVeg, const std::string & filenameInterp, const std::string & filenameObj);

 // generates the interpolation mask for the geometry from an external file 'inputObjMesh'
 void generateInterpolationMasks(const std::string & filenameInterp, const std::string & inputObjMesh);

 //  generates the normal correction matrix for the vertices from the external file 'inputObjMesh'
 void generateNormalCorrectionMatrix(const std::string filenameCorrectionMatrix, 
                const std::string inputObjMesh, 
		const std::string filenameVoxelModalMatrix,
 	        const std::string filenameNormals);

  typedef triple<int,int,int> voxel;
  typedef triple<int,int,int> gridPoint;

  class TopologicalFace
  {
  public:
    TopologicalFace(gridPoint p1, gridPoint p2, gridPoint p3, gridPoint p4);

    //accessor
    gridPoint vertex(int i) const { return vertices_[i];}

    void sortVertices(); // sorts the face

  protected:
    std::vector<gridPoint> vertices_;
  };

  class FaceOrder
  {
  public:
    bool operator()(const TopologicalFace & x, const TopologicalFace & y) const;
  };

  void render();
  void renderSurfaceFaces();
  void renderTopologicalFace(const TopologicalFace & face) const;

protected:
  ObjMesh * objMesh;

  int resolution[3]; 
  int depth;
  std::set<voxel> voxels;
  std::set<TopologicalFace,FaceOrder> surfaceFaces;
  std::set<TopologicalFace,FaceOrder> interiorFaces;

  Vec3d bmin,bmax,side,inc;

  void renderVoxel(voxel vox);

  // internal routine, builds a unique list of faces from the current voxels structure
  void buildUniqueListOfFaces();

  // performs flood fill from seed, starting with voxel set voxelSet (which is updated to reflect the addition of the new flood-filled region)
  // returns whether a voxel that touches the bounding box was added
  bool floodFillFromSet(Vec3d seed, std::set<voxel> & voxelSet);

  void init(int resolution[3], int depth, Vec3d bmin, Vec3d bmax);
};

#endif

