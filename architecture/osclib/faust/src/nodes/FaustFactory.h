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


#ifndef __FaustFactory__
#define __FaustFactory__

#include <stack>

#include "MessageDriven.h"

namespace oscfaust
{

class OSCIO;
class MessageDriven;
typedef class SMARTP<MessageDriven>	SMessageDriven;

//--------------------------------------------------------------------------
/*!
	\brief a factory to build a memory representation
	
	Actually, makes use of a stack to build the UI hierarchy.
	It includes a pointer to a OSCIO controler, but just to give it to the root node.
*/
class FaustFactory
{
	std::stack<SMessageDriven>	fNodes;	// maintains the current hierarchy level
	SMessageDriven			fRoot;		// keep track of the root node
	OSCIO * fIO;						// hack to support audio IO via OSC, actually the field is given to the root node

	public:
				 FaustFactory(OSCIO * io=0) : fIO(io) {}
		virtual ~FaustFactory() {}

		void addnode (const char* label, float* zone, float init, float min, float max);
		void opengroup (const char* label);
		void closegroup ();

		SMessageDriven	root() const	{ return fRoot; }
};

} // end namespoace

#endif
