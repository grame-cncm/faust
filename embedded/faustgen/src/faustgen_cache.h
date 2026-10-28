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

#ifndef faustgen_cache__h
#define faustgen_cache__h

#include <string>
#include <vector>

//========================================================================
// Disk cache of the machine code compiled by faustgen~
//========================================================================
//
// The machine code compiled from a source with a list of options is kept on
// disk, shared by every faustgen~ object and every patch of the user: an
// object compiled once (an entry point chosen with -pn, an abstraction used
// several times, a patch reopened) is created again from its machine code,
// whether or not the patch containing it has been saved. Patches keep the
// source and the options only.
//
// - An entry is the file '<key>.fgcache' in the cache directory. The key,
//   given by the caller, identifies the compilation (faustgen~ and libfaust
//   versions, machine, target, source, options, library paths).
//
// - The entry also records the content (SHA1) of each library file the DSP
//   was compiled with (getLibraryList): a library changed or removed since
//   makes the entry stale, it is then removed and the source compiled again.
//
// - The cache directory is FAUSTGEN_CACHE_DIR if set, otherwise
//   ~/Library/Caches/faustgen~ on macOS, %LOCALAPPDATA%\faustgen~ on Windows,
//   ~/.cache/faustgen~ elsewhere. Its size is bounded (FAUSTGEN_CACHE_SIZE
//   in bytes, 512 MB by default): the entries used least recently are removed
//   first. An entry is written to a temporary file then renamed, so that a
//   reader never sees a partial one.

class faustgen_cache {

    public:

        // The cache directory, created if needed (empty if it cannot be)
        static std::string directory();

        // The machine code stored for 'key', if any and if the libraries it was
        // compiled with are unchanged; a stale or damaged entry is removed
        static bool read(const std::string& key, std::string& machine_code);

        // Store 'machine_code', compiled with the library files 'libraries', for 'key'
        static bool write(const std::string& key, const std::string& machine_code,
                          const std::vector<std::string>& libraries);

        // Remove every entry, return how many were removed
        static int clear();
};

#endif
