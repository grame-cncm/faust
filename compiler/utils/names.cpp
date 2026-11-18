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

/**
 * \file eval.cpp
 * Interface for names propagation.
 *
 **/

#include <algorithm>

#include "Text.hh"
#include "doc_Text.hh"
#include "exception.hh"
#include "global.hh"
#include "names.hh"
#include "ppsig.hh"
#include "property.hh"

using namespace std;

// History
// 2009/09/08 : get/setDefNameProperty

/**
 * Definition name property : a property to keep track of the definition name
 * of an expression. Whenever an identifier is evaluated, it is attached as a
 * property of its definition. Obviously there is no perfect solution since a same
 * definition can be given to different names.
 */

void setDefNameProperty(Tree t, Tree id)
{
    // cerr << "setDefNameProperty : " << *id << " FOR " << t << "#" << boxpp(t) << endl;
    setProperty(t, gGlobal->DEFNAMEPROPERTY, id);
    // remember when the name was given, see defNameStamp()
    Tree stamp = tree(Node(int(gGlobal->gDefNameCount++)));
    setProperty(t, gGlobal->DEFNAMESTAMP, stamp);
}

// The name as a tree, reduced when it is too long
static Tree defNameTree(const string& name)
{
    int n = (int)name.size();
    int m = std::min<int>(1023, gGlobal->gMaxNameSize);

    if (n > m) {
        // the name is too long we reduce it to 2/3 of maxsize
        char buf[1024];
        int  i = 0;
        // copy first third
        for (; i < m / 3; i++) {
            buf[i] = name[i];
        }
        // add ...
        buf[i++] = '.';
        buf[i++] = '.';
        buf[i++] = '.';
        // copy last third
        for (int c = n - m / 3; c < n; c++, i++) {
            buf[i] = name[c];
        }
        buf[i] = 0;
        return tree(buf);
    } else {
        return tree(name.c_str());
    }
}

void setDefNameProperty(Tree t, const string& name)
{
    // cerr << "setDefNameProperty : " << name << " FOR " << t << "#" << boxpp(t) << endl;
    setDefNameProperty(t, defNameTree(name));
}

size_t defNameStamp()
{
    return gGlobal->gDefNameCount;
}

// A mark holds the name it was given for: it no longer applies once the tree is renamed
static bool isMarked(Tree t, Tree mark)
{
    Tree marked, id;
    return getProperty(t, mark, marked) && getDefNameProperty(t, id) && marked == id;
}

static void markName(Tree t, Tree mark)
{
    Tree id;
    if (getDefNameProperty(t, id)) {
        setProperty(t, mark, id);
    }
}

void setDefNameProperty(Tree t, Tree id, size_t stamp, bool uncertain)
{
    // A tree that is the value of independent definitions stays so when it is renamed
    bool shared = isMarked(t, gGlobal->DEFNAMESHARED);
    Tree old, given;
    if (!shared && getDefNameProperty(t, old) && old != id) {
        // a name given before <stamp> comes from a definition evaluated independently
        shared = !getProperty(t, gGlobal->DEFNAMESTAMP, given) || size_t(tree2int(given)) < stamp;
    }
    // otherwise <t> keeps a name given during its computation, by a definition nested in
    // the one named <id> : <id> replaces it, and an uncertain old name does not matter
    setDefNameProperty(t, id);
    if (shared) {
        markName(t, gGlobal->DEFNAMESHARED);
    } else if (uncertain) {
        markName(t, gGlobal->DEFNAMEUNCERTAIN);
    }
}

void setDefNameProperty(Tree t, const string& name, size_t stamp, bool uncertain)
{
    setDefNameProperty(t, defNameTree(name), stamp, uncertain);
}

void transferDefNameProperty(Tree src, Tree dst, size_t stamp)
{
    Tree id;
    if (getDefNameProperty(src, id)) {
        setDefNameProperty(dst, id, stamp, isDefNameAmbiguous(src));
    }
}

void checkDefNameProperty(Tree src, Tree dst)
{
    Tree id, old;
    if (getDefNameProperty(src, id) && getDefNameProperty(dst, old) && old != id) {
        markName(dst, gGlobal->DEFNAMESHARED);
    }
}

bool isDefNameAmbiguous(Tree t)
{
    return isMarked(t, gGlobal->DEFNAMESHARED) || isMarked(t, gGlobal->DEFNAMEUNCERTAIN);
}

LIBFAUST_API bool getDefNameProperty(Tree t, Tree& id)
{
    // cerr << "getDefNameProperty of : " << t << endl;
    return getProperty(t, gGlobal->DEFNAMEPROPERTY, id);
}

/**
 * Convert a definition name (can be long) into a short nickname
 * that can be used as an equation name in latex
 * @todo Simplify long definition names.
 */
string defName2NickName(const string& defname)
{
    return defname;
}

/**
 * Set the nickname property of a signal
 */
void setSigNickname(Tree t, const string& id)
{
    Tree s, d;
    if (isSigDelay(t, s, d) && isZero(d)) {
        setProperty(s, gGlobal->NICKNAMEPROPERTY, tree(id));
    } else {
        setProperty(t, gGlobal->NICKNAMEPROPERTY, tree(id));
    }
}

/**
 * Get the nickname property of a signal
 */
bool getSigNickname(Tree t, Tree& id)
{
    bool r = getProperty(t, gGlobal->NICKNAMEPROPERTY, id);
    return r;
}

/**
 * set the nickname property of a list of signals. If the list
 * contains more than one signal, adds an index to the nickname
 */
void setSigListNickName(Tree lsig, const string& nickname)
{
    faustassert(isList(lsig));

    if (isNil(tl(lsig))) {
        setSigNickname(hd(lsig), nickname);
    } else {
        int i = 0;
        while (!isNil(lsig)) {
            setSigNickname(hd(lsig), subst("$0_$1", nickname, T(++i)));
            lsig = tl(lsig);
        }
    }
}
