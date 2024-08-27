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
            u.path(u.path() + "/" + branch);
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
        registryPath = DEFAULT_REGISTRY_PATH;
        setenv("FAUST_REGISTRY_PATH", registryPath.c_str(), 1);
    } else {
        registryPath = fs::path(registryPathAux);
    }

    if (!registryUrlAux) {
        registryUrl = DEFAULT_REGISTRY_URL;
        setenv("FAUST_REGISTRY_URL", registryUrl.c_str(), 1);
    } else {
        registryUrl = registryUrlAux;
    }

    if (!branchAux) {
        branch = DEFAULT_BRANCH;
        setenv("FAUST_REGISTRY_BRANCH", branch.c_str(), 1);
    } else {
        branch = branchAux;
    }
}

void PackageManager::install(const string& url, char** buffer)
{
    downloader.download(url, buffer);
}

string PackageManager::install(const string& pkgUrl)
{
    PkgUrl pkg(pkgUrl);

    fs::path    path;
    fs::path    pkgPath = path = registryPath / pkg.getPath();
    string remoteUrl    = registryUrlTransform(registryUrl) + "/" + pkg.getPath();

    if (fs::exists(pkgPath)) {
        return pkgPath.string();
    }

    fs::create_directories(pkgPath.parent_path());

    try {
        downloader.download(remoteUrl, pkgPath.string());
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
