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
#include <climits>

extern string gFaustSuperDirectory;
extern string gFaustDirectory;
extern string gMasterDirectory;
//----------------------------------------------------------------


/**
 * Copy src to dst until specific line.
 */
void streamCopyUntil(istream& src, ostream& dst, const string& until)
{ 
	string	s;
	while ( getline(src,s) && (s != until) ) dst << s << endl;
}


/**
 * Copy src to dst until end
 */
void streamCopyUntilEnd(istream& src, ostream& dst)
{ 
	string	s;
	while ( getline(src,s) ) dst << s << endl;
}


/**
 * Try to open an architecture file searching in various directories
 */
ifstream* open_arch_stream(const char* filename)
{
	char	old[PATH_MAX];
    getcwd (old, PATH_MAX);

    {
	    ifstream* f = new ifstream();
	    f->open(filename, ifstream::in); if (f->is_open()) return f; else delete f;
    }
	if ( (chdir(gFaustDirectory.c_str())==0) && (chdir("architecture")==0) ) {
        ifstream* f = new ifstream();
		f->open(filename, ifstream::in);
		if (f->good()) return f; else delete f;
	}
	chdir(old);
	if ((chdir(gFaustSuperDirectory.c_str())==0) && (chdir("architecture")==0) ) {
        ifstream* f = new ifstream();
		f->open(filename, ifstream::in);
		if (f->good()) return f; else delete f;
	}
	chdir(old);
	if (chdir("/usr/local/lib/faust")==0) {
        ifstream* f = new ifstream();
		f->open(filename); 
		if (f->good()) return f; else delete f;
	}
	chdir(old);
	if (chdir("/usr/lib/faust")==0) {
        ifstream* f = new ifstream();
		f->open(filename); 
		if (f->good()) return f; else delete f;
	}
	
	return 0;
}



/*---------------------------------------------*/

/**
 * Check if a file exists.
 * @return true if the file exist, false otherwise
 */
		
bool check_file(const char* filename)
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
 * Try to open the file 'dir/filename'
 */
static FILE* fopenat(const char* dir, const char* filename)
{
    char        olddir[PATH_MAX];
    
    getcwd (olddir, PATH_MAX);
    if (chdir(dir) == 0) {           
        FILE* f = fopen(filename, "r");
        chdir(olddir);
        return f;
    }
    chdir(olddir);
    return 0;
}

/**
 * Try to open the file 'dir/filename'
 */
static FILE* fopenat(const string& dir, const char* filename)
{
    return fopenat(dir.c_str(), filename);
}

/**
 * Try to open the file 'dir/path/filename'
 */
static FILE* fopenat(const string& dir, const char* path, const char* filename)
{
    char        olddir[PATH_MAX];
    
    getcwd (olddir, PATH_MAX);
    if (chdir(dir.c_str()) == 0) {
        if (chdir(path) == 0) {            
            FILE* f = fopen(filename, "r");
            chdir(olddir);
            return f;
        }
    }
    chdir(olddir);
    return 0;
}


/**
 * Try to open the file searching in various directories
 */

#ifdef WIN32
FILE* fopensearch(const char* filename)
{   
    FILE* f;

    if ((f = fopen(filename, "r"))) return f;
    if ((f = fopenat(gMasterDirectory, filename))) return f;
    if ((f = fopenat(gFaustDirectory, "architecture", filename))) return f;
    if ((f = fopenat(gFaustSuperDirectory, "architecture", filename))) return f;
    return 0;
}
#else
FILE* fopensearch(const char* filename)
{   
    FILE* f;

    if ((f = fopen(filename, "r"))) return f;
    if ((f = fopenat(gMasterDirectory, filename))) return f;
    if ((f = fopenat(gFaustDirectory, "architecture", filename))) return f;
    if ((f = fopenat(gFaustSuperDirectory, "architecture", filename))) return f;
    if ((f = fopenat("/usr/local/lib/faust", filename))) return f;
    if ((f = fopenat("/usr/lib/faust", filename))) return f;
    return 0;
}
#endif
