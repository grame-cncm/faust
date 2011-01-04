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



#include "sigtype.hh"


//------------------------------------------------------------------------------------
//
//		Surcharges de l'operateur d'impression <<
//
//------------------------------------------------------------------------------------


ostream& operator<<(ostream& dst, const Type& t) 	{ return  t->print(dst);}

ostream& operator<<(ostream& dst, const SimpleType& t) 	{ return  t.print(dst); }

ostream& operator<<(ostream& dst, const TableType& t) 	{ return  t.print(dst); }

ostream& operator<<(ostream& dst, const TupletType& t) 	{ return  t.print(dst); }


//------------------------------------------------------------------------------------
//
//		Definition des methodes d'impression
//
//------------------------------------------------------------------------------------


/**
 * Print the content of a simple type on a stream
 */
ostream& SimpleType::print(ostream& dst) const
{
	return  dst << "NR"[nature()]
		    << "KB?S"[variability()]
		    << "CI?E"[computability()]
		    << "VS?TS"[vectorability()]
		    << "N?B"[boolean()]
			<< " " << fInterval;
}


/**
 * Print the content of a table type on a stream
 */
ostream& TableType::print(ostream& dst) const
{
	dst << "KB?S"[variability()]
		<< "CI?E"[computability()]
		<< " " << fInterval
		<< ":Table(";
	fContent->print(dst);
	return dst << ')';
}



/**
 * Print the content of a tuplet of types on a stream
 */
ostream& TupletType::print(ostream& dst) const
{
	dst << "KB?S"[variability()]
		<< "CI?E"[computability()]
		<< " " << fInterval
		<< " : {";
	string sep = "";
	for (unsigned int i = 0; i < fComponents.size(); i++, sep="*") {
		dst << sep;
		fComponents[i]->print(dst);
	}
	dst << '}';
	return  dst;
}

ostream& FaustVectorType::print(ostream& dst) const
{
    return  dst << "V" << fSize
            << "NR"[nature()]
            << "KB?S"[variability()]
            << "CI?E"[computability()]
            << "VS?TS"[vectorability()]
            << "N?B"[boolean()]
            << " " << fInterval;
}


//------------------------------------------------------------------------------------
//
//		Construction des types
// 		t := p, table(t), t|t, t*t
//
//------------------------------------------------------------------------------------

// Essential predefined types

Type TINT 	= new SimpleType(kInt, kKonst, kComp, kVect, kNum, interval());
Type TREAL 	= new SimpleType(kReal, kKonst, kComp, kVect, kNum, interval());

Type TKONST = new SimpleType(kInt, kKonst, kComp, kVect, kNum, interval());
Type TBLOCK = new SimpleType(kInt, kBlock, kComp, kVect, kNum, interval());
Type TSAMP 	= new SimpleType(kInt, kSamp, kComp, kVect, kNum, interval());

Type TCOMP 	= new SimpleType(kInt, kKonst, kComp, kVect, kNum, interval());
Type TINIT 	= new SimpleType(kInt, kKonst, kInit, kVect, kNum, interval());
Type TEXEC 	= new SimpleType(kInt, kKonst, kExec, kVect, kNum, interval());

// more predefined types

Type TINPUT	= new SimpleType(kReal, kSamp, kExec, kVect, kNum, interval());
Type TGUI	= new SimpleType(kReal, kBlock,kExec, kVect, kNum, interval());
Type INT_TGUI   = new SimpleType(kInt,  kBlock,kExec, kVect, kNum, interval());
//Type TREC   = new SimpleType(kInt,  kSamp, kInit, kVect, kNum, interval()); // kVect ou kScal ?
Type TREC   = TINT;


Type operator| ( const Type& t1, const Type& t2)
{
	SimpleType 	*st1, *st2;
	TableType	*tt1, *tt2;
	TupletType	*nt1, *nt2;
    FaustVectorType *vt1, *vt2;

	if ( (st1 = isSimpleType(t1)) && (st2 = isSimpleType(t2)) ) {

		return new SimpleType(	st1->nature()|st2->nature(),
					st1->variability()|st2->variability(),
					st1->computability()|st2->computability(),
					st1->vectorability()|st2->vectorability(),
					st1->boolean()|st2->boolean(),
					interval() /// achanger
					);

    } else if ( (vt1 = isVectorType(t1)) && (vt2 = isVectorType(t2)) ) {
        if (vt1->size() != vt2->size()) {
            cerr << "Type error: cannot unify vector types of different sizes!" << endl;
            exit(1);
        }
        Type dt1 = vt1->dereferenceType();
        Type dt2 = vt2->dereferenceType();

        return new FaustVectorType(vt1->size(), dt1 | dt2 );

	} else if ( (tt1 = isTableType(t1)) && (tt2 = isTableType(t2)) ) {

		return new TableType( tt1->content() | tt2->content() );

	} else if ( (nt1 = isTupletType(t1)) && (nt2 = isTupletType(t2)) ) {

		vector<Type> v;
		int n = min(nt1->arity(), nt2->arity());
		for (int i=0; i<n; i++) { v.push_back( (*nt1)[i] | (*nt2)[i]); }
		return new TupletType( v );

	} else {

		cerr << "Error : trying to combine incompatible types, " << t1 << " and " << t2 << endl;
		exit(1);
		return 0;
	}
}

bool operator== ( const Type& t1, const Type& t2)
{
	SimpleType 	*st1, *st2;
	TableType	*tt1, *tt2;
	TupletType	*nt1, *nt2;
    FaustVectorType *vt1, *vt2;

	if (t1->variability() != t2->variability()) 	return false;
	if (t1->computability() != t2->computability()) return false;

	if ( (st1 = isSimpleType(t1)) && (st2 = isSimpleType(t2)) ) return (st1->nature() == st2->nature())&&(st1->vectorability() == st2->vectorability())&&(st1->boolean() == st2->boolean());
	if ( (tt1 = isTableType(t1)) && (tt2 = isTableType(t2)) )	return tt1->content()== tt2->content();
	if ( (nt1 = isTupletType(t1)) && (nt2 = isTupletType(t2)) ) {
		int a1 = nt1->arity();
		int a2 = nt2->arity();
		if (a1 == a2) {
			for (int i=0; i<a1; i++)  { if ((*nt1)[i] != (*nt2)[i]) return false; }
			return true;
		} else {
			return false;
		}
	}
    if ( (vt1 = isVectorType(t1)) && (vt2 = isVectorType(t2)) ) {
        if (vt1->size() == vt2->size() &&
            vt1->dereferenceType() == vt2->dereferenceType() )
            return true;
    }
	return false;
}

bool operator<= ( const Type& t1, const Type& t2)
{
	return (t1|t2) == t2;
}



Type operator* 	(const Type& t1, const Type& t2)
{
	vector<Type>	v;

	TupletType* nt1 = dynamic_cast<TupletType*>((AudioType*)t1);
	TupletType* nt2 = dynamic_cast<TupletType*>((AudioType*)t2);

	if (nt1) {
		for (int i=0; i<nt1->arity(); i++) {
			v.push_back((*nt1)[i]);
		}
	} else {
		v.push_back(t1);
	}

	if (nt2) {
		for (int i=0; i<nt2->arity(); i++) {
			v.push_back((*nt2)[i]);
		}
	} else {
		v.push_back(t2);
	}
	return new TupletType(v);
}


SimpleType*	        isSimpleType(AudioType* t)	    { return dynamic_cast<SimpleType*>(t); }
TableType* 	        isTableType(AudioType* t)	    { return dynamic_cast<TableType*>(t);  }
TupletType*	        isTupletType(AudioType* t)	    { return dynamic_cast<TupletType*>(t); }
FaustVectorType*    isVectorType(AudioType* t)      { return dynamic_cast<FaustVectorType*>(t); }



//--------------------------------------------------
// verification de type

Type checkInt(Type t)
{
	// verifie que t est entier
	SimpleType* st = isSimpleType(t);
	if (st == 0 || st->nature() > kInt) {
		cerr << "Error : checkInt failed for type " << t << endl;
		exit(1);
	}
	return t;
}

Type checkKonst(Type t)
{
	// verifie que t est constant
	if (t->variability() > kKonst) {
		cerr << "Error : checkKonst failed for type " << t << endl;
		exit(1);
	}
	return t;
}

Type checkInit(Type t)
{
	// verifie que t est connu a l'initialisation
	if (t->computability() > kInit) {
		cerr << "Error : checkInit failed for type " << t << endl;
		exit(1);
	}
	return t;
}

Type checkIntParam(Type t)
{
	return checkInit(checkKonst(checkInt(t)));
}

Type checkWRTbl(Type tbl, Type wr)
{
	// verifie que wr est compatible avec le contenu de tbl
	if (wr->nature() > tbl->nature()) {
		cerr << "Error : checkWRTbl failed, the content of  " << tbl << " is incompatible with " << wr << endl;
		exit(1);
	}
	return tbl;
}

/**
	\brief Check is a type is appropriate for a delay.
	@return -1 if not appropriate, mxd (max delay) if appropriate

 */
int checkDelayInterval(Type t)
{
	interval i = t->getInterval();
	if (i.valid && i.lo >= 0) {
		return int(i.hi+0.5);
	} else {
		//cerr << "checkDelayInterval failed for : " << i << endl;
		return -1;
	}
}


// Donne le nom du type C correspondant �la nature d'un signal
string cType (Type t)
{
	return (t->nature() == kInt) ? "int" : "float";
}

Typed::VarType ctType (Type t)
{
	return (t->nature() == kInt) ? Typed::kInt : Typed::kFloat;
}

