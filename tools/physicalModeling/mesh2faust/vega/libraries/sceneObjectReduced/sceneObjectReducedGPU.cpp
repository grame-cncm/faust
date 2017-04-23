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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "sceneObjectReducedGPU.h"

SceneObjectReducedGPU::SceneObjectReducedGPU(const char * filenameOBJ, 
      ModalMatrix * modalMatrix, int GPUMethod):
      SceneObjectWithRestPosition(filenameOBJ), SceneObjectReduced(filenameOBJ, modalMatrix)
{
  Construct(GPUMethod);
}

SceneObjectReducedGPU::SceneObjectReducedGPU(ObjMesh * objMesh, 
      ModalMatrix * modalMatrix, int GPUMethod, bool deepCopy):
      SceneObjectWithRestPosition(objMesh, deepCopy), SceneObjectReduced(objMesh, modalMatrix, deepCopy)
{
  Construct(GPUMethod);
}

void SceneObjectReducedGPU::Construct(int GPUMethod)
{
  try
  {
    if (GPUMethod == 0)
    {
      render_uUq = new ObjMeshGPUDeformer_uUq_fbo();
      //SetMaterialAlpha(0.5);
      render_uUq->Init(mesh, meshRender, r, modalMatrix->GetMatrix(), renderMode);
    }
    else if (GPUMethod == 1)
    {
      #if defined(_WIN32) || defined(WIN32)
        render_uUq = new ObjMeshGPUDeformer_uUq_pbuffer();
        render_uUq->Init(mesh, meshRender, r, modalMatrix->GetMatrix(), renderMode);
      #else
        throw 10;
      #endif
    }
  }
  catch(int exception)
  {
    printf("Failed to initialize the GP-GPU renderer. Exception code: %d\n", exception);
    throw 1;
  }

  if (n != modalMatrix->Getn())
  {
    printf("Error (SceneObjectReducedGPU): modal matrix size (%d) doesn't match the number of "
           "obj file vertices (%d).\n", modalMatrix->Getn(), n);
    throw 2;
  }
}

void SceneObjectReducedGPU::Construct(SceneObjectReducedGPU * cloningSource, int GPUMethod)
{
  try
  {
    if (GPUMethod == 0)
    {
      render_uUq = new ObjMeshGPUDeformer_uUq_fbo();
      render_uUq->Clone(cloningSource->render_uUq);
    }
    else if (GPUMethod == 1)
    {
      #if defined(_WIN32) || defined(WIN32)
        render_uUq = new ObjMeshGPUDeformer_uUq_pbuffer();
        render_uUq->Clone(cloningSource->render_uUq);
      #else
        throw 10;
      #endif
    }
  }
  catch(int exception)
  {
    printf("Failed to initialize the GP-GPU renderer. Exception code: %d\n", exception);
    throw 1;
  }

  if (n != modalMatrix->Getn())
  {
    printf("Error (SceneObjectReducedGPU): modal matrix size (%d) doesn't match the number of "
           "obj file vertices (%d).\n", modalMatrix->Getn(), n);
    throw 2;
  }
}

SceneObjectReducedGPU::SceneObjectReducedGPU(const char * filenameOBJ, 
      ModalMatrix * modalMatrix, SceneObjectReducedGPU * cloningSource, int GPUMethod):
      SceneObjectWithRestPosition(filenameOBJ), SceneObjectReduced(filenameOBJ, modalMatrix)
{
  Construct(cloningSource, GPUMethod);
}

SceneObjectReducedGPU::SceneObjectReducedGPU(ObjMesh * objMesh, 
      ModalMatrix * modalMatrix, SceneObjectReducedGPU * cloningSource, int GPUMethod, bool deepCopy):
      SceneObjectWithRestPosition(objMesh, deepCopy), SceneObjectReduced(objMesh, modalMatrix, deepCopy)
{
  Construct(cloningSource, GPUMethod);
}

SceneObjectReducedGPU::~SceneObjectReducedGPU()
{
  delete(render_uUq);
}

void SceneObjectReducedGPU::Setq(double * q)
{
  memcpy(this->q,q,sizeof(double)*r);
  render_uUq->Setqdv(q);
}

void SceneObjectReducedGPU::Getq(double * q)
{
  memcpy(q,this->q,sizeof(double)*r);
}

void SceneObjectReducedGPU::Compute_uUq()
{
  render_uUq->Compute_uUq();
}

void SceneObjectReducedGPU::Render()
{
  render_uUq->Render();
}

void SceneObjectReducedGPU::RenderVertices()
{
  render_uUq->RenderVertices();
}

void SceneObjectReducedGPU::RenderEdges()
{
  render_uUq->RenderEdges();
}

void SceneObjectReducedGPU::Getu(double * u)
{
  render_uUq->ReadBack_u(u);
}

void SceneObjectReducedGPU::RenderShadow(double ground[4], double light[4])
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  SetShadowingModelviewMatrix(ground, light);
  render_uUq->RenderShadow(0.2);
  glPopMatrix();
}

void SceneObjectReducedGPU::SetLighting(Lighting * lighting)
{
  setGPULighting.SetLighting(render_uUq, lighting);
}

int SceneObjectReducedGPU::GetClosestVertex(Vec3d & queryPos, double * distance, double * auxVertexBuffer)
{
  modalMatrix->AssembleVector(q, auxVertexBuffer);
  SetVertexDeformations(auxVertexBuffer);
  return mesh->getClosestVertex(queryPos, distance);
}

