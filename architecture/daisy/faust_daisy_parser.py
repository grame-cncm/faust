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
configparse_reg = re.compile("([a-zA-Z_]*):([AD][0-9]+)")
dac_index_reg = re.compile("[AD]([0-9]+)")

project_dir = sys.argv[1]
mem_threshold = int(sys.argv[2]) 
nvoices = int(sys.argv[3])
use_sdram = int(sys.argv[4])
archfile = sys.argv[5]
config_file = sys.argv[6]


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

## If configuration file is provided 
config_layout = None
config_ui = None
config_midi = None
midi_pins = {}
if(config_file.isdigit() == False):
    f = open(config_file)
    conf_str = f.read()
    config_layout = json.loads(conf_str)
    chip = config_layout["chip"]
    if(chip == "seed"):
        print("SEED=true")
        print("PATCHSM=false")
    elif(chip == "patchsm"):
        print("PATCHSM=true")
        print("SEED=false")

    if("name" in config_layout):
        name = config_layout["name"]
        if(name == "pod"):
            print("POD=true")
            print("PATCH=false")
        elif(name == "patch"):
            print("PATCH=true")
            print("POD=false")
    
    if("midi" in config_layout):
        config_midi_list = config_layout["midi"]
        config_midi = {}
        for elem  in config_midi_list:
            for key, value in elem.items():
                config_midi[key] = value

        if(config_midi["type"] == "uart"):
            print("UART=true")
        elif(config_midi["type"] == "usb"):
            if("peripheral" in config_midi and config_midi["peripheral"] == "external"):
                print("MIDI_PERIPHERAL=EXERNAL")
            else:
                print("MIDI_PERIPHERAL=INTERNAL")
    
    if("ui" in config_layout):
        config_ui = config_layout["ui"]

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
        self.scale = "lin"
    
class digi_in:
    def __init__(self):
        self.type = ""
        self.init = 0
        self.min = 0
        self.max = 0
        self.step = 0
        self.pin_index = 0
        self.label = ""

class digi_out:
    def __init__(self):
        self.type = ""
        self.init = 0
        self.min = 0
        self.max = 0
        self.step = 0
        self.pin_index = 0
        self.label = ""
        self.pwm = False
        self.pwm_mode = "inv"

class dac:
    def __init__(self):
        self.type = ""
        self.label = ""
        self.channel = 0
        self.scale = "lin"

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
        self.scale = "lin"

class input: 
    def __init__(self):
        self.type = "adc"
        self.index = 0

class output: 
    def __init__(self):
        self.type = "dac"
        self.index = 0

class polyctrl:
    def __init__(self):
        self.label = ""
        self.control_type = "slider"
        self.init = 0
        self.min = 0
        self.max = 0
        self.step = 0
        self.scale = "lin"

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
        self.digi_in_count = 0
        self.digi_out_count = 0
        self.dac_count = 0
        self.dac = [False, False]
        self.adcs = []
        self.dacs = []
        self.midis = []
        self.polys = []
        self.digis_in = []
        self.digis_out = []
        self.inputs = []
        self.outputs = []
        self.scale = "lin"
        self.pwm = "off"
        self.poly_keys = {
            "key": False,
            "freq": False,
            "vel": False,
            "gain": False,
            "gate": False
        }

    ## To check if config file maps this meta (knob for example) to any ADC, DAC or GPIO
    def config_compare_exchange(self, orig_key, meta, config_ui):
        to_replace = f"{orig_key}:{meta[orig_key]}"
        for elem in config_ui:
            for key, value in elem.items():
                # parse to separate name from index 
                if(to_replace == key):
                    rep = configparse_reg.search(value)
                    if(rep != None and rep.group(1) != None and rep.group(2) != None):
                        return [rep.group(1), rep.group(2)]
        
        return None 

    def check_meta(self, node, config_ui): 
        count = 0
        label = node["label"]
        # For ADC DAC : type, index, label
        # For MIDI : type, miditype, key, channel, label  
        reslist = [] 
        self.scale = "lin"
        self.pwm = "off"
        if("meta" in node):
            for meta in node["meta"]:
                for k, v in meta.items():

                    key = k 
                    value = v 
                    ## Check if we find something in config_ui
                    if(config_ui != None):
                        config_res = self.config_compare_exchange(key, meta, config_ui)
                        if(config_res != None):
                            key = config_res[0]
                            value = config_res[1]

                    # Then create the meta to write
                    if(key == "adc"):
                        reslist.append("adc")
                        reslist.append(value)
                    elif(key == "dac"):
                        reslist.append("dac")
                        reslist.append(value)
                        #dac_index_reg = re.compile("[AD]([0-9]+)")
                        dac_index_res = dac_index_reg.search(value)
                        self.dac[dac_index_res.group(1)] = True;
                    elif(key == "gpio"):
                        reslist.append("gpio")
                        reslist.append(value)
                    elif(key == "midi"):
                        reslist.append("midi")
                        res = midiparse_reg.search(meta[key])
                        if(res == None):
                            eprint("Midi failed to parse")
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
                    # Missing scales, and custom
                    elif(key == "scale"):
                        self.scale = meta[key]
                    elif(key == "pwm"):
                        self.pwm = meta[key]
                    count += 1
            metaname = f"{label}_metadata"
            reslist.append(metaname)
            return reslist
        return None
            
    def recursive_lookup(self, node, config_ui):
        if("items" in node):
            for elem in node["items"]:
                ## Parse
                if("type" in elem and iscontrol(elem["type"])):
                    #item_type = elem["type"] #get_control_tpe(elem["type"])
                    item_type = get_control_type(elem["type"])
                    item_label = elem["label"]
                    metares = self.check_meta(elem, config_ui)

                    if(poly == True and is_poly(item_label)):
                        self.polys.append(polyctrl())
                        #if(item_label == "freq"):
                        #    item_label = "key"
                        #elif(item_label == "gain" or item_label == "velocity"):
                        #    item_label = "vel"
                        if(item_label == "vel" or item_label == "velocity"):
                            item_label = "vel"
                            self.poly_keys["vel"] = True
                        elif(item_label == "gain"):
                            self.poly_keys["gain"] = True
                        elif(item_label == "freq"):
                            self.poly_keys["freq"] = True
                        elif(item_label == "key"):
                            self.poly_keys["key"] = True
                        elif(item_label == "gate"): 
                            self.poly_keys["gate"] = True
                        
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
                            self.polys[-1].scale = self.scale
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
                            self.adcs[-1].scale = self.scale
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
                            self.dacs[-1].scale = self.scale
                        self.outputs.append(output())
                        self.outputs[-1].type = "dac"
                        self.outputs[-1].index = self.dac_count
                    elif(metares[0] == "gpio"):
                        if(item_type == "button" or item_type == "checkbox"):
                            self.digis_in.append(digi_in())
                            self.digis_in[-1].type = item_type
                            self.digis_in[-1].pin_index = metares[1]
                            self.digis_in[-1].label = metares[2]

                            self.digis_in[-1].min = 0
                            self.digis_in[-1].max = 1
                            self.digis_in[-1].step = 1
                            self.digis_in[-1].init = 0
                            self.inputs.append(input())
                            self.inputs[-1].type = "digi_in"
                            self.inputs[-1].index = self.digi_in_count
                            self.digi_in_count += 1
                        elif(item_type == "bargraph"): # Then it is digital output 
                            self.digis_out.append(digi_out())

                            self.digis_out[-1].type = item_type
                            self.digis_out[-1].pin_index = metares[1]
                            self.digis_out[-1].label = metares[2]
                            self.digis_out[-1].min = 0
                            self.digis_out[-1].max = 1
                            self.digis_out[-1].step = 1
                            self.digis_out[-1].init = 0
                            self.digis_out[-1].pwm = self.pwm

                            self.outputs.append(output())
                            self.outputs[-1].type = "digi_out"
                            self.outputs[-1].index = self.digi_out_count
                            self.digi_out_count += 1

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
                            self.midis[-1].scale = self.scale

                if("items" in elem):
                    self.recursive_lookup(elem) 
    

    def exists_or_add(self, keys, index, cnt):
        if(index in keys):
            return keys[index]
        keys[index] = cnt
        return -1

    def write(self, arch, layout, nvoices, config_midi):
        ccs_cnt = 0
        keys_cnt = 0
        keyons_cnt = 0
        keyoffs_cnt = 0

        ## Count midi element
        for elem in self.midis:
            if(elem.type == "ctrl"):
                ccs_cnt += 1
            if(elem.type == "key"):
                keys_cnt += 1
            if(elem.type == "keyon"):
                keyons_cnt += 1
            if(elem.type == "keyoff"):
                keyoffs_cnt += 1


        cc_used = {}
        key_used = {}
        keyon_used = {}
        keyoff_used = {}

        n_inputs = layout["inputs"]
        n_outputs = layout["outputs"]
        controlstr = f"#define N_INPUTS {n_inputs} \n"
        controlstr += f"#define N_OUTPUTS {n_outputs} \n\n"
        
        if(config_midi["type"] == "uart"):
            if("rx_pin" in config_midi):
                controlstr += f"#define RX_PIN {config_midi["rx_pin"]} \n"
            if("tx_pin" in config_midi):
                controlstr += f"#define TX_PIN {config_midi["tx_pin"]} \n"
        elif(config_midi["type"] == "usb"):
            if("peripheral" in config_midi and config_midi["peripheral"] == "external"):
                controlstr += "#define MIDI_USB_PERIPH daisy::MidiUsbTransport::Config::Periph::EXTERNAL \n"
            else:
                controlstr += "#define MIDI_USB_PERIPH daisy::MidiUsbTransport::Config::Periph::INTERNAL \n"


        polymidival = ""
        polystr = ""
        if(nvoices == 0):
            nvoices = 1

        ## Generate MIDI structures
        midistr = f"static std::array<midi_input, {len(self.midis) * nvoices}> midi_list = {{ \n"
        ccs = f"static std::array<midi_t, {ccs_cnt}> midi_cc = {{ \n"
        keys = f"static std::array<midi_t, {keys_cnt}> midi_key = {{ \n"
        keyons = f"static std::array<midi_t, {keyons_cnt}> midi_keyon = {{ \n"
        keyoffs = f"static std::array<midi_t, {keyoffs_cnt}> midi_keyoff = {{ \n"
        if(len(self.midis) > 0):
            midicnt = 0
            for elem in self.midis:
                res = -1
                if(elem.type == "ctrl"):
                    res = self.exists_or_add(cc_used, elem.key, midicnt)
                    if(res == -1):
                        ccs += f"\tmidi_t{{ midi_t::type_t::cc, {elem.key}, {elem.chan}  }}, \n"
                elif(elem.type == "key"):
                    res = self.exists_or_add(key_used, elem.key, midicnt)
                    if(res == -1):
                        keys += f"\tmidi_t{{ midi_t::type_t::{elem.type}, {elem.key}, {elem.chan}  }}, \n"
                elif(elem.type == "keyon"):
                    res = self.exists_or_add(keyon_used, elem.key, midicnt)
                    if(res == -1):
                        keyons += f"\tmidi_t{{ midi_t::type_t::{elem.type}, {elem.key}, {elem.chan}  }}, \n"
                elif(elem.type == "keyoff"):
                    res = self.exists_or_add(keyoff_used, elem.key, midicnt)
                    if(res == -1):
                        keyoffs += f"\tmidi_t{{ midi_t::type_t::{elem.type}, {elem.key}, {elem.chan}  }}, \n"
                for i in range(0, nvoices):
                    if(elem.type == "ctrl"):
                        ref_idx = self.exists_or_add(cc_used, elem.key, midicnt)
                        midistr += f"\tmidi_input(adc::type_t::{elem.control_type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, scale::scale_t::{elem.scale}, &(midi_cc[{ref_idx}])), \n"
                    elif(elem.type == "key"):
                        ref_idx = self.exists_or_add(key_used, elem.key, midicnt)
                        midistr += f"\tmidi_input(adc::type_t::{elem.control_type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, scale::scale_t::{elem.scale}, &(midi_key[{ref_idx}])), \n"
                    elif(elem.type == "keyon"):
                        ref_idx = self.exists_or_add(keyon_used, elem.key, midicnt)
                        midistr += f"\tmidi_input(adc::type_t::{elem.control_type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, scale::scale_t::{elem.scale}, &(midi_keyon[{ref_idx}])), \n"
                    elif(elem.type == "keyoff"):
                        ref_idx = self.exists_or_add(keyoff_used, elem.key, midicnt)
                        midistr += f"\tmidi_input(adc::type_t::{elem.control_type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, scale::scale_t::{elem.scale}, &(midi_keyoffs[{ref_idx}])), \n"
                if(res == -1):
                    midicnt += 1


        ## Generate polyphonic structs 
        polystruct = ""
        if(len(self.polys) > 0):
            if(self.poly_keys["key"] == True):
                controlstr += "#define POLY_KEY \n"
            if(self.poly_keys["freq"] == True):
                controlstr += "#define POLY_FREQ \n"
            if(self.poly_keys["vel"] == True):
                controlstr += "#define POLY_VEL \n"
            if(self.poly_keys["gain"] == True):
                controlstr += "#define POLY_GAIN \n"
            if(self.poly_keys["gate"] == True):
                controlstr += "#define POLY_GATE \n"

            polyconstr = "\tpoly_control("
            polyinit = ""
            polystruct = "struct poly_control : public poly_control_base {\n"
            polymethods = ""
            first = True
            for i, elem in enumerate(self.polys): 
                polyconstr += f"poly_input {elem.label}_ "
                if(i < (len(self.polys) - 1) ):
                    polyconstr += ", "
                if(first):
                    polyinit += f"\t\t: {elem.label}({elem.label}_)\n"
                else:
                    polyinit += f"\t\t, {elem.label}({elem.label}_)\n"

                first = False
                polystruct += f"\tpoly_input {elem.label}; \n"
                polymethods += f"\tpoly_input* get_{elem.label}() override {{return &{elem.label};}} \n"

            polyconstr += ") \n"
            polyconstr += polyinit
            polyconstr += "\t{} \n"
            polystruct += polyconstr
            polystruct += polymethods
            polystruct += "}; \n\n"

            polymidival = f"static std::array<midi_t, {nvoices * len(self.polys)}> poly_midi_values = {{ \n";
            polystr += f"static std::array< poly_control, {nvoices}> poly_inputs {{ \n"
            t = 0
            for v in range(0, nvoices):
                polystr += f"\tpoly_control( \n"
                c = 0
                last = False
                for i, elem in enumerate(self.polys): 
                    last = i == (len(self.polys) - 1)

                    polymidival += f"\tmidi_t{{midi_t::type_t::key, 0, 0}}, \n"
                    polystr += f"\t\tpoly_input(adc::type_t::{elem.control_type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, scale::scale_t::{elem.scale}, &(poly_midi_values[{t}] ), poly_input::type_t::{elem.label} ) "
                    if(not last):
                        polystr += ", "
                    polystr += "\n"

                    c += 1
                    t += 1
                polystr += "\t), \n"
            polystr += "}; \n\n"
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
            controlstr += polystruct
            controlstr += polymidival
            controlstr += polystr

        controlstr += "#endif // MIDICTRL \n\n" 


        ## Generate ADCs 
            
        if(nvoices < 2):
            controlstr += f"static std::array<adc, {len(self.adcs)}> adc_list = {{ \n"
        else:
            controlstr += f"static std::array<shared_adc<{nvoices}>, {len(self.adcs)}> adc_list = {{ \n"
        if(len(self.adcs) > 0):
            for elem in self.adcs:
                if(nvoices < 2):
                    controlstr += f"\tadc(adc::type_t::{elem.type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, scale::scale_t::{elem.scale}, {elem.pin_index}), \n"
                else: 
                    controlstr += f"\tshared_adc<{nvoices}>(adc::type_t::{elem.type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, scale::scale_t::{elem.scale}, {elem.pin_index}), \n"
        controlstr += "}; \n"
        controlstr += f"std::array<daisy::AdcChannelConfig, {len(self.adcs)}> adc_config_list; \n\n"

        if(nvoices < 2):
            controlstr += f"static std::array<digi_input, {len(self.digis_in)}> digi_input_list {{\n"
        else: 
            controlstr += f"static std::array<shared_digi_input<{nvoices}>, {len(self.digis_in)}> digi_input_list {{\n"
        if(len(self.digis_in) > 0):
            for elem in self.digis_in:
                if(nvoices < 2):
                    controlstr += f"\tdigi_input(adc::type_t::{elem.type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, {elem.pin_index}), \n"
                else:
                    controlstr += f"\tshared_digi_input<{nvoices}>(adc::type_t::{elem.type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, {elem.pin_index}), \n"
        controlstr += "}; \n\n"

        input_len = (len(self.adcs) + len(self.midis) + len(self.digis_in)) 
        if(poly):
            input_len = (input_len + len(self.polys)) * nvoices
        inputstr = f"static std::array<control *, {input_len}> input_list = {{ \n"
        if(poly):
            voice_counter = 0
            poly_index = 0
            for i in range(0, input_len):
                n = i % len(self.inputs)
                elem = self.inputs[n]
                if(elem.type == "midi"):
                    inputstr += f"\t&midi_list[{elem.index}], \n"
                    elem.index += 1
                elif(elem.type == "adc"):
                    inputstr += f"\t&adc_list[{elem.index}], \n"
                elif(elem.type == "digi_in"):
                    inputstr += f"\t&digi_input_list[{elem.index}], \n"
                elif(elem.type == "poly"):
                    inputstr += f"\tpoly_inputs[{voice_counter}].get_{self.polys[poly_index].label}(), \n"
                    poly_index = (poly_index + 1) % len(self.polys)
                    #inputstr += f"\tpoly_list[{elem.index + (voice_counter * len(self.polys))}], \n"
                if(n == (len(self.inputs ) - 1)):
                    voice_counter += 1
        else:
            for elem in self.inputs:
                if(elem.type == "midi"):
                    inputstr += f"\t&midi_list[{elem.index}], \n"
                elif(elem.type == "adc"):
                    inputstr += f"\t&adc_list[{elem.index}], \n"
                elif(elem.type == "digi_in"):
                    inputstr += f"\t&digi_input_list[{elem.index}], \n"
        
        inputstr += "}; \n\n"
        controlstr += inputstr


        last_chn = None
        if(len(self.dacs) > 0):
            controlstr += "constexpr bool dacs_used = true; \n"
        else:
            controlstr += "constexpr bool dacs_used = false; \n"
            controlstr += "static const daisy::DacHandle::Channel dac_chnls = daisy::DacHandle::Channel::BOTH; // dummy \n"

        if(nvoices < 2):
            controlstr += f"static std::array<dac, {len(self.dacs)}> dac_list = {{ \n"
        else:
            controlstr += f"static std::array<shared_dac<{nvoices}>, {len(self.dacs)}> dac_list = {{ \n"
        if(len(self.dacs) > 0):
            for elem in self.dacs:
                if(elem.channel == 1):
                    last_chn = "daisy::DacHandle::Channel::ONE"
                elif(elem.channel == 2):
                    last_chn = "daisy::DacHandle::Channel::TWO"
                if(nvoices < 2):
                    controlstr += f"\tdac({last_chn}, {elem.min}, {elem.max}, scale::scale_t::{elem.scale} ), \n"
                else:
                    controlstr += f"\tshared_dac<{nvoices}>({last_chn}, {elem.min}, {elem.max}, scale::scale_t::{elem.scale} ), \n"

        controlstr += "}; \n"
        if(len(self.dacs) > 0):
            if(len(self.dacs) == 2):
                controlstr += "daisy::DacHandle::Channel dac_chnls = daisy::DacHandle::Channel::BOTH; \n"
            else:
                controlstr += f"daisy::DacHandle::Channel dac_chnls = {last_chn}; \n"
            
        

        if(nvoices < 2):
            controlstr += f"static std::array<digi_output, {len(self.digis_out)}> digi_output_list = {{ \n"
        else:
            controlstr += f"static std::array<shared_digi_output<{nvoices}>, {len(self.digis_out)}> digi_output_list = {{ \n"
        for elem in self.digis_out:
            if(nvoices < 2):
                controlstr += f"\tdigi_output({elem.pin_index}, digi_output::pwm_t::{elem.pwm}), \n"
            else:
                controlstr += f"\tshared_digi_output<{nvoices}>({elem.pin_index}, digi_output::pwm_t::{pwm}), \n"
        controlstr += "}; \n\n"
            

        outputstr = f"static std::array<control *, {len(self.outputs)}> output_list = {{ \n"
        for elem in self.outputs:
            if(elem.type == "dac"):
                outputstr += f"\t&(dac_list[{elem.index}]), \n"
            elif(elem.type == "digi_out"):
                outputstr += f"\t&(digi_output_list[{elem.index}]), \n"
        outputstr += "}; \n\n"

        controlstr += outputstr 
        return arch.replace(control_tag, controlstr)

if("ui" in dsp_layout):
    scan = ui_scanner()
    scan.recursive_lookup(dsp_layout["ui"][0], config_ui)
    arch = scan.write(arch, dsp_layout, nvoices, config_midi)
    

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

print(f"NVOICES={nvoices}")
#print(nvoices) # To store output in bash NVOICES
sys.exit(0)


