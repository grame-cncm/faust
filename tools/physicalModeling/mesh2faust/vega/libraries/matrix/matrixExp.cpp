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
#include <math.h>
#include "lapack-headers.h"
#include "matrixMacros.h"
#include "matrixBLAS.h"
#include "expokit_xgpadm.h"
#include "matrixExp.h"

#ifdef __APPLE__
  #define DGPADM dgpadm_
  #define SGPADM sgpadm_
  #define INTEGER long int
#else
  #define DGPADM dgpadm_
  #define SGPADM sgpadm_
  #define INTEGER int
#endif

template<bool C>
class _xgpadm {};

template<>
class _xgpadm<true> {
public:
    inline static void f(INTEGER * ideg, INTEGER * m, float * t, float * H,
                 INTEGER * ldh, float * wsp, INTEGER * lwsp,
		 INTEGER * ipiv, INTEGER * iexph, INTEGER * ns, INTEGER * flag)
    {
      printf("Error: routine SGPADM is not supported by expokit.\n");
    }
};


template<>
class _xgpadm<false> {
public:
    inline static void f(INTEGER * ideg, INTEGER * m, double * t, double * H,
                 INTEGER * ldh, double * wsp, INTEGER * lwsp,
		 INTEGER * ipiv, INTEGER * iexph, INTEGER * ns, INTEGER * flag)
    {
      DGPADM(ideg, m, t, H, ldh, wsp, lwsp, ipiv, iexph, ns, flag);
    }
};

// computes output = exp(mtx*t)
template<class real>
int MatrixExp(int m, real * mtx, real t, real * output, int ideg_)
{
  INTEGER ideg = ideg_;
  INTEGER M = m;
  INTEGER ldh = M;
  INTEGER lwsp = 4*M*M+ideg+1;
  real * wsp = (real*) malloc (sizeof(real) * lwsp);
  INTEGER * ipiv = (INTEGER*) malloc (sizeof(INTEGER) * M);
  INTEGER iexph = 0;
  INTEGER ns = 0;
  INTEGER flag = 0;

  int mm = m*m;
  real maxEntry = 0;
  for(int i=0;i<mm; i++)
    maxEntry = MAX(maxEntry, fabs(mtx[i]));

  if (maxEntry != 0)
  {
    _xgpadm<sizeof(real)==sizeof(float)>::f(&ideg, &M, &t, mtx,
        &ldh, wsp, &lwsp,
        ipiv, &iexph, &ns, &flag);

    //printf("iexph=%d ns=%d flag=%d\n", (int)iexph, (int)ns, (int)flag);

    if (flag != 0)
    {
      printf("Error: xgpadm returned non-zero exit flag %d.\n", (int)flag);
      return flag;
    }

    memcpy(output, &wsp[iexph-1], sizeof(real) * m * m);
  }
  else
  {
    // set result to identity matrix
    memset(output, 0, sizeof(real) * m * m);
    for(int i=0; i<m; i++)
      output[ELT(m,i,i)] = 1.0;
  }

  free(wsp);

  return 0;
}

// computes w = exp(mtx*t)*v
template<class real>
int MatrixExpv(int m, real * mtx, real t, real * v, real * w, int ideg_)
{
  INTEGER ideg = ideg_;
  INTEGER M = m;
  INTEGER ldh = M;
  INTEGER lwsp = 4*M*M+ideg+1;
  real * wsp = (real*) malloc (sizeof(real) * lwsp);
  INTEGER * ipiv = (INTEGER*) malloc (sizeof(INTEGER) * M);
  INTEGER iexph = 0;
  INTEGER ns = 0;
  INTEGER flag = 0;

  int mm = m*m;
  real maxEntry = 0;
  for(int i=0;i<mm; i++)
    maxEntry = MAX(maxEntry, fabs(mtx[i]));

  if (maxEntry != 0)
  {
    _xgpadm<sizeof(real)==sizeof(float)>::f(&ideg, &M, &t, mtx,
          &ldh, wsp, &lwsp,
          ipiv, &iexph, &ns, &flag);

    //printf("iexph=%d ns=%d flag=%d\n", (int)iexph, (int)ns, (int)flag);

    if (flag != 0)
    {
      printf("Error: xgpadm returned non-zero exit flag %d.\n", (int)flag);
      return flag;
    }

    real * output = &wsp[iexph-1];
    MultiplyMatrices(M, M, 1, output, v, w);
  }
  else
  {
    memcpy(w,v,sizeof(real)*M);
  }

  free(wsp);

  return 0;
}

template int MatrixExpv(int m, float * mtx, float t, float * v, float * w, int ideg);
template int MatrixExpv(int m, double * mtx, double t, double * v, double * w, int ideg);

template int MatrixExp(int m, float * mtx, float t, float * output, int ideg_);
template int MatrixExp(int m, double * mtx, double t, double * output, int ideg_);
