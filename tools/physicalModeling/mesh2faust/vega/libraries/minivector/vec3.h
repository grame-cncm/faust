/*
* Copyright (c) 2008, Carnegie Mellon University
* All rights reserved.
*
* Code author: Jernej Barbic
* Research: Jernej Barbic, Doug L. James
* Funding: NSF, Link Foundation
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of Carnegie Mellon University, nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE* DISCLAIMED. IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  A simple class for vector algebra on 3D vectors 
  (summation, normalization, dot product, cross product, etc.).
*/

#ifndef _MINIVEC3_H_
#define _MINIVEC3_H_

#include <stdio.h>
#include <math.h>
#include <ostream>

// forward declarations for external helper functions
template <typename real> class Vec3;
template <typename real> inline Vec3<real> operator* (real alpha, Vec3<real> vec);
template <typename real> inline Vec3<real> operator/ (real alpha, Vec3<real> vec);
template <typename real> inline real dot(const Vec3<real> & vec1, const Vec3<real> & vec2); 
template <typename real> inline Vec3<real> cross(const Vec3<real> & vec1, const Vec3<real> & vec2); // cross product
template <typename real> inline real len(const Vec3<real> & vec); // length of vector
template <typename real> inline real len2(const Vec3<real> & vec); // length^2 of vector
template <typename real> inline Vec3<real> norm(const Vec3<real> & vec); // returns normalized vector (unit length)
template <typename real> inline std::ostream & operator << (std::ostream & s, const Vec3<real> & v);

typedef Vec3<double> Vec3d;
typedef Vec3<float> Vec3f;

template <class real>
class Vec3
{
public:
  inline Vec3() {}
  inline Vec3(real x, real y, real z) { elt[0]=x; elt[1]=y; elt[2]=z; }
  inline Vec3(real entry); // create a vector with all entries "entry" (can create zero vector for entry=0.0)
  inline Vec3(const real * vec); // create a vector from the array of three reals pointed to by "vec"
  inline Vec3(const Vec3 & vec);

  inline void set(real x0, real x1, real x2); // assign vector [x0, x1, x2]
  inline void set(real value); // set all elements to value

  inline Vec3 & operator=(const Vec3 & source);
  inline bool operator==(const Vec3 & vec) const;

  inline const Vec3 operator+ (const Vec3 & vec) const;
  inline Vec3 & operator+= (const Vec3 & vec);

  inline const Vec3 operator- (const Vec3 & vec) const;
  inline Vec3 & operator-= (const Vec3 & vec);

  inline const Vec3 operator* (real scalar) const;
  inline Vec3 & operator*= (real scalar);

  inline Vec3 operator/ (real scalar) const;
  inline Vec3 & operator/= (real scalar);

  inline void normalize(); // normalize itself 

  void print() const; // print the vector out

  inline real & operator[] (int index); // v[i] returns i-th entry of v
  inline const real & operator[] (int index) const;

  // finds a unit vector orthogonal to this vector
  Vec3 findOrthonormalVector() const;

  // copies the vector into an array of length 3
  inline void convertToArray(real * vecArray) const;
  
protected:
  real elt[3];
};

// === below is the implementation ===

template <class real>
inline Vec3<real>::Vec3(real entry)
{
  elt[0] = entry;
  elt[1] = entry;
  elt[2] = entry;
}

template <class real>
inline Vec3<real>::Vec3(const real * vec)
{
  elt[0] = vec[0];
  elt[1] = vec[1];
  elt[2] = vec[2];
}

template <class real>
inline Vec3<real>::Vec3(const Vec3<real> & vec)
{
  elt[0] = vec.elt[0];
  elt[1] = vec.elt[1];
  elt[2] = vec.elt[2];
}

template <class real>
inline Vec3<real> & Vec3<real>::operator=(const Vec3<real> & source)
{
  elt[0] = source.elt[0];
  elt[1] = source.elt[1];
  elt[2] = source.elt[2];

  return *this;
}

template <class real>
inline bool Vec3<real>::operator==(const Vec3<real> & vec) const
{
  return ((elt[0] == vec[0]) &&
          (elt[1] == vec[1]) &&
          (elt[2] == vec[2]));
}

template <class real>
inline Vec3<real> operator* (real scalar, const Vec3<real> & vec)
{
  Vec3<real> result = vec;
  result.elt[0] *= scalar;
  result.elt[1] *= scalar;
  result.elt[2] *= scalar;

  return result;
}

template <class real>
inline Vec3<real> operator/ (real scalar, const Vec3<real> & vec)
{
  Vec3<real> result = vec;
  result.elt[0] /= scalar;
  result.elt[1] /= scalar;
  result.elt[2] /= scalar;

  return result;
}

template <class real>
inline const Vec3<real> Vec3<real>::operator+ (const Vec3<real> & vec) const
{
  Vec3<real> sum = *this;
  sum.elt[0] += vec.elt[0];
  sum.elt[1] += vec.elt[1];
  sum.elt[2] += vec.elt[2];

  return sum;
}

template <class real>
inline Vec3<real> & Vec3<real>::operator+= (const Vec3<real> & vec)
{
  elt[0] += vec.elt[0];
  elt[1] += vec.elt[1];
  elt[2] += vec.elt[2];

  return *this;
}

template <class real>
inline const Vec3<real> Vec3<real>::operator- (const Vec3<real> & vec) const
{
  Vec3<real> sum = *this;
  sum.elt[0] -= vec.elt[0];
  sum.elt[1] -= vec.elt[1];
  sum.elt[2] -= vec.elt[2];

  return sum;
}

template <class real>
inline Vec3<real> & Vec3<real>::operator-= (const Vec3<real> & vec)
{
  elt[0] -= vec.elt[0];
  elt[1] -= vec.elt[1];
  elt[2] -= vec.elt[2];

  return *this;
}

template <class real>
inline real & Vec3<real>::operator[] (int index)
{
  return elt[index];
}

template <class real>
inline const real & Vec3<real>::operator[] (int index) const
{
  return elt[index];
}

template <class real>
inline real dot(const Vec3<real> & vec1, const Vec3<real> & vec2)
{
  return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}

template <class real>
inline Vec3<real> cross(const Vec3<real> & vec1, const Vec3<real> & vec2)
{
  Vec3<real> result(vec1[1] * vec2[2] - vec2[1] * vec1[2],
                   -vec1[0] * vec2[2] + vec2[0] * vec1[2],
                    vec1[0] * vec2[1] - vec2[0] * vec1[1]);

  return result;
}

template <class real>
inline Vec3<real> norm(const Vec3<real> & vec)
{
  real norm2 = dot(vec,vec);
  Vec3<real> result = vec;
  result *= 1.0 / sqrt(norm2);
  
  return result;
}

template <class real>
inline Vec3<real> & Vec3<real>::operator*= (real scalar)
{
  elt[0] *= scalar;
  elt[1] *= scalar;
  elt[2] *= scalar;
  return *this;
}

template <class real>
inline const Vec3<real> Vec3<real>::operator* (real scalar) const
{
  return (Vec3<real>(elt[0]*scalar, elt[1]*scalar, elt[2]*scalar));
}

template <class real>
inline Vec3<real> Vec3<real>::operator/ (real scalar) const
{
  return (Vec3<real>(elt[0]/scalar, elt[1]/scalar, elt[2]/scalar));
}

template <class real>
inline Vec3<real> & Vec3<real>::operator/= (real scalar)
{
  elt[0] /= scalar;
  elt[1] /= scalar;
  elt[2] /= scalar;
  return *this;
}

template <class real>
inline real len(const Vec3<real> & vec)
{
  return(sqrt(dot(vec,vec)));
}

template <class real>
inline real len2(const Vec3<real> & vec)
{
  return(dot(vec,vec));
}

template <class real>
inline std::ostream & operator << (std::ostream & s, const Vec3<real> & v)
{
  real a = v[0];
  real b = v[1];
  real c = v[2];
  
  return(s << '[' << a << ' ' << b << ' ' << c << ']');
}

template <class real>
inline void Vec3<real>::convertToArray(real * vecArray) const
{
  vecArray[0] = elt[0];
  vecArray[1] = elt[1];
  vecArray[2] = elt[2];
}

template <class real>
inline void Vec3<real>::normalize()
{
  real invMag = 1.0 / sqrt(elt[0]*elt[0] + elt[1]*elt[1] + elt[2]*elt[2]);
  elt[0] *= invMag;
  elt[1] *= invMag;
  elt[2] *= invMag;
}

template <class real>
inline void Vec3<real>::print() const
{
  real a = elt[0];
  real b = elt[1];
  real c = elt[2];
  
  printf("[%G %G %G]\n", a, b, c);
}

template <class real>
inline void Vec3<real>::set(real x0, real x1, real x2) // assign vector [x0, x1, x2]
{
  elt[0] = x0;
  elt[1] = x1;
  elt[2] = x2;
}

template <class real>
inline void Vec3<real>::set(real value) // set all elements to value
{
  elt[0] = value;
  elt[1] = value;
  elt[2] = value;
}

// Given an input vector v, find a unit vector that is orthogonal to it 
template <class real>
Vec3<real> Vec3<real>::findOrthonormalVector() const
{
  // find smallest abs component of v
  int smallestIndex = 0;
  for(int dim=1; dim<3; dim++)
    if (fabs(elt[dim]) < fabs(elt[smallestIndex]))
      smallestIndex = dim;

  Vec3<real> axis(0.0, 0.0, 0.0);
  axis[smallestIndex] = 1.0;

  // this cross-product will be non-zero (as long as v is not zero)
  Vec3<real> result = norm(cross(elt, axis));
  return result;
}

#endif

