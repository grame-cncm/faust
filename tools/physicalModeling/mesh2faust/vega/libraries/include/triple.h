/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "triple" include file, Copyright (C) 2007 CMU, 2009 MIT, 2016 USC     *
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

#ifndef _TRIPLE_H_
#define _TRIPLE_H_

// "triple" template, inspired by the STL pair template

template <class A, class B, class C>
class triple
{
public:
  // constructors
  triple() : first(A()), second(B()), third(C()) {}
  triple(const A & first_, const B & second_, const C & third_) : first(first_), second(second_), third(third_) {}

  // copy constructor 
  triple(const triple & x) : first(x.first), second(x.second), third(x.third) {}

  // operators
  inline triple & operator= (const triple & x) { first = x.first; second = x.second; third = x.third; return *this; }
  inline bool operator== (const triple & x) const { return ((first == x.first) && (second == x.second) && (third == x.third)); }
  inline bool operator!= (const triple & x) const { return ((first != x.first) || (second != x.second) || (third != x.third)); }
  bool operator< (const triple & x) const
  {
    // compare first entry:
    if (first < x.first)
      return true;
    if (x.first < first)
      return false;

    // first equals x.first; must compare second entry:
    if (second < x.second)
      return true;
    if (x.second < second)
      return false;

    // first equals x.first, AND second equals x.second; must compare third entry:
    return (third < x.third);
  }

  A first;
  B second;
  C third;
};

// makes a triple
template <class A, class B, class C>
triple<A,B,C> make_triple(const A & first, const B & second, const C & third) { return triple<A,B,C>(first, second, third); }

#endif

