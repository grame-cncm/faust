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

#include "sceneObjectReducedGPU6DOF.h"

SceneObjectReducedGPU6DOF::SceneObjectReducedGPU6DOF(const char * filenameOBJ, ModalMatrix * modalMatrix, int GPUMethod): SceneObjectWithRestPosition(filenameOBJ), SceneObjectReduced(filenameOBJ, modalMatrix), SceneObjectReducedGPU(filenameOBJ, modalMatrix, GPUMethod), SceneObjectReduced6DOF(filenameOBJ, modalMatrix) 
{
}

SceneObjectReducedGPU6DOF::SceneObjectReducedGPU6DOF(const char * filenameOBJ, ModalMatrix * modalMatrix, SceneObjectReducedGPU * cloningSource, int GPUMethod): SceneObjectWithRestPosition(filenameOBJ), SceneObjectReduced(filenameOBJ, modalMatrix), SceneObjectReducedGPU(filenameOBJ, modalMatrix, cloningSource, GPUMethod), SceneObjectReduced6DOF(filenameOBJ, modalMatrix) 
{
}

SceneObjectReducedGPU6DOF::SceneObjectReducedGPU6DOF(ObjMesh * objMesh, ModalMatrix * modalMatrix, int GPUMethod, bool deepCopy): SceneObjectWithRestPosition(objMesh, deepCopy), SceneObjectReduced(objMesh, modalMatrix, deepCopy), SceneObjectReducedGPU(objMesh, modalMatrix, GPUMethod, deepCopy), SceneObjectReduced6DOF(objMesh, modalMatrix, deepCopy){
}

SceneObjectReducedGPU6DOF::SceneObjectReducedGPU6DOF(ObjMesh * objMesh, ModalMatrix * modalMatrix, SceneObjectReducedGPU * cloningSource, int GPUMethod, bool deepCopy): SceneObjectWithRestPosition(objMesh, deepCopy), SceneObjectReduced(objMesh, modalMatrix, deepCopy), SceneObjectReducedGPU(objMesh, modalMatrix, cloningSource, GPUMethod, deepCopy), SceneObjectReduced6DOF(objMesh, modalMatrix, deepCopy) 
{
}

SceneObjectReducedGPU6DOF::~SceneObjectReducedGPU6DOF() 
{
}

void SceneObjectReducedGPU6DOF::Render()
{
  double M[16] = {R[0], R[3], R[6], 0,
        R[1], R[4], R[7], 0,
        R[2], R[5], R[8], 0,
        centerOfMass[0], centerOfMass[1], centerOfMass[2], 1 };

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixd(M);
    SceneObjectReducedGPU::Render();
  glPopMatrix();
}

void SceneObjectReducedGPU6DOF::RenderShadow(double ground[4], double light[4])
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    SetShadowingModelviewMatrix(ground, light);
    double M[16] = {R[0], R[3], R[6], 0,
          R[1], R[4], R[7], 0,
	  R[2], R[5], R[8], 0,
	  centerOfMass[0], centerOfMass[1], centerOfMass[2], 1 };

    glMultMatrixd(M);
    render_uUq->RenderShadow(0.2);
  glPopMatrix();
}

void SceneObjectReducedGPU6DOF::RenderVertices()
{
  double M[16] = {R[0], R[3], R[6], 0,
          R[1], R[4], R[7], 0,
	  R[2], R[5], R[8], 0,
	  centerOfMass[0], centerOfMass[1], centerOfMass[2], 1 };

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixd(M);
    SceneObjectReducedGPU::RenderVertices();
  glPopMatrix();
}

void SceneObjectReducedGPU6DOF::RenderVertices_Selection()
{
  double M[16] = {R[0], R[3], R[6], 0,
          R[1], R[4], R[7], 0,
	  R[2], R[5], R[8], 0,
	  centerOfMass[0],    centerOfMass[1],    centerOfMass[2], 1 };

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixd(M);
    SceneObjectReducedGPU::RenderVertices_Selection();
  glPopMatrix();
}

void SceneObjectReducedGPU6DOF::RenderEdges()
{
  double M[16] = {R[0], R[3], R[6], 0,
          R[1], R[4], R[7], 0,
	  R[2], R[5], R[8], 0,
	  centerOfMass[0], centerOfMass[1], centerOfMass[2], 1 };

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixd(M);
    SceneObjectReducedGPU::RenderEdges();
  glPopMatrix();
}

void SceneObjectReducedGPU6DOF::RenderVertices(int numVertices, int * vertexList)
{
  double M[16] = {R[0], R[3], R[6], 0,
          R[1], R[4], R[7], 0,
	  R[2], R[5], R[8], 0,
	  centerOfMass[0], centerOfMass[1], centerOfMass[2], 1 };

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixd(M);
    SceneObjectReducedGPU::RenderVertices(numVertices, vertexList);
  glPopMatrix();
}

int SceneObjectReducedGPU6DOF::GetClosestVertex(Vec3d & queryPos, double * distance, double * auxVertexBuffer)
{
  // transform the position to the local frame
  double queryPosv[3] = { queryPos[0], queryPos[1], queryPos[2] };
  double localQueryPosv[3];
  TransformToLocal(queryPosv, localQueryPosv);
  Vec3d localQueryPos(localQueryPosv);

  return SceneObjectReducedGPU::GetClosestVertex(localQueryPos, distance, auxVertexBuffer);
}

