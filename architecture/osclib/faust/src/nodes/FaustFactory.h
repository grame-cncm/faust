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
#include <string>
#include <sstream>

#include "MessageDriven.h"
#include "FaustNode.h"
#include "RootNode.h"
#include "MessageDriven.h"
#include "OSCAddress.h"

namespace oscfaust
{

//--------------------------------------------------------------------------
/*!
	\brief a factory to build a OSC UI hierarchy
	
	Actually, makes use of a stack to build the UI hierarchy.
	It includes a pointer to a OSCIO controler, but just to give it to the root node.
*/
class FaustFactory
{
	std::stack<SMessageDriven>	fNodes;		///< maintains the current hierarchy level
	SMessageDriven				fRoot;		///< keep track of the root node
	OSCIO * 					fIO;		///< hack to support audio IO via OSC, actually the field is given to the root node

	private:
		SMessageDriven 	followPath	(SMessageDriven fRoot, const std::string& fullpath, std::string& pathtoleaf);
		template <typename C>  void createNodeChain	(SMessageDriven node, const std::string& pathtoleaf, C* zone, C imin, C imax, C init, C min, C max);

	public:
				 FaustFactory(OSCIO * io=0) : fIO(io) {}
		virtual ~FaustFactory() {}

		template <typename C> void addnode (const char* label, C* zone, C init, C min, C max);
		template <typename C> void addfullpathnode (const std::string& fullpath, C* zone, C imin, C imax, C init, C min, C max);
		void opengroup (const char* label);
		void closegroup ();

		SMessageDriven	root() const	{ return fRoot; }
};

/**
 * Add a node to the OSC UI tree in the current group at the top of the stack 
 */
template <typename C> void FaustFactory::addnode (const char* label, C* zone, C init, C min, C max) 
{
	SMessageDriven top = fNodes.size() ? fNodes.top() : fRoot;
	if (top) {
		std::string prefix = top->getOSCAddress();
		top->add( FaustNode<C>::create (label, zone, init, min, max, prefix.c_str()) );
	}
}

/**
 * Add a node to the OSC UI tree using its fullpath directly from the root and bypassing the current group.
 * The argument fullpath = "/foo/fii/faa [imin [imax]]" can contain optional imin and imax values
 */
template <typename C> void FaustFactory::addfullpathnode (const std::string& fullpath, C* zone, C imin, C imax, C init, C min, C max)
{
	std::istringstream 	ss(fullpath);
	std::string 		realpath; 
	std::string			remainingpath;
	
	// Extract realpath and optional imin and imax fields. Note that if no values for imin and imax 
	// are specified in the fullpath string, the values passed as parameters will be used.
	ss >> realpath >> imin >> imax;
	// Note that realpath is prefixed before being added in the tree : /root/alias/realpath
	SMessageDriven node = followPath(fRoot, std::string("/alias") + realpath, remainingpath);
	createNodeChain<C>(node, remainingpath, zone, imin, imax, init, min, max);
}

/**
 * Creates a chain of nodes starting at node and following pathtoleaf
 */
template <typename C>  void FaustFactory::createNodeChain	(SMessageDriven node, const std::string& pathtoleaf, C* zone, C imin, C imax, C init, C min, C max)
{
	if (pathtoleaf.size() > 0) {
		std::string label 	= OSCAddress::addressFirst (pathtoleaf);
		std::string tail 	= OSCAddress::addressTail (pathtoleaf);
		if (tail.size() == 0) {
			std::string prefix = node->getOSCAddress();
			node->add( FaustNode<C>::create (label.c_str(), zone, imin, imax, init, min, max, prefix.c_str()) );
		} else {
			SMessageDriven group = MessageDriven::create (label.c_str(), node->getOSCAddress().c_str());
			node->add(group);
			createNodeChain(group, tail, zone, imin, imax, init, min, max);
		}
	} else {
		std::cerr << "osc address too short" << std::endl;
	}
}


} // end namespoace

#endif
