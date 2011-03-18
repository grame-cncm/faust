/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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


#include "schema.h"
#include <assert.h>

using namespace std;


void collector::computeVisibleTraits()
{
    bool modified;
    while (modified) {
        modified = false;
        for (set<trait>::iterator p = fTraits.begin(); p != fTraits.end(); p++) {
            if (fOutputs.count(p->start)) {
                fWithInput.insert(*p);
                fOutputs.insert(p->end);
                modified = true;
            }
            if (fInputs.count(p->end)) {
                fWithOutput.insert(*p);
                fInputs.insert(p->start);
                modified = true;
            }
        }
    }
}

bool collector::isVisible(const trait& t)
{
    return fWithInput.count(t) && fWithOutput.count(t);
}

void collector::draw(device& dev)
{
    computeVisibleTraits();
    for (set<trait>::iterator p = fTraits.begin(); p != fTraits.end(); p++) {
        if (isVisible(*p)) p->draw(dev);
    }
}

