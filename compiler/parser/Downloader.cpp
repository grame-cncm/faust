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

#include "Downloader.hh"
#include "exception.hh"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#ifndef EMCC
#include <curl/curl.h>

using namespace std;

inline string lower(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

size_t Downloader::write_data_file(void* ptr, size_t size, size_t nmemb, void* userData)
{
    ofstream* file = static_cast<ofstream*>(userData);
    if (!file->is_open()) {
        throw faustexception("ERROR : couldn't download package");
    }

    file->write(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

size_t Downloader::write_data(void* ptr, size_t size, size_t nmemb, void* userData)
{
    string* data = static_cast<string*>(userData);
    data->append(static_cast<char*>(ptr), size * nmemb);

    return size * nmemb;
}

void Downloader::download(const string& url, const string& savePath)
{
    ofstream file(savePath, ios::binary);
    locale loc;

    if (!file.is_open()) {
        throw faustexception("ERROR : can't open file: " + savePath);
    }

    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &Downloader::write_data_file);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &file);

    CURLcode res = curl_easy_perform(handle);
    file.close();

    if (res != CURLE_OK) {
        filesystem::remove(savePath);
        string str = string(curl_easy_strerror(res));
        throw faustexception("ERROR : download failed : " + lower(str) + "\n");
    }

    long http_code = 0;
    curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &http_code);

    if (to_string(http_code)[0] != '2') {
        filesystem::remove(savePath);
        throw faustexception("ERROR : unsuccessful download : HTTP code " +
                             to_string(http_code) + "\n");
    }
}

void Downloader::download(const string& url, char** buffer)
{
    string data;
    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &Downloader::write_data);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &data);

    CURLcode res = curl_easy_perform(handle);

    if (res != CURLE_OK) {
        string str = string(curl_easy_strerror(res));
        throw faustexception("ERROR : download failed : " + lower(str) + "\n");
    }

    long http_code = 0;
    curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &http_code);

    if (to_string(http_code)[0] != '2') {
        throw faustexception("ERROR : unsuccessful download : HTTP code " +
                             to_string(http_code) + "\n");
    }

    *buffer = new char[data.size() + 1];
    copy(data.begin(), data.end(), *buffer);
    (*buffer)[data.size()] = '\0';
}

Downloader::Downloader()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    handle = curl_easy_init();
}

Downloader::~Downloader()
{
    curl_easy_cleanup(handle);
    curl_global_cleanup();
}

#endif

#ifdef EMCC

#include <emscripten.h>

Downloader::Downloader()
{
}

Downloader::~Downloader()
{
}

EM_JS(char*, downloadFile, (const char* url), {
    var dsp_code = "";

    try {
        if (typeof window != = 'undefined' && typeof window.XMLHttpRequest != = 'undefined') {
            var xhr = new window.XMLHttpRequest();
            xhr.open('GET', UTF8ToString(url), false);
            xhr.send(null);

            if (xhr.status >= 200 && xhr.status < 300) {
                dsp_code = xhr.responseText;
            }
        } else if (typeof process != 'undefined' && process.versions != null &&
                   process.versions.node != null) {
            var XMLHttpRequest = require('xmlhttprequest').XMLHttpRequest;
            var xhr            = new XMLHttpRequest();
            xhr.open('GET', UTF8ToString(url), false);
            xhr.send(null);
            if (xhr.status >= 200 && xhr.status < 300) {
                dsp_code = xhr.responseText;
            }
        }
    } catch (error) {
        console.log('Error:', error);
    }

    return allocate(intArrayFromString(dsp_code), ALLOC_STACK);
});

void Downloader::download(const string& url, const string& savePath)
{
    ofstream file(savePath, ios::binary);

    if (!file.is_open()) {
        throw faustexception("ERROR : can't open file : " + savePath);
    }

    char* buffer = (char*)downloadFile(url.c_str());

    if (strlen(buffer) == 0) {
        filesystem::remove(savePath);
        throw faustexception("ERROR : couldn't download file : " + url);
    }

    try {
        file << buffer;
        file.close();
    } catch (const exception& e) {
        filesystem::remove(savePath);
        throw faustexception("ERROR : couldn't download file : " + url);
    }
}

void Downloader::download(const string& url, char** buffer)
{
    *buffer = (char*)downloadFile(url.c_str());

    if (strlen(*buffer) == 0) {
        stringstream error;
        error << "ERROR : unable to access URL '" << url << "'" << endl;
        throw faustexception(error.str());
    }
}

#endif
