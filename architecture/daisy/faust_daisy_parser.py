import json
import sys 
import re

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

freg = re.compile("(fZone)")
ireg = re.compile("(iZone)")
voicereg = re.compile("nvoices:([0-9]+)")
optreg = re.compile("(options)")
itemreg = re.compile(".?(slider|button|checkbox|bargraph|nentry)")
polyreg = re.compile("(freq|key|gain|vel|velocity|gate)")
midiparse_reg = re.compile("(keyon|keyoff|key|ctrl)\\s+([0-9]+)\\s*([0-9]+)?")

project_dir = sys.argv[1]
mem_threshold = int(sys.argv[2]) 
nvoices = int(sys.argv[3])
use_sdram = int(sys.argv[4])
archfile = sys.argv[5]

arch = ""
with open(archfile, 'r') as file:
    arch = file.read()

# Used for inlining in architecture file  
control_tag = "/*<UI CONTROL TAG>*/"
sdram_tag = "/*<SDRAM TAG>*/" 

if(use_sdram == 1):
    use_sdram = True
else:
    use_sdram = False

json_path = project_dir + ".dsp.json"
f = open(json_path)
json_str = f.read()
dsp_layout = json.loads(json_str)
meta = dsp_layout["meta"]

def iscontrol(item):
    return itemreg.match(item)

def get_control_type(item):
    res = itemreg.search(item).group(1)
    return res

def is_poly(label):
    return polyreg.match(label)


class adc:
    def __init__(self):
        self.type = ""
        self.init = 0
        self.min = 0
        self.max = 0
        self.step = 0
        self.pin_index = 0
        self.label = ""
    
class dac:
    def __init__(self):
        self.type = ""
        self.label = ""
        self.channel = 0

class midi:
    def __init__(self):
        self.type = ""
        self.chan = 0
        self.key = 0
        self.control_type = "slider"
        self.min = 0
        self.max = 0
        self.step = 0
        self.init = 0

class input: 
    def __init__(self):
        self.type = "adc"
        self.index = 0

class polyctrl:
    def __init__(self):
        self.label = ""
        self.control_type = "slider"
        self.init = 0
        self.min = 0
        self.max = 0
        self.step = 0

options = None
for elem in meta:
    if("options" in elem):
        options = elem["options"]


# Lookup for number of voices in options if not provided by the CLI options 
if(options != None and nvoices < 1):
    nvdict = voicereg.search(options)
    if(nvdict):
        nv = int(nvdict.group(1))
        if(nv > 1):
            nvoices = nv


poly = False
if(nvoices > 1):
    poly = True




class ui_scanner:
    def __init__(self):
        self.uicount = 0
        self.uistr = ""
        self.meta_str = ""
        self.adc_count = 0
        self.midi_count = 0
        self.poly_count = 0
        self.dac = [False, False]
        self.adcs = []
        self.dacs = []
        self.midis = []
        self.inputs = []
        self.polys = []

    def check_meta(self, node): 
        count = 0
        l_meta = ""
        label = node["label"]
        # For ADC DAC : type, index, label
        # For MIDI : type, miditype, key, channel, label  
        reslist = [] 
        if("meta" in node):
            for meta in node["meta"]:
                for key in meta.keys():
                    if(key == "adc"):
                        reslist.append("adc")
                        reslist.append(int(meta[key]))
                    elif(key == "dac"):
                        reslist.append("dac")
                        reslist.append(int(meta[key]))
                        self.dac[int(meta[key])] = True;
                    elif(key == "midi"):
                        reslist.append("midi")
                        res = midiparse_reg.search(meta[key])
                        if(res == None):
                            eprint("No res, midi failed to parse")
                            exit()
                        miditype = ""
                        key = 0
                        chan = 0
                        if(res): 
                            if(res.group(1) != None):
                                miditype = res.group(1)
                            if(res.group(2) != None):
                                key = res.group(2)
                            if(res.group(3) != None):
                                chan = int(res.group(3))
                            reslist.append(miditype)
                            reslist.append(key)
                            reslist.append(chan)
                        #l_meta += f"\tui_meta( midi_meta::midi_type_t::{miditype}, {key}, {chan} ), \n"
                    # Missing scales, and custom
                    elif(key == "scale"):
                        l_meta += f"\tui_meta(ui_meta::scale_t::{meta[key]}), \n"
                    else:
                        val = f"\"{meta[key]}\""
                        l_meta += f"\tui_meta(ui_meta::type_t::custom, \"{key}\", {val}), \n"
                    count += 1
            metaname = f"{label}_metadata"
            reslist.append(metaname)
            return reslist
        return None
            
    def recursive_lookup(self, node):
        if("items" in node):
            for elem in node["items"]:
                ## Parse
                if("type" in elem and iscontrol(elem["type"])):
                    #item_type = elem["type"] #get_control_tpe(elem["type"])
                    item_type = get_control_type(elem["type"])
                    item_label = elem["label"]
                    metares = self.check_meta(elem)

                    if(poly == True and is_poly(item_label)):
                        eprint("Poly :" )
                        eprint(item_label)
                        self.polys.append(polyctrl())
                        if(item_label == "key"):
                            item_label = "freq"
                        elif(item_label == "vel" or item_label == "velocity"):
                            item_label = "gain"
                        self.polys[-1].label = item_label
                        self.polys[-1].control_type = item_type
                        self.inputs.append(input())
                        self.inputs[-1].type = "poly"
                        self.inputs[-1].index = self.poly_count 
                        self.poly_count += 1
                        if(item_type == "button" or item_type == "checkbox"):
                            self.polys[-1].min = 0
                            self.polys[-1].max = 1
                            self.polys[-1].step = 1
                            self.polys[-1].init = 0
                        elif(item_type == "slider" or item_type == "nentry"):
                            self.polys[-1].min = elem["min"]
                            self.polys[-1].max = elem["max"]
                            self.polys[-1].step = elem["step"]
                            self.polys[-1].init = elem["init"]
                        continue
                    if(metares == None):
                        continue
                    if(metares[0] == "adc"):
                        self.adcs.append(adc())
                        self.adcs[-1].pin_index = metares[1]
                        self.adcs[-1].type = item_type 
                        self.adcs[-1].label = metares[2] 
                        if(item_type == "button" or item_type == "checkbox"):
                            self.adcs[-1].min = 0
                            self.adcs[-1].max = 1
                            self.adcs[-1].step = 1
                            self.adcs[-1].init = 0
                        elif(item_type == "slider" or item_type == "nentry"):
                            self.adcs[-1].min = elem["min"]
                            self.adcs[-1].max = elem["max"]
                            self.adcs[-1].step = elem["step"]
                            self.adcs[-1].init = elem["init"]
                        self.inputs.append(input())
                        self.inputs[-1].type = "adc"
                        self.inputs[-1].index = self.adc_count
                        self.adc_count += 1

                    elif(metares[0] == "dac"):
                        self.dacs.append(dac())
                        self.dacs[-1].channel = metares[1]
                        self.dacs[-1].label = metares[2]
                        if(item_type == "bargraph"):
                            self.dacs[-1].min = elem["min"]
                            self.dacs[-1].max = elem["max"]
                    elif(metares[0] == "midi"):
                        self.midis.append(midi())
                        self.midis[-1].type = metares[1]
                        self.midis[-1].key = metares[2]
                        self.midis[-1].chan = metares[3]
                        
                        self.midis[-1].control_type = item_type
                    
                        self.inputs.append(input())
                        self.inputs[-1].type = "midi"
                        self.inputs[-1].index = self.midi_count 
                        self.midi_count += 1
                        
                        if(item_type == "button" or item_type == "checkbox"):
                            self.midis[-1].min = 0
                            self.midis[-1].max = 1
                            self.midis[-1].step = 1
                            self.midis[-1].init = 0
                        elif(item_type == "slider" or item_type == "nentry"):
                            self.midis[-1].min = elem["min"]
                            self.midis[-1].max = elem["max"]
                            self.midis[-1].step = elem["step"]
                            self.midis[-1].init = elem["init"]

                if("items" in elem):
                    self.recursive_lookup(elem) 
    
    def write(self, arch, layout):
        n_inputs = layout["inputs"]
        n_outputs = layout["outputs"]
        eprint("IO IO IO")
        eprint(n_inputs)
        eprint(n_outputs)
        controlstr = f"#define N_INPUTS {n_inputs} \n"
        controlstr += f"#define N_OUTPUTS {n_outputs} \n\n"

        polymidival = ""
        polystr = ""
        polylist = ""
        midistr = f"static std::array<midi_input, {len(self.midis)}> midi_list = {{ \n"
        ccs = "static std::unordered_map<uint8_t, midi_t> midi_cc = { \n"
        keys = "static std::unordered_map<uint8_t, midi_t> midi_key = { \n"
        keyons = "static std::unordered_map<uint8_t, midi_t> midi_keyon = { \n"
        keyoffs = "static std::unordered_map<uint8_t, midi_t> midi_keyoff = { \n"
        if(len(self.midis) > 0):
            for elem in self.midis:
                if(elem.type == "ctrl"):
                    ccs += f"\t{{ {elem.key}, midi_t{{ midi_t::type_t::cc, {elem.key}, {elem.chan} }} }}, \n"
                    midistr += f"\tmidi_input(adc::type_t::{elem.control_type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, &(midi_cc[{elem.key}])), \n"
                elif(elem.type == "key"):
                    keys += f"\t{{ {elem.key}, midi_t{{ midi_t::type_t::{elem.type}, {elem.key}, {elem.chan} }} }}, \n"
                    midistr += f"\tmidi_input(adc::type_t::{elem.control_type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, &(midi_key[{elem.key}])), \n"
                elif(elem.type == "keyon"):
                    keyons += f"\t{{ {elem.key}, midi_t{{ midi_t::type_t::{elem.type}, {elem.key}, {elem.chan} }} }}, \n"
                    midistr += f"\tmidi_input(adc::type_t::{elem.control_type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, &(midi_keyon[{elem.key}])), \n"
                elif(elem.type == "keyoff"):
                    keyoffs += f"\t{{ {elem.key}, midi_t{{ midi_t::type_t::{elem.type}, {elem.key}, {elem.chan} }} }}, \n"
                    midistr += f"\tmidi_input(adc::type_t::{elem.control_type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, &(midi_keyoffs[{elem.key}])), \n"


        if(len(self.polys) > 0):
            polymidival = f"static std::array<midi_t, {nvoices * len(self.polys)}> poly_midi_values = {{ \n";
            polystr += "using poly_control = std::unordered_map<std::string, midi_input>; \n"
            polystr += f"static std::array< poly_control, {nvoices}> poly_inputs {{ \n"
            polylist = f"static std::array<midi_input*, {nvoices * len(self.polys)}> poly_list {{ \n"
            t = 0
            for v in range(0, nvoices):
                polystr += f"\tpoly_control{{ \n"
                c = 0
                for elem in self.polys: 
                    polymidival += f"\tmidi_t{{midi_t::type_t::key, 0, 0}}, \n"
                    polystr += f"\t\t{{ \"{elem.label}\",  midi_input(adc::type_t::{elem.control_type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, &(poly_midi_values[{t}] ) )}}, \n"
                    polylist += f"\t&(poly_inputs[{v}][\"{elem.label}\"]), \n"
                    c += 1
                    t += 1
                polystr += "\t}, \n"
            polystr += "}; \n\n"
            polylist += "}; \n\n"
            polymidival += "}; \n\n"
        
        ccs += "}; \n"
        keys += "}; \n"
        keyons += "}; \n"
        keyoffs += "}; \n"
        midistr += "}; \n\n"
        controlstr += "#ifdef MIDICTRL \n"
        controlstr += ccs
        controlstr += keys
        controlstr += keyons
        controlstr += keyoffs
        controlstr += midistr

        if(len(self.polys) > 0):
            controlstr += polymidival
            controlstr += polystr
            controlstr += polylist 

        controlstr += "#endif \n\n"

        controlstr += f"static std::array<adc, {len(self.adcs)}> adc_list = {{ \n"
        if(len(self.adcs) > 0):
            for elem in self.adcs:
                controlstr += f"\tadc(adc::type_t::{elem.type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, A{elem.pin_index}), \n"
        controlstr += "}; \n"
        controlstr += f"std::array<daisy::AdcChannelConfig, {len(self.adcs)}> adc_config_list; \n\n"

        input_len = (len(self.adcs) + len(self.midis)) 
        if(poly):
            input_len = (input_len + len(self.polys)) * nvoices
        inputstr = f"static std::array<control *, {input_len}> input_list = {{ \n"
        if(poly):
            voice_counter = 0
            for i in range(0, input_len):
                n = i % len(self.inputs)
                elem = self.inputs[n]
                if(elem.type == "midi"):
                    inputstr += f"\t&midi_list[{elem.index}], \n"
                elif(elem.type == "adc"):
                    inputstr += f"\t&adc_list[{elem.index}], \n"
                elif(elem.type == "poly"):
                    inputstr += f"\tpoly_list[{elem.index + (voice_counter * len(self.polys))}], \n"
                if(n == (len(self.inputs ) - 1)):
                    voice_counter += 1

        else:
            for elem in self.inputs:
                if(elem.type == "midi"):
                    inputstr += f"\t&midi_list[{elem.index}], \n"
                elif(elem.type == "adc"):
                    inputstr += f"\t&adc_list[{elem.index}], \n"
        
        inputstr += "}; \n\n"
        controlstr += inputstr

        last_chn = None
        if(len(self.dacs) > 0):
            controlstr += "constexpr bool dacs_used = true; \n"
        else:
            controlstr += "constexpr bool dacs_used = false; \n"
            controlstr += "static const daisy::DacHandle::Channel dac_chnls = daisy::DacHandle::Channel::BOTH; // dummy \n"

        controlstr += f"static std::array<dac, {len(self.dacs)}> dac_list = {{ \n"
        if(len(self.dacs) > 0):
            for elem in self.dacs:
                if(elem.channel == 1):
                    last_chn = "daisy::DacHandle::Channel::ONE"
                elif(elem.channel == 2):
                    last_chn = "daisy::DacHandle::Channel::TWO"
                controlstr += f"\tdac({last_chn}, {elem.min}, {elem.max} ), \n"

        controlstr += "}; \n"
        if(len(self.dacs) > 0):
            if(len(self.dacs) == 2):
                controlstr += "daisy::DacHandle::Channel dac_chnls = daisy::DacHandle::Channel::BOTH; \n"
            else:
                controlstr += f"daisy::DacHandle::Channel dac_chnls = {last_chn}; \n"
            

        return arch.replace(control_tag, controlstr)

if("ui" in dsp_layout):
    scan = ui_scanner()
    scan.recursive_lookup(dsp_layout["ui"][0])
    arch = scan.write(arch, dsp_layout)
    

fmem = 0
imem = 0 

### SDRAM Memory 
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
    
    sdram_content = "#define FAUST_SDRAM_SIZE_BYTES " + str(total_bytes) + "\n";
    arch = arch.replace(sdram_tag, sdram_content);


arch_dest = project_dir + "/daisy_arch.cpp"
with open(arch_dest, "w") as file:
    file.write(arch)

print(nvoices) # To store output in bash NVOICES
sys.exit(0)


