import json
import sys 
import re

freg = re.compile("(fZone)")
ireg = re.compile("(iZone)")
voicereg = re.compile("nvoices:([0-9]+)")
optreg = re.compile("(options)")

project_dir = sys.argv[1]
mem_threshold = int(sys.argv[2]) 
nvoices = int(sys.argv[3])
use_sdram = int(sys.argv[4])

if(use_sdram == 1):
    use_sdram = True
else:
    use_sdram = False

json_path = project_dir + ".dsp.json"
f = open(json_path)
json_str = f.read()
dsp_layout = json.loads(json_str)
meta = dsp_layout["meta"]

options = None
for elem in meta:
    if("options" in elem):
        options = elem["options"]

if(options != None and nvoices < 1):
    nvdict = voicereg.search(options)
    if(nvdict):
        nv = int(nvdict.group(1))
        if(nv > 1):
            nvoices = nv

fmem = 0
imem = 0 

if(use_sdram):
    mem_layout = dsp_layout["memory_layout"]
    for elem in mem_layout:
        if(freg.match(elem["name"]) and elem["size_bytes"] >= mem_threshold):
            fmem += elem["size_bytes"]
        elif(ireg.match(elem["name"]) and elem["size_bytes"] >= mem_threshold):
            imem += elem["size_bytes"]

    total_bytes = fmem+imem
    if(nvoices > 1):
        total_bytes *= nvoices

    with open( project_dir + "/faust2daisy_sdram.h", "w") as f:
        f.write("#pragma once\n")
        f.write("#include\"daisy.h\"\n")
        #f.write("constexpr static size_t faust_sdram_size_bytes = " + str(total_bytes) + ";\n")
        f.write("#define FAUST_SDRAM_SIZE_BYTES " + str(total_bytes) + "\n");

print(nvoices) # To store output in bash NVOICES
sys.exit(0)


