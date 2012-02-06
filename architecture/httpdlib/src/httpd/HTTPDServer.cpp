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
#include <fstream>
#include <stdexcept>

#include "HTTPDServer.h"
#include "Message.h"
#include "MessageProcessor.h"

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
int HTTPDServer::send (struct MHD_Connection *connection, const char *page, const char* type, int status)
{
	struct MHD_Response *response = MHD_create_response_from_buffer (strlen (page), (void *) page, MHD_RESPMEM_PERSISTENT);
	if (!response) {
		cerr << "send error: null response\n";
		return MHD_NO;
	}
	MHD_add_response_header (response, "Content-Type", type ? type : "text/plain");
	int ret = MHD_queue_response (connection, status, response);
	MHD_destroy_response (response);
//cout << "send response " << page << " status: " << status << " ret=" << ret << endl;
	return ret;
}

//--------------------------------------------------------------------------
const char* HTTPDServer::getMIMEType (const string& page)
{
	size_t n = page.find_last_of ('.');
	if (n != string::npos) {
		string ext = page.substr (n+1);
		if (ext == "css")	return "text/css";
		if (ext == "js")	return "application/javascript";
	}
	return "text/plain";		// default MIME type
}

//--------------------------------------------------------------------------
int HTTPDServer::page (struct MHD_Connection *connection, const char * page)
{
	int ret = 0;
	char * root =  getenv("FAUSTDocumentRoot");
	string file = root ? root : ".";
	file += page;
	const char* type = getMIMEType (file);
	fstream is (file.c_str(), ios_base::in);
	if (is.is_open()) {
		is.seekg (0, ios::end);
		int length = is.tellg();
		is.seekg (0, ios::beg);

		// allocate memory:
		char* buffer = new char [length+1];
		// read data as a block:
		is.read (buffer,length);
		is.close();
		buffer[length] = 0;
//cout << "sending page " << page << " type: " << type << " length: " << length << endl;
		ret = send (connection, buffer, type);
		delete[] buffer;
	}
	else {
cout << "Warning - Page not found: " << page << endl;
		ret = send (connection, "", 0, MHD_HTTP_NOT_FOUND);
	}
	return ret;
}

//--------------------------------------------------------------------------
int HTTPDServer::send (struct MHD_Connection *connection, std::vector<Message*> msgs)
{
	stringstream page;
	string mime;
	for (unsigned int i=0; i<msgs.size(); i++) {
		string currentmime = msgs[i]->mimetype();
		if (mime.size() && (currentmime != mime)) {					// check for mime type change
			send (connection, page.str().c_str(), mime.c_str());	// send the current mime data
			page.str("");											// and clear the stream
		}
		mime = currentmime;
		msgs[i]->print( page);
		page << endl;
		delete msgs[i];
	}
	return send (connection, page.str().c_str(), mime.c_str());
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
		return send (connection, msg.c_str(), 0, MHD_HTTP_BAD_REQUEST);
	}

	Message msg (url);
	MHD_get_connection_values (connection, t, _get_params, &msg);
	vector<Message*> outMsgs;
	cout << method << ": ";
	msg.print(cout);
	cout << endl;
	fProcessor->processMessage (&msg, outMsgs);
	if (outMsgs.size())
		send (connection, outMsgs);
	else 
		page (connection, url);
	return MHD_YES;
}


} // end namespoace
