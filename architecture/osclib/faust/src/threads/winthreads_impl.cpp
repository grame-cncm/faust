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
#ifdef WIN32

#include <windows.h>
#include "TThreads.h"

//_____________________________________________________________________
static DWORD WINAPI  baseThreadProc (LPVOID  ptr)
{
	TThreads* thread = (TThreads*)ptr;
	thread->running (true);
	thread->run();
	thread->running (false);
	return 0;
}

//_____________________________________________________________________
TThreads::TThreads () : fThread(0) {}

//_____________________________________________________________________
int	TThreads::SetPriority (int priority)
{
	if (!SetThreadPriority (fThread, priority))
		return TRUE;
	return FALSE;
}

//_____________________________________________________________________
bool TThreads::start (int priority)
{
	DWORD id;
	fThread = CreateThread(NULL, 0, baseThreadProc, this, 0, &id);
	if (fThread) {
		SetPriority (priority);
		return true;	
	}
	return false;	
}

//_____________________________________________________________________
void TThreads::quit ()
{
	if (fThread) {
		WaitForSingleObject (fThread, 1000);
		CloseHandle (fThread);
		fThread = 0;
	}
}

#endif
