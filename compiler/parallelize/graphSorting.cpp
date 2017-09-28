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

#include <set>
#include "graphSorting.hh"

/**
 * Set the order of a loop and place it to appropriate set
 */
static void setOrder(Loop* l, int order, lgraph& V)
{
    faustassert(l);
    V.resize(order+1);
    if (l->fOrder >= 0) { V[l->fOrder].erase(l); }
    l->fOrder = order; V[order].insert(l);
}

/**
 * Set the order of T1's loops and collect there sons into T2
 */
static void setLevel(int order, const lset& T1, lset& T2, lgraph& V)
{
    for (lset::const_iterator p = T1.begin(); p!=T1.end(); p++) {
        setOrder(*p, order, V);
        T2.insert((*p)->fBackwardLoopDependencies.begin(), (*p)->fBackwardLoopDependencies.end());
    }
}

static void resetOrder(Loop* l, set<Loop*>& visited)
{
    // Not yet visited...
    if (visited.find(l) == visited.end()) {
        visited.insert(l);
        l->fOrder = -1;
        for (lset::const_iterator p = l->fBackwardLoopDependencies.begin(); p != l->fBackwardLoopDependencies.end(); p++) {
            resetOrder(*p, visited);
        }
    }
}

/**
 * Topological sort of an acyclic graph of loops. The loops
 * are collect in an lgraph : a vector of sets of loops
 */
void sortGraph(Loop* root, lgraph& V)
{
    faustassert(root);
    set<Loop*> visited;
    resetOrder(root, visited);
    
    lset T1, T2;
    T1.insert(root);
    int level = 0;
    V.clear();
    
    do {
        setLevel(level, T1, T2, V); 
        T1 = T2; T2.clear(); level++;
    } while (T1.size() > 0);
    
    // Erase empty levels
    lgraph::iterator p = V.begin();
    while (p != V.end()) {
        if ((*p).size() == 1 && (*(*p).begin())->isEmpty()) {
            p = V.erase(p);
        } else {
            p++; 
        }
    }
}
