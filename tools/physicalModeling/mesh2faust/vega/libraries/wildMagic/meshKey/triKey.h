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

#ifndef TRIKEYS_H
#define TRIKEYS_H

#include <algorithm>

// unoriented edge
struct UEdgeKey
{
  int v[2];
  inline UEdgeKey(int v0, int v1);
  inline UEdgeKey();//creates an invalid key with v = {-1,-1}
  const int & operator[](int index) const { return v[index]; }
  inline bool operator < (const UEdgeKey &) const;
  inline bool operator == (const UEdgeKey &) const;
};

// oriented edge
struct OEdgeKey
{
  int v[2];
  inline OEdgeKey(int v0, int v1);
  inline OEdgeKey();//creates an invalid key with v = {-1,-1}
  const int & operator[](int index) const { return v[index]; }
  inline bool operator < (const OEdgeKey &) const;
  inline void reverse(); // reverse the orientation of this edge
};

// unoriented triangle key based on vtx indices
struct UTriKey
{
  
  inline UTriKey(const int v[3]);
  inline UTriKey(int v0, int v1, int v2);
  inline UTriKey(); // creates an invalid key with v = {-1,-1,-1}
  inline bool operator < (const UTriKey &) const;
  inline bool operator == (const UTriKey &) const;
  const int & operator[](int index) const { return v[index]; } 
  const int * indices() const { return v; }
  UEdgeKey uEdgeKey(int ind) const;
protected:
  int v[3];
};

// oriented triangle key that remember its orientation
struct OTriKey : public UTriKey
{
  inline OTriKey(const int v[3]);
  inline OTriKey(int v0, int v1, int v2);
  inline OTriKey();
  inline void reverse(); // reverse the orientation
  // permute v0, v1, v2 and store into r0, r1, r2 so that they share the same orientation but r0 = min(v0,v1,v2)
  inline static void permute(int v0, int v1, int v2, int & r0, int & r1, int & r2);
  //  UEdgeKey unorientedEdgeKey(int ind) const;
  inline int getInd(const int vtx) const;
  OEdgeKey oEdgeKey(int ind) const;
  static const int triEdgeIndex[3][2];
};


///////////////////////////////////////////////////////////////////////////////
//                             IMPLEMENTATION                                //
///////////////////////////////////////////////////////////////////////////////

inline UEdgeKey::UEdgeKey(int v0, int v1)
{
  if (v0 < v1)
  {
    v[0] = v0; v[1] = v1;
  }
  else
  {
    v[0] = v1; v[1] = v0;
  }
}

inline UEdgeKey::UEdgeKey()
{
  v[0] = v[1] = -1;
}

inline bool UEdgeKey::operator < (const UEdgeKey & other) const
{
  if (v[0] < other.v[0]) 
    return true;
  if (v[0] > other.v[0]) 
    return false;
  return v[1] < other.v[1];
}

inline bool UEdgeKey::operator == (const UEdgeKey & other) const
{
  return v[0] == other.v[0] && v[1] == other.v[1];
}

inline OEdgeKey::OEdgeKey(int v0, int v1)
{
  v[0] = v0;
  v[1] = v1;
}

inline OEdgeKey::OEdgeKey()
{
  v[0] = v[1] = -1;
}

inline bool OEdgeKey::operator < (const OEdgeKey & other) const
{
  if (v[0] < other.v[0]) 
    return true;
  if (v[0] > other.v[0]) 
    return false;
  return v[1] < other.v[1];
}

inline void OEdgeKey::reverse()
{
  std::swap(v[0], v[1]);
}

inline UTriKey::UTriKey(int v0, int v1, int v2)
{
  v[0] = v0;
  v[1] = v1;
  v[2] = v2;
  std::sort(v, v + 3);
}

inline UTriKey::UTriKey(const int vtx[3])
{
  v[0] = vtx[0];
  v[1] = vtx[1];
  v[2] = vtx[2];
  std::sort(v, v + 3);
}

inline UTriKey::UTriKey()
{
  v[0] = v[1] = v[2] = -1;
}

inline bool UTriKey::operator < (const UTriKey & other) const
{
  if (v[0] < other.v[0]) 
    return true;
  if (v[0] > other.v[0]) 
    return false;
  if (v[1] < other.v[1]) 
    return true;
  if (v[1] > other.v[1]) 
    return false;
  return v[2] < other.v[2];
}

inline bool UTriKey::operator == (const UTriKey & other) const
{
  return v[0] == other.v[0] && v[1] == other.v[1] && v[2] == other.v[2];
}

inline UEdgeKey UTriKey::uEdgeKey(int ind) const
{
  return UEdgeKey(v[OTriKey::triEdgeIndex[ind][0]], v[OTriKey::triEdgeIndex[ind][1]]);
}

inline OEdgeKey OTriKey::oEdgeKey(int ind) const
{
  return OEdgeKey(v[OTriKey::triEdgeIndex[ind][0]], v[OTriKey::triEdgeIndex[ind][1]]);
}

inline OTriKey::OTriKey(int v0, int v1, int v2)
{
  permute(v0, v1, v2, v[0], v[1], v[2]);
}

inline OTriKey::OTriKey(const int vtx[3])
{
  permute(vtx[0], vtx[1], vtx[2], v[0], v[1], v[2]);
}

inline OTriKey::OTriKey()
{
  v[0] = v[1] = v[2] = -1;
}

inline void OTriKey::permute(int v0, int v1, int v2, int & r0, int & r1, int & r2)
{
  if (v0 < v1)
  {
    if (v0 < v2)
    {
      r0 = v0; r1 = v1; r2 = v2;
    }
    else
    { // v2 <= v0
      r0 = v2; r1 = v0; r2 = v1;
    }
  }
  else
  { // v1 <= v0
    if (v1 < v2)
    {
      r0 = v1; r1 = v2; r2 = v0;
    }
    else
    { // v2 <= v1
      r0 = v2; r1 = v0; r2 = v1;
    }
  }
}

inline void OTriKey::reverse()
{
  std::swap(v[1], v[2]);
}

inline int OTriKey::getInd(const int vtx) const
{
  for(int i = 0; i < 3; i++)
    if (vtx == v[i])
      return i;
  return -1;
}

#endif
