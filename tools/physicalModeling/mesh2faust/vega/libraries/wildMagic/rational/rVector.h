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


#ifndef RVECTOR_H
#define RVECTOR_H

#include "rational.h"
#include <cassert>

template <int VSIZE, int ISIZE>
class RVector
{
public:
  // Construction.
  RVector ();
  RVector (const RVector& vec);

  // Coordinate access.
  inline operator const Rational<ISIZE>* () const;
  inline operator Rational<ISIZE>* ();
  inline const Rational<ISIZE>& operator[] (int i) const;
  inline Rational<ISIZE>& operator[] (int i);

  // Assignment.
  RVector& operator= (const RVector& vec);

  // Comparison.
  bool operator== (const RVector& vec) const;
  bool operator!= (const RVector& vec) const;
  bool operator<  (const RVector& vec) const;
  bool operator<= (const RVector& vec) const;
  bool operator>  (const RVector& vec) const;
  bool operator>= (const RVector& vec) const;

  // Arithmetic operations.
  RVector operator+ (const RVector& vec) const;
  RVector operator- (const RVector& vec) const;
  RVector operator* (const Rational<ISIZE>& scalar) const;
  RVector operator/ (const Rational<ISIZE>& scalar) const;
  RVector operator- () const;

  // Arithmetic updates.
  RVector& operator+= (const RVector& vec);
  RVector& operator-= (const RVector& vec);
  RVector& operator*= (const Rational<ISIZE>& scalar);
  RVector& operator/= (const Rational<ISIZE>& scalar);

  // Vector operations.
  Rational<ISIZE> squaredLength () const;
  Rational<ISIZE> dot (const RVector& vec) const;

protected:
  // Support for comparisons.
  int compareArrays (const RVector& vec) const;

  Rational<ISIZE> tuple[VSIZE];
};

template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE> operator* (const Rational<ISIZE>& scalar,
    const RVector<VSIZE,ISIZE>& vec);


template <int ISIZE>
class RVector3 : public RVector<3,ISIZE>
{
public:
  // Construction.
  RVector3 ();
  RVector3 (const RVector3& vec);
  RVector3 (const RVector<3,ISIZE>& vec);
  RVector3 (const Rational<ISIZE>& x, const Rational<ISIZE>& y, const Rational<ISIZE>& z);

  // Member access.
  inline Rational<ISIZE> X () const;
  inline Rational<ISIZE>& X ();
  inline Rational<ISIZE> Y () const;
  inline Rational<ISIZE>& Y ();
  inline Rational<ISIZE> Z () const;
  inline Rational<ISIZE>& Z ();

  // Assignment.
  RVector3& operator= (const RVector3& vec);
  RVector3& operator= (const RVector<3,ISIZE>& vec);

  // Returns dot(this,V).
  Rational<ISIZE> dot (const RVector3& vec) const;

  // Returns cross(this,V).
  RVector3 cross (const RVector3& vec) const;

  // Returns dot(this,cross(U,V)).
  Rational<ISIZE> tripleScalar (const RVector3& U, const RVector3& V) const;

protected:
  using RVector<3,ISIZE>::tuple;
};




//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE>::RVector ()
{
  // For efficiency in construction of large arrays of vectors, the
  // default constructor does not initialize the vector.
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE>::RVector (const RVector& vec)
{
  for(int i = 0; i < VSIZE; ++i)
  {
    tuple[i] = vec.tuple[i];
  }
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
inline RVector<VSIZE,ISIZE>::operator const Rational<ISIZE>* () const
{
  return tuple;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
inline RVector<VSIZE,ISIZE>::operator Rational<ISIZE>* ()
{
  return tuple;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
inline const Rational<ISIZE>& RVector<VSIZE,ISIZE>::operator[] (int i) const
{
  assert(0 <= i && i < VSIZE);
  return tuple[i];
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
inline Rational<ISIZE>& RVector<VSIZE,ISIZE>::operator[] (int i)
{
  assert(0 <= i && i < VSIZE);
  return tuple[i];
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE>& RVector<VSIZE,ISIZE>::operator= (const RVector& vec)
{
  for(int i = 0; i < VSIZE; ++i)
  {
    tuple[i] = vec.tuple[i];
  }
  return *this;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
bool RVector<VSIZE,ISIZE>::operator== (const RVector& vec) const
{
  for(int i = 0; i < VSIZE; ++i)
  {
    if (tuple[i] != vec.tuple[i])
    {
      return false;
    }
  }
  return true;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
bool RVector<VSIZE,ISIZE>::operator!= (const RVector& vec) const
{
  return !operator==(vec);
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
int RVector<VSIZE,ISIZE>::compareArrays (const RVector& vec) const
{
  for(int i = 0; i < VSIZE; ++i)
  {
    if (tuple[i] < vec.tuple[i])
    {
      return -1;
    }
    if (tuple[i] > vec.tuple[i])
    {
      return +1;
    }
  }
  return 0;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
bool RVector<VSIZE,ISIZE>::operator< (const RVector& vec) const
{
  return compareArrays(vec) < 0;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
bool RVector<VSIZE,ISIZE>::operator<= (const RVector& vec) const
{
  return compareArrays(vec) <= 0;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
bool RVector<VSIZE,ISIZE>::operator> (const RVector& vec) const
{
  return compareArrays(vec) > 0;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
bool RVector<VSIZE,ISIZE>::operator>= (const RVector& vec) const
{
  return compareArrays(vec) >= 0;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE> RVector<VSIZE,ISIZE>::operator+ (const RVector& vec)
const
{
  RVector<VSIZE,ISIZE> sum;
  for(int i = 0; i < VSIZE; ++i)
  {
    sum.tuple[i] = tuple[i] + vec.tuple[i];
  }
  return sum;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE> RVector<VSIZE,ISIZE>::operator- (const RVector& vec)
const
{
  RVector<VSIZE,ISIZE> diff;
  for(int i = 0; i < VSIZE; ++i)
  {
    diff.tuple[i] = tuple[i] - vec.tuple[i];
  }
  return diff;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE> RVector<VSIZE,ISIZE>::operator*
(const Rational<ISIZE>& scalar) const
{
  RVector<VSIZE,ISIZE> prod;
  for(int i = 0; i < VSIZE; ++i)
  {
    prod.tuple[i] = scalar*tuple[i];
  }
  return prod;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE> RVector<VSIZE,ISIZE>::operator/
(const Rational<ISIZE>& scalar) const
{
  assertion(scalar != 0, "Division by zero\n");

  RVector<VSIZE,ISIZE> div;
  for(int i = 0; i < VSIZE; ++i)
  {
    div.tuple[i] = tuple[i]/scalar;
  }

  return div;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE> RVector<VSIZE,ISIZE>::operator- () const
{
  RVector<VSIZE,ISIZE> neg;
  for(int i = 0; i < VSIZE; ++i)
  {
    neg.tuple[i] = -tuple[i];
  }
  return neg;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE> operator* (const Rational<ISIZE>& scalar,
    const RVector<VSIZE,ISIZE>& vec)
    {
  RVector<VSIZE,ISIZE> prod;
  for(int i = 0; i < VSIZE; ++i)
  {
    prod[i] = scalar*vec[i];
  }
  return prod;
    }
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE>& RVector<VSIZE,ISIZE>::operator+= (const RVector& vec)
{
  for(int i = 0; i < VSIZE; ++i)
  {
    tuple[i] += vec.tuple[i];
  }
  return *this;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE>& RVector<VSIZE,ISIZE>::operator-= (const RVector& vec)
{
  for(int i = 0; i < VSIZE; ++i)
  {
    tuple[i] -= vec.tuple[i];
  }
  return *this;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE>& RVector<VSIZE,ISIZE>::operator*=
    (const Rational<ISIZE>& scalar)
    {
  for(int i = 0; i < VSIZE; ++i)
  {
    tuple[i] *= scalar;
  }
  return *this;
    }
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
RVector<VSIZE,ISIZE>& RVector<VSIZE,ISIZE>::operator/=
    (const Rational<ISIZE>& scalar)
    {
  //assertion(scalar != 0, "Division by zero\n");

  for(int i = 0; i < VSIZE; ++i)
  {
    tuple[i] /= scalar;
  }
  return *this;
    }
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
Rational<ISIZE> RVector<VSIZE,ISIZE>::squaredLength () const
{
  Rational<ISIZE> sqrLen = 0;
  for(int i = 0; i < VSIZE; ++i)
  {
    sqrLen += tuple[i]*tuple[i];
  }
  return sqrLen;
}
//----------------------------------------------------------------------------
template <int VSIZE, int ISIZE>
Rational<ISIZE> RVector<VSIZE,ISIZE>::dot (const RVector& vec) const
{
  Rational<ISIZE> dot = 0;
  for(int i = 0; i < VSIZE; ++i)
  {
    dot += tuple[i]*vec.tuple[i];
  }
  return dot;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
template <int ISIZE>
RVector3<ISIZE>::RVector3 ()
{
  // the vector is uninitialized
}
//----------------------------------------------------------------------------
template <int ISIZE>
RVector3<ISIZE>::RVector3 (const RVector3& vec)
{
  tuple[0] = vec.tuple[0];
  tuple[1] = vec.tuple[1];
  tuple[2] = vec.tuple[2];
}
//----------------------------------------------------------------------------
template <int ISIZE>
RVector3<ISIZE>::RVector3 (const RVector<3,ISIZE>& vec)
{
  tuple[0] = vec[0];
  tuple[1] = vec[1];
  tuple[2] = vec[2];
}
//----------------------------------------------------------------------------
template <int ISIZE>
RVector3<ISIZE>::RVector3 (const Rational<ISIZE>& x, const Rational<ISIZE>& y, const Rational<ISIZE>& z)
{
  tuple[0] = x;
  tuple[1] = y;
  tuple[2] = z;
}
//----------------------------------------------------------------------------
template <int ISIZE>
RVector3<ISIZE>& RVector3<ISIZE>::operator= (const RVector3& vec)
{
  tuple[0] = vec.tuple[0];
  tuple[1] = vec.tuple[1];
  tuple[2] = vec.tuple[2];
  return *this;
}
//----------------------------------------------------------------------------
template <int ISIZE>
RVector3<ISIZE>& RVector3<ISIZE>::operator= (const RVector<3,ISIZE>& vec)
{
  tuple[0] = vec[0];
  tuple[1] = vec[1];
  tuple[2] = vec[2];
  return *this;
}
//----------------------------------------------------------------------------
template <int ISIZE>
inline Rational<ISIZE> RVector3<ISIZE>::X () const
{
  return tuple[0];
}
//----------------------------------------------------------------------------
template <int ISIZE>
inline Rational<ISIZE>& RVector3<ISIZE>::X ()
{
  return tuple[0];
}
//----------------------------------------------------------------------------
template <int ISIZE>
inline Rational<ISIZE> RVector3<ISIZE>::Y () const
{
  return tuple[1];
}
//----------------------------------------------------------------------------
template <int ISIZE>
inline Rational<ISIZE>& RVector3<ISIZE>::Y ()
{
  return tuple[1];
}
//----------------------------------------------------------------------------
template <int ISIZE>
inline Rational<ISIZE> RVector3<ISIZE>::Z () const
{
  return tuple[2];
}
//----------------------------------------------------------------------------
template <int ISIZE>
inline Rational<ISIZE>& RVector3<ISIZE>::Z ()
{
  return tuple[2];
}
//----------------------------------------------------------------------------
template <int ISIZE>
Rational<ISIZE> RVector3<ISIZE>::dot (const RVector3& vec) const
{
  return tuple[0]*vec.tuple[0] + tuple[1]*vec.tuple[1] +
      tuple[2]*vec.tuple[2];
}
//----------------------------------------------------------------------------
template <int ISIZE>
RVector3<ISIZE> RVector3<ISIZE>::cross (const RVector3& vec) const
{
  return RVector3<ISIZE>(
      tuple[1]*vec.tuple[2] - tuple[2]*vec.tuple[1],
      tuple[2]*vec.tuple[0] - tuple[0]*vec.tuple[2],
      tuple[0]*vec.tuple[1] - tuple[1]*vec.tuple[0]);
}
//----------------------------------------------------------------------------
template <int ISIZE>
Rational<ISIZE> RVector3<ISIZE>::tripleScalar (const RVector3& U, const RVector3& V) const 
{
  return dot(U.cross(V));
}
//----------------------------------------------------------------------------
#endif /* RVECTOR_H_ */
