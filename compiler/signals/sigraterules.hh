#ifndef SIGRATERULES_HH
#define SIGRATERULES_HH

#include <iostream>
#include "tlib.hh"
#include "property.hh"


class RateInferrer
{
    bool            fSuccess;       ///< true when rates can be correctly inferred
    Tree            fFullList;      ///< list of signals + list recursive signals inside
    Tree            fRateEnv;       ///< list of signals + list recursive signals inside
    property<int>   fRateProperty;  ///< property used to store the rate of signals
    
    int             fCommonRate;    ///< lcm of all rates

    int computeRate(Tree sig);
public:
    RateInferrer(Tree lsig);        ///< list of signals we want to inferre the rates
    int rate(Tree sig);             ///< returns the rate of sig assuming that sig is a subexpression of lsig
    int commonRate();               ///< returns the least common multiple rate
    
    int periodicity(Tree sig)       { int r = rate(sig); return fCommonRate/r; }

};

#endif // SIGRATERULES_HH
