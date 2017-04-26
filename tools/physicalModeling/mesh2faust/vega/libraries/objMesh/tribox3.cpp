/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "objMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC        *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Somya Sharma, Jernej Barbic                             *
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

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include "matrixMultiplyMacros.h"
using namespace std;

/*
  Tests if a 3D triangle overlaps with a 3D box.

  INPUT: center of box, box half sizes (in each of the three dimensions), and the three triangle vertices v0, v1, v2.
  OUTPUT: whether triangle intersects the box or not
  Note: all entries in boxHalfSize must be >= 0.
  Note: lower-left-front corner is boxCenter - boxHalfSize, upper-right-back corner is boxCenter + boxHalfSize.
*/

bool triBoxOverlap(const double boxcenter[3], const double boxhalfsize[3], const double trivert0[3], const double trivert1[3], const double trivert2[3])
{
  // translate so that box's center coincides with the origin
  double triverts[3][3];
  VECTOR_SUBTRACT3(trivert0, boxcenter, triverts[0]);
  VECTOR_SUBTRACT3(trivert1, boxcenter, triverts[1]);
  VECTOR_SUBTRACT3(trivert2, boxcenter, triverts[2]);

  // test AABB against minimal AABB around the triangle
  // 3 tests

  double minx = min( min(triverts[0][0], triverts[1][0]), triverts[2][0] );
  double miny = min( min(triverts[0][1], triverts[1][1]), triverts[2][1] );
  double minz = min( min(triverts[0][2], triverts[1][2]), triverts[2][2] );
  double maxx = max( max(triverts[0][0], triverts[1][0]), triverts[2][0] );
  double maxy = max( max(triverts[0][1], triverts[1][1]), triverts[2][1] );
  double maxz = max( max(triverts[0][2], triverts[1][2]), triverts[2][2] );
  
  if ( ( boxhalfsize[0] < minx ) || ( maxx < -boxhalfsize[0] ) || ( boxhalfsize[1] < miny ) || ( maxy < -boxhalfsize[1] ) || ( boxhalfsize[2] < minz ) || ( maxz < -boxhalfsize[2] ) )
    return false; //no overlap

  // normals of AABB at origin

  double e0[3] = { 1, 0, 0 };
  double e1[3] = { 0, 1, 0 };
  double e2[3] = { 0, 0, 1 };

  double f0[3];
  double f1[3];
  double f2[3];

  VECTOR_SUBTRACT3(triverts[1], triverts[0], f0);
  VECTOR_SUBTRACT3(triverts[2], triverts[1], f1);
  VECTOR_SUBTRACT3(triverts[0], triverts[2], f2);
 
  double * e[3] = { e0, e1, e2 };
  double * f[3] = { f0, f1, f2 };

  // aij = ej X fj
  // 9 tests
  double a[3];
  double p0, p1, p2;
  double radius;
  #define LOOP1(i,j)\
    {\
      VECTOR_CROSS_PRODUCT(e[i], f[j], a);\
      p0 = VECTOR_DOT_PRODUCT3(a, triverts[0]);\
      p1 = VECTOR_DOT_PRODUCT3(a, triverts[1]);\
      p2 = VECTOR_DOT_PRODUCT3(a, triverts[2]);\
      radius = ( boxhalfsize[0] * fabs(a[0]) ) + ( boxhalfsize[1] * fabs(a[1]) ) + ( boxhalfsize[2] * fabs(a[2]) );\
      if ( (min( min(p0, p1), p2 ) > radius) || (max( max(p0, p1), p2 ) < -radius ) )\
        return false;\
    }

  LOOP1(0, 0);
  LOOP1(0, 1);
  LOOP1(0, 2);
  LOOP1(1, 0);
  LOOP1(1, 1);
  LOOP1(1, 2);
  LOOP1(2, 0);
  LOOP1(2, 1);
  LOOP1(2, 2);
  #undef LOOP1

/*
  // aij = ej X fj
  // 9 tests
  for ( int i = 0; i <= 2; i ++ )
  {
    for ( int j = 0; j <= 2; j ++ )
    {
      double a[3];
      VECTOR_CROSS_PRODUCT(e[i], f[j], a);
      double p0 = VECTOR_DOT_PRODUCT3(a, triverts[0]);
      double p1 = VECTOR_DOT_PRODUCT3(a, triverts[1]);
      double p2 = VECTOR_DOT_PRODUCT3(a, triverts[2]);

      double radius = ( boxhalfsize[0] * fabs(a[0]) ) + ( boxhalfsize[1] * fabs(a[1]) ) + ( boxhalfsize[2] * fabs(a[2]) );

      if ( (min( min(p0, p1), p2 ) > radius) || (max( max(p0, p1), p2 ) < -radius ) )
      {
        overlap = false;
        return overlap;
      }
    }
  }
*/
  
  // plane and AABB overlap test
  // 1 test

  // triangle normal
  double normal[3];
  VECTOR_CROSS_PRODUCT(f0, f1, normal);
  // no need to normalize the normal as we only check the sign of expressions in the calculations that depend on normal
  // this also makes the code robust against degenerate triangles with zero-length normals
  //double len2 = normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2];
  //double invlen = 1.0 / sqrt(len2);
  //normal[0] *= invlen;
  //normal[1] *= invlen;
  //normal[2] *= invlen;

  // distance of plane from the origin
  double planeDist = -VECTOR_DOT_PRODUCT3(normal, triverts[0]);

  // get nearest and farthest corners
  double nearestPoint[3];
  double farthestPoint[3];

  #define LOOP2(i)\
    if ( normal[i] < 0 )\
    {\
      nearestPoint[i] = boxhalfsize[i];\
      farthestPoint[i] = - boxhalfsize[i];\
    }\
    else\
    {\
      nearestPoint[i] = - boxhalfsize[i];\
      farthestPoint[i] = boxhalfsize[i];\
    }\

  LOOP2(0);
  LOOP2(1);
  LOOP2(2);
  #undef LOOP2

/*
  for ( int i = 0; i <= 2; i++ )
  {
    if ( n[i] < 0 )
    {
      nearestPoint[i] = boxhalfsize[i];
      farthestPoint[i] = - boxhalfsize[i];
    }
    else
    {
      nearestPoint[i] = - boxhalfsize[i];
      farthestPoint[i] = boxhalfsize[i];
    }
  }
*/
  
  if ( VECTOR_DOT_PRODUCT3(normal, nearestPoint) + planeDist > 0 )
    return false; // no overlap
  
  bool overlap = ( VECTOR_DOT_PRODUCT3(normal, farthestPoint) + planeDist >= 0 );
  return overlap;
}

