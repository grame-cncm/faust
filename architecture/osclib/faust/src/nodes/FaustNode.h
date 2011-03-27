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

namespace oscfaust
{

class FaustNode;
typedef class SMARTP<FaustNode>	SFaustNode;

//--------------------------------------------------------------------------
class FaustNode : public MessageDriven
{
	float *	fZone;
	float	fMin, fMax;
	
	void store (float val);

	protected:
				 FaustNode(const char *name, float* zone, float init, float min, float max, const char* prefix) 
					: MessageDriven (name, prefix), fZone(zone), fMin(min), fMax(max) { *zone = init; }
		virtual ~FaustNode() {}

	public:
		static SFaustNode create (const char* name, float* zone, float init, float min, float max, const char* prefix)	
							{ return new FaustNode(name, zone, init, min, max, prefix); }

		virtual bool	accept( const Message* msg );
		virtual void	get (unsigned long ipdest) const;		///< handler for the 'get' message
};

} // end namespoace

#endif
