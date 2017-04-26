/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "volumetricMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC *
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

#include "volumetricMeshLoader.h"
#include "cubicMesh.h"
#include "tetMesh.h"

// for faster parallel loading of multimesh binary files, enable the -fopenmp -DUSE_OPENMP macro line in the Makefile-header file (see also documentation)

#ifdef USE_OPENMP
  #include <omp.h>
#endif

VolumetricMesh * VolumetricMeshLoader::load(const char * filename, VolumetricMesh::fileFormatType fileFormat, int verbose)
{
  VolumetricMesh::elementType elementType_ = VolumetricMesh::getElementType(filename, fileFormat);
  if (elementType_ == VolumetricMesh::INVALID)
  {
    return NULL;
  }

  VolumetricMesh * volumetricMesh = NULL;

  switch (fileFormat)
  {
    case VolumetricMesh::ASCII:
    {
      if (elementType_ == TetMesh::elementType())
        volumetricMesh = new TetMesh(filename, VolumetricMesh::ASCII, verbose); 

      if (elementType_ == CubicMesh::elementType())
        volumetricMesh = new CubicMesh(filename, VolumetricMesh::ASCII, verbose);
    }
  	break;

    case VolumetricMesh::BINARY:
    {
      if (elementType_ == TetMesh::elementType())
        volumetricMesh = new TetMesh(filename, VolumetricMesh::BINARY, verbose); 

      if (elementType_ == CubicMesh::elementType())
        volumetricMesh = new CubicMesh(filename, VolumetricMesh::BINARY, verbose);
    }
    break;

    default:
    {
      printf("Error in VolumetricMeshLoader: invalid file format.\n");
      return NULL;
    }
  }

  return volumetricMesh;
}

VolumetricMesh * VolumetricMeshLoader::load(void * fin, int memoryLoad)
{
  VolumetricMesh::elementType elementType_ = VolumetricMesh::getElementType(fin, memoryLoad);

  VolumetricMesh * volumetricMesh = NULL;

  if (elementType_ == TetMesh::elementType())
    volumetricMesh = new TetMesh(fin, memoryLoad); 

  if (elementType_ == CubicMesh::elementType())
    volumetricMesh = new CubicMesh(fin, memoryLoad);

  return volumetricMesh;
}

int VolumetricMeshLoader::load(const char * filename, int * numVolumetricMeshes, VolumetricMesh *** volumetricMeshes, int verbose)
{
  FILE * fin = fopen(filename, "rb");
  if (fin == NULL)
  {
    printf("Error in VolumetricMeshLoader::load: cannot open %s to read.\n", filename);
    return 1;
  }
  int code = load(fin, numVolumetricMeshes, volumetricMeshes, verbose);
  fclose(fin);

  return code;
}

int VolumetricMeshLoader::load(FILE * fin, int * numVolumetricMeshes, VolumetricMesh *** volumetricMeshes, int verbose)
{
  // read the number of volumetric meshes
  unsigned int items = fread(numVolumetricMeshes, sizeof(int), 1, fin);
  if (items != 1)
    return 1;

  int numMeshes = *numVolumetricMeshes;

  if (verbose)
    printf("number of volumetric meshes to be read from binary: %d\n", numMeshes);
  
  // read how many bytes are stored for every volumetric mesh
  unsigned int * bytesWritten = (unsigned int *) calloc (numMeshes, sizeof(unsigned int));
  items = fread(bytesWritten, sizeof(unsigned int), numMeshes, fin);
  if ((int)items != numMeshes)
    return 1;

  if (verbose)
  {
    printf("number of bytes for each volumetric mesh: \n");
    for(int i=0; i<numMeshes; i++)
      printf("%u, ", bytesWritten[i]);
    printf("\n");
  }

  // compute the total bytes
  unsigned int totalBytes = 0;
  for(int i=0; i<numMeshes; i++)
    totalBytes += bytesWritten[i];

  // allocate memory for volumetric meshes
  (*volumetricMeshes) = (VolumetricMesh **) malloc (sizeof(VolumetricMesh *) * numMeshes);
  for (int i=0; i<numMeshes; i++)
    (*volumetricMeshes)[i] = NULL;

  // read entire block from the memory
  unsigned char * memory = (unsigned char *) malloc (sizeof(unsigned char) * totalBytes);
  items = fread(memory, sizeof(unsigned char), totalBytes, fin);


  if (verbose)
    printf("total bytes excluding header: %u\n", totalBytes);

  // compute the offset for every volumetric mesh
  unsigned int * offset = (unsigned int *) calloc (numMeshes, sizeof(unsigned int));
  for(int i=1; i<numMeshes; i++)
    offset[i] = offset[i-1] + bytesWritten[i-1];

  // load every volumetric mesh from memory
  #ifdef USE_OPENMP
    #pragma omp parallel for
  #endif
  for(int i=0; i<numMeshes; i++)
  {
    if (bytesWritten[i] != 0)
    {
      unsigned char * location = memory + offset[i];
      int memoryLoad = 1;
      (*volumetricMeshes)[i] = load((void *)location, memoryLoad);
    }
  }
    
  free(bytesWritten);
  free(memory);
  free(offset);

  return 0;
}

int VolumetricMeshLoader::save(const char * filename, int numVolumetricMeshes, VolumetricMesh ** volumetricMeshes, int * saveVolumetricMeshFlag, int verbose)
{
  FILE * output = fopen(filename, "wb");
  if (output == NULL)
  {
    printf("Error in VolumetricMeshLoader::save: cannot open %s to write.\n", filename);
    return 1;
  }

  unsigned int * bytesWritten = (unsigned int*) calloc (numVolumetricMeshes, sizeof(unsigned int));
  // count the number of bytes written to the disk for every volumetric mesh
  for(int i=0; i<numVolumetricMeshes; i++)
  {
    if ((saveVolumetricMeshFlag != NULL) && (saveVolumetricMeshFlag[i] == 0))
      continue;

    bool countBytesOnly = true;
    volumetricMeshes[i]->saveToBinary(NULL, &bytesWritten[i], countBytesOnly);
  }

  if (verbose)
  {
    printf("number of bytes for each volumetric mesh: \n");
    for(int i=0; i<numVolumetricMeshes; i++)
      printf("%u, ", bytesWritten[i]);
    printf("\n");
  }

  // write the header to the disk
  fwrite(&numVolumetricMeshes, sizeof(int), 1, output);
  fwrite(bytesWritten, sizeof(unsigned int), numVolumetricMeshes, output);

  // write the volumetric meshes to the disk
  for(int i=0; i<numVolumetricMeshes; i++)
  {
    if ((saveVolumetricMeshFlag != NULL) && (saveVolumetricMeshFlag[i] == 0))
      continue;

    bool countBytesOnly = false;
    volumetricMeshes[i]->saveToBinary(output, &bytesWritten[i], countBytesOnly);
  }

  free(bytesWritten);
  fclose(output);

  return 0;
}

