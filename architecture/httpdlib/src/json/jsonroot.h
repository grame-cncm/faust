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


#ifndef __jsonroot__
#define __jsonroot__

#include <ostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

#include "smartpointer.h"
#include "jsonnode.h"


namespace httpdfaust
{

//--------------------------------------------------------------------------
/*!
	\brief a faust root is a terminal node and represents a faust parameter controler
*/
class jsonroot : public smartable
{

    private:
    
        std::string fName;
        std::string fAddress;
        int			fPort;
        int			fInputs;
        int			fOutputs;
        std::map<std::string, std::string> fMeta;
        std::vector<Sjsonnode> fUi;
        std::stringstream fJSON;
    
        inline std::string flatten(const std::string& src)
        {
            std::stringstream dst;
            for (size_t i = 0; i < src.size(); i++) {
                switch (src[i]) {
                    case '\n':
                    case '\t':
                        dst << ' ';
                        break;
                    default:
                        dst << src[i];
                        break;
                }
            }
            return dst.str();
        }
	
	public:
				 jsonroot(const char *name, const char* address, int port)
					:fName(name), fAddress(address), fPort(port), fInputs(0), fOutputs(0) {}
		virtual ~jsonroot() {}
		
		void print(std::ostream& out) const;
		void add(const Sjsonnode& node)					{ fUi.push_back(node); }
		void setPort(int port)							{ fPort = port; }
		void declare(const char* key, const char* val)	{ fMeta[key] = val; }
		void setInputs(int inputs)						{ fInputs = inputs;}
		void setOutputs(int outputs)                    { fOutputs = outputs; }
		std::string	json(bool flat = false)             { print(fJSON); return (flat) ? flatten(fJSON.str()) : fJSON.str(); }
};

} // end namespoace

#endif
