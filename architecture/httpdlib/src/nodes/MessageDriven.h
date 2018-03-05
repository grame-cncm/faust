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

namespace httpdfaust
{

class Message;
class MessageDriven;
typedef class SMARTP<MessageDriven>	SMessageDriven;

//--------------------------------------------------------------------------
/*!
	\brief a base class for objects accepting messages
	
	Message driven objects are hierarchically organized in a tree.
	They provides the necessary to dispatch a message to its destination
	node, according to the message address. 
	
	The principle of the dispatch is the following:
	- first the processMessage() method should be called on the top level node
	- next processMessage call propose 
	
	
*/
class MessageDriven : public MessageProcessor, public smartable
{
	std::string						fName;			///< the node name
	std::string						fPrefix;		///< the node address prefix (Address = fPrefix + '/' + fName)
	std::vector<SMessageDriven>		fSubNodes;		///< the subnodes of the current node

	protected:
				 MessageDriven(const char *name, const char *prefix) : fName (name), fPrefix(prefix) {}
		virtual ~MessageDriven() {}

	public:
		static SMessageDriven create (const char* name, const char *prefix)	{ return new MessageDriven(name, prefix); }

		/*!
			\brief message processing method.
			\param msg the osc message to be processed
			The method should be called on the top level node.
		*/
		virtual bool	processMessage( const Message* msg, std::vector<Message*>& outMsg );

		/*!
			\brief propose an OSc message at a given hierarchy level.
			\param msg the osc message currently processed
			\param regexp a regular expression based on the osc address head
			\param addrTail the osc address tail
			
			The method first tries to match the regular expression with the object name. 
			When it matches:
			- it calls \c accept when \c addrTail is empty 
			- or it \c propose the message to its subnodes when \c addrTail is not empty. 
			  In this case a new \c regexp is computed with the head of \c addrTail and a new \c addrTail as well.
		*/
		virtual bool	propose( const Message* msg, const char* address, const std::string addrTail, std::vector<Message*>& outMsg);

		/*!
			\brief accept a message. 
			\param msg the message currently processed
			\return true when the message is processed by the node
			
			The method is called only for the destination nodes. The real message acceptance is the node 
			responsability and may depend on the message content.
		*/
		virtual bool	accept( const Message* msg, std::vector<Message*>& outMsg );

		/*!
			\brief handler for the \c 'get' message
			\param ipdest the output message destination IP
			
			The \c 'get' message is supported by every node:
			- it is propagated to the subnodes until it reaches terminal nodes
			- a terminal node send its state on \c 'get' request to the IP address given as parameter.
			The \c get method is basically called by the accept method.
		*/
		virtual void	get (std::vector<Message*>& outMsg) const;		///< handler for the 'get' message

		void			add ( SMessageDriven node )	{ fSubNodes.push_back (node); }
		const char*		getName() const				{ return fName.c_str(); }
		std::string		getAddress() const;
		int				size () const				{ return (int)fSubNodes.size (); }
		
		const std::string&	name() const			{ return fName; }
		SMessageDriven	subnode (int i) 			{ return fSubNodes[i]; }
};

} // end namespoace

#endif
