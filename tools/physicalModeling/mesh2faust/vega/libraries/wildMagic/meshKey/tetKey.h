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

#ifndef TETKEYS_H
#define TETKEYS_H

#include "triKey.h"
#include <algorithm>

// unoriented tet key based on vtx indices
struct UTetKey
{
  inline UTetKey(const int v[4]);
  inline UTetKey(int v0, int v1, int v2, int v3);
  inline bool operator < (const UTetKey &) const;
  const int & operator[](int index) const { return v[index]; } 
  const int * indices() const { return v; }
  UTriKey uFaceKey(int ind) const;

  // opposite face for each vtx in a tet. The faces are ordered so that its normals pointing outside the tet if tet has positive orientation
  // static const int tetFaceIndex[4][3];
protected:
  int v[4];
};

// oriented tet key based on vtx indices
struct OTetKey
{
  inline OTetKey(const int v[4]);
  inline OTetKey(int v0, int v1, int v2, int v3);
  inline bool operator < (const OTetKey &) const;
  const int & operator[](int index) const { return v[index]; } 
  const int * indices() const { return v; }
  OTriKey oFaceKey(int ind) const;
  UTriKey uFaceKey(int ind) const;
  int getInd(const int vtx) const;
  // permute v0, v1, v2, v3 and store into r0, r1, r2, r3 so that they share the same orientation but r0 = min(v0,v1,v2,v3)
  inline static void permute(int v0, int v1, int v2, int v3, int & r0, int & r1, int & r2, int & r3);
  // opposite face for each vtx in a tet. The faces are ordered so that its normals pointing outside the tet if tet has positive orientation
  static const int tetFaceIndex[4][3];

  int v[4];
};


///////////////////////////////////////////////////////////////////////////////
//                             IMPLEMENTATION                                //
///////////////////////////////////////////////////////////////////////////////

inline UTetKey::UTetKey(int v0, int v1, int v2, int v3)
{
  v[0] = v0;
  v[1] = v1;
  v[2] = v2;
  v[3] = v3;
  std::sort(v, v + 4);
}

inline UTetKey::UTetKey(const int vtx[4])
{
  v[0] = vtx[0];
  v[1] = vtx[1];
  v[2] = vtx[2];
  v[3] = vtx[3];
  std::sort(v, v + 4);
}


inline bool UTetKey::operator < (const UTetKey & other) const
{
  if (v[0] < other.v[0]) 
    return true;
  if (v[0] > other.v[0]) 
    return false;
  if (v[1] < other.v[1]) 
    return true;
  if (v[1] > other.v[1]) 
    return false;
  if (v[2] < other.v[2]) 
    return true;
  if (v[2] > other.v[2]) 
    return false;
  return v[3] < other.v[3];
}

inline UTriKey UTetKey::uFaceKey(int ind) const
{
 return UTriKey(v[OTetKey::tetFaceIndex[ind][0]], v[OTetKey::tetFaceIndex[ind][1]], v[OTetKey::tetFaceIndex[ind][2]]);
}

inline void OTetKey::permute(int v0, int v1, int v2, int v3, int & r0, int & r1, int & r2, int & r3) {
  int minInd = 0;
  r0 = v0;
  if (v1 < r0)
  {
    r0 = v1;
    minInd = 1;
  }
  if (v2 < r0)
  {
    r0 = v2;
    minInd = 2;
  }
  if (v3 < r0)
  {
    r0 = v3;
    minInd = 3;
  }

  if (minInd == 0)
    OTriKey::permute(v1, v2, v3, r1, r2, r3);
  else if (minInd == 1)
    OTriKey::permute(v0, v3, v2, r1, r2, r3);
  else if (minInd == 2)
    OTriKey::permute(v0, v1, v3, r1, r2, r3);
  else  // minInd == 3
      OTriKey::permute(v0, v2, v1, r1, r2, r3);
}

inline OTetKey::OTetKey(int v0, int v1, int v2, int v3)
{
  permute(v0, v1, v2, v3, v[0], v[1], v[2], v[3]);
}

inline OTetKey::OTetKey(const int vtx[4])
{
  permute(vtx[0], vtx[1], vtx[2], vtx[3], v[0], v[1], v[2], v[3]);
}

inline bool OTetKey::operator < (const OTetKey & other) const
{
  if (v[0] < other.v[0]) 
    return true;
  if (v[0] > other.v[0]) 
    return false;
  if (v[1] < other.v[1]) 
    return true;
  if (v[1] > other.v[1]) 
    return false;
  if (v[2] < other.v[2]) 
    return true;
  if (v[2] > other.v[2]) 
    return false;
  return v[3] < other.v[3];
}

inline OTriKey OTetKey::oFaceKey(int ind) const
{
 return OTriKey(v[tetFaceIndex[ind][0]], v[tetFaceIndex[ind][1]], v[tetFaceIndex[ind][2]]);
}

inline UTriKey OTetKey::uFaceKey(int ind) const
{
 return UTriKey(v[tetFaceIndex[ind][0]], v[tetFaceIndex[ind][1]], v[tetFaceIndex[ind][2]]);
}

inline int OTetKey::getInd(const int vtx) const
{
 for(int i = 0; i < 4; i++)
  if (vtx == v[i])
    return i;
 return -1;
}

#endif
