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

//  Bounding Box
//  Author: Jernej Barbic, CMU

#include "openGL-headers.h"
#include <float.h>
#include <vector>
#include <iostream>
using namespace std;

#include "boundingBox.h"
#include "triangle.h"


BoundingBox::BoundingBox(const vector<Vec3d> & vertices)
{
  // set bmin_, bmax_
  bmin_ = Vec3d(+DBL_MAX, +DBL_MAX, +DBL_MAX);
  bmax_ = Vec3d(-DBL_MAX, -DBL_MAX, -DBL_MAX);
  for(size_t i = 0; i < vertices.size(); i++)
  {
    const Vec3d& p = vertices[i];
    if (p[0] < bmin_[0])
      bmin_[0] = p[0];
    if (p[0] > bmax_[0])
      bmax_[0] = p[0];

    if (p[1] < bmin_[1])
      bmin_[1] = p[1];
    if (p[1] > bmax_[1])
      bmax_[1] = p[1];

    if (p[2] < bmin_[2])
      bmin_[2] = p[2];
    if (p[2] > bmax_[2])
      bmax_[2] = p[2];
  }
  updateData();
}

template<class Triangle> 
BoundingBox::BoundingBox(const vector<Triangle> & tripool)
{
  // set bmin_, bmax_
  bmin_ = Vec3d(+DBL_MAX, +DBL_MAX, +DBL_MAX);
  bmax_ = Vec3d(-DBL_MAX, -DBL_MAX, -DBL_MAX);
  for(unsigned int i=0; i < tripool.size(); i++) // over all vertices
  {
    Vec3d p = tripool[i].first();
    if (p[0] < bmin_[0])
      bmin_[0] = p[0];
    if (p[0] > bmax_[0])
      bmax_[0] = p[0];

    if (p[1] < bmin_[1])
      bmin_[1] = p[1];
    if (p[1] > bmax_[1])
      bmax_[1] = p[1];

    if (p[2] < bmin_[2])
      bmin_[2] = p[2];
    if (p[2] > bmax_[2])
      bmax_[2] = p[2];

    p = tripool[i].second();

    if (p[0] < bmin_[0])
      bmin_[0] = p[0];
    if (p[0] > bmax_[0])
      bmax_[0] = p[0];

    if (p[1] < bmin_[1])
      bmin_[1] = p[1];
    if (p[1] > bmax_[1])
      bmax_[1] = p[1];

    if (p[2] < bmin_[2])
      bmin_[2] = p[2];
    if (p[2] > bmax_[2])
      bmax_[2] = p[2];

    p = tripool[i].third();

    if (p[0] < bmin_[0])
      bmin_[0] = p[0];
    if (p[0] > bmax_[0])
      bmax_[0] = p[0];

    if (p[1] < bmin_[1])
      bmin_[1] = p[1];
    if (p[1] > bmax_[1])
      bmax_[1] = p[1];

    if (p[2] < bmin_[2])
      bmin_[2] = p[2];
    if (p[2] > bmax_[2])
      bmax_[2] = p[2];
  }

  updateData();
}

void BoundingBox::regularize()
{
  Vec3d center_ = 0.5 * (bmin_ + bmax_);
  Vec3d halfside_ = 0.5* (bmax_ - bmin_);

  double maxHalf = halfside_[0];
  if (halfside_[1] > maxHalf)
    maxHalf = halfside_[1];
  if (halfside_[2] > maxHalf)
    maxHalf = halfside_[2];

  Vec3d cubeHalf_ = Vec3d(maxHalf,maxHalf,maxHalf);

  bmin_ = center_ - cubeHalf_;
  bmax_ = center_ + cubeHalf_;

  updateData();
}

void BoundingBox::updateData()
{
  center_ = 0.5 * (bmin_ + bmax_);
  halfSides_ = 0.5 * (bmax_ - bmin_);
}

void BoundingBox::verifyBox() const
{
  if (!((bmin_[0] <= bmax_[0]) && (bmin_[1] <= bmax_[1]) && (bmin_[2] <= bmax_[2])))
    printf("Error: inconsistent bounding box.\n");
}

bool BoundingBox::checkInside(const Vec3d & p) const
{
  return bmin_[0] <= p[0] && p[0] <= bmax_[0] && bmin_[1] <= p[1] && p[1] <= bmax_[1] && bmin_[2] <= p[2] && p[2] <= bmax_[2];
}

void BoundingBox::render() const
{
  // render the bounding box
  Vec3d p0(bmin_[0],bmin_[1],bmin_[2]);
  Vec3d p1(bmax_[0],bmin_[1],bmin_[2]);
  Vec3d p2(bmax_[0],bmax_[1],bmin_[2]);
  Vec3d p3(bmin_[0],bmax_[1],bmin_[2]);

  Vec3d p4(bmin_[0],bmin_[1],bmax_[2]);
  Vec3d p5(bmax_[0],bmin_[1],bmax_[2]);
  Vec3d p6(bmax_[0],bmax_[1],bmax_[2]);
  Vec3d p7(bmin_[0],bmax_[1],bmax_[2]);

  #define VTX(i) (i)[0],(i)[1],(i)[2]
  glBegin(GL_LINES);
    glVertex3f(VTX(p0));
    glVertex3f(VTX(p1));
    glVertex3f(VTX(p1));
    glVertex3f(VTX(p2));
    glVertex3f(VTX(p2));
    glVertex3f(VTX(p3));
    glVertex3f(VTX(p3));
    glVertex3f(VTX(p0));

    glVertex3f(VTX(p0));
    glVertex3f(VTX(p4));
    glVertex3f(VTX(p1));
    glVertex3f(VTX(p5));
    glVertex3f(VTX(p2));
    glVertex3f(VTX(p6));
    glVertex3f(VTX(p3));
    glVertex3f(VTX(p7));

    glVertex3f(VTX(p4));
    glVertex3f(VTX(p5));
    glVertex3f(VTX(p5));
    glVertex3f(VTX(p6));
    glVertex3f(VTX(p6));
    glVertex3f(VTX(p7));
    glVertex3f(VTX(p7));
    glVertex3f(VTX(p4));
  glEnd();

  #undef VTX
}

// should this be turned into a self-modifying function?
void BoundingBox::expand(double expansionFactor)
{
  bmin_ = center_ - expansionFactor * halfSides_;
  bmax_ = center_ + expansionFactor * halfSides_;

  updateData();
}

bool BoundingBox::lineSegmentIntersection(const Vec3d & segmentStart, const Vec3d & segmentEnd, Vec3d * intersection) const
{
  /*
    Jernej Barbic, CMU, 2005
    adapted from:

    Fast Ray-Box Intersection
    by Andrew Woo
    from "Graphics Gems", Academic Press, 1990
 */

  #define NUMDIM  3
  #define RIGHT   0
  #define LEFT    1
  #define MIDDLE  2

  Vec3d dir = segmentEnd - segmentStart;
  bool inside = true;
  char quadrant[NUMDIM];
  register int i;
  int whichPlane;
  double maxT[NUMDIM];
  double candidatePlane[NUMDIM];

  /* Find candidate planes; this loop can be avoided if
  rays cast all from the eye(assume perpsective view) */
  for (i=0; i<NUMDIM; i++)
    if(segmentStart[i] < bmin_[i]) 
    {
      quadrant[i] = LEFT;
      candidatePlane[i] = bmin_[i];
      inside = false;
    }
    else if (segmentStart[i] > bmax_[i]) 
    {
      quadrant[i] = RIGHT;
      candidatePlane[i] = bmax_[i];
      inside = false;
    }
    else   
    {
      quadrant[i] = MIDDLE;
    }
                                                                                                                                                             
  /* Ray origin inside bounding box */
  if(inside)      
  {
    *intersection = segmentStart;
    return (true);
  }

  /* Calculate T distances to candidate planes */
  for (i = 0; i < NUMDIM; i++)
    if (quadrant[i] != MIDDLE && dir[i] !=0.)
      maxT[i] = (candidatePlane[i]-segmentStart[i]) / dir[i];
    else
      maxT[i] = -1.;

  /* Get largest of the maxT's for final choice of intersection */
  whichPlane = 0;
  for (i = 1; i < NUMDIM; i++)
    if (maxT[whichPlane] < maxT[i])
      whichPlane = i;

  /* Check final candidate actually inside box */
  if (maxT[whichPlane] < 0.0) 
    return (false);
  if (maxT[whichPlane] > 1.0) 
    return (false); // remove this for ray

  for (i = 0; i < NUMDIM; i++)
  {
    if (whichPlane != i) 
    {
      (*intersection)[i] = segmentStart[i] + maxT[whichPlane] *dir[i];
      if ((*intersection)[i] < bmin_[i] || (*intersection)[i] > bmax_[i])
        return (false);
    } 
    else 
    {
      (*intersection)[i] = candidatePlane[i];
    }
  }

  return (true);                          /* ray hits box */

  #undef NUMDIM
  #undef RIGHT
  #undef LEFT
  #undef MIDDLE
}

double BoundingBox::distanceToPoint(const Vec3d & point) const
{
  double distance = 0.0;
  for(int dim=0; dim<3; dim++)
  {
    if (point[dim] < bmin_[dim])
      distance += (bmin_[dim] - point[dim]) * (bmin_[dim] - point[dim]);
    if (point[dim] > bmax_[dim])
      distance += (point[dim] - bmax_[dim]) * (point[dim] - bmax_[dim]);
  }
  return sqrt(distance);
}

void BoundingBox::print() const
{
  cout << bmin_ << " " << bmax_ << endl;
}

template BoundingBox::BoundingBox(const vector<TriangleBasic> & tripool);
template BoundingBox::BoundingBox(const vector<TriangleWithCollisionInfo> & tripool);
template BoundingBox::BoundingBox(const vector<TriangleWithCollisionInfoAndPseudoNormals> & tripool);
