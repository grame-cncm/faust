#include "Downloader.hh"
#include "../errors/exception.hh"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>





#ifndef EMCC
#include <curl/curl.h>

size_t Downloader::write_data_file(void* ptr, size_t size, size_t nmemb, void* userData) {

    std::ofstream* file = static_cast<std::ofstream*>(userData);

    if (!file->is_open()) {
        throw faustexception("Internal Error: Couldn't Download Package");
    }

    file->write(static_cast<char*>(ptr), size * nmemb);

    return size * nmemb;
}

size_t Downloader::write_data(void* ptr, size_t size, size_t nmemb, void* userData) {

    std::string* data = static_cast<std::string*>(userData);
    data->append(static_cast<char*>(ptr), size * nmemb);

    return size * nmemb;
}



void Downloader::download(const std::string url,const std::string& savePath)
{

    std::ofstream file(savePath, std::ios::binary);

    if (!file.is_open()) {
        throw faustexception("Can't open file: " + savePath);
    }

    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &Downloader::write_data_file);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &file);

    CURLcode res = curl_easy_perform(handle);
    file.close();

    if (res != CURLE_OK) {
        std::filesystem::remove(savePath); 
        throw faustexception("Download failed: " + std::string(curl_easy_strerror(res)) + "\n");
    }

    long http_code = 0;
    curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &http_code);

    if (std::to_string(http_code)[0] != '2'){
        std::filesystem::remove(savePath);  
        throw faustexception("Unsuccessful download: HTTP code " + std::to_string(http_code) + "\n");
    }
}

void Downloader::download(const std::string url,char** buffer)
{
    std::string data;
    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &Downloader::write_data);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &data);

    CURLcode res = curl_easy_perform(handle);

    if (res != CURLE_OK) {
        throw faustexception("Download failed: " + std::string(curl_easy_strerror(res)) + "\n");
    }

    long http_code = 0;
    curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &http_code);

    if (std::to_string(http_code)[0] != '2'){
        throw faustexception("Unsuccessful download: HTTP code " + std::to_string(http_code) + "\n");
    }

    *buffer = new char[data.size() + 1];
    std::copy(data.begin(), data.end(), *buffer);
    (*buffer)[data.size()] = '\0';
}

Downloader::Downloader(){
    curl_global_init(CURL_GLOBAL_DEFAULT);
    handle = curl_easy_init();
}

Downloader::~Downloader(){
    curl_easy_cleanup(handle);
    curl_global_cleanup();   
}


#endif

#ifdef EMCC

#include <emscripten.h>

Downloader::Downloader(){
}

Downloader::~Downloader(){
}



EM_JS(char*, downloadFile, (const char* url), {
    var dsp_code = "";

    try {
        if (typeof window !== 'undefined' && typeof window.XMLHttpRequest !== 'undefined') {
            var xhr = new window.XMLHttpRequest();
            xhr.open('GET', UTF8ToString(url), false);
            xhr.send(null);

            if (xhr.status >= 200 && xhr.status < 300) {
                dsp_code = xhr.responseText;   
            } 
        } else if (typeof process != 'undefined'  && process.versions != null && process.versions.node != null) {
            var XMLHttpRequest = require('xmlhttprequest').XMLHttpRequest;
            var xhr = new XMLHttpRequest();
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





void Downloader::download(const std::string url,const std::string& savePath){

    std::ofstream file(savePath, std::ios::binary);

    if (!file.is_open()) {
        throw faustexception("Can't open file: " + savePath);
    }

    char* buffer = (char*) downloadFile(url.c_str());

    if(strlen(buffer) == 0){
        std::filesystem::remove(savePath); 
        throw faustexception("Couldn't download file: " + url);
    }

    try{
        file << buffer;
        file.close();
    }catch(const std::exception& e){
        std::filesystem::remove(savePath); 
        throw faustexception("Couldn't download file: " + url);
    }
}


void Downloader::download(const std::string url,char** buffer){

    *buffer = (char*) downloadFile(url.c_str());

    if(strlen(*buffer) == 0){
        std::stringstream error;
        error << "ERROR : unable to access URL '" << url << "'" << std::endl;
        throw faustexception(error.str());
    }
}
#endif



