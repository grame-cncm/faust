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

void FaustFactory::addfullpathnode (const string& fullpath, float* zone, float imin, float imax, float init, float min, float max)
{
}


//--------------------------------------------------------------------------
void FaustFactory::opengroup (const char* label)
{
	if (fNodes.size() == 0) {					// the stack is empty: creates a root node 
		fRoot = RootNode::create (label, fIO);	// and gives the root node a possible OSCIO controler
		fNodes.push (fRoot);
	} else {
		
		// search for previously created group before ceating a new one
		SMessageDriven node = fNodes.top();
		int i=0; while ( (i < node->size()) && (node->subnode(i)->name() != label) ) i++;
		
		if (i < node->size()) {
			// found, make it top of stack
			fNodes.push(node->subnode(i));
		} else {
			// not found, create a new group and make it top of stack
			SMessageDriven group = MessageDriven::create (label, node->getOSCAddress().c_str());
			node->add( group );
			fNodes.push (group);
		}

		
/*		SMessageDriven node = fNodes.top();
		for (int i = 0; i < node->size(); i++) {
			if (node->subnode(i)->name() == label) {
				fNodes.push(node->subnode(i));
				return;
			}
		}
		// we need to create a new node
		SMessageDriven group = MessageDriven::create (label, node->getOSCAddress().c_str());
		node->add( group );
		fNodes.push (group);*/
	}
}

//--------------------------------------------------------------------------
void FaustFactory::closegroup ()
{
	fNodes.pop ();
}

} // end namespoace
