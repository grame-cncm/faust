/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "mesher" library , Copyright (C) 2016 USC                             *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Danyong Zhao, Yijing Li, Jernej Barbic                  *
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

/*
  Intersection between a tet and a triangle.
*/

#ifndef _TRIANGLETETINTERSECTION_H_
#define _TRIANGLETETINTERSECTION_H_

#include "vec3d.h"

// This class computes whether a tetrahedron intersects a triangle, excluding just touching.
class TriangleTetIntersection
{
public:

  // does the tetrahedron intersects the triangle, excluding just touching
  static bool tetrahedronIntersectTriangle(const Vec3d & tet1, const Vec3d & tet2, const Vec3d & tet3, const Vec3d & tet4, const Vec3d & t1, const Vec3d & t2, const Vec3d & t3);

protected:
  class Tetrahedron
  {
  protected:
    // The positions of the four vertices
    const Vec3d v0, v1, v2, v3;

    // The normals of the four faces
    Vec3d n0, n1, n2, n3;
    // The positions of the four faces
    double d0, d1, d2, d3;
  public:
    Tetrahedron(const Vec3d & v0, const Vec3d & v1, const Vec3d & v2, const Vec3d & v3);
    // Whether a point is inside the tetrahedron, excluding on the tetrahedron
    bool contains(const Vec3d & p);
  };

  class Triangle 
  {
  protected:
    // The positions of the three vertices
    const Vec3d v0, v1, v2;
    // The normal
    Vec3d n;
    // The position of the face
    double d;
    // The two base vectors of the face
    Vec3d base1, base2;
  public:
    Triangle(const Vec3d & v0, const Vec3d & v1, const Vec3d & v2);
    // Whether a point is inside the triangle, excluding on the triangle
    bool contains(const Vec3d & p);
    // Whether the segment starting from l0 and ending at l1 intersects the triangle, excluding just touching
    bool intersect(const Vec3d & l0, const Vec3d & l1);
  };

  //compute the determinant of a 3x3 matrix defined by three vectors whose dimensions are all three
  static inline double det(const Vec3d & a, const Vec3d & b, const Vec3d & c) { return dot(a, cross(b, c)); }

private:
  TriangleTetIntersection();
};

#endif /* INTERSECTION_H_ */

