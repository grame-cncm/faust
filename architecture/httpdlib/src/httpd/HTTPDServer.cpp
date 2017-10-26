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
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "HTTPDServer.h"
#include "Message.h"
#include "MessageProcessor.h"

#ifdef _WIN32
#include <io.h>
#define lseek _lseek
#endif

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

// Convert string to float. Accepts both . and , as decimal point
// Syntax is : [ ]*[+|-]n*(.|,)n*
static float mystrtof(const char* str, const char** endptr)
{
	const char* p = str;
	float		sign = 1.0;
	float		val = 0;
	
	// skip leading white spaces
	while (isspace(*p)) p++;
	// analyze sign
	if (*p == '-') { sign = -1.0; p++; }
	else if (*p == '+') { sign = 1.0; p++; }
	// fix part
	while (isdigit(*p)) { val = val*10 + (*p++ - '0'); }
	// decimal part
	if (*p == '.' | *p == ',') {
		p++;
		// decimal part
		int virgule = 10; 
		while (isdigit(*p)) { 
			val = val + double((*p++ - '0'))/virgule; 
			virgule *= 10; 
		}
	}
	*endptr = p;
	return sign*val;
}

//--------------------------------------------------------------------------
// fonct(ion appelée par libmicrohttpd pour tous les parametres de la requète (soit GET soit POST)
static int _get_params (void *cls, enum MHD_ValueKind kind, const char *key, const char *value)
{
	Message* msg = (Message*)cls;
	msg->add (string(key));
	if (value) {
		const char* endptr;
		float fval = mystrtof(value, &endptr);
		if ((fval == 0) && (endptr == value))		// not a float value
			msg->add (string(value));
		else 
			msg->add (fval);
	}
	return MHD_YES;
}

//--------------------------------------------------------------------------
// the http server
//--------------------------------------------------------------------------
HTTPDServer::HTTPDServer(MessageProcessor* mp)
	: fProcessor(mp), fServer(0), fDebug(false)
{
}

HTTPDServer::~HTTPDServer() { stop(); }

//--------------------------------------------------------------------------
bool HTTPDServer::start(int port)
{
	fServer = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, port, NULL, NULL, _answer_to_connection, this, MHD_OPTION_END);
	return fServer != 0;
}

//--------------------------------------------------------------------------
int HTTPDServer::send (struct MHD_Connection *connection, const char *page, const char* type, int status)
{
	struct MHD_Response *response = MHD_create_response_from_buffer (strlen (page), (void *) page, MHD_RESPMEM_MUST_COPY);
	if (!response) {
		cerr << "MHD_create_response_from_buffer error: null response\n";
		return MHD_NO;
	}
	MHD_add_response_header (response, "Content-Type", type ? type : "text/plain");
	MHD_add_response_header (response, "Access-Control-Allow-Origin", "*");
	int ret = MHD_queue_response (connection, status, response);
	MHD_destroy_response (response);
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
//	char * root =  getenv("FAUSTDocumentRoot");
	string file = ".";
	file += page;
	const char* type = getMIMEType (file);

	int fd;

#if defined(_WIN32) && !defined(__MINGW32__)
	int fhd;
	fd = _sopen_s(&fhd, file.c_str(), _O_RDONLY, _SH_DENYNO, _S_IREAD);
#else
	fd = open (file.c_str(), O_RDONLY);
#endif
	if (fd != -1) {
		int length = lseek(fd, (long)0, SEEK_END);
		lseek(fd, 0, SEEK_SET);
		
		struct MHD_Response *response = MHD_create_response_from_fd (length, fd);
		if (!response ) {
			cerr << "MHD_create_response_from_fd error: null response\n";
			return MHD_NO;
		}
		MHD_add_response_header (response, "Content-Type", type ? type : "text/plain");
		MHD_add_response_header (response, "Access-Control-Allow-Origin", "*");
		ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
		MHD_destroy_response (response);
	}
	else {
		ret = send (connection, "", 0, MHD_HTTP_NOT_FOUND);
	}
	return ret;
}

//--------------------------------------------------------------------------
int HTTPDServer::send(struct MHD_Connection *connection, std::vector<Message*> msgs)
{
    stringstream page;
    string mime;
    for (unsigned int i=0; i<msgs.size(); i++) {
        string currentmime = msgs[i]->mimetype();
        if (mime.size() && (currentmime != mime)) {         // check for mime type change
            string res = page.str();
            send(connection, res.c_str(), mime.c_str());    // send the current mime data
            page.str("");                                   // and clear the stream
        }
        mime = currentmime;
        msgs[i]->print( page);
        page << endl;
        delete msgs[i];
    }
    string res = page.str();
    return send(connection, res.c_str(), mime.c_str());
}

//--------------------------------------------------------------------------
// Callback appelée par libmicrohttpd
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
	if (fDebug) {
		cout << method << ": ";
		msg.print(cout);
		cout << endl;
	}
	fProcessor->processMessage (&msg, outMsgs);
	if (outMsgs.size())
		send (connection, outMsgs);
	else 
		page (connection, url);
	return MHD_YES;
}


} // end namespoace
