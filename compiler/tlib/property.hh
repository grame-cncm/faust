#ifndef __PROPERTY__
#define __PROPERTY__

#include "tree.hh"

template<class P> class property
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
            t->setProperty(fKey, tree(Node(new P(data))));
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


template<> class property<Tree>
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


template<> class property<int>
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


template<> class property<double>
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
