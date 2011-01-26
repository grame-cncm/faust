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

#include <windows.h>

#include "TThreads.h"


//_____________________________________________________________________
TThreads::TThreads () : fThread(0) {}

//_____________________________________________________________________
TThreads::TThreads (ThreadProcPtr proc, void * arg, int priority)
	: fThread (0)
{
	Create (proc, arg, priority);
}

//_____________________________________________________________________
int	TThreads::MapPriority (int priority)
{
	static BOOL classSet = FALSE;
	switch (priority) {
		case ClientHighPriority:
			return THREAD_PRIORITY_HIGHEST;
		case ClientRTPriority:
			return THREAD_PRIORITY_TIME_CRITICAL;
		case ServerHighPriority:
			if (!classSet) 
				classSet=SetPriorityClass (GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
			return THREAD_PRIORITY_HIGHEST;
		case ServerRTPriority:
			if (!classSet) 
				classSet=SetPriorityClass (GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
			SetPriorityClass (GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
			return THREAD_PRIORITY_TIME_CRITICAL;
		default:
			return THREAD_PRIORITY_NORMAL;
	}
}

//_____________________________________________________________________
int	TThreads::SetPriority (int priority)
{
	priority = MapPriority(priority);
	if (GetThreadPriority (fThread) == priority)
		return TRUE;
	if (!SetThreadPriority (fThread, MapPriority(priority)))
		return TRUE;
	return FALSE;
}

//_____________________________________________________________________
int	TThreads::Create (ThreadProcPtr proc, void * arg, int priority)
{
	DWORD id;
	fThread = CreateThread(NULL, 0, proc, arg, 0, &id);
	if (fThread) {
		SetPriority (priority);
		return TRUE;
	}
	return FALSE;
}

//_____________________________________________________________________
void TThreads::Join (int timeout)
{
	if (fThread) {
		WaitForSingleObject (fThread, timeout ? timeout : INFINITE);
		fThread = 0;
	}
}

//_____________________________________________________________________
void TThreads::Stop ()
{
	if (fThread) {
		WaitForSingleObject (fThread, 1000);
		CloseHandle (fThread);
		fThread = 0;
	}
}
