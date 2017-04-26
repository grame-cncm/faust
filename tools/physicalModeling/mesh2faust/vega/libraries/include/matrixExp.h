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
  Matrix wrappers to expokit routines.
  Note: although the wrappers are templated, only the value real=double works.
  This is because expokit supports double precision matrix exponentials 
  (DGPADM), but does not currently include a single-precision routine SGPADM.
  See also matrix.h and expokit_xgpadm.h.
*/

#ifndef _MATRIXEXP_H_
#define _MATRIXEXP_H_

// computes exp(mtx*t)
template<class real>
int MatrixExp(int m, real * mtx, real t, real * output, int ideg=6);

// computes w = exp(mtx*t)*v
template<class real>
int MatrixExpv(int m, real * mtx, real t, real * v, real * w, int ideg=6);

#endif
