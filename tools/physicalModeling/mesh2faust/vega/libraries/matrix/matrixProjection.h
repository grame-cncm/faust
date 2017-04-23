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

#ifndef _MATRIXPROJECTION_H_
#define _MATRIXPROJECTION_H_

/*
  These routines allow you to multiply a matrix with a vector,
  and project a vector onto a space spanned by an orthogonal matrix.
  They require a BLAS implementation for your system.

  See also matrixIO.h.
*/

// construct vector f, using the equation f = U q
// matrix U is of size n x r
template <class real>
void SynthesizeVector(int n, int r, real * U, real * q, real * f);

// construct sparse vector f, using the equation f = U q
// matrix U is of size n x r, and is given in the column-major order
// vector q is of length r
// the coordinates of the vector f of interest are specified in the array i_buffer
// k is the total number of requested coordinates
// result is written into vector f. Length of result is k <= n
template <class real>
void SynthesizeSparseVector(int n, int r, real * U, real * q, real * f, int * i_buffer, int k);

// project vector f onto basis, given by U, using the equation q = U^T f
// matrix U is of size n x r
template <class real>
void ProjectVector(int n, int r, real * U, real * q, real * f);

// project sparse vector f onto basis, given by U, using the equation q = U^T f
// matrix U is of size n x r
// number of non-zero components of f is given by k
// non-zero components of vector f are given by f_buffer and i_buffer, where i_buffer[j] specifies the position,
// and f_buffer[j] specifies the force component at i_buffer[j]
template <class real>
void ProjectSparseVector(int n, int r, real * U, real * q, real * f_buffer, int * i_buffer, int k);

#endif

