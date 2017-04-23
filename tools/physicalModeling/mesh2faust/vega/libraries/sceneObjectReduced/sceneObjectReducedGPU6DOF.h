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

#ifndef _SCENEOBJECTREDUCEDGPU6DOF_H_
#define _SCENEOBJECTREDUCEDGPU6DOF_H_

#include "sceneObjectReduced6DOF.h"
#include "sceneObjectReducedGPU.h"

class SceneObjectReducedGPU6DOF : public SceneObjectReducedGPU, public SceneObjectReduced6DOF
{
public:

  SceneObjectReducedGPU6DOF(const char * filenameOBJ, ModalMatrix * modalMatrix, int GPUMethod = 0); 
  SceneObjectReducedGPU6DOF(const char * filenameOBJ, ModalMatrix * modalMatrix, SceneObjectReducedGPU * cloningSource, int GPUMethod = 0);
  
  SceneObjectReducedGPU6DOF(ObjMesh * objMesh, ModalMatrix * modalMatrix, int GPUMethod = 0, bool deepCopy = true); 
  SceneObjectReducedGPU6DOF(ObjMesh * objMesh, ModalMatrix * modalMatrix,
    SceneObjectReducedGPU * cloningSource, int GPUMethod = 0, bool deepCopy = true);

  virtual ~SceneObjectReducedGPU6DOF();

  virtual void Render();
  virtual void RenderVertices();
  virtual void RenderVertices_Selection();
  virtual void RenderEdges();
  virtual void RenderVertices(int numVertices, int * vertexList);
  virtual void RenderShadow(double ground[4], double light[4]);

  virtual int GetClosestVertex(Vec3d & queryPos, double * distance, double * auxVertexBuffer);

protected:
};

#endif

