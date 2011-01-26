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

#include <iostream>

#include "Message.h"
#include "MessageDriven.h"
#include "OSCAddress.h"
#include "OSCFError.h"
#include "OSCRegexp.h"

using namespace std;
namespace oscfaust
{

//--------------------------------------------------------------------------
void MessageDriven::processMessage( const Message* msg )
{
	const string addr = msg->address();
std::cout << getName() << " MessageDriven::processMessage regexp " << OSCAddress::addressFirst(addr).c_str() << std::endl;
	OSCRegexp r (OSCAddress::addressFirst(addr).c_str());
	return propose (msg, &r, OSCAddress::addressTail (addr));
}

//--------------------------------------------------------------------------
void MessageDriven::accept( const Message* msg )
{
#if OSCFAUSTDEBUG
	OSCFErr << getName() << "unexpected accept method call" << OSCFEndl;
#endif
}

//--------------------------------------------------------------------------
void MessageDriven::propose( const Message* msg, const OSCRegexp* r, const std::string addrTail)
{
std::cout << getName() << " MessageDriven::propose" << std::endl;
	if (r->match(getName())) {
		if (addrTail.empty()) {
std::cout << getName() << " MessageDriven::propose -> accept" << std::endl;
			accept(msg);
		}
		else {
std::cout << getName() << " MessageDriven::propose -> subs count " << fSubNodes.size() << std::endl;
			OSCRegexp rtail (OSCAddress::addressFirst(addrTail).c_str());
			for (vector<SMessageDriven>::iterator i = fSubNodes.begin(); i != fSubNodes.end(); i++) {
std::cout << getName() << " MessageDriven::propose -> sub " << (*i)->getName() << std::endl;
				(*i)->propose (msg, &rtail, OSCAddress::addressTail(addrTail));
			}
		}
	}
	else std::cout << getName() << " bad address " << msg->address() << std::endl;
}

} // end namespoace
