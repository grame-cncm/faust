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
 * Add a node to the OSC UI tree in the current group at the top of the stack 
 */
void FaustFactory::addnode (const char* label, float* zone, float init, float min, float max)
{
	SMessageDriven top = fNodes.size() ? fNodes.top() : fRoot;
	if (top) {
		string prefix = top->getAddress();
		top->add( FaustNode::create (label, zone, init, min, max, prefix.c_str()) );
	}
}

/**
 * Add a node to the OSC UI tree using its fullpath directly from the root and bypassing the current group.
 * The argument fullpath = "/foo/fii/faa [imin [imax]]" can contain optional imin and imax values
 */
//void FaustFactory::addfullpathnode (const string& fullpath, float* zone, float imin, float imax, float init, float min, float max)
//{
//	istringstream 	ss(fullpath);
//	string 			realpath; 
//	string			remainingpath;
//	
//	// Extract realpath and optional imin and imax fields. Note that if no values for imin and imax 
//	// are specified in the fullpath string, the values passed as parameters will be used.
//	ss >> realpath >> imin >> imax;
//	// Note that realpath is prefixed before being added in the tree : /root/alias/realpath
//	SMessageDriven node = followPath(fRoot, string("/alias") + realpath, remainingpath);
//	createNodeChain(node, remainingpath, zone, imin, imax, init, min, max);
//}


/**
 * Follows fullpath as much as possible. Return the deepest node reached and
 * the remaining path.  We have path(node)++remainingpath = fullpath
 */
//SMessageDriven FaustFactory::followPath(SMessageDriven node, const string& fullpath, string& remainingpath)
//{
//	if (fullpath.size()>0) {
//		string label = OSCAddress::addressFirst (fullpath);
//		for (int i = 0; i < node->size(); i++) {
//			if (node->subnode(i)->name() == label) {
//				return followPath(node->subnode(i), OSCAddress::addressTail(fullpath), remainingpath);
//			}
//		}
//	}
//	remainingpath = fullpath;
//	return node;
//}


/**
 * Creates a chain of nodes starting at node and following pathtoleaf
 */
//void FaustFactory::createNodeChain(SMessageDriven node, const string& pathtoleaf, float* zone, float imin, float imax, float init, float min, float max)
//{
//	if (pathtoleaf.size() > 0) {
//		string label 	= OSCAddress::addressFirst (pathtoleaf);
//		string tail 	= OSCAddress::addressTail (pathtoleaf);
//		if (tail.size() == 0) {
//			string prefix = node->getOSCAddress();
//			node->add( FaustNode::create (label.c_str(), zone, imin, imax, init, min, max, prefix.c_str()) );
//		} else {
//			SMessageDriven group = MessageDriven::create (label.c_str(), node->getOSCAddress().c_str());
//			node->add(group);
//			createNodeChain(group, tail, zone, imin, imax, init, min, max);
//		}
//	} else {
//		cerr << "osc address too short" << endl;
//	}
//}


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
