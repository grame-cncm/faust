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
 * @file sigFIR.hh
 * @author Yann ORLAREY (yann.orlarey@inria.fr)
 * @brief Operations and predicats for FIR signals: [S, C0, C1, ...] = C0*S + C1*S@1 + ...
 * @version 0.1
 * @date 2024-01-10
 *
 * @copyright Copyright (c) 2024 INRIA
 *
 */
#pragma once

#include "signals.hh"

//=========================================================================
// Set of operations and predicates to create and manipulate FIR signals.
// A FIR is described by a vector V=[S,C0,C1,...]
// such that sigFIR([S,C0,C1,...]) = C0*S + C1*S@1 + C2*S@2,...]
// We assume that the last coefficient is non zero and that we have at
// least two coefficients.
//=========================================================================

//-------------------------------------------------------------------------
// FIR operations
//-------------------------------------------------------------------------

// Create a FIR form a signal with a fixed delay
Tree makeSigFIR(Tree sig, int d);

// Create a FIR by delaying an existing FIR
// Tree delaySigFIR(Tree sig, int d);

Tree delaySigFIR(Tree s1, Tree s2);

// Add two FIRs, or sigAdd(s1,s2) if s1 and s2 are not compatible FIRs
Tree addSigFIR(Tree s1, Tree s2);

// Subtract two FIRs, or sigSub(s1,s2) if s1 and s2 are not compatible FIRs
Tree subSigFIR(Tree s1, Tree s2);

// If it is a FIR, invert the coefficients
Tree negSigFIR(Tree s1);

// Multiply a FIR by a signal
Tree mulSigFIR(Tree s1, Tree s2);

// Divide a FIR by a signal
Tree divSigFIR(Tree s1, Tree s2);

// Simplify a FIR by removing trailing zeros and degenerated cases
Tree simplifyFIR(Tree sig);

// Promote the signal or the coefficients of a FIR if needed
Tree promotionSigFIR(Tree sig);

// Convert a FIR back to a combination of Delays
// (usefull to compute types ans intervals)
Tree convertFIR2Sig(Tree sig);

// Try to combine the FIRs of t1 and t2 and
// returns the resulting signal
Tree smartAddSigFIR(Tree t1, Tree t2);

//-------------------------------------------------------------------------
// FIR predicates
//-------------------------------------------------------------------------

// True if the signal is a FIR with only one non-zero coefficient
bool isSigFIR1Coef(Tree sig);

// True if the signal is a FIR with all non-zero coefficient are constant
// bool isSigFIRConstCoef(Tree sig);

// True if the signal is a FIR with all non-zero coefficient are constant or ctrl rate
// bool isSigFIRBlockCoef(Tree sig);

bool haveEquivCoefs(const tvec& V1, const tvec& V2);

bool haveComplementaryCoefs(const tvec& V1, const tvec& V2);

//-------------------------------------------------------------------------
// Auxiliary functions
//-------------------------------------------------------------------------

// remove trailing zero coefficients
void normalizeFIRCoefs(tvec& V);

// For an addition
Tree combineFIRs(Tree x, Tree y, bool subflag);

// combine FIRs according to their input signal
void combine(std::map<Tree, Tree>& M, bool subflag, Tree sig);

// internal tests for FIR reconstruction
void testFIR();

double FIRWorstPeakGain(const std::vector<double>& b_coeffs, int num_points = 10000);
