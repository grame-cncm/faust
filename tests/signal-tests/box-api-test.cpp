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

#include "faust/dsp/libfaust-box.h"
#include <iostream>
#include <cstddef>

#include "box-api-references.inc"

int main()
{
    const std::size_t linked = checkApiLinks();
    if (linked == 0) return 1;
    createLibContext();
    Box integer = boxInt(7);
    Box wire = boxWire();
    Box pair = boxPar(wire, integer);
    int value = -1;
    int inputs = -1;
    int outputs = -1;
    Box left = nullptr;
    Box right = nullptr;
    bool ok = isBoxInt(integer) && isBoxInt(integer, &value) && value == 7
           && isBoxWire(wire) && isBoxPar(pair, left, right)
           && left == wire && right == integer
           && getBoxType(pair, &inputs, &outputs) && inputs == 1 && outputs == 2;
    destroyLibContext();
    if (!ok) {
        std::cerr << "C++ box API checks failed\n";
        return 1;
    }
    std::cout << "C++ box API: " << linked << " function signatures linked; "
              << "constructors, predicates and arity passed\n";
    return 0;
}
