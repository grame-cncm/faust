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

#include "StVKHessianTensor.h"
#include "volumetricMeshENuMaterial.h"

#define QUADRATICFORM(m,x,y)\
  m[0] * x[0] * y[0] + \
  m[1] * x[1] * y[0] + \
  m[2] * x[2] * y[0] + \
  m[3] * x[0] * y[1] + \
  m[4] * x[1] * y[1] + \
  m[5] * x[2] * y[1] + \
  m[6] * x[0] * y[2] + \
  m[7] * x[1] * y[2] + \
  m[8] * x[2] * y[2]

#define TENSOR3_INDEX(i,j,k) (9*(i)+3*(j)+(k))

#define ADD_CONTRIB(aa,bb,cc)\
  v1 = vertices[(aa)];\
  v2 = vertices[(bb)];\
  v3 = vertices[(cc)];\
  phirj = &phir[3*v2];\
  phisk = &phis[3*v3];\
  result[3*v1+0] += QUADRATICFORM(hijk0,phisk,phirj);\
  result[3*v1+1] += QUADRATICFORM(hijk1,phisk,phirj);\
  result[3*v1+2] += QUADRATICFORM(hijk2,phisk,phirj);

#define ADD_CONTRIB_ALL(aa,bb,cc)\
  v1 = vertices[(aa)];\
  v2 = vertices[(bb)];\
  v3 = vertices[(cc)];\
  for(int ii=0; ii<k-numRigidModes; ii++)\
    for(int jj=ii; jj<k-numRigidModes; jj++)\
    {\
      int derivPos = ii * (k-numRigidModes) - ii * (ii+1) / 2 + jj;\
      phirj = &Ulin[m3*(numRigidModes+ii) + 3*v2];\
      phisk = &Ulin[m3*(numRigidModes+jj) + 3*v3];\
      result[m3*derivPos + 3*v1+0] += QUADRATICFORM(hijk0,phisk,phirj);\
      result[m3*derivPos + 3*v1+1] += QUADRATICFORM(hijk1,phisk,phirj);\
      result[m3*derivPos + 3*v1+2] += QUADRATICFORM(hijk2,phisk,phirj);\
    }

StVKHessianTensor::StVKHessianTensor(StVKStiffnessMatrix * stVKStiffnessMatrix_): stVKStiffnessMatrix(stVKStiffnessMatrix_), volumetricMesh(stVKStiffnessMatrix->GetVolumetricMesh()), precomputedIntegrals(stVKStiffnessMatrix->GetPrecomputedIntegrals())
{
  numVertices_ = volumetricMesh->getNumVertices();
  numElements_ = volumetricMesh->getNumElements();
  numElementVertices = volumetricMesh->getNumElementVertices();

  lambdaLame = (double*) malloc (sizeof(double) * numElements_);
  muLame = (double*) malloc (sizeof(double) * numElements_);

  for(int el=0; el<numElements_; el++)
  {
    VolumetricMesh::Material * material = volumetricMesh->getElementMaterial(el);
    VolumetricMesh::ENuMaterial * eNuMaterial = downcastENuMaterial(material);
    if (eNuMaterial == NULL)
    {
      printf("Error: StVKHessianTensor: mesh does not consist of E, nu materials.\n");
      throw 1;
    }

    lambdaLame[el] = eNuMaterial->getLambda();
    muLame[el] = eNuMaterial->getMu();
  }
}

StVKHessianTensor::~StVKHessianTensor()
{
  free(lambdaLame);
  free(muLame);
}

void StVKHessianTensor::AddTensor3x3x3Block(int v1, int v2, int v3, Vec3d & vec, int type)
{

  #define TENSOR3_INDEX(i,j,k) (9*(i)+3*(j)+(k))

  // seek for the Hessian term
  double * entry = NULL;

  hessianType::iterator pos;
  pos = hessian.find(triIndex(v1,v2,v3));

  if (pos == hessian.end())
  {
    // data is new
    entry = (double*) calloc (27,sizeof(double));
    hessian.insert(std::make_pair(triIndex(v1,v2,v3),entry));
  }
  else
  {
    // data already exists
    entry = pos->second;
  }

  // modify entry as necessary

  switch (type)
  {
    case 1: // vec tensor u

    for(int j=0; j<3; j++)
      for(int i=0; i<3; i++)
        entry[TENSOR3_INDEX(i,j,j)] += vec[i];

    break;

    case 2: // u tensor vec

    for(int j=0; j<3; j++)
      for(int i=0; i<3; i++)
        entry[TENSOR3_INDEX(j,i,j)] += vec[i];

    break;

    case 3: // <u,vec>I

    for(int j=0; j<3; j++)
      for(int i=0; i<3; i++)
        entry[TENSOR3_INDEX(j,j,i)] += vec[i];

    break;

    default:
      printf("Error: type with tensor3 invalid.\n");
  }
}


int StVKHessianTensor::ComputeHessianAtZero(int verbose)
{
  if (verbose)
    printf("Computing Hessian at zero... Total num elements: %d \n", numElements_);

  int * vertices = (int*) malloc (sizeof(int) * numElementVertices);

  void * elIter;
  precomputedIntegrals->AllocateElementIterator(&elIter);

  hessian.clear();

  for(int el=0; el < numElements_; el++)
  {
    precomputedIntegrals->PrepareElement(el, elIter);

    if (verbose && (el % 100 == 1))
    {
      printf("%d ",el);
      fflush(NULL);
    }

    for(int ver=0; ver<numElementVertices ;ver++)
      vertices[ver] = volumetricMesh->getVertexIndex(el, ver);

    double lambda = lambdaLame[el]; 
    double mu = muLame[el];

    for (int c=0; c<numElementVertices; c++) // over all vertices of the voxel, computing force on vertex c
    {
      // quadratic terms
      int a,b;
      for (a=0; a<numElementVertices; a++) // over all vertices
        for(b=0; b<numElementVertices; b++)
        {
          Vec3d D = 0.5 * lambda * precomputedIntegrals->C(elIter,c,a,b) +
                    mu * precomputedIntegrals->C(elIter,a,b,c);

          // tensorProduct(D,qb);
          AddTensor3x3x3Block(vertices[c], vertices[a], vertices[b], D, 1);

          // tensorProduct(D,qa);
          AddTensor3x3x3Block(vertices[c], vertices[b], vertices[a], D, 1);

          Vec3d C = lambda * precomputedIntegrals->C(elIter,a,b,c) +
                    mu * (precomputedIntegrals->C(elIter,c,a,b) + precomputedIntegrals->C(elIter,b,a,c));

          // tensorProduct(qb,C);
          AddTensor3x3x3Block(vertices[c], vertices[a], vertices[b], C, 2);

          // <qa,C> I
          AddTensor3x3x3Block(vertices[c], vertices[b], vertices[a], C, 3);
        }
    }
  }

  free(vertices);

  precomputedIntegrals->ReleaseElementIterator(elIter);

  if (verbose)
    printf("\n");

  return 0;
}

void StVKHessianTensor::EvaluateHessianQuadraticForm(double * phir, double * phis, double * result)
{
  // reset result to zero
  memset(result,0,sizeof(double)*3*numVertices_);

  int i,j,k;

  hessianType::iterator pos;

  for (pos = hessian.begin(); pos != hessian.end(); pos++)
  {
    triIndex index = pos->first;
    i = index.first;
    j = index.second;
    k = index.third;
    double * entry = pos->second;

    double * phisk = &phis[3*k];
    double * phirj = &phir[3*j];

    double * hijk0 = &entry[0];
    double * hijk1 = &entry[9];
    double * hijk2 = &entry[18];

    // compute quadratic forms
    double value0 = QUADRATICFORM(hijk0,phisk,phirj);
    double value1 = QUADRATICFORM(hijk1,phisk,phirj);
    double value2 = QUADRATICFORM(hijk2,phisk,phirj);

    result[3*i+0] += value0;
    result[3*i+1] += value1;
    result[3*i+2] += value2;
  }
}

int StVKHessianTensor::SaveHessianAtZeroToFile(const char * filename)
{
  FILE * fout = fopen(filename,"wb");

  if (!fout)
  {
    printf("Error: couldn't write to file %s.\n",filename);
    return 1;
  }

  size_t hessianSize = hessian.size();
  if ((int)(fwrite(&hessianSize,sizeof(int),1,fout)) < 1)
    return 1;

  hessianType::iterator pos;

  for (pos = hessian.begin(); pos != hessian.end(); pos++)
  {
    triIndex index = pos->first;
    int data0 = index.first;
    int data1 = index.second;
    int data2 = index.third;

    if ((int)(fwrite(&data0,sizeof(int),1,fout)) < 1)
      return 1;

    if ((int)(fwrite(&data1,sizeof(int),1,fout)) < 1)
      return 1;

    if ((int)(fwrite(&data2,sizeof(int),1,fout)) < 1)
      return 1;

    double * entry = pos->second;
    for(int j=0; j<27; j++)
    {
      double entry0 = entry[j];
      if ((int)(fwrite(&entry0,sizeof(double),1,fout)) < 1)
        return 1;
    }
  }

  fclose(fout);

  return 0;
}

void StVKHessianTensor::EvaluateHessianQuadraticFormDirect(double * phir, double * phis, double * result)
{
  double entry[27];
  double * hijk0 = &entry[0];
  double * hijk1 = &entry[9];
  double * hijk2 = &entry[18];

  double * phisk;
  double * phirj;

  int v1,v2,v3;

  int i,j;

  // reset result to zero
  memset(result,0,sizeof(double)*3*numVertices_);

  int * vertices = (int*) malloc (sizeof(int) * numElementVertices);

  void * elIter;
  precomputedIntegrals->AllocateElementIterator(&elIter);

  printf("Evaluating Hessian Quadratic Form (rhs matrix)... Total num elements: %d \n",numElements_);

  for(int el=0; el < numElements_; el++)
  {
    precomputedIntegrals->PrepareElement(el, elIter);
    if (el % 500 == 1)
      printf("%d ",el);

    for(int ver=0; ver<numElementVertices; ver++)
      vertices[ver] = volumetricMesh->getVertexIndex(el, ver);

    double lambda = lambdaLame[el]; 
    double mu = muLame[el];

    for (int c=0; c<numElementVertices; c++) // over all vertices of the voxel, computing force on vertex c
    {
      // quadratic terms
      int a,b;
      for (a=0; a<numElementVertices; a++) // over all vertices
        for(b=0; b<numElementVertices; b++)
        {
          Vec3d D = 0.5 * lambda * precomputedIntegrals->C(elIter,c,a,b) +
                    mu * precomputedIntegrals->C(elIter,a,b,c);

          // tensorProduct(D,qb);
          //AddTensor3x3x3BlockContributionToQuadraticForm(vertices[c], vertices[a], vertices[b], D, 1, phir, phis, result);

          // tensorProduct(D,qa);
          //AddTensor3x3x3BlockContributionToQuadraticForm(vertices[c], vertices[b], vertices[a], D, 1, phir, phis, result);

          memset(entry,0,sizeof(double)*27);
          for(j=0; j<3; j++)
            for(i=0; i<3; i++)
              entry[TENSOR3_INDEX(i,j,j)] += D[i];

          ADD_CONTRIB(c,a,b);
          ADD_CONTRIB(c,b,a);

          //-------

          Vec3d C = lambda * precomputedIntegrals->C(elIter,a,b,c) +
                    mu * (precomputedIntegrals->C(elIter,c,a,b) + precomputedIntegrals->C(elIter,b,a,c)); 

          // tensorProduct(qb,C);
          //AddTensor3x3x3BlockContributionToQuadraticForm(vertices[c], vertices[a], vertices[b], C, 2, phir, phis, result);

          memset(entry,0,sizeof(double)*27);
          for(j=0; j<3; j++)
            for(i=0; i<3; i++)
              entry[TENSOR3_INDEX(j,i,j)] += C[i];

          ADD_CONTRIB(c,a,b);

          //-------

          // <qa,C> I
          //AddTensor3x3x3BlockContributionToQuadraticForm(vertices[c], vertices[b], vertices[a], C, 3, phir, phis, result);

          memset(entry,0,sizeof(double)*27);
          for(j=0; j<3; j++)
            for(i=0; i<3; i++)
              entry[TENSOR3_INDEX(j,j,i)] += C[i];

          ADD_CONTRIB(c,b,a);
        }
    }
  }

  free(vertices);

  precomputedIntegrals->ReleaseElementIterator(elIter);

  printf("\n");
}

void StVKHessianTensor::EvaluateHessianQuadraticFormDirectAll(double * Ulin, int k, double * result, int numRigidModes, int verbose)
{
  double entry[27];
  double * hijk0 = &entry[0];
  double * hijk1 = &entry[9];
  double * hijk2 = &entry[18];

  double * phisk;
  double * phirj;

  int v1,v2,v3;

  // reset result to zero
  int numDeriv = (k-numRigidModes) * (k-numRigidModes+1) / 2; 
  int m3 = 3*numVertices_;

  memset(result,0,sizeof(double)*m3*numDeriv);

  int * vertices = (int*) malloc (sizeof(int) * numElementVertices);

  void * elIter;
  precomputedIntegrals->AllocateElementIterator(&elIter);

  if (verbose)
  {
    printf("Evaluating the Hessian quadratic form (rhs matrix)...\n");
    printf("  Total num elements: %d \n",numElements_);
    printf("  Total num DOFs: %d \n",m3);
    printf("  Total num linear modes: %d \n",k);
    printf("  Total num rigid modes: %d \n",numRigidModes);
    printf("  Total num derivatives: %d \n",numDeriv);
  }

  for(int el=0; el < numElements_; el++)
  {
    precomputedIntegrals->PrepareElement(el, elIter);
    if ((el % 200 == 0) && (verbose))
    {
      printf("%d ",el);
      fflush(NULL);
    }
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
          Vec3d D = lambda * precomputedIntegrals->C(elIter,c,a,b) + 
                    mu * (precomputedIntegrals->C(elIter,a,b,c) + precomputedIntegrals->C(elIter,b,a,c));

          // tensorProduct(D,qb);
          //AddTensor3x3x3BlockContributionToQuadraticForm(vertices[c], vertices[a], vertices[b], D, 1, phir, phis, result);

          // tensorProduct(D,qa);
          //AddTensor3x3x3BlockContributionToQuadraticForm(vertices[c], vertices[b], vertices[a], D, 1, phir, phis, result);

          memset(entry,0,sizeof(double)*27);
          for(int j=0; j<3; j++)
            for(int i=0; i<3; i++)
              entry[TENSOR3_INDEX(i,j,j)] += D[i];

          ADD_CONTRIB_ALL(c,a,b);

          //-------

          Vec3d C = lambda * precomputedIntegrals->C(elIter,a,b,c) +
                    mu * (precomputedIntegrals->C(elIter,c,a,b) + 
                          precomputedIntegrals->C(elIter,b,a,c)); 

          // tensorProduct(qb,C);
          //AddTensor3x3x3BlockContributionToQuadraticForm(vertices[c], vertices[a], vertices[b], C, 2, phir, phis, result);

          memset(entry,0,sizeof(double)*27);
          for(int j=0; j<3; j++)
            for(int i=0; i<3; i++)
              entry[TENSOR3_INDEX(j,i,j)] += C[i];

          ADD_CONTRIB_ALL(c,a,b);

          //-------

          // <qa,C> I
          //AddTensor3x3x3BlockContributionToQuadraticForm(vertices[c], vertices[b], vertices[a], C, 3, phir, phis, result);

          memset(entry,0,sizeof(double)*27);
          for(int j=0; j<3; j++)
            for(int i=0; i<3; i++)
              entry[TENSOR3_INDEX(j,j,i)] += C[i];

          ADD_CONTRIB_ALL(c,b,a);
       }
    } 
  }

  free(vertices);

  precomputedIntegrals->ReleaseElementIterator(elIter);

  if (verbose)
    printf("\n");
}

void StVKHessianTensor::ComputeStiffnessMatrixCorrection(double * u, double * du, SparseMatrix * dK)
{
  dK->ResetToZero();
  AddQuadraticTermsContribution(u, du, dK);
  AddCubicTermsContribution(u, du, dK);
}

#define ADD_MATRIX_BLOCK(where)\
  for(k=0; k<3; k++)\
    for(l=0; l<3; l++)\
    {\
      dataHandle[rowc+k][3*column[c8+(where)]+l] += matrix[3*k+l];\
    }

void StVKHessianTensor::AddQuadraticTermsContribution(double * u, double * du, SparseMatrix * dK, int elementLow, int elementHigh) 
{
  if (elementLow < 0)
    elementLow = 0;
  if (elementHigh < 0)
    elementHigh = volumetricMesh->getNumElements();

  int ** row_, ** column_;
  stVKStiffnessMatrix->GetMatrixAccelerationIndices(&row_, &column_);

  int * vertices = (int*) malloc (sizeof(int) * numElementVertices);

  void * elIter;
  precomputedIntegrals->AllocateElementIterator(&elIter);

  double ** dataHandle = dK->GetDataHandle();

  for(int el=elementLow; el < elementHigh; el++)
  {
    precomputedIntegrals->PrepareElement(el, elIter);
    int * row = row_[el];
    int * column = column_[el];

    for(int ver=0; ver<numElementVertices ;ver++)
      vertices[ver] = volumetricMesh->getVertexIndex(el, ver);

    double lambda = lambdaLame[el]; 
    double mu = muLame[el];

    for (int c=0; c<numElementVertices; c++) // over all vertices of the voxel
    {
      int rowc = 3*row[c];
      int c8 = numElementVertices*c;
      for (int e=0; e<numElementVertices; e++) // compute contribution to block (c,e) of dK
      {
        double matrix[9];
        memset(matrix, 0, sizeof(double) * 9);
        for(int f=0; f<numElementVertices; f++)
        {
          double qf[3] = { du[3*vertices[f]+0], du[3*vertices[f]+1], du[3*vertices[f]+2] };
          
          Vec3d C0v = lambda * precomputedIntegrals->C(elIter,c,f,e) + mu * (precomputedIntegrals->C(elIter,e,f,c) + precomputedIntegrals->C(elIter,f,e,c));
          double C0[3] = {C0v[0], C0v[1], C0v[2]};

          // C0 tensor qf
          matrix[0] += C0[0] * qf[0]; matrix[1] += C0[0] * qf[1]; matrix[2] += C0[0] * qf[2];
          matrix[3] += C0[1] * qf[0]; matrix[4] += C0[1] * qf[1]; matrix[5] += C0[1] * qf[2];
          matrix[6] += C0[2] * qf[0]; matrix[7] += C0[2] * qf[1]; matrix[8] += C0[2] * qf[2];

          Vec3d C1v = lambda * precomputedIntegrals->C(elIter,e,f,c) + mu * (precomputedIntegrals->C(elIter,c,e,f) + precomputedIntegrals->C(elIter,f,e,c));
          double C1[3] = {C1v[0], C1v[1], C1v[2]};

          // qf tensor C1
          matrix[0] += qf[0] * C1[0]; matrix[1] += qf[0] * C1[1]; matrix[2] += qf[0] * C1[2];
          matrix[3] += qf[1] * C1[0]; matrix[4] += qf[1] * C1[1]; matrix[5] += qf[1] * C1[2];
          matrix[6] += qf[2] * C1[0]; matrix[7] += qf[2] * C1[1]; matrix[8] += qf[2] * C1[2];

          Vec3d C2v = lambda * precomputedIntegrals->C(elIter,f,e,c) + mu * (precomputedIntegrals->C(elIter,c,f,e) + precomputedIntegrals->C(elIter,e,f,c));
          double C2[3] = {C2v[0], C2v[1], C2v[2]};

          // qf dot C2
          double dotp = qf[0]*C2[0] + qf[1]*C2[1] + qf[2]*C2[2];
          matrix[0] += dotp;
          matrix[4] += dotp;
          matrix[8] += dotp;
        }
        int k,l;
        ADD_MATRIX_BLOCK(e);
      }
    }
  }

  precomputedIntegrals->ReleaseElementIterator(elIter);

  free(vertices);
}

void StVKHessianTensor::AddCubicTermsContribution(double * u, double * du, SparseMatrix * dK, int elementLow, int elementHigh)
{
  if (elementLow < 0)
    elementLow = 0;
  if (elementHigh < 0)
    elementHigh = volumetricMesh->getNumElements();

  int ** row_, ** column_;
  stVKStiffnessMatrix->GetMatrixAccelerationIndices(&row_, &column_);

  int * vertices = (int*) malloc (sizeof(int) * numElementVertices);

  void * elIter;
  precomputedIntegrals->AllocateElementIterator(&elIter);

  double ** dataHandle = dK->GetDataHandle();

  for(int el=elementLow; el < elementHigh; el++)
  {
    precomputedIntegrals->PrepareElement(el, elIter);
    int * row = row_[el];
    int * column = column_[el];

    for(int ver=0; ver<numElementVertices ;ver++)
      vertices[ver] = volumetricMesh->getVertexIndex(el, ver);

    double lambda = lambdaLame[el]; 
    double mu = muLame[el];

    for (int c=0; c<numElementVertices; c++) // over all vertices of the voxel
    {
      int rowc = 3*row[c];
      int c8 = numElementVertices*c;
      for (int e=0; e<numElementVertices; e++) // compute contribution to block (c,e) of dK
      {
        double matrix[9];
        memset(matrix, 0, sizeof(double) * 9);
        for(int f=0; f<numElementVertices; f++)
        {
          double qf[3] = { du[3*vertices[f]+0], du[3*vertices[f]+1], du[3*vertices[f]+2] };
          for(int a=0; a<numElementVertices; a++)
          {
            double qa[3] = { u[3*vertices[a]+0], u[3*vertices[a]+1], u[3*vertices[a]+2] };

            // qa tensor qf
            double qaqf[9];
            qaqf[0] = qa[0] * qf[0]; qaqf[1] = qa[0] * qf[1]; qaqf[2] = qa[0] * qf[2];
            qaqf[3] = qa[1] * qf[0]; qaqf[4] = qa[1] * qf[1]; qaqf[5] = qa[1] * qf[2];
            qaqf[6] = qa[2] * qf[0]; qaqf[7] = qa[2] * qf[1]; qaqf[8] = qa[2] * qf[2];

            double D0 = lambda * precomputedIntegrals->D(elIter,f,c,a,e) + mu * (precomputedIntegrals->D(elIter,f,e,a,c) + precomputedIntegrals->D(elIter,f,a,c,e));

            matrix[0] += D0 * qaqf[0]; matrix[1] += D0 * qaqf[3]; matrix[2] += D0 * qaqf[6];
            matrix[3] += D0 * qaqf[1]; matrix[4] += D0 * qaqf[4]; matrix[5] += D0 * qaqf[7];
            matrix[6] += D0 * qaqf[2]; matrix[7] += D0 * qaqf[5]; matrix[8] += D0 * qaqf[8];

            double D1 = lambda * precomputedIntegrals->D(elIter,a,c,f,e) + mu * (precomputedIntegrals->D(elIter,a,e,f,c) + precomputedIntegrals->D(elIter,a,f,c,e));

            matrix[0] += D1 * qaqf[0]; matrix[1] += D1 * qaqf[1]; matrix[2] += D1 * qaqf[2];
            matrix[3] += D1 * qaqf[3]; matrix[4] += D1 * qaqf[4]; matrix[5] += D1 * qaqf[5];
            matrix[6] += D1 * qaqf[6]; matrix[7] += D1 * qaqf[7]; matrix[8] += D1 * qaqf[8];

            double D2 = lambda * precomputedIntegrals->D(elIter,f,a,c,e) + mu * (precomputedIntegrals->D(elIter,f,c,a,e) + precomputedIntegrals->D(elIter,a,c,f,e));

            // qf dot qa
            double dotp = D2 * (qf[0]*qa[0] + qf[1]*qa[1] + qf[2]*qa[2]);
            matrix[0] += dotp;
            matrix[4] += dotp;
            matrix[8] += dotp;
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


