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

#include "PackageManager.hh"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include "Downloader.hh"
#include "PkgUrl.hh"
#include "exception.hh"
#include "url.hpp"

using namespace std;

namespace fs = std::filesystem;

#ifdef _WIN32
#include <windows.h>
#define setenv(name, value, overwrite) _putenv_s(name, value)
#endif

// Define default registry paths based on the operating system
#if defined(_WIN32) || defined(_WIN64)
#define DEFAULT_REGISTRY_PATH (filesystem::path(getenv("APPDATA")) / "Faust" / "Registry")
#define DEFAULT_HOME_PATH (filesystem::path(getenv("USERPROFILE")))
#elif defined(__APPLE__) && defined(__MACH__)
#define DEFAULT_REGISTRY_PATH \
    (filesystem::path(getenv("HOME")) / "Library" / "Faust" / "Registry")
#else
#define DEFAULT_REGISTRY_PATH (filesystem::path(getenv("HOME")) / ".faust" / "Registry")
#endif

#define DEFAULT_REGISTRY_URL "https://github.com/grame-cncm/faustregistry"
#define DEFAULT_BRANCH "main";

PackageManager::PackageManager()
{
    config();
}

string PackageManager::registryUrlTransform(const string& url)
{
    Url u(url);

    try {
        if (u.host() == "github.com") {
            u.scheme("https");
            u.host("raw.githubusercontent.com");
            u.path(u.path() + "/" + fBranch);
        }
    } catch (const exception& e) {
        throw faustexception("The Registry Url Provided Is Not Valid");
    }

    return u.str();
}

void PackageManager::config()
{
    char* registryPathAux = getenv("FAUST_REGISTRY_PATH");
    char* registryUrlAux  = getenv("FAUST_REGISTRY_URL");
    char* branchAux       = getenv("FAUST_REGISTRY_BRANCH");

    if (!registryPathAux) {
        fRegistryPath = DEFAULT_REGISTRY_PATH;
        string registry_path_str = fRegistryPath.string();
        setenv("FAUST_REGISTRY_PATH", registry_path_str.c_str(), 1);
    } else {
        fRegistryPath = fs::path(registryPathAux);
    }

    if (!registryUrlAux) {
        fRegistryUrl = DEFAULT_REGISTRY_URL;
        string registry_url_str = fRegistryPath.string();
        setenv("FAUST_REGISTRY_URL", registry_url_str.c_str(), 1);
    } else {
        fRegistryUrl = registryUrlAux;
    }

    if (!branchAux) {
        fBranch = DEFAULT_BRANCH;
        string branch_str = fRegistryPath.string();
        setenv("FAUST_REGISTRY_BRANCH", branch_str.c_str(), 1);
    } else {
        fBranch = branchAux;
    }
}

void PackageManager::install(const string& url, char** buffer)
{
    fDownloader.download(url, buffer);
}

string PackageManager::install(const string& pkgUrl)
{
    PkgUrl pkg(pkgUrl);

    fs::path    path;
    fs::path    pkgPath = path = fRegistryPath / pkg.getPath();
    string remoteUrl    = registryUrlTransform(fRegistryUrl) + "/" + pkg.getPath();

    if (fs::exists(pkgPath)) {
        return pkgPath.string();
    }

    fs::create_directories(pkgPath.parent_path());

    try {
        fDownloader.download(remoteUrl, pkgPath.string());
    } catch (const faustexception& e) {
        stringstream error;
        error << "ERROR : couldn't download library " << pkg.getLibraryName() << " of version "
              << pkg.getVersion() << " by author " << pkg.getAuthor() << endl;

        pkgPath = pkgPath.parent_path();
        while (fs::is_empty(pkgPath) && fs::exists(pkgPath)) {
            fs::remove(pkgPath);
            pkgPath = pkgPath.parent_path();
        }

        throw faustexception(error.str());
    }

    return path.string();
}
