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

/*
  Loads a volumetric mesh from a text file or a binary file. It automatically determines 
  the type of the mesh (tet mesh, cube mesh).
*/

#ifndef _VOLUMETRICMESHLOADER_H_
#define _VOLUMETRICMESHLOADER_H_

#include "volumetricMesh.h"

class VolumetricMeshLoader
{
public:
  // loads a volumetric mesh (ASCII (.veg format), or BINARY)
  static VolumetricMesh * load(const char * filename, VolumetricMesh::fileFormatType fileFormat = VolumetricMesh::ASCII, int verbose=1);

  // loads several volumetric meshes from a single binary file
  static int load(const char * filename, int * numVolumetricMeshes, VolumetricMesh *** volumetricMeshes, int verbose=1);

  // saves several volumetric meshes to a single binary file
  // if you do not want to use "saveVolumetricMeshFlag", set it to NULL
  // if saveVolumetricMeshFlag is not NULL, then:
  // saveVolumetricMeshFlag[i] = 0: skip (do not save) volumetric mesh i
  // saveVolumetricMeshFlag[i] != 0: save volumetric mesh i to disk
  static int save(const char * filename, int numVolumetricMeshes, VolumetricMesh ** volumetricMeshes, int * saveVolumetricMeshFlag, int verbose=0);

  // advanced usage: loads a volumetric mesh from the current position of the file stream (binary mode).
  // if memoryLoad is 0, binaryStream is FILE* (load from a file), otherwise, it is char* (load from a memory buffer)
  static VolumetricMesh * load(void * fin, int memoryLoad = 0);

protected:
  static int load(FILE * fin, int * numVolumetricMeshes, VolumetricMesh *** volumetricMeshes, int verbose=1);
};

#endif

