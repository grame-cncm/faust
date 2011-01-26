/*
  Copyright (c) Grame 2010

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr
  
*/

#ifndef __OSCFError__
#define __OSCFError__

#include <iostream>
#include "OSCStream.h"

namespace oscfaust
{

//--------------------------------------------------------------------------
/*!
\brief	OSC error stream

	Combines the \c cerr and \c oscerr streams
*/
typedef struct OSCFError {
	bool oscpending;
	OSCFError() { oscpending = false; }
} OSCFError;

typedef struct OSCFErrorEnd {
} OSCFErrEnd;


inline OSCFError& operator << (OSCFError& err, OSCFErrEnd end)
{
	std::cerr << std::endl;
#ifndef NO_OSC
	oscerr <<  OSCEnd();
	err.oscpending = false;
#endif
	return err;
}

template <typename T>	OSCFError& operator << (OSCFError& err, const T& arg)
{
	std::cerr << arg;
#ifndef NO_OSC
	if (!err.oscpending) {
		oscerr << OSCErr();
		err.oscpending = true;
	}
	oscerr << arg;
#endif
	return err;
}

class Message;
OSCFError& operator <<  (OSCFError& err, const Message* arg);

extern OSCFError	OSCFErr;		// static OSC error output stream
extern OSCFErrEnd	OSCFEndl;		// static OSC error output stream end

} // end namespace

#endif
