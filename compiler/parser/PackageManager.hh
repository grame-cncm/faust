#pragma once

#include <filesystem>
#include <Downloader.hh>

namespace fs = std::filesystem;

class PackageManager{

private:
    fs::path registryPath;
    std::string registryUrl;
    std::string branch;
    Downloader downloader;

    void config();

    std::string registryUrlTransform(std::string& url);

public:
    PackageManager();

    void install(std::string url, char** buffer);

    std::string install(std::string pkgUrl);

};