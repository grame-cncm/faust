#ifndef __OCCURENCES__
#define __OCCURENCES__

#include "sigraterules.hh"
#include "tlib.hh"

/**
 * Statistics about the various occurences of a signal in a global root signal
 */

class Occurences {
    const int fXVariability;   ///< Extended Variability of the expression
    int       fOccurences[4];  ///< Occurences count according to Contexts
    bool      fMultiOcc;       ///< True when exp has multiple occ. or occ. in higher ctxt
    bool      fOutDelayOcc;    ///< True when exp has at least one occ. outside a delay
    int       fMinDelay;       ///< Minimal fix delay usage
    int       fMaxDelay;       ///< Maximal fix delay usage
    int       fMinRate;        ///< Minimal rate usage
    int       fMaxRate;        ///< Maximal rate usage

   public:
    Occurences(int rate, int v, int r);

    Occurences* incOccurences(int rate, int v, int r, int d);  ///< inc occurences in context rate,v,r,d

    bool hasMultiOccurences() const;     ///< true if multiple occurences or occ. in higher ctxt
    bool hasOutDelayOccurences() const;  ///< true if has occurences outside a a delay
    int  getMaxDelay() const;            ///< return the maximal delay collected
    int  getMinDelay() const;            ///< return the minimal delay collected
    int  getMaxRate() const;             ///< return the maximal delay collected
    int  getMinRate() const;             ///< return the minimal delay collected
};

/**
 * Occurences Markup of a root tree. First create an OccMarkup om,
 * second om.mark(root) then om.retrieve(subtree)
 */
class OccMarkup {
    Tree          fRootTree;  ///< occurences computed within this tree
    Tree          fPropKey;   ///< key used to store occurences property
    RateInferrer* fRates;     ///< rate information

    void        incOcc(int rate, int v, int r, int d, Tree t);  ///< inc the occurence of t in context rate,v,r,d
    Occurences* getOcc(Tree t);                                 ///< get Occurences property of t or null
    void        setOcc(Tree t, Occurences* occ);                ///< set Occurences property of t

   public:
    void        markOccurences(RateInferrer* R, Tree root);  ///< start markup of root tree with new unique key
    Occurences* retrieveOccurences(Tree t);                  ///< occurences of subtree t within root tree
};

#endif
