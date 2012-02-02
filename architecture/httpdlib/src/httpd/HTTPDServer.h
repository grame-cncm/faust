/*

  Copyright (C) 2012 Grame

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


#ifndef __HTTPDServer__
#define __HTTPDServer__

#include <string>
#include <ostream>
#include <microhttpd.h>

#include "TThreads.h"

namespace httpdfaust
{

class MessageProcessor;

//--------------------------------------------------------------------------
/*!
	\brief a specific thread to listen incoming osc packets
*/
class HTTPDServer : public TThreads
{
	MessageProcessor*	fProcessor;
	int					fPort;
	struct MHD_Daemon *	fServer;

	public:
				 HTTPDServer(MessageProcessor* mp, int port)  : fProcessor(mp), fPort(port), fServer(0) {}
		virtual ~HTTPDServer() { stop(); }

		/// \brief starts the httpd server
		void run ();
		void stop ()			{ if (fServer) MHD_stop_daemon (fServer); fServer=0; quit(); }
		int answer (struct MHD_Connection *connection, const char *url, const char *method, const char *version, 
					const char *upload_data, size_t *upload_data_size, void **con_cls);

		static int send (struct MHD_Connection *connection, const char *page, int status=MHD_HTTP_OK);
};

} // end namespoace

#endif
