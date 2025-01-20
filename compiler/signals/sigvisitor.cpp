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

#include <iostream>

#include "exception.hh"
#include "signals.hh"
#include "sigvisitor.hh"

using namespace std;

#undef TRACE

Tree unclockSignal(Tree sig)
{
    // We remove the clock
    if (Tree h, y; isSigClocked(sig, h, y)) {
        return unclockSignal(y);
    }

    if (Tree body; isRec(sig, body)) {
        return rec(unclockSignal(body));
    }

    if (int level; isRef(sig, level)) {
        return ref(level);
    }

    // symbolic recursion not supposed to happen here
    if (Tree var, body; isRec(sig, var, body)) {
        std::cerr << "symbolic recursion not supposed to happen here" << std::endl;
        faustassert(false);
    }

    // generic case
    const Node& n = sig->node();

    const tvec& br = sig->branches();
    tvec        br2;
    for (Tree t : br) {
        br2.push_back(unclockSignal(t));
    }
    Tree sig2 = tree(n, br2);
#ifdef TRACE
    std::cerr << "\n\nunclock of : " << *sig << std::endl;
    std::cerr << "gives      : " << *sig2 << std::endl;
#endif
    return sig2;
}