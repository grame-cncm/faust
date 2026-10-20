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
 * The place of a gain through a linear node, one place whatever the writing of the
 * program. A gain is a factor of order 1 or less (a number, a constant of the sample
 * rate) : it commutes with a FIR, an IIR and an IRM.
 *
 * - a number enters the coefficients of a FIR : FIR(k*x; b) and k*FIR(x; b) are
 *   FIR(x; k*b) ;
 * - any other gain goes to the output, so that the node itself can be shared :
 *   FIR(g*x; b) is g*FIR(x; b), IIR(g*x; c) is g*IIR(x; c), IRM(g*x; c) is g*IRM(x; c) ;
 * - g*IIR(x; c) of order 1, g a gain times the weight 1 - c of its input, is
 *   (g/(1 - c))*IRM(x; c) ;
 * - a sum whose terms change is written again, so that the contributions of a source
 *   still gather in one FIR ;
 * - a mix has one orientation : mix(c, a, b) = mix(1 - c, b, a), its operands in the order
 *   of the normal form.
 *
 * Applied after the IIR, IRM and Bpf reveals, whose gains it places too.
 */
Tree placeGains(Tree L);
