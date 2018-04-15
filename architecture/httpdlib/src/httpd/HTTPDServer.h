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
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#endif

#include <microhttpd.h>

namespace httpdfaust
{

class Message;
class MessageProcessor;

//--------------------------------------------------------------------------
/*!
	\brief a specific thread to listen incoming osc packets
*/
class HTTPDServer
{
	MessageProcessor*	fProcessor;
	struct MHD_Daemon *	fServer;
	bool				fDebug;
	
	int send (struct MHD_Connection *connection, std::vector<Message*> msgs);
	int page (struct MHD_Connection *connection, const char *page);
	const char* getMIMEType (const std::string& page);

	public:
				 HTTPDServer(MessageProcessor* mp);
		virtual ~HTTPDServer();

		/// \brief starts the httpd server
		bool start (int port);
		void stop ()			{ if (fServer) MHD_stop_daemon (fServer); fServer=0; }
		int answer (struct MHD_Connection *connection, const char *url, const char *method, const char *version, 
					const char *upload_data, size_t *upload_data_size, void **con_cls);

		static int send (struct MHD_Connection *connection, const char *page, const char *type, int status=MHD_HTTP_OK);
};

} // end namespoace

#endif
