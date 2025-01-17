#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "ppsig.hh"
#include "revealFIR.hh"
#include "sigFIR.hh"
#include "sigIIR.hh"
#include "sigIdentity.hh"

#define TRACE true

// Transform a signal expression by revealing FIR structures

// Tree revealIIR(Tree rt, Tree def);

class FIRRevealer : public SignalIdentity {
   protected:
    Tree postprocess(Tree L);
    Tree transformation(Tree L);
};

Tree FIRRevealer::transformation(Tree sig)
{
    Tree var, le;
    if (isRec(sig, var, le)) {
        Tree var2 = tree(unique("M"));
        Tree rec2 = rec(var2, gGlobal->nil);
        traceMsg("WARNING: We have set the definitions to nil for group", rec2);
        fResult.set(sig, rec2);     // We rename the recgroup
        Tree l2   = mapself(le);    // We transfom its definitions
        Tree rec3 = rec(var2, l2);  // We update the definition
        traceMsg("WARNING: We have updated the definitions of group", rec3);
        return rec3;

    } else {
        return SignalIdentity::transformation(sig);
    }
}

Tree FIRRevealer::postprocess(Tree sig)
{
    Tree x, y;
    if (isSigDelay(sig, x, y) && isSigIIR(x) && isZero(y)) {
        return x;
    } else if (isSigDelay(sig, x, y) && isZero(x)) {
        return x;
    } else if (isSigDelay(sig, x, y)) {
        return delaySigFIR(x, y);
    } else if (isSigAdd(sig, x, y)) {
        // return smartAddSigFIR(x, y);
        return combineFIRs(x, y, false);
    } else if (isSigSub(sig, x, y)) {
        // return smartAddSigFIR(x, negSigFIR(y));
        return combineFIRs(x, y, true);
    } else if (isSigMul(sig, x, y)) {
        return mulSigFIR(x, y);
    } else if (isSigDiv(sig, x, y)) {
        return divSigFIR(x, y);
    } else {
        return sig;
    }
}

// External API

Tree revealFIR(Tree L1)
{
    FIRRevealer R;
    R.trace(TRACE, "revealFIR");
    Tree L2 = R.mapself(L1);
    return L2;
}
