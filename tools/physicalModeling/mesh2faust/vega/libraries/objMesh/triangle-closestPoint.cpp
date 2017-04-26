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

/*
  Closest point in a 3D triangle to the given query 3D point
  Jernej Barbic
  Carnegie Mellon University, 2003-2007
*/
#include "triangle.h"
#ifdef __VERSION_WITH_BARYCENTRIC_COORDS_JNB_CMU__
double TriangleWithCollisionInfo::distanceToPoint2(const Vec3d & point, int * closestFeature, double * alpha, double * beta, double * gamma) const
#else
double TriangleWithCollisionInfo::distanceToPoint2(const Vec3d & point, int * closestFeature) const
#endif

{
  // squared 3d distance to a point
  // also returns the closest feature to the query point:
  //  0: vertex0
  //  1: vertex1
  //  2: vertex2
  //  3: edge among 01
  //  4: edge among 12
  //  5: edge among 20
  //  6: the face itself

  // and also returns the barycentric coordinates of the closest point

  /*

   y    \G E /
    ^ N21\  /N12
    |     2/
    | I   /\
    |    /  \  F
 N22|   /    \      /
 \  |  /S2  S1\    /N11
  \ | /   J    \  /   
 H \|/          \/  D
     ---------------------->
   0|            |1        x
    |            |
 A  |     C      |    B
    |            |

  */

  #ifdef __VERSION_WITH_BARYCENTRIC_COORDS_JNB_CMU__
    double * barycentricCoordsRaw[3] = { alpha, beta, gamma};
    double * barycentricCoords[3] = { 
      barycentricCoordsRaw[permutation[0]], barycentricCoordsRaw[permutation[1]], barycentricCoordsRaw[permutation[2]]};
  #endif

  // first transform the point into the plane
  Vec3d P = Q * point + x0;

  //printf("Transformed point: %.15f %.15f %.15f\n", P[0], P[1], P[2]);
  //printf("a: %.15f\n", sidea);
  double d = P[2] * P[2]; // contribution due to the z-offset

  // determine distance of P[0],P[1] to the planar triangle
 
  P[2] = 1; // transformation to homogeneous coordinates
  double x = P[0];
  double y = P[1];

  double u,v;
  bool caseECandidate = false;
 
  if (y <= 0)
  {
    if (x < 0)
    {
      // case A
      //printf("case A\n");
      *closestFeature = permutation[0]; // vertex 0
      #ifdef __VERSION_WITH_BARYCENTRIC_COORDS_JNB_CMU__
        // *alpha = 1; *beta = 0; *gamma = 0;
        *(barycentricCoords[0]) = 1; *(barycentricCoords[1]) = 0; *(barycentricCoords[2]) = 0;
      #endif
      return (d + x*x + y*y);
    }
    else if (x > sidea)
    {
      // case B
      //printf("case B\n");
      *closestFeature = permutation[1]; // vertex 1
      #ifdef __VERSION_WITH_BARYCENTRIC_COORDS_JNB_CMU__
        // *alpha = 0; *beta = 1; *gamma = 0;
        *(barycentricCoords[0]) = 0; *(barycentricCoords[1]) = 1; *(barycentricCoords[2]) = 0;
      #endif
      return (d + (x-sidea)*(x-sidea) + y*y);
    }
    else
    {
      // case C
      //printf("case C\n");
      *closestFeature = permutation[3]; // edge 01
      #ifdef __VERSION_WITH_BARYCENTRIC_COORDS_JNB_CMU__
        // *alpha = (sidea-x)/sidea; *beta = 1 - *alpha; *gamma = 0;
        *(barycentricCoords[0]) = (sidea-x)/sidea; *(barycentricCoords[1]) = 1 - *(barycentricCoords[0]); *(barycentricCoords[2]) = 0;
      #endif
      return (d + y*y);
    }
  }
  else 
  {
    // we have y > 0

    u = dot(S1,P);
    if (u >= 0) // above s1
    {
      v = dot(N11,P);
      if (v <= 0) // below N11
      {
        // case D
        //printf("case D\n");
        *closestFeature = permutation[1]; // vertex 1
        #ifdef __VERSION_WITH_BARYCENTRIC_COORDS_JNB_CMU__
          // *alpha = 0; *beta = 1; *gamma = 0;
          *(barycentricCoords[0]) = 0; *(barycentricCoords[1]) = 1; *(barycentricCoords[2]) = 0;
        #endif
        return (d + v*v + u*u);
      }
      else
      {
        v = dot(N12,P);
        if (v >= 0) // above N12
        {
          // case E
          caseECandidate = true;

          //printf("case E (candidate)\n");
          // *closestFeature = permutation[2]; // vertex 2
          // *alpha = 0; *beta = 0; *gamma = 1;
          // *(barycentricCoords[0]) = 0; *(barycentricCoords[1]) = 0; *(barycentricCoords[2]) = 1;
          //return (d + v*v + u*u);
        }
        else // between N11 and N12
        {
          // case F
          //printf("case F\n");
          *closestFeature = permutation[4]; // edge 12
          #ifdef __VERSION_WITH_BARYCENTRIC_COORDS_JNB_CMU__
            // *alpha = 0; *beta = -v / sideb; *gamma = 1 - *beta; 
            *(barycentricCoords[0]) = 0; *(barycentricCoords[1]) = -v / sideb; *(barycentricCoords[2]) =  1 - *(barycentricCoords[1]);
          #endif
          return (d + u*u);
        }
      }
    }

    u = dot(S2,P);
    if ((u >= 0) || (caseECandidate)) // above s2
    {
      v = dot(N21,P);
//begin
      if (v > 0) // above N21
      {
        // here, we always have u >= 0 (check?)

        v = dot(N22,P);
        if (v >= 0) // above N22
        {
          // case H
          //printf("case H\n");
          *closestFeature = permutation[0]; // vertex 0
          #ifdef __VERSION_WITH_BARYCENTRIC_COORDS_JNB_CMU__
            // *alpha = 1; *beta = 0; *gamma = 0;
            *(barycentricCoords[0]) = 1; *(barycentricCoords[1]) = 0; *(barycentricCoords[2]) = 0;
          #endif
          return (d + v*v + u*u);
        }
        else // between N21 and N22
        {
          // case I
          //printf("case I\n");
          *closestFeature = permutation[5]; // edge 20
          #ifdef __VERSION_WITH_BARYCENTRIC_COORDS_JNB_CMU__
            // *beta = 0;
            // *gamma = -v / sidec;
            // *alpha = 1-*gamma; 
            *(barycentricCoords[1]) = 0; 
            *(barycentricCoords[2]) = -v / sidec;
            *(barycentricCoords[0]) = 1- *(barycentricCoords[2]);
          #endif
          return (d + u*u);
        }
      }
      else
      {
        // below N21

        // case G
        //printf("case G\n");
        *closestFeature = permutation[2]; // vertex 2
        #ifdef __VERSION_WITH_BARYCENTRIC_COORDS_JNB_CMU__
          //*alpha = 0; *beta = 0; *gamma = 1;
          *(barycentricCoords[0]) = 0; *(barycentricCoords[1]) = 0; *(barycentricCoords[2]) = 1;
        #endif
        return (d + v*v + u*u);
      }
//end


/*
// old begin
      if ((v <= 0) || (caseECandidate) )// below N21
      {
        // case G
        //printf("case G\n");
        *closestFeature = permutation[2]; // vertex 2
        // *alpha = 0; *beta = 0; *gamma = 1;
        *(barycentricCoords[0]) = 0; *(barycentricCoords[1]) = 0; *(barycentricCoords[2]) = 1;
        return (d + v*v + u*u);
      }
      else
      {
        // not caseECandidate or else would have exited already
    
        v = dot(N22,P);
        if (v >= 0) // above N22
        {
          // case H
          printf("case H\n");
          *closestFeature = permutation[0]; // vertex 0
          // *alpha = 1; *beta = 0; *gamma = 0;
          *(barycentricCoords[0]) = 1; *(barycentricCoords[1]) = 0; *(barycentricCoords[2]) = 0;
          return (d + v*v + u*u);
        }
        else // between N21 and N22
        {
          // case I
          printf("case I\n");
          // *beta = 0;
          // *gamma = -v / sidec;
          // *alpha = 1-*gamma; 
          *(barycentricCoords[1]) = 0; 
          *(barycentricCoords[2]) = -v / sidec;
          *(barycentricCoords[0]) = 1- *(barycentricCoords[2]);
          *closestFeature = permutation[5]; // edge 20
          return (d + u*u);
        }
      }
// old end
*/
    }

    // case J
    //printf("case J\n");
    *closestFeature = 6; // the face itself
    #ifdef __VERSION_WITH_BARYCENTRIC_COORDS_JNB_CMU__
      // *gamma = 0.5 * y * sidea / area;
      // *beta = - 0.5 * u * sidec / area;
      // *alpha = 1 - *beta - *gamma;
      *(barycentricCoords[2]) = 0.5 * y * sidea / area;
      *(barycentricCoords[1]) = - 0.5 * u * sidec / area;
      *(barycentricCoords[0]) = 1 - *(barycentricCoords[1]) - *(barycentricCoords[2]);
    #endif
    return d; // inside the triangle
  }

}
