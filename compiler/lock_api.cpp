/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2019 GRAME, Centre National de Creation Musicale
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

#include "lock_api.hh"

// Global API access lock
TLockAble* gDSPFactoriesLock = nullptr;

extern "C" LIBFAUST_API bool startMTDSPFactories()
{
    try {
        if (!gDSPFactoriesLock) {
            gDSPFactoriesLock = new TLockAble();
        }
        return true;
    } catch (...) {
        return false;
    }
}

extern "C" LIBFAUST_API void stopMTDSPFactories()
{
    delete gDSPFactoriesLock;
    gDSPFactoriesLock = nullptr;
}
