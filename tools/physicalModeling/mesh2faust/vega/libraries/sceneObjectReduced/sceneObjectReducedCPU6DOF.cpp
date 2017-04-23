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

#include "sceneObjectReducedCPU6DOF.h"

SceneObjectReducedCPU6DOF::SceneObjectReducedCPU6DOF(const char * filenameOBJ, ModalMatrix * modalMatrix): SceneObjectWithRestPosition(filenameOBJ), SceneObjectReduced(filenameOBJ, modalMatrix), SceneObjectReducedCPU(filenameOBJ, modalMatrix), SceneObjectReduced6DOF(filenameOBJ, modalMatrix)
{
}

SceneObjectReducedCPU6DOF::SceneObjectReducedCPU6DOF(ObjMesh * objMesh, ModalMatrix * modalMatrix, bool deepCopy): SceneObjectWithRestPosition(objMesh, deepCopy), SceneObjectReduced(objMesh, modalMatrix, deepCopy), SceneObjectReducedCPU(objMesh, modalMatrix, deepCopy), SceneObjectReduced6DOF(objMesh, modalMatrix, deepCopy)
{
}

SceneObjectReducedCPU6DOF::~SceneObjectReducedCPU6DOF() {}

void SceneObjectReducedCPU6DOF::Render()
{
  double M[16] = {R[0], R[3], R[6], 0,
                  R[1], R[4], R[7], 0,
		  R[2], R[5], R[8], 0,
		  centerOfMass[0], centerOfMass[1], centerOfMass[2], 1 };

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixd(M);
    SceneObjectReducedCPU::Render();
  glPopMatrix();
}

void SceneObjectReducedCPU6DOF::RenderShadow(double ground[4], double light[4])
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  SetShadowingModelviewMatrix(ground, light);

  double M[16] = {R[0], R[3], R[6], 0,
        R[1], R[4], R[7], 0,
        R[2], R[5], R[8], 0,
        centerOfMass[0], centerOfMass[1], centerOfMass[2], 1 };

  glMultMatrixd(M);
  SceneObjectReducedCPU::Render();
  glPopMatrix();
}

void SceneObjectReducedCPU6DOF::RenderVertices()
{
  double M[16] = {R[0], R[3], R[6], 0,
             R[1], R[4], R[7], 0,
	  R[2], R[5], R[8], 0,
	  centerOfMass[0],    centerOfMass[1],    centerOfMass[2], 1 };

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixd(M);
    SceneObjectReducedCPU::RenderVertices();
  glPopMatrix();
}

void SceneObjectReducedCPU6DOF::RenderVertices_Selection()
{
  double M[16] = {R[0], R[3], R[6], 0,
          R[1], R[4], R[7], 0,
	  R[2], R[5], R[8], 0,
	  centerOfMass[0],    centerOfMass[1],    centerOfMass[2], 1 };

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixd(M);
    SceneObjectReducedCPU::RenderVertices_Selection();
  glPopMatrix();
}

void SceneObjectReducedCPU6DOF::RenderEdges()
{
  double M[16] = {R[0], R[3], R[6], 0,
              R[1], R[4], R[7], 0,
	  R[2], R[5], R[8], 0,
	  centerOfMass[0],    centerOfMass[1],    centerOfMass[2], 1 };

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixd(M);
    SceneObjectReducedCPU::RenderEdges();
  glPopMatrix();
}

void SceneObjectReducedCPU6DOF::RenderVertices(int numVertices, int * vertexList)
{
  double M[16] = {R[0], R[3], R[6], 0,
              R[1], R[4], R[7], 0,
	  R[2], R[5], R[8], 0,
	  centerOfMass[0],    centerOfMass[1],    centerOfMass[2], 1 };

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixd(M);
    SceneObjectReducedCPU::RenderVertices(numVertices, vertexList);
  glPopMatrix();
}

int SceneObjectReducedCPU6DOF::GetClosestVertex(Vec3d & queryPos, double * distance, double * auxVertexBuffer)
{
  // transform the position to the local frame
  double queryPosv[3] = { queryPos[0], queryPos[1], queryPos[2] };
  double localQueryPosv[3];
  TransformToLocal(queryPosv, localQueryPosv);
  Vec3d localQueryPos(localQueryPosv);

  return SceneObjectReducedCPU::GetClosestVertex(localQueryPos, distance, auxVertexBuffer);
}

