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


#ifndef __MessageDriven__
#define __MessageDriven__

#include <string>
#include <vector>

#include "MessageProcessor.h"
#include "smartpointer.h"

namespace oscfaust
{

class Message;
class OSCRegexp;
class MessageDriven;
typedef class SMARTP<MessageDriven>	SMessageDriven;

//--------------------------------------------------------------------------
class MessageDriven : public MessageProcessor, public smartable
{
	std::string						fName;
	std::string						fOSCPrefix;
	std::vector<SMessageDriven>		fSubNodes;

	protected:
				 MessageDriven(const char *name, const char *oscprefix) : fName (name), fOSCPrefix(oscprefix) {}
		virtual ~MessageDriven() {}

	public:
		static SMessageDriven create (const char* name, const char *oscprefix)	{ return new MessageDriven(name, oscprefix); }

		virtual void	processMessage( const Message* msg );
		virtual void	propose( const Message* msg, const OSCRegexp* regexp, const std::string addrTail);
		virtual void	accept( const Message* msg );
		virtual void	get (unsigned long ipdest) const;		///< handler for the 'get' message

		void			add ( SMessageDriven node )	{ fSubNodes.push_back (node); }
		const char*		getName() const				{ return fName.c_str(); }
		std::string		getOSCAddress() const;
		int				size () const				{ return fSubNodes.size (); }

};

} // end namespoace

#endif
