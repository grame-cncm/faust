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

#include "StVKStiffnessMatrix.h"
#include "volumetricMeshENuMaterial.h"

StVKStiffnessMatrix::StVKStiffnessMatrix(StVKInternalForces *  stVKInternalForces)
{
  precomputedIntegrals = stVKInternalForces->GetPrecomputedIntegrals();
  volumetricMesh = stVKInternalForces->GetVolumetricMesh();
  numElementVertices = volumetricMesh->getNumElementVertices();
  int numElements = volumetricMesh->getNumElements();

  lambdaLame = (double*) malloc (sizeof(double) * numElements);
  muLame = (double*) malloc (sizeof(double) * numElements);

  for(int el=0; el<numElements; el++)
  {
    VolumetricMesh::Material * material = volumetricMesh->getElementMaterial(el);
    VolumetricMesh::ENuMaterial * eNuMaterial = downcastENuMaterial(material);
    if (eNuMaterial == NULL)
    {
      printf("Error: StVKStiffnessMatrix: mesh does not consist of E, nu materials.\n");
      throw 1;
    }

    lambdaLame[el] = eNuMaterial->getLambda();
    muLame[el] = eNuMaterial->getMu();
  }

  // build stiffness matrix skeleton 
  SparseMatrix * stiffnessMatrixTopology;
  GetStiffnessMatrixTopology(&stiffnessMatrixTopology);

  // build acceleration indices
  row_ = (int**) malloc (sizeof(int*) * numElements);
  column_ = (int**) malloc (sizeof(int*) * numElements);

  for (int el=0; el < numElements; el++)
  {
    row_[el] = (int*) malloc (sizeof(int) * numElementVertices);
    column_[el] = (int*) malloc (sizeof(int) * numElementVertices * numElementVertices);

    for(int ver=0; ver<numElementVertices; ver++)
      row_[el][ver] = volumetricMesh->getVertexIndex(el, ver);

    // seek for value row[j] in list associated with row[i]
    for(int i=0; i<numElementVertices; i++)
      for(int j=0; j<numElementVertices; j++)
        column_[el][numElementVertices * i + j] =
          stiffnessMatrixTopology->GetInverseIndex(3*row_[el][i],3*row_[el][j]) / 3;
  }

  delete(stiffnessMatrixTopology);

}

void StVKStiffnessMatrix::GetStiffnessMatrixTopology(SparseMatrix ** stiffnessMatrixTopology)
{
  int numVertices = volumetricMesh->getNumVertices();

  int * vertices = (int*) malloc (sizeof(int) * numElementVertices);

  // build skeleton of sparseMatrix
  SparseMatrixOutline * emptyMatrix = new SparseMatrixOutline(3 * numVertices);
  for (int el=0; el < volumetricMesh->getNumElements(); el++)
  {
    //if(el % 100 == 1)
      //printf(".");

    for(int ver=0; ver<numElementVertices; ver++)
      vertices[ver] = volumetricMesh->getVertexIndex(el, ver);

    for (int i=0; i<numElementVertices; i++)
      for (int j=0; j<numElementVertices; j++)
      {
        for(int k=0; k<3; k++)
          for(int l=0; l<3; l++)
          {
            // only add the entry if both vertices are free (non-fixed)
            // the corresponding elt is in row 3*i+k, column 3*j+l
            emptyMatrix->AddEntry( 3*vertices[i]+k, 3*vertices[j]+l, 0.0 );
          }
      }
  }
  //printf("\n");

  *stiffnessMatrixTopology = new SparseMatrix(emptyMatrix);
  delete(emptyMatrix);

  free(vertices);
}

StVKStiffnessMatrix::~StVKStiffnessMatrix()
{
  int numElements = volumetricMesh->getNumElements();

  for(int i=0; i<numElements; i++)
    free(row_[i]);
  free(row_);

  for(int i=0; i<numElements; i++)
    free(column_[i]);
  free(column_);

  free(lambdaLame);
  free(muLame);
}

// the master function
void StVKStiffnessMatrix::ComputeStiffnessMatrix(const double * vertexDisplacements, SparseMatrix * sparseMatrix)
{
  //PerformanceCounter stiffnessCounter;
  sparseMatrix->ResetToZero();

  AddLinearTermsContribution(vertexDisplacements, sparseMatrix);
  AddQuadraticTermsContribution(vertexDisplacements, sparseMatrix);
  AddCubicTermsContribution(vertexDisplacements, sparseMatrix);

  //stiffnessCounter.StopCounter();
  //printf("Stiffness matrix: %G\n", stiffnessCounter.GetElapsedTime());
}

void StVKStiffnessMatrix::AddLinearTermsContribution(const double * vertexDisplacements, SparseMatrix * sparseMatrix, int elementLow, int elementHigh)
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

    for (int c=0; c<numElementVertices; c++) // over all vertices of the voxel, computing row of vertex c
    {
      // linear terms
      for (int a=0; a<numElementVertices; a++) // over all vertices
      {
        Mat3d matrix(1.0);
        matrix *= mu * precomputedIntegrals->B(elIter,a,c);
        matrix += lambda * precomputedIntegrals->A(elIter,c,a) +
                  mu * precomputedIntegrals->A(elIter,a,c);

        AddMatrix3x3Block(c, a, el, matrix, sparseMatrix);
      }
    }
  }

  free(vertices);

  precomputedIntegrals->ReleaseElementIterator(elIter);
}

#define ADD_MATRIX_BLOCK(where)\
  for(k=0; k<3; k++)\
    for(l=0; l<3; l++)\
    {\
      dataHandle[rowc+k][3*column[c8+(where)]+l] += matrix[3*k+l];\
    }

void StVKStiffnessMatrix::AddQuadraticTermsContribution(const double * vertexDisplacements, SparseMatrix * sparseMatrix, int elementLow, int elementHigh)
{
  if (elementLow < 0)
    elementLow = 0;
  if (elementHigh < 0)
    elementHigh = volumetricMesh->getNumElements();

  int * vertices = (int*) malloc (sizeof(int) * numElementVertices);

  void * elIter;
  precomputedIntegrals->AllocateElementIterator(&elIter);

  double ** dataHandle = sparseMatrix->GetDataHandle();

  for(int el=elementLow; el < elementHigh; el++)
  {
    precomputedIntegrals->PrepareElement(el, elIter);
    int * row = row_[el];
    int * column = column_[el];

    for(int ver=0; ver<numElementVertices; ver++)
      vertices[ver] = volumetricMesh->getVertexIndex(el, ver);

    double lambda = lambdaLame[el]; 
    double mu = muLame[el];

    for (int c=0; c<numElementVertices; c++) // over all vertices of the voxel, computing row of vertex c
    {
      int rowc = 3*row[c];
      int c8 = numElementVertices*c;
      // quadratic terms
      for (int e=0; e<numElementVertices; e++) // compute contribution to block (c,e) of the stiffness matrix
      {
        double matrix[9];
        memset(matrix, 0, sizeof(double) * 9);
        for(int a=0; a<numElementVertices; a++)
        {
          double qa[3] = { vertexDisplacements[3*vertices[a]+0], vertexDisplacements[3*vertices[a]+1], vertexDisplacements[3*vertices[a]+2] };

          Vec3d C0v = lambda * precomputedIntegrals->C(elIter,c,a,e) + mu * (precomputedIntegrals->C(elIter,e,a,c) + precomputedIntegrals->C(elIter,a,e,c));
          double C0[3] = {C0v[0], C0v[1], C0v[2]};

          // C0 tensor qa
          matrix[0] += C0[0] * qa[0]; matrix[1] += C0[0] * qa[1]; matrix[2] += C0[0] * qa[2];
          matrix[3] += C0[1] * qa[0]; matrix[4] += C0[1] * qa[1]; matrix[5] += C0[1] * qa[2];
          matrix[6] += C0[2] * qa[0]; matrix[7] += C0[2] * qa[1]; matrix[8] += C0[2] * qa[2];

          Vec3d C1v = lambda * precomputedIntegrals->C(elIter,e,a,c) + mu * (precomputedIntegrals->C(elIter,c,e,a) + precomputedIntegrals->C(elIter,a,e,c));
          double C1[3] = {C1v[0], C1v[1], C1v[2]};

          // qa tensor C1
          matrix[0] += qa[0] * C1[0]; matrix[1] += qa[0] * C1[1]; matrix[2] += qa[0] * C1[2];
          matrix[3] += qa[1] * C1[0]; matrix[4] += qa[1] * C1[1]; matrix[5] += qa[1] * C1[2];
          matrix[6] += qa[2] * C1[0]; matrix[7] += qa[2] * C1[1]; matrix[8] += qa[2] * C1[2];

          Vec3d C2v = lambda * precomputedIntegrals->C(elIter,a,e,c) + mu * (precomputedIntegrals->C(elIter,c,a,e) + precomputedIntegrals->C(elIter,e,a,c));
          double C2[3] = {C2v[0], C2v[1], C2v[2]};

          // qa dot C2
          double dotp = qa[0]*C2[0] + qa[1]*C2[1] + qa[2]*C2[2];
          matrix[0] += dotp; 
          matrix[4] += dotp; 
          matrix[8] += dotp; 

        }
        int k,l;
        ADD_MATRIX_BLOCK(e);
      }
    }
  }

  free(vertices);

  precomputedIntegrals->ReleaseElementIterator(elIter);
}

void StVKStiffnessMatrix::AddCubicTermsContribution(const double * vertexDisplacements, SparseMatrix * sparseMatrix, int elementLow, int elementHigh)
{
  if (elementLow < 0)
    elementLow = 0;
  if (elementHigh < 0)
    elementHigh = volumetricMesh->getNumElements();

  int * vertices = (int*) malloc (sizeof(int) * numElementVertices);

  void * elIter;
  precomputedIntegrals->AllocateElementIterator(&elIter);

  double ** dataHandle = sparseMatrix->GetDataHandle();

  for(int el=elementLow; el < elementHigh; el++)
  {
    precomputedIntegrals->PrepareElement(el, elIter);
    int * row = row_[el];
    int * column = column_[el];

    for(int ver=0; ver<numElementVertices; ver++)
      vertices[ver] = volumetricMesh->getVertexIndex(el, ver);

    double lambda = lambdaLame[el]; 
    double mu = muLame[el];

    for (int c=0; c<numElementVertices; c++) // over all vertices of the voxel, computing derivative on force on vertex c
    {
      int rowc = 3*row[c];
      int c8 = numElementVertices*c;
      // cubic terms
      for (int e=0; e<numElementVertices; e++) // compute contribution to block (c,e) of the stiffness matrix
      {
        double matrix[9];
        memset(matrix, 0, sizeof(double) * 9);
        for(int a=0; a<numElementVertices; a++)
        {
          int va = vertices[a];
          const double * qa = &(vertexDisplacements[3*va]);
          for(int b=0; b<numElementVertices; b++)
          {
            int vb = vertices[b];

            const double * qb = &(vertexDisplacements[3*vb]);

            double D0 = lambda * precomputedIntegrals->D(elIter,a,c,b,e) +
                        mu * ( precomputedIntegrals->D(elIter,a,e,b,c) + precomputedIntegrals->D(elIter,a,b,c,e) );

            matrix[0] += D0 * qa[0] * qb[0]; matrix[1] += D0 * qa[0] * qb[1]; matrix[2] += D0 * qa[0] * qb[2];
            matrix[3] += D0 * qa[1] * qb[0]; matrix[4] += D0 * qa[1] * qb[1]; matrix[5] += D0 * qa[1] * qb[2];
            matrix[6] += D0 * qa[2] * qb[0]; matrix[7] += D0 * qa[2] * qb[1]; matrix[8] += D0 * qa[2] * qb[2];

            double D1 = 0.5 * lambda * precomputedIntegrals->D(elIter,a,b,c,e) +
                        mu * precomputedIntegrals->D(elIter,a,c,b,e);

            double dotpD = D1 * (qa[0] * qb[0] + qa[1] * qb[1] + qa[2] * qb[2]);

            matrix[0] += dotpD; 
            matrix[4] += dotpD; 
            matrix[8] += dotpD; 
          }
        }
        int k,l;
        ADD_MATRIX_BLOCK(e);
      }
    }
  }

  free(vertices);

  precomputedIntegrals->ReleaseElementIterator(elIter);
}

