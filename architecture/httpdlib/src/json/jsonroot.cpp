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

#include "jsonroot.h"

using namespace std;

namespace httpdfaust
{

//______________________________________________________________________________
ostream& operator<< (ostream& os, const jsonendl& endl)
{
    endl.print(os);
    return os;
}

//______________________________________________________________________________
void jsonendl::print(std::ostream& os) const { 
	int i = fIndent;
    os << std::endl;
    while (i-- > 0)  os << "	";
}

//--------------------------------------------------------------------------
void jsonroot::print(std::ostream& out) const
{
	jsonendl eol;
	out << "{" << eol++;
	out << "\"name\": \"" << fName << "\"," << eol;
	out << "\"address\": \"" << fAddress << "\"," << eol;
	out << "\"port\": \"" << fPort << "\"," << eol;
	out << "\"inputs\": \"" << fInputs << "\"," << eol;
	out << "\"outputs\": \"" << fOutputs << "\"," << eol;

	if (fMeta.size()) {
		out << "\"meta\": [ "; eol++;
		map<string, string>::const_iterator i=fMeta.begin();
		while (true) {
			out << eol << "{ \"" << i->first << "\": \"" << i->second << "\"}";
			if (++i == fMeta.end()) break;
			out << ",";			
		}
		out << --eol << "]," << eol;
	}

	out << "\"ui\": ["; eol++;
	const char* sep = "";
	for (unsigned int i=0; i< fUi.size(); i++) {
		out << sep;
		sep = ",";
		fUi[i]->print(out, eol);
	}
	out << --eol << "]";
	out << --eol << "}" << eol;
}

} // end namespoace
