/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2024 INRIA
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

/**
 * @file sigIIR.hh
 * @author Yann ORLAREY (yann.orlarey@inria.fr)
 * @brief Operations and predicats for IIR signals: [V, X, C1, C2, ...] ==> (V = X + C1*V@1 + C2*V@2
 * + ...)
 * @version 0.1
 * @date 2024-01-15
 *
 * @copyright Copyright (c) 2024 INRIA
 *
 */

#pragma once

#include "signals.hh"

//=========================================================================
// Set of operations and predicates to create and manipulate IIR signals.
// A IIR is described by a vector [V,X,C1,C2,...] where V is a recursive
// variable projection : proj(i,W), X is the input signal of the filter
// and it is independent of W
// such that sigIIR([V,X,C1,C2,...]) = (V = X + C1*V@1 + C2*V@2 + ...)
// We assume that the last coefficient is non zero and that we have at
// least one coefficient C1.
//=========================================================================

//-------------------------------------------------------------------------
// IIR operations
//-------------------------------------------------------------------------

bool concernedIIR(Tree rt, Tree x, tvec& coef);

/**
 * @brief Try to create an IIR from a delayed signal
 *
 * @param rt recursive target group
 * @param jt recursive target projection
 * @param s1 the delayed signal
 * @param s2 the delay signal
 * @return Tree: IIR, sig, nil
 */

// Create an IIR from a recursive projection
Tree proj2SigIIR(Tree rt, Tree sig);

// Delay an IIR
Tree delaySigIIR(Tree rt, Tree x, Tree y);

// Add two IIRs
Tree addSigIIR(Tree rt, Tree s1, Tree s2);

// Subtract two IIRs
Tree subSigIIR(Tree rproj, Tree s1, Tree s2);

// Multiply an IIR by a signal
Tree mulSigIIR(Tree rproj, Tree s1, Tree s2);

// Divide an IIR by a signal
Tree divSigIIR(Tree rproj, Tree s1, Tree s2);

// Simplify an IIR by removing trailing zeros and degenerated cases
Tree simplifyFIR(Tree sig);

// Promote the signal or the coefficients of an IIR if needed
Tree promotionSigIIR(Tree sig);

// Convert an IIR back to a combination of Delays
// (usefull to compute types ans intervals)
Tree convertFIR2Sig(Tree sig);

Tree embeddedIIR(Tree rt, Tree fir);

//-------------------------------------------------------------------------
// IIR predicates
//-------------------------------------------------------------------------

bool hasNonValidArgs(Tree sig);
bool hasConcernedIIRArgs(Tree rt, Tree sig);

// True if the signal is an IIR with only one non-zero coefficient
bool isSigIIR1Coef(Tree sig);

// True if the signal is an IIR with all non-zero coefficient are constant
// bool isSigIIRConstCoef(Tree sig);

// True if the signal is an IIR with all non-zero coefficient are constant or ctrl rate
// bool isSigIIRBlockCoef(Tree sig);

bool haveEquivCoefs(const tvec& V1, const tvec& V2);

bool haveComplementaryCoefs(const tvec& V1, const tvec& V2);

//-------------------------------------------------------------------------
// Auxiliary functions
//-------------------------------------------------------------------------

// remove trailing zero coefficients
void normalizeFIRCoefs(tvec& V);

// internal tests for IIR reconstruction
void testFIR();

double IIRWorstPeakGain(const std::vector<double>& a_coeffs, int num_points = 10000);
