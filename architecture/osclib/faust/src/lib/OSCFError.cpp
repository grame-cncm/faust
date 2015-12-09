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

#include "OSCFError.h"
#include "faust/osc/Message.h"

namespace oscfaust
{

OSCFError	OSCFErr;		// static OSC error output stream
OSCFErrEnd	OSCFEndl;		// static OSC error output stream end

OSCFError& operator << (OSCFError& err, const Message* arg)
{
	arg->print (std::cerr);
#ifndef NO_OSC
	if (!err.oscpending) {
		oscerr << OSCErr();
		err.oscpending = true;
	}
	oscerr << arg->address().c_str();
	arg->printArgs(oscerr);
#endif
	return err;
}

} // end namespace
