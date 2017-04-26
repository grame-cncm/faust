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

#include "triangleTetIntersection.h"

bool TriangleTetIntersection::tetrahedronIntersectTriangle(const Vec3d & v1, const Vec3d & v2, const Vec3d & v3, const Vec3d & v4, const Vec3d & t1, const Vec3d & t2, const Vec3d & t3)
{
  Tetrahedron tet(v1, v2, v3, v4);

  // If any vertex of a triangle is in the tetrahedron, intersect.
  if (tet.contains(t1) || tet.contains(t2) || tet.contains(t3))
    return true;
  Triangle triangle(t1, t2, t3);

  // If any edge of a tetrahedron intersects the triangle, intersect
  bool intersect = triangle.intersect(v2, v1) || triangle.intersect(v1, v3) || triangle.intersect(v1, v4) || triangle.intersect(v2, v3) || triangle.intersect(v2, v4) || triangle.intersect(v3, v4);
  if (intersect)
    return true;

  // If any edge of a triangle intersects any face of the tetrahedron, intersect
  Triangle triangle1(v1, v2, v3), triangle2(v1, v2, v4), triangle3(v1, v3, v4), triangle4(v2, v3, v4);
  if (triangle1.intersect(t1, t2) || triangle1.intersect(t1, t3) || triangle1.intersect(t2, t3))
    return true;
  if (triangle2.intersect(t1, t2) || triangle2.intersect(t1, t3) || triangle2.intersect(t2, t3))
    return true;
  if (triangle3.intersect(t1, t2) || triangle3.intersect(t1, t3) || triangle3.intersect(t2, t3))
    return true;
  if (triangle4.intersect(t1, t2) || triangle4.intersect(t1, t3) || triangle4.intersect(t2, t3))
    return true;
  return false;
}

TriangleTetIntersection::Tetrahedron::Tetrahedron(const Vec3d & v0_, const Vec3d & v1_, const Vec3d & v2_, const Vec3d & v3_)
    : v0(v0_), v1(v1_), v2(v2_), v3(v3_)
{
  static const Vec3d ZERO = Vec3d(0, 0, 0);
  n0 = cross(v2 - v1, v3 - v1);
  d0 = dot(n0, v1);
  n1 = cross(v2 - v0, v3 - v0);
  d1 = dot(n1, v0);
  n2 = cross(v1 - v0, v3 - v0);
  d2 = dot(n2, v0);
  n3 = cross(v2 - v0, v1 - v0);
  d3 = dot(n3, v0);
  if (dot(n0, v0) < d0)
  {
    n0 = ZERO - n0;
    d0 = -d0;
  }
  if (dot(n1, v1) < d1)
  {
    n1 = ZERO - n1;
    d1 = -d1;
  }
  if (dot(n2, v2) < d2)
  {
    n2 = ZERO - n2;
    d2 = -d2;
  }
  if (dot(n3, v3) < d3)
  {
    n3 = ZERO - n3;
    d3 = -d3;
  }
}

bool TriangleTetIntersection::Tetrahedron::contains(const Vec3d & p)
{
//  cout << dot(p, n0) << " " << dot(p, n1) << " " << dot(p, n2) << " " << dot(p, n3) << "\n";
  bool ret = dot(p, n0) > d0 + 1e-10 && dot(p, n1) > d1 + 1e-10 && dot(p, n2) > d2 + 1e-10 && dot(p, n3) > d3 + 1e-10;
  //printf("%d\n", ret);
  return ret;
}

TriangleTetIntersection::Triangle::Triangle(const Vec3d & v0_, const Vec3d & v1_, const Vec3d & v2_)
    : v0(v0_), v1(v1_), v2(v2_)
{
  base1 = v1 - v0;
  base2 = v2 - v0;
  n = cross(base1, base2);
  n.normalize();
  d = dot(n, v0);
}

bool TriangleTetIntersection::Triangle::contains(const Vec3d & p)
{
  double d0 = (base1[1] * base2[2] - base1[2] * base2[1]);
  double d1 = (base1[0] * base2[2] - base1[2] * base2[0]);
  double d2 = (base1[0] * base2[1] - base1[1] * base2[0]);
  Vec3d v = p - v0;
  double t1, t2;
  if (fabs(d2) > fabs(d1) && fabs(d2) > fabs(d0))
  {
    t1 = (v[0] * base2[1] - v[1] * base2[0]) / d2;
    t2 = (v[1] * base1[0] - v[0] * base1[1]) / d2;
  }
  else if (fabs(d1) > fabs(d0))
  {
    t1 = (v[0] * base2[2] - v[2] * base2[0]) / d1;
    t2 = (v[2] * base1[0] - v[0] * base1[2]) / d1;
  }
  else
  {
    t1 = (v[1] * base2[2] - v[2] * base2[1]) / d0;
    t2 = (v[2] * base1[1] - v[1] * base1[2]) / d0;
  }
  return t1 >= 1e-10 && t2 >= 1e-10 && t1 + t2 <= 1 - 1e-10;
}

bool TriangleTetIntersection::Triangle::intersect(const Vec3d & l0, const Vec3d & l1)
{
  double t = (d - dot(n, l0)) / dot(n, l1 - l0);
  if (!(t > 1e-10 && t < 1 - 1e-10))
    return false;
  return contains(l0 * (1 - t) + l1 * t);
}

