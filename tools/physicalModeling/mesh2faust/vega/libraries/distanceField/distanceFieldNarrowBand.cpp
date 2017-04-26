/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "distance field" library , Copyright (C) 2007 CMU, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Hongyi Xu, Jernej Barbic                                 *
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
  Narrowband distance field computation.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <fstream>
#include <set>
#include "triangle.h"
#include "boundingBox.h"
#include "distanceFieldNarrowBand.h"
#include "objMeshOrientable.h"
#include "objMeshOctree.h"
#include "trilinearInterpolation.h"
#include "vegalong.h"
using namespace std;

vegalong DistanceFieldNarrowBand::GetFilesize(const char *filename)
{
  FILE * f = fopen(filename, "rb");  /* open the file in read only */

  vegalong size = 0;
  if (fseek(f, 0, SEEK_END) == 0) /* seek was successful */
      size = ftell(f);
  fclose(f);
  return size;
}

DistanceFieldNarrowBand::DistanceFieldNarrowBand() : DistanceFieldBase()
{ 
  gridPointStatus = NULL;
  signFieldFlooded = 0;
}

DistanceFieldNarrowBand::~DistanceFieldNarrowBand()
{
  free(gridPointStatus);
}

// the routines for signed and unsigned distance field computation
#define COMPUTE_SIGNED_FIELD_NARROWBAND
  #define COMPUTE_INTERIOR_FIELD_NARROWBAND
    #include "computeFieldNarrowBand.cpp"
  #undef COMPUTE_INTERIOR_FIELD_NARROWBAND
    #include "computeFieldNarrowBand.cpp"
#undef COMPUTE_SIGNED_FIELD_NARROWBAND
  #include "computeFieldNarrowBand.cpp"

int DistanceFieldNarrowBand::load(const std::string& filename)
{
  ifstream fin(filename.c_str(),ios::binary);
  if (!fin)
    return 1;

  fin.read((char*)&resolutionX, sizeof(int));

  // the type of data (single-precision or double-precision) is encoded as the sign of the x-resolution
  bool floatData = (resolutionX < 0);
  if (floatData)
    resolutionX = -resolutionX;
   
  fin.read((char*)&resolutionY, sizeof(int)); 

  if (resolutionY < 0) // negative second resolution implies closest point data
    return 1;

  fin.read((char*)&resolutionZ, sizeof(int));

  vegalong size =  (resolutionZ + 1) * (resolutionY + 1) * (resolutionX + 1);
  gridPointStatus = (char*) realloc (gridPointStatus, sizeof(char) * size);
  for(vegalong i=0; i<size; i++)
    gridPointStatus[i] = DistanceFieldNarrowBand::EXTERIOR_UNCOMPUTED;

  fin.read((char*)&(bmin_[0]), sizeof(double));
  fin.read((char*)&(bmin_[1]), sizeof(double));
  fin.read((char*)&(bmin_[2]), sizeof(double));

  fin.read((char*)&(bmax_[0]), sizeof(double));
  fin.read((char*)&(bmax_[1]), sizeof(double));
  fin.read((char*)&(bmax_[2]), sizeof(double));

  setGridParameters();

  int numGridPoints = 0;
  fin.read((char*)&numGridPoints, sizeof(int));
  
  int i, j, k;
  double * buffer = (double*)malloc(sizeof(double));
  for(int p = 0; p < numGridPoints; p++)
  {
    fin.read((char*)&i, sizeof(int));
    fin.read((char*)&j, sizeof(int));
    fin.read((char*)&k, sizeof(int));
    if (floatData)
      fin.read((char*)buffer, sizeof(float));
    else
      fin.read((char*)buffer, sizeof(double));

    distanceData.insert(pair<gridPoint, float>(gridPoint(i,j,k), *(float*)(buffer)));
  }
  free(buffer);

  finalizeGridPointStatus();
  
  fin.close();
  
  return 0;
}

int DistanceFieldNarrowBand::saveToText(const std::string& filename)
{
  FILE * fout = fopen((char*)filename.c_str(), "w");
  if (!fout)
    return 1;

  fprintf(fout, "%d\n", resolutionX);
  fprintf(fout, "%d\n", resolutionY);
  fprintf(fout, "%d\n", resolutionZ);

  for (map<gridPoint, float>::iterator it = distanceData.begin(); it != distanceData.end(); it++)
  {
    gridPoint v = it->first;
    fprintf(fout, "%d %d %d %G\n", v.first, v.second, v.third, it->second);
  }

  fclose(fout);

  return 0;
}

int DistanceFieldNarrowBand::saveToDistanceField(const std::string& filename, bool doublePrecision)
{
  if (doublePrecision)
    printf("Error: double precision output is not supported. Using float instead.\n");
  doublePrecision = false;

  ofstream fout;
  fout.open(filename.c_str(),ios::binary);

  int data = resolutionX;
  if (!doublePrecision)
    data = -data;

  fout.write((char*)&data,sizeof(int));
  fout.write((char*)&resolutionY,sizeof(int));
  fout.write((char*)&resolutionZ,sizeof(int));

  fout.write((char*)&(bmin_[0]),sizeof(double));
  fout.write((char*)&(bmin_[1]),sizeof(double));
  fout.write((char*)&(bmin_[2]),sizeof(double));

  fout.write((char*)&(bmax_[0]),sizeof(double));
  fout.write((char*)&(bmax_[1]),sizeof(double));
  fout.write((char*)&(bmax_[2]),sizeof(double));

  int flag = 1;
  for(vegalong k=0; k<=resolutionZ; k++)
    for(vegalong j=0; j<=resolutionY; j++)
      for(vegalong i=0; i<=resolutionX; i++)
      {
        float dist = distance(i,j,k);
        if (fabs(dist) != FLT_MAX)
          flag = (dist >= 0) ? 1 : -1;
        else
        {
          if (flag == -1)
            dist = -FLT_MAX;
        }
        fout.write((char*)&dist, sizeof(float));
      }
  fout.close();

  return 0;
}

int DistanceFieldNarrowBand::save(const std::string& filename, bool doublePrecision)
{
  if (doublePrecision)
    printf("Error: double precision output is not supported. Using float instead.\n");
  doublePrecision = false;

  ofstream fout;
  fout.open(filename.c_str(),ios::binary);

  int data = resolutionX;
  if (!doublePrecision)
    data = -data;

  fout.write((char*)&data,sizeof(int));
  fout.write((char*)&resolutionY,sizeof(int));
  fout.write((char*)&resolutionZ,sizeof(int));

  fout.write((char*)&(bmin_[0]),sizeof(double));
  fout.write((char*)&(bmin_[1]),sizeof(double));
  fout.write((char*)&(bmin_[2]),sizeof(double));

  fout.write((char*)&(bmax_[0]),sizeof(double));
  fout.write((char*)&(bmax_[1]),sizeof(double));
  fout.write((char*)&(bmax_[2]),sizeof(double));

  vegalong numGridPoints = distanceData.size();
  fout.write((char*)&(numGridPoints),sizeof(int));

  for (map<gridPoint, float>::iterator it = distanceData.begin(); it != distanceData.end(); it++)
  {
    gridPoint v = it->first;
    fout.write((char*)&(v.first), sizeof(int));
    fout.write((char*)&(v.second), sizeof(int));
    fout.write((char*)&(v.third), sizeof(int));
    float value = it->second;
    fout.write((char*)&(value), sizeof(float));
  }

  fout.close();

  return 0;
}

void DistanceFieldNarrowBand::finalizeGridPointStatus()
{
  // assumption: bounding box covers the entire geometry

  int flag = 1;
  vegalong index = 0;
  for(vegalong k=0; k<=resolutionZ; k++)
    for(vegalong j=0; j<=resolutionY; j++)
      for(vegalong i=0; i<=resolutionX; i++)
      {
        float dist = distance(i,j,k);
        if ((dist == FLT_MAX) || (dist == -FLT_MAX))
        {
          gridPointStatus[index] = (flag == -1) ? DistanceFieldNarrowBand::INTERIOR_UNCOMPUTED : DistanceFieldNarrowBand::EXTERIOR_UNCOMPUTED; 
        }
        else
        {
          flag = (dist >= 0) ? 1 : -1;
          gridPointStatus[index] = DistanceFieldNarrowBand::COMPUTED; 
        }

        index++;
      }
}

typedef struct
{
  int i,j,k;
  int di,dj,dk;
  double fieldDist, gridDist, relError; 
} errorData;

struct more_errorData : public std::binary_function< errorData, errorData, bool > {
  bool operator()(const errorData& x, const errorData& y) {
    return((x.relError) > (y.relError)); 
  }
};

bool DistanceFieldNarrowBand::sanityCheck()
{
  //double diagonal = sqrt(gridX*gridX + gridY*gridY + gridZ*gridZ);

  bool result = true;
  int count = 0;

  const int numErrorsPrinted = 3;

  vector<errorData> relErrors;
  errorData emptyEntry = {0,0,0,0,0,0,0.0,0.0,-1.0};
  for(int i=0; i<numErrorsPrinted; i++)
   relErrors.push_back(emptyEntry);

  int counter = 0;
  for (map<gridPoint, float>::iterator it = distanceData.begin(); it != distanceData.end(); it++)
  {
    gridPoint v = it->first; 
    int i = v.first;
    int j = v.second;
    int k = v.third;

    float d = it->second;
    float d1;
    float sanity;
    float relError;
    float fieldDist;
    float gridDist;

    #define PROCESS(di,dj,dk)\
    if ((i+(di) <= resolutionX) && (i+(di) >= 0) &&\
        (j+(dj) <= resolutionY) && (j+(dj) >= 0) &&\
        (k+(dk) <= resolutionZ) && (k+(dk) >= 0))\
    {\
      d1 = distance(i+(di),j+(dj),k+(dk));\
      if ((d1 != -FLT_MAX) && (d1 != FLT_MAX))\
      {\
        gridDist = (float) (len(Vec3d((di)*gridX,(dj)*gridY,(dk)*gridZ)));\
        fieldDist = fabs(d-d1);\
        sanity = fieldDist - gridDist;\
        if (sanity > 1E-6)\
        {\
          relError = sanity/gridDist;\
          if (relError > relErrors[numErrorsPrinted-1].relError)\
          {\
            errorData errorEntry = {i,j,k,di,dj,dk,fieldDist,gridDist,relError};\
            relErrors[numErrorsPrinted-1] = errorEntry;\
            sort(relErrors.begin(),relErrors.end(),more_errorData());\
          }\
          result = false;\
          count++;\
        }\
      }\
    }
    
    PROCESS(1,0,0);
    PROCESS(1,1,0);
    PROCESS(0,1,0);
    PROCESS(-1,1,0);
    PROCESS(-1,0,0);
    PROCESS(-1,-1,0);
    PROCESS(0,-1,0);
    PROCESS(1,-1,0);

    PROCESS(0,0,1);
    PROCESS(1,0,1);
    PROCESS(1,1,1);
    PROCESS(0,1,1);
    PROCESS(-1,1,1);
    PROCESS(-1,0,1);
    PROCESS(-1,-1,1);
    PROCESS(0,-1,1);
    PROCESS(1,-1,1);

    PROCESS(0,0,-1);
    PROCESS(1,0,-1);
    PROCESS(1,1,-1);
    PROCESS(0,1,-1);
    PROCESS(-1,1,-1);
    PROCESS(-1,0,-1);
    PROCESS(-1,-1,-1);
    PROCESS(0,-1,-1);
    PROCESS(1,-1,-1);

    counter++;
    if (counter % (resolutionX * resolutionY)== 0)
    {
      counter = 0;
      cout << "." << flush;
    }
  }

  cout << endl;

  if (count == 0)
    cout << "Success: sanity check passed." << endl;
  else
  {
    cout << "Encountered " << count << " possible errors. Largest top " << numErrorsPrinted << " errors (or all errors if fewer):" << endl;
    for(int i=0; i< (count < numErrorsPrinted ? count : numErrorsPrinted); i++)
    {
      errorData * errorEntry = &relErrors[i]; 
      float d1 = distance(errorEntry->i,errorEntry->j,errorEntry->k);
      float d2 = distance(errorEntry->i + errorEntry->di ,errorEntry->j + errorEntry->dj, errorEntry->k + errorEntry->dk);
      cout << "Distance field change too large. [" << errorEntry->i << "," << errorEntry->j << "," << errorEntry->k << "] to [" << errorEntry->i + (errorEntry->di) << "," << errorEntry->j + (errorEntry->dj) << "," << errorEntry->k + (errorEntry->dk) << "]" << " Dist 1: " << d1 << " Dist 2: " << d2 << " Reported change in distance field: " << errorEntry->fieldDist << " Grid distance: " << errorEntry->gridDist << " Relative error: " << errorEntry->relError << endl;
    }
  }
  return result;
}

float DistanceFieldNarrowBand::distance(Vec3d pos, int constrainToBox)
{
  // get the index coordinate of the lower-right-bottom corner of the voxel containing 'pos'
  int i = (int)((pos[0] - bmin_[0]) * invGridX);
  int j = (int)((pos[1] - bmin_[1]) * invGridY);
  int k = (int)((pos[2] - bmin_[2]) * invGridZ);

  if (((i<0) || (i>=resolutionX) || (j<0) || (j>=resolutionY) || (k<0) || (k>=resolutionZ)) && (!constrainToBox))
  {
    printf("Warning: querying the distance field outside of the bounding box: (i,j,k)=(%d,%d,%d), (x, y, z)=(%lf,%lf,%lf), resolution=(%d,%d,%d)\n",i, j, k, pos[0], pos[1], pos[2], resolutionX, resolutionY, resolutionZ);
    return FLT_MAX;
  }

  if (constrainToBox)
  {
    if (i >= resolutionX)
    {
      i = resolutionX - 1;
      pos[0] = bmax_[0];
    }

    if (i < 0)
    {
      i = 0;
      pos[0] = bmin_[0];
    }

    if (j >= resolutionY)
    {
      j = resolutionY - 1;
      pos[1] = bmax_[1];
    }

    if (j < 0)
    {
      j = 0;
      pos[1] = bmin_[1];
    }

    if (k >= resolutionZ)
    {
      k = resolutionZ - 1;
      pos[2] = bmax_[2];
    }

    if (k < 0)
    {
      k = 0;
      pos[2] = bmin_[2];
    }
  }

  float distances[8];
  
  #define PROCESS2(i,j,k,l)\
   {\
     distances[(l)] = distance((i), (j), (k));\
     if (fabs(distances[(l)]) == FLT_MAX)\
     {\
       return distances[(l)];\
     }\
   }

  PROCESS2(i,j,k,0);
  PROCESS2(i+1,j,k,1);
  PROCESS2(i+1,j+1,k,2);
  PROCESS2(i,j+1,k,3);
  PROCESS2(i,j,k+1,4);
  PROCESS2(i+1,j,k+1,5);
  PROCESS2(i+1,j+1,k+1,6);
  PROCESS2(i,j+1,k+1,7);
  
  double wx,wy,wz;
  wx = ((pos[0]-bmin_[0]) / gridX) - i;
  wy = ((pos[1]-bmin_[1]) / gridY) - j;
  wz = ((pos[2]-bmin_[2]) / gridZ) - k;

  return (float)(TRILINEAR_INTERPOLATION(wx,wy,wz,distances[0],distances[1],distances[2],distances[3],
                                distances[4],distances[5],distances[6],distances[7]));
}

float DistanceFieldNarrowBand::maxValue()
{
  float maxValue=-FLT_MAX;
  
  for(map<gridPoint, float>::iterator it = distanceData.begin(); it != distanceData.end(); it++)
  {
    if ((it->second) > maxValue)
      maxValue = it->second;
  }
 
  return maxValue;
}

float DistanceFieldNarrowBand::minValue()
{
  float minValue=FLT_MAX;
 
  for(map<gridPoint, float>::iterator it = distanceData.begin(); it != distanceData.end(); it++)
  {
    if ((it->second) < minValue)
      minValue = it->second;
  }
  
  return minValue;
}

void DistanceFieldNarrowBand::maxMinValue(float* maxValue, float* minValue)
{
  *minValue=FLT_MAX;
  *maxValue=-FLT_MAX;
  
  for(map<gridPoint, float>::iterator it = distanceData.begin(); it != distanceData.end(); it++)
  {
    float dist = it->second;
    if (dist < *minValue)
      *minValue = dist;

    if (dist > *maxValue)
      *maxValue = dist;
  }
}

float DistanceFieldNarrowBand::maxAbsValue()
{
  float maxValue=0;

  for(map<gridPoint, float>::iterator it = distanceData.begin(); it != distanceData.end(); it++)
  {
    float dist = fabs(it->second);
    if (dist > maxValue)
      maxValue = dist;
  } 

  return maxValue;
}

float DistanceFieldNarrowBand::maxNonInftyAbsValue()
{
  float maxValue=0;

  for(map<gridPoint, float>::iterator it = distanceData.begin(); it != distanceData.end(); it++)
  {
    float dist = fabs(it->second);
    if ((dist > maxValue) && (dist != FLT_MAX))
      maxValue = dist;
  } 
  
  return maxValue;
}

float DistanceFieldNarrowBand::maxAbsValue(float threshold)
{
  float maxValue=0;
 
  for(map<gridPoint, float>::iterator it = distanceData.begin(); it != distanceData.end(); it++)
  {
    float dist = fabs(it->second);
    if ((dist > maxValue) && (dist < threshold))
      maxValue = dist;
  } 

  return maxValue;
}

Vec3d DistanceFieldNarrowBand::gradient(const Vec3d& pos)
{
  int i,j,k;

  // get the indices
  i = (int)((pos[0] - bmin_[0]) * invGridX);
  j = (int)((pos[1] - bmin_[1]) * invGridY);
  k = (int)((pos[2] - bmin_[2]) * invGridZ);

  if ((i<=0) || (i>=resolutionX) || (j<=0) || (j>=resolutionY) || (k<=0) || (k>=resolutionZ))
  {
    return Vec3d(0,0,0);
  }
                                                                                                                                                             
  double wx,wy,wz;
  wx = ((pos[0]-bmin_[0]) / gridX) - i;
  wy = ((pos[1]-bmin_[1]) / gridY) - j;
  wz = ((pos[2]-bmin_[2]) / gridZ) - k;

  // gradient with respect to trilinear interpolation
  float distances[8];
  #define PROCESS3(i,j,k,l)\
  {\
    distances[(l)] = distance(i, j, k);\
    if ((distances[(l)] == FLT_MAX) || (distances[(l)] == -FLT_MAX))\
    {\
      return distances[(l)];\
    }\
  }

  PROCESS3(i,j,k,0);
  PROCESS3(i+1,j,k,1);
  PROCESS3(i+1,j+1,k,2);
  PROCESS3(i,j+1,k,3);
  PROCESS3(i,j,k+1,4);
  PROCESS3(i+1,j,k+1,5);
  PROCESS3(i+1,j+1,k+1,6);
  PROCESS3(i,j+1,k+1,7);

  return Vec3d(
    GRADIENT_COMPONENT_X(wx,wy,wz,distances[0],distances[1],distances[2],distances[3],distances[4],distances[5],distances[6],distances[7]),
    GRADIENT_COMPONENT_Y(wx,wy,wz,distances[0],distances[1],distances[2],distances[3],distances[4],distances[5],distances[6],distances[7]),
    GRADIENT_COMPONENT_Z(wx,wy,wz,distances[0],distances[1],distances[2],distances[3],distances[4],distances[5],distances[6],distances[7]) );
                              
}

void DistanceFieldNarrowBand::findSurfaceGridPoints(ObjMesh* objMeshIn)
{
  ObjMesh objMesh(*objMeshIn);

  surfaceGridPoints.clear();
  //typedef triple<int,int,int> gridPoint;

  std::set<gridPoint> checkedGridPoints;
  std::vector<gridPoint> scheduledGridPoints;

  for(unsigned int i=0; i < objMesh.getNumGroups(); ++i)
  {
    const ObjMesh::Group * group = objMesh.getGroupHandle(i);

    for (unsigned int j=0; j<group->getNumFaces(); ++j)
    {
      Vec3d p0 = objMesh.getPosition(group->getFace(j).getVertex(0).getPositionIndex());
      Vec3d p1 = objMesh.getPosition(group->getFace(j).getVertex(1).getPositionIndex());
      Vec3d p2 = objMesh.getPosition(group->getFace(j).getVertex(2).getPositionIndex());

      TriangleBasic triangle(p0,p1,p2);
      
      Vec3d center = 1.0/3 * (p0 + p1 + p2);
      Vec3d recCenter = center - bmin_;

      int vi,vj,vk;

      vi = (int)(recCenter[0] / gridX);
      vj = (int)(recCenter[1] / gridY);
      vk = (int)(recCenter[2] / gridZ);

      checkedGridPoints.clear();
      checkedGridPoints.insert(gridPoint(vi, vj, vk));

      scheduledGridPoints.clear();
      scheduledGridPoints.push_back(gridPoint(vi,vj,vk));

      while (!scheduledGridPoints.empty())
      {
        gridPoint v = scheduledGridPoints.back();
        scheduledGridPoints.pop_back();

        Vec3d bbmin = bmin_ + Vec3d(v.first * gridX, v.second * gridY, v.third * gridZ);
        Vec3d bbmax = bbmin + Vec3d(gridX, gridY, gridZ);

        BoundingBox bbox(bbmin, bbmax);

        if (triangle.doesIntersectBox(bbox))
        {
          //surfaceVoxels.insert(v);
          //floodFillTag[(v.third * (resolutionY+1) + v.second) * (resolutionX + 1) + v.first] = 1;

          gridPoint neighbor;
          vegalong index;
          #define TAGNEIGHBOR(ii,jj,kk)\
          neighbor = gridPoint(v.first+(ii), v.second+(jj), v.third+(kk));\
          if ((neighbor.first <= resolutionX) &&\
              (neighbor.second <= resolutionY) &&\
              (neighbor.third <= resolutionZ))\
          {\
            index = (neighbor.third * (resolutionY+1) + neighbor.second) * (resolutionX + 1) + neighbor.first;\
                  surfaceGridPoints.push_back(index);\
          }

          for (int iii=0; iii<=1; ++iii)
            for (int jjj=0; jjj<=1; ++jjj)
              for (int kkk=0; kkk<=1; ++kkk)
              {
                TAGNEIGHBOR(iii, jjj, kkk);
              }


          #define CHECKNEIGHBOR(ii,jj,kk)\
          neighbor = gridPoint(v.first+(ii), v.second+(jj), v.third+(kk));\
                if ((neighbor.first >= 0) && (neighbor.first <= resolutionX) &&\
              (neighbor.second >= 0) && (neighbor.second <= resolutionY) &&\
              (neighbor.third >= 0) && (neighbor.third <= resolutionZ))\
          {\
            if (checkedGridPoints.find(neighbor) == checkedGridPoints.end())\
            {\
              checkedGridPoints.insert(neighbor);\
              scheduledGridPoints.push_back(neighbor);\
            }\
          }

          for (int iii=-1; iii<=1; ++iii)
            for (int jjj=-1; jjj<=1; ++jjj)
              for (int kkk=-1; kkk<=1; ++kkk)
              {
                if ((iii == 0) && (jjj == 0) && (kkk == 0))
                  continue;

                CHECKNEIGHBOR(iii, jjj, kkk);
              }
        }
      }
    }
  }
}

void DistanceFieldNarrowBand::offsetDistanceField(double offset)
{
  for(std::map<gridPoint, float>::iterator it = distanceData.begin(); it != distanceData.end(); it++)
    it->second += (float) offset;
}

