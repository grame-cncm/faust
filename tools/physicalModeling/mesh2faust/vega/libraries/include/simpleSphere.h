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

#ifndef _SIMPLESPHERE_H_
#define _SIMPLESPHERE_H_

/*
  A sphere
  Author: Jernej Barbic, CMU
*/

#include "minivector.h"
#include "boundingBox.h"

class SimpleSphere
{
public:
  SimpleSphere(Vec3d center_, double radius_) : center(center_), radius(radius_) {}

  SimpleSphere(double x, double y, double z, double radius_) : center(Vec3d(x,y,z)), radius(radius_) {}

  // does the sphere intersect the bounding box
  bool doesBoundingBoxIntersect(BoundingBox & box) const;

private:
  Vec3d center;
  double radius;
};

#endif

