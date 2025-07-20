#include "DependenciesUtils.hh"
#include "ppsig.hh"

/**
 * @brief Checks if a signal requires a separate subgraph for scheduling.
 *
 * This is typically the case for on-demand signals (OD, US, DS).
 *
 * @param sig The signal to check.
 * @param clk Reference to a Tree where the clock of the subgraph will be stored if needed.
 * @return True if a subgraph is needed, false otherwise.
 */
bool needSubGraph(Tree sig, Tree& clk)
{
    if (tvec V; isSigOD(sig, V) || isSigUS(sig, V) || isSigDS(sig, V)) {
        clk = V[0];
        return true;
    }
    return false;
}

/**
 * @brief Checks if a signal is external to the current clock environment.
 *
 * A signal is considered external if it belongs to a different clock domain.
 *
 * @param clkenv The current clock environment.
 * @param sig The signal to check.
 * @return True if the signal is external, false otherwise.
 */
bool isExternal(Tree clkenv, Tree sig)
{
    // Tempvar can be external
    if (Tree content; isSigTempVar(sig, content)) {
        Tree clk2, sig2;
        faustassert(isSigClocked(content, clk2, sig2));
        return clk2 != clkenv;
    }

    // Clocked signals can be external
    if (Tree clk2, sig2; isSigClocked(sig, clk2, sig2)) {
        return clk2 != clkenv;
    }

    // Otherwise it's an internal signal
    return false;
}

/**
 * @brief Checks if a signal is a control signal.
 *
 * Control signals have a variability less than kSamp and are typically
 * used for parameters or control logic.
 *
 * @param sig The signal to check.
 * @return True if the signal is a control signal, false otherwise.
 */
bool isControl(Tree sig)
{
    Type ty   = getCertifiedSigType(sig);
    bool ctrl = ty->variability() < kSamp;
    return ctrl;
}

/**
 * @brief Extracts the immediate and delayed subsignals of a given signal.
 *
 * This function analyzes the signal and separates its dependencies into
 * two categories: immediate and delayed.
 *
 * @param sig The signal to analyze.
 * @return A pair containing two vectors:
 *         - first: vector of immediate subsignals.
 *         - second: vector of delayed subsignals.
 */
std::pair<std::vector<Tree>, std::vector<Tree>> getSignalDependencies(Tree sig)
{
    std::vector<Tree> immediate;
    std::vector<Tree> delayed;
    int               i;

    // Handle recursive projection: rec(id, body).i
    // The subsignal is body.i, considered as an immediate dependency.
    if (Tree w; isProj(sig, &i, w)) {
        Tree id, le;
        faustassert(isRec(w, id, le));
        Tree d = nth(le, i);  // Extract the i-th signal from the body
        immediate.push_back(d);
        return {immediate, delayed};
    }

    // Handle seq(od,x). Only OD is a dependency as the signal x is computed by OD
    if (Tree od, x; isSigSeq(sig, od, x)) {
        immediate.push_back(od);
        return {immediate, delayed};
    }

    // Handle delayed signal x@d: delay(x, d)
    // x@d has two subsignals: x (the signal to be delayed) and d (the delay time).
    if (Tree x, d; isSigDelay(sig, x, d)) {
        Type     Td   = getCertifiedSigType(d);  // Get the type of the delay signal
        interval Id   = Td->getInterval();       // Get the interval of the delay signal
        int      dmin = int(Id.lo());            // Get the minimum delay value

        // If the minimum delay is 0, x is an immediate dependency.
        // Otherwise, x is a delayed dependency.
        if (dmin == 0) {
            immediate.push_back(x);
        } else {
            delayed.push_back(x);
        }

        immediate.push_back(d);  // d is always an immediate dependency
        return {immediate, delayed};
    }

    // Handle one sample delay: x'
    // x' has one subsignal: x, which is a delayed dependency.
    if (Tree x; isSigDelay1(sig, x)) {
        delayed.push_back(x);
        return {immediate, delayed};
    }

    // Handle FIR[X,C0,C1,C2,...] = C0*X + C1*X@1 + C2*X@2 + ...
    // FIR has several subsignals: X and C0, C1, C2, ...
    // Ci are the coefficients, and X is the input signal.
    if (tvec V; isSigFIR(sig, V)) {
        for (unsigned int ii = 1; ii < V.size(); ii++) {
            immediate.push_back(V[ii]);  // Ci are immediate dependencies
        }

        // If the first coefficient C0 is not zero, then X is an immediate dependency.
        // Otherwise, X is only used delayed.
        if (!isZero(V[1])) {
            immediate.push_back(
                V[0]);  // X is an immediate dependency only if it is used undelayed with C0!=0
        } else {
            delayed.push_back(V[0]);  // otherwise X is only used delayed
        }
        return {immediate, delayed};
    }

    // Handle IIR[nil,X,C0,C1,C2,...] = W = X+C1*W@1 + C2*W@2 + ...
    // IIR has several subsignals: X and C0, C1, C2, ...
    // Ci are the coefficients, and X is the input signal.
    if (tvec V; isSigIIR(sig, V)) {
        for (unsigned int ii = 1; ii < V.size(); ii++) {
            immediate.push_back(V[ii]);  // Ci are immediate dependencies
        }

        return {immediate, delayed};
    }

    // Handle Tables: rdtable(table, index)
    // rdtable has two subsignals: table and index.
    // index is an immediate dependency.
    if (Tree tbl, ri; isSigRDTbl(sig, tbl, ri)) {
        immediate.push_back(ri);  // index is an immediate dependency

        // If the table is also a writable table, then handle the write dependencies.
        if (Tree size, gen, wi, ws; isSigWRTbl(tbl, size, gen, wi, ws) && (wi != gGlobal->nil)) {
            immediate.push_back(wi);  // write index is an immediate dependency
            immediate.push_back(ws);  // write signal is an immediate dependency
        }
        return {immediate, delayed};
    }

    // For test purposes only: return the internal subsignals (after nil) of an ondemand
    // expression.
    if (tvec V; isSigOD(sig, V) || isSigUS(sig, V) || isSigDS(sig, V)) {
        for (unsigned int ii = 1; ii < V.size(); ii++) {
            immediate.push_back(V[ii]);  // HACK, for test purposes only
        }
        return {immediate, delayed};
    }

    // Check for cases that should have been handled by the previous cases
    {
        Tree id, le;
        faustassert(!isRec(sig, id, le));  // Recursive signals should have been handled with proj
    }

    // Handle general case that always depends on immediate subsignals
    getSubSignals(sig, immediate, false);
    return {immediate, delayed};
}
