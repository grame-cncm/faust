/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include <stdio.h>
#include "compatibility.hh"
#include "sigtype.hh"

#include "exception.hh"
#include "global.hh"
#include "privatise.hh"
#include "sigprint.hh"
#include "sigtyperules.hh"

/*****************************************************************************
                         privatise : compile a list of signals
*****************************************************************************/

static Tree makePrivatisationKey(const Tree& t);
static Tree makePrivatisationLabel(const Tree& exp);

static Tree privatisation(const Tree& k, const Tree& t);
static Tree computePrivatisation(const Tree& k, const Tree& t);
static Tree labelize(const Tree& label, const Tree& exp);

Tree privatise(const Tree& t)
{
    return privatisation(makePrivatisationKey(t), t);
}

// -- implementation -----------------

static Tree makePrivatisationKey(const Tree& t)
{
    char name[256];
    snprintf(name, 256, "PRIVATISE %p : ", (void*)(CTree*)t);
    return tree(unique(name));
}

static Tree makePrivatisationLabel(const Tree& t)
{
    char name[256];
    snprintf(name, 256, "OWNER IS %p : ", (void*)(CTree*)t);
    return tree(unique(name));
}

// -- implementation -----------------

static Tree privatisation(const Tree& k, const Tree& t)
{
    Tree v;

    if (t->arity() == 0) {
        return t;

    } else if (getProperty(t, k, v)) {
        /*
         Already visited Term. The property indicates us
         the privatized version or nil if it is identical
         to the initial term.
        */
        return isNil(v) ? t : v;

    } else {
        /*
         Computation of the privatized and update the property.
         Nil indicates that the privatized term is identical
         to the one we start with (to avoid loops with reference counters).
        */
        v = computePrivatisation(k, t);
        if (v != t) {
            setProperty(t, k, v);
        } else {
            setProperty(t, k, gGlobal->nil);
        }
        return v;
    }
}

static Tree computePrivatisation(const Tree& k, const Tree& exp)
{
    Tree tbl, size, idx, wrt, content, id, var, body;

    if (isSigWRTbl(exp, id, tbl, idx, wrt)) {
        /*
         What cannot be shared are the tables in which
         we write. For this purpose we give them a unique label.
        */
        return sigWRTbl(id, labelize(makePrivatisationLabel(exp), privatisation(k, tbl)), privatisation(k, idx),
                        privatisation(k, wrt));

    } else if (isSigTable(exp, id, size, content)) {
        /*
         Nothing to privatize in a table (because size is supposed to
         be an integer expression)
        */
        return exp;

    } else if (isSigGen(exp, content)) {
        /*
         We do not visit the contents of the tables.
         */
        throw faustexception("ERROR : computePrivatisation");

    } else if (isRec(exp, var, body)) {
        /*
         We do not visit the contents of the tables.
         */
        setProperty(exp, k, gGlobal->nil);
        return rec(var, privatisation(k, body));

    } else {
        /*
         We go through the other trees by privatizing the branches
         */

        tvec br;
        int  n = exp->arity();
        for (int i = 0; i < n; i++) {
            br.push_back(privatisation(k, exp->branch(i)));
        }

        return tree(exp->node(), br);
    }
}

static Tree labelize(const Tree& newid, const Tree& exp)
{
    Tree tbl, size, idx, wrt, content, oldid;

    if (isSigWRTbl(exp, oldid, tbl, idx, wrt)) {
        /*
         What cannot be shared are the tables in which
         we write. For this purpose we give them a unique label.
        */
        return sigWRTbl(newid, tbl, idx, wrt);

    } else if (isSigTable(exp, oldid, size, content)) {
        /*
         Nothing to privatize in a table (because size is supposed to
         be an integer expression).
        */
        return sigTable(newid, size, content);

    } else {
        throw faustexception("ERROR : labelize");
    }

    return exp;
}
