#include <iostream>
#include <string>

#include "Schedule.hh"
#include "global.hh"
#include "ppsig.hh"
#include "sigDependenciesGraph.hh"
#include "sigIdentity.hh"
#include "sigNewConstantPropagation.hh"
#include "signals.hh"
#include "sigtyperules.hh"

class SigNewConstantPropagation final : public SignalIdentity {
   protected:
    Tree transformation(Tree sig) override;
};
static void explainInterval(Tree sig)
{
    digraph<Tree>  G = fullGraph(list1(sig));
    schedule<Tree> S = dfcyclesschedule(G);
    int            i = 0;
    std::cerr << "\n\n EXPLAIN INTERVAL: " << getCertifiedSigType(sig)->getInterval() << " FOR SIGNAL " << sig << " = " << ppsig(sig, 10) << std::endl;
    for (Tree s : S.elements()) {
        Type Ty = getSigType(sig);
        if (Ty.pointee() == nullptr) {
            std::cerr << "\n" << ++i << "@" << s << " : " << "NOTYPE" << "; sig = " << ppsig(s, 10) << std::endl;
        } else {
            std::cerr << "\n" << ++i << "@" << s << " : " << Ty->getInterval() << "; sig = " << ppsig(s, 10) << std::endl;
        }
    }
}

Tree SigNewConstantPropagation::transformation(Tree sig)
{
    Type     tt = getCertifiedSigType(sig);
    interval I  = tt->getInterval();

    Tree res;
    if (I.isconst()) {
        if (tt->nature() == kInt) {
            res = sigInt(int(I.lo()));
        } else {
            res = sigReal(I.lo());
        }
    } else {
        res = SignalIdentity::transformation(sig);
    }
    // if (res != sig) {
    //     std::cerr << "\n\nConstant propagation: " << ppsig(sig, 10) << " ==> " << ppsig(res, 10) << std::endl;
    //     explainInterval(sig);
    // }
    return res;
}

/**
 * @brief
 *
 * @param sig
 * @param trace
 * @return Tree
 */
Tree newConstantPropagation(Tree sig, bool trace)
{
    SigNewConstantPropagation cp;
    cp.trace(trace);

    if (isList(sig)) {
        return cp.mapself(sig);
    } else {
        return cp.self(sig);
    }
}
