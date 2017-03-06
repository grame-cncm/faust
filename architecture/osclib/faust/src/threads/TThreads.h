/*

  Copyright (C) 2011 Grame

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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __TThreads__
#define __TThreads__

#ifdef WIN32

	#include <windows.h>
	#define ThreadAPI(proc, arg) DWORD WINAPI proc(LPVOID arg)

	typedef LPTHREAD_START_ROUTINE ThreadProcPtr;
	typedef HANDLE	ThreadHandle;
	
#else

	#include <pthread.h>
	#define ThreadAPI(proc, arg) void* proc (void* arg)
	
	typedef void* (* ThreadProcPtr) (void* ptr);
	typedef	pthread_t	ThreadHandle;

#endif

//___________________________________________________________________
/*!
	\brief cross platform threads support

	Based on pthread on linux and mac and 
	Windows native threads on Windows
*/
class TThreads
{
    public:
    
        enum { kNormalPriority = 0 };

        TThreads();
        virtual ~TThreads()	{ quit (); }

        virtual void	run() = 0;

        bool start(int priority = kNormalPriority);
        bool isRunning() const	{ return fRunning; }
        void quit();

        void running(bool state)	{ fRunning = state; }

    private:
    
        int SetPriority(int priority);

        bool fRunning;
        ThreadHandle fThread;	// the thread handler
};

#endif
