/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _SigType_
#define _SigType_

#include <iostream>
#include <vector>
#include "garbageable.hh"
#include "interval.hh"
#include "smartpointer.hh"
#include "tree.hh"

/*********************************************************************
 *
 *                        Type System for FAUST
 *
 *    <type>          ::= <simpletype> || table(<type>) || <type>|<type> || <type>*<type>
 *    <simpletype>    ::= <nature><variability><computability><vectorability>||<boolean>
 *    <nature>        ::= TINT || TREAL
 *    <variability>   ::= TKONST || TBLOCK || TSAMP
 *    <computability> ::= TCOMP  || TINIT  || TEXEC
 *    <vectorability> ::= KVECT  || KSCAL  || KTRUESCAL
 *    <boolean>       ::= KNUM   || KBOOL
 *
 **********************************************************************/

//--------------------------------------------------
// simple types quality

// kAny is a kind of 'wildcard' type and is only used with ffunction (no signal with never have this
// type). Therefore kAny is not supposed to be used with a | operation, so kAny = 2 coding can be
// used.

enum Nature {
    kInt  = 0,
    kReal = 1,
    kAny  = 2
};  ///< nature : integer, floating point or 'any' values
enum Boolean {
    kNum  = 0,
    kBool = 1
};  ///< boolean : when a signal stands for a boolean value (while being of c-type int or float)
enum Variability { kKonst = 0, kBlock = 1, kSamp = 3 };  ///< variability : how fast values change
enum Computability {
    kComp = 0,
    kInit = 1,
    kExec = 3
};  ///< computability : when values are available
enum Vectorability {
    kVect     = 0,
    kScal     = 1,
    kTrueScal = 3 /*, kIndex = 4*/
};  ///< vectorability: when a signal can be vectorized (actually, only kVect and kScal matter;
    ///< kTrueScal and kIndex don't denote types but are here to simplify code generation)

/*---------------------------------------------------------------------

    AbstractType :
    The root class of the audio type hierarchy (SimpleType is the concrete citizen)

    Type :
    A smartPointer to type

----------------------------------------------------------------------*/

class AudioType;

typedef P<AudioType>             Type;
typedef const std::vector<Type>& ConstTypes;

/**
 * The Root class for all audio data types.
 * All audio types have a "variability" (how fast the values change) and
 * a "computability" (when the values are available). Simple types have
 * also a "nature" (integer or floating point).
 */

class AudioType : public virtual Garbageable {
   protected:
    int           fNature;         ///< The kind of data represented
    int           fVariability;    ///< How fast values change
    int           fComputability;  ///< When are values available
    int           fVectorability;  ///< When a signal can be vectorized
    int           fBoolean;        ///< When a signal stands for a boolean value
    itv::interval fInterval;       ///< Minimal and maximal values the signal can take
    res           fRes;            ///< Resolution (fixed-point)
    Tree          fCode;           ///< Tree representation (for memoization purposes)

   public:
    AudioType(int n, int v, int c, int vec = kVect, int b = kNum, itv::interval i = interval(),
              res r = res());
    virtual ~AudioType() {}  ///< not really useful here, but make compiler happier

    int nature() const
    {
        return fNature;
    }  ///< returns the kind of values (integer or floating point)
    int variability() const
    {
        return fVariability;
    }  ///< returns how fast values change (constant, by blocks, by samples)
    int computability() const
    {
        return fComputability;
    }  ///< returns when values are available (compilation, initialisation, execution)
    int vectorability() const
    {
        return fVectorability;
    }  ///< returns when a signal can be vectorized
    int boolean() const { return fBoolean; }  ///< returns when a signal stands for a boolean value

    interval getInterval() const
    {
        return fInterval;
    }  ///< returns the interval (min and max values) of a signal
    void setInterval(const interval& r) { fInterval = r; }
    res  getRes() const { return fRes; }  ///< returns the resolution of the signal (fixed)

    void setCode(Tree code) { fCode = code; }  ///< sets the memoized code of a signal
    Tree getCode() { return fCode; }           ///< returns the memoized code of a signal

    virtual AudioType* promoteNature(int n)        = 0;  ///< promote the nature of a type
    virtual AudioType* promoteVariability(int n)   = 0;  ///< promote the variability of a type
    virtual AudioType* promoteComputability(int n) = 0;  ///< promote the computability of a type
    virtual AudioType* promoteVectorability(int n) = 0;  ///< promote the vectorability of a type
    virtual AudioType* promoteBoolean(int n)       = 0;  ///< promote the booleanity of a type
    virtual AudioType* promoteInterval(const interval& i) = 0;  ///< promote the interval of a type

    virtual std::ostream& print(std::ostream& dst) const = 0;  ///< print nicely a type
    ///< true when type is maximal (and therefore can't change depending of hypothesis)
    virtual bool isMaximal() const = 0;
};

// printing
inline std::ostream& operator<<(std::ostream& s, const AudioType& n)
{
    return n.print(s);
}

/**
 * Return the nature of a vector of types.
 */
inline int mergenature(ConstTypes v)
{
    int r = 0;
    for (size_t i = 0; i < v.size(); i++) {
        r |= v[i]->nature();
    }
    return r;
}

/**
 * Return the variability of a vector of types.
 */
inline int mergevariability(ConstTypes v)
{
    int r = 0;
    for (size_t i = 0; i < v.size(); i++) {
        r |= v[i]->variability();
    }
    return r;
}

/**
 * Return the computability of a vector of types.
 */
inline int mergecomputability(ConstTypes v)
{
    int r = 0;
    for (size_t i = 0; i < v.size(); i++) {
        r |= v[i]->computability();
    }
    return r;
}

/**
 * Return the vectorability of a vector of types.
 */
inline int mergevectorability(ConstTypes v)
{
    int r = 0;
    for (size_t i = 0; i < v.size(); i++) {
        r |= v[i]->vectorability();
    }
    return r;
}

/**
 * Return the booleanity of a vector of types.
 */
inline int mergeboolean(ConstTypes v)
{
    int r = 0;
    for (size_t i = 0; i < v.size(); i++) {
        r |= v[i]->boolean();
    }
    return r;
}

/**
 * Return the interval of a vector of types.
 */
inline interval mergeinterval(ConstTypes v)
{
    if (v.size() == 0) {
        return interval();
    } else {
        interval r = v[0]->getInterval();
        for (size_t i = 1; i < v.size(); i++) {
            r = itv::reunion(r, v[i]->getInterval());
        }
        return r;
    }
}

AudioType* makeSimpleType(int nature, int variability, int computability, int vectorability,
                          int boolean, const interval& i);
AudioType* makeSimpleType(int n, int v, int c, int vec, int b, const interval& i, const res& lsb);
// didn't use a default arg, would have created a cyclic dependancy with global.hh

/**
 * The type of a simple numeric audio signal.
 * Beside a computability and a variability, SimpleTypes have
 * a "nature" indicating if they represent an integer or floating
 * point audio signals.
 */
class SimpleType : public AudioType {
   public:
    SimpleType(int n, int v, int c, int vec, int b, const interval& i, const res& lsb)
        : AudioType(n, v, c, vec, b, i, lsb)
    {
        // cerr << "new simple type " << i << " -> " << *this << endl;
    }  ///< constructs a SimpleType from a nature a variability and a computability

    virtual std::ostream& print(std::ostream& dst) const;  ///< print a SimpleType

    virtual AudioType* promoteNature(int n)
    {
        return makeSimpleType(n | fNature, fVariability, fComputability, fVectorability, fBoolean,
                              fInterval);
    }  ///< promote the nature of a type
    virtual AudioType* promoteVariability(int v)
    {
        return makeSimpleType(fNature, v | fVariability, fComputability, fVectorability, fBoolean,
                              fInterval);
    }  ///< promote the variability of a type
    virtual AudioType* promoteComputability(int c)
    {
        return makeSimpleType(fNature, fVariability, c | fComputability, fVectorability, fBoolean,
                              fInterval);
    }  ///< promote the computability of a type
    virtual AudioType* promoteVectorability(int vec)
    {
        return makeSimpleType(fNature, fVariability, fComputability, vec | fVectorability, fBoolean,
                              fInterval);
    }  ///< promote the vectorability of a type
    virtual AudioType* promoteBoolean(int b)
    {
        return makeSimpleType(fNature, fVariability, fComputability, fVectorability, b | fBoolean,
                              fInterval);
    }  ///< promote the booleanity of a type
    virtual AudioType* promoteInterval(const interval& i)
    {
        // cerr << "promote to Interval " << i << endl;
        // cerr << "for type : " << *this << endl;
        Type t = makeSimpleType(fNature, fVariability, fComputability, fVectorability, fBoolean,
                                i);  ///< promote the interval of a type
                                     // cerr << "gives type " << *t << endl;
        return t;
    }
    virtual bool isMaximal()
        const;  ///< true when type is maximal (and therefore can't change depending of hypothesis)
};



//-------------------------------------------------
//-------------------------------------------------
//                 operations on types
//-------------------------------------------------
//-------------------------------------------------

//--------------------------------------------------
// types creation

Type operator|(const Type& t1, const Type& t2);

//--------------------------------------------------
// types comparaison

bool operator==(const Type& t1, const Type& t2);
bool operator<=(const Type& t1, const Type& t2);

inline bool operator!=(const Type& t1, const Type& t2)
{
    return !(t1 == t2);
}
inline bool operator<(const Type& t1, const Type& t2)
{
    return t1 <= t2 && t1 != t2;
}
inline bool operator>(const Type& t1, const Type& t2)
{
    return t2 < t1;
}
inline bool operator>=(const Type& t1, const Type& t2)
{
    return t2 <= t1;
}

//--------------------------------------------------
// types predicats-conversion

SimpleType* isSimpleType(AudioType* t);

//--------------------------------------------------
// types impressions

std::ostream& operator<<(std::ostream& dst, const SimpleType& t);
std::ostream& operator<<(std::ostream& dst, const Type& t);

//--------------------------------------------------
// type verification

Type checkInt(Type t);    ///< check that t is an integer
Type checkKonst(Type t);  ///< check that t is a constant
Type checkInit(Type t);   ///< check that t is known at init time

int checkDelayInterval(Type t);  ///< check if the interval of t is appropriate for a delay

//--------------------------------------------------
// Type conversion

Tree codeAudioType(AudioType* t);  ///< Code an audio type as a tree (memoization)

#endif
