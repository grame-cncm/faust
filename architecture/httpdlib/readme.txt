=================================================================
                         FAUST HTTPD Library

                     Copyright (c) 2012 Grame
=================================================================

----------------------------------------------------------------------
 Compiling the library
----------------------------------------------------------------------

The FAUST HTTPD library project depends on the libmicrohttpd library.
You should first compile and install this library before compiling 
the FAUST HTTPD library. 
(see at http://www.gnu.org/software/libmicrohttpd/).

1) Compiling libmicrohttpd
-----------------------------------
Typically on linux or Mac OS systems:
	> cd location/of/libmicrohttpd
	> ./configure
	> make
	> sudo make

2) Compiling the FAUST HTTPD library
-----------------------------------
To compile:
	change to cmake directory
	type:  cmake -G "your target generator"
	run your project/makefile and compile

Typically on linux systems:
	> cd cmake
	> cmake -G "Unix Makefiles"
	> make

The compiler output is a static library named libHTTPDFaust.a and placed 
in the 'httpdlib' folder. Note that when 'Release' and 'Debug' targets
apply, only the 'Release' output goes to the 'httpdlib' folder.

----------------------------------------------------------------------
 Using the library
----------------------------------------------------------------------
The library provides a single interface file: HTTPDControler.h
The following options should be used to compile:
	-Ihttpdlib/include lmicrohttpd -Lhttpdlib -lHTTPDFaust
See the faust/readme.txt file for more details about the library.

----------------------------------------------------------------------
 Note about URLs and the Faust UI names:
----------------------------------------------------------------------
Characters in a url could be:
1. Reserved: ; / ? : @ & = + $ ,
   These characters delimit URL parts.
2. Unreserved: alphanum - _ . ! ~ * ' ( )
   These characters have no special meaning and can be used as is.
3. Excluded: control characters, space, < > # % ", { } | \ ^ [ ] `

To solve potential conflicts between the Faust UI objects naming scheme and
the URL allowed characters, the reserved and excluded characters are replaced
with '-' (hyphen).
Space or tabulation are replaced with '_' (underscore)

-----------------------------------------------------------------
    Note about the http messages and urls
-----------------------------------------------------------------
The url address space adheres strictly to the hierarchy defined by
the 'addnode' and 'opengroup' calls.
A node expects to receive http messages with a single float value 
as parameter. A Faust server supports both 'GET' and 'POST' transactions.
When using 'GET', values are expected to be associated to the 'value' key
(e.g. any/param/url?value=0.8)

*** Faust server root url ***
A Faust server delivers a web page containing all its user interface 
from its root url. It delivers the json description of its user
interface as answer to a value='json' message.

*** Querying values ***
When sending a message to an url without associated value, a Faust 
server answers with the corresponding node value.

-----------------------------------------------------------------
    Note about network management
-----------------------------------------------------------------
The default TCP port is chosen in an unassigned range 
see IANA PORT NUMBERS (last updated 2011-01-24)
at http://www.iana.org/assignments/port-numbers
As of today (jan. 27 2011), the range 5507-5552 is unassigned
and the default listening port number is 5510.

*** Changing the ports numbers with the command line ***
An HTTPDControler object takes the command line arguments as constructor 
parameters. It supports the following options to change the UDP ports 
numbers:
	-port number

*** Dynamic TCP listening port allocation ***
When the TCP listening port number is busy, the system automatically 
looks for the next available port number. 

======================================================================
In case of trouble, contact me: <fober@grame.fr>
----------------------------------------------------------------------
Copyright 2012 (c) Grame 
