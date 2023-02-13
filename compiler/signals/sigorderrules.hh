/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef __SIGORDER__
#define __SIGORDER__

#include "signals.hh"

/**
 * Retrieve the order annotation (between 0 and 3) of a signal.
 * (compute the order the first time). Orders have the following meanings:
 *    0 : numbers
 *    1 : constants
 *    2 : user interface values
 *    3 : audio values
 * @param sig the signal we want to know the order
 * @return the order number
 */
int getSigOrder(Tree sig);

#endif
