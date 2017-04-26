/*
  This code is based on code from the Geometric Tools library,
  which is licensed under a boost license.
  Such usage is permitted by the boost license; for details, 
  please see the boost license below.
*/

// Geometric Tools, LLC
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt

/*************************************************************************
 *                                                                       *
 * We release our improvements to the wildMagic code under our standard  *
 * Vega FEM license, as follows:                                         *
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "improvements to the wildMagic library" , Copyright (C) 2016 USC      *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Yijing Li                                                *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Funding: National Science Foundation                                  *
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


#ifndef VERTICESQUERYFILTERED_H
#define VERTICESQUERYFILTERED_H

#include "verticesQueryRational.h"

class VerticesQueryFiltered : public VerticesQuery 
{
public:
  // uncertainty: [0,1] 0: double,    1: rational
  VerticesQueryFiltered (int numVertices, const Vec3d * vertices, double uncertainty);
  virtual ~VerticesQueryFiltered();

  // run-time type information
  virtual Type getType () const { return FILTERED; }

  virtual void addVertex(const Vec3d & v);

  virtual int toPlane (const Vec3d& test, int v0, int v1, int v2) const;

  virtual int toCircumsphere (const Vec3d& test, int v0, int v1, int v2, int v3) const;
  virtual int toCircumsphere (const Vec3d& test, int v0, int v1, int v2) const;

protected:

  double uncertainty;
  VerticesQueryRational rational;
};

#endif
