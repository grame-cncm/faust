/************************************************************************
 ************************************************************************
    TLIB : tree library
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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

#include "garbageable.hh"

#include <list>

// The allocation registries. In the Faust compiler these lived in the
// 'global' singleton; the library owns them directly so it has no
// dependency on any host application state.
//
// Construct-on-first-use : a Garbageable can be allocated from another
// translation unit's static initializer, whose order relative to this file's
// statics is unspecified by C++. Function-local statics are initialized on
// first call, which makes the registries safe whatever the order.
static std::list<Garbageable*>& rawObjectTable()
{
    static std::list<Garbageable*> table;
    return table;
}

static std::list<Garbageable*>& arrayObjectTable()
{
    static std::list<Garbageable*> table;
    return table;
}

// True while cleanup() is running: individual deletes then skip the
// (pointless and slow) removal from the registry.
static bool gHeapCleanup = false;

void Garbageable::cleanup()
{
    gHeapCleanup = true;

    for (Garbageable* obj : rawObjectTable()) {
        delete obj;
    }
    rawObjectTable().clear();

    for (Garbageable* obj : arrayObjectTable()) {
        delete[] obj;
    }
    arrayObjectTable().clear();

    gHeapCleanup = false;
}

void* Garbageable::operator new(std::size_t size)
{
    Garbageable* res = static_cast<Garbageable*>(::operator new(size));
    rawObjectTable().push_front(res);
    return res;
}

void Garbageable::operator delete(void* ptr)
{
    // An object may be deleted individually during a session: it then has to
    // be removed from the registry so cleanup() doesn't free it twice.
    if (!gHeapCleanup) {
        rawObjectTable().remove(static_cast<Garbageable*>(ptr));
    }
    ::operator delete(ptr);
}

void* Garbageable::operator new[](std::size_t size)
{
    Garbageable* res = static_cast<Garbageable*>(::operator new[](size));
    arrayObjectTable().push_front(res);
    return res;
}

void Garbageable::operator delete[](void* ptr)
{
    if (!gHeapCleanup) {
        arrayObjectTable().remove(static_cast<Garbageable*>(ptr));
    }
    ::operator delete[](ptr);
}
