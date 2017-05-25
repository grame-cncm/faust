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
  Wrapper to expokit routines.
  See also matrix.h.
*/

#ifndef _EXPOKIT_H_
#define _EXPOKIT_H_

#ifdef __APPLE__
  #define INTEGER long int
#else
  #define INTEGER int
#endif

extern"C" {
void sgpadm_(INTEGER * ideg, INTEGER * m, float * t, float * H,
             INTEGER * ldh, float * wsp, INTEGER * lwsp, 
             INTEGER * ipiv, INTEGER * iexph, INTEGER * ns, INTEGER * flag);

void dgpadm_(INTEGER * ideg, INTEGER * m, double * t, double * H,
             INTEGER * ldh, double * wsp, INTEGER * lwsp, 
             INTEGER * ipiv, INTEGER * iexph, INTEGER * ns, INTEGER * flag);
}

/*
Fortran definition:

subroutine DGPADM( ideg,m,t,H,ldh,wsp,lwsp,ipiv,iexph,ns,iflag )
      implicit none
      integer ideg, m, ldh, lwsp, iexph, ns, iflag, ipiv(m)
      double precision t, H(ldh,m), wsp(lwsp)
*/

#endif
