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

#else

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "TThreads.h"

//_____________________________________________________________________
static void * baseThreadProc (void * ptr)
{
	TThreads* thread = (TThreads*)ptr;
	thread->running (true);
	thread->run();
	thread->running (false);
	pthread_exit(NULL);
	return 0;
}

//_____________________________________________________________________
TThreads::TThreads () : fRunning(false), fThread(0) {}

//_____________________________________________________________________
int	TThreads::SetPriority (int priority)
{
	if (fThread) {
		struct sched_param param;
		
		param.sched_priority = priority;
		if (!pthread_setschedparam (fThread, SCHED_OTHER, &param)) 
			return true;
	}
	return false;
}

//_____________________________________________________________________
bool TThreads::start (int priority)
{
	int ret = pthread_create(&fThread, NULL, baseThreadProc, this);
	if (!ret) {
		SetPriority (priority);
		return true;	
	}
	return false;	
}

//_____________________________________________________________________
void TThreads::quit ()
{
#ifndef android
	if (fThread) {
		void *threadRet; 
		pthread_cancel (fThread);
		pthread_join (fThread, &threadRet);
		fThread = 0;
	}
#else
#warning "pthread_cancel not implemented on android"
#endif
}
#endif
