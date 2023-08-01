"""
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
"""

"""
Take the DSP name, the DSP compiled as codebox file, the JSON file, and the maxpat output file name. Codebox code will be added in the codebox~ object.
Parsing the JSON file gives:
    - the list of parameters (button, checkbox, sliders, nentry) to be added as "set param" objects
    - the number of audio inputs/outputs to be added in the subpatch
The maxpat file is generated with the following structure: 
    - rnbo~ object
        - subpatch
            - codebox~ object
            - possibly loadbang box and 'compile C++ and export' message
            - input boxes
            - output boxes
            - parameter boxes
            - lines between boxes
    - ezdac~ object
"""

from py2max.py2max import *
import argparse
import json


# Extracting items info
def extract_items_info(json_data):
    def extract_from_ui(ui_items):
        info_list = []
        for item in ui_items:
            shortname = item.get("shortname", "")
            item_type = item.get("type", "")

            # button and checkbox
            if item_type in ["button", "checkbox"]:
                info_list.append(
                    {
                        "shortname": shortname,
                        "type": item_type,
                        "init": 0,
                        "min": 0,
                        "max": 1,
                        "step": 1,
                    }
                )
            # slider and nentry
            elif "min" in item and "max" in item and "step" in item:
                init_value = item.get("init", 0)
                min_value = item["min"]
                max_value = item["max"]
                step_value = item["step"]
                info_list.append(
                    {
                        "shortname": shortname,
                        "type": item_type,
                        "init": init_value,
                        "min": min_value,
                        "max": max_value,
                        "step": step_value,
                    }
                )

            # possibly recurse
            if "items" in item:
                info_list.extend(extract_from_ui(item["items"]))
        return info_list

    # Extracting items info from the "ui" section
    if "ui" in json_data:
        ui_section = json_data["ui"]
        return extract_from_ui(ui_section)
    return []


def create_rnbo_patch(
    maxpat_path,
    dsp_name,
    codebox_code,
    items_info_list,
    compile,
    num_inputs,
    num_outputs,
):
    # Create the patcher
    patcher = Patcher(maxpat_path)

    # Faust generated patch
    patcher.add_comment(
        "Faust generated RNBO patch, Copyright (c) 2023 Grame",
        patching_rect=[50.0, 20.0, 250.0, 50.0],
    )

    # Add the audio driver output
    audio_out = patcher.add_textbox("ezdac~", patching_rect=[50.0, 370.0, 50.0, 50.0])
    sbox = patcher.add_rnbo(
        saved_object_attributes=dict(optimization="O3", title=dsp_name),
        patching_rect=[50.0, 320.0, 50.0, 80.0],
    )

    # Add loadbang and 'compile C++ and export' message
    if compile:
        load_bang = patcher.add_textbox(
            "loadbang", patching_rect=[100.0, 260.0, 150.0, 70.0]
        )
        compile_message = patcher.add_message(
            "export cpp-export cpp-code-export",
            patching_rect=[50.0, 280.0, 150.0, 70.0],
        )
        patcher.add_line(load_bang, compile_message)
        patcher.add_line(compile_message, sbox)

    # Create the subpatcher
    sp = sbox.subpatcher

    # Create codebox~ section
    codebox = sp.add_codebox_tilde(
        code=codebox_code, patching_rect=[200.0, 300.0, 400.0, 300.0]
    )

    # Workaround for C++ generation bug when no audio inputs
    # See: https://beta.cycling74.com/t/still-confused-on-how-to-use-parameters-in-rnbo-codebox-patches/1763/4
    if num_inputs == 0:
        sp.add_line(sp.add_textbox("sig~ 0"), codebox)

    # Generating the lines of code for inputs
    for i in range(num_inputs):
        input_box = sp.add_textbox(f"in~ {i + 1}")
        sp.add_line(input_box, codebox, inlet=i)

    # Generating the lines of code for outputs
    for i in range(num_outputs):
        output_box = sp.add_textbox(f"out~ {i + 1}")
        sp.add_line(codebox, output_box, outlet=i)

    # Add parameter control for button/checkbox and slider/nentry
    for item in items_info_list:
        shortname = item["shortname"]
        item_type = item["type"]

        # Add a global 'set' param object
        param = sp.add_textbox(f"set {shortname}")

        # button and checkbox use a 'toggle' object
        if item_type in ["button", "checkbox"]:
            # Upper level parameter control

            # patcher.add_comment(shortname)
            # param_wrap = patcher.add_textbox("toggle")

            toggle = patcher.add_textbox("toggle")
            param_wrap = patcher.add_textbox(
                "attrui",
                initial=0,
                minimum=0,
                maximum=1,
            )
            patcher.add_line(toggle, param_wrap)
            patcher.add_line(param_wrap, sbox)

            """
            value = sp.add_textbox(
                "toggle",
                patching_rect=[
                    param.patching_rect[0],
                    param.patching_rect[1] - 25,
                    24.0,
                    24.0,
                ],
            )
            """
            value = sp.add_textbox(
                f"param {shortname} 0 @min 0 @max 1",
            )

        #  slider and nentry use a 'param' object
        else:
            min_value = item["min"]
            max_value = item["max"]
            init_value = item["init"]

            # Upper level parameter control with a 'floatbox' object
            param_wrap = patcher.add_textbox(
                "attrui",
                initial=init_value,
                minimum=min_value,
                maximum=max_value,
            )
            patcher.add_line(param_wrap, sbox)

            """
            value = sp.add_textbox(
                "number~",
                mode=1,
                sig=init_value,
                minimum=min_value,
                maximum=max_value,
                patching_rect=[
                    param.patching_rect[0],
                    param.patching_rect[1] - 25,
                    param.patching_rect[2],
                    param.patching_rect[3],
                ],
            )
            """
            value = sp.add_textbox(
                f"param {shortname} {init_value} @min {min_value} @max {max_value}",
            )

        sp.add_line(value, param)
        sp.add_line(param, codebox)

    # And finally save the patch
    patcher.save()


# Generate RNBO patch
def gen_faust_rnbo(dsp_name, codebox_path, json_path, maxpat_path, compile):
    with open(codebox_path) as codebox_file:
        codebox_code = codebox_file.read()

    with open(json_path) as json_file:
        json_data = json.load(json_file)
        items_info_list = extract_items_info(json_data)
        num_inputs = json_data.get("inputs", 0)
        num_outputs = json_data.get("outputs", 0)

    create_rnbo_patch(
        maxpat_path,
        dsp_name,
        codebox_code,
        items_info_list,
        compile,
        num_inputs,
        num_outputs,
    )


# Parse command line
if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("arg1", type=str, help="DSP name")
    parser.add_argument("arg2", type=str, help="Codebox file")
    parser.add_argument("arg3", type=str, help="JSON file")
    parser.add_argument("arg4", type=str, help="RNBO maxpat file")
    parser.add_argument("arg5", type=str, help="compile")
    args = parser.parse_args()

    gen_faust_rnbo(args.arg1, args.arg2, args.arg3, args.arg4, args.arg5 == "True")
