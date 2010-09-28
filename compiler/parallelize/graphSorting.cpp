#include <set>
#include "graphSorting.hh"
#include "code_container.hh"

/**
 * Set the order of a loop and place it to appropriate set
 */
static void setOrder(Loop* l, int order, lgraph& V)
{
    assert(l);
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

static void resetOrder(Loop* l)
{
    l->fOrder = -1;
    for (lset::const_iterator p = l->fBackwardLoopDependencies.begin(); p!=l->fBackwardLoopDependencies.end(); p++) {
        resetOrder(*p);
    }
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
    resetOrder(root);
    T1.insert(root); level=0; V.clear();
    do {
        setLevel(level, T1, T2, V); 
        T1=T2; T2.clear(); level++;
    } while (T1.size()>0);
    
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

/**
 * Compute how many time each loop is used in a DAG
 */
void computeUseCount(Loop* l)
{
	l->fUseCount++;
	if (l->fUseCount == 1) {
		for (lset::iterator p =l->fBackwardLoopDependencies.begin(); p!=l->fBackwardLoopDependencies.end(); p++) {
		    computeUseCount(*p);
		}
	}
}

/**
 * Group together sequences of loops
 */
void groupSeqLoops(Loop* l)
{
	int n = l->fBackwardLoopDependencies.size();
	if (n == 0) {
		return;
	} else if (n == 1) {
		Loop* f = *(l->fBackwardLoopDependencies.begin());
		if (f->fUseCount ==  1) {
			l->concat(f);
			groupSeqLoops(l);
		} else {
			groupSeqLoops(f);
		}
		return;
	} else if (n > 1) {
		for (lset::iterator p =l->fBackwardLoopDependencies.begin(); p!=l->fBackwardLoopDependencies.end(); p++) {
			groupSeqLoops(*p);
		}
	}
}

