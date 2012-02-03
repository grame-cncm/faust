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
	jsonendl jsendl;
	out << "{" << jsendl++;
	out << "\"name\": \"" << fName << "\"," << jsendl;
	out << "\"address\": \"" << fAddress << "\"," << jsendl;
	out << "\"port\": \"" << fPort << "\"," << jsendl;
	out << "\"ui\": \"[";
	for (unsigned int i=0; i< fUi.size(); i++) {
		fUi[i]->print(out, jsendl);
	}
	out << --jsendl << "]";
	out << --jsendl << "}" << jsendl;
}

} // end namespoace
