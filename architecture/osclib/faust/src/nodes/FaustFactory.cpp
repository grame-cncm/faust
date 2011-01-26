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
#include "MessageDriven.h"

namespace oscfaust
{

//--------------------------------------------------------------------------
void FaustFactory::addnode (const char* label, float* zone, float init, float min, float max)
{
//	std::cout << "FaustFactory::addnode " << label << std::endl;
	fNodes.top()->add( FaustNode::create (label, zone, init, min, max) );
}

//--------------------------------------------------------------------------
void FaustFactory::opengroup (const char* label)
{
//	std::cout << "FaustFactory::opengroup " << label << std::endl;
	fNodes.push (MessageDriven::create (label) );
	if (!fRoot) fRoot = fNodes.top();
}

//--------------------------------------------------------------------------
void FaustFactory::closegroup ()
{
	fNodes.pop ();
}

} // end namespoace
