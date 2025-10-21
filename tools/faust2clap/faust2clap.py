#!/usr/bin/env python3

#####################################################################
#                                                                   #
#                        faust2clap generator                       #
#               (c) GRAME & Facundo Franchino, 2025                 #
#                                                                   #
#####################################################################   

"""
faust2clap.py

A tool that generates CLAP (CLever Audio Plugin) format plugins from Faust DSP code.
It compiles Faust .dsp files into fully functional CLAP plugins that can be loaded
in any CLAP-compatible DAW.

Created by Facundo Franchino, early Summer 2025
"""

import sys #cli arguments
import os #file path manipulation
import subprocess #run shell commands
import json
import re
import argparse
import shutil
import hashlib
import platform

#config
ARCH_REL_PATH="architecture/clap/clap-arch.cpp"
OUTPUT_ROOT="build"

#cache and SDK paths
def get_cache_dir():
    """Get user-specific cache directory for faust2clap builds"""
    home = os.path.expanduser("~")
    if platform.system() == "Darwin":
        return os.path.join(home, "Library", "Caches", "faust", "faust2clap")
    elif platform.system() == "Linux":
        return os.path.join(home, ".cache", "faust", "faust2clap")
    elif platform.system() == "Windows":
        return os.path.join(home, "AppData", "Local", "faust", "faust2clap")
    else:
        return os.path.join(home, ".cache", "faust", "faust2clap")

def get_faust_version():
    """Get Faust version for cache versioning"""
    try:
        result = subprocess.check_output(["faust", "--version"], universal_newlines=True)
        # extract version from output
        match = re.search(r'Version\s+([\d\.]+)', result)
        return match.group(1) if match else "unknown"
    except:
        return "unknown"

#parse command line arguments properly
parser = argparse.ArgumentParser(description='faust2clap - Generate CLAP plugins from Faust DSP code')
parser.add_argument('dsp_file', help='Input .dsp file')
parser.add_argument('-nvoices', type=int, default=16, help='Number of polyphonic voices (default: 16)')
parser.add_argument('-mono', action='store_true', help='Generate monophonic plugin instead of polyphonic')
parser.add_argument('-poly', action='store_true', help='Generate polyphonic plugin (default behaviour)')

args = parser.parse_args()

dsp_path = args.dsp_file #full path to the provided .dsp file
nvoices = args.nvoices
# note: is_polyphonic will be set later based on auto-detection or user override
if not os.path.isfile(dsp_path):
    print(f"[!] dsp file not found: {dsp_path}")
    sys.exit(1)

base=os.path.splitext(os.path.basename(dsp_path))[0] #name minus extension (.dsp)
out_cpp=f"{base}_clap.cpp" #target outpu filename

#locate arch file using faust command
this_dir=os.path.dirname(os.path.abspath(__file__))

# try to get architecture directory from faust itself 
arch_path = None
faust_root = None

try:
    # use faust --archdir to get the architecture directory
    arch_dir = subprocess.check_output(["faust", "--archdir"], universal_newlines=True).strip()
    # faust --archdir returns /path/to/share/faust, so we need /path/to/share/faust/clap/clap-arch.cpp
    arch_path_from_faust = os.path.join(arch_dir, "clap/clap-arch.cpp")
    if os.path.isfile(arch_path_from_faust):
        arch_path = arch_path_from_faust
        # get faust root from libdir for CMake builds
        faust_root = subprocess.check_output(["faust", "--libdir"], universal_newlines=True).strip()
    # if faust --archdir doesn't have CLAP files, keep arch_path as None to try fallbacks
except (subprocess.CalledProcessError, FileNotFoundError):
    # faust command not available or failed
    pass

# fallback: try other possible locations
if not arch_path:
    # check both installed and development locations for CLAP arch file
    possible_paths = [
        # relative to script location (development setup)
        os.path.join(this_dir, "../..", ARCH_REL_PATH),
        # system installation paths (installed via CMake)
        os.path.join(this_dir, "../../clap/clap-arch.cpp"),  # installed location
        # check FAUST_LIB environment variable
        os.path.join(os.environ.get("FAUST_LIB", ""), ARCH_REL_PATH) if os.environ.get("FAUST_LIB") else "",
        os.path.join(os.environ.get("FAUST_LIB", ""), "clap/clap-arch.cpp") if os.environ.get("FAUST_LIB") else "",
        # system-wide fallbacks (both patterns)
        f"/usr/local/share/faust/{ARCH_REL_PATH}",  # development pattern
        f"/usr/local/share/faust/clap/clap-arch.cpp",  # installed pattern
        f"/usr/share/faust/{ARCH_REL_PATH}",
        f"/usr/share/faust/clap/clap-arch.cpp",
        f"/opt/homebrew/share/faust/{ARCH_REL_PATH}",
        f"/opt/homebrew/share/faust/clap/clap-arch.cpp",
    ]
    
    for path in possible_paths:
        if path and os.path.isfile(path):
            arch_path = path
            # determine faust_root based on which path worked
            if "share/faust" in path:
                faust_root = path.split("share/faust")[0] + "share/faust"
            elif os.environ.get("FAUST_LIB"):
                faust_root = os.environ.get("FAUST_LIB")
            else:
                faust_root = os.path.abspath(os.path.join(os.path.dirname(path), "../.."))
            break

if not arch_path:
    print(f"[!] Architecture file not found: {ARCH_REL_PATH}")
    print("[!] Your Faust installation doesn't include CLAP support yet.")
    print("[!] CLAP support is being added - it will be available in the next Faust release.")
    print("[!] Current solutions:")
    print("[!]   - Build and run from the Faust source directory with CLAP support")
    print("[!]   - Or set FAUST_LIB environment variable to point to faust sources with CLAP")
    print(f"[!]   - faust --archdir reports: {subprocess.check_output(['faust', '--archdir'], universal_newlines=True).strip()}")
    sys.exit(1)

#create output directory in current working directory (like other faust2* tools)
output_dir = os.path.join(os.getcwd(), OUTPUT_ROOT, base)
os.makedirs(output_dir, exist_ok=True)
out_cpp_path=os.path.join(output_dir,out_cpp)

#extract metadata from the .dsp using faust -json
def extract_metadata(dsp_path):
    try:
        json_output = subprocess.check_output(["faust", "-json", dsp_path], universal_newlines=True)
        parsed = json.loads(json_output)
        meta_entries = parsed.get("meta", []) or parsed.get("ui", [{}])[0].get("meta", [])
        metadata = {}
        for entry in meta_entries:
            metadata.update(entry)
        return metadata
    except (subprocess.CalledProcessError, json.JSONDecodeError, Exception) as e:
        print(f"[i] JSON metadata not available, falling back to C++ parsing.")

    #final fallback: parse -lang cpp output for m->declare("...", "...")
    try:
        cpp_output = subprocess.check_output(["faust", "-lang", "cpp", dsp_path], universal_newlines=True)
        metadata = {}
        for line in cpp_output.splitlines():
            if 'm->declare' in line:
                match = re.search(r'm->declare\("([^"]+)",\s*"([^"]+)"\)', line)
                if match:
                    key, value = match.groups()
                    metadata[key] = value
        return metadata
    except Exception as e:
        print(f"[!] failed to fallback-parse cpp metadata: {e}")
        return {}

metadata = extract_metadata(dsp_path)

#auto-detect if DSP is an effect or instrument
def detect_dsp_type(dsp_path, metadata):
    """
    Detect if DSP is an effect or instrument based on:
    1. If it has 'effect' in metadata
    2. If it has audio inputs (effects process audio, instruments generate it)
    3. Common naming patterns
    """
    #check metadata for explicit type
    if 'effect' in metadata:
        return 'effect'
    if 'instrument' in metadata or 'synth' in metadata:
        return 'instrument'
    
    #check DSP name patterns
    dsp_name = os.path.basename(dsp_path).lower()
    effect_keywords = ['reverb', 'delay', 'filter', 'eq', 'compress', 'distort', 'phaser', 
                      'flanger', 'chorus', 'echo', 'pitch', 'gate', 'limiter', 'expand']
    instrument_keywords = ['synth', 'organ', 'piano', 'drum', 'bass', 'lead', 'pad', 
                          'string', 'brass', 'voice', 'osc', 'vco', 'sawtooth']
    
    for keyword in effect_keywords:
        if keyword in dsp_name:
            print(f"[i] Detected as EFFECT based on name containing '{keyword}'")
            return 'effect'
    
    for keyword in instrument_keywords:
        if keyword in dsp_name:
            print(f"[i] Detected as INSTRUMENT based on name containing '{keyword}'")
            return 'instrument'
    
    #check if DSP has inputs by parsing the generated C++
    try:
        cpp_output = subprocess.check_output(["faust", "-lang", "cpp", dsp_path], universal_newlines=True)
        #look for getNumInputs function
        if 'getNumInputs' in cpp_output:
            #extract the return value
            match = re.search(r'int\s+getNumInputs\(\)\s*{\s*return\s+(\d+);', cpp_output)
            if match:
                num_inputs = int(match.group(1))
                if num_inputs > 0:
                    print(f"[i] Detected as EFFECT (has {num_inputs} audio inputs)")
                    return 'effect'
                else:
                    print(f"[i] Detected as INSTRUMENT (has no audio inputs)")
                    return 'instrument'
    except:
        pass
    
    #default to effect for safety (effects work for both cases)
    print(f"[i] Defaulting to EFFECT mode")
    return 'effect'

dsp_type = detect_dsp_type(dsp_path, metadata)

#override with user preference if specified
if args.mono:
    is_polyphonic = False
    print(f"[i] User forced MONO mode")
elif args.poly:
    is_polyphonic = True
    print(f"[i] User forced POLY mode")
else:
    #auto-detect based on DSP type
    is_polyphonic = (dsp_type == 'instrument')

#fallback values
plugin_id = f"org.faust.{base.lower()}"
plugin_name = metadata.get("name", base)
plugin_vendor = metadata.get("author", "faust")
plugin_version = metadata.get("version", "1.0.0")
plugin_description = metadata.get("description", f"Plugin generated from {base}.dsp")

#generate plugin_metadata.h
metadata_header_path = os.path.join(output_dir, "plugin_metadata.h")
print(f"[i] Add this to your CMakeLists.txt:")
print(f'    include_directories("{output_dir}")')
with open(metadata_header_path, "w") as f:
    f.write(f'#define FAUST_PLUGIN_ID "{plugin_id}"\n')
    f.write(f'#define FAUST_PLUGIN_NAME "{plugin_name}"\n')
    f.write(f'#define FAUST_PLUGIN_VENDOR "{plugin_vendor}"\n')
    f.write(f'#define FAUST_PLUGIN_VERSION "{plugin_version}"\n')
    f.write(f'#define FAUST_PLUGIN_DESCRIPTION "{plugin_description}"\n')
    f.write(f'#define FAUST_NVOICES {nvoices}\n')
    f.write(f'#define FAUST_IS_POLYPHONIC {"1" if is_polyphonic else "0"}\n')

print("[*] extracted metadata:")
print(f"    id:          {plugin_id}")
print(f"    name:        {plugin_name}")
print(f"    vendor:      {plugin_vendor}")
print(f"    version:     {plugin_version}")
print(f"    description: {plugin_description}")
print(f"    polyphonic:  {is_polyphonic}")
print(f"    voices:      {nvoices}")


#run faust to generate the plugin source file
try:
    subprocess.run(["faust", "-a", arch_path, dsp_path, "-o", out_cpp_path], check=True)
    print(f"[✓] generated: {out_cpp_path}")
except subprocess.CalledProcessError:
    print("[!] faust compilation failed.")
    sys.exit(1)

# detect environment and setup build system
def detect_faust_sdk():
    """Detect if we're in development or system installation and find SDK components"""
    
    # check for development environment (has external dependencies)
    dev_clap_sdk = os.path.join(this_dir, "../../external/clap-sdk")
    dev_clap_helpers = os.path.join(this_dir, "../../external/clap-helpers")
    
    if os.path.isdir(dev_clap_sdk) and os.path.isdir(dev_clap_helpers):
        return {
            'type': 'development',
            'clap_sdk': dev_clap_sdk,
            'clap_helpers': dev_clap_helpers,
            'faust_lib': os.path.join(this_dir, "../.."),
            'cmake_template': os.path.join(this_dir, "CMakeLists.txt"),
            'plugin_template': os.path.join(this_dir, "lib/plugin.cc"),
            'gui_glue': os.path.join(this_dir, "lib/faust_gui_glue.cpp"),
            'plist_template': os.path.join(this_dir, "cmake/generic.plist.in")
        }
    
    # check for system installation SDK
    # try multiple system paths where SDK might be installed
    system_paths = [
        "/usr/local/share/faust/tools/faust2clap",
        "/usr/share/faust/tools/faust2clap",
        "/opt/homebrew/share/faust/tools/faust2clap"
    ]
    
    # also try based on current script location
    if "/share/faust/tools/faust2clap" in this_dir:
        system_paths.insert(0, this_dir)
    
    for base_path in system_paths:
        if os.path.isdir(base_path):
            sdk_path = os.path.join(base_path, "sdk")
            if os.path.isdir(sdk_path):
                return {
                    'type': 'system',
                    'clap_sdk': os.path.join(sdk_path, "clap-sdk"),
                    'clap_helpers': os.path.join(sdk_path, "clap-helpers"),
                    'faust_lib': faust_root,
                    'cmake_template': os.path.join(sdk_path, "CMakeLists.txt"),
                    'plugin_template': os.path.join(sdk_path, "plugin.cc"),
                    'gui_glue': os.path.join(sdk_path, "faust_gui_glue.cpp"),
                    'plist_template': os.path.join(sdk_path, "generic.plist.in")
                }
    
    # fallback: try to use current development setup even if incomplete
    return {
        'type': 'fallback',
        'clap_sdk': dev_clap_sdk,
        'clap_helpers': dev_clap_helpers,
        'faust_lib': os.path.join(this_dir, "../.."),
        'cmake_template': os.path.join(this_dir, "CMakeLists.txt"),
        'plugin_template': os.path.join(this_dir, "lib/plugin.cc"),
        'gui_glue': os.path.join(this_dir, "lib/faust_gui_glue.cpp"),
        'plist_template': os.path.join(this_dir, "cmake/generic.plist.in")
    }

def setup_build_environment(sdk_info, base_name):
    """Setup user-writable build environment in cache directory"""
    
    # create cache directory structure
    cache_base = get_cache_dir()
    faust_version = get_faust_version()
    platform_name = platform.system().lower()
    
    cache_dir = os.path.join(cache_base, faust_version, platform_name)
    build_dir = os.path.join(cache_dir, "build", base_name)
    
    # create directories
    os.makedirs(build_dir, exist_ok=True)
    os.makedirs(os.path.join(cache_dir, "sdk"), exist_ok=True)
    
    # copy SDK files to cache if needed (for system installations)
    sdk_cache_dir = os.path.join(cache_dir, "sdk")
    
    if sdk_info['type'] == 'system':
        # copy SDK files to cache for out-of-tree builds
        for name, path in sdk_info.items():
            if name.startswith('clap_') and os.path.isdir(path):
                cache_path = os.path.join(sdk_cache_dir, os.path.basename(path))
                if not os.path.exists(cache_path):
                    print(f"[i] Copying {name} to cache...")
                    shutil.copytree(path, cache_path)
                sdk_info[name] = cache_path
            elif name.endswith('_template') and os.path.isfile(path):
                cache_path = os.path.join(sdk_cache_dir, os.path.basename(path))
                if not os.path.exists(cache_path):
                    shutil.copy2(path, cache_path)
                sdk_info[name] = cache_path
    
    return build_dir, sdk_info

def generate_cmake_content(sdk_info, plugin_name, cpp_path, metadata_path):
    """Generate CMakeLists.txt content for out-of-tree builds"""
    
    return f"""# Generated CMakeLists.txt for {plugin_name} CLAP plugin
# Auto-generated by faust2clap - do not edit manually

cmake_minimum_required(VERSION 3.15)
project({plugin_name}_clap LANGUAGES C CXX)

# C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# macOS deployment target
if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.11" CACHE STRING "macOS target")
endif()

# Find RtMidi library
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(RTMIDI rtmidi)
endif()

# Fallback to common system locations if pkg-config fails
if(NOT RTMIDI_FOUND)
    find_library(RTMIDI_LIBRARY 
        NAMES rtmidi librtmidi librtmidi.7 librtmidi.6 librtmidi.5
        PATHS 
            /opt/homebrew/lib
            /opt/homebrew/Cellar/rtmidi/*/lib
            /usr/local/lib 
            /usr/lib
        PATH_SUFFIXES lib
    )
    find_path(RTMIDI_INCLUDE_DIR 
        NAMES RtMidi.h rtmidi/RtMidi.h
        PATHS 
            /opt/homebrew/include
            /opt/homebrew/Cellar/rtmidi/*/include
            /usr/local/include 
            /usr/include
        PATH_SUFFIXES include
    )
    
    if(RTMIDI_LIBRARY AND RTMIDI_INCLUDE_DIR)
        set(RTMIDI_FOUND TRUE)
        set(RTMIDI_LIBRARIES "${{RTMIDI_LIBRARY}}")
        set(RTMIDI_INCLUDE_DIRS "${{RTMIDI_INCLUDE_DIR}}")
    endif()
endif()

if(NOT RTMIDI_FOUND)
    message(WARNING "RtMidi not found. MIDI support will be limited.")
    set(RTMIDI_LIBRARIES "")
    set(RTMIDI_INCLUDE_DIRS "")
endif()

# Include CLAP SDK and helpers
add_subdirectory("{sdk_info['clap_sdk']}" clap-sdk)
add_subdirectory("{sdk_info['clap_helpers']}" clap-helpers)

# Build GUI glue library
add_library(faust_gui_glue STATIC "{sdk_info['gui_glue']}")
target_include_directories(faust_gui_glue PRIVATE
    "{sdk_info['faust_lib']}/architecture"
    "{sdk_info['faust_lib']}/architecture/faust/gui"
)

# Main plugin target
add_library({plugin_name} MODULE "{os.path.basename(cpp_path)}")

# Add plugin implementation
target_sources({plugin_name} PRIVATE "{sdk_info['plugin_template']}")

# Include directories
target_include_directories({plugin_name} PRIVATE
    "${{CMAKE_CURRENT_SOURCE_DIR}}"
    "{sdk_info['faust_lib']}/architecture"
    "{sdk_info['faust_lib']}/architecture/faust/gui"
    "{sdk_info['faust_lib']}/architecture/faust/midi"
    "{sdk_info['faust_lib']}/architecture/faust/dsp"
    "{sdk_info['clap_helpers']}/include"
    "{sdk_info['clap_sdk']}/include"
    ${{RTMIDI_INCLUDE_DIRS}}
)

# Link libraries  
target_link_libraries({plugin_name} PRIVATE
    clap
    clap-helpers
    faust_gui_glue
)

# Add RtMidi if found
if(RTMIDI_FOUND)
    if(RTMIDI_LDFLAGS)
        # Use LDFLAGS for complete linking setup (includes -L and -l flags)
        target_link_options({plugin_name} PRIVATE ${{RTMIDI_LDFLAGS}})
    else()
        # Use LIBRARIES and LIBRARY_DIRS separately
        target_link_directories({plugin_name} PRIVATE ${{RTMIDI_LIBRARY_DIRS}})
        target_link_libraries({plugin_name} PRIVATE ${{RTMIDI_LIBRARIES}})
    endif()
endif()

# macOS bundle properties
if(APPLE)
    set_target_properties({plugin_name} PROPERTIES
        OUTPUT_NAME {plugin_name}
        BUNDLE TRUE
        BUNDLE_EXTENSION clap
        MACOSX_BUNDLE_GUI_IDENTIFIER org.faust.{plugin_name}
        MACOSX_BUNDLE_BUNDLE_NAME {plugin_name}
        MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
    )
    
    # Generate Info.plist if template exists
    if(EXISTS "{sdk_info.get('plist_template', '')}")
        configure_file(
            "{sdk_info['plist_template']}"
            "${{CMAKE_CURRENT_BINARY_DIR}}/{plugin_name}.plist"
            @ONLY
        )
        set_target_properties({plugin_name} PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST "${{CMAKE_CURRENT_BINARY_DIR}}/{plugin_name}.plist"
        )
    endif()
endif()
"""

# detect SDK and setup build environment
sdk_info = detect_faust_sdk()
print(f"[i] Detected {sdk_info['type']} environment")

# check if we can actually build
can_build = False
if sdk_info['type'] != 'fallback':
    #verify all required components exist
    required_components = ['clap_sdk', 'clap_helpers', 'cmake_template', 'plugin_template']
    missing = [comp for comp in required_components if not os.path.exists(sdk_info[comp])]
    
    if missing:
        print(f"[!] Missing SDK components: {missing}")
        can_build = False
    else:
        can_build = True
else:
    print("[!] Incomplete SDK installation detected")

if can_build:
    # setup build environment in user cache
    try:
        build_dir, updated_sdk_info = setup_build_environment(sdk_info, base)
        
        print("[*] Setting up build environment in user cache")
        print(f"[i] Build directory: {build_dir}")
        
        # generate CMakeLists.txt in build directory
        cmake_content = generate_cmake_content(updated_sdk_info, base, out_cpp_path, metadata_header_path)
        cmake_path = os.path.join(build_dir, "CMakeLists.txt")
        
        with open(cmake_path, "w") as f:
            f.write(cmake_content)
        
        # copy necessary files to build directory
        shutil.copy2(out_cpp_path, build_dir)
        shutil.copy2(metadata_header_path, build_dir)
        
        print("[*] Running cmake build")
        
        # platform-specific build setup
        cmake_args = [
            "cmake", "-S", build_dir, "-B", os.path.join(build_dir, "_build")
        ]
        
        if platform.system() == "Darwin":
            try:
                sdk_path = subprocess.check_output(["xcrun", "--sdk", "macosx", "--show-sdk-path"], universal_newlines=True).strip()
                cmake_args.append(f"-DCMAKE_OSX_SYSROOT={sdk_path}")
            except:
                pass  # continue without SDK path if xcrun fails
        
        subprocess.run(cmake_args, check=True, capture_output=True)
        subprocess.run(["cmake", "--build", os.path.join(build_dir, "_build")], check=True, capture_output=True)
        
        # copy built plugin to output location
        if platform.system() == "Darwin":
            built_plugin = os.path.join(build_dir, "_build", f"{base}.clap")
            if os.path.exists(built_plugin):
                # copy to system plugin directory
                system_plugin_dir = os.path.expanduser("~/Library/Audio/Plug-Ins/CLAP")
                os.makedirs(system_plugin_dir, exist_ok=True)
                final_plugin_path = os.path.join(system_plugin_dir, f"{base}.clap")
                if os.path.exists(final_plugin_path):
                    shutil.rmtree(final_plugin_path)
                shutil.copytree(built_plugin, final_plugin_path)
                print(f"[✓] Plugin installed: {final_plugin_path}")
        
        print("[✓] Build completed successfully.")
        
    except subprocess.CalledProcessError as e:
        print("[!] cmake build failed.")
        print(f"[stderr]\n{e.stderr.decode() if e.stderr else 'No stderr'}")
        print(f"[stdout]\n{e.stdout.decode() if e.stdout else 'No stdout'}")
        sys.exit(1)
    except Exception as e:
        print(f"[!] Build setup failed: {e}")
        sys.exit(1)
else:
    # cannot build, provide helpful instructions
    print("[i] C++ generation completed")
    print("")
    if sdk_info['type'] == 'fallback':
        print("⚠️  Incomplete faust2clap installation detected")
        print("")
        print("To build CLAP plugins, you need:")
        print("  1. A complete Faust installation with CLAP support")
        print("  2. CLAP SDK and helper libraries")
        print("")
        print("Solutions:")
        print("  • Install Faust from source:")
        print("    git clone https://github.com/grame-cncm/faust")
        print("    cd faust")
        print("    make && sudo make install")
        print("")
        print("  • Or run from development environment:")
        print(f"    cd faust/tools/faust2clap && ./faust2clap {dsp_path}")
    else:
        print("To complete the build manually:")
        print(f"  1. Copy generated files to a build environment")
        print(f"  2. Compile with CLAP SDK and helper libraries")
    print("")
    print(f"Generated files:")
    print(f"  C++ source: {out_cpp_path}")
    print(f"  Metadata:   {metadata_header_path}")