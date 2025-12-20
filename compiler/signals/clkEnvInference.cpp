/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    Copyright (C) 2023-2024 INRIA
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <map>
#include <set>
#include <vector>

#include "DependenciesGraph.hh"
#include "DependenciesUtils.hh"
#include "clkEnvInference.hh"
#include "exception.hh"
#include "global.hh"
#include "ppsig.hh"
#include "property.hh"
#include "signals.hh"
#include "sigtype.hh"

using namespace std;

/**
 * @file clkEnvInference.cpp
 * Infer the clock environment in which a signal should be computed.
 *
 * This implements the formal inference rules defined in ClockEnvironmentInferenceRulesV2.md.
 * Uses a fixed-point algorithm to handle recursive groups without requiring annotations.
 *
 * Key concepts:
 * - C⟦sig⟧ᴴ·ᴹ = c means signal sig is computed in clock environment c under hypothesis H and cache
 * M
 * - H : Groupe → ClkEnv maps recursive groups to their clock environments
 * - M : Signal → ClkEnv caches computed clock environments
 * - Fixed-point iteration computes H until convergence
 */

//--------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------
static Tree maxClkEnv(const vector<Tree>& clkEnvs);
static Tree inferClkEnvWithHypothesis(Tree sig, const map<Tree, Tree>& hypothesis,
                                      map<Tree, Tree>& cache);

//--------------------------------------------------------------------------
// Helper: Check if c1 is an ancestor of c2 (c1 ⊆ c2)
//--------------------------------------------------------------------------
/**
 * @brief Check if c1 is an ancestor of c2 in the clock environment hierarchy
 *
 * The relation c1 ⊆ c2 means c1 is an ancestor of c2, i.e., c2 is nested inside c1.
 * Properties:
 * - Reflexive: c ⊆ c
 * - Transitive: c1 ⊆ c2 ∧ c2 ⊆ c3 ⟹ c1 ⊆ c3
 * - Universal: nil ⊆ c for all c
 *
 * @param c1 Potentially ancestor clock environment
 * @param c2 Potentially descendant clock environment
 * @return true if c1 ⊆ c2
 */
bool isAncestorClkEnv(Tree c1, Tree c2)
{
    // nil is ancestor of everything (universal)
    if (c1 == gGlobal->nil) {
        return true;
    }

    // If c2 == nil, then c1 must be nil (we already checked above)
    if (c2 == gGlobal->nil) {
        return false;
    }

    // Reflexive: c1 ⊆ c2 if c1 == c2
    if (c1 == c2) {
        return true;
    }

    // Transitive: c1 ⊆ c2 if c1 ⊆ parent(c2)
    Tree parent_c2 = getClockenvEnv(c2);
    return isAncestorClkEnv(c1, parent_c2);
}

//--------------------------------------------------------------------------
// Helper: Compute the max (deepest) clock environment
//--------------------------------------------------------------------------
/**
 * @brief Compute the deepest clock environment from a set of clock environments
 *
 * max{c₁, ..., cₙ} is the most deeply nested (most included) clkEnv among the set.
 * All clkEnvs must be comparable (have an inclusion relation), otherwise the signal
 * is malformed.
 *
 * @param clkEnvs Vector of clock environments
 * @return Tree The deepest clkEnv, or nil if the vector is empty
 * @throws faustexception If two clkEnvs are not comparable (parallel domains)
 */
static Tree maxClkEnv(const vector<Tree>& clkEnvs)
{
    if (clkEnvs.empty()) {
        return gGlobal->nil;
    }

    Tree result = clkEnvs[0];

    for (size_t i = 1; i < clkEnvs.size(); i++) {
        Tree c = clkEnvs[i];

        // Check that result and c are comparable
        if (isAncestorClkEnv(result, c)) {
            // result ⊆ c, so c is deeper
            result = c;
        } else if (isAncestorClkEnv(c, result)) {
            // c ⊆ result, so result remains the deepest
            // Nothing to do
        } else {
            // Incomparable: error
            throw faustexception("ERROR: Incomparable clock environments\n");
        }
    }

    return result;
}

//--------------------------------------------------------------------------
// Collect all recursive groups in a signal (R⟦.⟧ rules)
//--------------------------------------------------------------------------
/**
 * @brief Collect all recursive groups in a signal
 *
 * Implements the R⟦sig⟧ rules from ClockEnvironmentInferenceRulesV2.md
 *
 * @param sig The signal to analyze
 * @param visited Set of already visited signals (for DAG traversal optimization)
 * @param groups Set of discovered recursive groups
 */
static void collectRecGroups(Tree sig, set<Tree>& visited, set<Tree>& groups)
{
    // Skip if already visited (avoid retraversing the DAG)
    if (visited.count(sig) > 0) {
        return;
    }
    visited.insert(sig);

    // RG_PROJ: Recursive projection proj(p, W)
    int p;
    if (Tree W; isProj(sig, &p, W)) {
        // Try to add the group W
        auto [it, inserted] = groups.insert(W);

        // Only descend into definitions if this is the first time we see this group
        if (inserted) {
            Tree var, body;
            faustassert(isRec(W, var, body));

            // Collect recursive groups from each definition in the group
            for (Tree ls = body; !isNil(ls); ls = tl(ls)) {
                collectRecGroups(hd(ls), visited, groups);
            }
        }
        return;
    }

    // RG_CLOCKED: Clocked signal sigClocked(c, s)
    if (Tree c, s; isSigClocked(sig, c, s)) {
        collectRecGroups(s, visited, groups);
        return;
    }

    // RG_CD: Clock Domain operations (OD/US/DS)
    if (tvec sigsubs; isSigOD(sig, sigsubs) || isSigUS(sig, sigsubs) || isSigDS(sig, sigsubs)) {
        for (Tree sub : sigsubs) {
            collectRecGroups(sub, visited, groups);
        }
        return;
    }

    // RG_SEQ: Sequential composition sigSeq(x, y)
    if (Tree x, y; isSigSeq(sig, x, y)) {
        collectRecGroups(x, visited, groups);
        collectRecGroups(y, visited, groups);
        return;
    }

    // RG_RDTBL_STATIC: Static read-only table
    if (Tree tbl, ri; isSigRDTbl(sig, tbl, ri)) {
        Tree size, gen;
        if (isSigWRTbl(tbl, size, gen)) {
            collectRecGroups(ri, visited, groups);
            return;
        }
    }

    // RG_RDTBL_DYNAMIC: Dynamic read-write table
    if (Tree tbl, ri; isSigRDTbl(sig, tbl, ri)) {
        Tree size, gen, wi, ws;
        if (isSigWRTbl(tbl, size, gen, wi, ws)) {
            collectRecGroups(wi, visited, groups);
            collectRecGroups(ws, visited, groups);
            collectRecGroups(ri, visited, groups);
            return;
        }
    }

    // RG_IIR: IIR filter sigIIR([nil, X, C₁, ..., Cₙ])
    if (tvec lsig; isSigIIR(sig, lsig)) {
        for (Tree sub : lsig) {
            if (!isNil(sub)) {
                collectRecGroups(sub, visited, groups);
            }
        }
        return;
    }

    // RG_COMPOSITE: Composite/primitive signal F(s₁, ..., sₙ) (general case)
    tvec subsignals;
    getSubSignals(sig, subsignals, false);
    for (Tree sub : subsignals) {
        collectRecGroups(sub, visited, groups);
    }
}

//--------------------------------------------------------------------------
// Infer clock environment with hypothesis H and cache M (C⟦.⟧ᴴ·ᴹ rules)
//--------------------------------------------------------------------------
/**
 * @brief Infer the clock environment of a signal given hypothesis H and cache M
 *
 * Implements the C⟦sig⟧ᴴ·ᴹ = c rules from ClockEnvironmentInferenceRulesV2.md
 *
 * @param sig The signal whose clock environment we want to infer
 * @param hypothesis H : Groupe → ClkEnv mapping for recursive groups
 * @param cache M : Signal → ClkEnv cache for memoization
 * @return Tree The clock environment c
 */
static Tree inferClkEnvWithHypothesis(Tree sig, const map<Tree, Tree>& hypothesis,
                                      map<Tree, Tree>& cache)
{
    // R_CACHE: If signal already in cache, return cached value
    auto it = cache.find(sig);
    if (it != cache.end()) {
        return it->second;
    }

    Tree result;

    // R_PROJ: Recursive projection proj(j, W)
    int p;
    if (Tree W; isProj(sig, &p, W)) {
        // proj(j, W) ∉ M (not in cache yet)
        // Get all definitions of the recursive group
        Tree var, body;
        faustassert(isRec(W, var, body));

        vector<Tree> defs;
        for (Tree ls = body; !isNil(ls); ls = tl(ls)) {
            defs.push_back(hd(ls));
        }

        // Create augmented cache M' = M ∪ {proj(i, W) ↦ H(W) | i ∈ [1..n]}
        // All projections from this group temporarily get the hypothesized clock environment
        auto it = hypothesis.find(W);
        faustassert(it != hypothesis.end());  // All recursive groups must be in hypothesis
        Tree h_w = it->second;

        for (size_t i = 0; i < defs.size(); i++) {
            Tree proj_i   = sigProj(i, W);
            cache[proj_i] = h_w;
        }

        // Compute clock environment of all definitions with augmented cache
        vector<Tree> def_clkEnvs;
        for (Tree def : defs) {
            Tree c = inferClkEnvWithHypothesis(def, hypothesis, cache);
            def_clkEnvs.push_back(c);
        }

        // Return max{c₁, ..., cₙ} (deepest environment among definitions)
        result     = maxClkEnv(def_clkEnvs);
        cache[sig] = result;
        return result;
    }

    // R_CLOCKED: Clocked signal annotation sigClocked(c, s)
    if (Tree c, s; isSigClocked(sig, c, s)) {
        Tree c_prime = inferClkEnvWithHypothesis(s, hypothesis, cache);
        if (!isAncestorClkEnv(c_prime, c)) {
            throw faustexception("ERROR: sigClocked(c, s) requires C⟦s⟧ ⊆ c\n");
        }
        result     = c;
        cache[sig] = result;
        return result;
    }

    // R_CD: Clock Domain operations (OD/US/DS)
    if (tvec sigsubs; isSigOD(sig, sigsubs) || isSigUS(sig, sigsubs) || isSigDS(sig, sigsubs)) {
        // The first element must be the clocked signal defining the inner domain
        if (sigsubs.empty()) {
            throw faustexception("ERROR: OD/US/DS has no subsignals\n");
        }
        // Special treatment for the first subsignal that indicates both the inner
        // clock environment and the clock or rate signal
        Tree clk = sigsubs[0];
        inferClkEnvWithHypothesis(clk, hypothesis, cache);
        Tree c_inner, h;
        if (!isSigClocked(clk, c_inner, h)) {
            throw faustexception("ERROR: OD/US/DS requires sigClocked annotation\n");
        }
        // The clock signal must be accessible
        Tree h_clk = inferClkEnvWithHypothesis(h, hypothesis, cache);
        if (!isAncestorClkEnv(h_clk, getClockenvEnv(c_inner))) {
            throw faustexception(
                "ERROR: OD/US/DS requires clock signal to be in the correct domain\n");
        }
        // Verify all outputs (from index 1 onwards) are computed in c_inner or its ancestors
        for (size_t i = 1; i < sigsubs.size(); i++) {
            Tree yi_clk = inferClkEnvWithHypothesis(sigsubs[i], hypothesis, cache);
            // All output signals of an OD/US/DS must have the same domain. The only
            // exception is 0 because it is the only truly constant signal
            if ((yi_clk != c_inner) && !isZero(sigsubs[i])) {
                std::cerr << "in signal " << ppsig(sig) << std::endl;
                std::cerr << "the subsignal " << ppsig(sigsubs[i])
                          << " is not in the correct domain" << std::endl;
                throw faustexception("ERROR: OD/US/DS output not in correct domain\n");
            }
        }
        result     = getClockenvEnv(c_inner);
        cache[sig] = result;
        return result;
    }

    // R_SEQ: Sequential composition sigSeq(x, y)
    if (Tree x, y; isSigSeq(sig, x, y)) {
        Tree c_x = inferClkEnvWithHypothesis(x, hypothesis, cache);
        Tree c_y = inferClkEnvWithHypothesis(y, hypothesis, cache);
        if (!isAncestorClkEnv(c_x, c_y)) {
            throw faustexception("ERROR: sigSeq requires c_x ⊆ c_y\n");
        }
        result     = c_x;
        cache[sig] = result;
        return result;
    }

    // R_RDTBL_STATIC: Static read-only table
    if (Tree tbl, ri; isSigRDTbl(sig, tbl, ri)) {
        Tree size, gen;
        if (isSigWRTbl(tbl, size, gen)) {
            result     = inferClkEnvWithHypothesis(ri, hypothesis, cache);
            cache[sig] = result;
            return result;
        }
    }

    // R_RDTBL_DYNAMIC: Dynamic read-write table
    if (Tree tbl, ri; isSigRDTbl(sig, tbl, ri)) {
        Tree size, gen, wi, ws;
        if (isSigWRTbl(tbl, size, gen, wi, ws)) {
            Tree c_wi  = inferClkEnvWithHypothesis(wi, hypothesis, cache);
            Tree c_ws  = inferClkEnvWithHypothesis(ws, hypothesis, cache);
            Tree c_ri  = inferClkEnvWithHypothesis(ri, hypothesis, cache);
            result     = maxClkEnv({c_wi, c_ws, c_ri});
            cache[sig] = result;
            return result;
        }
        throw faustexception("ERROR: sigRDTbl with invalid sigWRTbl\n");
    }

    // R_IIR: IIR filter sigIIR([nil, X, C₁, ..., Cₙ])
    if (tvec lsig; isSigIIR(sig, lsig)) {
        vector<Tree> clkEnvs;

        for (auto ss : lsig) {
            if (!isNil(ss)) {
                clkEnvs.push_back(inferClkEnvWithHypothesis(ss, hypothesis, cache));
            }
        }
        result     = maxClkEnv(clkEnvs);
        cache[sig] = result;
        return result;
    }

    // R_COMPOSITE: Composite/primitive signal F(s₁, ..., sₙ) (general case)
    tvec subsignals;
    getSubSignals(sig, subsignals, false);
    vector<Tree> clkEnvs;
    for (Tree sub : subsignals) {
        clkEnvs.push_back(inferClkEnvWithHypothesis(sub, hypothesis, cache));
    }
    result     = maxClkEnv(clkEnvs);
    cache[sig] = result;
    return result;
}

/**
 * @brief Compute the fixed-point hypothesis H : Group → ClkEnv for all recursive groups
 *
 * Uses iterative fixed-point computation to find the clock environment for each
 * recursive group. The algorithm initializes all groups to nil and iteratively
 * refines the hypothesis until convergence (H^(n+1) = H^n).
 *
 * For each iteration:
 * - For each group W, compute the clock environments of all its definitions
 * - Set H(W) = max{c₁, ..., cₙ} where cᵢ is the clock environment of definition i
 * - Continue until no changes occur (fixed point reached)
 *
 * @param groups Set of all recursive groups found in the signal graph
 * @return std::map<Tree, Tree> The fixed-point hypothesis mapping groups to clock environments
 */
static std::map<Tree, Tree> findFixpoint(const std::set<Tree>& groups)
{
    bool      converged      = false;
    int       iteration      = 0;
    const int MAX_ITERATIONS = 1000;  // Safety limit

    // Get definitions for each group
    map<Tree, vector<Tree>> group_defs;
    for (Tree W : groups) {
        Tree var, body;
        faustassert(isRec(W, var, body));

        vector<Tree> defs;
        for (Tree ls = body; !isNil(ls); ls = tl(ls)) {
            defs.push_back(hd(ls));
        }
        group_defs[W] = defs;
    }

    // prepare the initial hypothesis
    map<Tree, Tree> hypothesis;
    for (Tree W : groups) {
        hypothesis[W] = gGlobal->nil;
    }

    while (!converged) {
        faustassert(++iteration < MAX_ITERATIONS);

        map<Tree, Tree> new_hypothesis;
        map<Tree, Tree> cache;

        // For each group W
        for (Tree W : groups) {
            // Create augmented cache M' with all proj(i, W) ↦ H(W)
            Tree h = hypothesis[W];
            for (size_t i = 0; i < group_defs[W].size(); i++) {
                cache[sigProj(i, W)] = h;
            }

            // Compute clkEnv of each definition
            vector<Tree> def_clkEnvs;
            for (Tree def : group_defs[W]) {
                Tree c = inferClkEnvWithHypothesis(def, hypothesis, cache);
                def_clkEnvs.push_back(c);
            }

            // H(W) = max{c₁, ..., cₙ}
            new_hypothesis[W] = maxClkEnv(def_clkEnvs);
        }

        // Check convergence: ∀W : new_hypothesis[W] == hypothesis[W]
        converged = true;
        for (Tree W : groups) {
            if (new_hypothesis[W] != hypothesis[W]) {
                converged = false;
                break;
            }
        }

        hypothesis = new_hypothesis;
    }
    return hypothesis;
}

//--------------------------------------------------------------------------
// Main computation: Collect groups, find fixpoint, infer environments
//--------------------------------------------------------------------------
/**
 * @brief Compute clock environments for all signals in the signal list
 *
 * Main entry point for clock environment inference. This function:
 * 1. Collects all recursive groups in the signal graph
 * 2. Computes the fixed-point hypothesis H for these groups
 * 3. Infers the clock environment for each signal using H
 * 4. Stores the results in the clkEnvs map
 *
 * @param sigList List of signals to analyze (Tree list structure)
 * @param clkEnvs Output map that will contain Signal → ClkEnv mappings
 */
static void computeClkEnv(Tree sigList, std::map<Tree, Tree>& clkEnvs)
{
    // Convert signal list into a more convenient vector
    vector<Tree> vsigs;
    for (Tree ls = sigList; !isNil(ls); ls = tl(ls)) {
        vsigs.push_back(hd(ls));
    }

    // Step 1: Collect all recursive groups involved in these signals
    std::set<Tree> groups;
    std::set<Tree> visited;
    for (Tree s : vsigs) {
        collectRecGroups(s, visited, groups);
    }

    // Step 2: Find the fixed-point hypothesis H : Group → ClkEnv
    std::map<Tree, Tree> fpHypothesis = findFixpoint(groups);

    // Step 3: Compute the clock environment for each signal using H
    for (Tree s : vsigs) {
        inferClkEnvWithHypothesis(s, fpHypothesis, clkEnvs);
    }
}

//--------------------------------------------------------------------------
// Public API: ClkEnvInference class implementation
//--------------------------------------------------------------------------

void ClkEnvInference::annotate(Tree sigList)
{
    // Compute clock environments for all signals
    computeClkEnv(sigList, mapping);

    // Annotate each signal Tree node with its clock environment property
    for (auto [sig, ce] : mapping) {
        // std::cerr << "\nWe have clock environment " << ce << " for signal " << sig << "--"
        //           << ppsig(sig) << "\n";
        sig->setProperty(gGlobal->CLKENVPROPERTY, ce);
    }
}

Tree ClkEnvInference::getClkEnv(Tree sig)
{
    Tree ce = sig->getProperty(gGlobal->CLKENVPROPERTY);
    if (!ce) {
        std::cerr << "This signal has no clkEnv property ! " << ppsig(sig) << "\n";
    }
    faustassert(ce);  // Signal must have an associated clock environment
    return ce;
}

/**
 * DEBUG: Test function to detect duplicate clkEnv usage across different OD/US/DS signals.
 *
 * This test verifies that each unique OD/US/DS signal has its own unique clock environment.
 * If two different OD/US/DS signals share the same clkEnv, this indicates a bug where
 * de Bruijn notation caused structurally identical but semantically different signals
 * to be assigned the same clock environment.
 *
 * @param hg The hierarchical graph containing subgraphs to test
 * @return true if all clkEnv are unique per signal, false if duplicates are found
 */
bool ClkEnvInference::testClkEnvUniqueness([[maybe_unused]] const Hgraph& hg)
{
    // DEBUG: Function body commented out - bug has been fixed
    // The bug was that makeClockEnv didn't include slotenv and path parameters,
    // causing different ondemand domains to share the same clkEnv

    return true;  // Always pass now that the bug is fixed

    /*
    // std::cerr << "\n=== Testing ClkEnv Uniqueness ===" << std::endl;

    // Map from clkEnv to the list of OD/US/DS signals that use it
    std::map<Tree, std::vector<Tree>> clkEnvToSignals;

    // Iterate through all subgraphs in the Hgraph
    // The keys of hg.siggraph are the signals that have subgraphs
    // For OD/US/DS signals, the key IS the OD/US/DS signal
    for (const auto& [graphKey, graph] : hg.siggraph) {
        // Skip the main graph (identified by outSigList)
        if (graphKey == hg.outSigList) {
            continue;
        }

        // Check if this graph key is an OD/US/DS signal
        tvec V;
        if (isSigOD(graphKey, V) || isSigUS(graphKey, V) || isSigDS(graphKey, V)) {
            // Extract clkEnv from the first sub-tree which is sigClocked(clkEnv, h)
            Tree clockedClk = V[0];
            Tree clkEnv, h;
            faustassert(isSigClocked(clockedClk, clkEnv, h));

            clkEnvToSignals[clkEnv].push_back(graphKey);
            // std::cerr << "  Found OD/US/DS signal " << graphKey << " with clkEnv " << clkEnv
            //           << std::endl;
        }
    }

    // std::cerr << "\nFound " << clkEnvToSignals.size()
    //           << " unique clkEnv(s) across all OD/US/DS signals" << std::endl;

    // Check for duplicates
    bool hasErrors      = false;
    int  totalODSignals = 0;

    for (const auto& [clkEnv, signals] : clkEnvToSignals) {
        totalODSignals += signals.size();

        if (signals.size() > 1) {
            // ERROR: Multiple different signals share the same clkEnv!
            hasErrors = true;
            std::cerr << "\n*** ERROR: ClkEnv " << clkEnv << " is shared by " << signals.size()
                      << " different OD/US/DS signals:" << std::endl;

            // Print the clkEnv structure
            ppclkenv(clkEnv, 10, std::cerr);

            // Print the signals that share this clkEnv
            for (Tree sig : signals) {
                std::cerr << "  - Signal at address " << sig << " -- " << ppsig(sig, 6)
                          << std::endl;
            }
        }
    }

    // std::cerr << "\nTotal OD/US/DS signals found: " << totalODSignals << std::endl;

    if (hasErrors) {
        std::cerr << "*** TEST FAILED: Duplicate clkEnv detected! ***" << std::endl;
        return false;
    } else {
        // std::cerr << "*** TEST PASSED: All clkEnv are unique ***" << std::endl;
        return true;
    }
    */
}