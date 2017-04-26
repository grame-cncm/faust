/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "volumetricMesh" library , Copyright (C) 2007 CMU, 2009 MIT           *
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

#ifndef _INTERPOLATIONWEIGHTSMULTILOAD_H_
#define _INTERPOLATIONWEIGHTSMULTILOAD_H_

// input: filename, numModels
// output: numTargetLocations, numElementVertices, vertices, weights
int multiLoadInterpolationWeightsBinary(const char * filename, int * numModels, int ** numTargetLocations, int ** numElementVertices, int *** vertices, double *** weights); // binary version; returns 0 on success

// input: filename, numModels, numTargetLocations, numElementVertices, vertices, weights
int multiSaveInterpolationWeightsBinary(const char * filename, int numModels, int * numTargetLocations, int * numElementVertices, int ** vertices, double ** weights); // binary version; returns 0 on success

#endif

