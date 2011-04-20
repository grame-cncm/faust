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
#include <vector>

#include "MessageDriven.h"

namespace oscfaust
{

class OSCIO;
class RootNode;
typedef class SMARTP<RootNode>	SRootNode;

//--------------------------------------------------------------------------
/*!
	\brief a faust root node

	A Faust root node handles the \c 'hello' message and provides support
	for incoming osc signal data. 
*/
class RootNode : public MessageDriven
{
	int *fUPDIn, *fUDPOut, *fUDPErr;	// the osc port numbers (required by the hello method)
	OSCIO * fIO;						// an OSC IO controler
	
	protected:
				 RootNode(const char *name, OSCIO* io=0) : MessageDriven (name, ""), fUPDIn(0), fUDPOut(0), fUDPErr(0), fIO(io) {}
		virtual ~RootNode() {}

	public:
		static SRootNode create (const char* name, OSCIO* io=0) { return new RootNode(name, io); }

		virtual bool	accept( const Message* msg );
				
				bool	acceptSignal( const Message* msg );				///< handler for signal data
				void	hello (unsigned long ipdest) const;				///< handler for the 'hello' message
				void	setPorts (int* in, int* out, int* err);
};

} // end namespoace

#endif
