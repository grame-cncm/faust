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

#pragma once

#include <string>

class PkgUrl {
   private:
    std::string version;
    std::string author;
    std::string libName;

    void parse(const std::string&);

   public:
    PkgUrl(const std::string&);

    std::string getVersion() const;
    std::string getAuthor() const;
    std::string getLibraryName() const;
    std::string getPath() const;

    static bool isPKgUrl(const std::string&);
};
