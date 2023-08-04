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
Addionally, the C++ export path and filename can be specified, and the C++ code will be exported and compiled if 'compile' is True.
The 'test' option allows to generate a patch with the 'RB_xx' prefixed labels for the parameters, 
to be used with the C++ RNBO test application with the rnbo_dsp class.

Parsing the JSON file gives:
    - the list of parameters (button, checkbox, sliders, nentry) to be added as "set param" objects
    - the number of audio inputs/outputs to be added in the subpatch
The maxpat file is generated with the following structure: 
    - rnbo~ object
        - subpatch
            - codebox~ object
            - input boxes
            - output boxes
            - parameter boxes
            - lines between boxes
    - possibly loadbang box and 'compile C++ and export' machinery
    - ezdac~ object
"""

from py2max.py2max import *
import argparse
import json


# Extracting UI items info
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


# Creating the proper label for the parameter
def build_label(type, shortname, test):
    if test:
        if type == "button":
            return f"RB_Button_{shortname}"
        elif type == "checkbox":
            return f"RB_Checkbox_{shortname}"
        elif type == "hslider":
            return f"RB_HSlider_{shortname}"
        elif type == "vslider":
            return f"RB_VSlider_{shortname}"
        elif type == "nentry":
            return f"RB_NEntry_{shortname}"
        else:
            raise ValueError(f"Unknown type {type}")
    else:
        return shortname


# Create the RNBO maxpat file
def create_rnbo_patch(
    dsp_name,
    maxpat_path,
    export_path,
    cpp_filename,
    codebox_code,
    items_info_list,
    compile,
    test,
    num_inputs,
    num_outputs,
):
    # Create the patcher
    patcher = Patcher(maxpat_path)

    # Faust generated patch comment
    patcher.add_comment(
        "Faust generated RNBO patch, Copyright (c) 2023 Grame",
        patching_rect=[50.0, 10.0, 350.0, 100.0],
        fontsize=16,
    )

    # Create the audio driver output
    audio_out = patcher.add_textbox("ezdac~")

    # Create the rnbo~ object
    rnbo = patcher.add_rnbo(
        saved_object_attributes=dict(optimization="O3", title=dsp_name, dumpoutlet=1)
    )

    # Add loadbang and 'compile C++ and export' machinery
    if compile:
        load_bang = patcher.add_textbox("loadbang")
        dump_target_config = patcher.add_message(
            "dumptargetconfig cpp-export cpp-code-export"
        )
        tb = patcher.add_textbox("t b b s")
        set_path = patcher.add_message(
            f"set output_path {export_path}, set export_name {cpp_filename}"
        )
        dict1 = patcher.add_textbox("dict")
        route_dict = patcher.add_textbox("route dictionary")
        export = patcher.add_message("export cpp-export cpp-code-export $1")
        route = patcher.add_textbox("route targetconfig")

        # internal routing
        patcher.add_line(load_bang, dump_target_config)
        patcher.add_line(dump_target_config, rnbo)
        patcher.add_line(tb, dict1)
        patcher.add_line(tb, set_path, outlet=1)
        patcher.add_line(tb, dict1, outlet=2, inlet=1)
        patcher.add_line(set_path, dict1)
        patcher.add_line(dict1, route_dict)
        patcher.add_line(route_dict, export)
        patcher.add_line(route, tb)

        # routing with rnbo object
        patcher.add_line(export, rnbo)
        patcher.add_line(rnbo, route, outlet=1)

    # Create the codebox subpatcher
    sub_patch = rnbo.subpatcher

    # Create codebox~ section in the subpatcher
    codebox = sub_patch.add_codebox_tilde(
        code=codebox_code, patching_rect=[500.0, 500.0, 400.0, 200.0]
    )

    # Workaround for C++ generation bug when no audio inputs
    # See: https://beta.cycling74.com/t/still-confused-on-how-to-use-parameters-in-rnbo-codebox-patches/1763/4
    if num_inputs == 0:
        sub_patch.add_line(sub_patch.add_textbox("sig~ 0"), codebox)

    # Generating the lines of code for inputs
    for i in range(num_inputs):
        input_box = sub_patch.add_textbox(f"in~ {i + 1}")
        sub_patch.add_line(input_box, codebox, inlet=i)

    # Generating the lines of code for outputs
    for i in range(num_outputs):
        output_box = sub_patch.add_textbox(f"out~ {i + 1}")
        sub_patch.add_line(codebox, output_box, outlet=i)

    # Add parameter control for button/checkbox and slider/nentry
    for item in items_info_list:
        shortname = item["shortname"]
        item_type = item["type"]
        label = build_label(item_type, shortname, test)

        # Add a global 'set' param object
        param = sub_patch.add_textbox(f"set {label}")

        # button and checkbox use a 'toggle' object
        if item_type in ["button", "checkbox"]:
            # Upper level parameter control with a 'toggle' and 'attrui' objects
            toggle = patcher.add_textbox("toggle")
            param_wrap = patcher.add_textbox(
                "attrui",
                maxclass="attrui",
                attr=label,
                parameter_enable=1,
                minimum=0,
                maximum=1,
                saved_attribute_attributes={
                    "valueof": {
                        "parameter_initial": [label, 0],
                        "parameter_initial_enable": 1,
                    }
                },
            )
            patcher.add_line(toggle, param_wrap)
            patcher.add_line(param_wrap, rnbo)

            value = sub_patch.add_textbox(
                f"param {label} 0 @min 0 @max 1",
            )

        # slider and nentry use a 'param' object
        else:
            min_value = item["min"]
            max_value = item["max"]
            init_value = item["init"]
            steps_value = (max_value - min_value) / item["step"]

            # Upper level parameter control with a 'attrui' object
            param_wrap = patcher.add_textbox(
                "attrui",
                maxclass="attrui",
                attr=label,
                minimum=min_value,
                maximum=max_value,
                parameter_enable=1,
                saved_attribute_attributes={
                    "valueof": {
                        "parameter_initial": [label, init_value],
                        "parameter_initial_enable": 1,
                    }
                },
            )
            patcher.add_line(param_wrap, rnbo)

            value = sub_patch.add_textbox(
                # Doe nos work with @steps, with parameter values slightly different
                # f"param {label} {init_value} @min {min_value} @max {max_value} @steps {steps_value} ",
                f"param {label} {init_value} @min {min_value} @max {max_value}",
            )

        sub_patch.add_line(value, param)
        sub_patch.add_line(param, codebox)

    # And finally save the patch
    patcher.save()


# Open files and create the RNBO maxpat file
def load_files_create_rnbo_patch(
    dsp_name,
    codebox_path,
    json_path,
    maxpat_path,
    export_path,
    cpp_filename,
    compile,
    test,
):
    with open(codebox_path) as codebox_file:
        codebox_code = codebox_file.read()

    with open(json_path) as json_file:
        json_data = json.load(json_file)
        items_info_list = extract_items_info(json_data)
        num_inputs = json_data.get("inputs", 0)
        num_outputs = json_data.get("outputs", 0)

    create_rnbo_patch(
        dsp_name,
        maxpat_path,
        export_path,
        cpp_filename,
        codebox_code,
        items_info_list,
        compile,
        test,
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
    parser.add_argument("arg5", type=str, help="C++ export folder path")
    parser.add_argument("arg6", type=str, help="C++ export filename")
    parser.add_argument("arg7", type=str, help="compile")
    parser.add_argument("arg8", type=str, help="test")
    args = parser.parse_args()

    load_files_create_rnbo_patch(
        args.arg1,
        args.arg2,
        args.arg3,
        args.arg4,
        args.arg5,
        args.arg6,
        args.arg7 == "True",
        args.arg8 == "True",
    )
