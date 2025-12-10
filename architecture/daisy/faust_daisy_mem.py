import json
import sys 
import re

freg = re.compile("(fZone)")
ireg = re.compile("(iZone)")

project_dir = sys.argv[1]
mem_threshold = int(sys.argv[2]) 
nvoices = int(sys.argv[3])

json_path = project_dir + ".dsp.json"
f = open(json_path)
json_str = f.read()
dsp_layout = json.loads(json_str)

mem_layout = dsp_layout["memory_layout"]

fmem = 0
imem = 0 

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
    f.write("constexpr static size_t faust_sdram_size_bytes = " + str(total_bytes) + ";\n")
    #f.write("extern uint8_t DSY_SDRAM_BSS faust_sdram_mem[ faust_sdram_size_bytes ]; \n")

