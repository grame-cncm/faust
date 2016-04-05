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

#include "faust/osc/FaustFactory.h"
#include "faust/osc/FaustNode.h"
#include "faust/osc/MessageDriven.h"
#include "faust/osc/RootNode.h"
#include "OSCAddress.h"

using namespace std;

namespace oscfaust
{

FaustFactory::FaustFactory(GUI* ui, OSCIO * io) : fIO(io), fGUI(ui) {}
FaustFactory::~FaustFactory() {}

/**
 * Open a group in the current group and place it on the top of the stack. 
 * Takes into account that due to alias, a group can been previously created.  
 */
void FaustFactory::opengroup(const char* label)
{
	if (fNodes.size() == 0) {	
		// the stack is empty: creates a root node 
		// and gives the root node a possible OSCIO controler
		fRoot = RootNode::create(label, fIO);	
		fNodes.push(fRoot);					
		
	} else {
		// only create a group if not previously created
		SMessageDriven node = fNodes.top();
		int i = 0; while ((i < node->size()) && (node->subnode(i)->name() != label)) i++;
		
		if (i < node->size()) {
			// found, make it top of stack
			fNodes.push(node->subnode(i));
		} else {
			// not found, create a new group and make it top of stack
			SMessageDriven group = MessageDriven::create(label, node->getOSCAddress().c_str());
			node->add(group);
			fNodes.push(group);
		}
	}
}

//--------------------------------------------------------------------------
SRootNode FaustFactory::root() const	{ return fRoot; }

//--------------------------------------------------------------------------
// add an alias to the root node
//--------------------------------------------------------------------------
void FaustFactory::addAlias(const char* alias, const char* address, float imin, float imax, float omin, float omax)
{
	if (fRoot) fRoot->addAlias(alias, address, imin, imax, omin, omax);
}

//--------------------------------------------------------------------------
std::string FaustFactory::addressFirst(const std::string& address) const    { return OSCAddress::addressFirst(address); }
std::string FaustFactory::addressTail(const std::string& address) const     { return OSCAddress::addressTail(address); }

//--------------------------------------------------------------------------
void FaustFactory::closegroup()
{
	fNodes.pop();
}

} // end namespoace
