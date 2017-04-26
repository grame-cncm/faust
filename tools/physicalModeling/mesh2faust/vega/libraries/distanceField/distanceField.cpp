/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "distance field" library , Copyright (C) 2007 CMU, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Hongyi Xu, Yijing Li                     *
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
  This code generates a distance filed, either signed or unsigned, 
  to the given triangle mesh.

  The distance field can be loaded/saved to a file.
  You can also lookup the field (once computed or loaded) at arbitrary 
  locations inside the field, using trilinear interpolation.

  Input mesh need not have triangle faces (e.g., can have quads; 
  they will be triangulated).

  For signed field generation, the input mesh must be a closed manifold mesh.

  Input mesh must be given in the .obj format:
  http://www.royriggs.com/obj.html

  By default, the bounding box will be a cube, obtained by fitting the  
  smallest cube to the geometry, and then expanded (scaled) from its 
  center by a factor of 1.5. You can provide your own bounding boxes. 
  However, note: (1) the provided bounding box must cover all the geometry, 
  and (2) bounding boxes that are not cubes were not (yet) tested.

  The bounding box will be divided into a "resolution" number of 
  cubes ("voxels") along each axis. The distance field will be computed at the 
  vertices of these voxels. So, if resolution is 256, the bounding box 
  will get divided into 256 x 256 x 256 voxels, and the distance field 
  will be computed on the resulting 257 x 257 x 257 grid of voxel vertices. 
  Note that when indexing voxels, the indices (i,j,k) will run from 0 to 255 
  inclusive, whereas when indexing voxel vertices (also called "grid vertices"), 
  they will run from 0 to 256 inclusive.

  Distance field data is stored at voxel vertices. 
  In memory, distance field value at voxel vertex (i,j,k) is stored 
  at location k * (resolutionX+1)*(resolutionY+1) + j * (resolutionX+1) + i .

  Internally, the code builds an octree on top of the triangle mesh. 
  There are two parameters that control this process (you can keep them 
  at default values, which worked well in practice for us) :
  the max depth of the octree is "maxDepth", and
  the max number of triangles intersecting an octree cell is "maxTriCount".
  Note: once max depth level is reached, the maxTriCount bound is not imposed any more.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <fstream>
#include <set>
#include "triangle.h"
#include "triple.h"
#include "boundingBox.h"
#include "distanceField.h"
#include "trilinearInterpolation.h"
#include "vegalong.h"
using namespace std;

//#define GENERATE_DEBUG_DATA

vegalong DistanceField::GetFilesize(const char *filename)
{
  FILE * f = fopen(filename, "rb");  /* open the file in read only */

  vegalong size = 0;
  if (fseek(f,0,SEEK_END)==0) /* seek was successful */
      size = ftell(f);
  fclose(f);
  return size;
}

DistanceField::DistanceField() : DistanceFieldBase()
{ 
  distanceData = NULL;
  pseudoData = NULL;
  computeVoronoiDiagram = false;
  voronoiDiagram = NULL;
  minBoundaryDistance = 0;
  floodFillTag = NULL;
}

DistanceField::DistanceField(int resolutionX_, int resolutionY_, int resolutionZ_): DistanceFieldBase(resolutionX_, resolutionY_, resolutionZ_)
{
  distanceData = NULL;
  pseudoData = NULL;
  computeVoronoiDiagram = false;
  voronoiDiagram = NULL;
  minBoundaryDistance = 0;
  floodFillTag = NULL;
  
  distanceData = (float*) malloc (sizeof(float)*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));
}

DistanceField::~DistanceField()
{
  free(distanceData); 
  free(pseudoData); 
  free(floodFillTag);
  free(voronoiDiagram);
}

void DistanceField::enableVoronoiDiagramComputation(bool computeVoronoiDiagram)
{
  this->computeVoronoiDiagram = computeVoronoiDiagram;
}

// the routines for signed and unsigned distance field computation
#define COMPUTE_SIGNED_FIELD
  #define COMPUTE_FLOOD_FIELD
    #include "computeField.cpp"
  #undef COMPUTE_FLOOD_FIELD
    #include "computeField.cpp"
#undef COMPUTE_SIGNED_FIELD
  #include "computeField.cpp"

int DistanceField::load(const std::string& filename)
{
  ifstream fin(filename.c_str(),ios::binary);
  if (!fin)
    return 1;

  fin.read((char*)&resolutionX, sizeof(int));

  // the type of data (single-precision or double-precision) is encoded
  //   as the sign of the x-resolution
  bool floatData = (resolutionX < 0);
  if (floatData)
    resolutionX = -resolutionX;

  fin.read((char*)&resolutionY, sizeof(int));

  if (resolutionY < 0) // negative second resolution implies closest point data
    return 1;

  fin.read((char*)&resolutionZ, sizeof(int));

  fin.read((char*)&(bmin_[0]), sizeof(double));
  fin.read((char*)&(bmin_[1]), sizeof(double));
  fin.read((char*)&(bmin_[2]), sizeof(double));

  fin.read((char*)&(bmax_[0]), sizeof(double));
  fin.read((char*)&(bmax_[1]), sizeof(double));
  fin.read((char*)&(bmax_[2]), sizeof(double));

  setGridParameters();

  distanceData = (float*) realloc (distanceData, sizeof(float) * (resolutionX+1) * (resolutionY+1) * (resolutionZ+1));

  float * distanceDataPos = distanceData;
  int sliceResolution = (resolutionX+1) * (resolutionY+1);
  int unitSize = floatData ? sizeof(float) : sizeof(double);
  for(int k=0; k <= resolutionZ; k++, distanceDataPos += sliceResolution)
    fin.read((char*)distanceDataPos, unitSize * sliceResolution);
  //printf("\n");
  fin.close();

  return 0;
}

int DistanceField::openStreamDistanceField(const std::string& filename, Vec3d * bmin, Vec3d * bmax, int * resolutionX, int * resolutionY, int * resolutionZ, bool * floatData, ifstream & fin)
{
  fin.open(filename.c_str(),ios::binary);
  if (!fin)
    return 1;

  fin.read((char*)resolutionX, 4);

  // the type of data (single-precision or double-precision) is encoded
  //   as the sign of the x-resolution
  *floatData = (*resolutionX < 0);
  if (*floatData)
    *resolutionX = - *resolutionX;
   
  fin.read((char*)resolutionY, 4); 

  if (*resolutionY < 0) // negative second resolution implies closest point data
    return 1;

  fin.read((char*)resolutionZ, 4);

  double bminx, bminy, bminz;
  fin.read((char*)&bminx, 8);
  fin.read((char*)&bminy, 8);
  fin.read((char*)&bminz, 8);

  double bmaxx, bmaxy, bmaxz;
  fin.read((char*)&bmaxx, 8);
  fin.read((char*)&bmaxy, 8);
  fin.read((char*)&bmaxz, 8);

  (*bmin)[0] = bminx;
  (*bmin)[1] = bminy;
  (*bmin)[2] = bminz;

  (*bmax)[0] = bmaxx;
  (*bmax)[1] = bmaxy;
  (*bmax)[2] = bmaxz;

  return 0;
}

void DistanceField::retrieveZSlice(ifstream & fin, bool floatData, int resolutionX, int resolutionY, int resolutionZ, float * slice)
{
  double * buffer = (double*) malloc (sizeof(double) * (resolutionX+1) * (resolutionY+1)); // place for one slice

  float * distanceDataPos = slice;

  if (floatData)
    fin.read((char*)buffer, sizeof(float) * (resolutionX+1) * (resolutionY+1));
  else
    fin.read((char*)buffer, sizeof(double) * (resolutionX+1) * (resolutionY+1));

  char * bufferPos = (char*)buffer;
  int bufferPosInc = floatData ? sizeof(float) : sizeof(double);

  // copy data to the slice
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

void DistanceField::set(int resolutionX, int resolutionY, int resolutionZ, Vec3d bmin_, Vec3d bmax_, float * distanceData)
{
  this->resolutionX = resolutionX;
  this->resolutionY = resolutionY;
  this->resolutionZ = resolutionZ;
  this->bmin_ = bmin_; 
  this->bmax_ = bmax_; 

  setGridParameters();

  free(this->distanceData);
  this->distanceData = (float*) malloc (sizeof(float)*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));
  memcpy(this->distanceData, distanceData, sizeof(float)*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1));
}

int DistanceField::isDoublePrecision(const std::string & filename, bool & doublePrecision)
{
  ifstream fin(filename.c_str(),ios::binary);
  if (!fin)
    return 1;

  int res;
  fin.read((char*)&res,4);

  // the type of data (single-precision or double-precision) is encoded
  //   as the sign of the x-resolution
  doublePrecision = (res >= 0);

  fin.close();

  return 0;
}

int DistanceField::saveToText(const std::string& filename)
{
  FILE * fout = fopen((char*)filename.c_str(), "w");
  if (!fout)
    return 1;

  fprintf(fout, "%d\n", resolutionX);
  fprintf(fout, "%d\n", resolutionY);
  fprintf(fout, "%d\n", resolutionZ);

  for(int i=0; i<=resolutionX; i++)
    for(int j=0; j<=resolutionY; j++)
      for(int k=0; k<=resolutionZ; k++)
      {
        fprintf(fout,"%G\n", distance(i,j,k));
      }

  fclose(fout);

  return 0;
}

int DistanceField::save(const std::string& filename, bool doublePrecision)
{
  if (doublePrecision)
    printf("Error: double precision output is not supported. Using float instead.\n");
  doublePrecision = false;

  ofstream fout(filename.c_str(),ios::binary);

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

  // float precision
  //fout.write((char*)distanceData,sizeof(float)*(resolutionX+1)*(resolutionY+1)*(resolutionZ+1)); // this version sometimes resulted in the field incorrectly written to file (unclear why)

  for(int k=0; k<=resolutionZ; k++)
    for(int j=0; j<=resolutionY; j++)
      for(int i=0; i<=resolutionX; i++)
      {
        fout.write((char*)&distanceData[k * (resolutionX+1)*(resolutionY+1) + j * (resolutionX+1) + i], sizeof(float));
      }

/*
  if (doublePrecision)
    fout.write((char*)distanceData,sizeof(double)*(resolution+1)*(resolution+1)*(resolution+1));
  else
  {
    float * buffer;
    convertToFloat(&buffer);
    fout.write((char*)buffer,sizeof(float)*(resolution+1)*(resolution+1)*(resolution+1));
    free(buffer);
  }
*/
  fout.close();

  #ifdef GENERATE_DEBUG_DATA
    ofstream fout1("debugPseudo", ios::binary);
    fout1.write((char*)pseudoData, 6*sizeof(float)*(resolution+1)*(resolution+1)*(resolution+1));
    fout1.close();
  #endif

  return 0;
}

int DistanceField::saveVoronoiDiagram(const std::string& filename)
{
  if (voronoiDiagram == NULL)
  {
    printf("Error in saveVoronoiDiagram: Voronoi diagram has not been computed.\n");
    return 1;
  }

  ofstream fout(filename.c_str(), ios::binary);

  int header = 0;

  fout.write((char*)&header,sizeof(int));
  fout.write((char*)&resolutionX,sizeof(int));
  fout.write((char*)&resolutionY,sizeof(int));
  fout.write((char*)&resolutionZ,sizeof(int));

  fout.write((char*)&(bmin_[0]),sizeof(double));
  fout.write((char*)&(bmin_[1]),sizeof(double));
  fout.write((char*)&(bmin_[2]),sizeof(double));

  fout.write((char*)&(bmax_[0]),sizeof(double));
  fout.write((char*)&(bmax_[1]),sizeof(double));
  fout.write((char*)&(bmax_[2]),sizeof(double));

  fout.write((char*)voronoiDiagram, sizeof(int) * (resolutionX+1) * (resolutionY+1) * (resolutionZ+1));

  fout.close();

  return 0;
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

bool DistanceField::sanityCheck()
{
  //double diagonal = sqrt(gridX*gridX + gridY*gridY + gridZ*gridZ);

  bool result = true;
  int count = 0;

  const int numErrorsPrinted = 3;

  vector<errorData> relErrors;
  errorData emptyEntry = {0,0,0,0,0,0,0.0,0.0,-1.0};
  for(int i=0; i<numErrorsPrinted; i++)
   relErrors.push_back(emptyEntry);

  for (int k=0; k <= resolutionZ; k++)
  {
    for (int j=0; j <= resolutionY; j++)
      for (int i=0; i <= resolutionX; i++)
      {
        float d = distance(i,j,k);
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
          gridDist = (float) len(Vec3d((di)*gridX,(dj)*gridY,(dk)*gridZ));\
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

      }
    cout << "." << flush;
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

float DistanceField::distance(Vec3d pos, int constrainToBox)
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
  
  //printf("I=%d J=%d K=%d\n", i,j,k);
  //printf("remx=%f remy=%f remz=%f\n", pos[0] - bmin_[0] - gridX * i,
  //        pos[1] - bmin_[1] - gridY * j, pos[2] - bmin_[2] - gridZ * k);

  double wx,wy,wz;
  wx = ((pos[0]-bmin_[0]) / gridX) - i;
  wy = ((pos[1]-bmin_[1]) / gridY) - j;
  wz = ((pos[2]-bmin_[2]) / gridZ) - k;

  return (float) (TRILINEAR_INTERPOLATION(wx,wy,wz,distance(i,j,k),distance(i+1,j,k),distance(i+1,j+1,k),distance(i,j+1,k),
                                distance(i,j,k+1),distance(i+1,j,k+1),distance(i+1,j+1,k+1),distance(i,j+1,k+1)));
}

float DistanceField::maxValue()
{
  float maxValue=-FLT_MAX;
  for (int k=0; k <= resolutionZ; k++)
    for (int j=0; j <= resolutionY; j++)
      for (int i=0; i <= resolutionX; i++)
      {
        float dist = distance(i,j,k);
        if (dist > maxValue)
          maxValue = dist;
      }
  return maxValue;
}

float DistanceField::minValue()
{
  float minValue=FLT_MAX;
  for (int k=0; k <= resolutionZ; k++)
    for (int j=0; j <= resolutionY; j++)
      for (int i=0; i <= resolutionX; i++)
      {
        float dist = distance(i,j,k);
        if (dist < minValue)
          minValue = dist;
      }
  return minValue;
}

void DistanceField::maxMinValue(float* maxValue, float* minValue)
{
  *minValue=FLT_MAX;
  *maxValue=-FLT_MAX;
  for (int k=0; k <= resolutionZ; k++)
    for (int j=0; j <= resolutionY; j++)
      for (int i=0; i <= resolutionX; i++)
      {
        float dist = distance(i,j,k);
        if (dist < *minValue)
          *minValue = dist;
        if (dist > *maxValue)
          *maxValue = dist;
      }
}

float DistanceField::maxAbsValue()
{
  float maxValue=0;
  for (int k=0; k <= resolutionZ; k++)
    for (int j=0; j <= resolutionY; j++)
      for (int i=0; i <= resolutionX; i++)
      {
        float dist = fabs(distance(i,j,k));
        if (dist > maxValue)
          maxValue = dist;
      }
  return maxValue;
}

float DistanceField::maxNonInftyAbsValue()
{
  float maxValue=0;
  for (int k=0; k <= resolutionZ; k++)
    for (int j=0; j <= resolutionY; j++)
      for (int i=0; i <= resolutionX; i++)
      {
        float dist = fabs(distance(i,j,k));
        if ((dist > maxValue) && (dist != FLT_MAX))
          maxValue = dist;
      }
  return maxValue;
}

float DistanceField::maxAbsValue(float threshold)
{
  float maxValue=0;
  for (int k=0; k <= resolutionZ; k++)
    for (int j=0; j <= resolutionY; j++)
      for (int i=0; i <= resolutionX; i++)
      {
        float dist = fabs(distance(i,j,k));
        if ((dist > maxValue) && (dist < threshold))
          maxValue = dist;
      }
  return maxValue;
}

Vec3d DistanceField::gradient(const Vec3d& pos)
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

  float v000 = distance(i,j,k);
  float v100 = distance(i+1,j,k);
  float v110 = distance(i+1,j+1,k);
  float v010 = distance(i,j+1,k);
  float v001 = distance(i,j,k+1);
  float v101 = distance(i+1,j,k+1);
  float v111 = distance(i+1,j+1,k+1);
  float v011 = distance(i,j+1,k+1);

  return Vec3d(
    GRADIENT_COMPONENT_X(wx,wy,wz,v000,v100,v110,v010,v001,v101,v111,v011),
    GRADIENT_COMPONENT_Y(wx,wy,wz,v000,v100,v110,v010,v001,v101,v111,v011),
    GRADIENT_COMPONENT_Z(wx,wy,wz,v000,v100,v110,v010,v001,v101,v111,v011) );
                              
}

void DistanceField::getDistanceData(float ** floatBuffer)
{
  unsigned int size = (resolutionX+1) * (resolutionY+1) * (resolutionZ+1);
  *floatBuffer = (float*) malloc (sizeof(float) * size);
  memcpy(*floatBuffer, distanceData, sizeof(float) * size);
  //for(unsigned int i=0; i< size; i++)
    //(*floatBuffer)[i] = (float) (distanceData[i]);
}


/*
void DistanceField::convertToFloat(float ** floatBuffer)
{
  unsigned int size = (resolutionX+1) * (resolutionY+1) * (resolutionZ+1);
  *floatBuffer = (float*) malloc (sizeof(float) * size);
  for(unsigned int i=0; i< size; i++)
    (*floatBuffer)[i] = (float) (distanceData[i]);
}
*/

/*
void DistanceField::convertToDouble(double ** doubleBuffer)
{
  unsigned int size = (resolutionX+1) * (resolutionY+1) * (resolutionZ+1);
  *doubleBuffer = (double*) malloc (sizeof(double) * size);
  memcpy(*doubleBuffer, distanceData, sizeof(double) * size);
}
*/

bool DistanceField::isSurfaceVoxel(int i, int j, int k)
{
  float v[8];
  v[0] = distance(i,j,k);
  v[1] = distance(i+1,j,k);
  v[2] = distance(i+1,j+1,k);
  v[3] = distance(i,j+1,k);
  v[4] = distance(i,j,k+1);
  v[5] = distance(i+1,j,k+1);
  v[6] = distance(i+1,j+1,k+1);
  v[7] = distance(i,j+1,k+1);

  bool allPositive = true;
  for(int l=0; l<8; l++)
    if (v[l] < 0)
    {
      allPositive = false;
      break;
    }

  bool allNegative = true;
  for(int l=0; l<8; l++)
    if (v[l] >= 0)
    {
      allNegative = false;
      break;
    }

  return (!allNegative && !allPositive);
}

bool DistanceField::isSurfaceVoxel(int customResolutionX, int customResolutionY, int customResolutionZ, int i, int j, int k, float levelSetValue)
{
  //printf("i: %d j:%d k:%d\n",i,j,k);
  Vec3d customGrid;
  customGrid[0] = 1.0 * side[0] / customResolutionX;
  customGrid[1] = 1.0 * side[1] / customResolutionY;
  customGrid[2] = 1.0 * side[2] / customResolutionZ;
  
  Vec3d basePos = bmin_ + Vec3d( 1.0 * i * customGrid[0], 1.0 * j * customGrid[1], 1.0 * k * customGrid[2] );

  if (((i < 0) || (i >= customResolutionX)) && ((j < 0) || (j >= customResolutionY)) && ((k < 0) || (k >= customResolutionZ)))
  {
    printf("Warning (inside isSurfaceVoxel): voxel insides specified outside of the bounding box: (i,j,k)=(%d,%d,%d), customResolution=(%d,%d,%d)\n", i, j, k, customResolutionX, customResolutionY, customResolutionZ);
  }

  // pass parameter 1 to constrain to box
  float v[8];
  v[0] = distance(basePos, 1) - levelSetValue;
  v[1] = distance(basePos + Vec3d(customGrid[0], 0, 0), 1) - levelSetValue;
  v[2] = distance(basePos + Vec3d(customGrid[0], customGrid[1], 0), 1) - levelSetValue;
  v[3] = distance(basePos + Vec3d(0, customGrid[1], 0), 1) - levelSetValue;
  v[4] = distance(basePos + Vec3d(0, 0, customGrid[2]), 1) - levelSetValue;
  v[5] = distance(basePos + Vec3d(customGrid[0], 0, customGrid[2]), 1) - levelSetValue;
  v[6] = distance(basePos + Vec3d(customGrid[0], customGrid[1], customGrid[2]), 1) - levelSetValue;
  v[7] = distance(basePos + Vec3d(0, customGrid[1], customGrid[2]), 1) - levelSetValue;

/*
  double v[8];
  v[0] = distance(i,j,k);
  v[1] = distance(i+1,j,k);
  v[2] = distance(i+1,j+1,k);
  v[3] = distance(i,j+1,k);
  v[4] = distance(i,j,k+1);
  v[5] = distance(i+1,j,k+1);
  v[6] = distance(i+1,j+1,k+1);
  v[7] = distance(i,j+1,k+1);
*/

  bool allPositive = true;
  for(int l=0; l<8; l++)
    if (v[l] < 0)
    {
      allPositive = false;
      break;
    }

  bool allNegative = true;
  for(int l=0; l<8; l++)
    if (v[l] >= 0)
    {
      allNegative = false;
      break;
    }

  return (!allNegative && !allPositive);
}

int DistanceField::numSurfaceVoxels(float levelSetValue)
{
  return numSurfaceVoxels(resolutionX, resolutionY, resolutionZ, levelSetValue);
}

int DistanceField::numSurfaceVoxels(int customResolutionX, int customResolutionY, int customResolutionZ, float levelSetValue)
{
  printf("num surface voxels... custom res: (%d,%d,%d)\n", customResolutionX, customResolutionY, customResolutionZ);
  int count = 0;

  for(int k=0; k<customResolutionZ; k++)
    for(int j=0; j<customResolutionY; j++)
      for(int i=0; i<customResolutionX; i++)
        if (isSurfaceVoxel(customResolutionX, customResolutionY, customResolutionZ, i, j, k, levelSetValue))
          count++;

  return count;
}

float DistanceField::minBoundaryValue()
{
  float minDistance = FLT_MAX;
  for(int k=0; k <= resolutionZ; k++)
    for(int j=0; j <= resolutionY; j++)
      for(int i=0; i <= resolutionX; i += resolutionX)
      {
        float value = distance(i,j,k);
        if (value < minDistance)
          minDistance = value;
      }

  for(int k=0; k <= resolutionZ; k++)
    for(int j=0; j <= resolutionY; j += resolutionY)
      for(int i=0; i <= resolutionX; i++)
      {
        float value = distance(i,j,k);
        if (value < minDistance)
          minDistance = value;
      }

  for(int k=0; k <= resolutionZ; k += resolutionZ)
    for(int j=0; j <= resolutionY; j++)
      for(int i=0; i <= resolutionX; i++)
      {
        float value = distance(i,j,k);
        if (value < minDistance)
          minDistance = value;
      }

  minBoundaryDistance = minDistance;
  return minDistance;
}

void DistanceField::print()
{
  for(int k=0; k <= resolutionX; k++)
    for(int j=0; j <= resolutionY; j++)
      for(int i=0; i <= resolutionZ; i++)
      {
        printf("i=%d j=%d k=%d d=%G\n", i, j, k, distance(i,j,k));
      }
}

void DistanceField::computeFloodFillTag(ObjMesh* objMeshIn)
{
  ObjMesh objMesh(*objMeshIn);
  vegalong size = sizeof(char) * (resolutionX+1) * (resolutionY+1) * (resolutionZ+1);
  if (floodFillTag != NULL)
    free(floodFillTag);
  floodFillTag = (char*) malloc(size);  
  memset(floodFillTag, 0, sizeof(char) * (resolutionX+1) * (resolutionY+1) * (resolutionZ+1));

  typedef triple<int,int,int> voxel;

  std::set<voxel> checkedVoxels;
  std::vector<voxel> scheduledVoxels;

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

      checkedVoxels.clear();
      checkedVoxels.insert(voxel(vi, vj, vk));

      scheduledVoxels.clear();
      scheduledVoxels.push_back(voxel(vi,vj,vk));

      while (!scheduledVoxels.empty())
      {
        voxel v = scheduledVoxels.back();
        scheduledVoxels.pop_back();

        Vec3d bbmin = bmin_ + Vec3d(v.first * gridX, v.second * gridY, v.third * gridZ);
        Vec3d bbmax = bbmin + Vec3d(gridX, gridY, gridZ);

        BoundingBox bbox(bbmin, bbmax);

        if (triangle.doesIntersectBox(bbox))
        {
          //surfaceVoxels.insert(v);
          //floodFillTag[(v.third * (resolutionY+1) + v.second) * (resolutionX + 1) + v.first] = 1;

          voxel neighbor;
          vegalong index;
          #define TAGNEIGHBOR(ii,jj,kk)\
          neighbor = voxel(v.first+(ii), v.second+(jj), v.third+(kk));\
          if ((neighbor.first <= resolutionX) &&\
              (neighbor.second <= resolutionY) &&\
              (neighbor.third <= resolutionZ))\
          {\
            index = (neighbor.third * (resolutionY+1) + neighbor.second) * (resolutionX + 1) + neighbor.first;\
            floodFillTag[index] = 1;\
          }

          for (int kkk=0; kkk<=1; ++kkk)
            for (int jjj=0; jjj<=1; ++jjj)
              for (int iii=0; iii<=1; ++iii)
              {
                TAGNEIGHBOR(iii, jjj, kkk);
              }


          #define CHECKNEIGHBOR(ii,jj,kk)\
          neighbor = voxel(v.first+(ii), v.second+(jj), v.third+(kk));\
          if ((neighbor.first >= 0) && (neighbor.first <= resolutionX) &&\
              (neighbor.second >= 0) && (neighbor.second <= resolutionY) &&\
              (neighbor.third >= 0) && (neighbor.third <= resolutionZ))\
              {\
            if (checkedVoxels.find(neighbor) == checkedVoxels.end())\
            {\
              checkedVoxels.insert(neighbor);\
              scheduledVoxels.push_back(neighbor);\
            }\
          }

          for (int kkk=-1; kkk<=1; ++kkk)
            for (int jjj=-1; jjj<=1; ++jjj)
              for (int iii=-1; iii<=1; ++iii)
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

double DistanceField::pointCCD(Vec3d startPos, Vec3d endPos)
{
  int constrainToBox = 0;
  double startDist = distance(startPos, constrainToBox);
  double endDist = distance(endPos, constrainToBox);

  if (((startDist > 0) && (endDist > 0)) || (startDist - endDist == 0))
    return -1.0;

  int flip = 0;
  if (startDist > 0)
  {
    flip = 1;
    Vec3d bufv = startPos;
    startPos = endPos;
    endPos = bufv;
    double buf = startDist;
    startDist = endDist;
    endDist = buf;
  }

  // now, startPos is inside, and endPos is outside

  double eps = 1E-12;
  double d;
  Vec3d x;
  double t = 0.0;
  double tLo = 0.0;
  double tHi = 1.0;
  Vec3d xLo = startPos;
  Vec3d xHi = endPos;
  double distLo = startDist;
  double distHi = endDist;
  do
  {
    // distLo + deltaT * (distHi - distLo) = 0
    t += distLo / (distLo - distHi) * (tHi - tLo);
    x = startPos + t * (endPos - startPos);
    d = distance(x, constrainToBox);

    if (d <= 0)
    {
      // lo must go to new point
      tLo = t;
      xLo = x;
      distLo = d;
    }
    else
    {
      // hi must go to new point
      tHi = t;
      xHi = x;
      distHi = d;
    }
  }
  while (fabs(d) > eps);

  if (flip)
    t = 1.0 - t;

  return t;
}

void DistanceField::offsetDistanceField(double offset)
{
  vegalong numGridPoints = (resolutionX+1) * (resolutionY+1) * (resolutionZ+1);

  printf("Applying offset %G to the distance field. Resolution is %d x %d x %d.\n", offset, resolutionX, resolutionY, resolutionZ);

  for(vegalong i=0; i<numGridPoints; i++)
    distanceData[i] += (float) offset;
}

