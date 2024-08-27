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

#ifndef EMCC
#include <curl/curl.h>
#endif

class Downloader {
   private:
#ifndef EMCC
    CURL*         handle;
    static size_t write_data_file(void* ptr, size_t size, size_t nmemb, void* userData);
    static size_t write_data(void* ptr, size_t size, size_t nmemb, void* userData);
#endif

   public:
    Downloader();
    ~Downloader();

    void download(const std::string& url, const std::string& savePath);
    void download(const std::string& url, char** buffer);
};
