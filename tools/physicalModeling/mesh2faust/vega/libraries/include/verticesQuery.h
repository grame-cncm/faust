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


#ifndef VERTICESQUERY_H
#define VERTICESQUERY_H

// handles floating-point queries among vertices
#include <vector>
#include "minivector.h"
#include "query.h"

class VerticesQuery : public Query 
{
public:

  VerticesQuery (int numVertices, const Vec3d * vertices);
  virtual ~VerticesQuery ();

  // Run-time type information.
  virtual Type getType () const { return DOUBLE; }

  // Member access.
  inline size_t getNumVertices () const { return vertices.size(); }
  inline const Vec3d * getVertices () const { return vertices.data(); }

  virtual void addVertex(const Vec3d & v);

  // Queries about the relation of a point to various geometric objects.

  // Returns:
  //   +1, on positive side of plane
  //   -1, on negative side of plane
  //    0, on the plane
  // normal direction of plane: cross(v1-v0, v2-v0)
  virtual int toPlane (int i, int v0, int v1, int v2) const;
  virtual int toPlane (const Vec3d& test, int v0, int v1, int v2) const;

  // Returns:
  //   +1, outside tetrahedron
  //   -1, inside tetrahedron
  //    0, on tetrahedron
  virtual int toTetrahedron (int i, int v0, int v1, int v2, int v3) const;
  virtual int toTetrahedron (const Vec3d & test, int v0, int v1, int v2, int v3) const;

  // Returns:
  //   +1, outside circumsphere of tetrahedron
  //   -1, inside circumsphere of tetrahedron
  //    0, on circumsphere of tetrahedron
  virtual int toCircumsphere (int i, int v0, int v1, int v2, int v3) const;
  virtual int toCircumsphere (const Vec3d & test, int v0, int v1, int v2, int v3) const;

  // Returns:
  //   +1, outside circumsphere of triangle
  //   -1, inside circumsphere of triangle
  //    0, on circumsphere of triangle
  virtual int toCircumsphere (int i, int v0, int v1, int v2) const;
  virtual int toCircumsphere (const Vec3d & test, int v0, int v1, int v2) const;

  struct Information 
  {
    // The intrinsic dimension of the input set. The parameter 'epsilon'
    // to the VerticesQuery::getInformation function is used to provide a tolerance when
    // determining the dimension.
    // if dimension == 0, all points are effectively the same (or very close based on epsilon)
    // If dimension == 1, all points effectively lie on a line segment.
    // If dimension == 2, all points effectively line on a plane.
    // If dimension == 3, the points are not coplanar.
    int dimension;

    // Axis-aligned bounding box of the input set.
    double min[3], max[3];
    // mMaxRange = max(max[0]-min[0], max[1]-min[1], and max[2]-min[2].)
    double maxRange;

    // The indices that define the maximum dimensional extents.  The
    // values mExtreme[0] and mExtreme[1] are the indices for the points
    // that define the largest extent in one of the coordinate axis
    // directions.
    // If the dimension is 2, then mExtreme[2] is the index
    // for the point that generates the largest extent in the direction
    // perpendicular to the line through the points corresponding to
    // mExtreme[0] and mExtreme[1].
    // Furthermore, if the dimension is 3, then mExtreme[3] is the index
    // for the point that generates the largest extent in the direction
    // perpendicular to the triangle defined by the other extreme points.
    int extreme[4];
    // If dimenstion == 3, the tetrahedron formed by the
    // points V[extreme0], V[extreme1], V[extreme2], V[extreme3]> is
    // counterclockwise (positive) if extremeCCW == true.
    // tet is positive if its vertices satisfy:  ((v1 - v0) x (v2 - v0)) dot (v3 - v0) >= 0
    bool extremeCCW;

    // Coordinate system.
    // The origin == vertices[exterme[0].  The
    // unit-length direction vector is valid only for 0 <= i < d.
    Vec3d origin;
    Vec3d direction[3];
  };

  // get dimensional information about the vertices
  void getInformation(double epsilon, Information & info);

  // Helper functions.
  static double dot (double x0, double y0, double z0, double x1, double y1, double z1);

  static double det3 (double x0, double y0, double z0, double x1, double y1, double z1,
      double x2, double y2, double z2);

  static double det4 (double x0, double y0, double z0, double w0, double x1, double y1,
      double z1, double w1, double x2, double y2, double z2, double w2, double x3,
      double y3, double z3, double w3);

  // Support for ordering a set of unique indices into the vertex pool.  On
  // output it is guaranteed that:  v0 < v1 < v2.  This is used to guarantee
  // consistent queries when the vertex ordering of a primitive is permuted,
  // a necessity when using floating-point arithmetic that suffers from
  // numerical round-off errors.  The input indices are considered the
  // positive ordering.  The output indices are either positively ordered
  // (an even number of transpositions occurs during sorting) or negatively
  // ordered (an odd number of transpositions occurs during sorting).  The
  // functions return 'true' for a positive ordering and 'false' for a
  // negative ordering.
  static bool sort (int& v0, int& v1);
  static bool sort (int& v0, int& v1, int& v2);
  static bool sort (int& v0, int& v1, int& v2, int& v3);

protected:
  // Input points.
  std::vector<Vec3d> vertices;
};

#endif
