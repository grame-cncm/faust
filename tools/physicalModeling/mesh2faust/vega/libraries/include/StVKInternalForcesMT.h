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

#ifndef _STVKINTERNALFORCESMT_H_
#define _STVKINTERNALFORCESMT_H_

#include "StVKInternalForces.h"

/*
  This class is a multi-threaded version of the class "StVKInternalForces".
  It uses POSIX threads ("pthreads") as the threading API.
  Each thread assembles the internal force with respect to a subset of all the mesh elements. 
  At the end, the individual results are added into a global internal force vector.

  See also StVKInternalForces.h .
*/

class StVKInternalForcesMT : public StVKInternalForces
{
public:

  // same usage as StVKInternalForces, except must specify the number of threads
  StVKInternalForcesMT(VolumetricMesh * volumetricMesh, StVKElementABCD * precomputedABCDIntegrals, bool addGravity, double g, int numThreads);
  virtual ~StVKInternalForcesMT();

  virtual void ComputeForces(const double * vertexDisplacements, double * internalForces);
  virtual double ComputeEnergy(const double * vertexDisplacements); 

  // advanced function (tells what range of volumetric mesh elements is assigned to each thread)
  int GetStartElement(int rank);
  int GetEndElement(int rank);

protected:
  int numThreads;
  int * startElement, * endElement;
  double * internalForceBuffer;
  double * energyBuffer;
  double * energyAuxBuffer;

  void Compute(int computationTarget, const double * vertexDisplacements, double * internalForces);
};

#endif

