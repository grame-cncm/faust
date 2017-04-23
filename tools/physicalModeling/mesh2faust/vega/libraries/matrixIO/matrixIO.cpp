/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "matrix" library , Copyright (C) 2007 CMU, 2009 MIT                   *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
 * http://www.jernejbarbic.com/code                                      *
 * Research: Jernej Barbic, Doug L. James, Jovan Popovic                 *
 * Funding: NSF, Link Foundation, Singapore-MIT GAMBIT Game Lab          *
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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "matrixMacros.h"
#include "matrixIO.h"

// writes out the m x n matrix onto the stream, in binary format
// LAPACK column-major order
template <class real>
int WriteMatrixToStream(FILE * file, int m, int n, const real * matrix)
{
  if ((int)(fwrite(matrix,sizeof(real),m*n,file)) < m*n)
    return 1;
  return 0;
}

// writes out the m x n matrix header onto the stream
int WriteMatrixHeaderToStream(FILE * file, int m, int n)
{
  if (fwrite(&m,sizeof(int),1,file) < 1)
    return 1;

  if (fwrite(&n,sizeof(int),1,file) < 1)
    return 1;

  return 0;
}


template <class real>
int WriteMatrixToDisk(const char * filename, int m, int n, const real * matrix)
{
  FILE * file;
  file = fopen(filename, "wb");
  if (!file)
  {
    printf ("Can't open output file: %s.\n", filename);
    return 1;
  }

  if (WriteMatrixHeaderToStream(file,m,n) != 0)
  {
    printf ("Error writing the matrix header to disk file: %s.\n", filename);
    return 1;
  }

  if (WriteMatrixToStream(file,m,n,matrix) != 0)
  {
    printf ("Error writing the matrix to disk file: %s.\n", filename);
    return 1;
  }

  fclose(file);

  return 0;
}

template <class real>
int AppendMatrixToDisk(const char * filename, int mAppendix, int nAppendix, const real * matrixAppendix)
{
  int m, n;
  real * matrix;
  int code = ReadMatrixFromDisk(filename, &m, &n, &matrix);
  if (code != 0)
  {
    printf ("Can't open output file: %s.\n", filename);
    return 1;
  }

  if (mAppendix != m)
  {
    printf ("The existing matrix %s and appendix matrix do not have the same number of rows.\n", filename);
    return 1;
  }

  matrix = (real*) realloc (matrix, sizeof(real) * mAppendix * (n + nAppendix));
  memcpy(&matrix[mAppendix * n], matrixAppendix, sizeof(real) * mAppendix * nAppendix);

  code = WriteMatrixToDisk(filename, mAppendix, n + nAppendix, matrix);
  if (code != 0)
  {
    printf ("Error writing the matrix to disk file: %s.\n", filename);
    return 1;
  }

  free(matrix);

  return 0;
}

// read the m x n matrix from the stream, in binary format
template <class real>
int ReadMatrixFromStream(FILE * file, int M, int N, real * matrix)
{
  unsigned int readBytes;
  if ((readBytes = fread(matrix,sizeof(real),M*N,file)) < (unsigned int)M*N)
  {
    printf("Error: I have only read %u bytes. sizeof(real)=%lu\n", readBytes, sizeof(real));
    return 1;
  }

  return 0;
}

template <class real>
int ReadMatrixFromDisk(const char * filename, int * m, int * n, real ** matrix)
{
  FILE * file;
  file = fopen(filename ,"rb");
  if (!file)
  {
    printf ("Can't open input matrix file: %s.\n", filename);
    return 1;
  }

  if (ReadMatrixSizeFromStream(file,m,n) != 0)
  {
    printf ("Error reading matrix header from disk file: %s.\n", filename);
    return 1;
  }

  //int size = (*m) * (*n) * sizeof(real) + 2 * sizeof(int);

  *matrix = (real *) malloc (sizeof(real)*(*m)*(*n));

  if (ReadMatrixFromStream(file,*m,*n,*matrix) != 0)
  {
    printf ("Error reading matrix data from disk file: %s.\n", filename);
    return 1;
  }

  fclose(file);

  return 0;
}

template <class real>
int ReadMatrixFromDiskListOfFiles(const char * fileList, int * m, int * n, real ** matrix)
{
  FILE * jobFileList = fopen(fileList,"r");

  if (!jobFileList)
  {
    printf("Couldn't open matrix list file %s.\n", fileList);
    return 1;
  }

  *n = 0;

  // pass 1: determine the total number of columns
  char matrixFilename[4096];
  int totalFiles = 0;
  while (fgets(matrixFilename,4096,jobFileList) != NULL)
  {
    // remove trailing newline character from matrixFilename
    int k=0;
    while (matrixFilename[k] != '\0')
      k++;

    if ((k > 0) && (matrixFilename[k-1] == '\n'))
      matrixFilename[k-1] = '\0';
     
    if (k <= 1) // blank line, ignore it
      continue;
    
    totalFiles++;
    if (totalFiles % 100 == 1)
      printf ("\nPass 1: Processing input file: %s.\n",matrixFilename);

    // determine the number of degrees of freedom
    int M,N;
    if (ReadMatrixSizeFromDisk(matrixFilename,&M,&N) != 0)
    {
      printf("Error: couldn't load mode information from file %s.\n",matrixFilename);
      return 1;
    }

    printf("%d ",N); fflush(NULL);

    if (*n == 0)
    {
      // register the number of degrees of freedom
      *m = M; 
    }
    else // compare the current length to the length of the first vector
    {
      if (M != *m)
      {
        printf("Error: length of vector (%d x %d) from file %s is not the same as for the other vectors (%d x 1).\n",M,N,matrixFilename,*m);
        return 1;
      }
    }

    *n += N; // this file contained N columns
  }

  printf("\n");

  // now, *m contains the number of rows
  // *n equals the total number of columns

  printf("Creating %d x %d matrix... (%G Mb)\n", *m, *n, 1.0 * sizeof(double) * (*m) * (*n) / 1024 / 1024);
  *matrix = (real*) malloc (sizeof(real) * (*m) * (*n));
  
  rewind(jobFileList);

  // pass 2: assemble the files together
  totalFiles = 0;
  real * currentMatrix; 
  int currentColumn = 0;
  while (fgets(matrixFilename,4096,jobFileList) != NULL)
  {
    // remove trailing newline character from matrixFilename
    int k=0;
    while (matrixFilename[k] != '\0')
    {
      k++;
    }
    if ((k > 0) && (matrixFilename[k-1] == '\n'))
      matrixFilename[k-1] = '\0';
     
    if (k <= 1) // blank line, ignore it
      continue;

    totalFiles++;

    if (totalFiles % 100 == 1)
      printf ("Pass 2: Processing input file: %s.\n",matrixFilename);

    // read the deformations from file 'matrixFilename'
    int M,N;
    if (ReadMatrixFromDisk(matrixFilename, &M, &N, &currentMatrix) != 0)
    {
      printf("Couldn't load matrix from file %s.\n",matrixFilename);
      return 1;
    }

    memcpy(&(*matrix)[ELT(*m,0,currentColumn)], currentMatrix, sizeof(real) * M * N);

    printf("%d ",N); fflush(NULL);

    free(currentMatrix);

    currentColumn += N;
  }
  
  fclose(jobFileList);

  printf("Matrix has been loaded (from %d files).\n", totalFiles);
  
  return 0;
}

template <class real>
int WriteMatrixToDisk_(const char * filename, int m, int n, const real * matrix)
{
  if (WriteMatrixToDisk(filename, m, n, matrix) != 0)
    exit(1);

  return 0;
}

template <class real>
int AppendMatrixToDisk_(const char * filename, int mAppendix, int nAppendix, const real * matrixAppendix)
{
  if (AppendMatrixToDisk(filename, mAppendix, nAppendix, matrixAppendix) != 0)
    exit(1);

  return 0;
}

template <class real>
int ReadMatrixFromDisk_(const char * filename, int * m, int * n, real ** matrix)
{
  if (ReadMatrixFromDisk(filename, m, n, matrix) != 0)
    exit(1);

  return 0;
}

int ReadMatrixSizeFromDisk(const char * filename, int * m, int * n)
{
  FILE * file;
  file = fopen(filename, "rb");
  if (!file)
  {
    printf ("Can't open input matrix file: %s.\n", filename);
    return 1;
  }

  if (fread(m,sizeof(int),1,file) < 1)
    return 1;

  if (fread(n,sizeof(int),1,file) < 1)
    return 1;

  fclose(file);

  return 0;
}

void ReadMatrixSizeFromDisk_(const char * filename, int * m, int * n)
{
  if (ReadMatrixSizeFromDisk(filename, m, n) != 0)
    exit(1);
}

int ReadMatrixSizeFromStream(FILE * file, int * m, int * n)
{
  if (fread(m,sizeof(int),1,file) < 1)
    return 1;

  if (fread(n,sizeof(int),1,file) < 1)
    return 1;

  return 0;
}

int OpenFile_(const char * filename, FILE ** fin, const char * mode)
{
  *fin = fopen(filename, mode);
  if (!(*fin))
  {
    printf("Error: could not open file %s.\n", filename);
    exit(1);
  }

  return 0;
}

void Abort_(const char * reason)
{
  Abort_(reason,1);
}

void Abort_(const char * reason, int exitCode)
{
  printf("%s\n",reason);
  exit(exitCode);
}

int Assert_(int a, int b, int positionIdentifier)
{
  if (a != b)
  {
    printf("Error: assertion %d == %d failed (%d).\n",a,b,positionIdentifier);
    exit(1);
  }
  return 0;
}

int Assert_(bool cond, int positionIdentifier)
{
  if (!cond)
  {
    printf("Error: assertion failed (%d).\n",positionIdentifier);
    exit(1);
  }
  return 0;
}

// prints the matrix out to stdout in Mathematica format
template <class real>
void PrintMatrixInMathematicaFormat(int n, int r, real * U)
{
  printf("{\n");

  for(int i=0; i<n; i++)
  {
    printf("{");
    for(int j=0; j<r; j++)
    {
      printf("%.15f",U[ELT(n,i,j)]);
      if (j != r-1)
	printf(", ");
    }
    printf("}");

    if (i != n-1)
      printf(",\n");
  }

  printf("\n}\n");
}

void ChangeMatrixHeader(const char * filename, int numRows, int numColumns)
{
  FILE * fin = fopen(filename, "r+");
  fwrite(&numRows,sizeof(int),1,fin);
  fwrite(&numColumns,sizeof(int),1,fin);
  fclose(fin);
}

template <class T>
int ReadBinary(FILE * fin, T * data)
{
  if (fread(data,sizeof(T),1,fin) < 1)
    return 1;

  return 0;
}


template <class T>
void ReadBinary_(FILE * fin, T * data)
{
  if (ReadBinary<T>(fin,data) != 0)
  {
    printf("Read binary: Error reading data.\n");
    exit(1);
  }
}

template <class T>
int ReadBinaryBuffer(FILE * fin, int size, T * data)
{
  if (fread(data,sizeof(T),size,fin) < (unsigned int)size)
    return 1;

  return 0;
}

template <class T>
void ReadBinaryBuffer_(FILE * fin, int size, T * data)
{
  if (ReadBinaryBuffer<T>(fin,size,data) != 0)
  {
    printf("Read binary buffer: Error reading data.\n");
    exit(1);
  }
}

template <class real>
int ReadMatrixFromDiskTextFile(const char * filename, int * m, int * n, real ** matrix)
{
  // open input
  FILE * file;
  file = fopen(filename, "r");
  if (!file)
  {
    printf("Error: couldn't open input file %s.\n", filename);
    return 1;
  }

  // parse dimensions
  if (fscanf(file,"%d\n",m) < 1)
  {
    printf ("ReadMatrixFromDiskTextFile: failed to read the number of rows.\n");
    return 1;
  }

  if (fscanf(file,"%d\n",n) < 1)
  {
    printf ("ReadMatrixFromDiskTextFile: failed to read the number of columns.\n");
    return 1;
  }

  if (*m <= 0)
  {
    printf("Error: bad parameter for the number of rows: %d.\n", *m);
    return 1;
  }

  if (*n <= 0)
  {
    printf("Error: bad parameter for the number of columns: %d.\n", *n);
    return 0;
  }

  // allocate space
  *matrix = (real *)malloc(sizeof(real)* *m* *n);
  real data;

  int i=0;

  int bufSize = *n * 100;
  char * buf = (char*) malloc (sizeof(char) * bufSize);

  char sscanfFormat[4] = "%lf";
  if (sizeof(real) == sizeof(float))
    strcpy(sscanfFormat,"%f");

  while(fgets(buf,bufSize,file) != NULL)
  {
    /*
    if (i % 100 == 1)
    {
      printf("%d ",i);
      fflush(NULL);
    }
    */

    if (i == *m)
    {
      printf("Error: the number of data rows in file %s is greater than the declared dimension %d x %d .\n", filename, *m, *n);
      free(buf);
      free(*matrix);
      return 1;
    }

    // remove multiple white space characters from line
    char * w = buf;
    while (*w != '\0')
    {
      while ((*w == ' ') && (*(w+1) == ' ')) // erase second blank
      {
        char * u = w+1;
        while (*u != '\0') // shift everything left one char
        {
          *u = *(u+1);
          u++;
        }
      }
      w++;
    }

    // remove whitespace at beginning of line
    if (*buf == ' ')
    {
      char * u = buf;
      while (*u != '\0') // shift everything left one char
      {
        *u = *(u+1);
        u++;
      }
    }

    //printf("%s\n",buf);

    char * token = strtok(buf," ");

    for(int j=0; j<*n; j++)
    {
      if (token == NULL)
      {
        printf("Token is NULL. Error parsing line %d.\n",i+1);
        return  1 ;
      }

      

      if (sscanf(token,sscanfFormat,&data) < 1)
      {
        printf("Cannot parse data from current token. Error parsing line %d.\n",i);
        return  1 ;
      }

      //printf("%G\n",data);

      (*matrix)[ELT(*m,i,j)] = data;

      token = strtok(NULL," ");

    }
    i++;
  }

  fclose(file);

  free(buf);

  if (i < *m) // not enough data has been read
  {
    printf("Error: the number of data rows in file %s is smaller than the declared dimension %d x %d .\n", filename, *m, *n);
    free(*matrix);
    return 1;
  }

  return 0;
}

template <class real>
int WriteMatrixToDiskTextFile(const char * filename, int m, int n, const real * matrix)
{
  // open file
  FILE * fout;
  fout = fopen(filename, "w");

  if( !fout )
  {
    printf("Couldn't open output file %s.\n", filename);
    return 1;
  }

  fprintf(fout, "%d\n%d\n", m, n);

  // matrix is m x n
  int i,j;
  for (i=0; i<m; i++)
  {
    for (j=0; j<n; j++)
      fprintf(fout,"%.15G ",matrix[ELT(m,i,j)]);
    fprintf(fout,"\n");
  }

  fclose(fout);

  return 0;
}

// n will contain number of nodes
// r will contain number of frequencies
// modes will contain the mode matrix
template <class real>
int ReadModesFromDisk(const char * filename, int * N, int * R, real ** frequencies, real ** modes)
{
  FILE * file;
  file = fopen(filename, "r");

  if (!file)
  {
    printf ("ReadModesFromDisk: failed to open input file %s.\n", filename);
    return 1;
  }

  if (fscanf(file,"%d\n",N) < 1)
  {
    printf ("ReadModesFromDisk: failed to read the number of nodes.\n");
    return 1;
  }

  if (fscanf(file,"%d\n",R) < 1)
  {
    printf ("ReadModesFromDisk: failed to read the number of modes.\n");
    return 1;
  }

  int n = *N;
  int r = *R;

  *modes = (real *) malloc (sizeof(real)*3*n*r);
  *frequencies = (real *) malloc (sizeof(real)*r);

  // read in frequencies
  int i,j,k;
  char s[1024];

  for (i=0; i<r; i++)
  {
    char formatString[6];
    if (sizeof(real) == sizeof(float))
      strcpy(formatString,"%f\n");
    else
      strcpy(formatString,"%lf\n");

    if (fscanf(file,formatString,&((*frequencies)[i])) < 1)
    {
      printf ("ReadModesFromDisk: failed to read frequency %d.\n",i+1);
      return 1;
    }
  }

  char formatStringLong[20];
  if (sizeof(real) == sizeof(float))
    strcpy(formatStringLong,"%d %f %f %f\n");
  else
    strcpy(formatStringLong,"%d %lf %lf %lf\n");

  // read in modes
  // each mode is one column
  // matrix is 3n x r
  for (i=0; i<r; i++) // over all modes
  {
    if (!fgets(s,1024,file)) // node header
    {
      printf ("ReadModesFromDisk: failed to read mode header for mode %d.\n",i+1);
      return 1;
    }

    for (j=0; j<n; j++) // over all nodes
    {
      if (fscanf(file, formatStringLong, &k,
	      &((*modes)[ELT(3*n,3*j,i)]),
	      &((*modes)[ELT(3*n,3*j+1,i)]),
	      &((*modes)[ELT(3*n,3*j+2,i)])) < 4)
      {
        printf ("ReadModesFromDisk: failed to read mode %d data at node %d.\n",i+1,j+1);
        return 1;
      }
    }
  }

  fclose(file);

  return 0;
}

int ReadModeInfoFromDisk(const char * filename, int * N, int * R)
{
  FILE * file;
  file = fopen(filename, "r");

  if (!file)
  {
    printf ("ReadModeInfoFromDisk: failed to open input file %s.\n", filename);
    return 1;
  }

  if (fscanf(file,"%d\n",N) < 1)
  {
    printf ("ReadModeInfoFromDisk: failed to read the number of nodes.\n");
    return 1;
  }

  if (fscanf(file,"%d\n",R) < 1)
  {
    printf ("ReadModeInfoFromDisk: failed to read the number of modes.\n");
    return 1;
  }

  fclose(file);
  return 0;
}

template <class real>
int WriteModesToDisk(const char * filename, int n, int r, real * frequencies, real * modes)
{
  FILE * file;
  file = fopen(filename, "w");

  if (!file)
    return 1;

  if (fprintf(file,"%d\n", n) < 1)
    return 1;

  if (fprintf(file,"%d\n", r) < 1)
    return 1;

  // write frequencies
  for (int i=0; i<r; i++) // over all modes
  {
    if (fprintf(file,"%.15f\n",frequencies[i]) < 1)
      return 1;
  }

  // write modes
  for (int i=0; i<r; i++) // over all modes
  {
    fprintf(file,"------ Mode %d : ----\n",i+1);

    for (int j=0; j<n; j++) // over all nodes
    {
      if (fprintf(file,"%d %.15f %.15f %.15f\n", j+1,
			      modes[ELT(3*n,3*j,i)],
			      modes[ELT(3*n,3*j+1,i)],
			      modes[ELT(3*n,3*j+2,i)]) < 4)
        return 1;
    }
  }

  fclose(file);

  return 0;
}

template void PrintMatrixInMathematicaFormat<double>(int n, int r, double * U);
template void PrintMatrixInMathematicaFormat<float>(int n, int r, float * U);

template int ReadModesFromDisk<double>(const char * filename, int * n, int * r, double ** frequencies, double ** modes);
template int ReadModesFromDisk<float>(const char * filename, int * n, int * r, float ** frequencies, float ** modes);

template int WriteModesToDisk<double>(const char * filename, int n, int r, double * frequencies, double * modes);
template int WriteModesToDisk<float>(const char * filename, int n, int r, float * frequencies, float * modes);

template int WriteMatrixToStream<double>(FILE * file, int m, int n, const double * matrix);
template int WriteMatrixToStream<float>(FILE * file, int m, int n, const float * matrix);

template int WriteMatrixToDisk<double>(const char * filename, int m, int n, const double * matrix);
template int WriteMatrixToDisk<float>(const char * filename, int m, int n, const float * matrix);

template int WriteMatrixToDisk_<double>(const char * filename, int m, int n, const double * matrix);
template int WriteMatrixToDisk_<float>(const char * filename, int m, int n, const float * matrix);

template int AppendMatrixToDisk_<double>(const char * filename, int m, int n, const double * matrix);
template int AppendMatrixToDisk_<float>(const char * filename, int m, int n, const float * matrix);

template int ReadMatrixFromDiskListOfFiles<double>(const char * fileList, int * m, int * n, double ** matrix);
template int ReadMatrixFromDiskListOfFiles<float>(const char * fileList, int * m, int * n, float ** matrix);

template int ReadMatrixFromStream<double>(FILE * file, int m, int n, double * matrix);
template int ReadMatrixFromStream<float>(FILE * file, int m, int n, float * matrix);

template int ReadMatrixFromDisk<double>(const char * filename, int * m, int * n, double ** matrix);
template int ReadMatrixFromDisk<float>(const char * filename, int * m, int * n, float ** matrix);

template int ReadMatrixFromDisk_<double>(const char * filename, int * m, int * n, double ** matrix);
template int ReadMatrixFromDisk_<float>(const char * filename, int * m, int * n, float ** matrix);

template int ReadMatrixFromDiskTextFile<double>(const char * filename, int * m, int * n, double ** matrix);
template int ReadMatrixFromDiskTextFile<float>(const char * filename, int * m, int * n, float ** matrix);

template int WriteMatrixToDiskTextFile<double>(const char * filename, int m, int n, const double * matrix);
template int WriteMatrixToDiskTextFile<float>(const char * filename, int m, int n, const float * matrix);

template int ReadBinary(FILE * fin, bool * data);
template int ReadBinary(FILE * fin, int * data);
template int ReadBinary(FILE * fin, float * data);
template int ReadBinary(FILE * fin, double * data);

template void ReadBinary_(FILE * fin, bool * data);
template void ReadBinary_(FILE * fin, int * data);
template void ReadBinary_(FILE * fin, float * data);
template void ReadBinary_(FILE * fin, double * data);

template int ReadBinaryBuffer(FILE * fin, int size, bool * data);
template int ReadBinaryBuffer(FILE * fin, int size, int * data);
template int ReadBinaryBuffer(FILE * fin, int size, float * data);
template int ReadBinaryBuffer(FILE * fin, int size, double * data);

template void ReadBinaryBuffer_(FILE * fin, int size, bool * data);
template void ReadBinaryBuffer_(FILE * fin, int size, int * data);
template void ReadBinaryBuffer_(FILE * fin, int size, float * data);
template void ReadBinaryBuffer_(FILE * fin, int size, double * data);

