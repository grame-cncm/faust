#!/usr/bin/env python3

#####################################################################
#                                                                   #
#                        faust2clap                                 #
#                (c) Grame & Facundo Franchino, 2025                #
#                                                                   #
#####################################################################

import sys #cli arguments
import os #file path manipulation
import subprocess #run shell commands
import json
import re
import argparse 
import time
from pathlib import Path
import shutil

def generate_info_plist(app_name, identifier, version, executable_name):
    return f"""<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN"
  "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
  <dict>
    <key>CFBundlePackageType</key>
    <string>BNDL</string>
    <key>CFBundleExecutable</key>
    <string>{executable_name}</string>
    <key>CFBundleIdentifier</key>
    <string>{identifier}</string>
    <key>CFBundleName</key>
    <string>{app_name}</string>
    <key>CFBundleVersion</key>
    <string>{version}</string>
  </dict>
</plist>
"""

def get_dynamic_plugin_metadata():
        return {
            "app_name": "FaustDynamic",
            "identifier": "org.faust.dynamic",
            "version": "1.0.0",
            "executable_name": "FaustDynamic"
        }

def symlink_external(name, install_root):
    """Symlink an external/ dependency (clap-helpers or clap-sdk) into ~/.faust2clap."""
    source = (install_root / "external" / name).resolve()
    dest = Path.home() / ".faust2clap" / "external" / name

    if dest.exists():
        print(f"{CYAN}[*] {name} already exists at: {dest}{RESET}")
    else:
        try:
            print(f"{CYAN}[*] Symlinking {name} → {dest}{RESET}")
            dest.parent.mkdir(parents=True, exist_ok=True)
            dest.symlink_to(source)
        except Exception as e:
            print(f"{RED}[!] Failed to symlink {name}: {e}{RESET}")
            sys.exit(1)

# colours for terminal output
GREEN = "\033[92m"
RED = "\033[91m"
CYAN = "\033[96m"
YELLOW = "\033[93m"
RESET = "\033[0m"

def locate_clap_architecture_file():
    """Locate the clap-arch.cpp file used for generating plugins."""

    # try using `faust --archdir`
    try:
        archdir = subprocess.check_output(["faust", "--archdir"], universal_newlines=True).strip()
        candidate = Path(archdir) / "clap" / "clap-arch.cpp"
        if candidate.exists():
            return candidate.resolve()
    except Exception:
        pass

    # try FAUST_LIB env variable
    faust_lib = os.environ.get("FAUST_LIB")
    if faust_lib:
        candidate = Path(faust_lib) / "clap" / "clap-arch.cpp"
        if candidate.exists():
            return candidate.resolve()

    # fallback to bundled path relative to this script
    script_dir = Path(__file__).resolve().parent
    bundled = (script_dir / ".." / ".." / "architecture" / "clap" / "clap-arch.cpp").resolve()
    if bundled.exists():
        return bundled

    # try standard install locations
    fallback_paths = [
        "/usr/local/share/faust/architecture/clap/clap-arch.cpp",
        "/opt/homebrew/share/faust/architecture/clap/clap-arch.cpp",  # apple silicon
        "/usr/share/faust/architecture/clap/clap-arch.cpp",
    ]
    for path in fallback_paths:
        if Path(path).exists():
            return Path(path).resolve()
    # nothing worked — fail
    print(f"{RED}[!] Could not locate 'clap-arch.cpp' file.{RESET}")
    print(f"{RED}[!] Tried:{RESET}")
    print(f"    - faust --archdir")
    print(f"    - $FAUST_LIB/clap/clap-arch.cpp")
    print(f"    - bundled relative path near this script: {bundled}")
    for path in fallback_paths:
        print(f"    - {path}")
    sys.exit(1)

def locate_clap_dir():
    """Try to locate the architecture/clap directory."""

    # prefer FAUST_SRC if set
    faust_src = os.environ.get("FAUST_SRC")
    if faust_src:
        candidate = Path(faust_src) / "architecture" / "clap"
        if candidate.is_dir():
            return candidate.resolve()

    # try walking from the script location
    script_path = Path(__file__).resolve()
    for parent in script_path.parents:
        candidate = parent / "architecture" / "clap"
        if candidate.is_dir():
            return candidate.resolve()
    print(f"{RED}[!] Could not locate architecture/clap directory.{RESET}")
    print(f"{RED}[!] Tried:{RESET}")
    print(f"    - $FAUST_SRC")
    for path in fallback_paths:
        print(f"    {path}")
    print(f"{YELLOW}[i] If you're running from a global install, try setting FAUST_SRC to your Faust repo path.{RESET}")
    print(f"{CYAN}[*] Using clap_dir from: {clap_dir}{RESET}")
    sys.exit(1)

def build_dynamic_plugin(install=False):
    global clap_dir
    
    clap_dir = (
    Path(os.environ["FAUST_SRC"]) / "architecture" / "clap"
    if "FAUST_SRC" in os.environ
    else Path(os.path.dirname(__file__)) / "architecture" / "clap"
    )
    make_cmd = ["make", "-f", "Makefile.simple"]

    try:
        print(f"{CYAN}[*] Building dynamic plugin in: {clap_dir}{RESET}")
        subprocess.run(make_cmd, cwd=clap_dir, check=True)
        print(f"{GREEN}[✓] Built dynamic plugin{RESET}")

        if install:
        # create proper macOS bundle layout
            plugin_binary = clap_dir / "FaustDynamic.clap"
            bundle_dir = Path.home() / "Library" / "Audio" / "Plug-Ins" / "CLAP" / "FaustDynamic.clap"
            contents_dir = bundle_dir / "Contents" / "MacOS"
            plist_path = bundle_dir / "Contents" / "Info.plist"

            shutil.rmtree(bundle_dir, ignore_errors=True)

            # create directories
            contents_dir.mkdir(parents=True, exist_ok=True)

            # move binary
            shutil.copy2(plugin_binary, contents_dir / "FaustDynamic")

            # write Info.plist
            info = get_dynamic_plugin_metadata()
            plist_contents = generate_info_plist(
                app_name=info["app_name"],
                identifier=info["identifier"],
                version=info["version"],
                executable_name=info["executable_name"]
            )
            with open(plist_path, "w") as f:
                f.write(plist_contents)
            print(f"{GREEN}[✓] Info.plist written to: {plist_path}{RESET}")
            print(f"{GREEN}[✓] Bundled and installed dynamic plugin as .clap bundle{RESET}")
            print(f"{GREEN}[✓] Installed dynamic plugin{RESET}")
    except subprocess.CalledProcessError as e:
        print(f"{RED}[!] Error building dynamic plugin: {e}{RESET}")
        sys.exit(1)

def launch_hot_reload_gui():
    clap_dir = locate_clap_dir()
    gui_path = clap_dir / "faust-hot-reload.py"

    if not gui_path.exists():
        print(f"{RED}[!] GUI not found at: {gui_path}{RESET}")
        return
    try:
        subprocess.run(["python3", str(gui_path)])
    except Exception as e:
        print(f"{RED}[!] Error launching GUI: {e}{RESET}")

parser = argparse.ArgumentParser(
    description='faust2clap: Generate CLAP plugins from Faust DSP code - by Facundo Franchino',
    formatter_class=argparse.ArgumentDefaultsHelpFormatter
)
parser.add_argument('--version', action='version', version='faust2clap 1.0.0')
parser.add_argument('dsp_file', nargs='?', help='Input .dsp file')
parser.add_argument('-nvoices', type=int, default=16, help='Number of polyphonic voices (default: 16)')
parser.add_argument('-mono', action='store_true', help='Generate monophonic plugin instead of polyphonic')
parser.add_argument('-poly', action='store_true', help='Generate polyphonic plugin (default behaviour)')
parser.add_argument('--dry-run', action='store_true', help='Run without generating or building anything')
parser.add_argument('--dynamic', action='store_true', help='Build the dynamic plugin to load any .dsp file at run-time (interpreter-based)')
parser.add_argument('--install', action='store_true', help='Install the dynamic plugin after building it (requires --dynamic)')
parser.add_argument('--gui', action='store_true', help='Launch the hot-reload GUI (faust-hot-reload.py)')
args = parser.parse_args()

# dynamic mode
if args.dynamic:
    if args.dsp_file:
        print("[i] Ignoring DSP file, since --dynamic mode doesn't compile a specific file.")
    build_dynamic_plugin(install=args.install)
    if args.gui:
        launch_hot_reload_gui()
    sys.exit(0)

#GUI only 
if args.gui:
    launch_hot_reload_gui()
    sys.exit(0)

#check for .dsp file
if not args.dsp_file:
    print(f"{RED}[!] Error: No .dsp file provided.{RESET}")
    sys.exit(1)

dsp_path = os.path.abspath(args.dsp_file) #full path to the provided .dsp file
nvoices = args.nvoices
# Note: is_polyphonic will be set later based on auto-detection or user override
if not os.path.isfile(dsp_path):
    print(f"{RED}[!] dsp file not found: {dsp_path}{RESET}")
    sys.exit(1)

base=os.path.splitext(os.path.basename(dsp_path))[0] #name minus extension (.dsp)
out_cpp=f"{base}_clap.cpp" #target outpu filename

# try to get architecture directory from faust itself 
arch_path = str(locate_clap_architecture_file())

# we'll build everything in ./build/<plugin_name>
plugin_name = os.path.splitext(os.path.basename(args.dsp_file))[0]
output_dir = Path.cwd() / "build" / plugin_name

# make sure the output directory exists
os.makedirs(output_dir, exist_ok=True)
out_cpp_path = os.path.join(output_dir, out_cpp)

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
        print(f"{YELLOW}[i] JSON metadata not available, falling back to C++ parsing.{RESET}")

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
        print(f"{YELLOW}[!] failed to fallback-parse cpp metadata: {e}{RESET}")
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
print(f"{CYAN}[i] Add this to your CMakeLists.txt:{RESET}")
print(f'    include_directories("{output_dir}")')
with open(metadata_header_path, "w") as f:
    f.write(f'#define FAUST_PLUGIN_ID "{plugin_id}"\n')
    f.write(f'#define FAUST_PLUGIN_NAME "{plugin_name}"\n')
    f.write(f'#define FAUST_PLUGIN_VENDOR "{plugin_vendor}"\n')
    f.write(f'#define FAUST_PLUGIN_VERSION "{plugin_version}"\n')
    f.write(f'#define FAUST_PLUGIN_DESCRIPTION "{plugin_description}"\n')
    f.write(f'#define FAUST_NVOICES {nvoices}\n')
    f.write(f'#define FAUST_IS_POLYPHONIC {"1" if is_polyphonic else "0"}\n')

print(f"{CYAN}[*] extracted metadata:{RESET}")
print(f"    id:          {plugin_id}")
print(f"    name:        {plugin_name}")
print(f"    vendor:      {plugin_vendor}")
print(f"    version:     {plugin_version}")
print(f"    description: {plugin_description}")
print(f"    polyphonic:  {is_polyphonic}")
print(f"    voices:      {nvoices}")

#run faust to generate the plugin source file
if args.dry_run:
    print(f"{GREEN}[✓] Dry run: skipping Faust C++ generation.{RESET}")
else:
    try:
        subprocess.run(["faust", "-a", arch_path, dsp_path, "-o", out_cpp_path], check=True)
        print(f"{GREEN}[✓] generated: {out_cpp_path}{RESET}")
    except subprocess.CalledProcessError:
        print(f"{RED}[!] faust compilation failed.{RESET}")

        sys.exit(1)

#dry run 
if args.dry_run:
    print(f"{GREEN}[✓] Dry run: Skipping CMake configuration and build.{RESET}")
    sys.exit(0)
start_time = time.time()

#run cMake with macOS sdk path to find stdlib headers
try:
    sdk_path = subprocess.check_output(["xcrun", "--sdk", "macosx", "--show-sdk-path"], universal_newlines=True).strip()
    cxx_include_path = "/Library/Developer/CommandLineTools/usr/include/c++/v1"

    faust2clap_cmake_dir = Path(__file__).resolve().parent
    build_dir = os.path.abspath(output_dir)  # reusing generated output dir

# decided to hardcode faust2clap_cmake_dir so a little safeguard can help a fail to be early and clear
# so add a defensive check to make sure CMakeLists.txt exists 
    if not os.path.isfile(os.path.join(faust2clap_cmake_dir, "CMakeLists.txt")):
        print(f"{RED}[!] CMakeLists.txt not found in {faust2clap_cmake_dir}{RESET}")

        sys.exit(1)

    subprocess.run([
        "cmake", "-S", faust2clap_cmake_dir, "-B", build_dir,
        f"-DCMAKE_CXX_FLAGS=-isysroot {sdk_path} -I{cxx_include_path}"
    ], check=True, capture_output=True)

    subprocess.run(["cmake", "--build", build_dir], check=True, capture_output=True)
        
# wee change here, let's also print the build directory, if succesful
    print(f"{GREEN}[✓] build completed successfully. Plugin is in: {build_dir}{RESET}")
    duration = time.time() - start_time
    print(f"{GREEN}✓ Done in {duration:.2f}s{RESET}")
except subprocess.CalledProcessError as e:
    print(f"{RED}[!] cmake build failed.{RESET}")
    print(f"{RED}[stderr]\n{e.stderr.decode() if e.stderr else 'No stderr'}{RESET}")
    print(f"{RED}[stdout]\n{e.stdout.decode() if e.stdout else 'No stdout'}{RESET}")




