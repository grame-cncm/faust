/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2006 GRAME, Centre National de Creation Musicale
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

#ifndef _RECURSIVNESS_
#define _RECURSIVNESS_

#include "signals.hh"

/**
 * Annotate a signal with recursivness information, the amount of
 * recursive dependencies of a signal. Should be used before
 * calling getRecursivness.
 * @param sig signal to annotate
 */
void recursivnessAnnotation(Tree sig);

/**
 * Return the recursivness of a previously
 * annotated signal. An error is generated
 * if the signal has no recursivness property.
 * @param sig signal
 * @return recursivness of the signal
 */
int getRecursivness(Tree t);

/**
 * Return the set of recursive symbols appearing in a signal.
 * @param sig the signal to analyze
 * @return the set of symbols
 */
Tree symlist(Tree sig);

#endif
