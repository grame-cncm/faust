#pragma once

#include <filesystem>
#include <Downloader.hh>

namespace fs = std::filesystem;

class PackageManager{

private:
    fs::path registryPath;
    std::string registryUrl;
    Downloader downloader;

    void config();

public:
    PackageManager();

    void install(std::string url, char** buffer);

    std::string install(std::string pkgUrl);

};