#ifndef __OCCURENCES__
#define __OCCURENCES__

#include <map>
#include "tlib.hh"

using namespace std;

class Occurences
{
	const int 	fXVariability;		///< Extended Variability of the expression
	int			fOccurences[4];		///< Occurences count according to Contexts
	bool		fMultiOcc;			///< True when exp has multiple occ. or occ. in higher ctxt
	bool		fOutDelayOcc;		///< True when exp has at least one occ. outside a delay
    int			fMinDelay;			///< Minimal fix delay usage
    int			fMaxDelay;			///< Maximal fix delay usage
    Tree        fExecCondition;     ///< When this expression must be computed

 public:
    Occurences(int v, int r, Tree xc);

    Occurences* incOccurences(int v, int r, int d, Tree xc);	///< inc occurences in context v,r,d,xc
	
	bool 		hasMultiOccurences() const;			///< true if multiple occurences or occ. in higher ctxt
	bool 		hasOutDelayOccurences() const;		///< true if has occurences outside a a delay
    int			getMaxDelay() const;				///< return the maximal delay collected
    int			getMinDelay() const;				///< return the minimal delay collected
    Tree        getExecCondition() const;           ///< return the exec condition
};


/**
 * Occurences Markup of a root tree. First create an OccMarkup om,
 * second om.mark(root) then om.retrieve(subtree)
 */
class OccMarkup
{
    Tree                        fRootTree;				///< occurences computed within this tree
    Tree                        fPropKey;				///< key used to store occurences property
    map<Tree, Tree>   fConditions;            ///< condition associated to each tree

    void 		incOcc (Tree env, int v, int r, int d, Tree xc, Tree t);	///< inc the occurence of t in context v,r
	Occurences* getOcc (Tree t);						///< get Occurences property of t or null
	void 		setOcc (Tree t, Occurences* occ);		///< set Occurences property of t

 public:

    OccMarkup() {}
    OccMarkup(map<Tree, Tree> conditions) : fConditions(conditions) {}

 	void 		mark(Tree root);						///< start markup of root tree with new unique key
	Occurences* retrieve(Tree t);						///< occurences of subtree t within root tree
};



#endif
