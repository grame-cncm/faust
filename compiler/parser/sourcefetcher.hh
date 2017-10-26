/* http_fetcher.h - HTTP handling functions

	HTTP Fetcher
	Copyright (C) 2001, 2003, 2004 Lyle Hanson (lhanson@users.sourceforge.net)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	See LICENSE file for details
									
*/

#ifndef HTTP_FETCHER_H
#define HTTP_FETCHER_H

/* Error sources */
#define FETCHER_ERROR	0
#define ERRNO			1
#define H_ERRNO			2

/* HTTP Fetcher error codes */
#define HF_SUCCESS		0
#define HF_METAERROR	1
#define HF_NULLURL		2
#define HF_HEADTIMEOUT	3
#define HF_DATATIMEOUT	4
#define HF_FRETURNCODE	5
#define HF_CRETURNCODE	6
#define HF_STATUSCODE	7
#define HF_CONTENTLEN	8
#define HF_HERROR		9
#define HF_CANTREDIRECT 10
#define HF_MAXREDIRECTS 11

#define PORT_NUMBER 			80
#define HTTP_VERSION 			"HTTP/1.0"
#define DEFAULT_USER_AGENT		"HTTP Fetcher"
//#define DEFAULT_READ_TIMEOUT	30		// Seconds to wait before giving up when no data is arriving 
#define DEFAULT_READ_TIMEOUT	5		// Seconds to wait before giving up when no data is arriving 
	 
#define REQUEST_BUF_SIZE 		1024
#define HEADER_BUF_SIZE 		1024
#define DEFAULT_PAGE_BUF_SIZE   (1024 * 200)    /* 200K should hold most things */
#define DEFAULT_REDIRECTS       3               /* Number of HTTP redirects to follow */

#ifdef _WIN32
	#define	EXPORT __declspec(dllexport)
#else
	#define	EXPORT __attribute__ ((visibility("default")))
#endif

/******************************************************************************/
/**************** Function declarations and descriptions **********************/
/******************************************************************************/

/* 
 * [!!! NOTE !!!]  All HTTP Fetcher functions return -1 on error.  You can
 *	then either call http_perror to print the error message or call
 *	http_strerror to get a pointer to it
 */

	/*
	 * Download the page, registering a hit. If you pass it a NULL for fileBuf,
	 *  'url' will be requested but will not remain in memory (useful for
	 *  simply registering a hit).  Otherwise necessary space will be allocated
	 *  and will be pointed to by fileBuf, and has to be dealoocated after use.  
     *  Note that a NULL byte is added to the data, so the actual buffer 
     *  will be the file size + 1. 
	 * Returns:
	 *	# of bytes downloaded, or
	 *	-1 on error
	 */
EXPORT int http_fetch(const char *url, char **fileBuf);

	/*
	 * Changes the User Agent (shown to the web server with each request)
	 *	Send it NULL to avoid telling the server a User Agent
	 *	By default, the User Agent is sent (The default one unless changed)
	 * Returns:
	 *	0 on success, or
	 *	-1 on error (previous value for agent remains unchanged)
	 */
int http_setUserAgent(const char *newAgent);

	/*
	 * Changes the Referer (shown to the web server with each request)
	 *	Send it NULL to avoid thelling the server a Referer
	 *	By default, no Referer is sent
	 * Returns:
	 *	0 on success, or
	 *	-1 on error
	 */
int http_setReferer(const char *newReferer);

	/*
	 * Changes the maximum amount of time that HTTP Fetcher will wait on
	 *	data.  If this many seconds elapses without more data from the
	 *	server, http_fetch will return with an error.
	 * If you pass a value less than 0, reads will not time out, potentially
	 *	waiting forever (or until data shows up, whichever comes first)
	 */
void http_setTimeout(int seconds);

	/*
	 * Changes the number of HTTP redirects HTTP Fetcher will automatically
	 *	follow.  If a request returns a status code of 3XX and contains
	 *	a "Location:" field, the library will transparently follow up to
	 *	the specified number of redirects.  With this implementation
	 *	(which is just a stopgap, really) the caller won't be aware of any
	 *	redirection and will assume the returned document came from the original
	 *	URL.
	 * To disable redirects, pass a 0.  To follow unlimited redirects (probably
	 *  unwise), pass a negative value.  The default is to follow 3 redirects.
	 */
void http_setRedirects(int redirects);

	/*
	 * Takes a url and puts the filename portion of it into 'filename'.
	 * Returns:
	 *	0 on success, or
	 *	1 when url contains no end filename (i.e., "www.foo.com/")
	 *	and **filename should not be assumed to point to anything), or
	 *	-1 on error
	 */
int http_parseFilename(const char *url, char **filename);

	/*
	 * Works like perror.  If an HTTP Fetcher function ever returns an
	 *	error (-1), this will print a descriptive message to standard output
	 */
void http_perror(const char *string);

	/*
	 * Returns a pointer to the current error description message.  The
	 *	message pointed to is only good until the next call to http_strerror(),
	 *	so if you need to hold on to the message for a while you should make
	 *	a copy of it.
	 */
const char *http_strerror();

/******************************************************************************/
/**** The following functions are used INTERNALLY by http_fetcher *************/
/******************************************************************************/

	/*
	 * Reads the metadata of an HTTP response.  On success returns the number
	 * Returns:
	 *	# of bytes read on success, or
	 *	-1 on error
	 */
int _http_read_header(int sock, char *headerPtr);

	/*
	 * Opens a TCP socket and returns the descriptor
	 * Returns:
	 *	socket descriptor, or
	 *	-1 on error
	 */
int makeSocket(char *host);

	/*
	 * Determines if the given NULL-terminated buffer is large enough to
	 *	concatenate the given number of characters.  If not, it attempts to
	 *	grow the buffer to fit.
	 * Returns:
	 *	0 on success, or
	 *	-1 on error (original buffer is unchanged).
	 */
int _checkBufSize(char **buf, int *bufsize, int more);

#endif
