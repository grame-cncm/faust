/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _SigType_
#define _SigType_

#include <vector>
#include <string>
#include <iostream>
#include "tree.hh"
#include "smartpointer.hh"
#include "interval.hh"
#include "instructions.hh"
#include "garbageable.hh"

/*********************************************************************
*
*						Type System for FAUST
*
*	<type> 			::= <simpletype> ||  table(<type>)
*			 		 	||  <type>|<type>  || <type>*<type>
*	<simpletype>	::= <nature><variability><computability><vectorability>||<boolean>
*	<nature>		::= TINT || TREAL
*	<variability>	::= TKONST || TBLOCK || TSAMP
*	<computability>	::= TCOMP  || TINIT  || TEXEC
*	<vectorability> ::= KVECT  || KSCAL  || KTRUESCAL
*	<boolean>       ::= KNUM   || KBOOL
*
**********************************************************************/


//--------------------------------------------------
// qualite des types simples

enum { kInt = 0, kReal = 1 };                           ///< nature : integer or floating point values
enum { kNum = 0 , kBool = 1};                           ///< boolean : when a signal stands for a boolean value ( while being of c-type int or float )
enum { kKonst = 0, kBlock = 1, kSamp = 3 };             ///< variability : how fast values change
enum { kComp = 0, kInit = 1, kExec = 3 };               ///< computability : when values are available
enum { kVect = 0, kScal = 1, kTrueScal = 3/*, kIndex = 4*/};///< vectorability: when a signal can be vectorized ( actually, only kVect and kScal matter; kTrueScal and kIndex don't denote types but are here to simplify code generation )

/*---------------------------------------------------------------------

	AbstractType :
	The root class for SimpleType, TableType and TupletType

	Type :
	A smartPointer to type

----------------------------------------------------------------------*/

using namespace std;

class AudioType;

typedef P<AudioType> Type;

/**
 * The Root class for all audio data types.
 * All audio types have a "variability" (how fast the values change) and
 * a "computability" (when the values are available). Simple types have
 * also a "nature" (integer or floating point).
 */
 
class AudioType : public virtual Garbageable
{
  protected:
	int   		fNature;  		  	///< the kind of data represented
	int   		fVariability; 	  	///< how fast values change
  	int   		fComputability;	  	///< when are values available
    int   		fVectorability;     ///< when a signal can be vectorized
    int   		fBoolean;           ///< when a signal stands for a boolean value

    interval	fInterval;			///< Minimal and maximal values the signal can take
    Tree        fCode;              ///< Tree representation (for memoization purposes)


  public :
	AudioType(int n, int v, int c, int vec = kVect, int b = kNum, interval i = interval())
		  : fNature(n), fVariability(v), fComputability(c),
		    fVectorability(vec), fBoolean(b),
            fInterval(i), fCode(0) {}                           ///< constructs an abstract audio type
  	virtual ~AudioType(){}                                      ///< not really useful here, but make compiler happier

	int 	nature() 		const	{ return fNature; }         ///< returns the kind of values (integre or floating point)
	int 	variability() 	const	{ return fVariability; }	///< returns how fast values change (constant, by blocks, by samples)
	int 	computability() const	{ return fComputability;}	///< returns when values are available (compilation, initialisation, execution)
	int 	vectorability() const 	{ return fVectorability;} 	///< returns when a signal can be vectorized
	int 	boolean() 		const	{ return fBoolean; } 		///< returns when a signal stands for a boolean value

    interval getInterval() 	const	{ return fInterval; }		///< returns the interval (min dn max values) of a signal

    void    setCode(Tree code)      { fCode = code; }           ///< returns the interval (min dn max values) of a signal
    Tree    getCode()               { return fCode; }           ///< returns the interval (min dn max values) of a signal


	virtual AudioType* promoteNature(int n)         = 0;		///< promote the nature of a type
    virtual AudioType* promoteVariability(int n)	= 0;		///< promote the variability of a type
    virtual AudioType* promoteComputability(int n)	= 0;		///< promote the computability of a type
    virtual AudioType* promoteVectorability(int n)	= 0;		///< promote the vectorability of a type
	virtual AudioType* promoteBoolean(int n)   	= 0;			///< promote the booleanity of a type
	//virtual AudioType* promoteInterval(const interval& i) = 0;		///< promote the interval of a type

    virtual ostream& print(ostream& dst) const		= 0;		///< print nicely a type
    virtual bool    isMaximal() const               = 0;        ///< true when type is maximal (and therefore can't change depending of hypothesis)

  protected:
	void		setInterval(const interval& r)	{ fInterval = r;}

};

//printing
inline ostream& operator << (ostream& s, const AudioType& n) { return n.print(s); }

/**
 * Return the nature of a vector of types.
 */
inline int mergenature(const vector<Type>& v)
{
	int r = 0;
	for (unsigned int i = 0; i < v.size(); i++) r |= v[i]->nature();
	return r;
}

/**
 * Return the variability of a vector of types.
 */
inline int mergevariability(const vector<Type>& v)
{
	int r = 0;
	for (unsigned int i = 0; i < v.size(); i++) r |= v[i]->variability();
	return r;
}

/**
 * Return the computability of a vector of types.
 */
inline int mergecomputability(const vector<Type>& v)
{
	int r = 0;
	for (unsigned int i = 0; i < v.size(); i++) r |= v[i]->computability();
	return r;
}

/**
 * Return the vectorability of a vector of types.
 */
inline int mergevectorability(const vector<Type>& v)
{
	int r = 0;
	for (unsigned int i = 0; i < v.size(); i++) r |= v[i]->vectorability();
	return r;
}

/**
 * Return the booleanity of a vector of types.
 */
inline int mergeboolean(const vector<Type>& v)
{
	int r = 0;
	for (unsigned int i = 0; i < v.size(); i++) r |= v[i]->boolean();
	return r;
}

/**
 * Return the interval of a vector of types.
 */
inline interval mergeinterval(const vector<Type>& v)
{
	if (v.size()==0) {
		return interval();
	} else {
		double lo=0, hi=0;
		for (unsigned int i = 0; i < v.size(); i++) {
			interval r = v[i]->getInterval();
			if (!r.valid) return r;
			if (i==0) {
				lo = r.lo;
				hi = r.hi;
			} else {
				lo = min(lo,r.lo);
				hi = max(hi,r.hi);
			}
		}
		return interval(lo, hi);
	}
}

AudioType* makeSimpleType(int n, int v, int c, int vec, int b, const interval& i);

AudioType* makeTableType(const Type& ct);
AudioType* makeTableType(const Type& ct, int n, int v, int c, int vec);
AudioType* makeTableType(const Type& ct, int n, int v, int c, int vec, int b, const interval& i);

AudioType* makeTupletType(const vector<Type>& vt);
AudioType* makeTupletType(const vector<Type>& vt, int n, int v, int c, int vec, int b, const interval& i);

/**
 * The type of a simple numeric audio signal.
 * Beside a computability and a variability, SimpleTypes have
 * a "nature" indicating if they represent an integer or floating
 * point audio signals.
 */
class SimpleType : public AudioType
{
  public :

	SimpleType(int n, int v, int c, int vec, int b, const interval& i) : AudioType(n,v,c,vec,b,i) {
		//cerr << "new simple type " << i << " -> " << *this << endl;
	}			///< constructs a SimpleType from a nature a variability and a computability

	virtual ostream& print(ostream& dst) const;						///< print a SimpleType

    virtual AudioType* promoteNature(int n)                 { return makeSimpleType(n|fNature, fVariability, fComputability, fVectorability, fBoolean, fInterval); }		///< promote the nature of a type
    virtual AudioType* promoteVariability(int v)			{ return makeSimpleType(fNature, v|fVariability, fComputability, fVectorability, fBoolean, fInterval); }		///< promote the variability of a type
    virtual AudioType* promoteComputability(int c)			{ return makeSimpleType(fNature, fVariability, c|fComputability, fVectorability, fBoolean, fInterval); }		///< promote the computability of a type
    virtual AudioType* promoteVectorability(int vec)		{ return makeSimpleType(fNature, fVariability, fComputability, vec|fVectorability, fBoolean, fInterval); }	///< promote the vectorability of a type
    virtual AudioType* promoteBoolean(int b)        		{ return makeSimpleType(fNature, fVariability, fComputability, fVectorability, b|fBoolean, fInterval); }		///< promote the booleanity of a type
// 	virtual AudioType* promoteInterval(const interval& i)	{
// 		cerr << "promote to Interval " << i  << endl;
// 		cerr << "for type : " << *this << endl;
// 		Type t = makeSimpleType(fNature, fVariability, fComputability, fVectorability, fBoolean, i); 				///< promote the interval of a type
// 		cerr << "gives type " << *t << endl;
// 		return t;
// 	}

    virtual bool isMaximal() const;                          ///< true when type is maximal (and therefore can't change depending of hypothesis)
};

inline Type intCast (Type t)	{ return makeSimpleType(kInt, t->variability(), t->computability(), t->vectorability(), t->boolean(), t->getInterval()); }
inline Type floatCast (Type t)	{ return makeSimpleType(kReal, t->variability(), t->computability(), t->vectorability(), t->boolean(), t->getInterval()); }
inline Type sampCast (Type t)	{ return makeSimpleType(t->nature(), kSamp, t->computability(), t->vectorability(), t->boolean(), t->getInterval()); }
inline Type boolCast (Type t)   { return makeSimpleType(kInt, t->variability(), t->computability(), t->vectorability(), kBool, t->getInterval()); }
inline Type numCast (Type t)    { return makeSimpleType(t->nature(), t->variability(), t->computability(), t->vectorability(), kNum, t->getInterval()); }
inline Type vecCast (Type t)    { return makeSimpleType(t->nature(), t->variability(), t->computability(), kVect, t->boolean(), t->getInterval()); }
inline Type scalCast (Type t)   { return makeSimpleType(t->nature(), t->variability(), t->computability(), kScal, t->boolean(), t->getInterval()); }
inline Type truescalCast (Type t){ return makeSimpleType(t->nature(), t->variability(), t->computability(), kTrueScal, t->boolean(), t->getInterval()); }

inline Type castInterval (Type t, const interval& i)
{
    return makeSimpleType(t->nature(), t->variability(), t->computability(), t->vectorability(), t->boolean(), i);
}

/**
 * The type of a table of audio data.
 * Beside a computability and a variability, TableTypes have
 * a "content" indicating the type of the data stored in the table.
 */
class TableType : public AudioType
{
  protected :
	const Type fContent;											///< type of that data stored in the table

  public :
	TableType(const Type& t) :
		  AudioType(t->nature(), kKonst, kInit, kVect, t->boolean()), 
		  fContent(t) {}		///< construct a TableType with a content of a type t
#if 0
	TableType(const Type& t, int v, int c) :
		  AudioType(t->nature(), t->variability()|v, t->computability()|c, t->vectorability(), t->boolean()),
		  fContent(t) {}		///< construct a TableType with a content of a type t, promoting variability and computability

	TableType(const Type& t, int n, int v, int c) :
		  AudioType(t->nature()|n, t->variability()|v, t->computability()|c, t->vectorability(), t->boolean()),
		  fContent(t) {}		///< construct a TableType with a content of a type t, promoting nature, variability and computability

	TableType(const Type& t, int n, int v, int c, int vec, int b) :
		  AudioType(t->nature()|n, t->variability()|v, t->computability()|c, t->vectorability()|vec, t->boolean()|b),
		  fContent(t) {}		///< construct a TableType with a content of a type t, promoting nature, variability, computability, vectorability and booleanity
#endif

    TableType(const Type& t, int n, int v, int c, int vec, int b, const interval& i) :
          AudioType(t->nature()|n, kKonst|v, kInit|c, kVect|vec, t->boolean()|b, i),
          fContent(t) {}		///< construct a TableType with a content of a type t, promoting nature, variability, computability, vectorability and booleanity

    TableType(const Type& t, int n, int v, int c, int vec) :
          AudioType(t->nature()|n, kKonst|v, kInit|c, kVect|vec, t->boolean()),
          fContent(t) {}		///< construct a TableType with a content of a type t, promoting nature, variability, computability and vectorability


  	Type content() const				{ return fContent; 	}		///< return the type of data store in the table
	virtual ostream& print(ostream& dst) const;						///< print a TableType

    virtual AudioType* promoteNature(int n)                 { return makeTableType(fContent, n|fNature, fVariability, fComputability, fVectorability, fBoolean, fInterval); }	///< promote the nature of a type
    virtual AudioType* promoteVariability(int v)			{ return makeTableType(fContent, fNature, v|fVariability, fComputability, fVectorability, fBoolean, fInterval); }	///< promote the variability of a type
    virtual AudioType* promoteComputability(int c)			{ return makeTableType(fContent, fNature, fVariability, c|fComputability, fVectorability, fBoolean, fInterval); }	///< promote the computability of a type
    virtual AudioType* promoteVectorability(int vec)		{ return makeTableType(fContent, fNature, fVariability, fComputability, vec|fVectorability, fBoolean, fInterval);}///< promote the vectorability of a type
    virtual AudioType* promoteBoolean(int b)        		{ return makeTableType(fContent, fNature, fVariability, fComputability, fVectorability, b|fBoolean, fInterval); }	///< promote the booleanity of a type
    //virtual AudioType* promoteInterval(const interval& i)	{ return makeTableType(fContent, fNature, fVariability, fComputability, fVectorability, fBoolean, i); }			///< promote the interval of a type

    virtual bool isMaximal() const;                                 ///< true when type is maximal (and therefore can't change depending of hypothesis)
};


/**
 * The type of a tuplet of data.
 * Beside a computability and a variability, TupletTypes have
 * a set of components.
 */
class TupletType : public AudioType
{
  protected:
	vector<Type> fComponents;

  public:
    TupletType() :
          AudioType(0,0,0)
          {}

    TupletType(const vector<Type>& vt) :
          AudioType(mergenature(vt),mergevariability(vt),mergecomputability(vt),mergevectorability(vt),mergeboolean(vt), mergeinterval(vt)),
          fComponents(vt) {}

	TupletType(const vector<Type>& vt, int n, int v, int c, int vec, int b, const interval& i) :
		  AudioType(n|mergenature(vt), v|mergevariability(vt), c|mergecomputability(vt), vec|mergevectorability(vt), b|mergeboolean(vt), i),
		  fComponents(vt) {}

	int arity()	const						{ return (int)fComponents.size(); }
	Type operator[](unsigned int i) const	{ return fComponents[i]; }
	virtual ostream& print(ostream& dst) const;

	virtual AudioType* promoteNature(int n)                 { return new TupletType(fComponents, n|fNature, fVariability, fComputability, fVectorability, fBoolean, fInterval); }	///< promote the nature of a type
	virtual AudioType* promoteVariability(int v)			{ return new TupletType(fComponents, fNature, v|fVariability, fComputability, fVectorability, fBoolean, fInterval); }	///< promote the variability of a type
	virtual AudioType* promoteComputability(int c)			{ return new TupletType(fComponents, fNature, fVariability, c|fComputability, fVectorability, fBoolean, fInterval); }	///< promote the computability of a type
	virtual AudioType* promoteVectorability(int vec)		{ return new TupletType(fComponents, fNature, fVariability, fComputability, vec|fVectorability, fBoolean, fInterval); }	///< promote the vectorability of a type
	virtual AudioType* promoteBoolean(int b)        		{ return new TupletType(fComponents, fNature, fVariability, fComputability, fVectorability, b|fBoolean, fInterval); }	///< promote the booleanity of a type
	//virtual AudioType* promoteInterval(const interval& i)	{ return new TupletType(fComponents, fNature, fVariability, fComputability, fVectorability, fBoolean, i);  }			///< promote the interval of a type

    virtual bool isMaximal() const;                         ///< true when type is maximal (and therefore can't change depending of hypothesis)

};

//-------------------------------------------------
//-------------------------------------------------
// 				operations sur les types
//-------------------------------------------------
//-------------------------------------------------


//--------------------------------------------------
// liste de types predefinis

extern Type TINT;
extern Type TREAL;

extern Type TKONST;
extern Type TBLOCK;
extern Type TSAMP;

extern Type TCOMP;
extern Type TINIT;
extern Type TEXEC;

extern Type TINPUT;
extern Type TGUI;
extern Type TGUI01;
extern Type INT_TGUI;
extern Type TREC;

//--------------------------------------------------
// creation de types

Type table(const Type& t);
Type operator|(const Type& t1, const Type& t2);
Type operator*(const Type& t1, const Type& t2);

//--------------------------------------------------
// comparaison de types

bool operator==(const Type& t1, const Type& t2);
bool operator<=(const Type& t1, const Type& t2);

inline bool operator!=(const Type& t1, const Type& t2) { return !(t1==t2); }
inline bool operator< (const Type& t1, const Type& t2) { return t1<=t2 && t1!=t2; }
inline bool operator> (const Type& t1, const Type& t2) { return t2<t1; 	}
inline bool operator>=(const Type& t1, const Type& t2) { return t2<=t1; }

//--------------------------------------------------
// predicats-conversion de types

SimpleType* 	isSimpleType (AudioType* t);
TableType* 		isTableType  (AudioType* t);
TupletType* 	isTupletType (AudioType* t);

//--------------------------------------------------
// impressions de types

ostream& operator<<(ostream& dst, const SimpleType& t);
ostream& operator<<(ostream& dst, const Type& t);
ostream& operator<<(ostream& dst, const TableType& t);
ostream& operator<<(ostream& dst, const TupletType& t);

//--------------------------------------------------
// verification de type

Type checkInt(Type t); 				///< verifie que t est entier
Type checkKonst(Type t);			///< verifie que t est constant
Type checkInit(Type t);				///< verifie que t est connu a l'initialisation

Type checkIntParam(Type t);			///< verifie que t est connu a l'initialisation, constant et entier

Type checkWRTbl(Type tbl, Type wr);	///< verifie que wr est compatible avec le contenu de tbl

int checkDelayInterval(Type t);		///< Check if the interval of t is appropriate for a delay

//--------------------------------------------------
// conversion de type

// SL : 28/09/17
string old_cType(Type t);

Typed::VarType ctType(Type t);

Tree codeAudioType(AudioType* t);   ///< Code an audio type as a tree (memoization)

#endif
