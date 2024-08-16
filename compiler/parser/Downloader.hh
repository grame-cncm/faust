#pragma once
#include <string>

#ifndef EMCC
#include <curl/curl.h>
#endif

class Downloader{

private:

#ifndef EMCC
    CURL* handle;

    static size_t write_data_file(void* ptr, size_t size, size_t nmemb, void* userData);

    static size_t write_data(void* ptr, size_t size, size_t nmemb, void* userData);
#endif

public:
    Downloader();

    void download(const std::string url,const std::string& savePath);

    void download(const std::string url,char** buffer);

    ~Downloader();
};