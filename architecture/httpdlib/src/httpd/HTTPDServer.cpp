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
#include <stdexcept>

#include "HTTPDServer.h"
#include "Message.h"
#include "MessageProcessor.h"
#include "TThreads.h"

using namespace std;

namespace httpdfaust
{

#define kPortsScanRange		1000		// scan this number of TCP ports to find a free one (in case of busy port)

//--------------------------------------------------------------------------
// static functions
// provided as callbacks to mhttpd
//--------------------------------------------------------------------------
static int _answer_to_connection (void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, 
                          const char *upload_data, size_t *upload_data_size, void **con_cls)
{
	HTTPDServer* server = (HTTPDServer*)cls;
	return server->answer(connection, url, method, version, upload_data, upload_data_size, con_cls); 
}

//--------------------------------------------------------------------------
static int _get_params (void *cls, enum MHD_ValueKind kind, const char *key, const char *value)
{
	Message* msg = (Message*)cls;
	msg->add (string(key));
	if (value) {
		char* endptr;
		float fval = strtof(value, &endptr);
		if ((fval == 0) && (endptr == value))		// not a float value
			msg->add (string(value));
		else 
			msg->add (fval);
	}
	return MHD_YES;
}

//--------------------------------------------------------------------------
HTTPDServer::HTTPDServer(MessageProcessor* mp, int port)  
	: fProcessor(mp), fPort(port), fServer(0) 
{
	cout << "HTTPDServer::HTTPDServe called with " << (void*)mp << endl;
}

HTTPDServer::~HTTPDServer() { stop(); }

//--------------------------------------------------------------------------
bool HTTPDServer::start(int port)
{
	fServer = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, port, NULL, NULL, _answer_to_connection, this, MHD_OPTION_END);
	return fServer != 0;
//	if (!fServer) throw std::runtime_error("Starting MHD daemon error");
}

//--------------------------------------------------------------------------
int HTTPDServer::send (struct MHD_Connection *connection, const char *page, int status)
{
	struct MHD_Response *response = MHD_create_response_from_buffer (strlen (page), (void *) page, MHD_RESPMEM_PERSISTENT);
	if (!response) {
		cerr << "send error: null response\n";
		return MHD_NO;
	}
	MHD_add_response_header (response, "Content-Type", "text/plain");
	int ret = MHD_queue_response (connection, status, response);
	MHD_destroy_response (response);
//cout << "send response " << page << " status: " << status << " ret=" << ret << endl;
	return ret;
}

//--------------------------------------------------------------------------
int HTTPDServer::send (struct MHD_Connection *connection, std::vector<Message*> msgs)
{
	stringstream page;
	for (unsigned int i=0; i<msgs.size(); i++) {
		msgs[i]->print( page);
		page << endl;
		delete msgs[i];
	}
	return send (connection, page.str().c_str());
}

//--------------------------------------------------------------------------
int HTTPDServer::answer (struct MHD_Connection *connection, const char *url, const char *method, const char *version, 
					const char *upload_data, size_t *upload_data_size, void **con_cls)
{
	MHD_ValueKind t = MHD_GET_ARGUMENT_KIND;
	if (0 == strcmp (method, "GET"))		t = MHD_GET_ARGUMENT_KIND;
	else if (0 == strcmp (method, "POST"))	t = MHD_POSTDATA_KIND;
	else {
		string msg = "Method ";
		msg += method;
		msg += " is not supported";
		return send (connection, msg.c_str(), MHD_HTTP_BAD_REQUEST);
	}

	Message msg (url);
	MHD_get_connection_values (connection, t, _get_params, &msg);
	vector<Message*> outMsgs;
//	cout << "got message: ";
//	msg.print(cout);
//	cout << endl;
	fProcessor->processMessage (&msg, outMsgs);
	if (outMsgs.size())
		send (connection, outMsgs);
	else 
		send (connection, "", MHD_HTTP_NOT_FOUND);
	return MHD_YES;
}


} // end namespoace
