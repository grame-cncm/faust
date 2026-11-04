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

// The probe of the argument evaluation order : prints the order in which a
// compiler evaluates the three arguments of one call. A determinism pair must
// join two compilers that answer differently (build-two.sh checks it) : two
// compilers that agree cannot reveal an unsequenced construction.
#include <cstdio>
static int  g(const char* s) { std::printf("%s", s); return 0; }
static void f(int, int, int) {}
int main() { f(g("1"), g("2"), g("3")); std::printf("\n"); return 0; }
