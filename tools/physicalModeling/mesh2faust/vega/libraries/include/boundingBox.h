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

#ifndef __BOUNDINGBOX_H__
#define __BOUNDINGBOX_H__

//  Bounding Box
//  Author: Jernej Barbic, CMU

#include <vector>
#include "minivector.h"

class BoundingBox
{
public:

  BoundingBox(Vec3d bmin_g=Vec3d(0,0,0), Vec3d bmax_g=Vec3d(1,1,1)): bmin_(bmin_g), bmax_(bmax_g) { updateData();}
  BoundingBox(const std::vector<Vec3d> & vertices);
  template<class Triangle> BoundingBox(const std::vector<Triangle> & tripool);

  // accessors
  const Vec3d & bmin() const { return bmin_;}
  const Vec3d & bmax() const { return bmax_;}

  const Vec3d & center() const { return center_;}
  const Vec3d & halfSides() const { return halfSides_;}

  double diameter() const { return len(bmax_-bmin_); }

  // mutators
  void setbmin(const Vec3d & bmin_g) { bmin_=bmin_g; updateData();}
  void setbmin(double x, double y, double z) { bmin_=Vec3d(x,y,z); updateData();}
  void setbmax(const Vec3d & bmax_g) { bmax_=bmax_g; updateData();}
  void setbmax(double x, double y, double z) { bmax_=Vec3d(x,y,z); updateData();}

  void render() const;

  double distanceToPoint(const Vec3d & point) const;
  bool checkInside(const Vec3d & point) const;

  // sanity check bmin <= bmax
  void verifyBox() const;

  // expands from the center 
  // factor of 1.0 indicates no expansion
  void expand(double expansionFactor);
  void regularize(); // converts the box into one with all sides equal

  bool lineSegmentIntersection(const Vec3d & segmentStart, const Vec3d & segmentEnd, Vec3d * intersection) const;

  void print() const;

protected:

  void updateData(); // updates center and half-sides
  Vec3d center_, halfSides_;
  Vec3d bmin_,bmax_;
};

#endif
