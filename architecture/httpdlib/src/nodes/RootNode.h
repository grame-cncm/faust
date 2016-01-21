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


#ifndef __RootNode__
#define __RootNode__

#include <string>
#include "MessageDriven.h"

namespace httpdfaust
{

class RootNode;
typedef class SMARTP<RootNode>	SRootNode;

//--------------------------------------------------------------------------
/*!
	\brief a faust program root node
*/
class RootNode : public MessageDriven
{
	std::string fJson;
	std::string fHtml;
	
	protected:
				 RootNode(const char *name) : MessageDriven (name, "") {}
		virtual ~RootNode() {}

	public:
		static SRootNode create(const char* name) { return new RootNode(name); }

		void			setJSON(const std::string& json)	{ fJson = json; }
		void			setHtml(const std::string& html)	{ fHtml = html; }
		//--------------------------------------------------------------------------
		bool			processMessage(const Message* msg, std::vector<Message*>& outMsg);
		virtual bool	accept(const Message* msg, std::vector<Message*>& outMsg);
};

} // end namespoace

#endif
