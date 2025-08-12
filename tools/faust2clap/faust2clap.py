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
is_monophonic = args.mono
is_polyphonic = args.poly or not args.mono  # default to poly unless mono specified
if not os.path.isfile(dsp_path):
    print(f"[!] dsp file not found: {dsp_path}")
    sys.exit(1)

base=os.path.splitext(os.path.basename(dsp_path))[0] #name minus extension (.dsp)
out_cpp=f"{base}_clap.cpp" #target outpu filename

#locate arch file relative to script location
this_dir=os.path.dirname(os.path.abspath(__file__))
faust_root=os.path.abspath(os.path.join(this_dir,"../.."))

arch_path=os.path.join(faust_root, ARCH_REL_PATH)
if not os.path.isfile(arch_path):
    print(f"[!]missing architecture file: {arch_path}")
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



