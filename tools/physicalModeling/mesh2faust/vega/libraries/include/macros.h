/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "macros" include files, Copyright (C) 2007 CMU, 2009 MIT, 2016 USC    *
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

#ifndef _MACROS_H_
#define _MACROS_H_

#ifndef PI
  #define PI 3.141592653589793238462643
#endif

#ifndef M_PI
  #define M_PI 3.141592653589793238462643
#endif

#define DOTPRODUCT(x1,y1,z1,x2,y2,z2)\
\
  ((x1)*(x2) + (y1)*(y2) + (z1)*(z2))

#define CROSSPRODUCT(x1,y1,z1,x2,y2,z2,x,y,z)\
\
  x = (y1) * (z2) - (y2) * (z1);\
  y = (x2) * (z1) - (x1) * (z2);\
  z = (x1) * (y2) - (x2) * (y1)

#define CROSSPRODUCT_ADD(x1,y1,z1,x2,y2,z2,x,y,z)\
\
  (x) += (y1) * (z2) - (y2) * (z1);\
  (y) += (x2) * (z1) - (x1) * (z2);\
  (z) += (x1) * (y2) - (x2) * (y1)

#define XSTR11(s) STR11(s)
#define STR11(s) #s

#endif

