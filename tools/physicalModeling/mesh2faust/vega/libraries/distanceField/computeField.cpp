/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "distance field" library , Copyright (C) 2007 CMU, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
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
  These are the key computational routines to compute the distance field.
*/

#include <float.h>
#include "objMeshGraph.h"
#include "vegalong.h"

#ifdef COMPUTE_SIGNED_FIELD
  #ifdef COMPUTE_FLOOD_FIELD
    int DistanceField::computeFloodFillSignedField(ObjMesh* objMeshIn, int  resolutionX_, int resolutionY_, int resolutionZ_, int maxTriCount_, int maxDepth_,int zMin_, int zMax_ )
  #else
    #ifdef COMPUTE_CLOSEST_POINT
      int ClosestPointField::computeSignedField(ObjMesh * objMeshIn, int resolutionX_, int resolutionY_, int resolutionZ_, int maxTriCount_, int maxDepth_,int zMin_, int zMax_ )
    #else
      int DistanceField::computeSignedField(ObjMesh * objMeshIn, int resolutionX_, int resolutionY_, int resolutionZ_, int maxTriCount_, int maxDepth_, int zMin_, int zMax_)
    #endif
  #endif
#else
  #ifdef COMPUTE_CLOSEST_POINT
    int ClosestPointField::computeUnsignedField(ObjMesh * objMeshIn, int resolutionX_, int resolutionY_, int resolutionZ_, int maxTriCount_, int maxDepth_, int zMin_, int zMax_)
  #else
    int DistanceField::computeUnsignedField(ObjMesh * objMeshIn, int resolutionX_, int resolutionY_, int resolutionZ_, int maxTriCount_, int maxDepth_, int zMin_, int zMax_)
  #endif
#endif
{
  ObjMesh objMesh(*objMeshIn);

  maxTriCount = maxTriCount_; 
  maxDepth = maxDepth_;
  resolutionX = resolutionX_;
  resolutionY = resolutionY_;
  resolutionZ = resolutionZ_;

  #ifdef COMPUTE_SIGNED_FIELD
    // === check if closed mesh
    if (!(objMesh.isTriangularMesh()))
    {
      printf("Mesh was not triangular. Triangulating..."); fflush(NULL);
      objMesh.triangulate();
      printf(" done\n");
    }
    ObjMeshOrientable * objMeshOrientable = new ObjMeshOrientable(&objMesh, 0);

    int numOrientationFlips = objMeshOrientable->GenerateHalfEdgeDataStructure();
    if (numOrientationFlips < 0)
    {
      printf("Error: cannot orient the mesh. Geometry is non-manifold.\n");
      exit(1);
    }

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

  ObjMeshGraph * meshGraph = NULL;
  if (computeVoronoiDiagram)
  {
    meshGraph = new ObjMeshGraph(&objMesh);
    printf("Original graph:\n");
    meshGraph->PrintInfo();
    //meshGraph->ExpandNeighbors();
    //printf("Expanded graph:\n");
    //meshGraph->PrintInfo();
    if (voronoiDiagram != NULL)
      free(voronoiDiagram);
    voronoiDiagram = (int*) malloc (sizeof(int) * (resolutionX+1) * (resolutionY+1) * (resolutionZ+1));
  }

  // === build octree

  printf("Preparing to build the octree. Max triangle count per cell: %d . Max depth: %d .\n", maxTriCount, maxDepth);fflush(NULL);

  #ifdef COMPUTE_SIGNED_FIELD
    ObjMeshOctree<TriangleWithCollisionInfoAndPseudoNormals> * objMeshOctree = 
      new ObjMeshOctree<TriangleWithCollisionInfoAndPseudoNormals>( &objMesh, maxTriCount, maxDepth );
  #else
    ObjMeshOctree<TriangleWithCollisionInfo> * objMeshOctree =
      new ObjMeshOctree<TriangleWithCollisionInfo>( &objMesh, maxTriCount, maxDepth );
  #endif


  #ifndef COMPUTE_FLOOD_FIELD
    if (useAutomaticBox && !bboxComputed)
    {
      computeBoundingBox(&objMesh, resolutionX, resolutionY, resolutionZ);
    }
   #endif

  setGridParameters();
  zMin = (zMin_==-1) ? 0 : zMin_;
  zMax = (zMax_==-1) ? resolutionZ : zMax_;
  
  #ifndef COMPUTE_FLOOD_FIELD
    //distanceData = (float*) malloc (sizeof(float)*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));
    vegalong size = sizeof(float)*(resolutionX+1)*(resolutionY+1)*(zMax - zMin +1);
    distanceData = (float*) realloc (distanceData, size);
     
    // initialize to FLT_MAX
    for(vegalong ii=0; ii<=resolutionX; ii++)
      for(vegalong jj=0; jj<=resolutionY; jj++)
        for(vegalong kk=zMin; kk<=zMax; kk++)
        {
          vegalong index = (kk-zMin) * (resolutionX+1) * (resolutionY+1) + jj * (resolutionX+1) + ii;
          distanceData[index] = FLT_MAX;
        }
  #else
    if(zMin == 0)
    {
      cout << "computing the flood fill tag..." << endl;
      computeFloodFillTag(&objMesh);
    }
  #endif

  // debug
  #ifdef GENERATE_DEBUG_DATA
    pseudoData = (float*) malloc (6*sizeof(float)*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));
  #endif

  #ifdef COMPUTE_CLOSEST_POINT
     closestPointData = (float*) malloc (3*sizeof(float)*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));
  #endif

  cout << "Computing the distance field..." << endl;
  cout << "Corners of the bounding box are:" << endl;
  cout << "  " << bmin_ << endl;
  cout << "  " << bmax_ << endl;
  cout << "Grid sizes are: " << side[0] / resolutionX << " " << side[1] / resolutionY << " " << side[2] / resolutionZ << endl;

  #ifdef COMPUTE_SIGNED_FIELD
    #ifdef COMPUTE_FLOOD_FIELD
      ZigZagFloodFillSigned((void*)objMeshOctree, (void*)meshGraph);
    #else
      ZigZagSigned((void*)objMeshOctree, (void*)meshGraph);
    #endif
  #else
    ZigZagUnsigned((void*)objMeshOctree, (void*)meshGraph);
  #endif

  delete(objMeshOctree);
  delete(meshGraph);

  if(zMax == resolutionZ)
  {
    //free(floodFillTag);
    #ifdef COMPUTE_SIGNED_FIELD
      cout << endl << "Signed distance field successfully computed..." << endl;
    #else
      cout << endl << "Unsigned distance field successfully computed..." << endl;
    #endif
  }

  return 0;
}

#ifdef COMPUTE_SIGNED_FIELD
  #ifdef COMPUTE_FLOOD_FIELD
    int DistanceField::ZigZagFloodFillSigned(void * objMeshOctree_, void * meshGraph_)
  #else
    #ifdef COMPUTE_CLOSEST_POINT
      int ClosestPointField::ZigZagSigned(void * objMeshOctree_, void * meshGraph_)
    #else
      int DistanceField::ZigZagSigned(void * objMeshOctree_, void * meshGraph_)
    #endif
  #endif
  #ifdef COMPUTE_FLOOD_FIELD
     #define ZIGZAGROUTINE ZigZagFloodFillSigned
  #else
     #define ZIGZAGROUTINE ZigZagSigned
  #endif
#else
  #ifdef COMPUTE_CLOSEST_POINT
    int ClosestPointField::ZigZagUnsigned(void * objMeshOctree_, void * meshGraph_)
  #else
    int DistanceField::ZigZagUnsigned(void * objMeshOctree_, void * meshGraph_)
  #endif
  #define ZIGZAGROUTINE ZigZagUnsigned
#endif
{
  return ZIGZAGROUTINE (objMeshOctree_, meshGraph_, zMin, zMax);
}
#undef ZIGZAGROUTINE

#ifdef COMPUTE_SIGNED_FIELD
  #ifdef COMPUTE_FLOOD_FIELD
    int DistanceField::ZigZagFloodFillSigned(void * objMeshOctree_, void * meshGraph_, int zLo, int zHi, int asterisk)
  #else
    #ifdef COMPUTE_CLOSEST_POINT
      int ClosestPointField::ZigZagSigned(void * objMeshOctree_, void * meshGraph_, int zLo, int zHi, int asterisk)
    #else
      int DistanceField::ZigZagSigned(void * objMeshOctree_, void * meshGraph_, int zLo, int zHi, int asterisk)
    #endif
  #endif
#else
  #ifdef COMPUTE_CLOSEST_POINT
    int ClosestPointField::ZigZagUnsigned(void * objMeshOctree_, void * meshGraph_, int zLo, int zHi, int asterisk)
  #else
    int DistanceField::ZigZagUnsigned(void * objMeshOctree_, void * meshGraph_, int zLo, int zHi, int asterisk)
  #endif
#endif
{
  ObjMeshGraph * meshGraph = (ObjMeshGraph*) meshGraph_;

  // triangleList will hold the triangles retrieved by range query
  #ifdef COMPUTE_SIGNED_FIELD
    vector< TriangleWithCollisionInfoAndPseudoNormals* > triangleList;
    ObjMeshOctree<TriangleWithCollisionInfoAndPseudoNormals> * objMeshOctree = (ObjMeshOctree<TriangleWithCollisionInfoAndPseudoNormals> *) objMeshOctree_;
  #else
    vector< TriangleWithCollisionInfo* > triangleList;
    ObjMeshOctree<TriangleWithCollisionInfo> * objMeshOctree = (ObjMeshOctree<TriangleWithCollisionInfo> *) objMeshOctree_;
  #endif

  // do the zig-zag
  vegalong i=0, j=0, k=0;
  k = zLo;
  
  int diri=1;
  int dirj=1;

  double radius = len(side);

  int needtoCheckFlag = 0;
  int skipFlag = 0;
  needtoCheckFlag = needtoCheckFlag; // just for removing warnings
  do
  {
    vegalong index = (k-zMin) * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i;
    skipFlag = 0;
    #ifdef COMPUTE_FLOOD_FIELD
    if(!needtoCheckFlag && floodFillTag[index] == 0)
       skipFlag = 1;
    #endif

    float closestDistance = 0;
    if(!skipFlag)
    {
      Vec3d currentPosition
                  (bmin_[0] + 1.0 * i * gridX,
                   bmin_[1] + 1.0 * j * gridY, 
                   bmin_[2] + 1.0 * k * gridZ);

      //printf("%d %d %d\n",i,j,k);
      // process grid point i,j,k 
      triangleList.clear();
    
      while (triangleList.size() <= 0) // we should only go through this loop exactly once
      {
        //printf("radius: %f pos: %f %f %f\n", radius, currentPosition[0], currentPosition[1], currentPosition[2]);
        objMeshOctree->rangeQuery(triangleList, SimpleSphere(currentPosition, radius));

        if (triangleList.size() <= 0) 
        { // should never happen... but to stay robust
          cout << "Warning: range query didn't find any triangles. Increasing radius by a factor of 2 and re-trying." << endl;
          radius *= 2;
        }

        //if (triangleList.size() > 5)
        //makeUniqueList(triangleList);
      }    

      // find closest triangle among the retrieved ones
      // initialization:
      double closestDistance2 = 1.25 * radius * radius; // there will be somebody within that radius (actually even without the factor "1.25")
        // (factor "1.25" added to account for numerical round-off)

      int closestFeature = -1;
      int closestTriangle = -1;
      closestTriangle = closestTriangle; // to avoid compiler warnings
      int indexClosestTriangle = -1;

      #ifdef COMPUTE_CLOSEST_POINT
        Vec3d closestPosition(DBL_MAX, DBL_MAX, DBL_MAX);
      #endif
    
      for (unsigned int l=0; l<triangleList.size(); l++)
      {
        int closestLocalFeature = -1;        

        #ifdef COMPUTE_CLOSEST_POINT
          double alpha, beta, gamma;
          double d2 = triangleList[l]->distanceToPoint2(currentPosition, &closestLocalFeature, &alpha, &beta, &gamma);        
          if (d2 < closestDistance2)
          {          
            closestDistance2 = d2;
            closestPosition = triangleList[l]->getBarycentricLocation(alpha, beta, gamma);          
            closestFeature = closestLocalFeature; 
            closestTriangle = l;
            indexClosestTriangle =  triangleList[l]->index();          
          }
        #else
          double d2 = triangleList[l]->distanceToPoint2(currentPosition,&closestLocalFeature);
          if (d2 < closestDistance2)
          {
            closestDistance2 = d2;
            closestFeature = closestLocalFeature;
            closestTriangle = l;
            indexClosestTriangle =  triangleList[l]->index();          
          }
        #endif
      }

      // now, indexClosestTriangle and closestFeature are set to the closest triangle and the closest feature on the triangle
    
      if (computeVoronoiDiagram)
      {
        int closestSite = meshGraph->graphID(indexClosestTriangle, closestFeature);
        voronoiDiagram[k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i] = closestSite;
        //printf("cs: %d cf: %d\n", closestSite, closestFeature);
      }

      if (closestFeature < 0) // should never happen
      {
        cout << "Internal error: did not find any triangle within the guaranteed radius:" << radius << endl;
        return 3;
      }

      #ifdef GENERATE_DEBUG_DATA      
         if ((i==34) && (j==17) && ((k==44) || (k==45)))      
         {
           printf("Closest index: %d Feature: %d Min dist2: %.15f\n\n", indexClosestTriangle, closestFeature, closestDistance2);
         }      
         if ((i==34) && (j==17) && ((k==44) || (k==45)))        
           printf("Grid location: %.15f %.15f %.15f\n", currentPosition[0], currentPosition[1], currentPosition[2]);    
      #endif
    
      // square root...
      closestDistance = (float) sqrt(closestDistance2);
    
      #ifdef COMPUTE_SIGNED_FIELD
        // determine sign, as in [Baerentzen 2002]
        Vec3d pseudoNormal = triangleList[closestTriangle]->pseudoNormal(closestFeature);
        Vec3d pseudoClosestPosition = triangleList[closestTriangle]->pseudoClosestPosition(closestFeature);

        #ifdef COMPUTE_FLOOD_FIELD
          if (dot(pseudoNormal,currentPosition-pseudoClosestPosition) <= 0) // interior, must flip sign
          {
	    closestDistance *= -1;
	    needtoCheckFlag = 1;
          }
          else
	    needtoCheckFlag = 0;
        #else
          if (dot(pseudoNormal,currentPosition-pseudoClosestPosition) < 0) // interior, must flip sign
             closestDistance *= -1;
        #endif
        //printf("%G ", closestDistance);
      #endif

      // register result
      distanceData[index] = closestDistance;
    
      #ifdef COMPUTE_CLOSEST_POINT
        vegalong dataIndex = 3 * (k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i);
        closestPointData[dataIndex+0] = closestPosition[0];
        closestPointData[dataIndex+1] = closestPosition[1];
        closestPointData[dataIndex+2] = closestPosition[2];
      #endif

      // store debug info to disk file
      #ifdef GENERATE_DEBUG_DATA
        //pseudoData[6*(k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i)+0] = pseudoNormal[0];
        //pseudoData[6*(k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i)+1] = pseudoNormal[1];
        //pseudoData[6*(k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i)+2] = pseudoNormal[2];
        //pseudoData[6*(k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i)+3] = pseudoClosestPosition[0];
        //pseudoData[6*(k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i)+4] = pseudoClosestPosition[1];
        //pseudoData[6*(k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i)+5] = pseudoClosestPosition[2];
        pseudoData[6*(k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i)+0] = 0;
        pseudoData[6*(k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i)+1] = 0;
        pseudoData[6*(k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i)+2] = 0;
        pseudoData[6*(k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i)+3] = closestPosition[0];
        pseudoData[6*(k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i)+4] = closestPosition[1];
        pseudoData[6*(k * (resolutionX+1) * (resolutionY+1) + j * (resolutionX+1) + i)+5] = closestPosition[2];
      #endif
    }

    closestDistance = distanceData[index];
   
    vegalong oldi = i;
    vegalong oldj = j;
    vegalong oldk = k;

    // increment i,j,k
    i += diri; 

    if (i>resolutionX)
    {
      diri = -1; // start going to the left
      i = resolutionX;
      j += dirj;
    }

    if (i<0)
    {
      diri = +1; // start going to the right
      i = 0;
      j += dirj;
    }

    if (j>resolutionY)
    {
      dirj = -1; // start going down
      j = resolutionY;
      if (asterisk)
        cout << "*";
      cout << k << " " << flush;
      k += 1;
    }

    if (j<0)
    {
      dirj = +1; // start going  up
      j = 0;
      if (asterisk)
        cout << "*";
      cout << k << " " << flush;
      k += 1;
    }

    // spatial coherence: update radius for next iteration
    double delta=0.0; // this will be modified below
    if (i != oldi)
      delta = 1.01 * gridX;

    if (j != oldj)
      delta = 1.01 * gridY;

    if (k != oldk)
      delta = 1.01 * gridZ;

    radius = fabs(closestDistance) + delta;
  }
  while (k <= zHi); 

  return 0;
}

