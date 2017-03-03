 /*

  Copyright (C) 2006,2007 Grame

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

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

class TMutex 
{
	
	private:
	
	#ifdef _WIN32
		HANDLE fMutex;
	#else
		pthread_mutex_t fMutex;  
	#endif

	public:

	#ifdef _WIN32

		TMutex()
		{		
			fMutex = CreateMutex(0, FALSE, 0);
            if (!fMutex) throw std::bad_alloc();
		}
		virtual ~TMutex()
		{
			CloseHandle(fMutex);
		}
		
		bool Lock()
		{	
			 return (WaitForSingleObject(fMutex, INFINITE) == WAIT_OBJECT_0);
		}
		
		bool TryLock()
		{	
			 return (WaitForSingleObject(fMutex, 0) == WAIT_TIMEOUT);
		}

		void Unlock()
		{	
			ReleaseMutex(fMutex);
		}

	#else

		TMutex()
		{
			// Use recursive mutex
			pthread_mutexattr_t mutex_attr;
			if (pthread_mutexattr_init(&mutex_attr) != 0) throw std::bad_alloc();
			if (pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE) != 0) throw std::bad_alloc();
			if (pthread_mutex_init(&fMutex, &mutex_attr) != 0) throw std::bad_alloc();
		}
		virtual ~TMutex()
		{
			pthread_mutex_destroy(&fMutex);
		}
		
		bool Lock()
		{
            return (pthread_mutex_lock(&fMutex) == 0);
		}
		
		bool TryLock()
		{
			return (pthread_mutex_trylock(&fMutex) == 0);
		}

		void Unlock()
		{
			pthread_mutex_unlock(&fMutex);
		}

	#endif
};

class TLockAble
{

	private:

		TMutex fMutex;

	public:

		TLockAble() {}
		virtual ~TLockAble() {}

		bool Lock()
		{	
			return fMutex.Lock();
		}

		void Unlock()
		{	
			fMutex.Unlock();
		}
        
        bool TryLock()
		{	
			return fMutex.TryLock();
		}
		
};

class TLock
{
	private:
	
        TLockAble* fObj;
				
	public:
	
        TLock(TLockAble* obj):fObj(obj)
        {	
            if (fObj) fObj->Lock();
        }
		
        TLock(const TLockAble* obj):fObj((TLockAble*)obj)
        {	
            if (fObj) fObj->Lock();
        }	
		
        virtual ~TLock()
        {
            if (fObj) fObj->Unlock();
        }
};

#endif
