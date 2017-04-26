/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "distance field" library , Copyright (C) 2007 CMU, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Hongyi Xu                                *
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
  Main computational routine for narrowband distance field computation.
*/

#include <float.h>
#include "performanceCounter.h"
#include "vegalong.h"

#ifdef COMPUTE_SIGNED_FIELD_NARROWBAND
   #ifdef COMPUTE_INTERIOR_FIELD_NARROWBAND
     int DistanceFieldNarrowBand::computeInteriorSignedField(ObjMesh * objMeshIn, int resolutionX_, int resolutionY_, int resolutionZ_, double bandWidth, int maxTriCount_, int maxDepth_)
   #else
     int DistanceFieldNarrowBand::computeSignedField(ObjMesh * objMeshIn, int resolutionX_, int resolutionY_, int resolutionZ_, double bandWidth, int maxTriCount_, int maxDepth_)
   #endif
#else
   int DistanceFieldNarrowBand::computeUnsignedField(ObjMesh * objMeshIn, int resolutionX_, int resolutionY_, int resolutionZ_, double bandWidth, int maxTriCount_, int maxDepth_)
#endif
{
  ObjMesh objMesh(*objMeshIn);

  maxTriCount = maxTriCount_; 
  maxDepth = maxDepth_;
  resolutionX = resolutionX_;
  resolutionY = resolutionY_;
  resolutionZ = resolutionZ_;

  vegalong size = (resolutionX + 1) * (resolutionY + 1) * (resolutionZ + 1);
  gridPointStatus = (char*) realloc(gridPointStatus, sizeof(char) * size);
  
  for(vegalong i = 0; i < size; i++)
    gridPointStatus[i] = DistanceFieldNarrowBand::EXTERIOR_UNCOMPUTED;
  
  #ifdef COMPUTE_SIGNED_FIELD_NARROWBAND
    // === check if closed mesh
    if (!(objMesh.isTriangularMesh()))
    {
      printf("Mesh was not triangular. Triangulating..."); fflush(NULL);
      objMesh.triangulate();
      printf(" done\n");
    }
    ObjMeshOrientable * objMeshOrientable = new ObjMeshOrientable(&objMesh, 0);

    int numOrientationFlips = objMeshOrientable->GenerateHalfEdgeDataStructure();

    if (numOrientationFlips==-1)
      return -1;

    cout << "Number of distinct connected components: " << objMeshOrientable->numConnectedComponents() << endl;
  
    cout << "Checking if mesh has no boundary..." << endl;
   
    // check if mesh has no boundary
    if (objMeshOrientable->hasBoundary())
    {
      cout << "Error: mesh has boundary. Signed distance field is ill-defined." << endl;
      cout << "  Num boundary edges: " << objMeshOrientable->numBoundaryEdges() << endl;
      int edge = objMeshOrientable->boundaryEdge(0);
      cout << "  A boundary edge: " << objMesh.getPosition(objMeshOrientable->halfEdge(edge).startVertex()) << " " <<
            objMesh.getPosition(objMeshOrientable->halfEdge(edge).endVertex()) << endl;
      return 1;
    }

    cout << "Mesh has no boundary (i.e. is closed surface)." << endl;

    cout << "Checking if input mesh is oriented consistently..."; 
    if (numOrientationFlips != 0)
    {
      cout << " no." << endl;
      cout << "Error: triangles in the input mesh are not oriented consistently." << endl;
      return 2;
    }
    else
      cout << " yes." << endl;
  
    delete(objMeshOrientable);
  #endif

  // === build octree

  printf("Preparing to build the octree. Max triangle count per cell: %d . Max depth: %d .\n", maxTriCount, maxDepth);fflush(NULL);

  #ifdef COMPUTE_SIGNED_FIELD_NARROWBAND
    ObjMeshOctree<TriangleWithCollisionInfoAndPseudoNormals> * objMeshOctree = 
      new ObjMeshOctree<TriangleWithCollisionInfoAndPseudoNormals>( &objMesh, maxTriCount, maxDepth );
  #else
    ObjMeshOctree<TriangleWithCollisionInfo> * objMeshOctree =
      new ObjMeshOctree<TriangleWithCollisionInfo>( &objMesh, maxTriCount, maxDepth );
  #endif

  if (useAutomaticBox && !bboxComputed)
    computeBoundingBox(&objMesh, resolutionX, resolutionY, resolutionZ);

  setGridParameters();
 
  cout << "Finding all the surface grid points..." << endl;
  // find all grid points that are in voxels that intersect the input polygonal geometry
  findSurfaceGridPoints(objMeshIn);

  cout << "Computing the distance field..." << endl;
  cout << "Corners of the bounding box are:" << endl;
  cout << "  " << bmin_ << endl;
  cout << "  " << bmax_ << endl;
  cout << "Grid sizes are: " << side[0] / resolutionX << " " << side[1] / resolutionY << " " << side[2] / resolutionZ << endl;

  int asterisk = 1;
  #ifdef COMPUTE_SIGNED_FIELD_NARROWBAND
    #ifdef COMPUTE_INTERIOR_FIELD_NARROWBAND
      {
        // compute the signed field inside the outer sigma-isosurface (assumes unsigned field has already been computed)
        std::map<gridPoint, float> distanceDataCopy = distanceData;
        distanceData.clear(); // clear the map
        breadthFirstTraversalInteriorSigned((void*)objMeshOctree, bandWidth, 0, resolutionZ, asterisk);

        for(std::map<gridPoint, float>::iterator it = distanceDataCopy.begin(); it != distanceDataCopy.end(); it++)
        {
          gridPoint v = it->first;
          vegalong index = (v.third * (resolutionY+1) + v.second) * (resolutionX + 1) + v.first;
          if (gridPointStatus[index] != DistanceFieldNarrowBand::COMPUTED)
          {
            distanceData.insert(*it);
            gridPointStatus[index] = DistanceFieldNarrowBand::COMPUTED;
          }
        }
      }
    #else
      // input geometry is manifold
      distanceData.clear(); // clear the compressed map
      breadthFirstTraversalSigned((void*)objMeshOctree, bandWidth, 0, resolutionZ, asterisk);
    #endif
  #else
    distanceData.clear();
    breadthFirstTraversalUnsigned((void*)objMeshOctree, bandWidth, 0, resolutionZ, asterisk);
  #endif

  delete(objMeshOctree);
  
  finalizeGridPointStatus();

  #ifdef COMPUTE_SIGNED_FIELD_NARROWBAND
    cout << endl << "Signed distance field successfully computed..." << endl;
  #else
    cout << endl << "Unsigned distance field successfully computed..." << endl;
  #endif

  return 0;
}

#ifdef COMPUTE_SIGNED_FIELD_NARROWBAND
  #ifdef COMPUTE_INTERIOR_FIELD_NARROWBAND
    int DistanceFieldNarrowBand::breadthFirstTraversalInteriorSigned(void * objMeshOctree_, float bandWidth, int zLo, int zHi, int asterisk)
  #else
    int DistanceFieldNarrowBand::breadthFirstTraversalSigned(void * objMeshOctree_, float bandWidth, int zLo, int zHi, int asterisk)
  #endif
#else
  int DistanceFieldNarrowBand::breadthFirstTraversalUnsigned(void * objMeshOctree_, float bandWidth, int zLo, int zHi, int asterisk)
#endif
{
  // triangleList will hold the triangles retrieved by range query
  #ifdef COMPUTE_SIGNED_FIELD_NARROWBAND
    vector< TriangleWithCollisionInfoAndPseudoNormals* > triangleList;
    ObjMeshOctree<TriangleWithCollisionInfoAndPseudoNormals> * objMeshOctree = (ObjMeshOctree<TriangleWithCollisionInfoAndPseudoNormals> *) objMeshOctree_;
  #else
    vector< TriangleWithCollisionInfo* > triangleList;
    ObjMeshOctree<TriangleWithCollisionInfo> * objMeshOctree = (ObjMeshOctree<TriangleWithCollisionInfo> *) objMeshOctree_;
  #endif

  double radius = len(side);

  std::set<gridPoint> scheduledGridPoints;
  
  vegalong mul = (resolutionX + 1) * (resolutionY + 1);
  for(unsigned int p = 0; p < surfaceGridPoints.size(); p++)
  {
    vegalong index = surfaceGridPoints[p];

    vegalong k = index / mul;
    if ((k >= zLo) && (k <= zHi))
    {
      int i = index % (resolutionX + 1);
      int j = (index / (resolutionX + 1)) % (resolutionY + 1);

      scheduledGridPoints.insert(gridPoint(i, j, k));
    }
  }

  int counter = 0;
  while(!scheduledGridPoints.empty())
  {
    gridPoint v = *(scheduledGridPoints.begin());
    scheduledGridPoints.erase(scheduledGridPoints.begin());

    int i = v.first;
    int j = v.second;
    int k = v.third;

    radius = len(side);
    
    float d[6];
    d[0] = distance((i < resolutionX) ? (i+1) : resolutionX, j, k);
    d[1] = distance((i > 0) ? (i-1) : 0, j, k);
    d[2] = distance(i, (j < resolutionY) ? (j+1) : resolutionY, k);
    d[3] = distance(i, (j > 0) ? (j-1) : 0, k);
    d[4] = distance(i, j, (k < resolutionZ) ? (k+1) : resolutionZ);
    d[5] = distance(i, j, (k > 0) ? (k-1) : 0);

    int ll = -1;
    for(int l = 0; l < 6; l++)
    {
      if (d[l] != FLT_MAX)
      {
	float fd = fabs(d[l]);
	if (fd < radius)
	{
	  radius = fabs(fd);
	  ll = l;
	}
      }
    }

    if ((ll == 0) || (ll == 1))
      radius += 1.01 * gridX;
    if ((ll == 2) || (ll == 3))
      radius += 1.01 * gridY;
    if ((ll == 4) || (ll == 5))
      radius += 1.01 * gridZ;

    Vec3d currentPosition
      (bmin_[0] + 1.0 * i * gridX,
       bmin_[1] + 1.0 * j * gridY, 
       bmin_[2] + 1.0 * k * gridZ);

    triangleList.clear();
    
    while (triangleList.size() <= 0) // we should only go through this loop exactly once
    {
      //printf("radius: %f pos: %f %f %f\n", radius, currentPosition[0], currentPosition[1], currentPosition[2]);
      objMeshOctree->rangeQuery(triangleList, SimpleSphere(currentPosition, radius));

      if (triangleList.size() <= 0) 
      { // should never happen... but to stay robust
        cout << "Warning: range query didn't find any triangles. Radius = " << radius << " . Increasing radius by a factor of 2 and re-trying." << endl;
        radius *= 2;
      }
    }    

    // find closest triangle among the retrieved ones
    // initialization:
    double closestDistance2 = 1.25 * radius * radius; // there will be somebody within that radius (actually even without the factor "1.25")
    // (factor "1.25" added to account for numerical round-off)

    int closestFeature = -1;
    int closestTriangle = -1;
    closestTriangle = closestTriangle; // to avoid compiler warnings
  
    for (unsigned int l=0; l<triangleList.size(); l++)
    {
      int closestLocalFeature = -1;        
      
      double d2 = triangleList[l]->distanceToPoint2(currentPosition,&closestLocalFeature);
    
      if (d2 < closestDistance2)
      {
        closestDistance2 = d2;
        closestFeature = closestLocalFeature;
        closestTriangle = l;
      }
    }

    // now, indexClosestTriangle and closestFeature are set to the closest triangle and the closest feature on the triangle
   
    if (closestFeature < 0) // should never happen
    {
      cout << "Internal error: did not find any triangle within the guaranteed radius:" << radius << endl;
      return 3;
    }

    // square root...
    float closestDistance = (float) sqrt(closestDistance2);

    #ifdef COMPUTE_SIGNED_FIELD_NARROWBAND    
    // determine sign, as in [Baerentzen 2002]
      Vec3d pseudoNormal = triangleList[closestTriangle]->pseudoNormal(closestFeature);
      Vec3d pseudoClosestPosition = triangleList[closestTriangle]->pseudoClosestPosition(closestFeature);
        
      if (dot(pseudoNormal,currentPosition-pseudoClosestPosition) < 0) // interior, must flip sign
        closestDistance *= -1;
    #endif

    if (fabs(closestDistance) < bandWidth)
    {
      int flag = 1;
      #ifdef COMPUTE_INTERIOR_FIELD_NARROWBAND
        if (closestDistance > 0)
          flag = 0;
      #endif

      if (flag)
      {
        for(int l = 0; l < 6; l++) 
        {
          if (fabs(d[l]) == FLT_MAX)
          {
            if (l < 2)
            {
              int xIndex = i + ((l % 2) ? -1 : 1);
              if ((xIndex >= 0) && (xIndex <= resolutionX))
                scheduledGridPoints.insert(gridPoint(xIndex, j, k));
            }
            else if ((l >= 2) && (l < 4))
            {
              int yIndex = j + ((l % 2) ? -1 : 1);
              if ((yIndex >= 0) && (yIndex <= resolutionY))
                scheduledGridPoints.insert(gridPoint(i, yIndex, k));
            }
            else
            {
              int zIndex = k + ((l % 2) ? -1 : 1);
              if ((zIndex >= zLo) && (zIndex <= zHi))
                scheduledGridPoints.insert(gridPoint(i, j, zIndex));
            }
          }
        }
      }
    }
    
    distanceData.insert(pair<gridPoint, float>(v, closestDistance));
    vegalong index = (v.third * (resolutionY + 1) + v.second) * (resolutionX + 1)+ v.first;
    gridPointStatus[index] = DistanceFieldNarrowBand::COMPUTED;

    counter ++;
    if (asterisk && (counter % (resolutionX * resolutionY) == 0))
    {
      counter = 0;
      printf("*"); fflush(NULL);
    }
  }

  return 0;
}

