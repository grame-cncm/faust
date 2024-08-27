/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2024 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

/************************************************************************
 * @author Shehab Khaled (Shehab299@outlook.com)
 ***********************************************************************/

#include "PkgUrl.hh"
#include <regex>
#include "exception.hh"

using namespace std;

PkgUrl::PkgUrl(const string& url)
{
    parse(url);
}

void PkgUrl::parse(const string& url)
{
    using namespace regex_constants;

    regex pattern(
        "^pkg:faust(?:/([_a-zA-Z]\\w*))?/"
        "([_a-zA-Z]\\w*.lib)@((?:\\d+)(?:\\.(?:\\d+)(?:\\.(?:\\d+))?)?)$",
        icase | ECMAScript);

    smatch locater_parts;

    if (!regex_search(url, locater_parts, pattern)) {
        throw faustexception("ERROR : package URL is not valid");
    }

    author  = locater_parts[1].str();
    libName = locater_parts[2].str();
    version = locater_parts[3].str();
}

string PkgUrl::getAuthor() const
{
    return author;
}

bool PkgUrl::isPKgUrl(const string& url)
{
    using namespace regex_constants;

    regex pattern(
        "^pkg:faust(?:/([_a-zA-Z]\\w*))?/"
        "([_a-zA-Z]\\w*.lib)@((?:\\d+)(?:\\.(?:\\d+)(?:\\.(?:\\d+))?)?)$",
        icase | ECMAScript);

    return regex_search(url, pattern);
}

string PkgUrl::getLibraryName() const
{
    return libName;
}

string PkgUrl::getVersion() const
{
    return version;
}

string PkgUrl::getPath() const
{
    string path = "";

    if (!author.empty()) {
        path += author + "/";
    }

    path += libName + "/";
    path += version + "/";
    path += libName;

    return path;
}
