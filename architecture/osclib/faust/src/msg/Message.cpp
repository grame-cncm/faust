/*

  INScore Project

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
#include <sstream>

#include "faust/osc/Message.h"
#include "OSCFError.h"

using namespace std;

namespace oscfaust
{

//--------------------------------------------------------------------------
// Message implementation
//--------------------------------------------------------------------------
Message::Message(const Message& msg)
{
	setAddress(msg.address());
	fArguments = msg.params();
}

//--------------------------------------------------------------------------
static string escape(const string& str) 
{
	string out;
	const char *ptr = str.c_str();
	while (*ptr) {
		char c = *ptr++;
		if (c == '"')
			out += "\\\"";
		else out += c;
	}
	return out;
}

//--------------------------------------------------------------------------
void Message::print(std::ostream& out) const
{
	out << address() << " " ;
	argslist::const_iterator i = params().begin();

	ios::fmtflags f = out.flags ( ios::showpoint );
	while (i != params().end()) {
		MsgParam<string>* s = dynamic_cast<MsgParam<string>*>((baseparam*)(*i));
		if (s) out << "\"" << escape(s->getValue()) << "\" ";
		MsgParam<int>* ip = dynamic_cast<MsgParam<int>*>((baseparam*)(*i));
		if (ip) out << ip->getValue() << " ";
		MsgParam<float>* fv = dynamic_cast<MsgParam<float>*>((baseparam*)(*i));
		if (fv) out << fv->getValue() << " ";
        MsgParam<double>* dv = dynamic_cast<MsgParam<double>*>((baseparam*)(*i));
        if (dv) out << dv->getValue() << " ";
		i++;
	}
	out.flags ( f );
}

//--------------------------------------------------------------------------
void Message::print(OSCStream& out) const
{
	out << OSCStart(address().c_str());
	printArgs(out);
	out << OSCEnd();
}

//--------------------------------------------------------------------------
void Message::printArgs(OSCStream& out) const
{
	for (int i = 0; i < size(); i++) {
		string str; float fv; int iv;
		if (param(i, fv))			out << fv;
		else if (param(i, iv))		out << iv;
		else if (param(i, str))		out << str;
		else OSCFErr << "Message::print(OSCStream& out): unknown message parameter type" << OSCFEndl;
	}
}

} // end namespoace
