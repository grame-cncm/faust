/************************************************************************
 FAUST Architecture File
 Copyright (C) 2012-2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************
 ************************************************************************/

#include "faustgen_cache.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <map>
#include <mutex>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef WIN32
#include <direct.h>
#include <process.h>
#include <sys/utime.h>
#include <windows.h>
#define getpid _getpid
#else
#include <dirent.h>
#include <unistd.h>
#include <utime.h>
#endif

#include <faust/dsp/libfaust.h>  // generateSHA1

using namespace std;

static const char* kHeader = "faustgen~ cache 1";
static const char* kExtension = ".fgcache";
static const long long kDefaultSize = 512LL * 1024 * 1024;

#ifdef WIN32
static const char kSeparator = '\\';
#else
static const char kSeparator = '/';
#endif

// An entry on disk, for the eviction
struct CacheEntry {
    string fPath;
    long long fSize;
    long long fTime;
};

// Create 'path' and its missing parents
static bool make_directories(const string& path)
{
    for (size_t i = 1; i <= path.size(); i++) {
        if (i == path.size() || path[i] == '/' || path[i] == '\\') {
            string prefix = path.substr(0, i);
            struct stat info;
            if (stat(prefix.c_str(), &info) == 0) {
                if (!(info.st_mode & S_IFDIR)) return false;
                continue;
            }
        #ifdef WIN32
            if (_mkdir(prefix.c_str()) != 0) return false;
        #else
            if (mkdir(prefix.c_str(), 0755) != 0) return false;
        #endif
        }
    }
    return true;
}

// The cache directory, without its final separator
static string cache_root()
{
    const char* dir = getenv("FAUSTGEN_CACHE_DIR");
    if (dir && dir[0]) {
        string res = dir;
        while (res.size() > 1 && (res.back() == '/' || res.back() == '\\')) res.pop_back();
        return res;
    }
#if defined(WIN32)
    const char* base = getenv("LOCALAPPDATA");
    return (base && base[0]) ? string(base) + "\\faustgen~" : "";
#elif defined(__APPLE__)
    const char* home = getenv("HOME");
    return (home && home[0]) ? string(home) + "/Library/Caches/faustgen~" : "";
#else
    const char* xdg = getenv("XDG_CACHE_HOME");
    if (xdg && xdg[0]) return string(xdg) + "/faustgen~";
    const char* home = getenv("HOME");
    return (home && home[0]) ? string(home) + "/.cache/faustgen~" : "";
#endif
}

string faustgen_cache::directory()
{
    string root = cache_root();
    if (root.empty() || !make_directories(root)) {
        return "";
    }
    return root + kSeparator;
}

// A key names a file: only letters and digits (the caller gives a SHA1)
static bool valid_key(const string& key)
{
    if (key.empty()) return false;
    for (char c : key) {
        if (!isalnum(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

static bool read_file(const string& path, string& content)
{
    ifstream in(path.c_str(), ios::in | ios::binary);
    if (!in) return false;
    stringstream buffer;
    buffer << in.rdbuf();
    content = buffer.str();
    return !in.bad();
}

// The SHA1 of the content of a library file, or "" if it cannot be read. Computed again
// only when the file changes (size, modification time), since all the objects of a
// patch check the same libraries
static string library_sha1(const string& path)
{
    static mutex lock;
    static map<string, pair<pair<long long, long long>, string>> known;
    struct stat info;
    if (stat(path.c_str(), &info) != 0) return "";
    pair<long long, long long> stamp(static_cast<long long>(info.st_size), static_cast<long long>(info.st_mtime));
    {
        lock_guard<mutex> guard(lock);
        auto it = known.find(path);
        if (it != known.end() && it->second.first == stamp) return it->second.second;
    }
    string content;
    if (!read_file(path, content)) return "";
    string sha = generateSHA1(content);
    lock_guard<mutex> guard(lock);
    known[path] = make_pair(stamp, sha);
    return sha;
}

// Mark an entry as used now, for the eviction
static void touch(const string& path)
{
#ifdef WIN32
    _utime(path.c_str(), nullptr);
#else
    utime(path.c_str(), nullptr);
#endif
}

bool faustgen_cache::read(const string& key, string& machine_code)
{
    string dir = directory();
    if (dir.empty() || !valid_key(key)) return false;
    string path = dir + key + kExtension;
    string content;
    if (!read_file(path, content)) return false;

    // "faustgen~ cache 1", then "library <sha1> <path>" lines, then "machinecode <size>" and the code
    istringstream in(content);
    string line;
    bool valid = getline(in, line) && (line == kHeader);
    long long size = -1;
    while (valid && getline(in, line)) {
        if (line.compare(0, 8, "library ") == 0) {
            size_t space = line.find(' ', 8);
            if (space == string::npos || library_sha1(line.substr(space + 1)) != line.substr(8, space - 8)) {
                valid = false;  // a library changed or disappeared since the compilation
            }
        } else if (line.compare(0, 12, "machinecode ") == 0) {
            size = atoll(line.c_str() + 12);
            break;
        } else {
            valid = false;
        }
    }
    streamoff start = in.tellg();
    if (!valid || size < 0 || start < 0 || static_cast<long long>(content.size()) - start != size) {
        remove(path.c_str());
        return false;
    }
    machine_code = content.substr(static_cast<size_t>(start));
    touch(path);
    return true;
}

// The entries of the cache directory
static vector<CacheEntry> list_entries(const string& dir)
{
    vector<CacheEntry> entries;
    const size_t extension = strlen(kExtension);
#ifdef WIN32
    WIN32_FIND_DATAA data;
    HANDLE find = FindFirstFileA((dir + "*" + kExtension).c_str(), &data);
    if (find == INVALID_HANDLE_VALUE) return entries;
    do {
        string name = data.cFileName;
#else
    DIR* folder = opendir(dir.c_str());
    if (!folder) return entries;
    while (struct dirent* item = readdir(folder)) {
        string name = item->d_name;
#endif
        if (name.size() > extension && name.compare(name.size() - extension, extension, kExtension) == 0) {
            struct stat info;
            string path = dir + name;
            if (stat(path.c_str(), &info) == 0) {
                entries.push_back({path, static_cast<long long>(info.st_size), static_cast<long long>(info.st_mtime)});
            }
        }
#ifdef WIN32
    } while (FindNextFileA(find, &data));
    FindClose(find);
#else
    }
    closedir(folder);
#endif
    return entries;
}

// Remove the entries used least recently while the cache is larger than its bound
static void evict(const string& dir)
{
    const char* bound = getenv("FAUSTGEN_CACHE_SIZE");
    long long limit = (bound && bound[0]) ? atoll(bound) : kDefaultSize;
    vector<CacheEntry> entries = list_entries(dir);
    long long total = 0;
    for (const auto& entry : entries) total += entry.fSize;
    sort(entries.begin(), entries.end(),
         [](const CacheEntry& a, const CacheEntry& b) { return a.fTime < b.fTime; });
    for (const auto& entry : entries) {
        if (total <= limit) break;
        if (remove(entry.fPath.c_str()) == 0) total -= entry.fSize;
    }
}

bool faustgen_cache::write(const string& key, const string& machine_code, const vector<string>& libraries)
{
    string dir = directory();
    if (dir.empty() || !valid_key(key)) return false;

    ostringstream content;
    content << kHeader << "\n";
    for (const auto& library : libraries) {
        string sha = library_sha1(library);
        if (sha.empty()) return false;  // a library that cannot be read cannot be checked later
        content << "library " << sha << " " << library << "\n";
    }
    content << "machinecode " << machine_code.size() << "\n" << machine_code;

    // Written aside then renamed, so that a reader never sees a partial entry
    static int counter = 0;
    string path = dir + key + kExtension;
    string temporary = path + ".tmp" + to_string(getpid()) + "-" + to_string(counter++);
    {
        ofstream out(temporary.c_str(), ios::out | ios::binary | ios::trunc);
        out << content.str();
        out.close();
        if (!out) {
            remove(temporary.c_str());
            return false;
        }
    }
#ifdef WIN32
    bool renamed = MoveFileExA(temporary.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING) != 0;
#else
    bool renamed = rename(temporary.c_str(), path.c_str()) == 0;
#endif
    if (!renamed) {
        remove(temporary.c_str());
        return false;
    }
    evict(dir);
    return true;
}

int faustgen_cache::clear()
{
    string dir = directory();
    if (dir.empty()) return 0;
    int removed = 0;
    for (const auto& entry : list_entries(dir)) {
        removed += (remove(entry.fPath.c_str()) == 0);
    }
    return removed;
}
