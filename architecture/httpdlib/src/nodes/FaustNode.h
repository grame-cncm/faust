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

namespace httpdfaust
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
	
	bool store(C val)			{ *fZone = fMapping.scale(val); return true; }

	protected:
		FaustNode(const char *name, C* zone, C min, C max, const char* prefix, bool initZone) 
			: MessageDriven (name, prefix), fZone(zone), fMapping(min, max, min, max) 
			{ 
                if (initZone)
                    *zone = min; 
            }

		FaustNode(const char *name, C* zone, C init, C min, C max, const char* prefix, bool initZone)
			: MessageDriven(name, prefix), fZone(zone), fMapping(min, max, min, max) 
			{ 
                if (initZone)
                    *zone = init; 
            }
			
		FaustNode(const char *name, C* zone,  C imin, C imax, C init, C min, C max, const char* prefix, bool initZone) 
			: MessageDriven(name, prefix), fZone(zone), fMapping(imin, imax, min, max) 
			{ 
                if (initZone)
                    *zone = init; 
            }
		virtual ~FaustNode() {}

	public:
		typedef SMARTP<FaustNode<C> > SFaustNode;
		static SFaustNode create(const char* name, C* zone, C min, C max, const char* prefix, bool initZone)
							{ return new FaustNode(name, zone, min, max, prefix, initZone); }
		static SFaustNode create(const char* name, C* zone, C init, C min, C max, const char* prefix, bool initZone)	
							{ return new FaustNode(name, zone, init, min, max, prefix, initZone); }
		static SFaustNode create(const char* name, C* zone, C imin, C imax, C init, C min, C max, const char* prefix, bool initZone)	
							{ return new FaustNode(name, zone, imin, imax, init, min, max, prefix, initZone); }


		virtual bool accept(const Message* msg, std::vector<Message*>& outMsg)	///< handler for the 'accept' message
        {
            if (msg->size() == 2) {			// checks for the message parameters count
                                            // messages with a param count other than 2 are rejected
                std::string key;
                if (msg->param(0, key) &&  (key == "value")) {
                    float val=0;
                    if (msg->param(1, val)) {
                        store(val);			// accepts float values
                    }
                    get(outMsg);
                    return true;
                }
            }
            return MessageDriven::accept(msg, outMsg);
        }

		virtual void get(std::vector<Message*>& outMsg) const						///< handler for the 'get' message
        {
            Message * msg = new Message(getAddress());
            msg->add(float(*fZone));
            outMsg.push_back(msg);
        }
};

} // end namespoace

#endif
