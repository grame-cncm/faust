/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "sceneObject" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC    *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Daniel Schroeder                         *
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

/*
  A reduced-deformable scene object, with deformations computed on the CPU.
  See also sceneObject.h . 
*/

#ifndef _SCENEOBJECTREDUCEDCPU_H_
#define _SCENEOBJECTREDUCEDCPU_H_

#include "sceneObjectReduced.h"

class SceneObjectReducedCPU : virtual public SceneObjectReduced
{
public:

  SceneObjectReducedCPU(const char * filenameOBJ, ModalMatrix * modalMatrix);
  SceneObjectReducedCPU(ObjMesh * objMesh, ModalMatrix * modalMatrix, bool deepCopy = true);

  void Getq(double * q);
  void Setq(double * q);
  virtual void Compute_uUq(); // computes u=U*q in software and sets internal position to: rest position + u

  double * Getu() { return u; }
  virtual void Getu(double * u);

  virtual int GetClosestVertex(Vec3d & queryPos, double * distance=NULL, double * auxVertexBuffer=NULL);

protected:
  void Construct(ModalMatrix * modalMatrix);
  double * u;
};

#endif

