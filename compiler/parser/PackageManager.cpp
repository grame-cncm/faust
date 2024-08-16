#include "PackageManager.hh"
#include <cstdlib>
#include <iostream>
#include <filesystem>
#include "PkgUrl.hh"
#include "Downloader.hh"
#include "../errors/exception.hh"
#include "../utils/url.hpp"


namespace fs = std::filesystem;

#ifdef _WIN32
#include <windows.h>
#define setenv(name, value, overwrite) _putenv_s(name, value)
#endif

// Define default registry paths based on the operating system
#if defined(_WIN32) || defined(_WIN64)
    #define DEFAULT_REGISTRY_PATH (std::filesystem::path(std::getenv("APPDATA")) / "Faust" / "Registry")
    #define DEFAULT_HOME_PATH (std::filesystem::path(std::getenv("USERPROFILE")))
#elif defined(__APPLE__) && defined(__MACH__)
    #define DEFAULT_REGISTRY_PATH (std::filesystem::path(std::getenv("HOME")) / "Library" / "Faust" / "Registry")
#else
    #define DEFAULT_REGISTRY_PATH (std::filesystem::path(std::getenv("HOME")) / ".faust" / "Registry")
#endif


#define DEFAULT_REGISTRY_URL "https://github.com/shehab299/Registry"
#define DEFAULT_BRANCH "main";


PackageManager::PackageManager(){
    config();
}

std::string PackageManager::registryUrlTransform(std::string& url){

    Url u(url);

    try
    {
        if(u.host() == "github.com"){
            u.scheme("https");
            u.host("raw.githubusercontent.com");
            u.path(u.path() + "/" + this->branch);
        }
    }
    catch(const std::exception& e)
    {
        throw faustexception("The Registry Url Provided Is Not Valid");
    }

    return u.str();
}


void PackageManager::config()
{
    char* registryPath = getenv("FAUST_REGISTRY_PATH");
    char* registryUrl = getenv("FAUST_REGISTRY_URL");
    char* branch = getenv("FAUST_REGISTRY_BRANCH");

    if(!registryPath)
    {
        this->registryPath = DEFAULT_REGISTRY_PATH;
        setenv("FAUST_REGISTRY_PATH", this->registryPath.c_str(), 1);
    }
    else
    {
        this->registryPath = fs::path(registryPath);
    }

    if(!registryUrl)
    {
        this->registryUrl =  DEFAULT_REGISTRY_URL;
        setenv("FAUST_REGISTRY_URL", this->registryUrl.c_str(), 1);
    }
    else
    {
        this->registryUrl = registryUrl;
    }

    if(!branch)
    {
        this->branch = DEFAULT_BRANCH;
        setenv("FAUST_REGISTRY_BRANCH", this->branch.c_str(), 1);
    }
    else
    {
        this->branch = branch;
    }

}

    
void PackageManager::install(std::string url, char** buffer){
    downloader.download(url,buffer);
}

std::string PackageManager::install(std::string pkgUrl){

    PkgUrl pkg(pkgUrl);

    fs::path path;
    fs::path pkgPath = path = this->registryPath / pkg.getPath();
    std::string remoteUrl = registryUrlTransform(this->registryUrl) + "/" + pkg.getPath();      

    if(fs::exists(pkgPath)){
        return pkgPath.string();
    }

    fs::create_directories(pkgPath.parent_path());

    try{
        downloader.download(remoteUrl, pkgPath.string());
    }
    catch(const faustexception& e){

        std::cerr << "Couldn't download library " 
                  << pkg.getLibraryName() 
                  << " of version " 
                  << pkg.getVersion()
                  << " by author "
                  << pkg.getAuthor() 
                  << std::endl;

        pkgPath = pkgPath.parent_path();
    
        while(fs::is_empty(pkgPath) && fs::exists(pkgPath)){
            fs::remove(pkgPath);
            pkgPath = pkgPath.parent_path();
        }

        throw e;
    }
    
    return path.string();
}
