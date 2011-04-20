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


#ifndef __OSCIO__
#define __OSCIO__

#include <string>

namespace oscfaust
{

//--------------------------------------------------------------------------
// build in support
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
/*!
	\brief build in support for osc audio input / output
*/
class OSCIO
{	
	std::string	fDest;			// the output destination osc address
	public:
				 OSCIO(const char *dst) : fDest(dst) {}
		virtual ~OSCIO() {} 

		virtual void	receive( int nframes, float * val ) = 0;
		virtual int		numOutputs() const = 0;
		virtual int		numInputs() const = 0;
		
		/*!
			\brief send audio frames on osc out
			\param nframes the frames count
			\param val		a pointer to the frames values
			\param chan		the current channel number (used as part of the dest osc address)
		*/
		virtual void 	send ( int nframes, float * val, int chan ) const;
		const char* 	dest () const				{ return fDest.c_str(); }
		void			setDest (const char *dst)	{ fDest = dst; }
};

} // end namespoace

#endif
