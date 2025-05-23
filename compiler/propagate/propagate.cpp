/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include "propagate.hh"
#include "Text.hh"
#include "aterm.hh"
#include "exception.hh"
#include "floats.hh"
#include "global.hh"
#include "labels.hh"
#include "names.hh"
#include "ppbox.hh"
#include "ppsig.hh"
#include "prim2.hh"
#include "simplify.hh"
#include "xtended.hh"

//========================================================================
// Memoization Tables
//========================================================================

static std::map<Tree, bool>                             memo_can_be_route;
static std::map<Tree, std::vector<std::pair<int, int>>> memo_routing_pairs;

//========================================================================
// Memoization Cache Management
//========================================================================

/**
 * Clears the memoization cache for can_be_fully_represented_as_single_box_route.
 */
static void clear_can_be_route_memoization()
{
    memo_can_be_route.clear();
}

/**
 * Clears the memoization cache for compute_routing_pairs.
 */
static void clear_routing_pairs_memoization()
{
    memo_routing_pairs.clear();
}

//========================================================================
// Eligibility Check Function (`can_be_fully_represented_as_single_box_route`)
//========================================================================

/**
 * Checks if a given 'box' expression can be fully represented as a single BoxRoute.
 * It recursively checks if the box and its children consist only of pure routing elements.
 *
 * @param box The Tree expression to check.
 * @return True if the box can be represented as a single BoxRoute, false otherwise.
 */
static bool can_be_fully_represented_as_single_box_route(Tree box)
{
    // 1. Check memoization table
    auto memo_it = memo_can_be_route.find(box);
    if (memo_it != memo_can_be_route.end()) {
        return memo_it->second;
    }

    bool result = false;
    Tree child1, child2, content, label;
    Tree route_ins, route_outs, route_list;

    // 2. Check for allowed primitive routing elements
    if (isBoxWire(box) || isBoxCut(box) || isBoxRoute(box, route_ins, route_outs, route_list)) {
        result = true;
    }
    // 3. Check for allowed routing combinators and UI groups (recursive check)
    else if (isBoxSeq(box, child1, child2)) {
        result = can_be_fully_represented_as_single_box_route(child1) &&
                 can_be_fully_represented_as_single_box_route(child2);
    } else if (isBoxPar(box, child1, child2)) {
        result = can_be_fully_represented_as_single_box_route(child1) &&
                 can_be_fully_represented_as_single_box_route(child2);
    } else if (isBoxSplit(box, child1, child2)) {
        result = can_be_fully_represented_as_single_box_route(child1) &&
                 can_be_fully_represented_as_single_box_route(child2);
    } else if (isBoxMerge(box, child1, child2)) {
        result = can_be_fully_represented_as_single_box_route(child1) &&
                 can_be_fully_represented_as_single_box_route(child2);
    } else if (isBoxVGroup(box, label, content) || isBoxHGroup(box, label, content) ||
               isBoxTGroup(box, label, content)) {
        result = can_be_fully_represented_as_single_box_route(content);
    }
    // 4. Check for extended primitives (assuming not pure routing)
    else if (getUserData(box) != nullptr) {
        result = false;
    }
    // 5. If it's none of the above, it's considered a non-routing element.
    else {
        result = false;
    }

    // Store result in memoization table
    memo_can_be_route[box] = result;
    return result;
}

//========================================================================
// Routing Pair Computation Function (`compute_routing_pairs`)
//========================================================================

/**
 * Recursively parses a boxPar structure (expected to contain boxInt nodes)
 * into a flat vector of integers.
 *
 * @param box The Tree node to parse (starting with the BoxRoute's route_list).
 * @param list The vector to populate with integers.
 * @return True on success, false if the structure is not as expected.
 */
static bool parse_boxpar_to_int_vector(Tree box, std::vector<int>& list)
{
    Tree t1, t2;
    int  val;

    if (isBoxPar(box, t1, t2)) {
        // We expect the first element to be a boxInt
        if (isBoxInt(t1, &val)) {  // Assumes isBoxInt extracts value into 'val'
            list.push_back(val);
            // Recurse on the second element
            return parse_boxpar_to_int_vector(t2, list);
        } else {
            // Error: Expected boxInt as the first part of boxPar
            return false;
        }
    } else if (isBoxInt(box, &val)) {
        // This is the last element in the chain
        list.push_back(val);
        return true;
    } else {
        // Check for the special 'empty' case: boxPar(boxInt(0), boxInt(0))
        // This check needs to be robust. If isBoxPar returns false, we check isBoxInt.
        // If both fail, we might be at an unexpected node.
        // A simple `boxPar(boxInt(0), boxInt(0))` would be caught by the first 'if'.
        // If 'box' itself is boxPar(0,0), we need to check both branches.
        // For simplicity, we assume valid structures or an empty list (size 0)
        // If it's neither Par nor Int, it's either empty (handled by caller) or an error.
        return false;  // Or handle more specific error/empty cases
    }
}

/**
 * Computes the direct input-to-output routing pairs (0-indexed) for a given box expression.
 * Assumes the box is eligible (checked via can_be_fully_represented_as_single_box_route).
 *
 * @param box The Tree expression to analyze.
 * @return A vector of (source_input_idx, destination_output_idx) pairs.
 */
static std::vector<std::pair<int, int>> compute_routing_pairs(Tree box)
{
    // 1. Check memoization table
    auto memo_it = memo_routing_pairs.find(box);
    if (memo_it != memo_routing_pairs.end()) {
        return memo_it->second;
    }

    std::vector<std::pair<int, int>> routes;
    Tree t1, t2, label, ins_tree_route, outs_tree_route, route_list_tree_content;
    // int  num_inputs, num_outputs;

    // 2. Base Cases
    if (isBoxWire(box)) {
        routes.push_back({0, 0});
    } else if (isBoxCut(box)) {
        // No routes
    } else if (isBoxRoute(box, ins_tree_route, outs_tree_route, route_list_tree_content)) {
        std::vector<int> flat_routes_1_indexed;

        // Use the new helper to parse the boxPar structure
        if (parse_boxpar_to_int_vector(route_list_tree_content, flat_routes_1_indexed)) {
            // Check if the parsed list is the 'empty' representation [0, 0]
            if (flat_routes_1_indexed.size() == 2 && flat_routes_1_indexed[0] == 0 &&
                flat_routes_1_indexed[1] == 0) {
                // It's the conventional empty route list, 'routes' remains empty.
            }
            // Check if the number of elements is even (must be pairs)
            else if (flat_routes_1_indexed.size() % 2 != 0) {
                // This is an error - log or throw an exception if necessary
                std::cerr << "ERROR: BoxRoute has an odd number of route elements: " << boxpp(box)
                          << std::endl;
            } else {
                // Process the valid, non-empty list
                for (size_t i = 0; i < flat_routes_1_indexed.size(); i += 2) {
                    int src = flat_routes_1_indexed[i];
                    int dst = flat_routes_1_indexed[i + 1];

                    // Sanity check: ensure src and dst are > 0 before subtracting
                    if (src > 0 && dst > 0) {
                        // Convert 1-indexed to 0-indexed
                        routes.push_back({src - 1, dst - 1});
                    } else {
                        // This shouldn't happen for valid BoxRoutes, except for the empty [0,0]
                        // case.
                        std::cerr << "WARNING: BoxRoute contains non-positive route index:" << src
                                  << "," << dst << std::endl;
                    }
                }
            }

        } else {
            faustassert(false);

            // Parsing failed - the structure wasn't as expected.
            // This might indicate an error or an empty list not caught yet.
            // If flat_routes_1_indexed is empty after the call, it means an empty or invalid
            // structure.
            if (flat_routes_1_indexed.empty()) {
                // Assume it means no routes, so 'routes' remains empty.
            } else {
                // std::cerr << "ERROR: Failed to parse BoxRoute structure: " << boxpp(box) <<
                // std::endl;
            }
        }
    }
    // 3. Recursive Cases for Combinators
    else if (isBoxSeq(box, t1, t2)) {
        std::vector<std::pair<int, int>> routes1 = compute_routing_pairs(t1);
        std::vector<std::pair<int, int>> routes2 = compute_routing_pairs(t2);
        for (const auto& r1 : routes1) {
            for (const auto& r2 : routes2) {
                if (r1.second == r2.first) {
                    routes.push_back({r1.first, r2.second});
                }
            }
        }
    } else if (isBoxPar(box, t1, t2)) {
        int t1_ins, t1_outs;
        getBoxType(t1, &t1_ins, &t1_outs);
        std::vector<std::pair<int, int>> routes1 = compute_routing_pairs(t1);
        std::vector<std::pair<int, int>> routes2 = compute_routing_pairs(t2);
        routes                                   = routes1;
        for (const auto& r2 : routes2) {
            routes.push_back({r2.first + t1_ins, r2.second + t1_outs});
        }
    } else if (isBoxSplit(box, t1, t2)) {
        int t1_ins, t1_outs, t2_ins, t2_outs;
        getBoxType(t1, &t1_ins, &t1_outs);
        getBoxType(t2, &t2_ins, &t2_outs);
        if (t1_outs > 0) {
            std::vector<std::pair<int, int>> routes1 = compute_routing_pairs(t1);
            std::vector<std::pair<int, int>> routes2 = compute_routing_pairs(t2);
            for (const auto& r1 : routes1) {
                for (int t2_input_idx = 0; t2_input_idx < t2_ins; ++t2_input_idx) {
                    if ((t2_input_idx % t1_outs) == r1.second) {
                        for (const auto& r2 : routes2) {
                            if (r2.first == t2_input_idx) {
                                routes.push_back({r1.first, r2.second});
                            }
                        }
                    }
                }
            }
        }
    } else if (isBoxMerge(box, t1, t2)) {
        int t1_ins, t1_outs, t2_ins, t2_outs;
        getBoxType(t1, &t1_ins, &t1_outs);
        getBoxType(t2, &t2_ins, &t2_outs);
        if (t2_ins > 0) {
            std::vector<std::pair<int, int>> routes1 = compute_routing_pairs(t1);
            std::vector<std::pair<int, int>> routes2 = compute_routing_pairs(t2);
            for (const auto& r1 : routes1) {
                int target_t2_input = r1.second % t2_ins;
                for (const auto& r2 : routes2) {
                    if (r2.first == target_t2_input) {
                        routes.push_back({r1.first, r2.second});
                    }
                }
            }
        }
    }
    // 4. Handle Groups (recurse on content)
    else if (isBoxVGroup(box, label, t2) || isBoxHGroup(box, label, t2) ||
             isBoxTGroup(box, label, t2)) {
        // Here t2 should contain the content based on isBoxVGroup predicate signature.
        // If the predicate only returns the content, we call compute_routing_pairs on that.
        // Assuming the 'content' Tree is extracted into 't2' (or 'content')
        // routes = compute_routing_pairs(content_tree_variable); // Needs adjustment based on
        // actual predicate. This part needs refinement based on how Groups are structured and how
        // 'content' is accessed. If groups only contain *one* child, and
        // can_be_fully_represented_as_single_box_route handled them, then this function should
        // ideally be called on the content, not the group itself, or it should directly recurse on
        // the content. Let's assume recursion is handled by the caller or that this function won't
        // be called on a Group directly if it should look *inside*. For simplicity here, we assume
        // if it got here, it's an error or needs specific group handling. throw
        // std::runtime_error("compute_routing_pairs called on UI Group - handle content instead");
        routes = compute_routing_pairs(t2);
    }
    // 5. Default: Empty routes (should not happen for eligible boxes)
    else {
        // Potentially throw an error if called on an unsupported box type
        // throw std::runtime_error("compute_routing_pairs called on unsupported box type");
        faustassert(false);
    }

    // Store result in memoization table
    memo_routing_pairs[box] = routes;
    return routes;
}

//========================================================================
// Conceptual Helper & Usage Example
//========================================================================

/**
 * Converts a set of unique 0-indexed routing pairs into a
 * 'boxPar' expression of 'boxInt' nodes, representing the route list
 * for a BoxRoute primitive, following the structure used in eval.cpp.
 * The pairs are converted to a 1-indexed flat list [s1,d1,s2,d2,...].
 *
 * @param unique_zero_indexed_pairs A set of unique (src, dst) pairs (0-indexed).
 * @return A Tree representing boxPar(boxInt(s1), boxPar(boxInt(d1), ...))
 * or a suitable representation for an empty route list (e.g., boxInt(0)).
 */
Tree convert_pairs_to_boxpar_route_list(
    const std::set<std::pair<int, int>>& unique_zero_indexed_pairs)
{
    if (unique_zero_indexed_pairs.empty()) {
        // The original code checks `(o3 > 1)`. If no pairs, o3=0.
        // A BoxRoute needs a route list. What should an empty one look like?
        // The original `iteratePar` used `boxRoute(boxInt(0), boxInt(0), boxPar(boxInt(0),
        // boxInt(0)))`. This has 2 outputs. If we need 0 outputs (o3=0), it's tricky. Let's return
        // a single boxInt(0) as a placeholder for an "empty but valid" list, though this might need
        // adjustment based on how BoxRoute(..., ..., empty) is handled. Perhaps `boxPar(boxInt(0),
        // boxInt(0))` *is* the canonical "empty list", despite having 2 outputs? Given the code
        // snippet's logic, it relies on having at least one element. Let's create
        // `boxPar(boxInt(0), boxInt(0))` as the "zero element" as seen in iteratePar
        // - this often signifies a 0->0 connector in some contexts.
        // A BoxRoute with 0 routes should likely have 0 outputs.
        // Let's return boxPar(boxInt(0), boxInt(0)) for now, consistent with iteratePar.
        return boxPar(boxInt(0), boxInt(0));
    }

    // 1. Create a flat vector of 1-indexed integers
    std::vector<int> flat_list;
    flat_list.reserve(unique_zero_indexed_pairs.size() * 2);
    for (const auto& pair : unique_zero_indexed_pairs) {
        flat_list.push_back(pair.first + 1);   // Convert src to 1-indexed
        flat_list.push_back(pair.second + 1);  // Convert dst to 1-indexed
    }

    // 2. Build the boxPar structure, starting from the last element
    //    and prepending with boxPar.
    Tree route_box_expression = boxInt(flat_list.back());
    for (int i = (int)flat_list.size() - 2; i >= 0; --i) {
        route_box_expression = boxPar(boxInt(flat_list[i]), route_box_expression);
    }

    return route_box_expression;
}

/**
 * (Conceptual) The main transformation pass function.
 */
static Tree simplify_to_box_route_pass(Tree current_box)
{
    Tree modified_box;

    // 1. Recurse on children (example for isBoxSeq)
    Tree t1, t2;
    if (isBoxSeq(current_box, t1, t2)) {
        Tree new_t1  = simplify_to_box_route_pass(t1);
        Tree new_t2  = simplify_to_box_route_pass(t2);
        modified_box = boxSeq(new_t1, new_t2);
    } else if (isBoxPar(current_box, t1, t2)) {
        Tree new_t1  = simplify_to_box_route_pass(t1);
        Tree new_t2  = simplify_to_box_route_pass(t2);
        modified_box = boxPar(new_t1, new_t2);
    } else if (isBoxSplit(current_box, t1, t2)) {
        Tree new_t1  = simplify_to_box_route_pass(t1);
        Tree new_t2  = simplify_to_box_route_pass(t2);
        modified_box = boxSplit(new_t1, new_t2);
    } else if (isBoxMerge(current_box, t1, t2)) {
        Tree new_t1  = simplify_to_box_route_pass(t1);
        Tree new_t2  = simplify_to_box_route_pass(t2);
        modified_box = boxMerge(new_t1, new_t2);
    } else {
        modified_box = current_box;
    }

    // 2. Try to convert the (potentially rebuilt) box
    if (can_be_fully_represented_as_single_box_route(modified_box)) {
        int ins, outs;
        //std::cerr << "modified_box " << *modified_box << std::endl;
        if (getBoxType(modified_box, &ins, &outs)) {
            std::vector<std::pair<int, int>> zero_indexed_pairs =
                compute_routing_pairs(modified_box);
            std::set<std::pair<int, int>> unique_pairs(zero_indexed_pairs.begin(),
                                                       zero_indexed_pairs.end());
            Tree route_list_aterm = convert_pairs_to_boxpar_route_list(unique_pairs);

            /*
            std::cout << "can_be_fully_represented_as_single_box_route " << ins << " " << outs
                      << "\n";
            */

            return boxRoute(tree(ins), tree(outs), route_list_aterm);
        } else {
            faustassert(false);
        }
    }

    return modified_box;
}

/**
 * Rebuild subgraph using 'route' when possible
 */
Tree run_box_route_optimization(Tree root_box)
{
    clear_can_be_route_memoization();
    clear_routing_pairs_memoization();
    return simplify_to_box_route_pass(root_box);
}

////////////////////////////////////////////////////////////////////////
/**
 * propagate : box listOfSignal-> listOfSignal'
 *
 * Propagate a list of signals into a box expression representing a
 * signal processor
 */
///////////////////////////////////////////////////////////////////////

using namespace std;

// Private Implementation
//------------------------

//! mix a list of signals on n bus
static siglist mix(const siglist& lsig, int nbus)
{
    int nlines = (int)lsig.size();

    siglist dst(nbus);

    for (int b = 0; b < nbus; b++) {
        Tree t = (b < nlines) ? lsig[b] : sigInt(0);
        for (int i = b + nbus; i < nlines; i += nbus) {
            t = sigAdd(t, lsig[i]);
        }
        dst[b] = t;
    }
    return dst;
}

//! split a list of signals on n bus
static siglist split(const siglist& inputs, int nbus)
{
    int nlines = (int)inputs.size();

    siglist outputs(nbus);

    for (int b = 0; b < nbus; b++) {
        outputs[b] = inputs[b % nlines];
    }
    return outputs;
}

//! build a list of n projections of a recursive group
static siglist makeSigProjList(Tree t, int n)
{
    siglist l(n);
    for (int i = 0; i < n; i++) {
        l[i] = sigDelay0(sigProj(i, t));
    }
    return l;
}

//! build a list of n mem projections of a recursive group
static siglist makeMemSigProjList(Tree t, int n)
{
    siglist l(n);
    for (int i = 0; i < n; i++) {
        l[i] = sigDelay1(sigProj(i, t));
    }
    return l;
}

static inline siglist makeList(Tree t)
{
    siglist l(1);
    l[0] = t;
    return l;
}

static siglist listRange(const siglist& l, int i, int j)
{
    siglist r(j - i);
    for (int x = i; x < j; x++) {
        r[x - i] = l[x];
    }
    return r;
}

static siglist listConcat(const siglist& a, const siglist& b)
{
    int     n1 = (int)a.size();
    int     n2 = (int)b.size();
    siglist r(n1 + n2);

    for (int x = 0; x < n1; x++) {
        r[x] = a[x];
    }
    for (int x = 0; x < n2; x++) {
        r[x + n1] = b[x];
    }
    return r;
}

/**
 * Convert a tree list of signals into an stl vector of signals
 */
static void treelist2siglist(Tree l, siglist& r)
{
    r.clear();
    while (!isNil(l)) {
        r.push_back(hd(l));
        l = tl(l);
    }
}

static siglist listLift(const siglist& l)
{
    int     n = (int)l.size();
    siglist r(n);

    for (int i = 0; i < n; i++) {
        r[i] = lift(l[i]);
    }
    return r;
}

/**
 * Store the propagation result as a property of the arguments tuplet.
 *
 * @param args propagation arguments
 * @param value propagation result
 */
static void setPropagateProperty(Tree args, const siglist& lsig)
{
    setProperty(args, tree(gGlobal->PROPAGATEPROPERTY), listConvert(lsig));
}

/**
 * Retreive the propagation result as a property of the arguments tuplet.
 *
 * @param args propagation arguments
 * @param lsig the propagation result if any
 * @return true if a propagation result was stored
 */
static bool getPropagateProperty(Tree args, siglist& lsig)
{
    Tree value;
    if (getProperty(args, tree(gGlobal->PROPAGATEPROPERTY), value)) {
        treelist2siglist(value, lsig);
        return true;
    } else {
        return false;
    }
}

/**
 * Propagate a list of signals into a block diagram.
 *
 * @param slotenv environment associating slots and signals
 * @param path user interface group path
 * @param box the block diagram
 * @param lsig the list of input signals to propagate
 * @return the resulting list of output signals
 */
static siglist realPropagate(Tree slotenv, Tree path, Tree box, const siglist& lsig);

// Collect the leaf numbers of tree l into vector v.
// return true if l is a number or a parallel tree of numbers.
static bool isIntTree(Tree l, vector<int>& v)
{
    int    n;
    double r;
    Tree   x, y;

    if (isBoxInt(l, &n)) {
        v.push_back(n);
        return true;

    } else if (isBoxReal(l, &r)) {
        v.push_back(int(r));
        return true;

    } else if (isBoxPar(l, x, y)) {
        return isIntTree(x, v) && isIntTree(y, v);

    } else {
        stringstream error;
        error << "ERROR : file " << __FILE__ << ':' << __LINE__
              << ", not a valid list of numbers : " << boxpp(l) << endl;
        throw faustexception(error.str());
    }
}

/**
 * Propagate a list of signals into a block diagram. Actual function.
 *
 * @param slotenv environment associating slots and signals
 * @param path user interface group path
 * @param box the block diagram
 * @param lsig the list of input signals to propagate
 * @return the resulting list of output signals
 */
static siglist realPropagate(Tree slotenv, Tree path, Tree box, const siglist& lsig)
{
    int    i;
    double r;
    prim0  p0;
    prim1  p1;
    prim2  p2;
    prim3  p3;
    prim4  p4;
    prim5  p5;

    Tree t1, t2, t3, ff, label, cur, min, max, step, type, name, file, slot, body, chan;
    tvec wf;

    xtended* xt = (xtended*)getUserData(box);

    // Extended Primitives

    if (xt) {
        faustassert(lsig.size() == xt->arity());
        return makeList(xt->computeSigOutput(lsig));
    }

    // Numbers and Constants

    else if (isBoxInt(box, &i)) {
        faustassert(lsig.size() == 0);
        return makeList(sigInt(i));
    } else if (isBoxReal(box, &r)) {
        faustassert(lsig.size() == 0);
        return makeList(sigReal(r));
    }

    // A Waveform has two outputs it size and a period signal representing its content

    else if (isBoxWaveform(box)) {
        faustassert(lsig.size() == 0);
        const tvec br = box->branches();
        return listConcat(makeList(sigInt(int(br.size()))), makeList(sigWaveform(br)));
    }

    else if (isBoxFConst(box, type, name, file)) {
        faustassert(lsig.size() == 0);
        return makeList(sigFConst(type, name, file));
    }

    else if (isBoxFVar(box, type, name, file)) {
        faustassert(lsig.size() == 0);
        return makeList(sigFVar(type, name, file));
    }

    // Wire and Cut

    else if (isBoxCut(box)) {
        faustassert(lsig.size() == 1);
        return siglist();
    }

    else if (isBoxWire(box)) {
        faustassert(lsig.size() == 1);
        return lsig;
    }

    // Slots and Symbolic Boxes

    else if (isBoxSlot(box)) {
        Tree sig;
        faustassert(lsig.size() == 0);
        if (!searchEnv(box, sig, slotenv)) {
            sig = sigInput(++gGlobal->gDummyInput);
        }
        return makeList(sig);
    }

    else if (isBoxSymbolic(box, slot, body)) {
        faustassert(lsig.size() > 0);
        return propagate(pushEnv(slot, lsig[0], slotenv), path, body,
                         listRange(lsig, 1, (int)lsig.size()));
    }

    // Primitives

    else if (isBoxPrim0(box, &p0)) {
        faustassert(lsig.size() == 0);
        return makeList(p0());
    }

    else if (isBoxPrim1(box, &p1)) {
        faustassert(lsig.size() == 1);
        num n;
        if (isNum(lsig[0], n)) {
            return makeList(simplify(p1(lsig[0])));
        } else {
            return makeList(p1(lsig[0]));
        }
    }

    else if (isBoxPrim2(box, &p2)) {
        // cerr << "prim2 receive : " << ppsig(lsig) << endl;
        faustassert(lsig.size() == 2);
        if (p2 == &sigEnable) {
            if (gGlobal->gEnableFlag) {
                // special case for sigEnable that requires a transformation
                // enable(X,Y) -> sigControl(X*Y, Y!=0)
                return makeList(sigControl(sigMul(lsig[0], lsig[1]), sigNE(lsig[1], sigReal(0.0))));
            } else {
                // If gEnableFlag is false we replace enable by a simple multiplication
                return makeList(sigMul(lsig[0], lsig[1]));
            }
        } else if (p2 == &sigControl) {
            if (gGlobal->gEnableFlag) {
                // special case for sigControl that requires a transformation
                // control(X,Y) -> sigControl(X, Y!=0)
                return makeList(sigControl(lsig[0], sigNE(lsig[1], sigReal(0.0))));
            } else {
                // If gEnableFlag is false we replace control by identity function
                return makeList(lsig[0]);
            }
        } else {
            num n, m;
            if (isNum(lsig[0], n) && isNum(lsig[1], m)) {
                return makeList(simplify(p2(lsig[0], lsig[1])));
            } else {
                return makeList(p2(lsig[0], lsig[1]));
            }
        }
    }

    else if (isBoxPrim3(box, &p3)) {
        faustassert(lsig.size() == 3);
        return makeList(p3(lsig[0], lsig[1], lsig[2]));
    }

    else if (isBoxPrim4(box, &p4)) {
        faustassert(lsig.size() == 4);
        return makeList(p4(lsig[0], lsig[1], lsig[2], lsig[3]));
    }

    else if (isBoxPrim5(box, &p5)) {
        return makeList(p5(lsig[0], lsig[1], lsig[2], lsig[3], lsig[4]));
    }

    else if (isBoxFFun(box, ff)) {
        faustassert(int(lsig.size()) == ffarity(ff));
        return makeList(sigFFun(ff, listConvert(lsig)));
    }

    // User Interface Widgets

    else if (isBoxButton(box, label)) {
        faustassert(lsig.size() == 0);
        return makeList(sigButton(normalizePath(cons(label, path))));
    }

    else if (isBoxCheckbox(box, label)) {
        faustassert(lsig.size() == 0);
        return makeList(sigCheckbox(normalizePath(cons(label, path))));
    }

    else if (isBoxVSlider(box, label, cur, min, max, step)) {
        faustassert(lsig.size() == 0);
        return makeList(sigVSlider(normalizePath(cons(label, path)), cur, min, max, step));
    }

    else if (isBoxHSlider(box, label, cur, min, max, step)) {
        faustassert(lsig.size() == 0);
        return makeList(sigHSlider(normalizePath(cons(label, path)), cur, min, max, step));
    }

    else if (isBoxNumEntry(box, label, cur, min, max, step)) {
        faustassert(lsig.size() == 0);
        return makeList(sigNumEntry(normalizePath(cons(label, path)), cur, min, max, step));
    }

    else if (isBoxVBargraph(box, label, min, max)) {
        faustassert(lsig.size() == 1);
        return makeList(sigVBargraph(normalizePath(cons(label, path)), min, max, lsig[0]));
    }

    else if (isBoxHBargraph(box, label, min, max)) {
        faustassert(lsig.size() == 1);
        return makeList(sigHBargraph(normalizePath(cons(label, path)), min, max, lsig[0]));
    }

    else if (isBoxSoundfile(box, label, chan)) {
        faustassert(lsig.size() == 2);
        Tree    soundfile = sigSoundfile(normalizePath(cons(label, path)));
        Tree    part      = lsig[0];
        int     c         = tree2int(chan);
        siglist lsig2(c + 2);
        lsig2[0] = sigSoundfileLength(soundfile, part);
        lsig2[1] = sigSoundfileRate(soundfile, part);

        // compute bound limited read index : int(max(0, min(ridx,length-1)))
        Tree ridx = sigMax(sigInt(0), sigMin(lsig[1], sigSub(lsig2[0], sigInt(1))));
        for (int i1 = 0; i1 < c; i1++) {
            lsig2[i1 + 2] = sigSoundfileBuffer(soundfile, sigInt(i1), part, ridx);
        }
        return lsig2;
    }

    // User Interface Groups

    else if (isBoxVGroup(box, label, t1)) {
        return propagate(slotenv, cons(cons(tree(0), label), path), t1, lsig);
    }

    else if (isBoxHGroup(box, label, t1)) {
        return propagate(slotenv, cons(cons(tree(1), label), path), t1, lsig);
    }

    else if (isBoxTGroup(box, label, t1)) {
        return propagate(slotenv, cons(cons(tree(2), label), path), t1, lsig);
    }

    // Block Diagram Composition Algebra

    else if (isBoxSeq(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        // Connection coherency is checked in evaluateBlockDiagram
        faustassert(out1 == in2);
        return propagate(slotenv, path, t2, propagate(slotenv, path, t1, lsig));
    }

    else if (isBoxPar(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        // No restriction in connection
        return listConcat(propagate(slotenv, path, t1, listRange(lsig, 0, in1)),
                          propagate(slotenv, path, t2, listRange(lsig, in1, in1 + in2)));
    }

    else if (isBoxSplit(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        // Connection coherency is checked in evaluateBlockDiagram
        siglist l1 = propagate(slotenv, path, t1, lsig);
        siglist l2 = split(l1, in2);
        return propagate(slotenv, path, t2, l2);
    }

    else if (isBoxMerge(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        // Connection coherency is checked in evaluateBlockDiagram
        siglist l1 = propagate(slotenv, path, t1, lsig);
        siglist l2 = mix(l1, in2);
        return propagate(slotenv, path, t2, l2);
    }

    else if (isBoxRec(box, t1, t2)) {
        int in1, out1, in2, out2;
        getBoxType(t1, &in1, &out1);
        getBoxType(t2, &in2, &out2);

        // The environment must also be lifted
        Tree slotenv2 = lift(slotenv);

        // Connection coherency is checked in evaluateBlockDiagram
        siglist l0 = makeMemSigProjList(ref(1), in2);
        siglist l1 = propagate(slotenv2, path, t2, l0);
        siglist l2 = propagate(slotenv2, path, t1, listConcat(l1, listLift(lsig)));
        Tree    g  = rec(listConvert(l2));

        // Compute output list of recursive signals
        siglist ol(out1);  // output list
        int     p = 0;     // projection number

        for (const auto& exp : l2) {
            if (exp->aperture() > 0) {
                // it is a regular recursive expression branch
                ol[p] = sigDelay0(sigProj(p, g));
            } else {
                // this expression is a closed term,
                // it doesn't need to be inside this recursion group.
                // cerr << "degenerate recursion " << exp << endl;
                ol[p] = exp;
            }
            p++;
        }

        return ol;
    }

    else if (isBoxEnvironment(box)) {
        faustassert(lsig.size() == 0);
        return siglist();

    } else if (isBoxRoute(box, t1, t2, t3)) {
        int         ins, outs;
        vector<int> route;
        siglist     outsigs;
        // ins, outs, route are casted to int in realeval
        if (isBoxInt(t1, &ins) && isBoxInt(t2, &outs) && isIntTree(t3, route)) {
            // initialize output signals
            for (int i1 = 0; i1 < outs; i1++) {
                outsigs.push_back(sigInt(0));
            }

            // route propagation
            size_t m = route.size() - 1;
            for (size_t i1 = 0; i1 < m; i1 += 2) {
                int src = route[i1];
                int dst = route[i1 + 1];
                if ((dst > 0) & (dst <= outs)) {
                    // we have a destination
                    Tree exp = outsigs[dst - 1];
                    if ((src > 0) & (src <= ins)) {
                        // we have a source
                        outsigs[dst - 1] = simplifyingAdd(exp, lsig[src - 1]);
                    }
                }
            }
            return outsigs;

        } else {
            stringstream error;
            error << "ERROR : file " << __FILE__ << ':' << __LINE__
                  << ", invalid route expression : " << boxpp(box) << endl;
            throw faustexception(error.str());
        }
    }
    cerr << "ASSERT : file " << __FILE__ << ':' << __LINE__
         << ", unrecognised box expression : " << boxpp(box) << endl;
    faustassert(false);

    return siglist();
}

//------------------
// Public Interface
//------------------

/**
 * Propagate a list of signals into a block diagram. Do memoization.
 *
 * @param slotenv environment associating slots and signals
 * @param path user interface group path
 * @param box the block diagram
 * @param lsig the list of input signals to propagate
 * @return the resulting list of output signals
 */

siglist propagate(Tree slotenv, Tree path, Tree box, const siglist& lsig)
{
    Tree    args = tree(gGlobal->PROPAGATEPROPERTY, slotenv, path, box, listConvert(lsig));
    siglist result;
    if (!getPropagateProperty(args, result)) {
        result = realPropagate(slotenv, path, box, lsig);
        setPropagateProperty(args, result);
    }
    // cerr << "propagate in " << boxpp(box) << endl;
    // for (int i = 0; i < lsig.size(); i++) { cerr << " -> signal " << i << " : " << *(lsig[i]) <<
    // endl; } cerr << endl;
    return result;
}

//! build a list of n inputs
siglist makeSigInputList(int n)
{
    siglist l(n);
    for (int i = 0; i < n; i++) {
        l[i] = sigInput(i);
    }
    return l;
}
/**
 * Top level propagate a list of signals into a block diagram. Do memoization.
 *
 * @param path user interface group path
 * @param box the block diagram
 * @param lsig the list of input signals to propagate
 * @return the resulting list of output signals
 */

Tree boxPropagateSig(Tree path, Tree box, const siglist& lsig)
{
    std::cerr << "boxPropagateSig 1 " << *box << std::endl;
    box = run_box_route_optimization(box);
    std::cerr << "boxPropagateSig 2 " << *box << std::endl;

    return listConvert(propagate(gGlobal->nil, path, box, lsig));
}
