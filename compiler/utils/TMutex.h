/*
 Copyright (C) 2006-2024 Grame

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
 research@grame.fr
*/

#ifndef __TMutex__
#define __TMutex__

#include <iostream>
#include <mutex>
#include <stdexcept>

class TMutex {
   private:
    std::recursive_mutex fMutex;

   public:
    TMutex()          = default;
    virtual ~TMutex() = default;

    // Lock the mutex (blocking)
    void Lock() { fMutex.lock(); }

    // Try to lock the mutex (non-blocking)
    bool TryLock() { return fMutex.try_lock(); }

    // Unlock the mutex
    void Unlock() { fMutex.unlock(); }
};

class TLockAble {
   private:
    TMutex fMutex;

   public:
    TLockAble()          = default;
    virtual ~TLockAble() = default;

    // Lock the mutex
    void Lock() { fMutex.Lock(); }

    // Unlock the mutex
    void Unlock() { fMutex.Unlock(); }

    // Try to lock the mutex
    bool TryLock() { return fMutex.TryLock(); }
};

class TLock {
   private:
    TLockAble* fObj;

   public:
    explicit TLock(TLockAble* obj) : fObj(obj)
    {
        if (fObj) {
            fObj->Lock();
        }
    }

    TLock(const TLockAble* obj) : fObj(const_cast<TLockAble*>(obj))
    {
        if (fObj) {
            fObj->Lock();
        }
    }

    virtual ~TLock()
    {
        if (fObj) {
            fObj->Unlock();
        }
    }
};

#endif
