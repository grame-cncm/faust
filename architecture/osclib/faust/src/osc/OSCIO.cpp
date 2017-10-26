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

#include <sstream>
#include <string>

#include "faust/OSCIO.h"
#include "OSCStream.h"

namespace oscfaust
{

//--------------------------------------------------------------------------
void OSCIO::send(int nframes, float* val, int chan) const
{
    std::stringstream dst;
    dst << dest() << chan;					// first set the destination osc address
    std::string res = dst.str();
    oscout << OSCStart(res.c_str());        // then starts the osc out stream
    for (int n = 0; n < nframes; n++) {
        oscout << val[n];					// and send the values
    }
    oscout << OSCEnd();						// end of stream (and actual transmission)
}

} // end namespoace
