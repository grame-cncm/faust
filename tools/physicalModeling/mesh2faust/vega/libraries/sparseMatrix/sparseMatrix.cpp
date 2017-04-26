/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "sparseMatrix" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC   *
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cassert>
#include "sparseMatrix.h"
using namespace std;

SparseMatrixOutline::SparseMatrixOutline(int numRows_): numRows(numRows_)
{
  Allocate();
}

SparseMatrixOutline::~SparseMatrixOutline()
{
  // deallocate column entries
  for(int i=0; i<numRows; i++)
    columnEntries[i].clear();
  columnEntries.clear();
}

SparseMatrixOutline::SparseMatrixOutline(int numRows_, double diagonal): numRows(numRows_)
{
  Allocate();

  pair<int,double> entry;

  for(int i=0; i<numRows; i++)
  {
    entry.first = i;
    entry.second = diagonal;
    columnEntries[i].insert(entry);
  }
}

SparseMatrixOutline::SparseMatrixOutline(int numRows_, double * diagonal): numRows(numRows_)
{
  Allocate();
  pair<int,double> entry;
  for(int i=0; i<numRows; i++)
  {
    entry.first = i;
    entry.second = diagonal[i];
    columnEntries[i].insert(entry);
  }
}

SparseMatrixOutline::SparseMatrixOutline(const char * filename, int expand)
{
  if (expand <= 0)
  {
    printf("Error: invalid expand factor %d in SparseMatrixOutline constructor.\n", expand);
    throw 1;
  }

  FILE * inputMatrix = fopen(filename,"r");
  if (!inputMatrix)
  {
    printf("Error: couldn't open input sparse matrix file %s.\n", filename);
    throw 2;
  }

  // read input size
  int m1, n1;
  if (fscanf(inputMatrix, "%d\n%d\n", &m1, &n1) < 2)
  {
    printf("Error: could not read sparse matrix dimensions in file %s.\n", filename);
    throw 3;
  }

  numRows = expand * m1;

  printf("Loading matrix from %s... Size is %d x %d .\n", filename, numRows, expand * n1);fflush(NULL);

  Allocate();

  char s[4096];
  while (fgets(s,4096,inputMatrix) != NULL)
  {
    int i1,j1;
    double x;
    sscanf(s, "%d %d %lf\n", &i1, &j1, &x);
    for(int e=0; e<expand; e++)
      AddEntry(expand * i1 + e, expand * j1 + e, x);
  }

  fclose(inputMatrix);
}

void SparseMatrixOutline::Allocate()
{
  // allocate empty datastructure for row entries
  columnEntries.clear();
  columnEntries.resize(numRows);
}

void SparseMatrixOutline::IncreaseNumRows(int numAddedRows)
{
  numRows += numAddedRows;
  columnEntries.resize(numRows);
}

void SparseMatrixOutline::AddEntry(int i, int j, double value)
{
  assert((size_t)i <= columnEntries.size());
  map<int,double>::iterator pos = columnEntries[i].find(j);
  if (pos != columnEntries[i].end())
    pos->second += value;
  else
  {
    pair<int,double> entry(j,value);
    columnEntries[i].insert(entry);
  }
}

// remove the entry in row i, column j
void SparseMatrixOutline::RemoveEntry(int i, int j)
{
  assert((size_t)i <= columnEntries.size());
  columnEntries[i].erase(j);
}

// add a block matrix, starting at row i, and column j 
void SparseMatrixOutline::AddBlockMatrix(int iStart, int jStart, const SparseMatrix * block, double scalarFactor)
{
  int nBlock = block->GetNumRows();
  for(int i=0; i<nBlock; i++)
  {
    int rowLength = block->GetRowLength(i);
    for(int j=0; j<rowLength; j++)
      AddEntry(iStart + i, jStart + block->GetColumnIndex(i,j), scalarFactor * block->GetEntry(i,j));
  }
}

void SparseMatrixOutline::MultiplyRow(int row, double scalar)
{
  for(map<int,double>::iterator iter = columnEntries[row].begin(); iter != columnEntries[row].end(); iter++)
    iter->second *= scalar;
}

void SparseMatrixOutline::AddBlock3x3Entry(int i, int j, const double * matrix3x3)
{
  for(int k=0; k<3; k++)
    for(int l=0; l<3; l++)
      AddEntry(3*i+k,3*j+l,matrix3x3[3*k+l]);
}

void SparseMatrixOutline::AddBlock3x3Entry(int i, int j, double value)
{
  for(int k=0; k<3; k++)
    for(int l=0; l<3; l++)
      AddEntry(3*i+k,3*j+l,value);
}

double SparseMatrixOutline::GetEntry(int i, int j) const
{
  map<int,double>::const_iterator pos = columnEntries[i].find(j);
  if (pos != columnEntries[i].end())
    return (pos->second);
  else
    return 0;
}

int SparseMatrixOutline::GetNumColumns() const
{
  int numColumns = -1;
  for(int i=0; i<numRows; i++)
  {
    map<int,double>::const_iterator j1;
    // traverse all row entries
    for(j1=columnEntries[i].begin(); j1 != columnEntries[i].end(); j1++)
      if (j1->first > numColumns)
        numColumns = j1->first;
  }
  return numColumns + 1;
}

int SparseMatrixOutline::Save(const char * filename, int oneIndexed) const
{
  FILE * fout = fopen(filename, "w");
  if (!fout)
    return 1;

  fprintf(fout, "%d\n%d\n", numRows, GetNumColumns());
  for(int i=0; i<numRows; i++)
  {
    map<int,double>::const_iterator j1;
    // traverse all row entries
    for(j1=columnEntries[i].begin(); j1 != columnEntries[i].end(); ++j1)
      fprintf(fout,"%d %d %.15f\n",i,j1->first + oneIndexed, j1->second + oneIndexed);
  }
  fclose(fout);

  return 0;
}

void SparseMatrixOutline::Print() const
{
  for (int i=0; i<numRows; i++)
  {
    for (int j=0; j<numRows; j++)
      printf("%f ",GetEntry(i,j));
    printf("\n");
  }
}

int SparseMatrixOutline::GetNumEntries() const
{
  int num = 0;
  for(int i=0; i<numRows; i++)
    num += (int)(columnEntries[i].size());
  return num;
}

SparseMatrix::SparseMatrix(const char * filename)
{
  SparseMatrixOutline sparseMatrixOutline(filename);
  InitFromOutline(&sparseMatrixOutline);
}

SparseMatrix::SparseMatrix(SparseMatrixOutline * sparseMatrixOutline)
{
  InitFromOutline(sparseMatrixOutline);
}

// construct matrix from the outline
void SparseMatrix::InitFromOutline(SparseMatrixOutline * sparseMatrixOutline)
{
  numRows = sparseMatrixOutline->GetNumRows();
  Allocate();

  for(int i=0; i<numRows; i++)
  {
    rowLength[i] = (int)(sparseMatrixOutline->columnEntries[i].size());
    columnIndices[i] = (int*) malloc (sizeof(int) * rowLength[i]);
    columnEntries[i] = (double*) malloc (sizeof(double) * rowLength[i]);

    map<int,double>::iterator pos;
    int j = 0;
    int prev = -1;
    for(pos = sparseMatrixOutline->columnEntries[i].begin(); pos != sparseMatrixOutline->columnEntries[i].end(); pos++)
    {
      columnIndices[i][j] = pos->first;
      if (columnIndices[i][j] <= prev)
        printf("Warning: entries not sorted in a row in a sparse matrix.\n");
      prev = columnIndices[i][j];
      columnEntries[i][j] = pos->second;
      j++;
    }
  }
}

// construct matrix by specifying all entries: number of rows, length of each row, indices of columns of non-zero entries in each row, values of non-zero entries in each row
SparseMatrix::SparseMatrix(int numRows_, int * rowLength_, int ** columnIndices_, double ** columnEntries_, int shallowCopy) : numRows(numRows_)
{
  if (shallowCopy)
  {
    rowLength = rowLength_;
    columnIndices = columnIndices_;
    columnEntries = columnEntries_;
    numSubMatrixIDs = 0;
    subMatrixIndices = NULL;
    subMatrixIndexLengths = NULL;
    subMatrixStartRow = NULL;
    subMatrixNumRows = NULL;
    superMatrixIndices = NULL;
    superRows = NULL;
    diagonalIndices = NULL;
    transposedIndices = NULL;
    return;
  }

  Allocate();

  for (int i = 0; i<numRows; i++)
  {
    rowLength[i] = rowLength_[i];
    columnIndices[i] = (int*) malloc(sizeof(int) * rowLength[i]);
    columnEntries[i] = (double*) malloc(sizeof(double) * rowLength[i]);
    for (int j = 0; j < rowLength[i]; j++)
    {
      columnIndices[i][j] = columnIndices_[i][j];
      columnEntries[i][j] = columnEntries_[i][j];
    }
  }
}

// allocator
void SparseMatrix::Allocate()
{
  // compressed row storage
  rowLength = (int*) malloc(sizeof(int) * numRows);
  columnIndices = (int**) malloc(sizeof(int*) * numRows);
  columnEntries = (double**) malloc(sizeof(double*) * numRows);
  numSubMatrixIDs = 0;
  subMatrixIndices = NULL;
  subMatrixIndexLengths = NULL;
  subMatrixStartRow = NULL;
  subMatrixNumRows = NULL;
  superMatrixIndices = NULL;
  superRows = NULL;
  diagonalIndices = NULL;
  transposedIndices = NULL;
}

// destructor
SparseMatrix::~SparseMatrix()
{
  for(int i=0; i<numRows; i++)
  {
    free(columnIndices[i]);
    free(columnEntries[i]);
  }

  if (subMatrixIndices != NULL)
  {
    for(int i=numSubMatrixIDs-1; i>=0; i--)
      FreeSubMatrixIndices(i);
  }

  if (superRows != NULL)
  {
    for(int i=0; i<numRows; i++)
      free(superMatrixIndices[i]);
    free(superMatrixIndices);
    free(superRows);
  }

  free(rowLength);
  free(columnIndices);
  free(columnEntries);
  free(diagonalIndices);
  FreeTranspositionIndices();
}

// copy constructor
SparseMatrix::SparseMatrix(const SparseMatrix & source)
{
  //printf("Copy constructor\n");fflush(NULL);
  numRows = source.GetNumRows();

  // compressed row storage
  rowLength = (int*) malloc(sizeof(int) * numRows);
  columnIndices = (int**) malloc(sizeof(int*) * numRows);
  columnEntries = (double**) malloc(sizeof(double*) * numRows);

  for(int i=0; i<numRows; i++)
  {
    rowLength[i] = source.rowLength[i];
    columnIndices[i] = (int*) malloc (sizeof(int) * rowLength[i]);
    columnEntries[i] = (double*) malloc (sizeof(double) * rowLength[i]);

    for(int j=0; j < rowLength[i]; j++)
    {
      columnIndices[i][j] = source.columnIndices[i][j];
      columnEntries[i][j] = source.columnEntries[i][j];
    }
  }

  subMatrixIndices = NULL;
  subMatrixIndexLengths = NULL;
  subMatrixStartRow = NULL;
  subMatrixNumRows = NULL;
  numSubMatrixIDs = source.numSubMatrixIDs;
  if (source.subMatrixIndices != NULL)
  {
    subMatrixIndices = (int***) malloc (sizeof(int**) * numSubMatrixIDs);
    subMatrixIndexLengths = (int**) malloc (sizeof(int*) * numSubMatrixIDs);
    subMatrixStartRow = (int*) malloc(sizeof(int) * numSubMatrixIDs);
    subMatrixNumRows = (int*) malloc(sizeof(int) * numSubMatrixIDs);
    memcpy(subMatrixStartRow, source.subMatrixStartRow, sizeof(int) * numSubMatrixIDs);
    memcpy(subMatrixNumRows, source.subMatrixNumRows, sizeof(int) * numSubMatrixIDs);

    for(int matrixID=0; matrixID < numSubMatrixIDs; matrixID++)
    {
      if (source.subMatrixIndices[matrixID] == NULL)
      {
        subMatrixIndices[matrixID] = NULL;
        subMatrixIndexLengths[matrixID] = NULL;
        continue;
      }

      subMatrixIndices[matrixID] = (int**) malloc(sizeof(int*) * numRows);
      subMatrixIndexLengths[matrixID] = (int*) malloc(sizeof(int) * numRows);

      for(int i=0; i<subMatrixNumRows[matrixID]; i++)
      {
        subMatrixIndexLengths[matrixID][i] = source.subMatrixIndexLengths[matrixID][i];
        subMatrixIndices[matrixID][i] = (int*) malloc(sizeof(int) * subMatrixIndexLengths[matrixID][i]);
        for(int j=0; j < subMatrixIndexLengths[matrixID][i]; j++)
          subMatrixIndices[matrixID][i][j] = source.subMatrixIndices[matrixID][i][j];
      }
    }
  }

  superRows = NULL;
  superMatrixIndices = NULL;
  if (source.superRows != NULL)
  {
    superRows = (int*) malloc(sizeof(int) * numRows);
    superMatrixIndices = (int**) malloc(sizeof(int*) * numRows);
    for(int i=0; i<numRows; i++)
    {
      superRows[i] = source.superRows[i];
      superMatrixIndices[i] = (int*) malloc(sizeof(int) * rowLength[i]);
      for(int j=0; j < rowLength[i]; j++)
      {
        superMatrixIndices[i][j] = source.superMatrixIndices[i][j];
      }
    }
  }

  diagonalIndices = NULL;
  if (source.diagonalIndices != NULL)
  {
    diagonalIndices = (int*) malloc (sizeof(int) * numRows);
    memcpy(diagonalIndices, source.diagonalIndices, sizeof(int) * numRows);
  }

  transposedIndices = NULL;
  if (source.transposedIndices != NULL)
  {
    transposedIndices = (int**) malloc (sizeof(int*) * numRows);
    for(int i=0; i<numRows; i++)
    {
      transposedIndices[i] = (int*) malloc (sizeof(int) * rowLength[i]);
      for(int j=0; j<rowLength[i]; j++)
        transposedIndices[i][j] = source.transposedIndices[i][j];
    }
  }
}

void SparseMatrix::MultiplyVector(int startRow, int endRow, const double * vector, double * result) const // result = A(startRow:endRow-1,:) * vector
{
  for(int i=startRow; i<endRow; i++)
  {
    result[i-startRow] = 0;
    for(int j=0; j < rowLength[i]; j++)
      result[i-startRow] += vector[columnIndices[i][j]] * columnEntries[i][j];
  }
}

void SparseMatrix::MultiplyVector(const double * vector, double * result) const
{
  for(int i=0; i<numRows; i++)
  {
    result[i] = 0;
    for(int j=0; j < rowLength[i]; j++)
      result[i] += vector[columnIndices[i][j]] * columnEntries[i][j];
  }
}

void SparseMatrix::MultiplyVectorAdd(const double * vector, double * result) const
{
  for(int i=0; i<numRows; i++)
    for(int j=0; j < rowLength[i]; j++)
      result[i] += vector[columnIndices[i][j]] * columnEntries[i][j];
}

void SparseMatrix::TransposeMultiplyVector(const double * vector, int resultLength, double * result) const
{
  for(int i=0; i<resultLength; i++)
    result[i] = 0;

  for(int i=0; i<numRows; i++)
    for(int j=0; j < rowLength[i]; j++)
      result[columnIndices[i][j]] += vector[i] * columnEntries[i][j];
}

void SparseMatrix::TransposeMultiplyVectorAdd(const double * vector, double * result) const
{
  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j < rowLength[i]; j++)
    {
      result[columnIndices[i][j]] += vector[i] * columnEntries[i][j];
    }
  }
}

void SparseMatrix::MultiplyMatrix(int numDenseRows, int numDenseColumns, const double * denseMatrix, double * result) const
{
  for(int column=0; column<numDenseColumns; column++)
    MultiplyVector(&denseMatrix[numDenseRows * column], &result[numRows * column]);
}

void SparseMatrix::MultiplyMatrixAdd(int numDenseRows, int numDenseColumns, const double * denseMatrix, double * result) const
{
  for(int column=0; column<numDenseColumns; column++)
    MultiplyVectorAdd(&denseMatrix[numDenseRows * column], &result[numRows * column]);
}

// result = A * trans(denseMatrix)
// trans(denseMatrix) is a dense matrix with 'numDenseColumns' columns, result is a numRows x numDenseColumns dense matrix
void SparseMatrix::MultiplyMatrixTranspose(int numDenseColumns, const double * denseMatrix, double * result) const
{
  memset(result, 0, sizeof(double) * numRows * numDenseColumns);
  for(int column=0; column<numDenseColumns; column++)
    for(int i=0; i<numRows; i++)
      for(int j=0; j < rowLength[i]; j++)
        result[numRows * column + i] += denseMatrix[numDenseColumns * columnIndices[i][j] + column] * columnEntries[i][j];
}

double SparseMatrix::QuadraticForm(const double * vector) const
{
  double result = 0;
  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j < rowLength[i]; j++)
    {
      int index = columnIndices[i][j];
      if (index < i)
        continue;
      if (index == i)
        result += columnEntries[i][j] * vector[i] * vector[index];
      else
        result += 2.0 * columnEntries[i][j] * vector[i] * vector[index];
    }
  }

  return result;
}

void SparseMatrix::NormalizeVector(double * vector) const
{
  double norm = sqrt(QuadraticForm(vector));
  for(int i=0; i<numRows; i++)
    vector[i] /= norm;
}

SparseMatrix SparseMatrix::operator+(const SparseMatrix & mat2) const
{
  SparseMatrix result(*this);
  for(int i=0; i<numRows; i++)
    for(int j=0; j < rowLength[i]; j++)
      result.columnEntries[i][j] += mat2.columnEntries[i][j];
  return result;
}

SparseMatrix SparseMatrix::operator-(const SparseMatrix & mat2) const
{
  SparseMatrix result(*this);
  for(int i=0; i<numRows; i++)
    for(int j=0; j < rowLength[i]; j++)
      result.columnEntries[i][j] -= mat2.columnEntries[i][j];
  return result;
}

SparseMatrix operator* (const double alpha, const SparseMatrix & mat2)
{
  SparseMatrix result(mat2);
  for(int i=0; i<result.numRows; i++)
    for(int j=0; j < result.rowLength[i]; j++)
      result.columnEntries[i][j] *= alpha;
  return result;
}

SparseMatrix & SparseMatrix::operator*=(const double alpha)
{
  for(int i=0; i<numRows; i++)
    for(int j=0; j < rowLength[i]; j++)
      columnEntries[i][j] *= alpha;
  return *this;
}

SparseMatrix & SparseMatrix::operator+=(const SparseMatrix & mat2)
{
  for(int i=0; i<numRows; i++)
    for(int j=0; j < rowLength[i]; j++)
      columnEntries[i][j] += mat2.columnEntries[i][j];
  return *this;
}

SparseMatrix & SparseMatrix::operator-=(const SparseMatrix & mat2)
{
  for(int i=0; i<numRows; i++)
    for(int j=0; j < rowLength[i]; j++)
      columnEntries[i][j] -= mat2.columnEntries[i][j];
  return *this;
}

SparseMatrix & SparseMatrix::operator=(const SparseMatrix & source)
{
  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j < rowLength[i]; j++)
      columnEntries[i][j] = source.columnEntries[i][j];
  }

  return *this;
}

bool SparseMatrix::operator==(const SparseMatrix & mat2) const
{
  if(numRows != mat2.numRows)
    return false;
  for(int i = 0; i < numRows; i++)
  {
    if(rowLength[i] != mat2.rowLength[i])
      return false;
    for(int j = 0; j < rowLength[i]; j++)
    {
      if(columnIndices[i][j] != mat2.columnIndices[i][j])
        return false;
      if(columnEntries[i][j] != mat2.columnEntries[i][j])
        return false;
    }
  }
  return true;
}

bool SparseMatrix::SameStructure(const SparseMatrix & mat2) const
{
  if(numRows != mat2.numRows) 
    return false;
  for(int i = 0; i < numRows; i++)
  {
    if(rowLength[i] != mat2.rowLength[i])
      return false;
    for(int j = 0; j < rowLength[i]; j++)
    {
      if(columnIndices[i][j] != mat2.columnIndices[i][j])
        return false;
    }
  }
  return true;
}

void SparseMatrix::ScalarMultiply(const double alpha, SparseMatrix * dest)
{
  if (dest == NULL)
    dest = this;

  for(int i=0; i<numRows; i++)
    for(int j=0; j < rowLength[i]; j++)
      dest->columnEntries[i][j] = columnEntries[i][j] * alpha;
}

void SparseMatrix::ScalarMultiplyAdd(const double alpha, SparseMatrix * dest)
{
  if (dest == NULL)
    dest = this;

  for(int i=0; i<numRows; i++)
    for(int j=0; j < rowLength[i]; j++)
      dest->columnEntries[i][j] += columnEntries[i][j] * alpha;
}

void SparseMatrix::ResetToZero()
{
  for(int i=0; i<numRows; i++)
    memset(columnEntries[i], 0, sizeof(double) * rowLength[i]);
}

void SparseMatrix::ResetRowToZero(int row)
{
  memset(columnEntries[row], 0, sizeof(double) * rowLength[row]);
}

void SparseMatrix::Print(int sparsePrint) const
{
  if (sparsePrint)
  {
    for (int i=0; i<numRows; i++)
      for(int j=0; j< rowLength[i]; j++)
        printf("%d %d %G\n", i, columnIndices[i][j], columnEntries[i][j]);
  }
  else
  {
    int numColumns = GetNumColumns();
    for (int i=0; i<numRows; i++)
    {
      int index = 0;
      for(int j=0; j< rowLength[i]; j++)
      {
        while (index < columnIndices[i][j])
        {
          index++;
          printf("%f,",0.0);
        }
        printf("%f,",columnEntries[i][j]);
        index++;
      }

      while (index < numColumns)
      {
        index++;
        printf("%f,",0.0);
      }

      printf("\n");
    }
  }
}

// seeks the element in column jDense (in row "row")
// if not found, returns -1
int SparseMatrix::GetInverseIndex(int row, int jDense) const
{
  for(int j=0; j < rowLength[row]; j++)
    if (columnIndices[row][j] == jDense)
      return j;

  return -1;
}

void SparseMatrix::BuildDiagonalIndices()
{
  if (diagonalIndices != NULL)
    return;

  diagonalIndices = (int*) malloc (sizeof(int) * numRows);
  for(int i=0; i<numRows; i++)
    diagonalIndices[i] = GetInverseIndex(i,i);
}

void SparseMatrix::FreeDiagonalIndices()
{
  free(diagonalIndices);
}

void SparseMatrix::GetDiagonal(double * diagonal) const
{
  if (diagonalIndices != NULL)
  {
    for(int i=0; i<numRows; i++)
      diagonal[i] = columnEntries[i][diagonalIndices[i]];
  }
  else
  {
    for(int i=0; i<numRows; i++)
      for(int j=0; j<GetRowLength(i); j++)
      {
        if (GetColumnIndex(i, j) == i)
          diagonal[i] = columnEntries[i][j];
      }
  }
}

void SparseMatrix::AddDiagonalMatrix(double * diagonalMatrix)
{
  if (diagonalIndices != NULL)
  {
    for(int i=0; i<numRows; i++)
      columnEntries[i][diagonalIndices[i]] += diagonalMatrix[i];
  }
  else
  {
    for(int i=0; i<numRows; i++)
      for(int j=0; j<GetRowLength(i); j++)
      {
        if (GetColumnIndex(i, j) == i)
          columnEntries[i][j] += diagonalMatrix[i];
      }
  }
}

void SparseMatrix::AddDiagonalMatrix(double constDiagonalElement)
{
  if (diagonalIndices != NULL)
  {
    for(int i=0; i<numRows; i++)
      columnEntries[i][diagonalIndices[i]] += constDiagonalElement;
  }
  else
  {
    for(int i=0; i<numRows; i++)
      for(int j=0; j<GetRowLength(i); j++)
      {
        if (GetColumnIndex(i, j) == i)
          columnEntries[i][j] += constDiagonalElement;
      }
  }
}

int SparseMatrix::GetNumEntries() const
{
  int num = 0;
  for(int i=0; i<numRows; i++)
    num += rowLength[i];

  return num;
}

double SparseMatrix::SumEntries() const
{
  double sum=0;
  for(int i=0; i<numRows; i++)
    for(int j=0; j<rowLength[i]; j++)
      sum += columnEntries[i][j];

  return sum;
}

void SparseMatrix::SumRowEntries(double * rowSums) const
{
  for(int i=0; i<numRows; i++)
  {
    double sum=0;
    for(int j=0; j<rowLength[i]; j++)
      sum += columnEntries[i][j];
    rowSums[i] = sum;
  }
}

void SparseMatrix::MakeLinearDataArray(double * data) const
{
  int count=0;
  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j<rowLength[i]; j++)
    {
      data[count] = columnEntries[i][j];
      count++;
    }
  }
}

void SparseMatrix::MakeLinearRowIndexArray(double * indices) const
{
  int count=0;
  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j<rowLength[i]; j++)
    {
      indices[count] = i;
      count++;
    }
  }
}

void SparseMatrix::MakeLinearColumnIndexArray(double * indices) const
{
  int count=0;
  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j<rowLength[i]; j++)
    {
      indices[count] = columnIndices[i][j];
      count++;
    }
  }
}

void SparseMatrix::MakeLinearRowIndexArray(int * indices) const
{
  int count=0;
  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j<rowLength[i]; j++)
    {
      indices[count] = i;
      count++;
    }
  }
}

void SparseMatrix::MakeLinearColumnIndexArray(int * indices) const
{
  int count=0;
  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j<rowLength[i]; j++)
    {
      indices[count] = columnIndices[i][j];
      count++;
    }
  }
}

void SparseMatrix::FreeTranspositionIndices()
{
  if (transposedIndices == NULL)
    return;

  for(int i=0; i<numRows; i++)
    free(transposedIndices[i]);
  free(transposedIndices);

  transposedIndices = NULL;
}

void SparseMatrix::BuildTranspositionIndices()
{
  if (transposedIndices != NULL)
    return;

  transposedIndices = (int**) malloc (sizeof(int*) * numRows);
  int * buffer = (int*) calloc (GetNumColumns(), sizeof(int));

  for(int i=0; i<numRows; i++)
  {
    transposedIndices[i] = (int*) malloc (sizeof(int) * rowLength[i]);
    for(int j=0; j<rowLength[i]; j++)
    {
      transposedIndices[i][j] = buffer[columnIndices[i][j]];
      buffer[columnIndices[i][j]]++;
    }
  }

  free(buffer);
}

double SparseMatrix::SkewSymmetricCheck()
{
  double maxEntry = 0;

  BuildTranspositionIndices();

  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j<GetRowLength(i); j++)
    {
      double entry1 = GetEntry(i, j);
      int tindex = TransposedIndex(i, j);
      double entry2 = GetEntry(GetColumnIndex(i,j), tindex);

      // entry1 + entry2 should be zero
      if (fabs(entry1 + entry2) > maxEntry)
        maxEntry = fabs(entry1 + entry2);
    }
  }

  return maxEntry;
}

void SparseMatrix::SymmetrizeMatrix()
{
  BuildTranspositionIndices();

  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j<rowLength[i]; j++)
    {
      int jAbs = columnIndices[i][j];

      if (jAbs >= i)
        break;

      // copy elt (jAbs,i) into position (i,jAbs)
      columnEntries[i][j] = columnEntries[jAbs][TransposedIndex(i,j)];
    }
  }
}

double SparseMatrix::GetMaxAbsEntry() const
{
  double max = 0;
  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j<rowLength[i]; j++)
    {
      double el = fabs(GetEntry(i,j));
      if (el > max)
        max = el;
    }
  }

  return max;
}

double SparseMatrix::GetRowNorm2(int row) const
{
  double norm2 = 0;
  for(int j=0; j<rowLength[row]; j++)
  {
    double el = columnEntries[row][j];
    norm2 += el * el;
  }
  return norm2;
}

// solve M * x = b
// ASSUMES the sparse matrix is diagonal !!!
void SparseMatrix::DiagonalSolve(double * rhs) const
{
  for(int i=0; i<numRows; i++)
    rhs[i] /= columnEntries[i][0]; // the diagonal element
}

void SparseMatrix::BuildRenumberingVector(int nConstrained, int nSuper, int numFixedDOFs, int * fixedDOFs, int ** superDOFs, int oneIndexed)
{
  // superRows[i] is the row index in the super matrix corresponsing to row i of constrained matrix
  (*superDOFs) = (int*) malloc (sizeof(int) * nConstrained);
  int constrainedDOF = 0;
  int superDOF = 0;
  for(int i=0; i<numFixedDOFs; i++)
  {
    int nextSuperDOF = fixedDOFs[i];
    nextSuperDOF -= oneIndexed;
    if ( (nextSuperDOF >= nSuper) || (nextSuperDOF < 0) )
    {
      printf("Error: invalid fixed super DOF %d specified.\n", nextSuperDOF);
      exit(1);
    }

    while (superDOF < nextSuperDOF)
    {
      if (constrainedDOF >= nConstrained)
      {
        printf("Error: too many DOFs specified.\n");
        exit(1);
      }
      (*superDOFs)[constrainedDOF] = superDOF;
      constrainedDOF++;
      superDOF++;
    }

    superDOF++; // skip the deselected DOF
  }
  while (superDOF < nSuper)
  {
    if (constrainedDOF >= nConstrained)
    {
      printf("Error: too many DOFs specified.\n");
      exit(1);
    }
    (*superDOFs)[constrainedDOF] = superDOF;

    constrainedDOF++;
    superDOF++;
  }
}

void SparseMatrix::BuildSuperMatrixIndices(int numFixedRowColumns, int * fixedRowColumns, const SparseMatrix * superMatrix, int oneIndexed)
{
  BuildSuperMatrixIndices(numFixedRowColumns, fixedRowColumns, numFixedRowColumns, fixedRowColumns, superMatrix, oneIndexed);
}

void SparseMatrix::BuildSuperMatrixIndices(int numFixedRows, int * fixedRows, int numFixedColumns, int * fixedColumns, const SparseMatrix * superMatrix, int oneIndexed)
{
  int numSuperColumns = superMatrix->GetNumColumns();
  int numColumns = numSuperColumns - numFixedColumns;

  if ((numRows + numFixedRows != superMatrix->numRows) || (GetNumColumns() + numFixedColumns > numSuperColumns) )
  {
    printf("Error in BuildSuperMatrixIndices: number of constrained DOFs does not match the size of the two matrices.\n");
    printf("num rows: %d num fixed rows in super matrix: %d num rows in super matrix: %d\n", numRows, numFixedRows, superMatrix->numRows);
    printf("num columns: %d num fixed columns in super matrix: %d num columns in super matrix: %d\n", numColumns, numFixedColumns, numSuperColumns);
    exit(1);
  }

  // build row renumbering function:
  BuildRenumberingVector(numRows, superMatrix->numRows, numFixedRows, fixedRows, &superRows, oneIndexed);
  // build column renumbering function:
  int * superColumns_;
  BuildRenumberingVector(numColumns, numSuperColumns, numFixedColumns, fixedColumns, &superColumns_, oneIndexed);

  // superRows[i] is the row index in the super matrix corresponsing to row i of constrained matrix
  // superColumns_[i] is the dense column index in the super matrix corresponsing to the dense column i of constrained matrix

  // build column indices
  superMatrixIndices = (int**) malloc (sizeof(int*) * numRows);
  for(int i=0; i < numRows; i++)
  {
    superMatrixIndices[i] = (int*) malloc (sizeof(int) *  rowLength[i]);
    for(int j=0; j < rowLength[i]; j++)
    {
      int iConstrained = i;
      int jConstrainedDense = columnIndices[iConstrained][j];
      int iSuper = superRows[iConstrained];
      int jSuperDense = superColumns_[jConstrainedDense];
      int jSuper = superMatrix->GetInverseIndex(iSuper, jSuperDense);
      if (jSuper < 0)
      {
        printf("Error in BuildSuperMatrixIndices: failed to compute inverse index.\n");
        printf("i=%d j=%d iConstrained=%d jConstrainedDense=%d iSuper=%d jSuperDense=%d jSuper=%d\n", i, j, iConstrained, jConstrainedDense, iSuper, jSuperDense, jSuper);
        fflush(NULL);
        exit(1);
      }
      superMatrixIndices[i][j] = jSuper;
    }
  }

  free(superColumns_);
}

void SparseMatrix::AssignSuperMatrix(const SparseMatrix & superMatrix)
{
  for(int i=0; i<numRows; i++)
  {
    double * row = superMatrix.columnEntries[superRows[i]];
    int * indices = superMatrixIndices[i];
    for(int j=0; j < rowLength[i]; j++)
      columnEntries[i][j] = row[indices[j]];
  }
}

void SparseMatrix::BuildSubMatrixIndices(const SparseMatrix & submatrix, int subMatrixID, int startRow, int startColumn)
{
  if (subMatrixID >= numSubMatrixIDs)
  {
    subMatrixIndices = (int***) realloc (subMatrixIndices, sizeof(int**) * (subMatrixID + 1));
    subMatrixIndexLengths = (int**) realloc (subMatrixIndexLengths, sizeof(int*) * (subMatrixID + 1));
    subMatrixStartRow = (int*) realloc(subMatrixStartRow, sizeof(int) * (subMatrixID + 1));
    subMatrixNumRows = (int*) realloc(subMatrixNumRows, sizeof(int) * (subMatrixID + 1));
    for(int i=numSubMatrixIDs; i <= subMatrixID; i++)
    {
      subMatrixIndices[i] = NULL;
      subMatrixIndexLengths[i] = NULL;
      subMatrixStartRow[i] = 0;
      subMatrixNumRows[i] = 0;
    }
    numSubMatrixIDs = subMatrixID + 1;
  }
  else if ((subMatrixIndices[subMatrixID] != NULL) || (subMatrixIndexLengths[subMatrixID] != NULL))
  {
    free(subMatrixIndices[subMatrixID]);
    free(subMatrixIndexLengths[subMatrixID]);
    subMatrixIndices[subMatrixID] = NULL;
    subMatrixIndexLengths[subMatrixID] = NULL;
    subMatrixStartRow[subMatrixID] = 0;
    subMatrixNumRows[subMatrixID] = 0;
    //printf("Warning: old submatrix indices (matrixID %d) have not been de-allocated.\n", subMatrixID);
  }

  subMatrixStartRow[subMatrixID] = startRow;
  subMatrixNumRows[subMatrixID] = submatrix.numRows;
  subMatrixIndices[subMatrixID] = (int**) malloc (sizeof(int*) * subMatrixNumRows[subMatrixID]);
  subMatrixIndexLengths[subMatrixID] = (int*) malloc (sizeof(int) * subMatrixNumRows[subMatrixID]);

  int endRow = startRow + subMatrixNumRows[subMatrixID];
  if(endRow > numRows)
  {
    printf("Error (BuildSubMatrixIndices): given submatrix placed at startRow %d exceeds the length of this matrix: %d\n", startRow, numRows);
    exit(1);
  }

  for(int i=0; i<subMatrixNumRows[subMatrixID]; i++)
  {
    //begin at the startRow, find correspondence to subMatrix at each row
    subMatrixIndices[subMatrixID][i] = (int*) malloc (sizeof(int) * submatrix.rowLength[i]);
    subMatrixIndexLengths[subMatrixID][i] = submatrix.rowLength[i];
    int * indices = submatrix.columnIndices[i];

    // this assumes that the column indices are sorted (which they always are)
    int col = 0;
    int * colIndices = columnIndices[startRow + i];

    for(int j=0; j < submatrix.rowLength[i]; j++)
    {
      int targetColumn = startColumn + indices[j];
      while (colIndices[col] < targetColumn)
        col++;

      subMatrixIndices[subMatrixID][i][j] = (colIndices[col] == targetColumn) ? col : -1;

      // finds the position in row i of element with column index jDense
      // int inverseIndex(int i, int jDense);
      //subMatrixIndices[subMatrixID][i][j] = GetInverseIndex(startRow + i, startColumn + indices[j]);
      if (subMatrixIndices[subMatrixID][i][j] == -1)
      {
        printf("Error (BuildSubMatrixIndices): given matrix is not a submatrix of this matrix. The following index does not exist in this matrix: (%d,%d)\n", startRow + i, startColumn + indices[j]);
        exit(1);
      }
    }
  }
}

void SparseMatrix::FreeSubMatrixIndices(int subMatrixID)
{
  if (subMatrixID >= numSubMatrixIDs)
  {
    printf("Warning: attempted to free submatrix index that does not exist.\n");
    return;
  }

  if (subMatrixIndices[subMatrixID] != NULL)
  {
    for(int i=0; i<subMatrixNumRows[subMatrixID]; i++)
      free(subMatrixIndices[subMatrixID][i]);
    free(subMatrixIndices[subMatrixID]);
    free(subMatrixIndexLengths[subMatrixID]);
    subMatrixIndices[subMatrixID] = NULL;
    subMatrixIndexLengths[subMatrixID] = NULL;
    subMatrixStartRow[subMatrixID] = 0;
    subMatrixNumRows[subMatrixID] = 0;
  }

  // check if this was the largest index
  for(int i=numSubMatrixIDs-1; i>=0; i--)
  {
    if (subMatrixIndices[i] != NULL)
    {
      numSubMatrixIDs = i + 1;
      subMatrixIndices = (int***) realloc (subMatrixIndices, sizeof(int**) * numSubMatrixIDs);
      subMatrixIndexLengths = (int**) realloc (subMatrixIndexLengths, sizeof(int*) * numSubMatrixIDs);
      subMatrixStartRow = (int*) realloc (subMatrixStartRow, sizeof(int) * numSubMatrixIDs);
      subMatrixNumRows = (int*) realloc (subMatrixNumRows, sizeof(int) * numSubMatrixIDs);
      break;
    }

    numSubMatrixIDs = i;
  }

  if (numSubMatrixIDs == 0)
  {
    free(subMatrixIndices);
    free(subMatrixIndexLengths);
    free(subMatrixStartRow);
    free(subMatrixNumRows);
    subMatrixIndices = NULL;
    subMatrixIndexLengths = NULL;
    subMatrixStartRow = NULL;
    subMatrixNumRows = NULL;
  }
}

void SparseMatrix::AssignSubMatrix(const SparseMatrix & submatrix, int subMatrixID)
{
  int startRow = subMatrixStartRow[subMatrixID];
  for(int i=0; i<subMatrixNumRows[subMatrixID]; i++)
  {
    int * indices = subMatrixIndices[subMatrixID][i];
    for(int j=0; j < submatrix.rowLength[i]; j++)
      columnEntries[startRow + i][indices[j]] = submatrix.columnEntries[i][j];
  }
}

void SparseMatrix::AssignToSubMatrix(SparseMatrix & submatrix, int subMatrixID) const
{
  int startRow = subMatrixStartRow[subMatrixID];
  for(int i=0; i<subMatrixNumRows[subMatrixID]; i++)
  {
    int * indices = subMatrixIndices[subMatrixID][i];
    for(int j=0; j < submatrix.rowLength[i]; j++)
      submatrix.columnEntries[i][j] = columnEntries[startRow + i][indices[j]];
  }
}

SparseMatrix & SparseMatrix::AddSubMatrix(double factor, SparseMatrix & submatrix, int subMatrixID)
{
  int startRow = subMatrixStartRow[subMatrixID];
  for(int i=0; i<subMatrixNumRows[subMatrixID]; i++)
  {
    int * indices = subMatrixIndices[subMatrixID][i];
    for(int j=0; j < submatrix.rowLength[i]; j++)
      columnEntries[startRow + i][indices[j]] += factor * submatrix.columnEntries[i][j];
  }

  return *this;
}

int SparseMatrix::GetNumLowerTriangleEntries() const
{
  int num = 0;
  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j < rowLength[i]; j++)
    {
      if (columnIndices[i][j] <= i)
        num++;
    }
  }
  return num;
}

int SparseMatrix::GetNumUpperTriangleEntries() const
{
  int num = 0;
  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j < rowLength[i]; j++)
    {
      if (columnIndices[i][j] >= i)
        num++;
    }
  }
  return num;
}

int SparseMatrix::GenerateNAGFormat(double * a, int * irow, int * icol, int * istr) const
{
  int num = 0;
  for(int i=0; i<numRows; i++)
  {
    istr[i] = num; // starting address of row i
    for(int j=0; j < rowLength[i]; j++)
    {
      if (columnIndices[i][j] <= i) // over lower triangle
      {
        a[num] = columnEntries[i][j];
        irow[num] = i+1; // NAG is 1-indexed
        icol[num] = columnIndices[i][j]+1; // NAG is 1-indexed
        num++;
      }
    }
  }

  istr[numRows] = num;

  return num;
}

void SparseMatrix::GenerateCompressedRowMajorFormat(double * a, int * ia, int * ja, int upperTriangleOnly, int oneIndexed) const
{
  int count = 0;
  for(int row=0; row<numRows; row++)
  {
    if (ia != NULL)
      ia[row] = count + oneIndexed;

    int rowLength = GetRowLength(row);
    for(int j=0; j< rowLength; j++)
    {
      if ((!upperTriangleOnly) || (columnIndices[row][j] >= row))
      {
        if (a != NULL)
          a[count] = columnEntries[row][j];
        if (ja != NULL)
          ja[count] = columnIndices[row][j] + oneIndexed;
        count++;
      }
    }
  }

  if (ia != NULL)
    ia[numRows] = count + oneIndexed;
}

void SparseMatrix::GenerateCompressedRowMajorFormat_four_array(double * values, int * columns, int * pointerB, int * pointerE, int upperTriangleOnly, int oneIndexed) const
{
  int count = 0;
  for(int row=0; row<numRows; row++)
  {
    if (pointerB != NULL)
      pointerB[row] = count + oneIndexed;

    int rowLength = GetRowLength(row);
    for(int j=0; j< rowLength; j++)
    {
      if ((!upperTriangleOnly) || (columnIndices[row][j] >= row))
      {
        if (values != NULL)
          values[count] = columnEntries[row][j];
        if (columns != NULL)
          columns[count] = columnIndices[row][j] + oneIndexed;
        count++;
      }
    }

    if (pointerE != NULL)
      pointerE[row] = count + oneIndexed;
  }
}

int SparseMatrix::Save(const char * filename, int oneIndexed) const
{
  FILE * fout = fopen(filename,"w");
  if (!fout)
    return 1;

  fprintf(fout,"%d\n%d\n", numRows, GetNumColumns());
  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j < rowLength[i]; j++)
    {
      int index = columnIndices[i][j];
      double entry = columnEntries[i][j];
      fprintf(fout,"%d %d %.15G\n",i + oneIndexed, index + oneIndexed, entry);
    }
  }
  fclose(fout);

  return 0;
}

int SparseMatrix::SaveToMatlabFormat(const char * filename) const
{
  FILE * fout = fopen(filename,"w");
  if (!fout)
    return 1;

  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j < rowLength[i]; j++)
    {
      int index = columnIndices[i][j];
      double entry = columnEntries[i][j];
      fprintf(fout,"%d %d %.15G\n",i + 1, index + 1, entry);
    }
  }
  fclose(fout);

  return 0;
}

void SparseMatrix::RemoveRowColumn(int index)
{
  // remove row 'index'
  free(columnEntries[index]);
  free(columnIndices[index]);

  for(int i=index; i<numRows-1; i++)
  {
    columnEntries[i] = columnEntries[i+1];
    columnIndices[i] = columnIndices[i+1];
    rowLength[i] = rowLength[i+1];
  }

  // remove column 'index'
  for(int i=0; i<numRows-1; i++)
  {
    // traverse all rows
    for(int j=0; j<rowLength[i]; j++)
    {
      // seek for entry 'index'
      if (columnIndices[i][j] == index) // found
      {
        // shift all elements ahead one step back
        for(int k=j; k<rowLength[i]-1; k++)
        {
          columnIndices[i][k] = columnIndices[i][k+1];
          columnEntries[i][k] = columnEntries[i][k+1];
        }
        rowLength[i]--;
      }
    }

    // decrease indices for DOFs above index
    for(int j=0; j<rowLength[i]; j++)
    {
      if(columnIndices[i][j] > index)
      {
        // decrease index
        columnIndices[i][j]--;
      }
    }
  }

  numRows--;
}

void SparseMatrix::RemoveRowsColumnsSlow(int numRemovedRowsColumns, const int * removedRowsColumns, int oneIndexed)
{
  for(int i=0; i<numRemovedRowsColumns; i++)
    RemoveRowColumn(removedRowsColumns[i]-i-oneIndexed);
}

void SparseMatrix::RemoveRowsColumns(int numRemovedRowsColumns, const int * removedRowsColumns, int oneIndexed)
{
  // the removed dofs must be pre-sorted
  // build a map from old dofs to new ones
  vector<int> oldToNew(numRows);
  int dof = 0;
  int dofCount = 0;
  for(int i=0; i<numRemovedRowsColumns; i++)
  {
    while (dof < removedRowsColumns[i] - oneIndexed)
    {
      oldToNew[dof] = dofCount;
      dofCount++;
      dof++;
    }
    oldToNew[dof] = -1;
    dof++;
  }
  while (dof < numRows)
  {
    oldToNew[dof] = dofCount;
    dofCount++;
    dof++;
  }

  // now, traverse all rows and renumber the entries
  int targetRow = 0;
  for(int sourceRow = 0; sourceRow < numRows; sourceRow++)
  {
    if (oldToNew[sourceRow] == -1)
    {
      free(columnIndices[sourceRow]);
      free(columnEntries[sourceRow]);
      continue;
    }

    int targetIndex = 0;
    for(int sourceIndex=0; sourceIndex<rowLength[sourceRow]; sourceIndex++)
    {
      int oldIndex = columnIndices[sourceRow][sourceIndex];
      int newIndex = oldToNew[oldIndex];
      if (newIndex == -1)
        continue;
      columnIndices[sourceRow][targetIndex] = newIndex;
      columnEntries[sourceRow][targetIndex] = columnEntries[sourceRow][sourceIndex];
      targetIndex++;
    }

    columnIndices[sourceRow] = (int*) realloc(columnIndices[sourceRow], sizeof(int) * targetIndex);
    columnEntries[sourceRow] = (double*) realloc(columnEntries[sourceRow], sizeof(double) * targetIndex);

    columnIndices[targetRow] = columnIndices[sourceRow];
    columnEntries[targetRow] = columnEntries[sourceRow];
    rowLength[targetRow] = targetIndex;
    targetRow++;
  }

  numRows -= numRemovedRowsColumns;
  columnEntries = (double**) realloc(columnEntries, sizeof(double*) * numRows);
  columnIndices = (int**) realloc(columnIndices, sizeof(int*) * numRows);
  rowLength = (int*) realloc(rowLength, sizeof(int) * numRows);
}

void SparseMatrix::RemoveColumn(int index)
{
  // remove column 'index'
  for(int i=0; i<numRows; i++)
  {
    // traverse all rows
    for(int j=0; j<rowLength[i]; j++)
    {
      // seek for entry 'index'
      if (columnIndices[i][j] == index) // found
      {
        // shift all elements ahead one step back
        for(int k=j; k<rowLength[i]-1; k++)
        {
          columnIndices[i][k] = columnIndices[i][k+1];
          columnEntries[i][k] = columnEntries[i][k+1];
        }
        rowLength[i]--;
      }
    }

    // decrease indices for DOFs above index
    for(int j=0; j<rowLength[i]; j++)
    {
      if(columnIndices[i][j] > index)
      {
        // decrease index
        columnIndices[i][j]--;
      }
    }
  }
}

void SparseMatrix::RemoveColumns(int numRemovedColumns, const int * removedColumns, int oneIndexed)
{
  // the removed dofs must be pre-sorted
  // build a map from old dofs to new ones
  int numColumns = GetNumColumns();

  // must increase numColumns to accommodate matrices with zero columns on the right
  for(int i=0; i<numRemovedColumns; i++)
  {
    int removedColumn0Indexed = removedColumns[i] - oneIndexed;
    int neededNumColumns = removedColumn0Indexed + 1;
    if (neededNumColumns > numColumns)
      numColumns = neededNumColumns;
  }

  vector<int> oldToNew(numColumns);
  int dof = 0;
  int dofCount = 0;
  for(int i=0; i<numRemovedColumns; i++)
  {
    while (dof < removedColumns[i] - oneIndexed)
    {
      oldToNew[dof] = dofCount;
      dofCount++;
      dof++;
    }
    oldToNew[dof] = -1;
    dof++;
  }
  while (dof < numColumns)
  {
    oldToNew[dof] = dofCount;
    dofCount++;
    dof++;
  }

  // now, traverse all rows and renumber the entries
  for(int row = 0; row < numRows; row++)
  {
    int targetIndex = 0;
    for(int sourceIndex=0; sourceIndex<rowLength[row]; sourceIndex++)
    {
      int oldIndex = columnIndices[row][sourceIndex];
      int newIndex = oldToNew[oldIndex];
      if (newIndex == -1)
        continue;
      columnIndices[row][targetIndex] = newIndex;
      columnEntries[row][targetIndex] = columnEntries[row][sourceIndex];
      targetIndex++;
    }

    columnIndices[row] = (int*) realloc(columnIndices[row], sizeof(int) * targetIndex);
    columnEntries[row] = (double*) realloc(columnEntries[row], sizeof(double) * targetIndex);
    rowLength[row] = targetIndex;
  }
}

void SparseMatrix::RemoveColumnsSlow(int numColumns, const int * columns, int oneIndexed)
{
  for(int i=0; i<numColumns; i++)
    RemoveColumn(columns[i]-i-oneIndexed);
}

void SparseMatrix::RemoveRow(int index)
{
  // remove row 'index'
  free(columnEntries[index]);
  free(columnIndices[index]);

  for(int i=index; i<numRows-1; i++)
  {
    columnEntries[i] = columnEntries[i+1];
    columnIndices[i] = columnIndices[i+1];
    rowLength[i] = rowLength[i+1];
  }

  numRows--;
}

void SparseMatrix::RemoveRowsSlow(int numRows, const int * rows, int oneIndexed)
{
  for(int i=0; i<numRows; i++)
    RemoveRow(rows[i]-i-oneIndexed);
}

void SparseMatrix::RemoveRows(int numRemovedRows, const int * removedRows, int oneIndexed)
{
  // the removed dofs must be pre-sorted
  // build a map from old dofs to new ones
  vector<int> oldToNew(numRows);
  int dof = 0;
  int dofCount = 0;
  for(int i=0; i<numRemovedRows; i++)
  {
    while (dof < removedRows[i] - oneIndexed)
    {
      oldToNew[dof] = dofCount;
      dofCount++;
      dof++;
    }
    oldToNew[dof] = -1;
    dof++;
  }
  while (dof < numRows)
  {
    oldToNew[dof] = dofCount;
    dofCount++;
    dof++;
  }

  // now, traverse all rows and renumber the entries
  int targetRow = 0;
  for(int sourceRow = 0; sourceRow < numRows; sourceRow++)
  {
    if (oldToNew[sourceRow] == -1)
    {
      free(columnIndices[sourceRow]);
      free(columnEntries[sourceRow]);
      continue;
    }

    columnIndices[targetRow] = columnIndices[sourceRow];
    columnEntries[targetRow] = columnEntries[sourceRow];
    rowLength[targetRow] = rowLength[sourceRow];
    targetRow++;
  }

  numRows -= numRemovedRows;
  columnEntries = (double**) realloc(columnEntries, sizeof(double*) * numRows);
  columnIndices = (int**) realloc(columnIndices, sizeof(double*) * numRows);
  rowLength = (int*) realloc(rowLength, sizeof(int) * numRows);
}

double SparseMatrix::GetInfinityNorm() const
{
  double norm = 0.0;
  for(int i=0; i<numRows; i++)
  {
    double absRowSum = 0;
    for(int j=0; j<rowLength[i]; j++)
      absRowSum += fabs(columnEntries[i][j]);
    if (absRowSum > norm)
      norm = absRowSum;
  }
  return norm;
}

double SparseMatrix::GetFrobeniusNorm() const
{
  double sum = 0.0;
  for(int i=0; i<numRows; i++)
  {
    double rowSum = 0.;
    for(int j=0; j<rowLength[i]; j++)
      rowSum += columnEntries[i][j] * columnEntries[i][j];
    sum += rowSum;
  }
  return sqrt(sum);
}

void SparseMatrix::DoOneGaussSeidelIteration(double * x, const double * b) const
{
  for(int i=0; i<numRows; i++)
  {
    double buffer = b[i];
    int diagIndex = -1;
    for(int j=0; j<rowLength[i]; j++)
    {
      int column = columnIndices[i][j];
      if (column != i)
        buffer -= columnEntries[i][j] * x[column];
      else
        diagIndex = j;
    }
    x[i] = buffer / columnEntries[i][diagIndex];
  }
}

void SparseMatrix::ComputeResidual(const double * x, const double * b, double * residual) const
{
  MultiplyVector(x,residual);
  for(int i=0; i<numRows; i++)
    residual[i] -= b[i];
}

double SparseMatrix::CheckLinearSystemSolution(const double * x, const double * b, int verbose, double * buffer) const
{
  double * bufferv = NULL;

  if (buffer == NULL)
  {
    bufferv = (double*) malloc (sizeof(double) * numRows);
    buffer = bufferv;
  }

  MultiplyVector(x,buffer);

  double inftyNorm = 0;
  double inftyNorm_b = 0;
  for(int i=0; i<numRows; i++)
  {
    if (fabs(buffer[i] - b[i]) > inftyNorm)
      inftyNorm = fabs(buffer[i] - b[i]);

    if (fabs(b[i]) > inftyNorm_b)
      inftyNorm_b = fabs(b[i]);
  }

  if (verbose)
  {
    printf("Infinity residual norm ||Ax-b|| is %G. ||b|| is %G.\n", inftyNorm, inftyNorm_b);
    printf("Relative infinity residual norm ||Ax-b||/||b|| is %G.\n", inftyNorm / inftyNorm_b);
  }

  free(bufferv);

  return inftyNorm / inftyNorm_b;
}

void SparseMatrix::MakeDenseMatrix(double * denseMatrix, int numColumns) const
{
  if (numColumns == -1)
    numColumns = GetNumColumns();
  memset(denseMatrix, 0, sizeof(double) * (numRows * numColumns));
  for(int i=0; i< numRows; i++)
    for(int j=0; j<rowLength[i]; j++)
    {
      if (columnIndices[i][j] < numColumns)
        denseMatrix[numRows * columnIndices[i][j] + i] = columnEntries[i][j];
    }
}

void SparseMatrix::MakeDenseMatrixTranspose(int numColumns, double * denseMatrix) const
{
  // note: we cannot use GetNumColumns() here because the rightmost columns of the sparse matrix can be zero and the GetNumColumns() will not be accurate
  memset(denseMatrix, 0, sizeof(double) * (numRows * numColumns));
  for(int i=0; i<numRows; i++)
  {
    int offset = i * numColumns;
    for(int j=0; j<rowLength[i]; j++)
      denseMatrix[offset + columnIndices[i][j]] = columnEntries[i][j];
  }
}

void SparseMatrix::MultiplyRow(int row, double scalar) // multiplies all elements in row 'row' with scalar 'scalar'
{
  for(int j=0; j<rowLength[row]; j++)
    columnEntries[row][j] *= scalar;
}

int SparseMatrix::GetNumColumns() const
{
  int numColumns = -1;
  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j<rowLength[i]; j++)
    {
      if (columnIndices[i][j] > numColumns)
        numColumns = columnIndices[i][j];
    }
  }
  return numColumns + 1;
}

void SparseMatrix::IncreaseNumRows(int numAddedRows)
{
  int newn = numRows + numAddedRows;

  rowLength = (int*) realloc (rowLength, sizeof(int) * newn);
  for(int i=0; i<numAddedRows; i++)
    rowLength[numRows + i] = 0;

  columnIndices = (int**) realloc (columnIndices, sizeof(int*) * newn);
  for(int i=0; i<numAddedRows; i++)
    columnIndices[numRows + i] = NULL;

  columnEntries = (double**) realloc (columnEntries, sizeof(double*) * newn);
  for(int i=0; i<numAddedRows; i++)
    columnEntries[numRows + i] = NULL;

  numRows = newn;
}

SparseMatrix SparseMatrix::ConjugateMatrix(SparseMatrix & U, int verbose, int numColumns)
{
  if (numColumns == -1)
    numColumns = U.GetNumColumns();

  SparseMatrixOutline outline(numColumns);

  for(int i=0; i<numRows; i++)
  {
    if (verbose)
    {
      if (i % 100 == 1)
        printf("Processing row %d / %d...\n", i, numRows);
    }
    for(int j=0; j<rowLength[i]; j++)
    {
      int I = i;
      int J = columnIndices[i][j];
      double scalar = columnEntries[i][j];

      // compute tensor product of rows I and J of U
      for(int k=0; k<U.rowLength[I]; k++)
        for(int l=0; l<U.rowLength[J]; l++)
        {
          int K = U.columnIndices[I][k];
          int L = U.columnIndices[J][l];

          // there is an entry at (I, K), and another entry at (J, L); compute their contribution to tensor product:
          outline.AddEntry(K, L, scalar * U.columnEntries[I][k] * U.columnEntries[J][l]);
        }
    }
  }

  if (verbose)
    printf("Creating sparse matrix from outline...\n");

  return SparseMatrix(&outline);
}

void SparseMatrix::BuildConjugationIndices(SparseMatrix & U, SparseMatrix & MTilde, precomputedIndicesType * precomputedIndices)
{
  typedef pair< pair<int,int>, pair<int, int> > fourTuple;
  typedef vector<fourTuple> listOfFourTuples;
  typedef map<int, listOfFourTuples> rowMap;
  vector<rowMap> rowMaps;
  for(int i=0; i<MTilde.numRows; i++)
    rowMaps.push_back(rowMap());

  for(int i=0; i<numRows; i++)
  {
    for(int j=0; j<rowLength[i]; j++)
    {
      int I = i;
      int J = columnIndices[i][j];

      // compute tensor product of rows I and J of U
      for(int k=0; k<U.rowLength[I]; k++)
        for(int l=0; l<U.rowLength[J]; l++)
        {
          int K = U.columnIndices[I][k];
          int L = U.columnIndices[J][l];
          //outline.AddEntry(K, L, scalar * U.columnEntries[I][k] * U.columnEntries[J][l]);

          fourTuple tuple(make_pair(make_pair(i,j), make_pair(k,l)));

          rowMap::iterator iter = rowMaps[K].find(L);
          if (iter == rowMaps[K].end())
          {
            listOfFourTuples singletonList;
            singletonList.push_back(tuple);
            rowMaps[K].insert(make_pair(L, singletonList));
          }
          else
          {
            (iter->second).push_back(tuple);
          }
        }
    }
  }

  // copy map to precomputedIndices
  (*precomputedIndices) = (int***) malloc (sizeof(int**) * MTilde.numRows);
  for(int i=0; i<MTilde.numRows; i++)
  {
    (*precomputedIndices)[i] = (int**) malloc (sizeof(int*) * rowMaps[i].size());
    int j = 0;
    for(rowMap::iterator iter = rowMaps[i].begin(); iter != rowMaps[i].end(); ++iter)
    {
      (*precomputedIndices)[i][j] = (int*) malloc (sizeof(int) * (4 * ((iter->second).size()) + 1));
      ((*precomputedIndices)[i][j])[0] = (int)((iter->second).size());
      for(int k=0; k<((*precomputedIndices)[i][j])[0]; k++)
      {
        ((*precomputedIndices)[i][j])[1+4*k+0] = ((iter->second)[k]).first.first;
        ((*precomputedIndices)[i][j])[1+4*k+1] = ((iter->second)[k]).first.second;
        ((*precomputedIndices)[i][j])[1+4*k+2] = ((iter->second)[k]).second.first;
        ((*precomputedIndices)[i][j])[1+4*k+3] = ((iter->second)[k]).second.second;
      }
      j++;
    }
  }
}

void SparseMatrix::ConjugateMatrix(precomputedIndicesType precomputedIndices, SparseMatrix & U, SparseMatrix & MTilde)
{
  MTilde.ResetToZero();
  for(int row=0; row<MTilde.numRows; row++)
  {
    int ** rowIndices = precomputedIndices[row];
    for(int j=0; j<MTilde.rowLength[row]; j++)
    {
      int * entryIndices = rowIndices[j];
      int numSummationTerms = entryIndices[0];
      for(int k=0; k<numSummationTerms; k++)
      {
        int * entryIndex = &entryIndices[4*k+1];
        int rowOfM = entryIndex[0];
        int columnIndexOfM = entryIndex[1];
        int columnOfM = columnIndices[rowOfM][columnIndexOfM];
        int columnIndexofU_for_MTilde_row = entryIndex[2];
        int columnIndexofU_for_MTilde_column = entryIndex[3];
        (MTilde.columnEntries)[row][j] += columnEntries[rowOfM][columnIndexOfM] * U.columnEntries[row][columnIndexofU_for_MTilde_row] * U.columnEntries[columnOfM][columnIndexofU_for_MTilde_column];
      }
    }
  }
}

void SparseMatrix::ConjugateMatrix(const double * U, int r, double * UTilde) const
{
  double * MU = (double*) malloc (sizeof(double) * numRows * r);
  MultiplyMatrix(numRows, r, U, MU);

  // compute U^T * MU
  for(int i=0; i<r; i++)
    for(int j=0; j<r; j++)
    {
      double entry = 0.0;
      for(int k=0; k<numRows; k++)
        entry += U[i * numRows + k] * MU[j * numRows + k];
      UTilde[j * r + i] = entry;
    }

  free(MU);
}

SparseMatrix * SparseMatrix::Transpose(int numColumns)
{
  if (numColumns < 0)
    numColumns = GetNumColumns();

  SparseMatrixOutline outline(numColumns);

  for(int i=0; i<numRows; i++)
    for(int j=0; j<rowLength[i]; j++)
      outline.AddEntry(columnIndices[i][j], i, columnEntries[i][j]);

  return new SparseMatrix(&outline);
}

void SparseMatrix::AssignTransposedMatrix(SparseMatrix & AT)
{
  AT.BuildTranspositionIndices();
  for(int i = 0; i < AT.numRows; i++)
    for(int j = 0; j < AT.rowLength[i]; j++)
    {
      int index = AT.TransposedIndex(i,j);
      int row = AT.columnIndices[i][j];
      columnEntries[row][index] = AT.columnEntries[i][j];
    }
}

void SparseMatrix::SetRows(const SparseMatrix * source, int startRow, int startColumn)
{
  for(int i=0; i<source->GetNumRows(); i++)
  {
    int row = startRow + i;
    if (row >= numRows)
      return;

    rowLength[row] = source->GetRowLength(i);
    columnIndices[row] = (int*) realloc (columnIndices[row], sizeof(int) * rowLength[row]);
    columnEntries[row] = (double*) realloc (columnEntries[row], sizeof(double) * rowLength[row]);
    for(int j=0; j<rowLength[row]; j++)
    {
      columnIndices[row][j] = startColumn + source->columnIndices[i][j];
      columnEntries[row][j] = source->columnEntries[i][j];
    }
  }
}

void SparseMatrix::AppendRowsColumns(const SparseMatrix * source)
{
  int * oldRowLengths = (int*) malloc (sizeof(int) * numRows);
  for(int i=0; i<numRows; i++)
    oldRowLengths[i] = rowLength[i];

  int oldNumRows = numRows;
  IncreaseNumRows(source->GetNumRows());
  SetRows(source, oldNumRows);

  // add transpose of rows:

  // first, establish new column lengths
  for(int row=0; row<source->GetNumRows(); row++)
  {
    for(int j=0; j<source->GetRowLength(row); j++)
    {
      int column = source->GetColumnIndex(row, j);
      rowLength[column]++;
    }
  }

  // extend size
  for(int row=0; row<oldNumRows; row++)
  {
    columnIndices[row] = (int*) realloc (columnIndices[row], sizeof(int) * rowLength[row]);
    columnEntries[row] = (double*) realloc (columnEntries[row], sizeof(double) * rowLength[row]);
  }

  // write entries into their place
  for(int i=0; i<oldNumRows; i++)
    rowLength[i] = oldRowLengths[i];

  for(int row=0; row<source->GetNumRows(); row++)
  {
    for(int j=0; j<source->GetRowLength(row); j++)
    {
      int column = source->GetColumnIndex(row, j);
      columnIndices[column][rowLength[column]] = oldNumRows + row;
      columnEntries[column][rowLength[column]] = source->GetEntry(row, j);
      rowLength[column]++;
    }
  }

  free(oldRowLengths);

  // append zero diagonal in lower-right block (helps with some solvers, such as PARDISO)
  for(int row=0; row<source->GetNumRows(); row++)
  {
    rowLength[oldNumRows + row]++;
    columnIndices[oldNumRows + row] = (int*) realloc (columnIndices[oldNumRows + row], sizeof(int) * rowLength[oldNumRows + row]);
    columnEntries[oldNumRows + row] = (double*) realloc (columnEntries[oldNumRows + row], sizeof(double) * rowLength[oldNumRows + row]);
    columnIndices[oldNumRows + row][rowLength[oldNumRows + row] - 1] = oldNumRows + row;
    columnEntries[oldNumRows + row][rowLength[oldNumRows + row] - 1] = 0.0;
  }
}

SparseMatrix * SparseMatrix::CreateIdentityMatrix(int numRows)
{
  SparseMatrixOutline * outline = new SparseMatrixOutline(numRows);
  for (int row=0; row<numRows; row++)
    outline->AddEntry(row, row, 1.0);
  SparseMatrix * mat = new SparseMatrix(outline);
  delete outline;
  return mat;
}
