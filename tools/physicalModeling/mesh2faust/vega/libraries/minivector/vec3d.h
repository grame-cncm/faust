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

#ifndef _MINIVEC3D_H_
#define _MINIVEC3D_H_

#include <stdio.h>
#include <math.h>
#include <ostream>

class Vec3d {

public:
  inline Vec3d() {}
  inline Vec3d(double x, double y, double z) {elt[0]=x; elt[1]=y; elt[2]=z;}
  inline Vec3d(double entry); // create a vector with all entries "entry" (can create zero vector for entry=0.0)
  inline Vec3d(const double * vec); // create a vector from the array of three doubles pointed to by "vec"
  inline Vec3d(const Vec3d & vec);

  inline void set(double x0, double x1, double x2); // assign vector [x0, x1, x2]
  inline void set(double value); // set all elements to value

  inline Vec3d & operator=(const Vec3d & source);
  inline bool operator==(const Vec3d & vec2) const;
  inline bool operator!=(const Vec3d & vec2) const;

  inline const Vec3d operator+ (const Vec3d & vec2) const;
  inline Vec3d & operator+= (const Vec3d & vec2);

  inline const Vec3d operator- (const Vec3d & vec2) const;
  inline Vec3d & operator-= (const Vec3d & vec2);

  inline const Vec3d operator* (double scalar) const;
  inline Vec3d & operator*= (double scalar);

  inline Vec3d operator/ (double scalar) const;
  inline Vec3d & operator/= (double scalar);

  // operator for Vec3d to be used as a key in std::set, std::map, etc.
  inline bool operator < (const Vec3d & vec2) const;

  friend inline Vec3d operator* (double scalar, const Vec3d & vec2);
  friend inline Vec3d operator/ (double scalar, const Vec3d & vec2);
  friend inline Vec3d operator- (const Vec3d & vec1);

  friend inline double dot(const Vec3d & vec1, const Vec3d & vec2); // dot product

  friend inline Vec3d cross(const Vec3d & vec1, const Vec3d & vec2); // cross product

  friend inline Vec3d norm(const Vec3d & vec1); // returns normalized vector (unit length)
  inline void normalize(); // normalize itself without returning anything

  friend inline std::ostream &operator << (std::ostream &s, const Vec3d &v);
  void print() const;

  friend class Mat3d;

  inline double & operator[] (int index); // v[i] returns i-th entry of v
  inline const double & operator[] (int index) const;

  // finds a unit vector orthogonal to this vector
  Vec3d findOrthonormalVector() const;

  // copies the vector into an array of length 3
  inline void convertToArray(double * vecArray) const;
  // adds the vector into an array of length 3
  inline void addToArray(double * vecArray) const;

  inline bool hasNaN() const;

  inline static bool isNaN(double x);
  
protected:
  double elt[3];
};

// === below is the implementation ===

inline Vec3d::Vec3d(double entry)
{
  elt[0] = entry;
  elt[1] = entry;
  elt[2] = entry;
}

inline Vec3d::Vec3d(const double * vec)
{
  elt[0] = vec[0];
  elt[1] = vec[1];
  elt[2] = vec[2];
}

inline Vec3d::Vec3d(const Vec3d & vec)
{
  elt[0] = vec.elt[0];
  elt[1] = vec.elt[1];
  elt[2] = vec.elt[2];
}

inline Vec3d & Vec3d::operator=(const Vec3d & source)
{
  elt[0] = source.elt[0];
  elt[1] = source.elt[1];
  elt[2] = source.elt[2];

  return *this;
}

inline bool Vec3d::operator==(const Vec3d & vec2) const
{
  return ((elt[0] == vec2[0]) &&
          (elt[1] == vec2[1]) &&
          (elt[2] == vec2[2]));
}

inline bool Vec3d::operator!=(const Vec3d & vec2) const
{
  return ((elt[0] != vec2[0]) ||
          (elt[1] != vec2[1]) ||
          (elt[2] != vec2[2]));
}

inline bool Vec3d::operator<(const Vec3d & vec2) const
{
  if(elt[0] < vec2[0]) 
    return true;
  if(elt[0] > vec2[0]) 
    return false;
  if(elt[1] < vec2[1]) 
    return true;
  if(elt[1] > vec2[1]) 
    return false;
  return elt[2] < vec2[2];
}

inline Vec3d operator* (double scalar, const Vec3d & vec2)
{
  Vec3d result = vec2;
  result.elt[0] *= scalar;
  result.elt[1] *= scalar;
  result.elt[2] *= scalar;

  return result;
}

inline Vec3d operator/ (double scalar, const Vec3d & vec2)
{
  Vec3d result = vec2;
  result.elt[0] /= scalar;
  result.elt[1] /= scalar;
  result.elt[2] /= scalar;

  return result;
}

inline Vec3d operator- (const Vec3d & vec1)
{
  Vec3d result = vec1;
  result.elt[0] *= -1.0;
  result.elt[1] *= -1.0;
  result.elt[2] *= -1.0;

  return result;
}

inline const Vec3d Vec3d::operator+ (const Vec3d & vec2) const
{
  Vec3d sum = *this;
  sum.elt[0] += vec2.elt[0];
  sum.elt[1] += vec2.elt[1];
  sum.elt[2] += vec2.elt[2];

  return sum;
}

inline Vec3d & Vec3d::operator+= (const Vec3d & vec2)
{
  elt[0] += vec2.elt[0];
  elt[1] += vec2.elt[1];
  elt[2] += vec2.elt[2];

  return *this;
}

inline const Vec3d Vec3d::operator- (const Vec3d & vec2) const
{
  Vec3d sum = *this;
  sum.elt[0] -= vec2.elt[0];
  sum.elt[1] -= vec2.elt[1];
  sum.elt[2] -= vec2.elt[2];

  return sum;
}

inline Vec3d & Vec3d::operator-= (const Vec3d & vec2)
{
  elt[0] -= vec2.elt[0];
  elt[1] -= vec2.elt[1];
  elt[2] -= vec2.elt[2];

  return *this;
}

inline double & Vec3d::operator[] (int index)
{
  return elt[index];
}

inline const double & Vec3d::operator[] (int index) const
{
  return elt[index];
}

inline double dot(const Vec3d & vec1, const Vec3d & vec2)
{
  return (vec1.elt[0] * vec2.elt[0] + vec1.elt[1] * vec2.elt[1] + vec1.elt[2] * vec2.elt[2]);
}

inline Vec3d cross(const Vec3d & vec1, const Vec3d & vec2)
{
  Vec3d result(vec1.elt[1] * vec2.elt[2] - vec2.elt[1] * vec1.elt[2],
              -vec1.elt[0] * vec2.elt[2] + vec2.elt[0] * vec1.elt[2],
               vec1.elt[0] * vec2.elt[1] - vec2.elt[0] * vec1.elt[1]);

  return result;
}

inline Vec3d norm(const Vec3d & vec1)
{
  double norm2 = dot(vec1,vec1);
  Vec3d result = vec1;
  result *= 1.0 / sqrt(norm2);
  
  return result;
}

inline Vec3d & Vec3d::operator*= (double scalar)
{
  elt[0] *= scalar;
  elt[1] *= scalar;
  elt[2] *= scalar;
  return *this;
}

inline const Vec3d Vec3d::operator* (double scalar) const
{
  return (Vec3d(elt[0] * scalar, elt[1] * scalar, elt[2] * scalar));
}

inline Vec3d Vec3d::operator/ (double scalar) const
{
  return (Vec3d(elt[0] / scalar, elt[1] / scalar, elt[2] / scalar));
}

inline Vec3d & Vec3d::operator/= (double scalar)
{
  elt[0] /= scalar;
  elt[1] /= scalar;
  elt[2] /= scalar;
  return *this;
}

inline double len(const Vec3d & vec1)
{
  return(sqrt(dot(vec1,vec1)));
}

inline double len2(const Vec3d & vec1)
{
  return(dot(vec1,vec1));
}

inline std::ostream &operator << (std::ostream &s, const Vec3d &v)
{
  double a = v[0];
  double b = v[1];
  double c = v[2];
  
  return(s << '[' << a << ' ' << b << ' ' << c << ']');
}

inline void Vec3d::convertToArray(double * vecArray) const
{
  vecArray[0] = elt[0];
  vecArray[1] = elt[1];
  vecArray[2] = elt[2];
}

inline void Vec3d::addToArray(double * vecArray) const
{
  vecArray[0] += elt[0];
  vecArray[1] += elt[1];
  vecArray[2] += elt[2];
}

inline void Vec3d::normalize()
{
  double invMag = 1.0 / sqrt(elt[0]*elt[0] + elt[1]*elt[1] + elt[2]*elt[2]);
  elt[0] *= invMag;
  elt[1] *= invMag;
  elt[2] *= invMag;
}

inline void Vec3d::print() const
{
  double a = elt[0];
  double b = elt[1];
  double c = elt[2];
  
  printf("[%G %G %G]\n", a, b, c);
}

inline void Vec3d::set(double x0, double x1, double x2) // assign vector [x0, x1, x2]
{
  elt[0] = x0;
  elt[1] = x1;
  elt[2] = x2;
}

inline void Vec3d::set(double value) // set all elements to value
{
  elt[0] = value;
  elt[1] = value;
  elt[2] = value;
}

inline bool Vec3d::hasNaN() const
{
  return (isNaN(elt[0]) || isNaN(elt[1]) || isNaN(elt[2]));
}

inline bool Vec3d::isNaN(double x) 
{ 
  #ifdef isnan
    return (isnan(x) != 0);
  #elif defined(_WIN32)
    return (_isnan(x) != 0);
  #else
    return (x != x); 
  #endif
}

#endif

