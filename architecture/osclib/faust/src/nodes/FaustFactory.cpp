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

#include <iostream>

#include "FaustFactory.h"
#include "FaustNode.h"
#include "RootNode.h"
#include "MessageDriven.h"

using namespace std;

namespace oscfaust
{

//--------------------------------------------------------------------------
void FaustFactory::addnode (const char* label, float* zone, float init, float min, float max)
{
	SMessageDriven top = fNodes.size() ? fNodes.top() : fRoot;
	if (top) {
		string prefix = top->getOSCAddress();
		top->add( FaustNode::create (label, zone, init, min, max, prefix.c_str()) );
	}
}

//--------------------------------------------------------------------------
void FaustFactory::opengroup (const char* label)
{
	if (!fNodes.size()) {						// the stack is empty: creates a root node 
		fRoot = RootNode::create (label, fIO);	// and gives the root node a possible OSCIO controler
		fNodes.push (fRoot);
	}
	else {
		SMessageDriven group = MessageDriven::create (label, fNodes.top()->getOSCAddress().c_str());
		fNodes.top()->add( group );
		fNodes.push (group);
	}
}

//--------------------------------------------------------------------------
void FaustFactory::closegroup ()
{
	fNodes.pop ();
}

} // end namespoace
