#ifndef SIGRATERULES_HH
#define SIGRATERULES_HH

#include <iostream>
#include "property.hh"
#include "tlib.hh"

class RateInferrer {
    bool          fSuccess;       ///< true when rates can be correctly inferred
    Tree          fFullList;      ///< list of signals + list recursive signals inside
    Tree          fRateEnv;       ///< list of signals + list recursive signals inside
    property<int> fRateProperty;  ///< property used to store the rate of signals

    int fCommonRate;  ///< lcm of all rates

    int computeRate(Tree sig);

   public:
    RateInferrer(Tree lsig);  ///< list of signals we want to inferre the rates
    int    rate(Tree sig);    ///< returns the rate of sig assuming that sig is a subexpression of lsig
    string clock(Tree sig);   ///< returns sig's C clock expression : C_{r_i}(t) = (t*r_i)/r_c
    string tick(Tree sig);    ///< returns sig's C tick expression  : T_{r_i}(t) = ((t % (r_c/r_i)) == 0)
    int    commonRate();      ///< returns the least common multiple rate

    int periodicity(Tree sig)
    {
        int r = rate(sig);
        return fCommonRate / r;
    }
};

#endif  // SIGRATERULES_HH
