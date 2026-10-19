/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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

#pragma once

#include "tlib.hh"

/**
 * The normal form written with the binary operations of the signal language, for the
 * backends that only know them (VHDL, SDF3) : Sum and Prod as left chains, a negated term
 * subtracted, Neg as 0 - x, FIR as its weighted taps, IIR and IRM as recursive groups,
 * Mix, Frac, Cfrac, Tpt, Phase and Bpf as their definitions. The result is typed.
 */
Tree lowerNormalForm(Tree L);
