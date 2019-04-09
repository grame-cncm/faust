/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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

#include "dsp_factory.hh"
#include "faust/dsp/dsp.h"

// Global API access lock
TLockAble* dsp_factory_imp::gDSPFactoriesLock = nullptr;

void* dsp_factory_imp::allocate(size_t size)
{
    if (fManager) {
        return fManager->allocate(size);
    } else {
        faustassert(false);
        return nullptr;
    }
}
void dsp_factory_imp::destroy(void* ptr)
{
    if (fManager) {
        fManager->destroy(ptr);
    } else {
        faustassert(false);
    }
}

extern "C" EXPORT bool startMTDSPFactories()
{
    try {
        if (!dsp_factory_imp::gDSPFactoriesLock) {
            dsp_factory_imp::gDSPFactoriesLock = new TLockAble();
        }
        return true;
    } catch (...) {
        return false;
    }
}

extern "C" EXPORT void stopMTDSPFactories()
{
    delete dsp_factory_imp::gDSPFactoriesLock;
    dsp_factory_imp::gDSPFactoriesLock = nullptr;
}
