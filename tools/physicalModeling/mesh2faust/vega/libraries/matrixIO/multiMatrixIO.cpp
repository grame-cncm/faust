/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "matrixIO" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC       *
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

/*
  Load/save multiple binary matrices from a single file.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "multiMatrixIO.h"

// for faster parallel loading of multimatrix binary files, enable the -fopenmp -DUSE_OPENMP macro line in the Makefile-header file (see also documentation)

#ifdef USE_OPENMP
  #include <omp.h>
#endif

int MultiMatrixIO::Save(const char * filename, int numMatrices, int * m, int * n, double ** matrices)
{
  FILE * fout = fopen(filename, "wb");
  if (fout == NULL)
  {
    printf("Error in MultiMatrixIO::Save: cannot open %s for writing.\n", filename);
    return 1;
  }

  // write the number of matrices
  fwrite(&numMatrices, sizeof(int), 1, fout);

  // write the dimensions of the matrices
  for(int i=0; i<numMatrices; i++)
  {
    fwrite(&m[i], sizeof(int), 1, fout);
    fwrite(&n[i], sizeof(int), 1, fout);
  }

  // write the matrices
  for(int i=0; i<numMatrices; i++)
  {
    fwrite(matrices[i], sizeof(double), m[i] * n[i], fout);
  }

  fclose(fout);

  return 0;
}

int MultiMatrixIO::Load(const char * filename, int * numMatrices, int ** m, int ** n, double *** matrices)
{
  FILE * fin = fopen(filename, "rb");
  if (fin == NULL)
  {
    printf("Error in MultiMatrixIO::Load: cannot open %s for reading.\n", filename);
    return 1;
  }

  // read number of matrices
  unsigned int items = fread(numMatrices, sizeof(int), 1, fin);
  if (items != 1)
  {
    printf("Error in MultiMatrixIO::Load: mismatch in the number of matrices.\n");
    return 1;
  }

  *m = (int*) malloc (sizeof(int) * (*numMatrices));
  *n = (int*) malloc (sizeof(int) * (*numMatrices));

  // read the matrix dimensions 
  for(int i=0; i<*numMatrices; i++)
  {
    items = fread(&((*m)[i]), sizeof(int), 1, fin);
    if (items != 1)
    {
      printf("Error in MultiMatrixIO::Load: mismatch in the number of matrices.\n");
      return 1;
    }

    items = fread(&((*n)[i]), sizeof(int), 1, fin);
    if (items != 1)
    {
      printf("Error in MultiMatrixIO::Load: mismatch in the number of matrices.\n");
      return 1;
    }
  }

  // allocate memory for matrices
  (*matrices) = (double **) malloc (sizeof(double*) * *numMatrices);
  unsigned int totalBytes = 0;
  unsigned int * offset = (unsigned int *) malloc (sizeof(unsigned int) * *numMatrices);
  offset[0] = 0;
  for(int i=0; i<*numMatrices; i++)
  {
    int numEntries = (*m)[i] * (*n)[i];
    if (numEntries > 0)
      (*matrices)[i] = (double *) malloc(sizeof(double) * numEntries);
    else
      (*matrices)[i] = NULL;
    offset[i] = totalBytes;
    totalBytes += sizeof(double) * numEntries;
  }

  // read the entire block of matrices
  unsigned char * mem = (unsigned char *) malloc (sizeof(unsigned char) * totalBytes);
  items = fread(mem, sizeof(unsigned char), totalBytes, fin);
  if (items != totalBytes)
  {
    printf("Error in MultiMatrixIO::Load: invalid number of bytes.\n");
    return 1;
  }
  fclose(fin);

  #ifdef USE_OPENMP
    #pragma omp parallel for
  #endif
  for(int i=0; i<*numMatrices; i++)
    memcpy((*matrices)[i], &mem[offset[i]], sizeof(double) * (*m)[i] * (*n)[i]);

  free(offset);
  free(mem);

  return 0;
}

