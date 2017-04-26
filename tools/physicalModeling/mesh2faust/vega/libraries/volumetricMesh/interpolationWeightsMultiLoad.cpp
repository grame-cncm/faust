/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "reducedStvk" library , Copyright (C) 2007 CMU, 2009 MIT              *
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
  Load/save many sets of interpolation weights from one file.
*/

#include <stdio.h>
#include "interpolationWeightsMultiLoad.h"
#include "volumetricMesh.h"
#include "vegalong.h"

// input: filename, numModels
// output: numTargetLocations, numElementVertices, vertices, weights
int multiLoadInterpolationWeightsBinary(const char * filename, int * numModels, int ** numTargetLocations, int ** numElementVertices, int *** vertices, double *** weights) // binary version; returns 0 on success
{
  FILE * fin = fopen(filename, "rb");
  if (!fin)
  {
    printf("Error: unable to open file %s.\n", filename);
    return 1;
  }

  int readItems = (int) fread(numModels, sizeof(int), 1, fin);
  if (readItems < 1)
  {
    printf("Error: unable to read from file %s.\n", filename);
    return 1;
  }

  (*numTargetLocations) = (int*) malloc (sizeof(int) * *numModels);
  (*numElementVertices) = (int*) malloc (sizeof(int) * *numModels);
  (*vertices) = (int**) malloc (sizeof(int*) * *numModels);
  (*weights) = (double**) malloc (sizeof(double*) * *numModels);

  vegaunsignedlong * header = (vegaunsignedlong*) malloc (sizeof(vegaunsignedlong) * *numModels); // we only read the header, but don't use it

  readItems = (int) fread(header, sizeof(vegaunsignedlong), *numModels, fin);
  if (readItems < *numModels)
  {
    printf("Error: unable to read from file %s.\n", filename);
    return 1;
  }
  free(header);

  int code = 0;
  for(int i=0; i<*numModels; i++)
    code = code | VolumetricMesh::loadInterpolationWeightsBinary(fin, &(*numTargetLocations)[i], &(*numElementVertices)[i], &(*vertices)[i], &(*weights)[i]);

  fclose(fin);

  return code;
}

// input: filename, numTargetLocations (array), numElementVertices (array), vertices, weights
int multiSaveInterpolationWeightsBinary(const char * filename, int numModels, int * numTargetLocations, int * numElementVertices, int ** vertices, double ** weights) // binary version; returns 0 on success
{
  FILE * fout = fopen(filename, "wb");
  if (!fout)
  {
    printf("Error: unable to open file %s.\n", filename);
    return 1;
  }

  int writtenItems = (int)fwrite(&numModels, sizeof(int), 1, fout);
  if (writtenItems < 1)
  {
    printf("Error: unable to write to file %s.\n", filename);
    return 1;
  }

  vegaunsignedlong numBytes = 0;
  for(int i=0; i<numModels; i++)
  {
    writtenItems = (int)fwrite(&numBytes, sizeof(vegaunsignedlong), 1, fout);
    if (writtenItems < 1)
    {
      printf("Error: unable to write to file %s.\n", filename);
      return 1;
    }
    numBytes += 2 * sizeof(int) + (vegaunsignedlong) numElementVertices[i] * numTargetLocations[i] * (sizeof(int) + sizeof(double));
  }

  int code = 0;
  for(int i=0; i<numModels; i++)
    code = code | VolumetricMesh::saveInterpolationWeightsBinary(fout, numTargetLocations[i], numElementVertices[i], vertices[i], weights[i]);
 
  fclose(fout);
  return code;
}

