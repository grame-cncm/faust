/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#pragma once

#include <map>
#include <vector>

#include "tlib.hh"

/**
 * The matrix form (spec LA-FORME-MATRICE) : the fourth gathering. K
 * n-ary sums whose non-zero terms are mul(slow c, x) over a SHARED
 * operand tuple are one matrix-vector product that does not know it.
 * No constructor is introduced -- the identity of a family is an
 * ANALYSIS KEY (the interned operand-tuple list), never a node ; this
 * pass only detects and plans, the emission regimes decide.
 *
 * A family : K >= 3 member sums, tuple = the UNION of their operands
 * (n >= 4), a missing column is a zero coefficient, and the total
 * zero budget of the K x n table is at most 10% (starting calibration
 * -- the election arbitrates anyway).
 */
struct MatrixFamily {
    Tree                           key;    ///< interned operand-tuple list
    std::vector<Tree>              tuple;  ///< the operands, canonical order
    std::vector<Tree>              rows;   ///< the member sum nodes
    std::vector<std::vector<Tree>> coef;   ///< coef[r][j], sigInt(0) when absent
};

struct MatrixPlans {
    std::map<Tree, std::pair<int, int>> rowOf;     ///< sum node -> (family, row)
    std::vector<MatrixFamily>           families;  ///< the detected families

    bool isRow(Tree t) const { return rowOf.count(t) != 0; }
};

/// Detect the matrix families of L. Analysis only : L is not modified.
MatrixPlans revealMatrix(Tree L);
