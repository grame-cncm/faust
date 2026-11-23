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

/**
 * The integer narrowing : the integer conversion of a real computed from integers, written
 * as the integer computation it is. Three exact laws, read on the certified intervals, with
 * p the bits of the significand of the program's precision (24 in single precision, 53 in
 * double) and B = min(2^p, 2^31 - 1) :
 *
 *  - float() goes up through the operations exact on the range : float(m) + float(n) =
 *    float(m + n), and alike for -, * and an n-ary sum, when every partial result lies in
 *    [-B, B] ; min and max, always ; a real number that is an integer of [-B, B] is that
 *    integer converted ;
 *  - int() goes down through min and max only : int(min(x, y)) = min(int(x), int(y)), and
 *    alike for max, because the conversion truncates and a nondecreasing function commutes
 *    with min and max on a total order. It never goes down through a sum :
 *    int(0.6 + 0.7) = 1, int(0.6) + int(0.7) = 0. x and y are valid (no NaN : the real min
 *    of the code is not that of the order there), and every x converted lies in the int32
 *    range, where the conversion is defined. The interval of a value read from outside (a
 *    control, an input, a sound file) is a convention, enforced after the read : the
 *    conversion never reaches such a value, and the clamp max(lo, min(hi, w)) of a control
 *    (-rui) is converted whole ;
 *  - where they meet, int(float(k)) = k, k in [-B, B] : float(k) is exact.
 *
 * A conversion is rewritten when the rewrite leaves fewer conversions computed at the
 * sample rate. The values are the same, bit for bit ; the bounds read hold at every sample
 * (none that holds over the analysis horizon only). The node rewritten keeps the type of
 * its source ; a node built has the type of its operation, its interval from its operands'.
 * Not under -fx. image, when given, receives every node of L with its rewriting. (-noin)
 */
Tree narrowIntegers(Tree L, std::unordered_map<Tree, Tree>* image = nullptr);
