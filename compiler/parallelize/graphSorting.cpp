#include <set>
#include "graphSorting.hh"

/**
 * Set the order of a loop and place it to appropriate set
 */
static void setOrder(Loop* l, int order, lgraph& V)
{
    assert(l);
    //cout << "ENTER SETORDER " << order << " (" << l->fOrder << ")" << endl;
    V.resize(order+1);
    if (l->fOrder >= 0) { V[l->fOrder].erase(l); }
    l->fOrder = order; V[order].insert(l);
    //cout << "EXIT SETORDER "<< endl;
}

/**
 * Set the order of T1's loops and collect there sons into T2
 */
static void setLevel(int order, const lset& T1, lset& T2, lgraph& V)
{
    //cout << "ENTER SETLEVEL" << endl;
    for (lset::const_iterator p = T1.begin(); p!=T1.end(); p++) {
        setOrder(*p, order, V);
        T2.insert((*p)->fLoopDependencies.begin(), (*p)->fLoopDependencies.end());
    }
    //cout << "EXIT SETLEVEL" << endl;
}

/**
 * Topological sort of an acyclic graph of loops. The loops
 * are collect in an lgraph : a vector of sets of loops
 */
void sortGraph(Loop* root, lgraph& V)
{
    lset            T1, T2;
    int             level;
    
    assert(root);
    //cout << "START ordering" << endl;
    T1.insert(root); level=0; V.clear();
    do {
        setLevel(level, T1, T2, V); 
        T1=T2; T2.clear(); level++;
    } while (T1.size()>0);
    //cout << "END ordering " << level << endl;
}
