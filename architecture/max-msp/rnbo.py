from py2max.py2max import *

import argparse
import json

def gen_faust_rnbo(dsp_path, json_path, output_path):

    # Extracting items info
    def extract_items_info(json_data):
        def extract_from_ui(ui_items):
            info_list = []
            for item in ui_items:
                if "shortname" in item:
                    shortname = item["shortname"]
                    if "min" in item and "max" in item and "step" in item:
                        init_value = item["init"]
                        min_value = item["min"]
                        max_value = item["max"]
                        step_value = item["step"]
                        info_list.append({"shortname": shortname, "init": init_value, "min": min_value, "max": max_value, "step": step_value})
                if "items" in item:
                    info_list.extend(extract_from_ui(item["items"]))
            return info_list

        # Extracting items info from the "ui" section
        short_names = []
        if "ui" in json_data:
            ui_section = json_data["ui"]
            short_names.extend(extract_from_ui(ui_section))

        return short_names
        
    patcher = Patcher(output_path)
    
    # Faust generated patch
    patcher.add_comment('Faust generated RNBO patch, Copyright (c) 2023 Grame', patching_rect = [50.0, 20.0, 250.0, 50.0])
    
    # Add the audio driver output
    audio_out = patcher.add_textbox('ezdac~', patching_rect = [50.0, 100.0, 50.0, 50.0]);

    # Opening JSON file
    json_file = open(json_path)

    # Read the file and parse it
    json_data = json.loads(json_file.read())

    # Create RNBO object
    sbox = patcher.add_rnbo(patching_rect = [50.0, 60.0, 50.0, 50.0])

    # Create the subpatcher
    sp = sbox.subpatcher

    # Opening JSON file
    codebox_file = open(dsp_path)
    
    # Create codebox~ section
    codebox = sp.add_codebox_tilde(
        code = codebox_file.read(),					  # required
        patching_rect = [200.0, 200.0, 400.0, 400.0]   # optional
    )

    # Create inputs
    if "inputs" in json_data:
        num_inputs = json_data["inputs"]
  
    # Generating the lines of code for inputs
    for i in range(0, num_inputs):
        input = sp.add_textbox('in~ ' + str(i+1))
        sp.add_line(input, codebox, inlet=i)

    # Create outputs
    if "outputs" in json_data:
        num_outputs = json_data["outputs"]
  
    # Generating the lines of code for outputs
    for i in range(0, num_outputs):
        output = sp.add_textbox('out~ ' + str(i+1))
        sp.add_line(codebox, output, outlet=i)
        #patcher.add_line(sbox, audio_out, inlet=i)

    # Add parameter control
    items_info_list = extract_items_info(json_data)
    for item in items_info_list:
        param = sp.add_textbox('set ' + item["shortname"])
        rect = param.patching_rect;
        value = sp.add_textbox('number~', mode=1, comment = item["shortname"], comment_pos = 'below',
            patching_rect = [rect[0], rect[1]+25, rect[2], rect[3]])
        sp.add_line(value, param)
        sp.add_line(param, codebox)

    patcher.save()

# Parse command line
parser = argparse.ArgumentParser()
parser.add_argument('arg1', type=str, help='DSP file')
parser.add_argument('arg2', type=str, help='JSON file')
parser.add_argument('arg3', type=str, help='RNBO output file')
args = parser.parse_args()

# Create the Faust RNBO patch
gen_faust_rnbo(args.arg1, args.arg2, args.arg3)
