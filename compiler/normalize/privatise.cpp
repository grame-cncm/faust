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
#include "compatibility.hh"
#include <stdio.h>

#include "sigprint.hh"
#include "sigtyperules.hh"
#include "privatise.hh"
#include "exception.hh"
#include "global.hh"

/*****************************************************************************
						 privatise : compile a list of signals
*****************************************************************************/

static Tree makePrivatisationKey(const Tree& t);
static Tree makePrivatisationLabel(const Tree& exp);

static Tree privatisation (const Tree& k, const Tree& t);
static Tree computePrivatisation (const Tree& k, const Tree& t);
static Tree labelize(const Tree& label, const Tree& exp);

Tree privatise(const Tree& t)
{
	return privatisation(makePrivatisationKey(t), t);
}

// -- implementation -----------------

static Tree makePrivatisationKey(const Tree& t)
{
	char 	name[256];
	snprintf(name, 256, "PRIVATISE %p : ", (void *)(CTree*)t);
	return tree(unique(name));
}

static Tree makePrivatisationLabel(const Tree& t)
{
	char 	name[256];
	snprintf(name, 256, "OWNER IS %p : ", (void *)(CTree*)t);
	return tree(unique(name));
}


// -- implementation -----------------

static Tree privatisation (const Tree& k, const Tree& t)
{
	Tree v;

	if (t->arity() == 0) {
		return t;

	} else if (getProperty(t, k, v)) {
		/*	Terme deja visité. La propriété nous indique
			la version privatisée ou nil si elle est identique
			au terme initial.
		*/
		return isNil(v) ? t : v;

	} else {
		/*	Calcul du terme privatisé et mis à jour
			de la propriété. Nil indique que le terme
			privatisé est identique à celui de depart
			(pour eviter les boucles avec les compteurs
			de references)
		*/
		v = computePrivatisation(k,t);
		if (v != t) {
			setProperty(t, k, v );
		} else {
			setProperty(t, k, gGlobal->nil);
		}
		return v;
	}
}

static Tree computePrivatisation(const Tree& k, const Tree& exp)
{
	Tree	tbl, size, idx, wrt, content, id, var, body;

	if ( isSigWRTbl(exp, id, tbl, idx, wrt) ) 	{
		/*	Ce qui ne peut pas être partagé, ce sont les
			tables dans lesquelles on ecrit. Pour cela
			on leur donne un label unique
		*/
		return sigWRTbl(
					id,
					labelize( makePrivatisationLabel(exp), privatisation(k, tbl) ),
					privatisation(k, idx),
					privatisation(k, wrt) );

	} else if ( isSigTable(exp, id, size, content) ) {
		/*	Rien à privatiser dans une table (car size est
			censée etre une expression entiere)
		*/
		return exp;

	} else if ( isSigGen(exp, content) ) {
		/*	On ne visite pas les contenus des tables
		*/
	    throw faustexception("ERROR 1 in computePrivatisation");

	} else if ( isRec(exp, var, body) ) {
		/*	On ne visite pas les contenus des tables
		*/
		setProperty(exp, k, gGlobal->nil);
		return rec(var, privatisation(k,body));

	} else {
		/*	On parcours les autres arbres en privatisant les branches
		*/

        tvec br;
        int n = exp->arity();
        for (int i = 0; i < n; i++) {
            br.push_back( privatisation(k,exp->branch(i)) );
        }

        return tree(exp->node(), br);

    }
}

static Tree labelize(const Tree& newid, const Tree& exp)
{
	Tree	tbl, size, idx, wrt, content, oldid;

	if ( isSigWRTbl(exp, oldid, tbl, idx, wrt) ) 	{
		/*	Ce qui ne peut pas être partagé, ce sont les
			tables dans lesquelles on ecrit. Pour cela
			on leur donne un label unique
		*/
		return sigWRTbl(newid, tbl, idx, wrt);

	} else  if ( isSigTable(exp, oldid, size, content) ) {
		/*	Rien à privatiser dans une table (car size est
			censée etre une expression entiere)
		*/
		return sigTable(newid, size, content);

	} else {
        throw faustexception("ERROR labelize");
	}

	return exp;
}

