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


#ifndef INTEGER_H
#define INTEGER_H
#include <exception>
#include <string>
#include <cassert>
#include <cstring>

template <int N> class Rational;

class IntegerException : public std::exception
{
public:
  IntegerException(const char * reason);
  IntegerException(const std::string & reason);
  virtual ~IntegerException() throw();
  virtual const char * what() const throw();

protected:
  std::string r;
};

// N is the number of 32-bit words you want per Integer.
template <int N>
class Integer
{
public:
	
  // Construction and destruction.
  Integer (int i = 0);
  Integer (const Integer& value);
  ~Integer ();

  // Assignment.
  Integer& operator= (const Integer& value);

  // Comparison.
  bool operator== (const Integer& value) const;
  bool operator!= (const Integer& value) const;
  bool operator<  (const Integer& value) const;
  bool operator<= (const Integer& value) const;
  bool operator>  (const Integer& value) const;
  bool operator>= (const Integer& value) const;

  // Arithmetic operations.
  Integer operator- () const;
  Integer operator+ (const Integer& value) const;
  Integer operator- (const Integer& value) const;
  Integer operator* (const Integer& value) const;
  Integer operator/ (const Integer& value) const;
  Integer operator% (const Integer& value) const;

  // Arithmetic updates.
  Integer& operator+= (const Integer& value);
  Integer& operator-= (const Integer& value);
  Integer& operator*= (const Integer& value);
  Integer& operator/= (const Integer& value);

  // Shift operations.
  Integer operator<< (int shift) const;
  Integer operator>> (int shift) const;

  // Shift updates.
  Integer& operator<<= (int shift);
  Integer& operator>>= (int shift);

  private:
	
	typedef IntegerException Exception;
  // Support for comparisons.  The return value of compare is
  //   -1 when value0 < value1,
  //    0 when value0 == value1,
  //   +1 when value0 > value1.
  static int compare (const Integer& value0, const Integer& value1);
  int getSign () const;

  // Support for division and modulo.
  static bool GetDivMod (const Integer& numer, const Integer& denom,
      Integer& quotient, Integer& remainder);

  static void divSingle (const Integer& numer, short denom,
      Integer& quotient, Integer& remainder);

  static void divMultiple (const Integer& numer, const Integer& denom,
      Integer& quotient, Integer& remainder);

  // Miscellaneous utilities.
  int getLeadingBlock () const;
  int getTrailingBlock () const;
  int getLeadingBit (int i) const;  // of buffer[i]
  int getTrailingBit (int i) const;  // of buffer[i]
  int getLeadingBit () const;  // of entire number
  int getTrailingBit () const;  // of entire number
  void setBit (int i, bool on);
  bool getBit (int i) const;
  unsigned int toUnsignedInt (int i) const;
  void fromUnsignedInt (int i, unsigned int value);
  unsigned int toUnsignedInt (int lo, int hi) const;
  int toInt (int i) const;

  enum
  {
    INT_SIZE = 2*N,
    INT_BYTES = INT_SIZE*sizeof(short),
    INT_LAST = INT_SIZE - 1
  };

  short buffer[INT_SIZE];

  // Rational needs access to private members of Integer.
  friend class Rational<N>;
};

template <int N>
Integer<N> operator* (int i, const Integer<N>& value);





//----------------------------------------------------------------------------
template <int N>
Integer<N>::Integer (int i)
{
  if (i >= 0)
  {
    memset(buffer, 0, INT_BYTES);
  }
  else
  {
    memset(buffer, 0xFF, INT_BYTES);
  }
  memcpy(buffer, &i, sizeof(int));

#ifdef WM5_BIG_ENDIAN
  short save = buffer[0];
  buffer[0] = buffer[1];
  buffer[1] = save;
#endif
}
//----------------------------------------------------------------------------
template <int N>
Integer<N>::Integer (const Integer& value)
{
  memcpy(buffer, value.buffer, INT_BYTES);
}
//----------------------------------------------------------------------------
template <int N>
Integer<N>::~Integer ()
{
}
//----------------------------------------------------------------------------
template <int N>
Integer<N>& Integer<N>::operator= (const Integer& value)
{
  memcpy(buffer, value.buffer, INT_BYTES);
  return *this;
}
//----------------------------------------------------------------------------
template <int N>
int Integer<N>::getSign () const
{
  return (buffer[INT_LAST] & 0x8000) ? -1 : +1;
}
//----------------------------------------------------------------------------
template <int N>
bool Integer<N>::operator== (const Integer& value) const
{
  return compare(*this, value) == 0;
}
//----------------------------------------------------------------------------
template <int N>
bool Integer<N>::operator!= (const Integer& value) const
{
  return compare(*this, value) != 0;
}
//----------------------------------------------------------------------------
template <int N>
bool Integer<N>::operator< (const Integer& value) const
{
  int s0 = getSign();
  int s1 = value.getSign();
  if (s0 > 0)
  {
    if (s1 > 0)
    {
      return compare(*this, value) < 0;
    }
    else
    {
      return false;
    }
  }
  else
  {
    if (s1 > 0)
    {
      return true;
    }
    else
    {
      return compare(*this, value) < 0;
    }
  }
}
//----------------------------------------------------------------------------
template <int N>
bool Integer<N>::operator<= (const Integer& value) const
{
  int s0 = getSign();
  int s1 = value.getSign();
  if (s0 > 0)
  {
    if (s1 > 0)
    {
      return compare(*this, value) <= 0;
    }
    else
    {
      return false;
    }
  }
  else
  {
    if (s1 > 0)
    {
      return true;
    }
    else
    {
      return compare(*this, value) <= 0;
    }
  }
}
//----------------------------------------------------------------------------
template <int N>
bool Integer<N>::operator> (const Integer& value) const
{
  int s0 = getSign();
  int s1 = value.getSign();
  if (s0 > 0)
  {
    if (s1 > 0)
    {
      return compare(*this, value) > 0;
    }
    else
    {
      return true;
    }
  }
  else
  {
    if (s1 > 0)
    {
      return false;
    }
    else
    {
      return compare(*this, value) > 0;
    }
  }
}
//----------------------------------------------------------------------------
template <int N>
bool Integer<N>::operator>= (const Integer& value) const
{
  int s0 = getSign();
  int s1 = value.getSign();
  if (s0 > 0)
  {
    if (s1 > 0)
    {
      return compare(*this, value) >= 0;
    }
    else
    {
      return true;
    }
  }
  else
  {
    if (s1 > 0)
    {
      return false;
    }
    else
    {
      return compare(*this, value) >= 0;
    }
  }
}
//----------------------------------------------------------------------------
template <int N>
int Integer<N>::compare (const Integer<N>& value0, const Integer<N>& value1)
{
  for(int i = INT_LAST; i >= 0; --i)
  {
    unsigned int uiValue0 = (unsigned int)value0.buffer[i];
    unsigned int uiValue1 = (unsigned int)value1.buffer[i];
    if (uiValue0 < uiValue1)
    {
      return -1;
    }
    else if (uiValue0 > uiValue1)
    {
      return +1;
    }
  }
  return 0;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N> Integer<N>::operator- () const
{
  Integer result = *this;

  // Negate the bits.
  int i;
  for(i = 0; i < INT_SIZE; ++i)
  {
    result.buffer[i] = ~result.buffer[i];
  }

  // Add 1 (place in carry bit and add zero to 'result').
  unsigned int carry = 1;
  for(i = 0; i < INT_SIZE; ++i)
  {
    unsigned int b1 = result.toUnsignedInt(i);
    unsigned int sum = b1 + carry;
    result.fromUnsignedInt(i, sum);
    carry = (sum & 0x00010000) ? 1 : 0;
  }

  // Test for overflow.
  if (result.getSign() == getSign())
  {
    if (result != 0) throw Exception("Integer overflow in Integer<N>::operator-");
  }

  return result;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N> Integer<N>::operator+ (const Integer& value) const
{
  Integer result;

  unsigned int carry = 0;
  for(int i = 0; i < INT_SIZE; ++i)
  {
    unsigned int b0 = toUnsignedInt(i);
    unsigned int b1 = value.toUnsignedInt(i);
    unsigned int sum = b0 + b1 + carry;
    result.fromUnsignedInt(i, sum);
    carry = (sum & 0x00010000) ? 1 : 0;
  }

  // Test for overflow.
  if (getSign() == value.getSign())
  {
    if (result.getSign() != getSign()) throw Exception("Integer overflow in Integer<N>::operator+");
  }

  return result;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N> Integer<N>::operator- (const Integer& value) const
{
  return *this + (-value);
}
//----------------------------------------------------------------------------
template <int N>
Integer<N> Integer<N>::operator* (const Integer& value) const
{
  int s0 = getSign();
  int s1 = value.getSign();
  int sProduct = s0*s1;
  Integer op0 = (s0 > 0 ? *this : -*this);
  Integer op1 = (s1 > 0 ? value : -value);

  // Product of single-digit number with multiple-digit number.
  unsigned short product[2*INT_SIZE];
  unsigned short* pCurrent = product;

  // Product of the two multiple-digit operands.
  unsigned short result[2*INT_SIZE];
  unsigned short* rCurrent = result;
  memset(result,0,2*INT_BYTES);

  for(int i0 = 0, size = 2*INT_SIZE; i0 < INT_SIZE; ++i0, --size)
  {
    unsigned int b0 = op0.toUnsignedInt(i0);
    if (b0 > 0)
    {
      unsigned short* pBuffer = pCurrent;
      unsigned int carry = 0;
      int i1;
      for(i1 = 0; i1 < INT_SIZE; ++i1)
      {
        unsigned int b1 = op1.toUnsignedInt(i1);
        unsigned int prod = b0*b1 + carry;
        *pBuffer++ = (unsigned short)(prod & 0x0000FFFF);
        carry = (prod & 0xFFFF0000) >> 16;
      }
      *pBuffer = (unsigned short)carry;

      unsigned short* rBuffer = rCurrent;
      pBuffer = pCurrent;
      carry = 0;
      unsigned int sum, term0, term1;
      for(i1 = 0; i1 <= INT_SIZE; ++i1)
      {
        term0 = (unsigned int)(*pBuffer++);
        term1 = (unsigned int)(*rBuffer);
        sum = term0 + term1 + carry;
        *rBuffer++ = (unsigned short)(sum & 0x0000FFFF);
        carry = (sum & 0x00010000) ? 1 : 0;
      }

      for(/**/; carry > 0 && i1 < size; i1++)
      {
        term0 = (unsigned int)(*rBuffer);
        sum = term0 + carry;
        *rBuffer++ = (unsigned short)(sum & 0x0000FFFF);
        carry = (sum & 0x00010000) ? 1 : 0;
      }
    }

    pCurrent++;
    rCurrent++;
  }

  // Test for overflow.  You can test earlier inside the previous loop, but
  // testing here allows you to get an idea of how much overflow there is.
  // This information might be useful for an application to decide how large
  // to choose the integer size.
  for(int i = 2*INT_SIZE-1; i >= INT_SIZE; --i)
  {
    if (result[i] != 0) throw Exception("Integer overflow in Integer<N>::operator*");
  }
  if ((result[INT_LAST] & 0x8000) != 0) throw Exception("Integer overflow in Integer<N>::operator*");

  Integer intResult;
  memcpy(intResult.buffer, result, INT_BYTES);
  if (sProduct < 0)
  {
    intResult = -intResult;
  }

  return intResult;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N> operator* (int i, const Integer<N>& value)
{
  return value*i;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N> Integer<N>::operator/ (const Integer& value) const
{
  // TO DO.  On division by zero, return INVALID or signed INFINITY?
  Integer quotient, remainder;
  return GetDivMod(*this, value, quotient, remainder) ? quotient : 0;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N> Integer<N>::operator% (const Integer& value) const
{
  // TO DO.  On division by zero, return INVALID or signed INFINITY?
  Integer quotient, remainder;
  return GetDivMod(*this, value, quotient, remainder) ? remainder : 0;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N>& Integer<N>::operator+= (const Integer& value)
{
  *this = *this + value;
  return *this;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N>& Integer<N>::operator-= (const Integer& value)
{
  *this = *this - value;
  return *this;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N>& Integer<N>::operator*= (const Integer& value)
{
  *this = *this * value;
  return *this;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N>& Integer<N>::operator/= (const Integer& value)
{
  *this = *this / value;
  return *this;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N> Integer<N>::operator<< (int shift) const
{
  if (shift < 0)
  {
    return 0;
  }
  if (shift == 0)
  {
    return *this;
  }

  // Number of 16-bit blocks to shift.
  Integer result;
  int blocks = shift/16;
  if (blocks > INT_LAST)
  {
    return 0;
  }

  int i;
  if (blocks > 0)
  {
    int j = INT_LAST - blocks;
    for(i = INT_LAST; j >= 0; --i, --j)
    {
      result.buffer[i] = buffer[j];
    }

    for(/**/; i >= 0; --i)
    {
      result.buffer[i] = 0;
    }
  }

  // Number of left-over bits to shift.
  int bits = shift % 16;
  if (bits > 0)
  {
    unsigned int lo, hi, value;
    int iM1;
    for(i = INT_LAST, iM1 = i - 1; iM1 >= 0; --i, --iM1)
    {
      lo = toUnsignedInt(iM1);
      hi = toUnsignedInt(i);
      value = (lo | (hi << 16));
      value <<= bits;
      result.fromUnsignedInt(i, ((0xFFFF0000 & value) >> 16));
    }

    value = toUnsignedInt(0);
    value <<= bits;
    result.fromUnsignedInt(0, (0x0000FFFF & value));
  }

  return result;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N> Integer<N>::operator>> (int shift) const
{
  if (shift < 0)
  {
    return 0;
  }
  if (shift == 0)
  {
    return *this;
  }

  // Number of 16-bit blocks to shift.
  Integer result;
  int blocks = shift/16;
  if (blocks > INT_LAST)
  {
    return 0;
  }

  int i;
  if (blocks > 0)
  {
    int j = blocks;
    for(i = 0; j <= INT_LAST; ++i, ++j)
    {
      result.buffer[i] = buffer[j];
    }

    if (getSign() > 0)
    {
      for(/**/; i <= INT_LAST; ++i)
      {
        result.buffer[i] = 0;
      }
    }
    else
    {
      for(/**/; i <= INT_LAST; ++i)
      {
        result.buffer[i] = (short)(0x0000FFFFu);
      }
    }
  }

  // Number of left-over bits to shift.
  int bits = shift % 16;
  if (bits > 0)
  {
    unsigned int value;
    int p1;
    for(i = 0, p1 = 1; p1 <= INT_LAST; ++i, ++p1)
    {
      value = toUnsignedInt(i, p1);
      value >>= bits;
      result.fromUnsignedInt(i, value);
    }

    value = toUnsignedInt(INT_LAST);
    if (getSign() < 0)
    {
      value |= 0xFFFF0000;  // sign extension
    }
    value >>= bits;
    result.fromUnsignedInt(INT_LAST, value);
  }

  return result;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N>& Integer<N>::operator<<= (int shift)
{
  if (shift <= 0)
  {
    return *this;
  }

  // Number of 16-bit blocks to shift.
  int blocks = shift/16;
  if (blocks > INT_LAST)
  {
    return *this;
  }

  int i;
  if (blocks > 0)
  {
    int j = INT_LAST - blocks;
    for(i = INT_LAST; j >= 0; --i, --j)
    {
      buffer[i] = buffer[j];
    }

    for(/**/; i >= 0; --i)
    {
      buffer[i] = 0;
    }
  }

  // Number of left-over bits to shift.
  int bits = shift % 16;
  if (bits > 0)
  {
    unsigned int value;
    int m1;
    for(i = INT_LAST, m1 = i-1; m1 >= 0; i--, m1--)
    {
      value = toUnsignedInt(m1, i);
      value <<= bits;
      fromUnsignedInt(i, ((0xFFFF0000 & value) >> 16));
    }

    value = toUnsignedInt(0);
    value <<= bits;
    fromUnsignedInt(0, (0x0000FFFF & value));
  }

  return *this;
}
//----------------------------------------------------------------------------
template <int N>
Integer<N>& Integer<N>::operator>>= (int shift)
{
  if (shift <= 0)
  {
    return *this;
  }

  // Number of 16-bit blocks to shift.
  int blocks = shift/16;
  if (blocks > INT_LAST)
  {
    return *this;
  }

  int i;
  if (blocks > 0)
  {
    int j = blocks;
    for(i = 0, j = blocks; j <= INT_LAST; ++i, ++j)
    {
      buffer[i] = buffer[j];
    }

    if (getSign() > 0)
    {
      for(/**/; i <= INT_LAST; ++i)
      {
        buffer[i] = 0;
      }
    }
    else
    {
      for(/**/; i <= INT_LAST; ++i)
      {
        buffer[i] = -1;
      }
    }
  }

  // Number of left-over bits to shift.
  int bits = shift % 16;
  if (bits > 0)
  {
    unsigned int value;
    int p1;
    for(i = 0, p1 = 1; p1 <= INT_LAST; ++i, ++p1)
    {
      value = toUnsignedInt(i, p1);
      value >>= bits;
      fromUnsignedInt(i, value);
    }

    value = toUnsignedInt(INT_LAST);
    if (getSign() < 0)
    {
      value |= 0xFFFF0000;  // sign extension
    }
    value >>= bits;
    fromUnsignedInt(INT_LAST, value);
  }

  return *this;
}
//----------------------------------------------------------------------------
template <int N>
bool Integer<N>::GetDivMod (const Integer& numer, const Integer& denom,
    Integer& quotient, Integer& remainder)
{
  if (denom == 0)
  {
    throw Exception("Division by zero in Integer<N>::GetDivMod");
    quotient = 0;
    remainder = 0;
    return false;
  }

  if (numer == 0)
  {
    quotient = 0;
    remainder = 0;
    return true;
  }

  // Work with the absolute values of the numerator and denominator.
  int s0 = numer.getSign();
  int s1 = denom.getSign();
  Integer absNumer = s0*numer;
  Integer absDenom = s1*denom;

  int comp = compare(absNumer, absDenom);
  if (comp < 0)
  {
    // numerator < denominator:  numerator = 0*denominator + numerator
    quotient = 0;
    remainder = numer;
    return true;
  }

  if (comp == 0)
  {
    // numerator == denominator:  numerator = 1*denominator + 0
    quotient = 1;
    remainder = 0;
    return true;
  }

  // numerator > denominator, do the division to find quotient and remainder
  if (absDenom > 0x0000FFFF)
  {
    divMultiple(absNumer, absDenom, quotient, remainder);
  }
  else
  {
    divSingle(absNumer, absDenom.buffer[0], quotient, remainder);
  }

  // Apply the original signs of numerator and denominator.
  quotient *= s0*s1;
  remainder *= s0;

#ifdef _DEBUG
  Integer test = numer - denom*quotient - remainder;
  assertion(test == 0, "Invalid result\n");
#endif
  return true;
    }
//----------------------------------------------------------------------------
template <int N>
void Integer<N>::divSingle (const Integer& numer, short denom,
    Integer& quotient, Integer& remainder)
{
  // The denominator is a single "digit".
  unsigned int uiDenom = 0x0000FFFF & (unsigned int)denom;

  // Get the numerator.
  int nStart = numer.getLeadingBlock();
  const short* nubuffer = &numer.buffer[nStart];
  unsigned int digit1 = 0;

  // Get the quotient.
  short* quoBuffer = &quotient.buffer[nStart];
  quotient = 0;
  int lastNonZero = -1;
  for(int i = nStart; i >= 0; --i, --nubuffer, --quoBuffer)
  {
    unsigned int digitB = digit1;
    digit1 = 0x0000FFFF & (unsigned int)(*nubuffer);
    unsigned int uiNumer = (digitB << 16) | digit1;
    unsigned int uiQuotient = uiNumer/uiDenom;
    digit1 = uiNumer - uiQuotient*uiDenom;
    *quoBuffer = (short)(uiQuotient & 0x0000FFFF);
    if (lastNonZero == -1 && uiQuotient > 0)
    {
      lastNonZero = i;
    }
  }
  if (lastNonZero < 0)
    throw Exception("Unexpected result in Integer<N>::divSingle");

  // Get the remainder.
  remainder = 0;
  if (digit1 & 0xFFFF0000)
  {
    memcpy(remainder.buffer, &digit1, 2*sizeof(short));
#ifdef WM5_BIG_ENDIAN
    short save = remainder.buffer[0];
    remainder.buffer[0] = remainder.buffer[1];
    remainder.buffer[1] = save;
#endif
  }
  else
  {
    unsigned short tmp = (unsigned short)digit1;
    memcpy(remainder.buffer, &tmp, sizeof(short));
  }
    }
//----------------------------------------------------------------------------
template <int N>
void Integer<N>::divMultiple (const Integer& numer,
    const Integer& denom, Integer& quotient, Integer& remainder)
{
  quotient = 0;
  remainder = 0;

  // Normalization to allow good estimate of quotient.  TO DO:  It is
  // possible that the numerator is large enough that normalization causes
  // overflow when computing the product adjust*numer; an assertion will
  // fire in this case.  Ideally, the overflow would be allowed and the
  // digit in the overflow position becomes the first digit of the numerator
  // in the division algorithm.  This will require a mixture of Integer<N>
  // and Integer<N+1>, though.
  int dInit = denom.getLeadingBlock();
  int leadingDigit = denom.toInt(dInit);
  int adjust = 0x10000/(leadingDigit + 1);
  Integer adjNum = adjust*numer;
  Integer adjDen = adjust*denom;
  if (adjDen.getLeadingBlock() != dInit)
    throw Exception("Unexpected result in Integer<N>::divMultiple");

  // Get first two "digits" of denominator.
  unsigned int d1 = adjDen.toUnsignedInt(dInit);
  unsigned int d2 = adjDen.toUnsignedInt(dInit - 1);

  // Determine the maximum necessary division steps.
  int nInit = adjNum.getLeadingBlock();
  if (nInit < dInit)
    throw Exception("Unexpected result in Integer<N>::divMultiple");

  int qInit;
  unsigned int rHat;
  if (nInit != dInit)
  {
    qInit = nInit - dInit - 1;
    rHat = 1;
  }
  else
  {
    qInit = 0;
    rHat = 0;
  }

  for(/**/; qInit >= 0; --qInit)
  {
    // Get first three indices of remainder.
    unsigned int n0, n1, n2;
    if (rHat > 0)
    {
      n0 = adjNum.toUnsignedInt(nInit--);
      n1 = adjNum.toUnsignedInt(nInit--);
      n2 = adjNum.toUnsignedInt(nInit);
    }
    else
    {
      n0 = 0;
      n1 = adjNum.toUnsignedInt(nInit--);
      n2 = adjNum.toUnsignedInt(nInit);
    }

    // Estimate the quotient.
    unsigned int tmp = (n0 << 16) | n1;
    unsigned int qHat = (n0 != d1 ? tmp/d1 : 0x0000FFFF);
    unsigned int prod = qHat*d1;
    if (tmp < prod)
      throw Exception("Unexpected result in Integer<N>::divMultiple");

    rHat = tmp - prod;
    if (d2*qHat > 0x10000*rHat + n2)
    {
      qHat--;
      rHat += d1;
      if (d2*qHat > 0x10000*rHat + n2)
      {
        // If this block is entered, we have exactly the quotient for
        // the division.  The adjustment block of code later cannot
        // happen.
        qHat--;
        rHat += d1;
      }
    }

    // Compute the quotient for this step of the division.
    Integer localQuo;
    localQuo.fromUnsignedInt(qInit, qHat);

    // Compute the remainder.
    Integer product = localQuo*adjDen;
    adjNum -= product;
    if (adjNum < 0)
    {
      qHat--;
      adjNum += adjDen;
      if (adjNum < 0)
        throw Exception("Unexpected result in Integer<N>::divMultiple");
//      assertion(adjNum >= 0, "Unexpected result\n");
    }

    // Set quotient digit.
    quotient.fromUnsignedInt(qInit, qHat);

    if (adjNum >= adjDen)
    {
      // Prepare to do another division step.
      nInit = adjNum.getLeadingBlock();
    }
    else
    {
      // Remainder is smaller than divisor, finished dividing.
      break;
    }
  }

  // Unnormalize the remainder.
  if (adjNum > 0)
  {
    short divisor = (short)(adjust & 0x0000FFFF);
    Integer shouldBeZero;
    divSingle(adjNum, divisor, remainder, shouldBeZero);
  }
  else
  {
    remainder = 0;
  }
    }
//----------------------------------------------------------------------------
template <int N>
int Integer<N>::getLeadingBlock () const
{
  for(int i = INT_LAST; i >= 0; --i)
  {
    if (buffer[i] != 0)
    {
      return i;
    }
  }
  return -1;
}
//----------------------------------------------------------------------------
template <int N>
int Integer<N>::getTrailingBlock () const
{
  for(int i = 0; i <= INT_LAST; ++i)
  {
    if (buffer[i] != 0)
    {
      return i;
    }
  }
  return -1;
}
//----------------------------------------------------------------------------
template <int N>
int Integer<N>::getLeadingBit (int i) const
{
  assert(0 <= i && i <= INT_LAST);
  if (i < 0 || i > INT_LAST)
  {
    return -1;
  }

  // This is a binary search for the high-order bit of buffer[i].  The
  // return value is the index into the bits (0 <= index < 16).
  int value = (int)buffer[i];
  if ((value & 0xFF00) != 0)
  {
    if ((value & 0xF000) != 0)
    {
      if ((value & 0xC000) != 0)
      {
        if ((value & 0x8000) != 0)
        {
          return 15;
        }
        else // (value & 0x4000) != 0
            {
          return 14;
            }
      }
      else  // (value & 0x3000) != 0
      {
        if ((value & 0x2000) != 0)
        {
          return 13;
        }
        else  // (value & 0x1000) != 0
        {
          return 12;
        }
      }
    }
    else  // (value & 0x0F00) != 0
    {
      if ((value & 0x0C00) != 0)
      {
        if ((value & 0x0800) != 0)
        {
          return 11;
        }
        else  // (value & 0x0400) != 0
            {
          return 10;
            }
      }
      else  // (value & 0x0300) != 0
      {
        if ((value & 0x0200) != 0)
        {
          return 9;
        }
        else  // (value & 0x0100) != 0
        {
          return 8;
        }
      }
    }
  }
  else  // (value & 0x00FF)
  {
    if ((value & 0x00F0) != 0)
    {
      if ((value & 0x00C0) != 0)
      {
        if ((value & 0x0080) != 0)
        {
          return 7;
        }
        else  // (value & 0x0040) != 0
            {
          return 6;
            }
      }
      else  // (value & 0x0030) != 0
      {
        if ((value & 0x0020) != 0)
        {
          return 5;
        }
        else  // (value & 0x0010) != 0
        {
          return 4;
        }
      }
    }
    else  // (value & 0x000F) != 0
    {
      if ((value & 0x000C) != 0)
      {
        if ((value & 0x0008) != 0)
        {
          return 3;
        }
        else  // (value & 0x0004) != 0
            {
          return 2;
            }
      }
      else  // (value & 0x0003) != 0
      {
        if ((value & 0x0002) != 0)
        {
          return 1;
        }
        else  // (value & 0x0001) != 0
        {
          return 0;
        }
      }
    }
  }
}
//----------------------------------------------------------------------------
template <int N>
int Integer<N>::getTrailingBit (int i) const
{
  assert(0 <= i && i <= INT_LAST);
  if (i < 0 || i > INT_LAST)
  {
    return -1;
  }

  // This is a binary search for the low-order bit of buffer[i].  The
  // return value is the index into the bits (0 <= index < 16).
  int value = (int)buffer[i];
  if ((value & 0x00FF) != 0)
  {
    if ((value & 0x000F) != 0)
    {
      if ((value & 0x0003) != 0)
      {
        if ((value & 0x0001) != 0)
        {
          return 0;
        }
        else // (value & 0x0002) != 0
            {
          return 1;
            }
      }
      else  // (value & 0x000C) != 0
      {
        if ((value & 0x0004) != 0)
        {
          return 2;
        }
        else  // (value & 0x0080) != 0
        {
          return 3;
        }
      }
    }
    else  // (value & 0x00F0) != 0
    {
      if ((value & 0x0030) != 0)
      {
        if ((value & 0x0010) != 0)
        {
          return 4;
        }
        else  // (value & 0x0020) != 0
            {
          return 5;
            }
      }
      else  // (value & 0x00C0) != 0
      {
        if ((value & 0x0040) != 0)
        {
          return 6;
        }
        else  // (value & 0x0080) != 0
        {
          return 7;
        }
      }
    }
  }
  else  // (value & 0xFF00)
  {
    if ((value & 0x0F00) != 0)
    {
      if ((value & 0x0300) != 0)
      {
        if ((value & 0x0100) != 0)
        {
          return 8;
        }
        else  // (value & 0x0200) != 0
            {
          return 9;
            }
      }
      else  // (value & 0x0C00) != 0
      {
        if ((value & 0x0400) != 0)
        {
          return 10;
        }
        else  // (value & 0x0800) != 0
        {
          return 11;
        }
      }
    }
    else  // (value & 0xF000) != 0
    {
      if ((value & 0x3000) != 0)
      {
        if ((value & 0x1000) != 0)
        {
          return 12;
        }
        else  // (value & 0x2000) != 0
            {
          return 13;
            }
      }
      else  // (value & 0xC000) != 0
      {
        if ((value & 0x4000) != 0)
        {
          return 14;
        }
        else  // (value & 0x8000) != 0
        {
          return 15;
        }
      }
    }
  }
}
//----------------------------------------------------------------------------
template <int N>
int Integer<N>::getLeadingBit () const
{
  int block = getLeadingBlock();
  if (block >= 0)
  {
    int bit = getLeadingBit(block);
    if (bit >= 0)
    {
      return bit + 16*block;
    }
  }

  return -1;
}
//----------------------------------------------------------------------------
template <int N>
int Integer<N>::getTrailingBit () const
{
  int block = getTrailingBlock();
  if (block >= 0)
  {
    int bit = getTrailingBit(block);
    if (bit >= 0)
    {
      return bit + 16*block;
    }
  }

  return -1;
}
//----------------------------------------------------------------------------
template <int N>
void Integer<N>::setBit (int i, bool on)
{
  // assert(0 <= i && i <= INT_LAST);
  int block = i/16;
  int bit = i % 16;
  if (on)
  {
    buffer[block] |= (1 << bit);
  }
  else
  {
    buffer[block] &= ~(1 << bit);
  }
}
//----------------------------------------------------------------------------
template <int N>
bool Integer<N>::getBit (int i) const
{
  // assert(0 <= i && i <= INT_LAST);
  int block = i/16;
  int bit = i % 16;
  return (buffer[block] & (1 << bit)) != 0;
}
//----------------------------------------------------------------------------
template <int N>
unsigned int Integer<N>::toUnsignedInt (int i) const
{
  // assert(0 <= i && i <= INT_LAST);
  return 0x0000FFFF & (unsigned int)buffer[i];
}
//----------------------------------------------------------------------------
template <int N>
void Integer<N>::fromUnsignedInt (int i, unsigned int value)
{
  // assert(0 <= i && i <= INT_LAST);
  buffer[i] = (short)(value & 0x0000FFFF);
}
//----------------------------------------------------------------------------
template <int N>
unsigned int Integer<N>::toUnsignedInt (int lo, int hi) const
{
  unsigned int uiLo = toUnsignedInt(lo);
  unsigned int uiHi = toUnsignedInt(hi);
  return (uiLo | (uiHi << 16));
}
//----------------------------------------------------------------------------
template <int N>
int Integer<N>::toInt (int i) const
{
  // assert(0 <= i && i <= INT_LAST);
  return (int)(0x0000FFFF & (unsigned int)buffer[i]);
}
//----------------------------------------------------------------------------
#endif
