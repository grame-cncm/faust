import json
import os
import sys
import re

## ADC's of Patch SM. 
## This is necessary since the PatchSM class of libdaisy is more abstracted to fit CV requirementts
# So we don't directly read ADC's, but read CV from PatchSM object, with those indexes.
patchsm_pin_map = {
    "C5": 0,
    "C4": 1,
    "C3": 2,
    "C2": 3,
    "C6": 4,
    "C7": 5,
    "C8": 6,
    "C9": 7, 
    "A2": 8,
    "A3": 9, 
    "D9": 10, 
    "D8": 11,
}    

# Allow importing sibling modules regardless of the invocation cwd.
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import daisy_soundfile_gen
import daisy_uart_pins
import daisy_pwm_pin
import daisy_pins

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

# Regex definitions for parsing the Faust DSP JSON layout and configuration files
freg = re.compile("(fZone)")
ireg = re.compile("(iZone)")
voicereg = re.compile("nvoices:([0-9]+)")
optreg = re.compile("(options)")
itemreg = re.compile(".?(slider|button|checkbox|bargraph|nentry)")
polyreg = re.compile("(freq|key|gain|vel|velocity|gate)")
midiparse_reg = re.compile("(keyon|keyoff|key|ctrl)\\s+([0-9]+)\\s*([0-9]+)?")
configparse_reg = re.compile("([a-zA-Z_]*):([AD][0-9]+)")
dac_index_reg = re.compile("[ACD]([0-9]+)")

# Argument parsing
project_dir = sys.argv[1]
mem_threshold = int(sys.argv[2]) 
nvoices = int(sys.argv[3])
use_sdram = int(sys.argv[4])
archfile = sys.argv[5]
config_file = sys.argv[6]

# Soundfile mode : "qspi" (inline samples in QSPI, default) or "sd" (load from
# the SD card /soundfiles folder at runtime).
soundfile_mode = sys.argv[7] if len(sys.argv) > 7 else "qspi"

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
# Default chip so 'chip' is always defined, even when no config file is passed
# (config_file == "0"); the config below overrides it when present.
chip = "seed"

# Serial (UART) control link. Per-control pins come from [rx:Dx] / [tx:Dx]
# metadata and are resolved by daisy_uart_pins; only the baud rate is global
# (one bus speed for all channels).
serial_baud = 115200

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
    
    if("serial" in config_layout):
        config_serial_list = config_layout["serial"]
        config_serial = {}
        for elem in config_serial_list:
            for key, value in elem.items():
                config_serial[key] = value
        if("baud" in config_serial):
            serial_baud = int(config_serial["baud"])
    
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
        self.softpwm = False  # [mode:softpwm] -> software PWM, else on/off

class pwm_out:
    def __init__(self):
        self.label = ""
        self.pin = ""
        self.min = 0
        self.max = 1
        self.timer = ""      # "TIM_3" | "TIM_4" | "TIM_5"
        self.channel = 0     # 1..4
        self.index = 0

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

class serial:
    def __init__(self):
        self.type = "serial"
        self.label = ""
        self.control_type = "slider"
        self.init = 0
        self.min = 0
        self.max = 0
        self.step = 0
        self.scale = "lin"
        self.pin = ""        # Daisy pin label, e.g. "D14"
        self.direction = "rx"  # "rx" (receive) or "tx" (transmit)
        self.index = 0         # index within serials_in / serials_out
        self.channel = 0       # DaisyUartListener channel this control belongs to


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
        self.serial_in_count = 0
        self.serial_out_count = 0
        self.dac = [False, False]
        self.adcs = []
        self.dacs = []
        self.midis = []
        self.polys = []
        self.digis_in = []
        self.digis_out = []
        
        self.serials_in = []
        self.serials_out = []
        self.serials_out_used = {} #
        self.serials_in_used = {}

        self.pwm_out_count = 0
        self.pwms_out = []

        self.inputs = []
        self.outputs = []
        self.scale = "lin"
        self.mode = ""  # gpio output rendering mode ("softpwm" or "")
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
        self.mode = ""
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
                        reslist.append(label)
                    elif(key == "dac"):
                        reslist.append("dac")
                        reslist.append(value)
                        dac_index_res = dac_index_reg.search(value)
                        if(chip == "seed"):
                            if(dac_index_res.group(1) == "7"):
                                self.dac[0] = True
                            elif(dac_index_res.group(1) == "8"):
                                self.dac[1] = True
                        elif(chip == "patchsm"):
                            if(dac_index_res.group(1) == "1"):
                                self.dac[0] = True
                            elif(dac_index_res.group(1) == "10"):
                                self.dac[1] = True
                    elif(key == "gpio"):
                        reslist.append("gpio")
                        reslist.append(value)
                    elif(key == "rx" or key == "tx"):
                        # Serial (UART) control: [rx:Dx] receives into an input
                        # control, [tx:Dx] transmits an output control. 'value'
                        # is the Daisy pin label.
                        reslist.append("serial")
                        reslist.append(key)    # direction: "rx" or "tx"
                        reslist.append(value)  # pin label, e.g. "D14"
                        reslist.append(label)  # control name
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
                    elif(key == "mode"):
                        # Output rendering modifier on a [gpio:] output
                        # (currently: "softpwm").
                        self.mode = meta[key]
                    elif(key == "pwm"):
                        # Hardware PWM primary key: [pwm:PIN].
                        reslist.append("pwm")
                        reslist.append(value)

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
                        self.dac_count += 1

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
                            self.digis_out[-1].softpwm = (self.mode == "softpwm")

                            self.outputs.append(output())
                            self.outputs[-1].type = "digi_out"
                            self.outputs[-1].index = self.digi_out_count
                            self.digi_out_count += 1

                    elif(metares[0] == "pwm"):
                        # Hardware PWM output ([pwm:PIN] on a bargraph).
                        if(item_type != "bargraph"):
                            eprint("faust2daisy: [pwm:] is only valid on a bargraph (got %s)" % item_type)
                            sys.exit(1)
                        try:
                            info = daisy_pwm_pin.resolve_pwm(chip, metares[1])
                        except ValueError as e:
                            eprint("faust2daisy pwm error: %s" % e)
                            sys.exit(1)
                        po = pwm_out()
                        po.pin     = metares[1]
                        po.label   = item_label
                        po.min     = elem["min"]
                        po.max     = elem["max"]
                        po.timer   = info["timer"]
                        po.channel = info["channel"]
                        po.index   = self.pwm_out_count
                        self.pwms_out.append(po)
                        self.outputs.append(output())
                        self.outputs[-1].type = "pwm"
                        self.outputs[-1].index = self.pwm_out_count
                        self.pwm_out_count += 1

                    elif(metares[0] == "serial"):
                        direction = metares[1]  # "rx" or "tx"
                        pin       = metares[2]
                        label     = metares[3]
                        if(direction == "rx"):
                            # Receive into an input control (slider/button/...).
                            s = serial()
                            s.label     = label
                            s.pin       = pin
                            s.direction = "rx"
                            if(item_type == "button" or item_type == "checkbox"):
                                s.control_type = item_type
                                s.min = 0; s.max = 1; s.step = 1; s.init = 0
                            else: # slider / nentry
                                s.control_type = "slider"
                                s.min = elem["min"]; s.max = elem["max"]
                                s.step = elem["step"]; s.init = elem["init"]
                            s.scale = self.scale
                            s.index = self.serial_in_count
                            self.serials_in.append(s)
                            self.inputs.append(input())
                            self.inputs[-1].type = "serial"
                            self.inputs[-1].index = self.serial_in_count
                            self.serial_in_count += 1
                        else: # "tx" : transmit a bargraph value out. Lives in
                              # output_list (so DaisyControlUI assigns its zone);
                              # serial_tx_poll() sends it (throttled, on change).
                            s = serial()
                            s.label     = label
                            s.pin       = pin
                            s.direction = "tx"
                            s.control_type = item_type
                            s.min = elem["min"]; s.max = elem["max"]
                            s.scale = self.scale
                            s.index = self.serial_out_count
                            self.serials_out.append(s)
                            self.outputs.append(output())
                            self.outputs[-1].type = "serial"
                            self.outputs[-1].index = self.serial_out_count
                            self.serial_out_count += 1

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
                            self.adc_count += 1
                        elif(item_type == "slider" or item_type == "nentry"):
                            self.midis[-1].min = elem["min"]
                            self.midis[-1].max = elem["max"]
                            self.midis[-1].step = elem["step"]
                            self.midis[-1].init = elem["init"]
                            self.midis[-1].scale = self.scale
                            self.adc_count += 1


                if("items" in elem):
                    self.recursive_lookup(elem, config_ui) 
    

    def exists_or_add(self, keys, index, cnt):
        if(index in keys):
            return keys[index]
        keys[index] = cnt
        return -1

    def check_pin_conflicts(self):
        # Each physical pin must be claimed by at most one control, EXCEPT
        # serial (UART) pins: several [rx:PIN] controls share one RX pin, and
        # several [tx:PIN] controls share one TX pin, so serial may repeat a
        # pin. Any pin shared with a non-serial feature is a conflict.
        # Pins are resolved to their physical MCU pin (daisy_pins) so aliases
        # collide too (Seed A0 == D15, dac A7 == adc D22, ...); an unknown label
        # falls back to comparing the label itself.
        usage = {}  # physical pin -> list of (label, feature)

        def add(pin, feature):
            if pin is None or pin == "":
                return
            label = str(pin)
            key = daisy_pins.physical(chip, label) or ("?" + label)
            usage.setdefault(key, []).append((label, feature))

        for a in self.adcs:        add(a.pin_index, "adc/cv-in")
        for d in self.digis_in:    add(d.pin_index, "gpio-in")
        for d in self.digis_out:   add(d.pin_index, "gpio-out")
        for d in self.dacs:        add(d.channel,   "dac/cv-out")
        for p in self.pwms_out:    add(p.pin,       "pwm")
        for s in self.serials_in:  add(s.pin,       "serial")
        for s in self.serials_out: add(s.pin,       "serial")

        for key in sorted(usage):
            claims = usage[key]
            has_non_serial = any(f != "serial" for (_, f) in claims)
            if len(claims) >= 2 and has_non_serial:
                phys = key if not key.startswith("?") else "(unresolved)"
                parts = ", ".join("%s [%s]" % (lbl, f) for (lbl, f) in claims)
                eprint("faust2daisy pin conflict: physical pin %s is claimed by "
                       "%d controls -- %s. Each pin may be used once; only "
                       "serial rx/tx pins may be shared."
                       % (phys, len(claims), parts))
                sys.exit(1)

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

        if( len(self.midis) > 0):
            print("MIDI=true")

        cc_used = {}
        key_used = {}
        keyon_used = {}
        keyoff_used = {}

        n_inputs = layout["inputs"]
        n_outputs = layout["outputs"]
        controlstr = f"#define N_INPUTS {n_inputs} \n"
        controlstr += f"#define N_OUTPUTS {n_outputs} \n\n"
        
        if(config_midi is None):
            pass
        elif(config_midi["type"] == "uart"):
            if("rx_pin" in config_midi):
                controlstr += f"#define RX_PIN {config_midi['rx_pin']} \n"
            if("tx_pin" in config_midi):
                controlstr += f"#define TX_PIN {config_midi['tx_pin']} \n"
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
                        midistr += f"\tmidi_input(adc::type_t::{elem.control_type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, scale::scale_t::{elem.scale}, &(midi_keyoff[{ref_idx}])), \n"
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


        ## Serial (UART) controls : group by USART peripheral into channels.
        if(len(self.serials_in) > 0 or len(self.serials_out) > 0):
            print("SERIAL=true")
            print(f"SERIAL_RX_INPUTS={len(self.serials_in)}")

            # instance -> {"rx": entry, "tx": entry, "idx": channel index}
            channels = {}
            channel_order = []

            def _serial_channel(direction, pin):
                try:
                    entry = daisy_uart_pins.resolve_uart(chip, pin, direction)
                except ValueError as e:
                    eprint(f"faust2daisy serial error: {e}")
                    sys.exit(1)
                inst = entry["instance"]
                if inst not in channels:
                    channels[inst] = {"rx": None, "tx": None,
                                      "idx": len(channel_order)}
                    channel_order.append(inst)
                channels[inst][direction] = entry
                return channels[inst]["idx"]

            for s in self.serials_in:
                s.channel = _serial_channel("rx", s.pin)
            for s in self.serials_out:
                s.channel = _serial_channel("tx", s.pin)

            # serial_in control objects + label routing table
            if(len(self.serials_in) > 0):
                # Shared (poly) variant fans one received value out to all voices.
                serial_in_t = "serial_in" if nvoices < 2 else f"shared_serial_in<{nvoices}>"
                controlstr += f"static std::array<{serial_in_t}, {len(self.serials_in)}> serial_input_list = {{\n"
                labels = "void init_serial_input_labels()\n{\n"
                count = 0
                for s in self.serials_in:
                    controlstr += f"\t{serial_in_t}(adc::type_t::{s.control_type}, {s.init}, {s.min}, {s.max}, {s.step}, scale::scale_t::{s.scale}, {count} ),\n"
                    labels += f"\tserial_input_labels[{count}] = string_view{{\"{s.label}\", {len(s.label)} }};\n"
                    count += 1
                controlstr += "};\n\n"
                labels += "}\n\n"
                controlstr += labels
            else:
                controlstr += "void init_serial_input_labels() {}\n\n"

            # serial_setup_channels(): one UART channel per peripheral, RX and/or
            # TX, each RX channel with its own DMA ring + line assembler.
            setup = "void serial_setup_channels()\n{\n"
            for inst in channel_order:
                ch  = channels[inst]
                idx = ch["idx"]
                rx  = ch["rx"]
                tx  = ch["tx"]
                if rx is not None:
                    setup += f"\tstatic uint8_t DMA_BUFFER_MEM_SECTION serial_ring_{idx}[SERIAL_RING_SIZE];\n"
                    setup += f"\tstatic serial_line_assembler serial_asm_{idx};\n"
                setup += "\t{\n"
                setup += "\t\tDaisyUartListener::ChannelConfig c = {};\n"
                setup += f"\t\tc.instance = {inst}; c.baud = {serial_baud};\n"
                if rx is not None:
                    setup += f"\t\tc.dmaRxRequest = {rx['dma_req']};\n"
                    setup += f"\t\tc.rxPort = {rx['port']}; c.rxPin = {rx['pin']}; c.rxAltFunc = {rx['af']};\n"
                    setup += f"\t\tc.ring = serial_ring_{idx}; c.ringSize = sizeof(serial_ring_{idx});\n"
                    setup += f"\t\tc.onReceive = serial_on_bytes; c.context = &serial_asm_{idx};\n"
                if tx is not None:
                    setup += f"\t\tc.txPort = {tx['port']}; c.txPin = {tx['pin']}; c.txAltFunc = {tx['af']};\n"
                setup += "\t\tserial_listener.addChannel(c);\n"
                setup += "\t}\n"
            setup += "}\n\n"
            controlstr += setup

            # tx controls: init_serial_outputs() fills the template-defined
            # serial_output_list[] (label + channel) for serial_tx_poll().
            print(f"SERIAL_TX_OUTPUTS={len(self.serials_out)}")
            outs = "void init_serial_outputs()\n{\n"
            for s in self.serials_out:
                outs += f"\tserial_output_list[{s.index}].label = \"{s.label}\"; serial_output_list[{s.index}].channel = {s.channel};\n"
            outs += "}\n\n"
            controlstr += outs

        ## Generate ADCs
            
        if(nvoices < 2):
            controlstr += f"static std::array<adc, {len(self.adcs)}> adc_list = {{ \n"
        else:
            controlstr += f"static std::array<shared_adc<{nvoices}>, {len(self.adcs)}> adc_list = {{ \n"
        if(len(self.adcs) > 0):
            prefix = ""
            for elem in self.adcs:
                if(nvoices < 2):
                    if(chip == "seed"):
                        controlstr += f"\tadc(adc::type_t::{elem.type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, scale::scale_t::{elem.scale}, {elem.pin_index}), \n"
                    elif(chip == "patchsm"):
                        pin = patchsm_pin_map.get(elem.pin_index)
                        if(pin == None): 
                            eprint(f"Error : the analog pin {elem.pin_index} does not exist in PatchSM")
                            sys.exit(1)
                        controlstr += f"\tadc(adc::type_t::{elem.type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, scale::scale_t::{elem.scale}, {pin}), \n"
                else: 
                    if(chip == "seed"): 
                        controlstr += f"\tshared_adc<{nvoices}>(adc::type_t::{elem.type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, scale::scale_t::{elem.scale}, {elem.pin_index}), \n"
                    elif(chip == "patchsm"):
                        pin = patchsm_pin_map.get(elem.pin_index)
                        if(pin == None): 
                            eprint(f"Error : the analog pin {elem.pin_index} does not exist in PatchSM")
                            sys.exit(1)
                        controlstr += f"\tshared_adc<{nvoices}>(adc::type_t::{elem.type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, scale::scale_t::{elem.scale}, {pin}), \n"
        controlstr += "}; \n"

        # Assign each ADC to a hardware DMA channel. With a platform config (e.g.
        # Daisy Patch), order the channels by the platform control number
        # (CV_in:N / knob:N) so that DMA channel i corresponds to physical knob
        # i+1. This matches the platform's own control order (libDaisy
        # DisplayControls, platform.controls[]...), which reads by channel index.
        # Without a config we keep the Faust emission order (identity mapping).
        def _platform_channel(pin):
            if config_ui is None:
                return None
            target = "adc:" + str(pin)
            for elem in config_ui:
                for k, v in elem.items():
                    if v == target:
                        m = re.search(r":([0-9]+)$", k)
                        if m:
                            return int(m.group(1)) - 1
            return None

        platform_channels = []
        if config_ui is not None and chip == "seed":
            platform_channels = [_platform_channel(e.pin_index) for e in self.adcs]
        # Use the platform order only if it is a clean 1:1 mapping (every ADC
        # resolved and no duplicates); otherwise fall back to emission order so
        # we never create gaps/collisions in the channel list.
        if (len(platform_channels) != len(self.adcs)
                or any(pc is None for pc in platform_channels)
                or len(set(platform_channels)) != len(platform_channels)):
            platform_channels = list(range(len(self.adcs)))
        n_channels = (max(platform_channels) + 1) if len(platform_channels) > 0 else 0

        controlstr += f"static std::array<uint8_t, {len(self.adcs)}> adc_platform_channel = {{ {', '.join(str(pc) for pc in platform_channels)} }}; \n"
        controlstr += f"std::array<daisy::AdcChannelConfig, {n_channels}> adc_config_list; \n\n"

        if(nvoices < 2):
            controlstr += f"static std::array<digi_input, {len(self.digis_in)}> digi_input_list {{\n"
        else: 
            controlstr += f"static std::array<shared_digi_input<{nvoices}>, {len(self.digis_in)}> digi_input_list {{\n"
        if(len(self.digis_in) > 0):
            prefix = ""
            eprint("CHIP = ", chip)
            if(chip == "patchsm"): 
                prefix = "daisy::patch_sm::DaisyPatchSM::"
            for elem in self.digis_in:
                if(nvoices < 2):
                    controlstr += f"\tdigi_input(adc::type_t::{elem.type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, {prefix}{elem.pin_index}), \n"
                else:
                    controlstr += f"\tshared_digi_input<{nvoices}>(adc::type_t::{elem.type}, {elem.init}, {elem.min}, {elem.max}, {elem.step}, {prefix}{elem.pin_index}), \n"
        controlstr += "}; \n\n"

        input_len = (len(self.adcs) + len(self.midis) + len(self.digis_in) + len(self.serials_in))
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
                elif(elem.type == "serial"):
                    inputstr += f"\t&serial_input_list[{elem.index}], \n"
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
                elif(elem.type == "serial"):
                    inputstr += f"\t&serial_input_list[{elem.index}], \n"
        
        inputstr += "}; \n\n"
        controlstr += inputstr


        last_chn = None
        if(len(self.dacs) > 0):
            controlstr += "constexpr bool dacs_used = true; \n"
        else:
            controlstr += "constexpr bool dacs_used = false; \n"
            if(chip == "seed"):
                controlstr +=  "static const daisy::DacHandle::Channel dac_chnls = daisy::DacHandle::Channel::BOTH; // dummy \n" 
            else: 
                controlstr += "static constexpr uint8_t dac_chnls = daisy::patch_sm::CV_OUT_BOTH; // dummy \n"

        if(nvoices < 2):
            controlstr += f"static std::array<dac, {len(self.dacs)}> dac_list = {{ \n"
        else:
            controlstr += f"static std::array<shared_dac<{nvoices}>, {len(self.dacs)}> dac_list = {{ \n"
        if(len(self.dacs) > 0):
            for elem in self.dacs:
                if(chip == "seed"): 
                    if(elem.channel == "A7"):
                        last_chn = "daisy::DacHandle::Channel::ONE" 
                    elif(elem.channel == "A8"):
                        last_chn = "daisy::DacHandle::Channel::TWO" 
                    else: 
                        eprint("DACs channels for Daisy Seed must be A7 or A8")
                        sys.exit(1)
                    if(nvoices < 2):
                        controlstr += f"\tdac({last_chn}, {elem.min}, {elem.max}, scale::scale_t::{elem.scale} ), \n"
                    else:
                        controlstr += f"\tshared_dac<{nvoices}>({last_chn}, {elem.min}, {elem.max}, scale::scale_t::{elem.scale} ), \n"
                elif(chip == "patchsm"):
                    if(elem.channel == "C1"): 
                        last_chn = "daisy::patch_sm::CV_OUT_1"
                    elif(elem.channel == "C10"):
                        last_chn = "daisy::patch_sm::CV_OUT_2"
                    else:
                        eprint("DACs channels for Daisy PatchSM must be C1 or C10")
                        sys.exit(1)
                    if(nvoices < 2):
                        controlstr += f"\tdac({last_chn}, {elem.min}, {elem.max}, scale::scale_t::{elem.scale} ), \n"
                    else:
                        controlstr += f"\tshared_dac<{nvoices}>({last_chn}, {elem.min}, {elem.max}, scale::scale_t::{elem.scale} ), \n"

        controlstr += "}; \n"
        if(len(self.dacs) > 0):
            if(len(self.dacs) == 2):
                if(chip == "seed"): 
                    controlstr += "static constexpr daisy::DacHandle::Channel dac_chnls = daisy::DacHandle::Channel::BOTH; \n" 
                elif(chip == "patchsm"):
                    controlstr += "static constexpr uint8_t dac_chnls = daisy::patch_sm::CV_OUT_BOTH; // dummy \n"
            else:
                if(chip == "seed"):
                    controlstr += f"static constexpr daisy::DacHandle::Channel dac_chnls = {last_chn}; \n"
                elif(chip == "patchsm"):
                    controlstr += f"static constexpr uint8_t dac_chnls = {last_chn}; \n"
            
        if(nvoices < 2):
            controlstr += f"static std::array<digi_output, {len(self.digis_out)}> digi_output_list = {{ \n"
        else:
            controlstr += f"static std::array<shared_digi_output<{nvoices}>, {len(self.digis_out)}> digi_output_list = {{ \n"
        prefix = ""
        if(chip == "patchsm"): 
            prefix = "daisy::patch_sm::DaisyPatchSM::"
        for elem in self.digis_out:
            softpwm = "true" if elem.softpwm else "false"
            if(nvoices < 2):
                controlstr += f"\tdigi_output({prefix}{elem.pin_index}, {softpwm}), \n"
            else:
                controlstr += f"\tshared_digi_output<{nvoices}>({prefix}{elem.pin_index}, {softpwm}), \n"
        controlstr += "}; \n\n"

        ## Hardware PWM outputs : group [pwm:PIN] controls by timer, one
        ## PWMHandle per timer, and wire each channel to pwm_output_list.
        if(len(self.pwms_out) > 0):
            print("PWM=true")
            print(f"PWM_OUTPUTS={len(self.pwms_out)}")
            pwm_prefix = "daisy::patch_sm::DaisyPatchSM::" if chip == "patchsm" else ""
            pwm_timers = []
            for po in self.pwms_out:
                if po.timer not in pwm_timers:
                    pwm_timers.append(po.timer)
            for t in pwm_timers:
                controlstr += f"static daisy::PWMHandle pwm_handle_{t.lower()};\n"
            controlstr += "\nvoid pwm_setup()\n{\n"
            for t in pwm_timers:
                controlstr += "\t{\n"
                controlstr += "\t\tdaisy::PWMHandle::Config cfg;\n"
                controlstr += f"\t\tcfg.periph = daisy::PWMHandle::Config::Peripheral::{t};\n"
                controlstr += "\t\tcfg.prescaler = 0; cfg.period = 8192;\n"
                controlstr += f"\t\tpwm_handle_{t.lower()}.Init(cfg);\n"
                controlstr += "\t}\n"
            for po in self.pwms_out:
                h = f"pwm_handle_{po.timer.lower()}"
                controlstr += "\t{\n"
                controlstr += "\t\tdaisy::PWMHandle::Channel::Config chcfg;\n"
                controlstr += f"\t\tchcfg.pin = {pwm_prefix}{po.pin};\n"
                controlstr += f"\t\t{h}.Channel{po.channel}().Init(chcfg);\n"
                controlstr += f"\t\tpwm_output_list[{po.index}].channel = &{h}.Channel{po.channel}();\n"
                controlstr += f"\t\tpwm_output_list[{po.index}].min = {po.min};\n"
                controlstr += f"\t\tpwm_output_list[{po.index}].max = {po.max};\n"
                controlstr += "\t}\n"
            controlstr += "}\n\n"

        outputstr = f"static std::array<control *, {len(self.outputs)}> output_list = {{ \n"
        for elem in self.outputs:
            if(elem.type == "dac"):
                outputstr += f"\t&(dac_list[{elem.index}]), \n"
            elif(elem.type == "digi_out"):
                outputstr += f"\t&(digi_output_list[{elem.index}]), \n"
            elif(elem.type == "serial"):
                outputstr += f"\t&(serial_output_list[{elem.index}]), \n"
            elif(elem.type == "pwm"):
                outputstr += f"\t&(pwm_output_list[{elem.index}]), \n"
        outputstr += "}; \n\n"

        controlstr += outputstr
        return arch.replace(control_tag, controlstr)

if("ui" in dsp_layout):
    scan = ui_scanner()
    for elem in dsp_layout["ui"]:
        scan.recursive_lookup(elem, config_ui)
        #scan.recursive_lookup(dsp_layout["ui"][0], config_ui)
    scan.check_pin_conflicts()
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


### Soundfile primitive support
# Look for "soundfile" widgets in the UI. If any, parse the referenced WAV
# files and inline them into daisy_soundfile.hpp, then tell the bash script
# (via USE_SOUNDFILE) to add the matching #define.
soundfiles = daisy_soundfile_gen.scan_soundfiles(dsp_layout)
if len(soundfiles) > 0:
    if soundfile_mode == "sd":
        # Samples are loaded from the SD card at runtime: nothing to inline,
        # just enable the SD reader in the architecture.
        print("USE_SD_SOUNDFILE=true")
        # Size the SDRAM arena to the referenced WAVs (if available at build
        # time); otherwise the architecture default is used.
        search_dirs = list(dict.fromkeys(
            [os.path.dirname(os.path.abspath(project_dir)), os.getcwd()]))
        arena = daisy_soundfile_gen.compute_sd_arena_bytes(soundfiles, search_dirs)
        if arena is not None:
            print("SD_SOUNDFILE_BYTES=%d" % arena)
    else:
        # WAV files are resolved relative to the DSP source directory and the cwd.
        search_dirs = list(dict.fromkeys(
            [os.path.dirname(os.path.abspath(project_dir)), os.getcwd()]))
        header_path = project_dir + "/daisy_soundfile.hpp"
        if daisy_soundfile_gen.generate_header(soundfiles, search_dirs, header_path):
            print("USE_SOUNDFILE=true")


arch_dest = project_dir + "/daisy_arch.cpp"
with open(arch_dest, "w") as file:
    file.write(arch)

print(f"NVOICES={nvoices}")
#print(nvoices) # To store output in bash NVOICES
sys.exit(0)


