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
struct MHD_Connection;

namespace httpdfaust
{

class FaustNode;
typedef class SMARTP<FaustNode>	SFaustNode;

/**
 * map (rescale) input values to output values
 */
struct mapping
{
	const float fMinIn;	
	const float fMaxIn;
	const float fMinOut;
	const float fMaxOut;
	const float fScale;

	mapping(float imin, float imax, float omin, float omax) : fMinIn(imin), fMaxIn(imax), 
											fMinOut(omin), fMaxOut(omax), 
											fScale( (fMaxOut-fMinOut)/(fMaxIn-fMinIn) ) {}
	float scale (float x) { float z = (x < fMinIn) ? fMinIn : (x > fMaxIn) ? fMaxIn : x; return fMinOut + (z - fMinIn) * fScale; }
};


//--------------------------------------------------------------------------
/*!
	\brief a faust node is a terminal node and represents a faust parameter controler
*/
class FaustNode : public MessageDriven
{
	float *	fZone;			// the parameter memory zone
	mapping	fMapping;
	
	bool store (float val);

	protected:
		FaustNode(const char *name, float* zone, float init, float min, float max, const char* prefix) 
			: MessageDriven (name, prefix), fZone(zone), fMapping(min, max, min, max) 
			{ *zone = init; }
			
		FaustNode(const char *name, float* zone,  float imin, float imax, float init, float min, float max, const char* prefix) 
			: MessageDriven (name, prefix), fZone(zone), fMapping(imin, imax, min, max) 
			{ *zone = init; }
		virtual ~FaustNode() {}

	public:
		static SFaustNode create (const char* name, float* zone, float init, float min, float max, const char* prefix)	
							{ return new FaustNode(name, zone, init, min, max, prefix); }
		static SFaustNode create (const char* name, float* zone, float imin, float imax, float init, float min, float max, const char* prefix)	
							{ return new FaustNode(name, zone, imin, imax, init, min, max, prefix); }


		virtual bool	accept( const Message* msg );				///< handler for the 'accept' message
		virtual int		get (struct MHD_Connection* cnx) const;		///< handler for the 'get' message
};

} // end namespoace

#endif
