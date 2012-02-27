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


#ifndef __FaustNode__
#define __FaustNode__

#include <string>
#include <vector>

#include "MessageDriven.h"
#include "Message.h"
#include "OSCStream.h"

namespace oscfaust
{

/**
 * map (rescale) input values to output values
 */
template <typename C> struct mapping
{
	const C fMinIn;	
	const C fMaxIn;
	const C fMinOut;
	const C fMaxOut;
	const C fScale;

	mapping(C imin, C imax, C omin, C omax) : fMinIn(imin), fMaxIn(imax), 
											fMinOut(omin), fMaxOut(omax), 
											fScale( (fMaxOut-fMinOut)/(fMaxIn-fMinIn) ) {}
	C scale (C x) { C z = (x < fMinIn) ? fMinIn : (x > fMaxIn) ? fMaxIn : x; return fMinOut + (z - fMinIn) * fScale; }
};


//--------------------------------------------------------------------------
/*!
	\brief a faust node is a terminal node and represents a faust parameter controler
*/
template <typename C> class FaustNode : public MessageDriven
{
	C *	fZone;			// the parameter memory zone
	mapping<C>	fMapping;
	
	bool store (C val)			{ *fZone = fMapping.scale(val); return true; }

	protected:
		FaustNode(const char *name, C* zone, C init, C min, C max, const char* prefix) 
			: MessageDriven (name, prefix), fZone(zone), fMapping(min, max, min, max) 
			{ *zone = init; }
			
		FaustNode(const char *name, C* zone,  C imin, C imax, C init, C min, C max, const char* prefix) 
			: MessageDriven (name, prefix), fZone(zone), fMapping(imin, imax, min, max) 
			{ *zone = init; }
		virtual ~FaustNode() {}

	public:
		typedef SMARTP<FaustNode<C> > SFaustNode;
		static SFaustNode create (const char* name, C* zone, C init, C min, C max, const char* prefix)	
							{ return new FaustNode(name, zone, init, min, max, prefix); }
		static SFaustNode create (const char* name, C* zone, C imin, C imax, C init, C min, C max, const char* prefix)	
							{ return new FaustNode(name, zone, imin, imax, init, min, max, prefix); }


		virtual bool	accept( const Message* msg )			///< handler for the 'accept' message
		{
			if (msg->size() == 1) {			// checks for the message parameters count
											// messages with a param count other than 1 are rejected
				int ival; float fval;
				if (msg->param(0, fval)) return store (C(fval));				// accepts float values
				else if (msg->param(0, ival)) return store (C(ival));	// but accepts also int values
			}
			return MessageDriven::accept(msg);
		}

		virtual void	get (unsigned long ipdest) const		///< handler for the 'get' message
		{
			unsigned long savedip = oscout.getAddress();		// saves the current destination IP
			oscout.setAddress(ipdest);							// sets the osc stream dest IP
			// send a state message on 'get' request
			oscout << OSCStart(getOSCAddress().c_str()) << 	float(*fZone) << float(fMapping.fMinOut) << float(fMapping.fMaxOut) << OSCEnd();
			oscout.setAddress(savedip);							// and restores the destination IP
		}
};



} // end namespoace

#endif
