/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "distance field" library , Copyright (C) 2007 CMU, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Yijing Li, Hongyi Xu, Jernej Barbic                     *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Research: Jernej Barbic, Hongyi Xu, Doug L. James                     *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
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

#include <stdio.h>
#include <cassert>
#include "distanceFieldCreator.h"
#include "signedDistanceFieldFromPolygonSoup.h"
#include "marchingCubes.h"
using namespace::std;

DistanceFieldCreator::DistanceFieldCreator(ObjMesh * objMesh_, double expansionRatio_, bool useCubicBox_, const Vec3d * bbmin_, const Vec3d * bbmax_): objMesh(objMesh_), expansionRatio(expansionRatio_), useCubicBox(useCubicBox_), bbmin(0.0), bbmax(1.0)
{
  if (bbmin_ != NULL && bbmax_ != NULL) // caller provides bmin and bmax
  {
    bbmin = *bbmin_;
    bbmax = *bbmax_;
    assert((bbmin[0] < bbmax[0]) && (bbmin[1] < bbmax[1]) && (bbmin[2] < bbmax[2]));
    autoBoundingBox = false;
  }
  else
    autoBoundingBox = true;
}

void DistanceFieldCreator::setBoundingBox(DistanceFieldBase * field, int resolutionX, int resolutionY, int resolutionZ)
{
  if (autoBoundingBox)
  {
    if (useCubicBox)
      printf("Forcing a cube-sized bounding box.\n");
    field->setAutomaticBoundingBox(useCubicBox, expansionRatio);
    field->computeBoundingBox(objMesh, resolutionX, resolutionY, resolutionZ);
    field->getBoundingBox(bbmin, bbmax);
  }
  else
    field->setBoundingBox(bbmin,bbmax);
}

DistanceField * DistanceFieldCreator::ComputeDistanceField(int resolutionX, int resolutionY, int resolutionZ, int signField, SignedFieldCreationMode mode, 
  double sigma, int subtractSigma, int numThreads, bool computeVoronoiDiagram, int maxTriCount, int maxDepth, int closestPointFlag,
  const char* precomputedUnsignedFieldFilename)
{
  DistanceField * field = NULL;
  if (signField && (mode == POLYGONSOUP)) // compute signField using PolygonSoup
  {
    printf("********* Computing signed distance field (%d x %d x %d) *************\n", resolutionX, resolutionY, resolutionZ); fflush(NULL);
    SignedDistanceFieldFromPolygonSoup signedDistanceFieldFromPolygonSoup(objMesh, expansionRatio, useCubicBox, 
      (autoBoundingBox ? NULL : &bbmin), (autoBoundingBox ? NULL : &bbmax));
    field = signedDistanceFieldFromPolygonSoup.ComputeDistanceField(resolutionX, resolutionY, resolutionZ, sigma, subtractSigma, numThreads, computeVoronoiDiagram, maxTriCount, maxDepth, closestPointFlag, precomputedUnsignedFieldFilename);
  }
  else // Use DistaneField->compute... first
  {
    if (!closestPointFlag)
    {
      if (numThreads == 0)
        field = new DistanceField();
      else
        field = new DistanceFieldMT(numThreads);
    }
    else
      field = new ClosestPointField();

    field->enableVoronoiDiagramComputation(computeVoronoiDiagram);

    setBoundingBox(field, resolutionX, resolutionY, resolutionZ);    

    int code = 0;
    if (signField)
    {
      printf("********* Computing signed distance field (%d x %d x %d) *************\n", resolutionX, resolutionY, resolutionZ); fflush(NULL);
      code = field->computeSignedField(objMesh, resolutionX, resolutionY, resolutionZ, maxTriCount, maxDepth);

      if (code != 0)
      {
        delete field;
        if (mode == BASIC)
        {
          printf("Error computing the signed distance field. Non-manifold geometry. \n");
          return NULL;
        }

        // use polygon-soup
        printf("Non-manifold geometry. Switching to polygon-soup signed distance field computation.\n");
        SignedDistanceFieldFromPolygonSoup signedDistanceFieldFromPolygonSoup(objMesh, expansionRatio, useCubicBox, &bbmin, &bbmax);
        field = signedDistanceFieldFromPolygonSoup.ComputeDistanceField(resolutionX, resolutionY, resolutionZ, sigma, subtractSigma, numThreads, computeVoronoiDiagram, maxTriCount, maxDepth, closestPointFlag, precomputedUnsignedFieldFilename);
        if (field == NULL)
          return NULL;
      }
    }
    else
    {
      printf("********* Computing unsigned distance field (%d x %d x %d) *************\n", resolutionX, resolutionY, resolutionZ); fflush(NULL);
      code = field->computeUnsignedField(objMesh, resolutionX, resolutionY, resolutionZ, maxTriCount, maxDepth);

      if (code !=0)
      {
        printf("Error computing unsigned distance field.\n");
        delete field;
        return NULL;
      }
    }
  }

  printf("Computation completed. Performing sanity check...\n");
  if (!field->sanityCheck())
    printf("Sanity check failed.\n");

  return field;
}

DistanceFieldNarrowBand * DistanceFieldCreator::ComputeDistanceFieldNarrowBand(int resolutionX, int resolutionY, int resolutionZ, double bandWidth,
  int signField, SignedFieldCreationMode mode, double sigma, int subtractSigma, int maxTriCount, int maxDepth,
  const char * precomputedUnsignedFieldFilename)
{
  int code = 0;
  DistanceFieldNarrowBand * field = NULL; 

  if (signField && (mode == POLYGONSOUP)) // compute signField using PolygonSoup
  {
    printf("********* Computing signed distance field (%d x %d x %d) *************\n", resolutionX, resolutionY, resolutionZ); fflush(NULL);
    SignedDistanceFieldFromPolygonSoup signedDistanceFieldFromPolygonSoup(objMesh, expansionRatio, useCubicBox, 
      (autoBoundingBox ? NULL : &bbmin), (autoBoundingBox ? NULL : &bbmax));
    field = signedDistanceFieldFromPolygonSoup.ComputeDistanceFieldNarrowBand(resolutionX, resolutionY, resolutionZ, bandWidth,
      sigma, subtractSigma, maxTriCount, maxDepth, precomputedUnsignedFieldFilename);
  }
  else
  {
    field = new DistanceFieldNarrowBand();
    setBoundingBox(field, resolutionX, resolutionY, resolutionZ);

    if (signField)
    {
      printf("********* Computing signed distance field (%d x %d x %d) *************\n", resolutionX, resolutionY, resolutionZ); fflush(NULL);
      code = field->computeSignedField(objMesh, resolutionX, resolutionY, resolutionZ, bandWidth, maxTriCount, maxDepth);

      if (code != 0)
      {
        delete field;
        if (mode == BASIC)
        {
          printf("Error computing the signed distance field. Non-manifold geometry. \n");
          return NULL;
        }

        // use polygon-soup
        printf("Non-manifold geometry. Switching to polygon-soup signed distance field computation.\n");
        if (sigma >= bandWidth)
        {
          printf("Error: sigma is not smaller than the bandwidth...\n");
          return NULL;
        }

        SignedDistanceFieldFromPolygonSoup signedDistanceFieldFromPolygonSoup(objMesh, expansionRatio, useCubicBox, &bbmin, &bbmax);
        field = signedDistanceFieldFromPolygonSoup.ComputeDistanceFieldNarrowBand(resolutionX, resolutionY, resolutionZ, bandWidth,
          sigma, subtractSigma, maxTriCount, maxDepth, precomputedUnsignedFieldFilename);

        if (field == NULL)
          return NULL;
      }
    }
    else
    {
      printf("********* Computing unsigned distance field (%d x %d x %d) *************\n", resolutionX, resolutionY, resolutionZ); fflush(NULL);
      code = field->computeUnsignedField(objMesh, resolutionX, resolutionY, resolutionZ, bandWidth, maxTriCount, maxDepth);

      if (code !=0)
      {
        printf("Error computing unsigned distance field.\n");
        delete field;
        return NULL;
      }
    }
  }

  printf("Computation completed. Performing sanity check...\n");
  if (!field->sanityCheck())
    printf("Sanity check failed.\n");

  return field;
}

