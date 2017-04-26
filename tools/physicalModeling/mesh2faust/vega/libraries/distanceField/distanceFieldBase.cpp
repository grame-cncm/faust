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

#include <iostream>
#include "objMeshOrientable.h"
#include "objMeshOctree.h"
#include "distanceFieldBase.h"
using namespace std;

DistanceFieldBase::DistanceFieldBase() 
{
  resolutionX = 1;
  resolutionY = 1;
  resolutionZ = 1;
  setAutomaticBoundingBox();
  bmin_ = Vec3d(0,0,0);
  bmax_ = Vec3d(1,1,1);
  setGridParameters();
  bboxComputed = false;
}

DistanceFieldBase::DistanceFieldBase(int resolutionX_, int resolutionY_, int resolutionZ_) : resolutionX(resolutionX_), resolutionY(resolutionY_), resolutionZ(resolutionZ_)
{
  setAutomaticBoundingBox();
  bmin_ = Vec3d(0,0,0);
  bmax_ = Vec3d(1,1,1);
  setGridParameters();
  bboxComputed = false;
}

void DistanceFieldBase::computeBoundingBox(ObjMesh * objMesh, int resolutionX, int resolutionY, int resolutionZ)
{
  Vec3d bminTemp, bmaxTemp;
  objMesh->getBoundingBox(1.0, &bminTemp, &bmaxTemp);

  // set aspect ratio that corresponds to the resolutions
  Vec3d bcenterTemp = 0.5 * (bminTemp + bmaxTemp);

  cout << "Tight bounding box:" << endl << "  " << bminTemp << endl << "  " << bmaxTemp << endl;

  Vec3d sideTemp = bmaxTemp - bminTemp;
  if (sideTemp[0] / resolutionX < sideTemp[1] / resolutionY)
  {
    // increase x
    sideTemp[0] = sideTemp[1] / resolutionY * resolutionX;
  }
  else
  {
    // increase y
    sideTemp[1] = sideTemp[0] / resolutionX * resolutionY;
  }

  // now x,y are ok, must adjust z
  if (sideTemp[1] / resolutionY < sideTemp[2] / resolutionZ)
  {
    // increase x and y
    double factor = (sideTemp[2] / resolutionZ * resolutionY) / sideTemp[1];
    sideTemp[1] *= factor;
    sideTemp[0] *= factor;
  }
  else
  {
    // increase z
    sideTemp[2] = sideTemp[1] / resolutionY * resolutionZ;
  }

  BoundingBox bbox(bminTemp, bmaxTemp);
  bbox.setbmin(bcenterTemp - 0.5 * sideTemp);
  bbox.setbmax(bcenterTemp + 0.5 * sideTemp);
  if (allBoxSidesEqual)
    bbox.regularize();
  bbox.expand(expansionRatio);

  bmin_ = bbox.bmin();
  bmax_ = bbox.bmax();

  bboxComputed = true;
}

