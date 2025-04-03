/*
 * http_fetcher.c - HTTP handling functions
 * 
 * HTTP Fetcher Copyright (C) 2001, 2003, 2004 Lyle Hanson
 * (lhanson@users.sourceforge.net)
 * 
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Library General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 * License for more details.
 * 
 * See LICENSE file for details
 * 
 * Modified by Yann Orlarey, Grame to be used within Faust (2013/01/23)
 * 
 */

#include <cstdlib> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#ifndef _WIN32
#include <strings.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#define herror perror
#else
#include <winsock2.h>
#define close closesocket
#define write(s, buf, len) send(s, buf, (int)(len), 0)
#define read(s, buf, len) recv(s, buf, (int)(len), 0)
#define rindex strchr
#define herror perror

#pragma warning(disable: 4996)

#endif
#include "compatibility.hh"
#include "sourcefetcher.hh"

#define VERSION "0.2"

/* Globals */
int timeout = DEFAULT_READ_TIMEOUT;
char* userAgent = NULL;
char* referer = NULL;
int hideUserAgent = 0;
int hideReferer = 1;
static int followRedirects = DEFAULT_REDIRECTS;	/* # of redirects to  follow */
extern const char* http_errlist[];              /* Array of HTTP Fetcher error messages */
extern char convertedError[128];                /* Buffer to used when errors contain %d */
static int errorSource = 0;
static int http_errno = 0;
static int errorInt = 0;                        /* When the error message has a %d in it, this variable is inserted */

const char* http_errlist[] =
{
	"Success",                                          /* HF_SUCCESS		*/
	"Internal Error. What the hell?!",                  /* HF_METAERROR		*/
	"Got NULL url",                                     /* HF_NULLURL		*/
	"Timed out, no metadata for %d seconds",            /* HF_HEADTIMEOUT 	*/
	"Timed out, no data for %d seconds",                /* HF_DATATIMEOUT	*/
	"Couldn't find return code in HTTP response",       /* HF_FRETURNCODE	*/
	"Couldn't convert return code in HTTP response",	/* HF_CRETURNCODE	*/
	"Request returned a status code of %d",             /* HF_STATUSCODE	*/
	"Couldn't convert Content-Length to integer",       /* HF_CONTENTLEN	*/
	"Network error, description unavailable",           /* HF_HERROR		*/
	"Status code of %d but no Location: field",         /* HF_CANTREDIRECT  */
	"Followed the maximum number of redirects (%d)"     /* HF_MAXREDIRECTS  */
};

/*
 * Used to copy in messages from http_errlist[] and replace %d's with the
 * value of errorInt.  Then we can pass the pointer to THIS
 */
char convertedError[128];

/*
 * Actually downloads the page, registering a hit (donation) If the fileBuf
 * passed in is NULL, the url is downloaded and then freed; otherwise the
 * necessary space is allocated for fileBuf. Returns size of download on
 * success, -1 on error is set.
 */
LIBFAUST_API int http_fetch(const char* url_tmp, char** fileBuf)
{
	fd_set rfds;
	struct timeval tv;
	char headerBuf [HEADER_BUF_SIZE];
	char* tmp, *url, *pageBuf, *requestBuf = NULL, *host, *charIndex;
	int sock, bytesRead = 0, contentLength = -1, bufsize = REQUEST_BUF_SIZE;
	int i, ret = -1, tempSize, selectRet, found = 0,	/* For redirects */
        redirectsFollowed = 0;

	if (url_tmp == NULL) {
		errorSource = FETCHER_ERROR;
		http_errno = HF_NULLURL;
		return -1;
	}
	/*
	 * Copy the url passed in into a buffer we can work with, change,
	 * etc.
	 */
	url = (char*)malloc(strlen(url_tmp) + 1);
	if (url == NULL) {
		errorSource = ERRNO;
		return -1;
	}
	strncpy(url, url_tmp, strlen(url_tmp) + 1);

	/*
	 * This loop allows us to follow redirects if need be.  An
	 * afterthought, added to provide this basic functionality.  Will
	 * hopefully be designed better in 2.x.x ;)
	 */
	/*
	 * while(!found && (followRedirects < 0 || redirectsFollowed <
	 * followRedirects))
	 */
	do {
		/* Seek to the file path portion of the url */
		charIndex = strstr(url, "://");
		if (charIndex != NULL) {
			/* url contains a protocol field */
			charIndex += strlen("://");
			host = charIndex;
			charIndex = strchr(charIndex, '/');
		} else {
			host = (char* )url;
			charIndex = strchr(url, '/');
		}

		/* Compose a request string */
		requestBuf = (char*)malloc(bufsize);
		if (requestBuf == NULL) {
			free(url);
			errorSource = ERRNO;
			return -1;
		}
		requestBuf[0] = 0;

		if (charIndex == NULL) {
			/*
			 * The url has no '/' in it, assume the user is
			 * making a root-level request
			 */
			tempSize = (int)strlen("GET /") + (int)strlen(HTTP_VERSION) + 2;
			if (_checkBufSize(&requestBuf, &bufsize, tempSize) ||
			    snprintf(requestBuf, bufsize, "GET / %s\r\n", HTTP_VERSION) < 0) {
				free(url);
				free(requestBuf);
				errorSource = ERRNO;
				return -1;
			}
		} else {
			tempSize = (int)strlen("GET ") + (int)strlen(charIndex) +
				(int)strlen(HTTP_VERSION) + 4;
			/* + 4 is for ' ', '\r', '\n', and NULL */
			if (_checkBufSize(&requestBuf, &bufsize, tempSize) ||
			    snprintf(requestBuf, bufsize, "GET %s %s\r\n",
				     charIndex, HTTP_VERSION) < 0) {
				free(url);
				free(requestBuf);
				errorSource = ERRNO;
				return -1;
			}
		}

		/* Null out the end of the hostname if need be */
		if (charIndex != NULL)
			*charIndex = 0;

		/*
		 * Use Host: even though 1.0 doesn't specify it.  Some
		 * servers won't play nice if we don't send Host, and it
		 * shouldn't hurt anything
		 */
		ret = (int)bufsize - (int)strlen(requestBuf);	/* Space left in buffer */
		tempSize = (int)strlen("Host: ") + (int)strlen(host) + 3;
		/* +3 for "\r\n\0" */
		if (_checkBufSize(&requestBuf, &bufsize, tempSize + 128)) {
			free(url);
			free(requestBuf);
			errorSource = ERRNO;
			return -1;
		}
		strcat(requestBuf, "Host: ");
		strcat(requestBuf, host);
		strcat(requestBuf, "\r\n");

		if (!hideReferer && referer != NULL) {	/* NO default referer */
			tempSize = (int)strlen("Referer: ") + (int)strlen(referer) + 3;
			/* + 3 is for '\r', '\n', and NULL */
			if (_checkBufSize(&requestBuf, &bufsize, tempSize)) {
				free(url);
				free(requestBuf);
				errorSource = ERRNO;
				return -1;
			}
			strcat(requestBuf, "Referer: ");
			strcat(requestBuf, referer);
			strcat(requestBuf, "\r\n");
		}
		if (!hideUserAgent && userAgent == NULL) {
			tempSize = (int)strlen("User-Agent: ") +
				(int)strlen(DEFAULT_USER_AGENT) + (int)strlen(VERSION) + 4;
			/* + 4 is for '\', '\r', '\n', and NULL */
			if (_checkBufSize(&requestBuf, &bufsize, tempSize)) {
				free(url);
				free(requestBuf);
				errorSource = ERRNO;
				return -1;
			}
			strcat(requestBuf, "User-Agent: ");
			strcat(requestBuf, DEFAULT_USER_AGENT);
			strcat(requestBuf, "/");
			strcat(requestBuf, VERSION);
			strcat(requestBuf, "\r\n");
		} else if (!hideUserAgent) {
			tempSize = (int)strlen("User-Agent: ") + (int)strlen(userAgent) + 3;
			/* + 3 is for '\r', '\n', and NULL */
			if (_checkBufSize(&requestBuf, &bufsize, tempSize)) {
				free(url);
				free(requestBuf);
				errorSource = ERRNO;
				return -1;
			}
			strcat(requestBuf, "User-Agent: ");
			strcat(requestBuf, userAgent);
			strcat(requestBuf, "\r\n");
		}
		tempSize = (int)strlen("Connection: Close\r\n\r\n");
		if (_checkBufSize(&requestBuf, &bufsize, tempSize)) {
			free(url);
			free(requestBuf);
			errorSource = ERRNO;
			return -1;
		}
		strcat(requestBuf, "Connection: Close\r\n\r\n");

		/* Now free any excess memory allocated to the buffer */
		tmp = (char*)realloc(requestBuf, strlen(requestBuf) + 1);
		if (tmp == NULL) {
			free(url);
			free(requestBuf);
			errorSource = ERRNO;
			return -1;
		}
		requestBuf = tmp;

		sock = makeSocket(host);	/* errorSource set within
                                    * makeSocket */
		if (sock == -1) {
			free(url);
			free(requestBuf);
			return -1;
		}
		free(url);
		url = NULL;

		if (write(sock, requestBuf, strlen(requestBuf)) == -1) {
			close(sock);
			free(requestBuf);
			errorSource = ERRNO;
			return -1;
		}
		free(requestBuf);
		requestBuf = NULL;

		/* Grab enough of the response to get the metadata */
		ret = _http_read_header(sock, headerBuf);	/* errorSource set
                                                    * within */
		if (ret < 0) {
			close(sock);
			return -1;
		}
		/* Get the return code */
		charIndex = strstr(headerBuf, "HTTP/");
		if (charIndex == NULL) {
			close(sock);
			errorSource = FETCHER_ERROR;
			http_errno = HF_FRETURNCODE;
			return -1;
		}
		while (*charIndex != ' ')
			charIndex++;
		charIndex++;

		ret = sscanf(charIndex, "%d", &i);
		if (ret != 1) {
			close(sock);
			errorSource = FETCHER_ERROR;
			http_errno = HF_CRETURNCODE;
			return -1;
		}
		if (i < 200 || i > 307) {
			close(sock);
			errorInt = i;	/* Status code, to be inserted in
                             * error string */
			errorSource = FETCHER_ERROR;
			http_errno = HF_STATUSCODE;
			return -1;
		}
		/*
		 * If a redirect, repeat operation until final URL is found
		 * or we redirect followRedirects times.  Note the case
		 * sensitive "Location", should probably be made more robust
		 * in the future (without relying on the non-standard
		 * strcasecmp()). This bit mostly by Dean Wilder, tweaked by
		 * me
		 */
		if (i >= 300) {
			redirectsFollowed++;

			/*
			 * Pick up redirect URL, allocate new url, and repeat
			 * process
			 */
			charIndex = strstr(headerBuf, "Location:");
			if (!charIndex) {
				close(sock);
				errorInt = i;	/* Status code, to be
                                 * inserted in error string */
				errorSource = FETCHER_ERROR;
				http_errno = HF_CANTREDIRECT;
				return -1;
			}
			charIndex += strlen("Location:");
			/* Skip any whitespace... */
			while (*charIndex != '\0' && isspace(*charIndex))
				charIndex++;
			if (*charIndex == '\0') {
				close(sock);
				errorInt = i;	/* Status code, to be
                                 * inserted in error string */
				errorSource = FETCHER_ERROR;
				http_errno = HF_CANTREDIRECT;
				return -1;
			}
			i = (int)strcspn(charIndex, " \r\n");
			if (i > 0) {
				url = (char*)malloc(i + 1);
				strncpy(url, charIndex, i);
				url[i] = '\0';
			} else
				/*
				 * Found 'Location:' but contains no URL!
				 * We'll handle it as 'found', hopefully the
				 * resulting document will give the user a
				 * hint as to what happened.
				 */
				found = 1;
		} else {
			found = 1;
		}
	} while (!found && (followRedirects < 0 || redirectsFollowed <= followRedirects));

	if (url) {		/* Redirection code may malloc this, then
                     * exceed followRedirects */
		free(url);
		url = NULL;
	}
	if (redirectsFollowed >= followRedirects && !found) {
		close(sock);
		errorInt = followRedirects;	/* To be inserted in error
                                     * string */
		errorSource = FETCHER_ERROR;
		http_errno = HF_MAXREDIRECTS;
		return -1;
	}
	/*
	 * Parse out about how big the data segment is. Note that under
	 * current HTTP standards (1.1 and prior), the Content-Length field
	 * is not guaranteed to be accurate or even present. I just use it
	 * here so I can allocate a ballpark amount of memory.
	 * 
	 * Note that some servers use different capitalization
	 */
	charIndex = strstr(headerBuf, "Content-Length:");
	if (charIndex == NULL)
		charIndex = strstr(headerBuf, "Content-length:");

	if (charIndex != NULL) {
		ret = sscanf(charIndex + strlen("content-length: "), "%d",
			     &contentLength);
		if (ret < 1) {
			close(sock);
			errorSource = FETCHER_ERROR;
			http_errno = HF_CONTENTLEN;
			return -1;
		}
	}
	/* Allocate enough memory to hold the page */
	if (contentLength == -1)
		contentLength = DEFAULT_PAGE_BUF_SIZE;

	pageBuf = (char*)malloc(contentLength);
	if (pageBuf == NULL) {
		close(sock);
		errorSource = ERRNO;
		return -1;
	}
	/* Begin reading the body of the file */
	while (ret > 0) {
		FD_ZERO(&rfds);
		FD_SET(sock, &rfds);
		tv.tv_sec = timeout;
		tv.tv_usec = 0;

		if (timeout >= 0)
			selectRet = select(sock + 1, &rfds, NULL, NULL, &tv);
		else		/* No timeout, can block indefinately */
			selectRet = select(sock + 1, &rfds, NULL, NULL, NULL);

		if (selectRet == 0) {
			errorSource = FETCHER_ERROR;
			http_errno = HF_DATATIMEOUT;
			errorInt = timeout;
			close(sock);
			free(pageBuf);
			return -1;
		} else if (selectRet == -1) {
			close(sock);
			free(pageBuf);
			errorSource = ERRNO;
			return -1;
		}
		ret = int(read(sock, pageBuf + bytesRead, contentLength));
		if (ret == -1) {
			close(sock);
			free(pageBuf);
			errorSource = ERRNO;
			return -1;
		}
		bytesRead += ret;

		if (ret > 0) {
			/*
			 * To be tolerant of inaccurate Content-Length
			 * fields, we'll allocate another read-sized chunk to
			 * make sure we have enough room.
			 */
			tmp = (char*)realloc(pageBuf, bytesRead + contentLength);
			if (tmp == NULL) {
				close(sock);
				free(pageBuf);
				errorSource = ERRNO;
				return -1;
			}
			pageBuf = tmp;
		}
	}

	/*
	 * The download buffer is too large.  Trim off the safety padding.
	 * Note that we add one NULL byte to the end of the data, as it may
	 * not already be NULL terminated and we can't be sure what type of
	 * data it is or what the caller will do with it.
	 */
	tmp = (char*)realloc(pageBuf, bytesRead + 1);
	/*
	 * tmp shouldn't be null, since we're _shrinking_ the buffer, and if
	 * it DID fail, we could go on with the too-large buffer, but
	 * something would DEFINATELY be wrong, so we'll just give an error
	 * message
	 */
	if (tmp == NULL) {
		close(sock);
		free(pageBuf);
		errorSource = ERRNO;
		return -1;
	}
	pageBuf = tmp;
	pageBuf[bytesRead] = '\0';	/* NULL terminate the data */

	if (fileBuf == NULL)        /* They just wanted us to "hit" the url */
		free(pageBuf);
	else
		*fileBuf = pageBuf;

	close(sock);
	return bytesRead;
}

/*
 * Changes the User Agent.  Returns 0 on success, -1 on error.
 */
int http_setUserAgent(const char* newAgent)
{
	static int freeOldAgent = 0;	/* Indicates previous
                                     * malloc's */
	char* tmp;

	if (newAgent == NULL) {
		if (freeOldAgent)
			free(userAgent);
		userAgent = NULL;
		hideUserAgent = 1;
	} else {
		tmp = (char*)malloc(strlen(newAgent) + 1);
		if (tmp == NULL) {
			errorSource = ERRNO;
			return -1;
		}
		if (freeOldAgent)
			free(userAgent);
		userAgent = tmp;
		strcpy(userAgent, newAgent);
		freeOldAgent = 1;
		hideUserAgent = 0;
	}

	return 0;
}

/*
 * Changes the Referer.  Returns 0 on success, -1 on error
 */
int http_setReferer(const char* newReferer)
{
	static int freeOldReferer = 0;	/* Indicated previous
                                    * malloc's */
	char* tmp;

	if (newReferer == NULL) {
		if (freeOldReferer)
			free(referer);
		referer = NULL;
		hideReferer = 1;
	} else {
		tmp = (char*)malloc(strlen(newReferer) + 1);
		if (tmp == NULL) {
			errorSource = ERRNO;
			return -1;
		}
		if (freeOldReferer)
			free(referer);
		referer = tmp;
		strcpy(referer, newReferer);
		freeOldReferer = 1;
		hideReferer = 0;
	}

	return 0;
}

/*
 * Changes the amount of time that HTTP Fetcher will wait for data before
 * timing out on reads
 */
void http_setTimeout(int seconds)
{
	timeout = seconds;
}

/*
 * Changes the number of HTTP redirects HTTP Fetcher will automatically
 * follow.  If a request returns a status code of 3XX and contains a
 * "Location:" field, the library will transparently follow up to the
 * specified number of redirects.  With this implementation (which is just a
 * stopgap, really) the caller won't be aware of any redirection and will
 * assume the returned document came from the original URL. To disable
 * redirects, pass a 0.  To follow unlimited redirects (probably unwise),
 * pass a negative value.  The default is to follow 3 redirects.
 */
void http_setRedirects(int redirects)
{
	followRedirects = redirects;
}

/*
 * Puts the filename portion of the url into 'filename'. Returns: 0 on
 * success 1 when url contains no end filename (i.e., 'www.foo.com/'), and
 * **filename should not be assumed to be valid -1 on error
 */
int http_parseFilename(const char* url, char** filename)
{
	char* ptr;

	if (url == NULL) {
		errorSource = FETCHER_ERROR;
		http_errno = HF_NULLURL;
		return -1;
	}
	ptr = (char*)strrchr(url, '/');
	if (ptr == NULL)
		/* Root level request, apparently */
		return 1;

	ptr++;
	if (*ptr == '\0')
		return 1;

	*filename = (char*)malloc(strlen(ptr) + 1);
	if (*filename == NULL) {
		errorSource = ERRNO;
		return -1;
	}
	strcpy(*filename, ptr);

	return 0;
}

/*
 * Depending on the source of error, calls either perror() or prints an HTTP
 * Fetcher error message to stdout
 */
void http_perror(const char* string)
{
	if (errorSource == ERRNO)
		perror(string);
	else if (errorSource == H_ERRNO)
		herror(string);
	else if (errorSource == FETCHER_ERROR) {
		const char* stringIndex;

		if (strstr(http_errlist[http_errno], "%d") == NULL) {
			fputs(string, stderr);
			fputs(": ", stderr);
			fputs(http_errlist[http_errno], stderr);
			fputs("\n", stderr);
		} else {
			/*
			 * The error string has a %d in it, we need to insert
			 * errorInt
			 */
			stringIndex = http_errlist[http_errno];
			while (*stringIndex != '%') {	/* Print up to the %d */
				fputc(*stringIndex, stderr);
				stringIndex++;
			}
			fprintf(stderr, "%d", errorInt);	/* Print the number */
			stringIndex += 2;	/* Skip past the %d */
			while (*stringIndex != 0) {	/* Print up to the end
							 * NULL */
				fputc(*stringIndex, stderr);
				stringIndex++;
			}
			fputs("\n", stderr);
		}
	}
}

/*
 * Returns a pointer to the current error description message. The message
 * pointed to is only good until the next call to http_strerror(), so if you
 * need to hold on to the message for a while you should make a copy of it
 */
const char* http_strerror()
{
	if (errorSource == ERRNO)
		return strerror(errno);
	else if (errorSource == H_ERRNO)
#ifdef HAVE_HSTRERROR
		return hstrerror(h_errno);
#else
		return http_errlist[HF_HERROR];
#endif
	else if (errorSource == FETCHER_ERROR) {
		if (strstr(http_errlist[http_errno], "%d") == NULL)
			return http_errlist[http_errno];
		else {
			/*
			 * The error string has a %d in it, we need to insert
			 * errorInt. convertedError[128] has been declared
			 * for that purpose
			 */
			char* stringIndex, *originalError;

			originalError = (char*)http_errlist[http_errno];
			convertedError[0] = 0;	/* Start off with NULL */
			stringIndex = strstr(originalError, "%d");
			strncat(convertedError, originalError,	/* Copy up to %d */
            labs(long(stringIndex - originalError)));
			snprintf(&convertedError[strlen(convertedError)], sizeof(convertedError), "%d", errorInt);
			stringIndex += 2;	/* Skip past the %d */
			strcat(convertedError, stringIndex);

			return convertedError;
		}
	}
	return http_errlist[HF_METAERROR];	/* Should NEVER happen */
}

/*
 * Reads the metadata of an HTTP response. Perhaps a little inefficient, as
 * it reads 1 byte at a time, but I don't think it's that much of a loss
 * (most headers aren't HUGE). Returns: # of bytes read on success, or -1 on
 * error
 */
int _http_read_header(int sock, char* headerPtr)
{
	fd_set rfds;
	struct timeval tv;
	int	bytesRead = 0, newlines = 0, ret, selectRet;

	while (newlines != 2 && bytesRead != HEADER_BUF_SIZE) {
		FD_ZERO(&rfds);
		FD_SET(sock, &rfds);
		tv.tv_sec = timeout;
		tv.tv_usec = 0;

		if (timeout >= 0)
			selectRet = select(sock + 1, &rfds, NULL, NULL, &tv);
		else		/* No timeout, can block indefinately */
			selectRet = select(sock + 1, &rfds, NULL, NULL, NULL);

		if (selectRet == 0) {
			errorSource = FETCHER_ERROR;
			http_errno = HF_HEADTIMEOUT;
			errorInt = timeout;
			return -1;
		} else if (selectRet == -1) {
			errorSource = ERRNO;
			return -1;
		}
		ret = int(read(sock, headerPtr, 1));
		if (ret == -1) {
			errorSource = ERRNO;
			return -1;
		}
		bytesRead++;

		if (*headerPtr == '\r') {	/* Ignore CR */
			/*
			 * Basically do nothing special, just don't set
			 * newlines to 0
			 */
			headerPtr++;
			continue;
		} else if (*headerPtr == '\n')	/* LF is the separator */
			newlines++;
		else
			newlines = 0;

		headerPtr++;
	}

	headerPtr -= 3;		/* Snip the trailing LF's */
	*headerPtr = '\0';
	return bytesRead;
}

/*
 * Opens a TCP socket and returns the descriptor Returns: socket descriptor,
 * or -1 on error
 */
int makeSocket(char* host)
{
	int	sock;               /* Socket descriptor */
	struct sockaddr_in sa;	/* Socket address */
	struct hostent* hp;     /* Host entity */
	int	ret;
	int	port;
	char* p;
 
	/* Check for port number specified in URL */
	p = strchr(host, ':');
	if (p) {
        port = std::atoi(p + 1);
		*p = '\0';
	} else
		port = PORT_NUMBER;

	hp = gethostbyname(host);
	if (hp == NULL) {
		errorSource = H_ERRNO;
		return -1;
	}
	/* Copy host address from hostent to (server) socket address */
	memcpy((char*)&sa.sin_addr, (char*)hp->h_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;	/* Set service sin_family to PF_INET */
	sa.sin_port = htons(port);	/* Put portnum into sockaddr */

	sock = (int)socket(hp->h_addrtype, SOCK_STREAM, 0);
	if (sock == -1) {
		errorSource = ERRNO;
		return -1;
	}
	ret = connect(sock, (struct sockaddr*)&sa, sizeof(sa));
	if (ret == -1) {
		errorSource = ERRNO;
		return -1;
	}
	return sock;
}

/*
 * Determines if the given NULL-terminated buffer is large enough to
 * concatenate the given number of characters.  If not, it attempts to grow
 * the buffer to fit. Returns: 0 on success, or -1 on error (original buffer
 * is unchanged).
 */
int _checkBufSize(char** buf, int* bufsize, int more)
{
	char* tmp;
	int	roomLeft = (int)*bufsize - (int)(strlen(*buf) + 1);
	if (roomLeft > more)
		return 0;
	tmp = (char*)realloc(*buf, *bufsize + more + 1);
	if (tmp == NULL)
		return -1;
	*buf = tmp;
	*bufsize += more + 1;
	return 0;
}
