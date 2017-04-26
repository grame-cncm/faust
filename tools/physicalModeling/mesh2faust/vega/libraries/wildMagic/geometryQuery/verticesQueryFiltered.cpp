/*
  This code is based on code from the Geometric Tools library,
  which is licensed under a boost license.
  Such usage is permitted by the boost license; for details, 
  please see the boost license below.
*/

// Geometric Tools, LLC
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt

/*************************************************************************
 *                                                                       *
 * We release our improvements to the wildMagic code under our standard  *
 * Vega FEM license, as follows:                                         *
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "improvements to the wildMagic library" , Copyright (C) 2016 USC      *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Yijing Li                                                *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Funding: National Science Foundation                                  *
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

#include "verticesQueryFiltered.h"

VerticesQueryFiltered::VerticesQueryFiltered(int n, const Vec3d * vertices, double uc) :
  VerticesQuery(n, vertices),uncertainty(uc), rational(n, vertices)
{
}

VerticesQueryFiltered::~VerticesQueryFiltered() {}

void VerticesQueryFiltered::addVertex(const Vec3d & v) 
{
  VerticesQuery::addVertex(v);
  rational.addVertex(v);
}

int VerticesQueryFiltered::toPlane(const Vec3d & test, int v0, int v1, int v2) const 
{
  const Vec3d & vec0 = vertices[v0];
  const Vec3d & vec1 = vertices[v1];
  const Vec3d & vec2 = vertices[v2];

  double x0 = test[0] - vec0[0];
  double y0 = test[1] - vec0[1];
  double z0 = test[2] - vec0[2];
  double x1 = vec1[0] - vec0[0];
  double y1 = vec1[1] - vec0[1];
  double z1 = vec1[2] - vec0[2];
  double x2 = vec2[0] - vec0[0];
  double y2 = vec2[1] - vec0[1];
  double z2 = vec2[2] - vec0[2];

  double len0 = sqrt(x0*x0 + y0*y0 + z0*z0);
  double len1 = sqrt(x1*x1 + y1*y1 + z1*z1);
  double len2 = sqrt(x2*x2 + y2*y2 + z2*z2);
  double scaledUncertainty = uncertainty*len0*len1*len2;

  double det = det3(x0, y0, z0, x1, y1, z1, x2, y2, z2);
  if (fabs(det) >= scaledUncertainty)
  {
    return (det > (double)0 ? +1 : (det < (double)0 ? -1 : 0));
  }
  return rational.toPlane(test, v0, v1, v2);
}

int VerticesQueryFiltered::toCircumsphere (const Vec3d & test, int v0, int v1, int v2, int v3) const 
{
  const Vec3d & vec0 = vertices[v0];
  const Vec3d & vec1 = vertices[v1];
  const Vec3d & vec2 = vertices[v2];
  const Vec3d & vec3 = vertices[v3];

  double s0x = vec0[0] + test[0];
  double d0x = vec0[0] - test[0];
  double s0y = vec0[1] + test[1];
  double d0y = vec0[1] - test[1];
  double s0z = vec0[2] + test[2];
  double d0z = vec0[2] - test[2];
  double s1x = vec1[0] + test[0];
  double d1x = vec1[0] - test[0];
  double s1y = vec1[1] + test[1];
  double d1y = vec1[1] - test[1];
  double s1z = vec1[2] + test[2];
  double d1z = vec1[2] - test[2];
  double s2x = vec2[0] + test[0];
  double d2x = vec2[0] - test[0];
  double s2y = vec2[1] + test[1];
  double d2y = vec2[1] - test[1];
  double s2z = vec2[2] + test[2];
  double d2z = vec2[2] - test[2];
  double s3x = vec3[0] + test[0];
  double d3x = vec3[0] - test[0];
  double s3y = vec3[1] + test[1];
  double d3y = vec3[1] - test[1];
  double s3z = vec3[2] + test[2];
  double d3z = vec3[2] - test[2];
  double w0 = s0x*d0x + s0y*d0y + s0z*d0z;
  double w1 = s1x*d1x + s1y*d1y + s1z*d1z;
  double w2 = s2x*d2x + s2y*d2y + s2z*d2z;
  double w3 = s3x*d3x + s3y*d3y + s3z*d3z;

  double len0 = sqrt(d0x*d0x+d0y*d0y+d0z*d0z+w0*w0);
  double len1 = sqrt(d1x*d1x+d1y*d1y+d1z*d1z+w1*w1);
  double len2 = sqrt(d2x*d2x+d2y*d2y+d2z*d2z+w2*w2);
  double len3 = sqrt(d3x*d3x+d3y*d3y+d3z*d3z+w3*w3);
  double scaledUncertainty = uncertainty*len0*len1*len2*len3;

  double det = det4(d0x, d0y, d0z, w0, d1x, d1y, d1z, w1, d2x, d2y, d2z,
      w2, d3x, d3y, d3z, w3);

  if (fabs(det) >= scaledUncertainty)
  {
    return (det > (double)0 ? 1 : (det < (double)0 ? -1 : 0));
  }

  return rational.toCircumsphere(test, v0, v1, v2, v3);
}

int VerticesQueryFiltered::toCircumsphere (const Vec3d & test, int v0, int v1, int v2) const 
{
  const Vec3d & p0 = vertices[v0];
  const Vec3d & p1 = vertices[v1];
  const Vec3d & p2 = vertices[v2];
  sort(v0,v1,v2);
  Vec3d d0 = p1 - p0, d1 = p2 - p1, d2 = p0 - p2;
  Vec3d S = cross(d0, d1);
  double S2 = len2(S);
  double d02 = len2(d0), d12 = len2(d1), d22 = len2(d2);
  Vec3d center( (d12 * ::dot(d0,d2)) * p0 + (d22 * ::dot(d0,d1)) * p1 + (d02 * ::dot(d2,d1)) * p2 );
  center /= -(2 * S2);
  double r2 = d02 * d12 * d22 / (4*S2);
  //assert(abs(len2(center - p0) - r2) < 1e-6);
  //assert(abs(len2(center - p1) - r2) < 1e-6);
  //assert(abs(len2(center - p2) - r2) < 1e-6);

  double dist2 =  len2(test - center);
  double scaledUncertainty = uncertainty*d02*d12*d22;
  if (fabs(dist2 - r2) > scaledUncertainty)
    return dist2 > r2 ? +1 : (dist2 < r2 ? -1 : 0);
  return rational.toCircumsphere(test, v0, v1, v2);
}
