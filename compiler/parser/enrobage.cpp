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
#include <vector>
#include <set>
#include <string>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include "compatibility.hh"
#include <climits>

extern string gFaustSuperSuperDirectory;
extern string gFaustSuperDirectory;
extern string gFaustDirectory;
extern string gMasterDirectory;
extern string gClassName;
extern bool	  gInlineArchSwitch;

//----------------------------------------------------------------


/**
 * Returns true is a line is blank (contains only white caracters)
 */
static bool isBlank(const string& s) {
    for (size_t i=0; i<s.size(); i++) {
        if (s[i] != ' ' && s[i] != '\t') return false;
    }
    return true;
}


/**
 * Replace every occurrence of oldstr by newstr inside str. str is modified
 * and returned as reference for convenience
 */
static string& replaceOccurences(string& str, const string& oldstr, const string& newstr)
{
    string::size_type l1 = oldstr.length();
    string::size_type l2 = newstr.length();

    string::size_type pos = str.find(oldstr);
    while ( pos != string::npos) {
        str.replace(pos, l1, newstr);
        pos = str.find(oldstr, pos + l2);
    }
    return str;
}


/**
 * Used when copying architecture files to replace default mydsp
 * class name with the user specified one
 */
static string& replaceClassName(string& str)
{
    return replaceOccurences(str, "mydsp", gClassName);
}


/**
 * Copy or remove license header. Architecture files can contain a header specifying
 * the license. If this header contains an exception tag (for example "FAUST COMPILER EXCEPTION")
 * it is an indication for the compiler to remove the license header from the resulting code. 
 * A header is the first non blank line that begins a comment.
 */
void streamCopyLicense(istream& src, ostream& dst, const string& exceptiontag)
{
    string          s;
    vector<string>	H;

    // skip blank lines
    while (getline(src,s) && isBlank(s)) dst << s << endl;

    // first non blank should start a comment
    if (s.find("/*")==string::npos) { dst << s << endl; return; }

    // copy the header into H
    bool remove = false;
    H.push_back(s);

    while (getline(src,s) && s.find("*/")==string::npos) {
        H.push_back(s);
        if (s.find(exceptiontag) != string::npos) remove=true;
    }

    // copy the header unless explicitely granted to remove it
    if (!remove) {
        // copy the header
        for (unsigned int i=0; i<H.size(); i++) {
            dst << H[i] << endl;
        }
        dst << s << endl;
    }
}



/**
 * A minimalistic parser used to recognize '#include <faust/...>' patterns when copying
 * architecture files 
 */
class myparser
{
    string  str;
    size_t  N;
    size_t  p;
public:
    myparser(const string& s) : str(s), N(s.length()), p(0) {}
    bool skip()                 { while ( p<N && isspace(str[p]) ) p++; return true; }
    bool parse(const string& s)   { bool f; if ((f = (p == str.find(s, p)))) p += s.length(); return f; }
    bool filename(string& fname) {
        size_t saved = p;
        if (p<N) {
            char c = str[p++];
            if (c== '<' | c=='"') {
                fname = "";
                while ( p<N && (str[p] != '>') && (str[p] != '"')) fname += str[p++];
                p++;
                return true;
            }
        }
        p = saved;
        return false;
    }
};


/**
 * True if string s match '#include <faust/fname>'
 */
bool isFaustInclude(const string& s, string& fname)
{
    myparser P(s);
    if ( P.skip() && P.parse("#include") && P.skip() && P.filename(fname) ) {
        myparser Q(fname);
        return Q.parse("faust/");
    } else {
        return false;
    }
}




/**
 * Inject file fname into dst ostream if not already done
 */

// to keep track of already injected files
set<string> alreadyIncluded;

void inject(ostream& dst, const string fname)
{
    if (alreadyIncluded.find(fname) == alreadyIncluded.end()) {
        alreadyIncluded.insert(fname);
        istream* src = open_arch_stream( fname.c_str());
        if (src) {
            streamCopy(*src, dst);
        } else {
            cerr << "NOT FOUND " << fname << endl;
        }
    }
}

/**
 * Copy src to dst until specific line.
 */
void streamCopyUntil(istream& src, ostream& dst, const string& until)
{
    string	s;
    string  fname;
    while ( getline(src,s) && (s != until) ) {
        if (gInlineArchSwitch && isFaustInclude(s, fname)) {
            inject(dst, fname);
        } else {
            dst << replaceClassName(s) << endl;
        }
    }
}

/**
 * Copy src to dst.
 */
void streamCopy(istream& src, ostream& dst)
{ 
    streamCopyUntil(src, dst, "<<<FOBIDDEN LINE IN A FAUST ARCHITECTURE FILE>>>");
}

/**
 * Copy src to dst until end
 */
void streamCopyUntilEnd(istream& src, ostream& dst)
{ 
    streamCopyUntil(src, dst, "<<<FOBIDDEN LINE IN A FAUST ARCHITECTURE FILE>>>");
}


/**
 * Try to open an architecture file searching in various directories
 */
ifstream* open_arch_stream(const char* filename)
{
	char	buffer[FAUST_PATH_MAX];
    char*	old = getcwd (buffer, FAUST_PATH_MAX);
	int		err;

    {
	    ifstream* f = new ifstream();
	    f->open(filename, ifstream::in); if (f->is_open()) return f; else delete f;
    }
    char *envpath = getenv("FAUST_LIB_PATH");
    if (envpath!=NULL) {
		if (chdir(envpath)==0) {
			ifstream* f = new ifstream();
			f->open(filename, ifstream::in);
			if (f->is_open()) return f; else delete f;
		}
    }
	err = chdir(old);
	if ( (chdir(gFaustDirectory.c_str())==0) && (chdir("architecture")==0) ) {
		//cout << "enrobage.cpp : 'architecture' directory found in gFaustDirectory" << endl;
        ifstream* f = new ifstream();
		f->open(filename, ifstream::in);
		if (f->good()) return f; else delete f;
	}
    err = chdir(old);
    if ((chdir(gFaustSuperDirectory.c_str())==0) && (chdir("architecture")==0) ) {
        //cout << "enrobage.cpp : 'architecture' directory found in gFaustSuperDirectory" << endl;
        ifstream* f = new ifstream();
        f->open(filename, ifstream::in);
        if (f->good()) return f; else delete f;
    }
    err = chdir(old);
	if ((chdir(gFaustSuperSuperDirectory.c_str())==0) && (chdir("architecture")==0) ) {
        //cout << "enrobage.cpp : 'architecture' directory found in gFaustSuperSuperDirectory" << endl;
        ifstream* f = new ifstream();
		f->open(filename, ifstream::in);
		if (f->good()) return f; else delete f;
	}
#ifdef INSTALL_PREFIX
	err = chdir(old);
	if (chdir(INSTALL_PREFIX "/lib/faust")==0) {
        ifstream* f = new ifstream();
		f->open(filename); 
		if (f->good()) return f; else delete f;
	}
    err = chdir(old);
    if (chdir(INSTALL_PREFIX "/include")==0) {
        ifstream* f = new ifstream();
        f->open(filename);
        if (f->good()) return f; else delete f;
    }
#endif
	err = chdir(old);
	if (chdir("/usr/local/lib/faust")==0) {
        ifstream* f = new ifstream();
		f->open(filename); 
		if (f->good()) return f; else delete f;
	}
    err = chdir(old);
    if (chdir("/usr/lib/faust")==0) {
        ifstream* f = new ifstream();
        f->open(filename);
        if (f->good()) return f; else delete f;
    }
    err = chdir(old);
    if (chdir("/usr/local/include")==0) {
        ifstream* f = new ifstream();
        f->open(filename);
        if (f->good()) return f; else delete f;
    }
    err = chdir(old);
    if (chdir("/usr/include")==0) {
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
 * Try to open the file '<dir>/<filename>'. If it succeed, it stores the full pathname
 * of the file into <fullpath>
 */
static FILE* fopenat(string& fullpath, const char* dir, const char* filename)
{
	int 		err; 
    char        olddirbuffer[FAUST_PATH_MAX];
    char        newdirbuffer[FAUST_PATH_MAX];
    
    char* 		olddir = getcwd (olddirbuffer, FAUST_PATH_MAX);

    if (chdir(dir) == 0) {           
        FILE* f = fopen(filename, "r");
		fullpath = getcwd (newdirbuffer, FAUST_PATH_MAX);
		fullpath += '/';
		fullpath += filename;
        err = chdir(olddir);
        return f;
    }
    err = chdir(olddir);
    return 0;
}

/**
 * Try to open the file '<dir>/<filename>'. If it succeed, it stores the full pathname
 * of the file into <fullpath>
 */
static FILE* fopenat(string& fullpath, const string& dir, const char* filename)
{
    return fopenat(fullpath, dir.c_str(), filename);
}

/**
 * Try to open the file '<dir>/<path>/<filename>'. If it succeed, it stores the full pathname
 * of the file into <fullpath>
 */
static FILE* fopenat(string& fullpath, const string& dir, const char* path, const char* filename)
{
	int			err;
    char        olddirbuffer[FAUST_PATH_MAX];
    char        newdirbuffer[FAUST_PATH_MAX];
    
    char* 		olddir = getcwd (olddirbuffer, FAUST_PATH_MAX);
    if (chdir(dir.c_str()) == 0) {
        if (chdir(path) == 0) {            
            FILE* f = fopen(filename, "r");
			fullpath = getcwd (newdirbuffer, FAUST_PATH_MAX);
			fullpath += '/';
			fullpath += filename;
            err = chdir(olddir);
            return f;
        }
    }
    err = chdir(olddir);
    return 0;
}



/**
 * Test absolute pathname.
 */
static bool isAbsolutePathname(const string& filename)
{
	//test windows absolute pathname "x:xxxxxx"
	if (filename.size()>1 && filename[1] == ':') return true;

	// test unix absolute pathname "/xxxxxx"
	if (filename.size()>0 && filename[0] == '/') return true;

	return false;
}


/**
 * Build a full pathname of <filename>.
 * <fullpath> = <currentdir>/<filename>
 */
static void buildFullPathname(string& fullpath, const char* filename)
{
	char	old[FAUST_PATH_MAX];

	if (isAbsolutePathname(filename)) {
		fullpath = filename;
	} else {
		fullpath = getcwd (old, FAUST_PATH_MAX);
		fullpath += '/';
		fullpath += filename;
	}
}

/**
 * Try to open the file <filename> searching in various directories. If succesful
 *  place its full pathname in the string <fullpath>
 */

#ifdef WIN32
FILE* fopensearch(const char* filename, string& fullpath)
{   
    FILE* f;
    char* envpath;

    if ((f = fopen(filename, "r"))) { 
    	buildFullPathname(fullpath, filename); 
    	return f;
    }
    if ((f = fopenat(fullpath, gMasterDirectory, filename))) { 
    	return f;
    }
    if ((envpath = getenv("FAUST_LIB_PATH")) && (f = fopenat(fullpath, envpath, filename))) {
        return f;
    }
    if ((f = fopenat(fullpath, gFaustDirectory, "architecture", filename))) { 
    	return f;
    }
    if ((f = fopenat(fullpath, gFaustSuperDirectory, "architecture", filename))) { 
    	return f;
    }
    if ((f = fopenat(fullpath, gFaustSuperSuperDirectory, "architecture", filename))) { 
    	return f;
    }
    return 0;
}
#else
FILE* fopensearch(const char* filename, string& fullpath)
{   
    FILE* f;
    char* envpath;

    if ((f = fopen(filename, "r"))) { 
    	buildFullPathname(fullpath, filename); 
    	return f;
    }
    if ((f = fopenat(fullpath, gMasterDirectory, filename))) { 
    	return f;
    }
    if ((envpath = getenv("FAUST_LIB_PATH")) && (f = fopenat(fullpath, envpath, filename))) {
		return f;
    }
    if ((f = fopenat(fullpath, gFaustDirectory, "architecture", filename))) { 
    	return f;
    }
    if ((f = fopenat(fullpath, gFaustSuperDirectory, "architecture", filename))) { 
    	return f;
    }
    if ((f = fopenat(fullpath, gFaustSuperSuperDirectory, "architecture", filename))) { 
    	return f;
    }
#ifdef INSTALL_PREFIX
    if ((f = fopenat(fullpath, INSTALL_PREFIX "/lib/faust", filename))) { 
    	return f;
    }
#endif
    if ((f = fopenat(fullpath, "/usr/local/lib/faust", filename))) { 
    	return f;
    }
    if ((f = fopenat(fullpath, "/usr/lib/faust", filename))) { 
    	return f;
    }
    return 0;
}
#endif


/** 
 * filebasename returns the basename of a path.
 * (adapted by kb from basename.c)
 *
 * @param[in]	The path to parse.
 * @return		The last component of the given path.
 */
#ifndef DIR_SEPARATOR
#define DIR_SEPARATOR '/'
#endif

#ifdef WIN32
#define HAVE_DOS_BASED_FILE_SYSTEM
#ifndef DIR_SEPARATOR_2 
#define DIR_SEPARATOR_2 '\\'
#endif
#endif

/* Define IS_DIR_SEPARATOR.  */
#ifndef DIR_SEPARATOR_2
# define IS_DIR_SEPARATOR(ch) ((ch) == DIR_SEPARATOR)
#else /* DIR_SEPARATOR_2 */
# define IS_DIR_SEPARATOR(ch) \
(((ch) == DIR_SEPARATOR) || ((ch) == DIR_SEPARATOR_2))
#endif /* DIR_SEPARATOR_2 */


/**
 * returns a pointer on the basename part of name
 */
const char* filebasename(const char* name)
{
#if defined (HAVE_DOS_BASED_FILE_SYSTEM)
	/* Skip over the disk name in MSDOS pathnames. */
	if (isalpha(name[0]) && name[1] == ':') 
		name += 2;
#endif

	const char* base;
	for (base = name; *name; name++)
    {
		if (IS_DIR_SEPARATOR (*name))
		{
			base = name + 1;
		}
    }
	return base;
}


/**
 * returns a string containing the dirname of name
 * If no dirname, returns "."
 */
string filedirname(const string& name)
{
    const char*         base = filebasename(name.c_str());
    const unsigned int  size = base-name.c_str();
    string              dirname;

    if (size==0) {
        dirname += '.';

    } else if (size==1) {
        dirname += name[0];

    } else {
        for (unsigned int i=0; i<size-1; i++) {
            dirname += name[i];
        }
    }
    return dirname;
}
