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
#include <list>
#include <set>
#include <string>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include "compatibility.hh"
#include "garbageable.hh"
#include "global.hh"
#include "sourcefetcher.hh"
#include "exception.hh"
#include <errno.h>
#include <climits>
#include <iostream>
#include <sstream>

//----------------------------------------------------------------

/**
 * Returns true is a line is blank (contains only white caracters)
 */
static bool isBlank(const string& s)
{
    for (size_t i = 0; i < s.size(); i++) {
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
    while (pos != string::npos) {
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
    return replaceOccurences(str, "mydsp", gGlobal->gClassName);
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
    if (s.find("/*") == string::npos) { dst << s << endl; return; }
    
    // copy the header into H
    bool remove = false;
    H.push_back(s);
    
    while (getline(src,s) && s.find("*/") == string::npos) {
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
class myparser : public virtual Garbageable
{
    
    private:
        string  str;
        size_t  N;
        size_t  p;
        
    public:
        myparser(const string& s) : str(s), N(s.length()), p(0) {}
        bool skip()                 { while (p < N && isspace(str[p])) p++; return true; }
        bool parse(const string& s) { bool f; if ((f = (p == str.find(s, p)))) p += s.length(); return f; }
        bool filename(string& fname)
        {
            size_t saved = p;
            if (p<N) {
                char c = str[p++];
                if (c == '<' | c == '"') {
                    fname = "";
                    while (p<N && (str[p] != '>') && (str[p] != '"')) fname += str[p++];
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
static bool isFaustInclude(const string& s, string& fname)
{
    myparser P(s);
    if (P.skip() && P.parse("#include") && P.skip() && P.filename(fname)) {
        myparser Q(fname);
        return Q.parse("faust/");
    } else {
        return false;
    }
}

/**
 * Inject file fname into dst ostream
 */
static void inject(ostream& dst, const string& fname)
{
    if (gGlobal->gAlreadyIncluded.find(fname) == gGlobal->gAlreadyIncluded.end()) {
        gGlobal->gAlreadyIncluded.insert(fname);
        istream* src = openArchStream(fname.c_str());
        if (src) {
            streamCopy(*src, dst);
            delete src;
        } else {
            stringstream error;
            error << fname << " not found\n";
            gGlobal->gErrorMsg = error.str();
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
        if (gGlobal->gInlineArchSwitch && isFaustInclude(s, fname)) {
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
    streamCopyUntil(src, dst, "<<<FORBIDDEN LINE IN A FAUST ARCHITECTURE FILE>>>");
}

/**
 * Copy src to dst until end
 */
void streamCopyUntilEnd(istream& src, ostream& dst)
{
    streamCopyUntil(src, dst, "<<<FORBIDDEN LINE IN A FAUST ARCHITECTURE FILE>>>");
}

#define TRY_OPEN(filename)                      \
    ifstream* f = new ifstream();               \
    f->open(filename, ifstream::in);            \
    err = chdir(old);                           \
    if (f->is_open()) return f; else delete f;  \

/**
 * Try to open an architecture file searching in various directories
 */
ifstream* openArchStream(const char* filename)
{
    char	buffer[FAUST_PATH_MAX];
    char*	old = getcwd(buffer, FAUST_PATH_MAX);
    int		err;
    
    TRY_OPEN(filename);
    for (string dirname : gGlobal->gArchitectureDirList) {
        if ((err = chdir(dirname.c_str()))==0) {
            TRY_OPEN(filename);
        }
    }
    
    return 0;
}

const char* stripStart(const char* filename)
{
    const char* start;
#ifdef _WIN32
    start = "file:///";
#else
    start = "file://";
#endif
    if (strstr(filename, start)) {
        return &filename[strlen(start)];
    }  else {
        return filename;
    }
}

/**
 * Check if an URL exists.
 * @return true if the URL exist, throw on exception otherwise
 */

static bool checkFile(const char* filename)
{
    // Otherwise tries to open as a regular file
    FILE* f = fopen(filename, "r");
    if (f) {
        fclose(f);
        return true;
    } else {
        stringstream error;
        error << "ERROR : cannot open file '" << filename << "' : " << strerror(errno) << endl;
        throw faustexception(error.str());
    }
}

bool checkURL(const char* filename)
{
    char* fileBuf = 0;
    
    // Tries to open as an URL for a local file
    if (strstr(filename, "file://") != 0) {
        // Tries to open as a regular file after removing 'file://'
        return checkFile(&filename[7]);
    // Tries to open as a http URL
    } else if ((strstr(filename, "http://") != 0) || (strstr(filename, "https://") != 0)) {
        if (http_fetch(filename, &fileBuf) != -1) {
            return true;
        } else {
            stringstream error;
            error << "ERROR : unable to access URL '" << filename << "' : " << http_strerror() << endl;
            throw faustexception(error.str());
        }
    } else {
        // Otherwise tries to open as a regular file
        return checkFile(filename);
    }
}

/**
 * Try to open the file '<dir>/<filename>'. If it succeed, it stores the full pathname
 * of the file into <fullpath>
 */
static FILE* fopenAt(string& fullpath, const char* dir, const char* filename)
{
    int err;
    char olddirbuffer[FAUST_PATH_MAX];
    char newdirbuffer[FAUST_PATH_MAX];

    char* olddir = getcwd(olddirbuffer, FAUST_PATH_MAX);

    if (chdir(dir) == 0) {
        FILE* f = fopen(filename, "r");
        char* newdir = getcwd(newdirbuffer, FAUST_PATH_MAX);
        if (!newdir) {
            fclose(f);
            stringstream error;
            error << "ERROR : getcwd '" << strerror(errno) << endl;
            throw faustexception(error.str());
        }
        fullpath = newdir;
        fullpath += '/';
        fullpath += filename;
        err = chdir(olddir);
        if (err != 0) {
            fclose(f);
            stringstream error;
            error << "ERROR : cannot change back directory to '" << olddir << "' : " << strerror(errno) << endl;
            throw faustexception(error.str());
        }
        return f;
    }
    err = chdir(olddir);
    if (err != 0) {
        stringstream error;
        error << "ERROR : cannot change back directory to '" << olddir << "' : " << strerror(errno) << endl;
        throw faustexception(error.str());
    }
    return 0;
}

/**
 * Try to open the file '<dir>/<filename>'. If it succeed, it stores the full pathname
 * of the file into <fullpath>
 */
static FILE* fopenAt(string& fullpath, const string& dir, const char* filename)
{
    return fopenAt(fullpath, dir.c_str(), filename);
}

/**
 * Test absolute pathname.
 */
static bool isAbsolutePathname(const string& filename)
{
	//test windows absolute pathname "x:xxxxxx"
	if (filename.size() > 1 && filename[1] == ':') return true;

	// test unix absolute pathname "/xxxxxx"
	if (filename.size() > 0 && filename[0] == '/') return true;

	return false;
}

/**
 * Build a full pathname of <filename>.
 * <fullpath> = <currentdir>/<filename>
 */
static void buildFullPathname(string& fullpath, const char* filename)
{
    char old[FAUST_PATH_MAX];
    
    if (isAbsolutePathname(filename)) {
        fullpath = filename;
    } else {
        char* newdir = getcwd(old, FAUST_PATH_MAX);
        if (!newdir) {
            stringstream error;
            error << "ERROR : getcwd '" << strerror(errno) << endl;
            throw faustexception(error.str());
        }
        fullpath = newdir;
        fullpath += '/';
        fullpath += filename;
    }
}

/**
 * Try to open the file <filename> searching in various directories. If succesful
 *  place its full pathname in the string <fullpath>
 */
FILE* fopenSearch(const char* filename, string& fullpath)
{
    FILE* f;
    
    if ((f = fopen(filename, "r"))) {
        buildFullPathname(fullpath, filename);
        return f;
    }
    
    // search file in user supplied directory path
    for (string dirname : gGlobal->gImportDirList) {
        if ((f = fopenAt(fullpath, dirname, filename))) {
            return f;
        }
    }
    return 0;
}

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

#ifdef _WIN32
#define HAVE_DOS_BASED_FILE_SYSTEM
#ifndef DIR_SEPARATOR_2
#define DIR_SEPARATOR_2 '\\'
#endif
#endif

/* Define IS_DIR_SEPARATOR.  */
#ifndef DIR_SEPARATOR_2
    #define IS_DIR_SEPARATOR(ch) ((ch) == DIR_SEPARATOR)
#else /* DIR_SEPARATOR_2 */
    #define IS_DIR_SEPARATOR(ch) \
    (((ch) == DIR_SEPARATOR) || ((ch) == DIR_SEPARATOR_2))
#endif /* DIR_SEPARATOR_2 */

/**
 * returns a pointer on the basename part of name
 */
const char* fileBasename(const char* name)
{
#if defined (HAVE_DOS_BASED_FILE_SYSTEM)
    /* Skip over the disk name in MSDOS pathnames. */
    if (isalpha(name[0]) && name[1] == ':')
        name += 2;
#endif
    const char* base;
    for (base = name; *name; name++) {
        if (IS_DIR_SEPARATOR(*name)) {
            base = name + 1;
        }
    }
    return base;
}

/**
 * returns a string containing the dirname of name
 * If no dirname, returns "."
 */
string fileDirname(const string& name)
{
    const char*         base = fileBasename(name.c_str());
    const unsigned int  size = (const unsigned int)(base-name.c_str());
    string              dirname;
    
    if (size == 0) {
        dirname += '.';
    } else if (size == 1) {
        dirname += name[0];
    } else {
        for (unsigned int i = 0; i < size-1; i++) {
            dirname += name[i];
        }
    }
    return dirname;
}

string stripEnd(const string& name, const string& ext)
{
    if (name.length() >= 4 && name.substr(name.length() - ext.length()) == ext) {
        return name.substr(0, name.length() - ext.length());
    } else {
        return name;
    }
}
