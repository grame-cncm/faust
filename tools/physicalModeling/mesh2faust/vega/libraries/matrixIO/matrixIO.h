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

/*
  These routines allow you to read/write a dense matrix from/to a file,
  using a special simple binary format. LAPACK-style column-major
  format is used. The code is templated for "float" and "double" datatypes.

  See also matrix.h.
  
  Binary file format, for a m x n matrix, is:
  <m> <n> <data>
  where: m is an integer (of type "int")
         n is an integer (of type "int")
         data is a sequence of m*n real numbers (of type either "float" or "double")

  All quantities are stored in binary format.
  Data is stored in column-major format (as in LAPACK): 
  first column first, then second column, and so on.
  Total file size is 2 * sizeof(int) + m * n * sizeof(real),
  where real is either "float" or "double".

  Underscored routines will perform error checking and cause the program to abort 
  in case of error when accessing the file.
*/

#ifndef _MATRIXIO_H_
#define _MATRIXIO_H_

#include <stdio.h>
#include <stdlib.h>
#include "matrixMacros.h"

// === matrix input/output routines ===

template <class real>
int ReadMatrixFromDisk(const char * filename, int * m, int * n, real ** matrix);
template <class real>
int ReadMatrixFromDisk_(const char * filename, int * m, int * n, real ** matrix);

int ReadMatrixSizeFromDisk(const char * filename, int * m, int * n);
void ReadMatrixSizeFromDisk_(const char * filename, int * m, int * n);
void ChangeMatrixHeader(const char * filename, int numRows, int numColumns); // overwrites any previous header; keeps data intact

template <class real>
int WriteMatrixToDisk(const char * filename, int m, int n, const real * matrix);
template <class real>
int WriteMatrixToDisk_(const char * filename, int m, int n, const real * matrix);

template <class real>
int AppendMatrixToDisk(const char * filename, int m, int n, const real * matrix);
template <class real>
int AppendMatrixToDisk_(const char * filename, int m, int n, const real * matrix);

template <class real>
int ReadMatrixFromDiskTextFile(const char * filename, int * m, int * n, real ** matrix);

template <class real>
int WriteMatrixToDiskTextFile(const char * filename, int m, int n, const real * matrix);

// "fileList" is a filename of a text file that contains the matrices to be loaded (concatenated column-wise) into the matrix, one text entry per line of "fileList"
template <class real>
int ReadMatrixFromDiskListOfFiles(const char * fileList, int * m, int * n, real ** matrix);

// prints the matrix to standard output in Mathematica format
template <class real>
void PrintMatrixInMathematicaFormat(int n, int r, real * U);

// === assert and abort ===

// if (a!=b) exit program (and print the integer "assertionIdentifier" to stdout)
int Assert_(int a, int b, int assertionIdentifier);
int Assert_(bool cond, int assertionIdentifier);

// exit the program, by first printing the "reason" text message
void Abort_(const char * reason);
void Abort_(const char * reason, int exitCode);

// === stream routines (they operate on a file that is already open, in binary mode) ===

int OpenFile_(const char * filename, FILE ** fin, const char * mode);

template <class real>
int WriteMatrixToStream(FILE * file, int m, int n, const real * matrix);

int WriteMatrixHeaderToStream(FILE * file, int m, int n);

template <class real>
int ReadMatrixFromStream(FILE * file, int m, int n, real * matrix);

int ReadMatrixSizeFromStream(FILE * file, int * m, int * n);

// === helper routines ===

template<class T>
int ReadBinary(FILE * fin, T * data);
template<class T>
void ReadBinary_(FILE * fin, T * data);

template<class T>
int ReadBinaryBuffer(FILE * fin, int size, T * data);
template<class T>
void ReadBinaryBuffer_(FILE * fin, int size, T * data);

// === specific research routines for linear modal analysis (rarely used) ===

template <class real>
int ReadModesFromDisk(const char * filename, int * n, int * r, real ** frequencies, real ** modes);

int ReadModeInfoFromDisk(const char * filename, int * n, int * r);

template <class real>
int WriteModesToDisk(const char * filename, int n, int r, real * frequencies, real * modes);

#endif

