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


#ifndef __OSCAddress__
#define __OSCAddress__

#include <string>

namespace oscfaust
{


//--------------------------------------------------------------------------
/*! \brief OSC addresses utilities
*/
class OSCAddress
{
	public:
		/*!
			\brief address decoding utility.
			
			An address has a form similar to a unix path.
			\param address the osc address to be processed
			\return the first part of the address (without leading '/')
		*/
		static std::string	addressFirst (const std::string& address);
		/*!
			\brief address decoding utility.
			\param address the osc address to be processed
			\return the last part of an address.
		*/
		static std::string	addressLast (const std::string& address);
		/*!
			\brief address decoding utility.

			An address has a form similar to a unix path.
			\param address the osc address to be processed
			\return the tail of an address after its first part.
		*/
		static std::string	addressTail (const std::string& address);
};


} // end namespoace

#endif
