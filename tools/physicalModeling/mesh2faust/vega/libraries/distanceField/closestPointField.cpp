/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "distance field" library , Copyright (C) 2007 CMU, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
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

/*
  ClosestPointField is similar to a distance field, 
  except it also stores the nearest point, not just the distance to it.
*/

#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "closestPointField.h"
#include "trilinearInterpolation.h"
using namespace std;

ClosestPointField::ClosestPointField() : DistanceField()
{
  closestPointData = NULL;
}

ClosestPointField::~ClosestPointField()
{
  free(closestPointData);
}

// the routines for signed/unsigned closest point field computation
#define COMPUTE_CLOSEST_POINT
  #define COMPUTE_SIGNED_FIELD
    #include "computeField.cpp"
  #undef COMPUTE_SIGNED_FIELD
    #include "computeField.cpp"
#undef COMPUTE_CLOSEST_POINT

void ClosestPointField::set(int resolutionX, int resolutionY, int resolutionZ, Vec3d bmin_, Vec3d bmax_, float * distanceData, float * closestPointData)
{
  DistanceField::set(resolutionX, resolutionY, resolutionZ, bmin_, bmax_, distanceData);

  free(this->closestPointData);
  this->closestPointData = (float*) malloc (sizeof(float)*3*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));
  memcpy(this->closestPointData, closestPointData, sizeof(float)*3*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));
}

int ClosestPointField::load(const std::string& filename)
{
  ifstream fin(filename.c_str(),ios::binary);
  if (!fin)
    return 1;

  fin.read((char*)&resolutionX,4);

  // the type of data (single-precision or double-precision) is encoded  
  // as the sign of the x-resolution
  bool floatData = (resolutionX < 0);
  if (floatData)
    resolutionX = -resolutionX;
  
  fin.read((char*)&resolutionY,4); 
  if (resolutionY >=0)
  {
    return 1; // by convention the second resolution must be negative, so that we can differentiate closest point files from distance files
  }
  resolutionY = -resolutionY;
  fin.read((char*)&resolutionZ,4);

  fin.read((char*)&(bmin_[0]),8);
  fin.read((char*)&(bmin_[1]),8);
  fin.read((char*)&(bmin_[2]),8);
  
  fin.read((char*)&(bmax_[0]),8);
  fin.read((char*)&(bmax_[1]),8);
  fin.read((char*)&(bmax_[2]),8);

  setGridParameters();

  double * buffer = (double*) malloc (sizeof(double) * 3 * (resolutionX+1) * (resolutionY+1)); // place for one slice

  // load distances
  distanceData = (float*) malloc (sizeof(float)*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));

  float * distanceDataPos = distanceData;

  for(int k=0; k <= resolutionZ; k++)
  {
    if (floatData)
      fin.read((char*)buffer,sizeof(float)*(resolutionX+1)*(resolutionY+1));
    else
      fin.read((char*)buffer,sizeof(double)*(resolutionX+1)*(resolutionY+1));

    char * bufferPos = (char*)buffer;
    int bufferPosInc = floatData ? sizeof(float) : sizeof(double);

    // copy data to internal distance field buffer
    for(int j = 0; j <= resolutionY; j++)
      for(int i = 0; i <= resolutionX; i++)
      {
        if (floatData)
          *distanceDataPos = *(float*)bufferPos;
        else
          *distanceDataPos = *(double*)bufferPos;
        distanceDataPos++;
        bufferPos += bufferPosInc;
      }
  }

  // load closest points
  closestPointData = (float*) malloc (sizeof(float)*3*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));

  float * closestPosDataPos = closestPointData;

  for(int k=0; k <= resolutionZ; k++)
  {
    if (floatData)
      fin.read((char*)buffer,sizeof(float)*3*(resolutionX+1)*(resolutionY+1));
    else
      fin.read((char*)buffer,sizeof(double)*3*(resolutionX+1)*(resolutionY+1));

    char * bufferPos = (char*)buffer;
    int bufferPosInc = floatData ? sizeof(float) : sizeof(double);

    // copy data to internal closest point field buffer
    for(int j = 0; j <= resolutionY; j++)
      for(int i = 0; i <= resolutionX; i++)
        for(int coord=0; coord<3; coord++)
        {
          if (floatData)
            *closestPosDataPos = *(float*)bufferPos;
          else
            *closestPosDataPos = *(double*)bufferPos;
          closestPosDataPos++;
          bufferPos += bufferPosInc;
        }
  }

  fin.close();

  return 0;
}

int ClosestPointField::save(const std::string& filename, bool doublePrecision)
{
  if (doublePrecision)
    printf("Error: double precision output not supported. Using float instead.\n");
  doublePrecision = false;

  ofstream fout(filename.c_str(),ios::binary);

  int data = resolutionX;
  if (!doublePrecision)
    data = -data;
  fout.write((char*)&data,4);
  data = -resolutionY;
  fout.write((char*)&data,4);
  fout.write((char*)&resolutionZ,4);

  fout.write((char*)&(bmin_[0]),8);
  fout.write((char*)&(bmin_[1]),8);
  fout.write((char*)&(bmin_[2]),8);

  fout.write((char*)&(bmax_[0]),8);
  fout.write((char*)&(bmax_[1]),8);
  fout.write((char*)&(bmax_[2]),8);

/*
  float * buffer = NULL;
  if (!doublePrecision)
    convertToFloat(&buffer);
*/

  // write out distances
  // float precision
  fout.write((char*)distanceData,
    sizeof(float)*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));
  
/*
  if (doublePrecision)
    fout.write((char*)distanceData,sizeof(double)*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));
  else
  {
    fout.write((char*)buffer,sizeof(float)*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));
  }
*/

  // write out closest points
  // float precision
  fout.write((char*)closestPointData, sizeof(float)*3*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));

/*
  if (doublePrecision)
    fout.write((char*)closestPointData,sizeof(double)*3*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));
  else
  {
    fout.write((char*)(buffer+(resolutionX+1)*(resolutionY+1)*(resolutionZ+1)),
      sizeof(float)*3*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));
    free(buffer);
  }
*/

  fout.close();

  return 0;
}

void ClosestPointField::getClosestPointData(float ** floatBuffer)
{
  unsigned int size = 3 * (resolutionX+1) * (resolutionY+1) * (resolutionZ+1);
  *floatBuffer = (float*) malloc (sizeof(float) * size);
  memcpy(*floatBuffer, closestPointData, sizeof(float) * size);
}

void ClosestPointField::closestPoint(float pos[3], float result[3])
{
  // get the indices
  int i = (int)((pos[0] - bmin_[0]) * invGridX);
  int j = (int)((pos[1] - bmin_[1]) * invGridY);
  int k = (int)((pos[2] - bmin_[2]) * invGridZ);

  if ((i<0) || (i>=resolutionX) || (j<0) || (j>=resolutionY) || (k<0) || (k>=resolutionZ))
  {
    printf("Warning: querying the closest point field outside of the bounding box.\n");
    result[0] = result[1] = result[2] = 0;
  }

  double wx = ((pos[0]-bmin_[0]) / gridX) - i;
  double wy = ((pos[1]-bmin_[1]) / gridY) - j;
  double wz = ((pos[2]-bmin_[2]) / gridZ) - k;

  float c0[3], c1[3], c2[3], c3[3], c4[3], c5[3], c6[3], c7[3];

  closestPoint(i,j,k,c0);
  closestPoint(i+1,j,k,c1);
  closestPoint(i+1,j+1,k,c2);
  closestPoint(i,j+1,k,c3);
  closestPoint(i,j,k+1,c4);
  closestPoint(i+1,j,k+1,c5);
  closestPoint(i+1,j+1,k+1,c6);
  closestPoint(i,j+1,k+1,c7);

  result[0] = TRILINEAR_INTERPOLATION(wx,wy,wz,
     c0[0], c1[0], c2[0], c3[0], c4[0], c5[0], c6[0], c7[0]);
  result[1] = TRILINEAR_INTERPOLATION(wx,wy,wz,
     c0[1], c1[1], c2[1], c3[1], c4[1], c5[1], c6[1], c7[1]);
  result[2] = TRILINEAR_INTERPOLATION(wx,wy,wz,
     c0[2], c1[2], c2[2], c3[2], c4[2], c5[2], c6[2], c7[2]);
}

bool ClosestPointField::sanityCheck()
{
  bool exitCode = DistanceField::sanityCheck();

  bool myExitCode = true;
  for (int k=0; k <= resolutionZ; k++)
    for (int j=0; j <= resolutionY; j++)
      for (int i=0; i <= resolutionX; i++)
      {
        float distanceScalar = distance(i,j,k);
        float closestPoint_[3];
        closestPoint(i,j,k, closestPoint_);
        Vec3d gridPos = getGridPosition(i,j,k);
        float distanceNorm = 
          sqrt((closestPoint_[0] - gridPos[0])*(closestPoint_[0] - gridPos[0]) +
               (closestPoint_[1] - gridPos[1])*(closestPoint_[1] - gridPos[1]) +
               (closestPoint_[2] - gridPos[2])*(closestPoint_[2] - gridPos[2]));

        if (distanceScalar - distanceNorm > 1E-6)
        {
          printf("(i,j,k)=(%d,%d,%d): distance=%G | norm of closest vector=%G\n", i,j,k, distanceScalar, distanceNorm);
          myExitCode = false;
        }
      }

  return exitCode && myExitCode;
}

