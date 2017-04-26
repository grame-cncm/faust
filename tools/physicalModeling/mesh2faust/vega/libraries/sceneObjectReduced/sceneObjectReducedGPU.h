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
  A reduced-deformable scene object, with deformations computed on the GPU
  (using custom vertex and fragment shaders (vertex texture fetch extension))
  See also sceneObject.h . 
*/

#ifndef _SCENEOBJECTREDUCEDGPU_H_
#define _SCENEOBJECTREDUCEDGPU_H_

#include "sceneObjectReduced.h"
#include "objMeshGPUDeformer_uUq_pbuffer.h"
#include "objMeshGPUDeformer_uUq_fbo.h"
#include "objMeshGPUDeformer_uUq_setLighting.h"

class SceneObjectReducedGPU : virtual public SceneObjectReduced
{
public:
  // GPUMethod: 
  // 0: framebuffer object
  // 1: pbuffer (Windows only)
  SceneObjectReducedGPU(const char * filenameOBJ, ModalMatrix * modalMatrix, int GPUMethod = 0);
  SceneObjectReducedGPU(ObjMesh * objMesh, ModalMatrix * modalMatrix, int GPUMethod = 0, bool deepCopy = true);

  SceneObjectReducedGPU(const char * filenameOBJ, ModalMatrix * modalMatrix, SceneObjectReducedGPU * cloningSource, int GPUMethod = 0);
  SceneObjectReducedGPU(ObjMesh * objMesh, ModalMatrix * modalMatrix, SceneObjectReducedGPU * cloningSource, int GPUMethod = 0, bool deepCopy = true);

  virtual ~SceneObjectReducedGPU();

  void Getq(double * q);
  void Setq(double * q);
  virtual void Compute_uUq(); // on a GPU

  virtual void SetLighting(Lighting * lighting);

  virtual void Render(); 
  virtual void RenderVertices();
  virtual void RenderEdges();

  virtual void Getu(double * u);

  // the following were not implemented and don't work
  virtual void RenderVertices_Selection() { printf("Error: invalid call to SceneObjectReducedGPU::RenderVertices_Selection.\n"); }
  virtual void RenderVertices(int numVertices, int * vertexList) { printf("Error: invalid call to SceneObjectReducedGPU::RenderVertices(with vertexList param).\n"); }
  virtual void RenderShadow(double ground[4], double light[4]);

  virtual int GetClosestVertex(Vec3d & queryPos, double * distance, double * auxVertexBuffer);

protected:
  void Construct(int GPUMethod);
  void Construct(SceneObjectReducedGPU * cloningSource, int GPUMethod);

  ObjMeshGPUDeformer_uUq * render_uUq;
  ObjMeshGPUDeformer_uUq_setLighting setGPULighting;
};

#endif

