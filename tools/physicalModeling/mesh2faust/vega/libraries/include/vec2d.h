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
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  A simple class for vector algebra on 2D vectors 
  (summation, normalization, dot product, etc.).
*/

#ifndef _MINIVEC2D_H_
#define _MINIVEC2D_H_

#include <math.h>
#include <ostream>

class Vec2d {
public:

  inline Vec2d() {}
  inline Vec2d(double x, double y) { elt[0]=x; elt[1]=y; }
  inline Vec2d(const double v[2]) { elt[0]=v[0]; elt[1]=v[1]; }
  inline Vec2d(double entry); // // create a vector with all entries "entry" (can create zero vector for entry=0.0)

  inline Vec2d & operator=(const Vec2d & source);
  inline bool operator==(const Vec2d & vec2);

  inline Vec2d operator+ (const Vec2d & vec2);
  inline Vec2d & operator+= (const Vec2d & vec2);

  inline Vec2d operator- (const Vec2d & vec2);
  inline Vec2d & operator-= (const Vec2d & vec2);

  inline Vec2d operator* (double scalar) const;
  inline Vec2d & operator*= (double scalar);

  inline Vec2d operator/ (double scalar) const;
  inline Vec2d & operator/= (double scalar);

  friend inline Vec2d operator* (double scalar, const Vec2d & vec2);
  friend inline Vec2d operator/ (double scalar, const Vec2d & vec2);

  friend inline double dot(const Vec2d & vec1, const Vec2d & vec2); // dot product

  friend inline Vec2d norm(const Vec2d & vec1); // returns normalized vector (unit length)
  friend inline std::ostream &operator << (std::ostream &s, const Vec2d &v);

  friend class Mat3d;

  inline double & operator[] (int index); // v[i] returns i-th vector component
  inline const double & operator[] (int index) const;

protected:
  double elt[2];
};

// === below is the implementation ===

inline Vec2d::Vec2d(double entry)
{
  elt[0] = entry;
  elt[1] = entry;
}

inline Vec2d & Vec2d::operator=(const Vec2d & source)
{
  elt[0] = source.elt[0];
  elt[1] = source.elt[1];

  return *this;
}

inline bool Vec2d::operator==(const Vec2d & vec2)
{
  return ((elt[0] == vec2[0]) &&
          (elt[1] == vec2[1]));
}

inline Vec2d operator* (double scalar, const Vec2d & vec2)
{
  Vec2d result = vec2;
  result.elt[0] *= scalar;
  result.elt[1] *= scalar;

  return result;
}

inline Vec2d operator/ (double scalar, const Vec2d & vec2)
{
  Vec2d result = vec2;
  result.elt[0] /= scalar;
  result.elt[1] /= scalar;

  return result;
}

inline Vec2d Vec2d::operator+ (const Vec2d & vec2)
{
  Vec2d sum = *this;
  sum.elt[0] += vec2.elt[0];
  sum.elt[1] += vec2.elt[1];

  return sum;
}

inline Vec2d & Vec2d::operator+= (const Vec2d & vec2)
{
  elt[0] += vec2.elt[0];
  elt[1] += vec2.elt[1];

  return *this;
}

inline Vec2d Vec2d::operator- (const Vec2d & vec2)
{
  Vec2d sum = *this;
  sum.elt[0] -= vec2.elt[0];
  sum.elt[1] -= vec2.elt[1];

  return sum;
}

inline Vec2d & Vec2d::operator-= (const Vec2d & vec2)
{
  elt[0] -= vec2.elt[0];
  elt[1] -= vec2.elt[1];

  return *this;
}

inline double & Vec2d::operator[] (int index)
{
  return elt[index];
}

inline const double & Vec2d::operator[] (int index) const
{
  return elt[index];
}

inline double dot(const Vec2d & vec1, const Vec2d & vec2)
{
  return (vec1.elt[0] * vec2.elt[0] + vec1.elt[1] * vec2.elt[1]);
}

inline Vec2d norm(const Vec2d & vec1)
{
  double norm2 = dot(vec1,vec1);
  Vec2d result = vec1;
  result *= 1.0 / sqrt(norm2);
  
  return result;
}

inline Vec2d & Vec2d::operator*= (double scalar)
{
  elt[0] *= scalar;
  elt[1] *= scalar;
  return *this;
}

inline Vec2d Vec2d::operator* (double scalar) const
{
  return (Vec2d(elt[0]*scalar,elt[1]*scalar));
}

inline Vec2d Vec2d::operator/ (double scalar) const
{
  return (Vec2d(elt[0]/scalar,elt[1]/scalar));
}

inline Vec2d & Vec2d::operator/= (double scalar)
{
  elt[0] /= scalar;
  elt[1] /= scalar;
  return *this;
}

inline double len(const Vec2d & vec1)
{
  return(sqrt(dot(vec1,vec1)));
}

inline std::ostream &operator << (std::ostream &s, const Vec2d &v)
{
  double a = v[0];
  double b = v[1];
  
  return(s << '[' << a << ' ' << b << ']');
}

#endif

