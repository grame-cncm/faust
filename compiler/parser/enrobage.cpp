/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/
 
 
 
#include "enrobage.hh"
#include <string>
#include "compatibility.hh"


//----------------------------------------------------------------


/**
 * Try to open a file within a path (a set of directory).
 */

void streamCopyUntil(istream& src, ostream& dst, const string& until)
{ 
	string	s;
	while ( getline(src,s) && (s != until) ) dst << s << endl;
}


/**
 * Try to open a file within a path (a set of directory).
 */

void streamCopyUntilEnd(istream& src, ostream& dst)
{ 
	string	s;
	while ( getline(src,s) ) dst << s << endl;
}


/**
 * Try to open a file within a path (a set of directory).
 */

ifstream* open_stream(const char* filename)
{
	ifstream* f = new ifstream();
	f->open(filename);
	if (f->good()) return f;
	delete f;
	return 0;
}
	
ifstream* open_path_stream (const char* lofdir, const char* filename)
{
	char		old[PATH_MAX];
	char* 		lod = strdup(lofdir);
	char* 		dir = strtok(lod, ":");
	
	getcwd (old, PATH_MAX);
	while (dir) {
		if (chdir(dir) == 0) {
			
			ifstream* f = open_stream(filename);
			if (f) {
				free(lod);
				return f;
			}
			chdir(old);
		} else  {
		}
		dir = strtok(NULL, ":");
	}
	cerr << "file " << filename << " not found in path " << lofdir << endl;
	free (lod);
	return 0;
}


/**
 * Try to open an architecture file.
 */
ifstream* open_arch_stream (const char* filename)
{	
	ifstream* f = open_stream(filename);
	
	if (f) {
		return f;
	} else {
		const char* p1 = getenv("FAUST_PATH");
		const char* p2 = (p1 != 0) ? p1 : "/usr/local/lib/faust/:/usr/lib/faust/";
		return open_path_stream(p2, filename);
	}
}


	


/*---------------------------------------------*/

		
bool check_file(char* filename)
{
	FILE* f = fopen(filename, "r");
	
	if (f == NULL) {
		fprintf(stderr, "faust: "); perror(filename);
	} else {
		fclose(f);
	}
	return f != NULL;
}
		

/**
 * Try to open a file.
 */
FILE* fopensearch(const char* filename)
{	
	FILE* f = fopen(filename, "r");
	
	if (f) {
		return f;
	} else {
		const char* p1 = getenv("FAUST_PATH");
		const char* p2 = (p1 != 0) ? p1 : "/usr/local/lib/faust/:/usr/lib/faust/";
		return fopenpath(p2, filename);
	}
}

	
FILE* fopenpath(const char* lofdir, const char* filename)
{
	char		old[PATH_MAX];
	char* 		lod = strdup(lofdir);
	char* 		dir = strtok(lod, ":");
	
	getcwd (old, PATH_MAX);
	while (dir) {
		if (chdir(dir) == 0) {
			
			FILE* f = fopen(filename, "r");
			chdir(old);
			if (f) {
				free(lod);
				return f;
			}
		} else  {
		}
		dir = strtok(NULL, ":");
	}
	cerr << "file " << filename << " not found in path " << lofdir << endl;
	free (lod);
	return 0;
}

