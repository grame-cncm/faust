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

#ifndef __PROPERTY__
#define __PROPERTY__

#include "tree.hh"
#include "garbageable.hh"

template<class P> class property : public virtual Garbageable
{
    Tree	fKey;

    P*	access(Tree t)
    {
        Tree d = t->getProperty(fKey);
        return d ? (P*)(d->node().getPointer()) : 0;
    }

public:

    property () : fKey(tree(Node(unique("property_")))) {}

    property (const char* keyname) : fKey(tree(Node(keyname))) {}
  
    void set(Tree t, const P& data)
    {
        P* p = access(t);
        if (p) {
            *p = data;
        } else {
            t->setProperty(fKey, tree(Node((new GarbageablePtr<P>(data))->getPointer())));
        }
    }

    bool get(Tree t, P& data)
    {
        P* p = access(t);
        if (p) {
            data = *p;
            return true;
        } else {
            return false;
        }
    }

    void clear(Tree t)
    {
        P* p = access(t);
        if (p) { delete p; }
        t->clearProperty(fKey);
    }
};

template<> class property<Tree> : public virtual Garbageable
{
    Tree	fKey;

public:

    property () : fKey(tree(Node(unique("property_")))) {}

    property (const char* keyname) : fKey(tree(Node(keyname))) {}

    void set(Tree t, Tree data)
    {
        t->setProperty(fKey, data);
    }

    bool get(Tree t, Tree& data)
    {
        Tree d = t->getProperty(fKey);
        if (d) {
            data = d;
            return true;
        } else {
            return false;
        }
    }

    void clear(Tree t)
    {
        t->clearProperty(fKey);
    }
};

template<> class property<int> : public virtual Garbageable
{
    Tree	fKey;

public:

    property () : fKey(tree(Node(unique("property_")))) {}

    property (const char* keyname) : fKey(tree(Node(keyname))) {}

    void set(Tree t, int i)
    {
        t->setProperty(fKey, tree(Node(i)));
    }

    bool get(Tree t, int& i)
    {
        Tree d = t->getProperty(fKey);
        if (d) {
            i = d->node().getInt();
            return true;
        } else {
            return false;
        }
    }

    void clear(Tree t)
    {
        t->clearProperty(fKey);
    }
};

template<> class property<double> : public virtual Garbageable
{
    Tree	fKey;

public:

    property () : fKey(tree(Node(unique("property_")))) {}

    property (const char* keyname) : fKey(tree(Node(keyname))) {}

    void set(Tree t, double x)
    {
        t->setProperty(fKey, tree(Node(x)));
    }

    bool get(Tree t, double& x)
    {
        Tree d = t->getProperty(fKey);
        if (d) {
            x = d->node().getDouble();
            return true;
        } else {
            return false;
        }
    }

    void clear(Tree t)
    {
        t->clearProperty(fKey);
    }
};

#endif
