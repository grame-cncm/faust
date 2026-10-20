/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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

#include "valueOrder.hh"

#include <cstring>

namespace {

// the comparison goes no deeper : beyond, the order of creation decides
const int kDepth = 16;

int creationCompare(Tree a, Tree b)
{
    return treeorder()(a, b) ? -1 : 1;
}

// the numbers first, then the symbols, then the pointers
int kindRank(const Node& n)
{
    switch (n.type()) {
        case kIntNode:
        case kInt64Node:
        case kDoubleNode:
            return 0;
        case kSymNode:
            return 1;
        default:
            return 2;
    }
}

double numberValue(const Node& n)
{
    switch (n.type()) {
        case kIntNode:
            return double(n.getInt());
        case kInt64Node:
            return double(n.getInt64());
        default:
            return n.getDouble();
    }
}

int compare(Tree a, Tree b, int depth)
{
    if (a == b) {
        return 0;
    }
    Tree var, body;
    if (depth > kDepth || isRec(a, var, body) || isRec(b, var, body)) {
        return creationCompare(a, b);
    }
    const Node& na = a->node();
    const Node& nb = b->node();
    const int   ka = kindRank(na);
    const int   kb = kindRank(nb);
    if (ka != kb) {
        return (ka < kb) ? -1 : 1;
    }
    if (ka == 0) {
        const double va = numberValue(na);
        const double vb = numberValue(nb);
        if (va != vb) {
            return (va < vb) ? -1 : 1;
        }
        if (na.type() != nb.type()) {
            return (na.type() < nb.type()) ? -1 : 1;
        }
    } else if (ka == 1) {
        const int c = std::strcmp(name(na.getSym()), name(nb.getSym()));
        if (c != 0) {
            return (c < 0) ? -1 : 1;
        }
    } else {
        return creationCompare(a, b);
    }
    if (a->arity() != b->arity()) {
        return (a->arity() < b->arity()) ? -1 : 1;
    }
    for (int i = 0; i < a->arity(); i++) {
        const int c = compare(a->branch(i), b->branch(i), depth + 1);
        if (c != 0) {
            return c;
        }
    }
    return creationCompare(a, b);
}

}  // namespace

int valueCompare(Tree a, Tree b)
{
    return compare(a, b, 0);
}
