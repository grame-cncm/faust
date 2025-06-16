#!/usr/bin/env python3
import sys #cli arguments
import os #file path manipulation
import subprocess #run shell commands

#config
ARCH_REL_PATH="architecture/clap/clap-arch.cpp"
OUTPUT_ROOT="build"

#check for user input, which should be a .dsp file, otherwise just exit
if len(sys.argv)<2:
    print("usage: faust2clap.py <file.dsp>")
    sys.exit(1)


dsp_path= sys.argv[1]#full path to the provdded .dsp file
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


#now run faust
try:
    subprocess.run(["faust","-a", arch_path, dsp_path, "-o", out_cpp_path], check=True)
    print(f"[✓] generated: {out_cpp_path}")

except subprocess.CalledProcessError:
    print("[!] faust compilation failed.")
    sys.exit(1)


#build plugin using cmake
try:
    print("[*] running cmake build")
    subprocess.run(["cmake", "-S", ".", "-B", "build"], cwd=this_dir, check=True, capture_output=True)
    subprocess.run(["cmake", "--build", "build"], cwd=this_dir, check=True, capture_output=True)
    print("[✓] build completed successfully.")

    
except subprocess.CalledProcessError as e:
    print("[!] cmake build failed.")
    print(f"[stderr]\n{e.stderr.decode() if e.stderr else 'No stderr'}")
    print(f"[stdout]\n{e.stdout.decode() if e.stdout else 'No stdout'}")
    sys.exit(1)



