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
  A reduced-deformable scene object.
  See also sceneObject.h . 
*/

#ifndef _SCENEOBJECTREDUCED_H_
#define _SCENEOBJECTREDUCED_H_

#include "macros.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "sceneObjectDeformable.h"
#include "modalMatrix.h"

// abstract class
class SceneObjectReduced : public SceneObjectDeformable
{
public:

  SceneObjectReduced(const char * filenameOBJ, ModalMatrix * modalMatrix);
  SceneObjectReduced(ObjMesh * objMesh, ModalMatrix * modalMatrix, bool deepCopy = true);
  virtual ~SceneObjectReduced();

  inline int Getr() { return r; }

  inline virtual void GetSingleVertexPosition(int vertex, double * x, double * y, double * z);

  virtual void Render() { SceneObject::Render(); }
  virtual void RenderVertices() { SceneObject::RenderVertices(); }
  virtual void RenderVertices_Selection() { SceneObject::RenderVertices_Selection(); }
  virtual void RenderEdges() { SceneObject::RenderEdges(); }
  virtual void RenderVertices(int numVertices, int * vertexList) { SceneObject::RenderVertices(numVertices, vertexList); }
  virtual void RenderShadow(double ground[4], double light[4]) { SceneObject::RenderShadow(ground, light); }

  virtual void Getu(double * u) = 0;

  void SetZeroq();
  double * Getqp() { return q; }
  virtual void Setq(double * q) = 0; // copies q into internal state
  void Scaleq(double scale); // scales the current q
  virtual void Compute_uUq() = 0;

protected:
  void Construct(ModalMatrix * modalMatrix);

  double * q;
  int r;

  ModalMatrix * modalMatrix;
};

inline void SceneObjectReduced::GetSingleVertexPosition(int vertex, double * x, double * y, double * z)
{
  *x = restPosition[3*vertex+0];
  *y = restPosition[3*vertex+1];
  *z = restPosition[3*vertex+2];

  modalMatrix->AddAssembleSingleVertex(vertex,q,x,y,z);
}

#endif

