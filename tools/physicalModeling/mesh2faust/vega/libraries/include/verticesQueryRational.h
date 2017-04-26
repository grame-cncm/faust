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


#ifndef VERTICESQUERYRATIONAL_H
#define VERTICESQUERYRATIONAL_H

#include "rational.h"
#include "rVector.h"
#include "verticesQuery.h"
#include "tetKey.h"
#include <map>

class VerticesQueryRational : public VerticesQuery 
{
public:
  // The components of the input vertices are represented exactly as
  // rational values.
  VerticesQueryRational (int numVertices, const Vec3d * vertices);
  virtual ~VerticesQueryRational ();

  // run-time type information
  virtual Type getType () const { return RATIONAL; }

  virtual void addVertex(const Vec3d & v);

  // Queries about the relation of a point to various geometric objects.

  virtual int toPlane (int i, int v0, int v1, int v2) const;
  virtual int toPlane (const Vec3d& test, int v0, int v1, int v2) const;

  virtual int toTetrahedron (int i, int v0, int v1, int v2, int v3) const;
  virtual int toTetrahedron (const Vec3d& test, int v0, int v1,
      int v2, int v3) const;

  virtual int toCircumsphere (int i, int v0, int v1, int v2, int v3) const;
  virtual int toCircumsphere (const Vec3d& test, int v0, int v1, int v2, int v3) const;

  virtual int toCircumsphere (int i, int v0, int v1, int v2) const;
  virtual int toCircumsphere (const Vec3d& test, int v0, int v1, int v2) const;

  // Helper functions.
  typedef Rational<8*sizeof(double)> QRational;
  typedef RVector3<8*sizeof(double)> QRVector;

  static QRational dot (QRational& x0, QRational& y0, QRational& z0,
      QRational& x1, QRational& y1, QRational& z1);

  static QRational det3 (QRational& x0, QRational& y0, QRational& z0,
      QRational& x1, QRational& y1, QRational& z1, QRational& x2,
      QRational& y2, QRational& z2);

  static QRational det4 (QRational& x0, QRational& y0, QRational& z0,
      QRational& w0, QRational& x1, QRational& y1, QRational& z1,
      QRational& w1, QRational& x2, QRational& y2, QRational& z2,
      QRational& w2, QRational& x3, QRational& y3, QRational& z3,
      QRational& w3);

protected:

  void convert (int numIndices, int* indices) const;
  int toPlane (const QRVector& ratTest, int v0, int v1, int v2) const;
  int toTetrahedron (const QRVector& ratTest, int v0, int v1, int v2,
      int v3) const;
  int toCircumsphere (const QRVector& ratTest, int v0, int v1, int v2,
      int v3) const;

  int toCircumsphere (const QRVector& test, int v0, int v1, int v2) const;

  // Caching for rational representations of the input.  The conversion of
  // floating-point numbers to Rational form is slow, so it is better to
  // keep track of which values have been converted.
  mutable std::vector<QRVector> rVertices;
  mutable std::vector<bool> evaluated;

  // ToPlane(x,a,b,c) > 0 <=> dot ( (x-a), cross(b-a, c-a) ) > 0
  // This struct stores: normal = cross(b-a, c-a), d = - dot(a, cross(b-a, c-a) )
  struct PlaneData 
  {
    QRVector normal;
    QRational d;
  };

  mutable std::map<OTriKey, PlaneData> planeDataMap;
  typedef std::map<OTriKey, PlaneData> PlaneDataMap;
  typedef std::map<OTriKey, PlaneData>::iterator PlaneDataMapIter;

  struct CircumsphereData 
  {
    QRVector center;
    QRational r2;
  };
  mutable std::map<OTetKey, CircumsphereData> circumsphereDataMap;
  typedef std::map<OTetKey, CircumsphereData> CircumsphereDataMap;
  typedef std::map<OTetKey, CircumsphereData>::iterator CircumsphereDataMapIter;
};

#endif
