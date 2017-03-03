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

/**
 * \file eval.cpp
 * Interface for names propagation.
 *
 **/

#include "ppsig.hh"
#include "names.hh"
#include "property.hh"
#include "ppsig.hh"
#include "doc_Text.hh"
#include "Text.hh"
#include "global.hh"
#include "exception.hh"

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
	//cerr << "setDefNameProperty : " << *id << " FOR " << t << "#" << boxpp(t) << endl;
	setProperty(t, gGlobal->DEFNAMEPROPERTY, id);
}

void setDefNameProperty(Tree t, const string& name)
{
	//cerr << "setDefNameProperty : " << name << " FOR " << t << "#" << boxpp(t) << endl;
	int		n = (int)name.size();
	int 	m = (gGlobal->gMaxNameSize>1023) ? 1023 : gGlobal->gMaxNameSize;

	if (n > m) {
		// the name is too long we reduce it to 2/3 of maxsize
		char 	buf[1024];
		int i = 0;
		// copy first third
		for (; i < m/3; i++) { buf[i] = name[i]; }
		// add ...
		buf[i++] = '.';
		buf[i++] = '.';
		buf[i++] = '.';
		// copy last third
		for (int c = n-m/3; c<n; c++, i++) { buf[i] = name[c]; }
		buf[i] = 0;
		setProperty(t, gGlobal->DEFNAMEPROPERTY, tree(buf));
	} else {
		setProperty(t, gGlobal->DEFNAMEPROPERTY, tree(name.c_str()));
	}
}

bool getDefNameProperty(Tree t, Tree& id)
{
	//cerr << "getDefNameProperty of : " << t << endl;
	return getProperty(t, gGlobal->DEFNAMEPROPERTY, id);
}


/**
 * Convert a definition name (can be long) into a short nickname
 * that can be used as an equation name in latex
 * @todo Simplify long definition names.
 */
string defName2NickName (const string& defname)
{
	return defname;
}

/**
 * Set the nickname property of a signal
 */
void setSigNickname(Tree t, const string& id)
{
	Tree 	s,d;
	if (isSigFixDelay(t,s,d) && isZero(d)) {
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
void setSigListNickName (Tree  lsig, const string& nickname)
{
	faustassert(isList(lsig));
	
	if (isNil(tl(lsig))) {
		setSigNickname(hd(lsig), nickname);
	} else {
		int 	i=0;
		while (!isNil(lsig)) {
			setSigNickname(hd(lsig), subst("$0_$1", nickname, T(++i)));
			lsig = tl(lsig);
		}
	}
}




