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
#include "property.hh"
#include "tree.hh"

int AudioType::gAllocationCount = 0;

bool SimpleType::isMaximal() const  ///< true when type is maximal (and therefore can't change depending of hypothesis)
{
    return (fNature == kReal) && (fVariability == kSamp) && (fComputability == kExec);
}

//------------------------------------------------------------------------------------
//
//		Surcharges de l'operateur d'impression <<
//
//------------------------------------------------------------------------------------

ostream& operator<<(ostream& dst, const Type& t)
{
    return t->print(dst);
}

ostream& operator<<(ostream& dst, const SimpleType& t)
{
    return t.print(dst);
}

ostream& operator<<(ostream& dst, const TableType& t)
{
    return t.print(dst);
}

ostream& operator<<(ostream& dst, const TupletType& t)
{
    return t.print(dst);
}

ostream& operator<<(ostream& dst, const VectorType& t)
{
    return t.print(dst);
}

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
    return dst << "NR"[nature()] << "KB?S"[variability()] << "CI?E"[computability()] << "VS?TS"[vectorability()]
               << "N?B"[boolean()] << " " << fInterval;
}

/**
 * Print the content of a table type on a stream
 */
ostream& TableType::print(ostream& dst) const
{
    dst << "KB?S"[variability()] << "CI?E"[computability()] << " " << fInterval << ":Table(";
    fContent->print(dst);
    return dst << ')';
}

/**
 *  true when type is maximal (and therefore can't change depending of hypothesis)
 */
bool TableType::isMaximal() const
{
    return (fNature == kReal) && (fVariability == kSamp) && (fComputability == kExec);
}

/**
 * Print the content of a tuplet of types on a stream
 */
ostream& TupletType::print(ostream& dst) const
{
    dst << "KB?S"[variability()] << "CI?E"[computability()] << " " << fInterval << " : {";
    string sep = "";
    for (unsigned int i = 0; i < fComponents.size(); i++, sep = "*") {
        dst << sep;
        fComponents[i]->print(dst);
    }
    dst << '}';
    return dst;
}

/**
 * Print the content of a vector type on a stream
 */
ostream& VectorType::print(ostream& dst) const
{
    dst << "vector[" << fSize << "," << fContent << "]";
    return dst;
}

/**
 *  true when type is maximal (and therefore can't change depending of hypothesis)
 */
bool TupletType::isMaximal() const
{
    for (unsigned int i = 0; i < fComponents.size(); i++) {
        if (!fComponents[i]->isMaximal()) return false;
    }
    return true;
}

//------------------------------------------------------------------------------------
//
//		Construction des types
// 		t := p, table(t), t|t, t*t
//
//------------------------------------------------------------------------------------

// Essential predefined types

Type TINT  = makeSimpleType(kInt, kKonst, kComp, kVect, kNum, interval());
Type TREAL = makeSimpleType(kReal, kKonst, kComp, kVect, kNum, interval());

Type TKONST = makeSimpleType(kInt, kKonst, kComp, kVect, kNum, interval());
Type TBLOCK = makeSimpleType(kInt, kBlock, kComp, kVect, kNum, interval());
Type TSAMP  = makeSimpleType(kInt, kSamp, kComp, kVect, kNum, interval());

Type TCOMP = makeSimpleType(kInt, kKonst, kComp, kVect, kNum, interval());
Type TINIT = makeSimpleType(kInt, kKonst, kInit, kVect, kNum, interval());
Type TEXEC = makeSimpleType(kInt, kKonst, kExec, kVect, kNum, interval());

// more predefined types

Type TINPUT   = makeSimpleType(kReal, kSamp, kExec, kVect, kNum, interval());
Type TGUI     = makeSimpleType(kReal, kBlock, kExec, kVect, kNum, interval());
Type TGUI01   = makeSimpleType(kReal, kBlock, kExec, kVect, kNum, interval(0, 1));
Type INT_TGUI = makeSimpleType(kInt, kBlock, kExec, kVect, kNum, interval());
// Type TREC   = makeSimpleType(kInt,  kSamp, kInit, kVect, kNum, interval()); // kVect ou kScal ?

// trying to accelerate type convergence
// Type TREC   = TINT;
Type TREC = makeSimpleType(kInt, kSamp, kInit, kScal, kNum, interval());  // kVect ou kScal ?

Type operator|(const Type& t1, const Type& t2)
{
    SimpleType *st1, *st2;
    TableType * tt1, *tt2;
    TupletType *nt1, *nt2;

    if ((st1 = isSimpleType(t1)) && (st2 = isSimpleType(t2))) {
        return makeSimpleType(st1->nature() | st2->nature(), st1->variability() | st2->variability(),
                              st1->computability() | st2->computability(), st1->vectorability() | st2->vectorability(),
                              st1->boolean() | st2->boolean(), reunion(st1->getInterval(), st2->getInterval()));

    } else if ((tt1 = isTableType(t1)) && (tt2 = isTableType(t2))) {
        return makeTableType(tt1->content() | tt2->content());

    } else if ((nt1 = isTupletType(t1)) && (nt2 = isTupletType(t2))) {
        vector<Type> v;
        int          n = min(nt1->arity(), nt2->arity());
        for (int i = 0; i < n; i++) {
            v.push_back((*nt1)[i] | (*nt2)[i]);
        }
        return new TupletType(v);

    } else {
        vector<int> D1, D2, D3;
        Type        b1 = t1->dimensions(D1);
        Type        b2 = t2->dimensions(D2);
        if (maxdimensions(D1, D2, D3)) {
            Type b3 = b1 | b2;
            return makeVectorType(b3, D3);
        }

        cerr << "Error : trying to combine incompatible types, " << t1 << " and " << t2 << endl;
        exit(1);
        return 0;
    }
}

bool operator==(const Type& t1, const Type& t2)
{
    SimpleType *st1, *st2;
    TableType * tt1, *tt2;
    TupletType *nt1, *nt2;
    VectorType *vt1, *vt2;

    if (t1->variability() != t2->variability()) return false;
    if (t1->computability() != t2->computability()) return false;

    if ((st1 = isSimpleType(t1)) && (st2 = isSimpleType(t2)))
        return (st1->nature() == st2->nature()) && (st1->variability() == st2->variability()) &&
               (st1->computability() == st2->computability()) && (st1->vectorability() == st2->vectorability()) &&
               (st1->boolean() == st2->boolean()) && (st1->getInterval().lo == st2->getInterval().lo) &&
               (st1->getInterval().hi == st2->getInterval().hi) &&
               (st1->getInterval().valid == st2->getInterval().valid);
    if ((tt1 = isTableType(t1)) && (tt2 = isTableType(t2))) return tt1->content() == tt2->content();
    if ((nt1 = isTupletType(t1)) && (nt2 = isTupletType(t2))) {
        int a1 = nt1->arity();
        int a2 = nt2->arity();
        if (a1 == a2) {
            for (int i = 0; i < a1; i++) {
                if ((*nt1)[i] != (*nt2)[i]) return false;
            }
            return true;
        } else {
            return false;
        }
    }

    // compare vector types
    if ((vt1 = isVectorType(t1)) && (vt2 = isVectorType(t2))) {
        if (vt1->size() == vt2->size()) {
            return vt1->content() == vt2->content();
        } else {
            return false;
        }
    }

    // types are different
    return false;
}

bool operator<=(const Type& t1, const Type& t2)
{
    return (t1 | t2) == t2;
}

Type operator*(const Type& t1, const Type& t2)
{
    vector<Type> v;

    TupletType* nt1 = dynamic_cast<TupletType*>((AudioType*)t1);
    TupletType* nt2 = dynamic_cast<TupletType*>((AudioType*)t2);

    if (nt1) {
        for (int i = 0; i < nt1->arity(); i++) {
            v.push_back((*nt1)[i]);
        }
    } else {
        v.push_back(t1);
    }

    if (nt2) {
        for (int i = 0; i < nt2->arity(); i++) {
            v.push_back((*nt2)[i]);
        }
    } else {
        v.push_back(t2);
    }
    return new TupletType(v);
}

SimpleType* isSimpleType(AudioType* t)
{
    return dynamic_cast<SimpleType*>(t);
}
TableType* isTableType(AudioType* t)
{
    return dynamic_cast<TableType*>(t);
}
TupletType* isTupletType(AudioType* t)
{
    return dynamic_cast<TupletType*>(t);
}
VectorType* isVectorType(AudioType* t)
{
    return dynamic_cast<VectorType*>(t);
}

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
        return int(i.hi + 0.5);
    } else {
        // cerr << "checkDelayInterval failed for : " << i << endl;
        return -1;
    }
}

// Donne le nom du type C correspondant �la nature d'un signal
string cType(Type t)
{
    return (t->nature() == kInt) ? "int" : "float";
}

/*****************************************************************************
 *
 *      codeAudioType(Type) -> Tree
 *      Code an audio type as a tree in order to benefit of memoization
 *
 *****************************************************************************/

// memoized type contruction

property<AudioType*> MemoizedTypes;

Sym SIMPLETYPE = symbol("SimpleType");
Sym TABLETYPE  = symbol("TableType");
Sym TUPLETTYPE = symbol("TupletType");
Sym VECTORTYPE = symbol("VectorType");

static Tree codeSimpleType(SimpleType* st);
static Tree codeTableType(TableType* st);
static Tree codeTupletType(TupletType* st);
static Tree codeVectorType(VectorType* st);

/**
 * codeAudioType(Type) -> Tree
 * Code an audio type as a tree in order to benefit of memoization
 * The type field (of the coded type) is used to store the audio
 * type
 */
Tree codeAudioType(AudioType* t)
{
    SimpleType* st;
    TableType*  tt;
    TupletType* nt;
    VectorType* vt;

    Tree r;

    if ((r = t->getCode())) return r;

    if ((st = isSimpleType(t))) {
        r = codeSimpleType(st);
    } else if ((tt = isTableType(t))) {
        r = codeTableType(tt);
    } else if ((nt = isTupletType(t))) {
        r = codeTupletType(nt);
    } else if ((vt = isVectorType(t))) {
        r = codeVectorType(vt);
    } else {
        cerr << "ERROR in codeAudioType() : invalide pointer " << t << endl;
        exit(1);
    }

    r->setType(t);
    return r;
}

/**
 * Code a simple audio type as a tree in order to benefit of memoization
 */
static Tree codeSimpleType(SimpleType* st)
{
    vector<Tree> elems;
    elems.push_back(tree(st->nature()));
    elems.push_back(tree(st->variability()));
    elems.push_back(tree(st->computability()));
    elems.push_back(tree(st->vectorability()));
    elems.push_back(tree(st->boolean()));

    elems.push_back(tree(st->getInterval().valid));
    elems.push_back(tree(st->getInterval().lo));
    elems.push_back(tree(st->getInterval().hi));

    return CTree::make(SIMPLETYPE, elems);
}

AudioType* makeSimpleType(int n, int v, int c, int vec, int b, const interval& i)
{
    SimpleType prototype(n, v, c, vec, b, i);
    Tree       code = codeAudioType(&prototype);

    AudioType* t;
    if (MemoizedTypes.get(code, t)) {
        return t;
    } else {
        AudioType::gAllocationCount++;
        t = new SimpleType(n, v, c, vec, b, i);
        MemoizedTypes.set(code, t);
        t->setCode(code);
        return t;
    }
}

AudioType* makeSimpleType(const vector<int>& dim, int n, int v, int c, int vec, int b, const interval& i)
{
    AudioType* t = makeSimpleType(n, v, c, vec, b, i);
    if (dim.size() > 0) {
        return makeVectorType(t, dim);
    } else {
        return t;
    }
}
/**
 * Code a table type as a tree in order to benefit of memoization
 */

static Tree codeTableType(TableType* tt)
{
    return tree(TABLETYPE, codeAudioType(tt->content()));
}

AudioType* makeTableType(const Type& ct)
{
    TableType prototype(ct);
    Tree      code = codeAudioType(&prototype);

    AudioType* tt;
    if (MemoizedTypes.get(code, tt)) {
        return tt;
    } else {
        AudioType::gAllocationCount++;
        tt = new TableType(ct);
        MemoizedTypes.set(code, tt);
        tt->setCode(code);
        return tt;
    }
}

AudioType* makeTableType(const Type& ct, int n, int v, int c, int vec, int b, const interval& i)
{
    TableType prototype(ct, n, v, c, vec, b, i);
    Tree      code = codeAudioType(&prototype);

    AudioType* tt;
    if (MemoizedTypes.get(code, tt)) {
        return tt;
    } else {
        AudioType::gAllocationCount++;
        tt = new TableType(ct);
        MemoizedTypes.set(code, tt);
        tt->setCode(code);
        return tt;
    }
}

AudioType* makeTableType(const Type& ct, int n, int v, int c, int vec)
{
    TableType prototype(ct, n, v, c, vec);
    Tree      code = codeAudioType(&prototype);

    AudioType* tt;
    if (MemoizedTypes.get(code, tt)) {
        return tt;
    } else {
        AudioType::gAllocationCount++;
        tt = new TableType(ct);
        MemoizedTypes.set(code, tt);
        tt->setCode(code);
        return tt;
    }
}

/**
 * Code a tuplet type as a tree in order to benefit of memoization
 */

static Tree codeTupletType(TupletType* nt)
{
    vector<Tree> elems;
    for (int i = 0; i < nt->arity(); i++) {
        elems.push_back(codeAudioType((*nt)[i]));
    }
    return CTree::make(TUPLETTYPE, elems);
}

AudioType* makeTupletType(const vector<Type>& vt)
{
    TupletType prototype(vt);
    Tree       code = codeAudioType(&prototype);

    AudioType* t;
    if (MemoizedTypes.get(code, t)) {
        return t;
    } else {
        AudioType::gAllocationCount++;
        t = new TupletType(vt);
        MemoizedTypes.set(code, t);
        t->setCode(code);
        return t;
    }
}

AudioType* makeTupletType(const vector<Type>& vt, int n, int v, int c, int vec, int b, const interval& i)
{
    TupletType prototype(vt, n, v, c, vec, b, i);
    Tree       code = codeAudioType(&prototype);

    AudioType* t;
    if (MemoizedTypes.get(code, t)) {
        return t;
    } else {
        AudioType::gAllocationCount++;
        t = new TupletType(vt, n, v, c, vec, b, i);
        MemoizedTypes.set(code, t);
        t->setCode(code);
        return t;
    }
}

/**
 * Code a vector type as a tree in order to benefit of memoization
 */

static Tree codeVectorType(VectorType* vt)
{
    assert(vt);
    // cerr << "codeVectorType(" << *vt << ")" << endl;
    int i = vt->size();
    return tree(VECTORTYPE, tree(i), codeAudioType(vt->content()));
}

Type makeVectorType(const Type& b, const vector<int>& dim)
{
    Type r = b;
    for (unsigned int i = 0; i < dim.size(); i++) r = new VectorType(dim[i], r);
    return r;
}

/**
 * Returns true if D1 and D2 are compatible (one is the prefix of the other)).
 * In this case D3 contains the longuest vector D1 or D2
 */
bool maxdimensions(const vector<int>& D1, const vector<int>& D2, vector<int>& D3)
{
    unsigned int n1 = D1.size();
    unsigned int n2 = D2.size();
    unsigned int i  = 0;
    while ((i < n1) && (i < n2) && (D1[i] == D2[i])) i++;
    if (i == n1) {
        D3 = D2;
        return true;
    } else if (i == n2) {
        D3 = D1;
        return true;
    } else {
        return false;
    }
}
