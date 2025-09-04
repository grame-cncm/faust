#!/usr/bin/env python3
import sys #cli arguments
import os #file path manipulation
import subprocess #run shell commands
import json
import re
import argparse

#config
ARCH_REL_PATH="architecture/clap/clap-arch.cpp"
OUTPUT_ROOT="build"

#parse command line arguments properly
parser = argparse.ArgumentParser(description='faust2clap - Generate CLAP plugins from Faust DSP code')
parser.add_argument('dsp_file', help='Input .dsp file')
parser.add_argument('-nvoices', type=int, default=16, help='Number of polyphonic voices (default: 16)')
parser.add_argument('-mono', action='store_true', help='Generate monophonic plugin instead of polyphonic')
parser.add_argument('-poly', action='store_true', help='Generate polyphonic plugin (default behaviour)')

args = parser.parse_args()

dsp_path = args.dsp_file #full path to the provided .dsp file
nvoices = args.nvoices
# Note: is_polyphonic will be set later based on auto-detection or user override
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
    arch_path_from_faust = os.path.join(arch_dir, "clap/clap-arch.cpp")
    if os.path.isfile(arch_path_from_faust):
        arch_path = arch_path_from_faust
        # get faust root from libdir
        faust_root = subprocess.check_output(["faust", "--libdir"], universal_newlines=True).strip()
except (subprocess.CalledProcessError, FileNotFoundError):
    # faust command not available or failed
    pass

# fallback: try other possible locations if faust command didn't work
if not arch_path:
    possible_paths = [
        # relative to script location (development setup)
        os.path.join(this_dir, "../..", ARCH_REL_PATH),
        # check FAUST_LIB environment variable
        os.path.join(os.environ.get("FAUST_LIB", ""), ARCH_REL_PATH) if os.environ.get("FAUST_LIB") else "",
        # system-wide fallbacks (last resort)
        f"/usr/local/share/faust/{ARCH_REL_PATH}",
        f"/usr/share/faust/{ARCH_REL_PATH}",
        f"/opt/homebrew/share/faust/{ARCH_REL_PATH}",
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
    print(f"[!]missing architecture file: {ARCH_REL_PATH}")
    print("[!]Try running: faust --archdir")
    print("[!]Or set FAUST_LIB environment variable")
    print("[!]Make sure Faust is properly installed and in PATH")
    sys.exit(1)

#create output directory
output_dir=os.path.join(faust_root, OUTPUT_ROOT,base)
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

#run cMake with macOS sdk path to find stdlib headers
try:
    print("[*] running cmake build")
    sdk_path = subprocess.check_output(["xcrun", "--sdk", "macosx", "--show-sdk-path"], universal_newlines=True).strip()
    cxx_include_path = "/Library/Developer/CommandLineTools/usr/include/c++/v1"

    subprocess.run([
        "cmake", "-S", ".", "-B", "build",
        f"-DCMAKE_CXX_FLAGS=-isysroot {sdk_path} -I{cxx_include_path}"
    ], cwd=this_dir, check=True, capture_output=True)

    subprocess.run(["cmake", "--build", "build"], cwd=this_dir, check=True, capture_output=True)

    print("[✓] build completed successfully.")
except subprocess.CalledProcessError as e:
    print("[!] cmake build failed.")
    print(f"[stderr]\n{e.stderr.decode() if e.stderr else 'No stderr'}")
    print(f"[stdout]\n{e.stdout.decode() if e.stdout else 'No stdout'}")
    sys.exit(1)

    
except subprocess.CalledProcessError as e:
    print("[!] cmake build failed.")
    print(f"[stderr]\n{e.stderr.decode() if e.stderr else 'No stderr'}")
    print(f"[stdout]\n{e.stdout.decode() if e.stdout else 'No stdout'}")
    sys.exit(1)



