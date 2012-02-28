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
#include <sstream>

#include "FaustFactory.h"
#include "FaustNode.h"
#include "RootNode.h"
#include "MessageDriven.h"

using namespace std;

namespace httpdfaust
{


/**
 * Open a group in the current group and place it on the top of the stack. 
 * Takes into account that due to alias, a group can been previously created.  
 */
void FaustFactory::opengroup (const char* label)
{
	if (fNodes.size() == 0) {	
		// the stack is empty: creates a root node 
		fRoot = RootNode::create (label);	
		fNodes.push (fRoot);					
		
	} else {
		// only create a group if not previously created
		SMessageDriven node = fNodes.top();
		int i=0; while ( (i < node->size()) && (node->subnode(i)->name() != label) ) i++;
		
		if (i < node->size()) {
			// found, make it top of stack
			fNodes.push(node->subnode(i));
		} else {
			// not found, create a new group and make it top of stack
			SMessageDriven group = MessageDriven::create (label, node->getAddress().c_str());
			node->add( group );
			fNodes.push (group);
		}

	}
}

//--------------------------------------------------------------------------
void FaustFactory::closegroup ()
{
	fNodes.pop ();
}

} // end namespoace
