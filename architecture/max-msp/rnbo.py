'''
 FAUST Architecture File
 Copyright (C) 2023 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either version 3
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
'''

from py2max.py2max import *

import argparse
import json

'''
Takes the DSP compiled as codebox file, the JSON file, an the output file.Codebox will be added in the codebox~ object.
Parsing the JSON file gives:
    - the list of parameters (button, checkbox, sliders, nentry) to be added as "set param" objects
    - the number of audio inputs/outputs to be added in the subpatch
'''

def gen_faust_rnbo(dsp_path, json_path, output_path):

    # Extracting items info
    def extract_items_info(json_data):
        def extract_from_ui(ui_items):
            info_list = []
            for item in ui_items:
                if "shortname" in item:
                    shortname = item["shortname"]
                    # slider and nentry
                    if "min" in item and "max" in item and "step" in item:
                        init_value = item["init"]
                        min_value = item["min"]
                        max_value = item["max"]
                        step_value = item["step"]
                        info_list.append({"shortname": shortname, "type": item["type"], "init": init_value, "min": min_value, "max": max_value, "step": step_value})
                    # button
                    if "type" in item and item["type"] == "button":
                        info_list.append({"shortname": shortname, "type": item["type"], "init": 0, "min": 0, "max": 1, "step": 1})
                    # checkbox
                    if "type" in item and item["type"] == "checkbox":
                        info_list.append({"shortname": shortname, "type": item["type"], "init": 0, "min": 0, "max": 1, "step": 1})
                # possibly recurse
                if "items" in item:
                    info_list.extend(extract_from_ui(item["items"]))
            return info_list

        # Extracting items info from the "ui" section
        info_list = []
        if "ui" in json_data:
            ui_section = json_data["ui"]
            info_list.extend(extract_from_ui(ui_section))

        return info_list
        
    # Create the patcher
    patcher = Patcher(output_path)
    
    # Faust generated patch
    patcher.add_comment('Faust generated RNBO patch, Copyright (c) 2023 Grame', patching_rect = [50.0, 20.0, 250.0, 50.0])
    
    # Add the audio driver output
    audio_out = patcher.add_textbox('ezdac~', patching_rect = [50.0, 100.0, 50.0, 50.0]);

    # Create RNBO object
    sbox = patcher.add_rnbo(patching_rect = [50.0, 60.0, 50.0, 50.0])

    # Create the subpatcher
    sp = sbox.subpatcher

    # Opening codebox file
    codebox_file = open(dsp_path)
    
    # Create codebox~ section
    codebox = sp.add_codebox_tilde(
        code = codebox_file.read(),                     # required
        patching_rect = [200.0, 200.0, 400.0, 400.0]   # optional
    )

    # Opening JSON file
    json_file = open(json_path)

    # Read the file and parse it
    json_data = json.loads(json_file.read())

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
    #print(items_info_list)
    for item in items_info_list:
        param = sp.add_textbox('set ' + item["shortname"])
        rect = param.patching_rect;
        if item["type"] == "button" or item["type"] == "checkbox":
            value = sp.add_textbox('toggle', patching_rect = [rect[0], rect[1]-25, 24.0, 24.0])
            sp.add_line(value, param)
            sp.add_line(param, codebox)
        else:
            value = sp.add_textbox('number~',
                mode = 1,
                sig = item["init"],
                minimum = item["min"],
                maximum = item["max"],
                patching_rect = [rect[0], rect[1]-25, rect[2], rect[3]])
            sp.add_line(value, param)
            sp.add_line(param, codebox)

    # And finally save the patch
    patcher.save()

# Parse command line
parser = argparse.ArgumentParser()
parser.add_argument('arg1', type=str, help='DSP file')
parser.add_argument('arg2', type=str, help='JSON file')
parser.add_argument('arg3', type=str, help='RNBO output file')
args = parser.parse_args()

# Create the Faust RNBO patch
gen_faust_rnbo(args.arg1, args.arg2, args.arg3)
