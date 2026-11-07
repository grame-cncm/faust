/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.
 ************************************************************************
 ************************************************************************/

#pragma once

#include <unordered_map>

#include "signals.hh"
#include "sumLanes.hh"

/**
 * The translation of a certified program into its computation form (computeSignals.hh,
 * FaustAlgebra/ComputeAlgebra.hh) : the decisions the code generation used to read in the
 * certified intervals are taken here, once, and become data of the nodes. The intervals
 * are read by this translation only.
 *
 * Every other node is rebuilt as it is (a recursive group with a fresh variable, the
 * immutability protocol). A translated node keeps the certified type of its source : the
 * same value, only the way to compute it is decided. A tree built here is newer than its
 * source : an emission that orders its statements by the creation of the trees (ocpp)
 * may order them otherwise, the same computations.
 */
class ComputeForm {
   public:
    /// L : the certified program (typeAnnotation done), a list of roots or a signal. With
    /// lower, the program translated is then lowered (spec LA-FORME-DE-CALCUL, "Le nouvel
    /// ordre", step 2) : shareSums, exactWeights and sumLanes (lanes in the given order),
    /// each under its option, outside the cone of the memory decisions (a delay amount, an
    /// index, an integer conversion), never under -fx (whose fixed-point types are read in
    /// the intervals)
    explicit ComputeForm(Tree L, bool lower = false, LaneOrder order = LaneOrder::kInterleaved);

    /// translates t, a part of the program or another root the emitter compiles (a
    /// condition atom, a display signal) : the same translation, shared nodes once
    Tree translate(Tree t);

    /// rebuilds a structure that holds signals of the source program (a condition, a list)
    /// on their translations ; a tree outside the program is left as it is
    Tree remap(Tree t);

    /// the translated program
    Tree program() const { return fProgram; }

   private:
    std::unordered_map<Tree, Tree> fImage;  ///< every source node -> its translation
    Tree                           fSource;     ///< the certified program
    Tree                           fProgram;
    void                           annotate();
    void                           lower(LaneOrder order);
};
