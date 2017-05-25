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

#include "verticesQueryRational.h"
#include <cstring>
using namespace std;

const double ep = 0;
VerticesQueryRational::VerticesQueryRational (int numVertices,
    const Vec3d * v) : VerticesQuery(numVertices, v)
{
  rVertices.resize(vertices.size());
  evaluated.resize(vertices.size(), 0);
//  memset(&mEvaluated[0], 0, mNumVertices * sizeof(bool));
}
//----------------------------------------------------------------------------

VerticesQueryRational::~VerticesQueryRational ()
{
}
//----------------------------------------------------------------------------

void VerticesQueryRational::addVertex(const Vec3d & v) 
{
  VerticesQuery::addVertex(v);
  rVertices.push_back(QRVector());
  evaluated.push_back(0);
}

int VerticesQueryRational::toPlane (int i, int v0, int v1, int v2) const
{
  int indices[4] = { i, v0, v1, v2 };
  convert(4, indices);
  return toPlane(rVertices[i], v0, v1, v2);
}
//----------------------------------------------------------------------------

int VerticesQueryRational::toPlane (const Vec3d& test, int v0, int v1,
    int v2) const
{
  QRVector ratTest;
  ratTest[0] = QRational(test[0]);
  ratTest[1] = QRational(test[1]);
  ratTest[2] = QRational(test[2]);
  int indices[3] = { v0, v1, v2 };
  convert(3, indices);
  return toPlane(ratTest, v0, v1, v2);
}
//----------------------------------------------------------------------------

int VerticesQueryRational::toTetrahedron (int i, int v0, int v1, int v2,
    int v3) const
{
  int indices[5] = { i, v0, v1, v2, v3 };
  convert(5, indices);
  return toTetrahedron(rVertices[i], v0, v1, v2, v3);
}
//----------------------------------------------------------------------------

int VerticesQueryRational::toTetrahedron (const Vec3d& test, int v0,
    int v1, int v2, int v3) const
{
  QRVector ratTest;
  ratTest[0] = QRational(test[0]);
  ratTest[1] = QRational(test[1]);
  ratTest[2] = QRational(test[2]);
  int indices[4] = { v0, v1, v2, v3 };
  convert(4, indices);
  return toTetrahedron(ratTest, v0, v1, v2, v3);
}
//----------------------------------------------------------------------------

int VerticesQueryRational::toCircumsphere (int i, int v0, int v1, int v2,
    int v3) const
{
  int indices[5] = { i, v0, v1, v2, v3 };
  convert(5, indices);
  return toCircumsphere(rVertices[i], v0, v1, v2, v3);
}
//----------------------------------------------------------------------------

int VerticesQueryRational::toCircumsphere (const Vec3d& test, int v0,
    int v1, int v2, int v3) const
{
  QRVector ratTest;
  ratTest[0] = QRational(test[0]);
  ratTest[1] = QRational(test[1]);
  ratTest[2] = QRational(test[2]);
  int indices[4] = { v0, v1, v2, v3 };
  convert(4, indices);
  return toCircumsphere(ratTest, v0, v1, v2, v3);
}
//----------------------------------------------------------------------------

void VerticesQueryRational::convert (int numIndices, int* indices) const
{
  for(int i = 0; i < numIndices; ++i)
  {
    int j = indices[i];
    if (!evaluated[j])
    {
      evaluated[j] = true;
      rVertices[j][0] = QRational(vertices[j][0]);
      rVertices[j][1] = QRational(vertices[j][1]);
      rVertices[j][2] = QRational(vertices[j][2]);
    }
  }
}
//----------------------------------------------------------------------------

int VerticesQueryRational::toPlane (const QRVector& ratTest, int v0, int v1,
    int v2) const
{

//  QRVector ab = (rVertices[v1] - rVertices[v0]);
//  QRVector ac = (rVertices[v2] - rVertices[v0]);
//  QRVector ax = ratTest - rVertices[v0];
//
//  QRational dd = ax.tripleScalar(ab, ac);
//  return (dd > 0 ? +1 : (dd < 0 ? -1 : 0));
//
//  QRational x0 = ratTest[0] - rVertices[v0][0];
//  QRational y0 = ratTest[1] - rVertices[v0][1];
//  QRational z0 = ratTest[2] - rVertices[v0][2];
//  QRational x1 = rVertices[v1][0] - rVertices[v0][0];
//  QRational y1 = rVertices[v1][1] - rVertices[v0][1];
//  QRational z1 = rVertices[v1][2] - rVertices[v0][2];
//  QRational x2 = rVertices[v2][0] - rVertices[v0][0];
//  QRational y2 = rVertices[v2][1] - rVertices[v0][1];
//  QRational z2 = rVertices[v2][2] - rVertices[v0][2];

//  QRational det = det3(x0, y0, z0, x1, y1, z1, x2, y2, z2);
//  return (det > 0 ? +1 : (det < 0 ? -1 : 0));

  OTriKey key(v0,v1,v2);

  PlaneDataMapIter it = planeDataMap.find(key);
  if (it == planeDataMap.end()) 
  {
    PlaneData data;
    QRVector ab = (rVertices[v1] - rVertices[v0]);
    QRVector ac = (rVertices[v2] - rVertices[v0]);
    data.normal = ab.cross(ac);
    data.d = rVertices[v0].dot(data.normal);
    data.d = -data.d;
    planeDataMap[key] = data;
    QRational ret = ratTest.dot(data.normal) + data.d;
    double r = ret.toDouble();
    return (r > ep ? +1 : (r < -ep ? -1 : 0));
//
//    QRVector ab = (rVertices[v1] - rVertices[v0]);
//    QRVector ac = (rVertices[v2] - rVertices[v0]);
//    QRVector ax = ratTest - rVertices[v0];
//
//    QRational dd = ax.tripleScalar(ab, ac);
//    return (dd > 0 ? +1 : (dd < 0 ? -1 : 0));


  }
  else 
  {
    PlaneData & data = it->second;
    planeDataMap[key] = data;
    QRational ret = ratTest.dot(data.normal) + data.d;
    double r = ret.toDouble();
    return (r > ep ? +1 : (r < -ep ? -1 : 0));
  }

}
//----------------------------------------------------------------------------

int VerticesQueryRational::toTetrahedron (const QRVector& ratTest, int v0,
    int v1, int v2, int v3) const
{
  int sign0 = toPlane(ratTest, v1, v2, v3);
  if (sign0 > 0)
    return +1;

  int sign1 = toPlane(ratTest, v0, v2, v3);
  if (sign1 < 0)
    return +1;

  int sign2 = toPlane(ratTest, v0, v1, v3);
  if (sign2 > 0)
    return +1;

  int sign3 = toPlane(ratTest, v0, v1, v2);
  if (sign3 < 0)
    return +1;

  return ((sign0 && sign1 && sign2 && sign3) ? -1 : 0);
}
//----------------------------------------------------------------------------


int VerticesQueryRational::toCircumsphere (const QRVector& ratTest, int v0, int v1, int v2, int v3) const
{
  QRVector& ratVec0 = rVertices[v0];
  QRVector& ratVec1 = rVertices[v1];
  QRVector& ratVec2 = rVertices[v2];
  QRVector& ratVec3 = rVertices[v3];

  QRational s0x = ratVec0[0] + ratTest[0];
  QRational s0y = ratVec0[1] + ratTest[1];
  QRational s0z = ratVec0[2] + ratTest[2];

  QRational d0x = ratVec0[0] - ratTest[0];
  QRational d0y = ratVec0[1] - ratTest[1];
  QRational d0z = ratVec0[2] - ratTest[2];

  QRational s1x = ratVec1[0] + ratTest[0];
  QRational s1y = ratVec1[1] + ratTest[1];
  QRational s1z = ratVec1[2] + ratTest[2];

  QRational d1x = ratVec1[0] - ratTest[0];
  QRational d1y = ratVec1[1] - ratTest[1];
  QRational d1z = ratVec1[2] - ratTest[2];

  QRational s2x = ratVec2[0] + ratTest[0];
  QRational s2y = ratVec2[1] + ratTest[1];
  QRational s2z = ratVec2[2] + ratTest[2];

  QRational d2x = ratVec2[0] - ratTest[0];
  QRational d2y = ratVec2[1] - ratTest[1];
  QRational d2z = ratVec2[2] - ratTest[2];

  QRational s3x = ratVec3[0] + ratTest[0];
  QRational s3y = ratVec3[1] + ratTest[1];
  QRational s3z = ratVec3[2] + ratTest[2];

  QRational d3x = ratVec3[0] - ratTest[0];
  QRational d3y = ratVec3[1] - ratTest[1];
  QRational d3z = ratVec3[2] - ratTest[2];

  // wi = dot(si,di)
  QRational w0 = s0x*d0x + s0y*d0y + s0z*d0z;
  QRational w1 = s1x*d1x + s1y*d1y + s1z*d1z;
  QRational w2 = s2x*d2x + s2y*d2y + s2z*d2z;
  QRational w3 = s3x*d3x + s3y*d3y + s3z*d3z;
  QRational det = det4(d0x, d0y, d0z, w0, d1x, d1y, d1z, w1, d2x, d2y, d2z,
      w2, d3x, d3y, d3z, w3);
  return (det > ep ? 1 : (det < -ep ? -1 : 0));
}

int VerticesQueryRational::toCircumsphere (int i, int v0, int v1, int v2) const
{
  return toCircumsphere(vertices[i], v0, v1, v2);
}

static VerticesQueryRational::QRVector cross(const VerticesQueryRational::QRVector &r1, const VerticesQueryRational::QRVector &r2)
{
  return r1.cross(r2);
}

static VerticesQueryRational::QRational len2(const VerticesQueryRational::QRVector &r)
{
  return r.dot(r);
}

int VerticesQueryRational::toCircumsphere (const Vec3d& test, int v0, int v1, int v2) const
{
  QRVector ratTest;
  ratTest[0] = QRational(test[0]);
  ratTest[1] = QRational(test[1]);
  ratTest[2] = QRational(test[2]);
  int indices[3] = { v0, v1, v2};
  convert(3, indices);
  return toCircumsphere(ratTest, v0, v1, v2);
}

int VerticesQueryRational::toCircumsphere (const QRVector& test, int v0, int v1, int v2) const
{
  const QRVector & p0 = rVertices[v0];
  const QRVector & p1 = rVertices[v1];
  const QRVector & p2 = rVertices[v2];
  sort(v0,v1,v2);
  QRVector d0 = p1 - p0, d1 = p2 - p1, d2 = p0 - p2;
  QRVector S = cross(d0, d1);
  QRational S2 = len2(S);
  QRational d02 = len2(d0), d12 = len2(d1), d22 = len2(d2);
  QRVector center( (d12 * d0.dot(d2)) * p0 + (d22 * d0.dot(d1)) * p1 + (d02 * d2.dot(d1)) * p2 );
  center /= -(S2 * 2);
  QRational r2 = d02 * d12 * d22 / (S2 * 4);
  //assert(abs(len2(center - p0) - r2) < 1e-6);
  //assert(abs(len2(center - p1) - r2) < 1e-6);
  //assert(abs(len2(center - p2) - r2) < 1e-6);

  QRational dist2 =  len2(test - center);
  return dist2 > r2 + ep ? +1 : (dist2 < r2 - ep ? -1 : 0);
}

//----------------------------------------------------------------------------

VerticesQueryRational::QRational VerticesQueryRational::dot (
    QRational& x0, QRational& y0, QRational& z0, QRational& x1,
    QRational& y1, QRational& z1)
{
  return x0*x1 + y0*y1 + z0*z1;
}
//----------------------------------------------------------------------------

VerticesQueryRational::QRational VerticesQueryRational::det3 (
    QRational& x0, QRational& y0, QRational& z0, QRational& x1,
    QRational& y1, QRational& z1, QRational& x2, QRational& y2,
    QRational& z2)
{
  QRational c00 = y1*z2 - y2*z1;
  QRational c01 = y2*z0 - y0*z2;
  QRational c02 = y0*z1 - y1*z0;
  return x0*c00 + x1*c01 + x2*c02;
}
//----------------------------------------------------------------------------

VerticesQueryRational::QRational VerticesQueryRational::det4 (
    QRational& x0, QRational& y0, QRational& z0, QRational& w0,
    QRational& x1, QRational& y1, QRational& z1, QRational& w1,
    QRational& x2, QRational& y2, QRational& z2, QRational& w2,
    QRational& x3, QRational& y3, QRational& z3, QRational& w3)
{
  QRational a0 = x0*y1 - x1*y0;
  QRational a1 = x0*y2 - x2*y0;
  QRational a2 = x0*y3 - x3*y0;
  QRational a3 = x1*y2 - x2*y1;
  QRational a4 = x1*y3 - x3*y1;
  QRational a5 = x2*y3 - x3*y2;
  QRational b0 = z0*w1 - z1*w0;
  QRational b1 = z0*w2 - z2*w0;
  QRational b2 = z0*w3 - z3*w0;
  QRational b3 = z1*w2 - z2*w1;
  QRational b4 = z1*w3 - z3*w1;
  QRational b5 = z2*w3 - z3*w2;
  return a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
}
