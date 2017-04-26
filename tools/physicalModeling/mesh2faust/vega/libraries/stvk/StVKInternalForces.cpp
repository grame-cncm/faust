/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "StVK" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
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

#include "StVKInternalForces.h"
#include "volumetricMeshENuMaterial.h"

StVKInternalForces::StVKInternalForces(VolumetricMesh * volumetricMesh_, StVKElementABCD * precomputedABCDIntegrals_, bool addGravity_, double g_): volumetricMesh(volumetricMesh_), precomputedIntegrals(precomputedABCDIntegrals_), gravityForce(NULL), addGravity(addGravity_), g(g_) 
{
  int numElements = volumetricMesh->getNumElements();
  lambdaLame = (double*) malloc (sizeof(double) * numElements);
  muLame = (double*) malloc (sizeof(double) * numElements);

  for(int el=0; el<numElements; el++)
  {
    VolumetricMesh::Material * material = volumetricMesh->getElementMaterial(el);
    VolumetricMesh::ENuMaterial * eNuMaterial = downcastENuMaterial(material);
    if (eNuMaterial == NULL)
    {
      printf("Error: StVKInternalForces: mesh does not consist of E, nu materials.\n");
      throw 1;
    }

    lambdaLame[el] = eNuMaterial->getLambda();
    muLame[el] = eNuMaterial->getMu();
  }

  buffer = (double*) malloc (sizeof(double) * 3 * volumetricMesh->getNumVertices());
  numElementVertices = volumetricMesh->getNumElementVertices();
  InitGravity();
}

StVKInternalForces::~StVKInternalForces()
{
  free(gravityForce);
  free(buffer);
  free(lambdaLame);
  free(muLame);
}

void StVKInternalForces::InitGravity()
{
  if (addGravity && (gravityForce == NULL))
  {
    gravityForce = (double*) malloc (sizeof(double) * 3 * volumetricMesh->getNumVertices());
    volumetricMesh->computeGravity(gravityForce, g);
  }  
}

double StVKInternalForces::ComputeEnergy(const double * vertexDisplacements)
{
  return ComputeEnergyContribution(vertexDisplacements, 0, volumetricMesh->getNumElements());
}

double StVKInternalForces::ComputeEnergyContribution(const double * vertexDisplacements, int elementLow, int elementHigh, double * buffer)
{
  if (buffer == NULL)
    buffer = this->buffer;

  int numVertices = volumetricMesh->getNumVertices();
  double energy = 0;

  // ---- linear
  ResetVector(buffer);
  AddLinearTermsContribution(vertexDisplacements, buffer, elementLow, elementHigh);
  for (int i=0; i< 3 * numVertices; i++)
    energy += 0.5 * buffer[i] * vertexDisplacements[i];

  // ---- quadratic
  ResetVector(buffer);
  AddQuadraticTermsContribution(vertexDisplacements, buffer, elementLow, elementHigh);
  double oneThird = 1.0 / 3;
  for (int i=0; i< 3 * numVertices; i++)
    energy += oneThird * buffer[i] * vertexDisplacements[i];

  // ---- cubic
  ResetVector(buffer);
  AddCubicTermsContribution(vertexDisplacements, buffer, elementLow, elementHigh);
  double oneQuarter = 1.0 / 4;
  for (int i=0; i< 3 * numVertices; i++)
    energy += oneQuarter * buffer[i] * vertexDisplacements[i];

  return energy;
}

void StVKInternalForces::ComputeForces(const double * vertexDisplacements, double * forces)
{
  //PerformanceCounter forceCounter;

  ResetVector(forces);
  AddLinearTermsContribution(vertexDisplacements, forces);
  AddQuadraticTermsContribution(vertexDisplacements, forces);
  AddCubicTermsContribution(vertexDisplacements, forces);

  if (addGravity)
  {
    int n = volumetricMesh->getNumVertices();
    for(int i=0; i<3*n; i++)
      forces[i] -= gravityForce[i];
  }

  //forceCounter.StopCounter();
  //printf("Internal forces: %G\n", forceCounter.GetElapsedTime());
}

void StVKInternalForces::AddLinearTermsContribution(const double * vertexDisplacements, double * forces, int elementLow, int elementHigh)
{
  if (elementLow < 0)
    elementLow = 0;
  if (elementHigh < 0)
    elementHigh = volumetricMesh->getNumElements();

  int * vertices = (int*) malloc (sizeof(int) * numElementVertices);

  void * elIter;
  precomputedIntegrals->AllocateElementIterator(&elIter);

  for(int el=elementLow; el < elementHigh; el++)
  {
    precomputedIntegrals->PrepareElement(el, elIter);
    for(int ver=0; ver<numElementVertices; ver++)
      vertices[ver] = volumetricMesh->getVertexIndex(el, ver);

    double lambda = lambdaLame[el]; 
    double mu = muLame[el];

    for (int c=0; c<numElementVertices; c++) // over all vertices of the voxel, computing force on vertex c
    {
      // linear terms
      for (int a=0; a<numElementVertices; a++) // over all vertices
      {
        Vec3d qa(vertexDisplacements[3*vertices[a]+0],
                 vertexDisplacements[3*vertices[a]+1],
                 vertexDisplacements[3*vertices[a]+2]);

        Vec3d force = lambda * (precomputedIntegrals->A(elIter,c,a) * qa) +
                      (mu * precomputedIntegrals->B(elIter,a,c)) * qa +
                      mu * (precomputedIntegrals->A(elIter,a,c) * qa);

        forces[3*vertices[c]+0] += force[0];
        forces[3*vertices[c]+1] += force[1];
        forces[3*vertices[c]+2] += force[2];
      }
    }
  }

  free(vertices);

  precomputedIntegrals->ReleaseElementIterator(elIter);
}

void StVKInternalForces::AddQuadraticTermsContribution(const double * vertexDisplacements, double * forces, int elementLow, int elementHigh)
{
  if (elementLow < 0)
    elementLow = 0;
  if (elementHigh < 0)
    elementHigh = volumetricMesh->getNumElements();

  int * vertices = (int*) malloc (sizeof(int) * numElementVertices);

  void * elIter;
  precomputedIntegrals->AllocateElementIterator(&elIter);

  for(int el=elementLow; el < elementHigh; el++)
  {
    precomputedIntegrals->PrepareElement(el, elIter);
    for(int ver=0; ver<numElementVertices; ver++)
      vertices[ver] = volumetricMesh->getVertexIndex(el, ver);

    double lambda = lambdaLame[el]; 
    double mu = muLame[el];

    for (int c=0; c<numElementVertices; c++) // over all vertices of the voxel, computing force on vertex c
    {
      // quadratic terms
      for (int a=0; a<numElementVertices; a++) // over all vertices
        for(int b=0; b<numElementVertices; b++)
        {
/*
          Vec3d force(0,0,0);
          Vec3d qa(vertexDisplacements[3*vertices[a]+0],
                   vertexDisplacements[3*vertices[a]+1],
                   vertexDisplacements[3*vertices[a]+2]);

          Vec3d qb(vertexDisplacements[3*vertices[b]+0],
                   vertexDisplacements[3*vertices[b]+1],
                   vertexDisplacements[3*vertices[b]+2]);

          double dotp = dot(qa,qb);

          force += 0.5 * lambda * dotp * precomputedIntegrals->C(el,c,a,b) +
                   mu * dotp * precomputedIntegrals->C(el,a,b,c);

          Vec3d C = lambda * precomputedIntegrals->C(el,a,b,c) +
                    mu * (precomputedIntegrals->C(el,c,a,b) + precomputedIntegrals->C(el,b,a,c)); 

          force += dot(C,qa) * qb;

          forces[3*vertices[c]+0] += force[0];
          forces[3*vertices[c]+1] += force[1];
          forces[3*vertices[c]+2] += force[2];
*/

          double qa[3] = {vertexDisplacements[3*vertices[a]+0],
                          vertexDisplacements[3*vertices[a]+1],
                          vertexDisplacements[3*vertices[a]+2]};
          double qb[3] = {vertexDisplacements[3*vertices[b]+0],
                          vertexDisplacements[3*vertices[b]+1],
                          vertexDisplacements[3*vertices[b]+2]};

          double dotp = qa[0] * qb[0] + qa[1] * qb[1] + qa[2] * qb[2];

          Vec3d forceTerm1 = 0.5 * lambda * dotp * precomputedIntegrals->C(elIter,c,a,b) +
                             mu * dotp * precomputedIntegrals->C(elIter,a,b,c);

          Vec3d C = lambda * precomputedIntegrals->C(elIter,a,b,c) +
                    mu * (precomputedIntegrals->C(elIter,c,a,b) + precomputedIntegrals->C(elIter,b,a,c)); 

          double dotCqa = C[0] * qa[0] + C[1] * qa[1] + C[2] * qa[2];

          forces[3*vertices[c]+0] += forceTerm1[0] + dotCqa * qb[0];
          forces[3*vertices[c]+1] += forceTerm1[1] + dotCqa * qb[1];
          forces[3*vertices[c]+2] += forceTerm1[2] + dotCqa * qb[2];
        }
    }
  }

  free(vertices);

  precomputedIntegrals->ReleaseElementIterator(elIter);
}

void StVKInternalForces::AddCubicTermsContribution(const double * vertexDisplacements, double * forces, int elementLow, int elementHigh)
{
  if (elementLow < 0)
    elementLow = 0;
  if (elementHigh < 0)
    elementHigh = volumetricMesh->getNumElements();

  int * vertices = (int*) malloc (sizeof(int) * numElementVertices);

  void * elIter;
  precomputedIntegrals->AllocateElementIterator(&elIter);

  for(int el=elementLow; el < elementHigh; el++)
  {
    precomputedIntegrals->PrepareElement(el, elIter);

    for(int ver=0; ver<numElementVertices; ver++)
      vertices[ver] = volumetricMesh->getVertexIndex(el, ver);

    double lambda = lambdaLame[el]; 
    double mu = muLame[el];

    for (int c=0; c<numElementVertices; c++) // over all vertices of the voxel, computing force on vertex c
    {
      int vc = vertices[c];
      // cubic terms
      for(int a=0; a<numElementVertices; a++) // over all vertices
      {
        int va = vertices[a];
        for(int b=0; b<numElementVertices; b++)
        {
          int vb = vertices[b];
          for(int d=0; d<numElementVertices; d++)
          {
            int vd = vertices[d];
/*
            Vec3d qa(vertexDisplacements[3*va+0],
                     vertexDisplacements[3*va+1],
                     vertexDisplacements[3*va+2]);

            Vec3d qb(vertexDisplacements[3*vb+0],
                     vertexDisplacements[3*vb+1],
                     vertexDisplacements[3*vb+2]);

            Vec3d qd(vertexDisplacements[3*vd+0],
                     vertexDisplacements[3*vd+1],
                     vertexDisplacements[3*vd+2]);

            double dotp = dot(qa,qb);

            Vec3d force = 0.5 * lambda * dotp * precomputedIntegrals_->D(a,b,c,d) * qd +
                          mu * dotp * precomputedIntegrals_->D(a,c,b,d) * qd;

            forces[3*vertices[c]+0] += force[0];
            forces[3*vertices[c]+1] += force[1];
            forces[3*vertices[c]+2] += force[2];
*/
            const double * qa = &(vertexDisplacements[3*va]);
            const double * qb = &(vertexDisplacements[3*vb]);
            const double * qd = &(vertexDisplacements[3*vd]);
            double * force = &(forces[3*vc]);

            double dotp = qa[0] * qb[0] + qa[1] * qb[1] + qa[2] * qb[2]; 
            double scalar = dotp * (0.5 * lambda * precomputedIntegrals->D(elIter,a,b,c,d) + mu * precomputedIntegrals->D(elIter,a,c,b,d) );

            force[0] += scalar * qd[0];
            force[1] += scalar * qd[1];
            force[2] += scalar * qd[2];
          }
        }
      }
    }
  }

  free(vertices);

  precomputedIntegrals->ReleaseElementIterator(elIter);
}

void StVKInternalForces::ResetVector(double * vec)
{
  memset(vec, 0, sizeof(double) * 3 * volumetricMesh->getNumVertices());
}

