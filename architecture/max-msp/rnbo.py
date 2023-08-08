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
    - the MIDI state to be used in the patch
    - the nvoices count to be used in the patch
The maxpat file is generated with the following structure: 
    - rnbo~ object for DSP
        - subpatch
            - codebox~ object
            - input boxes
            - output boxes
            - parameter boxes possibly with MIDI control
            - lines between boxes
    - possibly rnbo~ object for effect
    - possibly loadbang box and 'compile C++ and export' machinery
    - possibly midiin/midiout objects
    - ezdac~ object
"""

from py2max.py2max import *
import argparse
import json
import logging
import re


def get_midi_and_nvoices(json_data):
    """
    Extracts the MIDI state and nvoices count from the given JSON data.

    Args:
        json_data (dict): The JSON data in dictionary format.

    Returns:
        tuple: A tuple containing the MIDI state (True or False) and nvoices count (int).
               If the MIDI state or nvoices count is not present in the JSON, the corresponding
               value in the tuple will be None.
    """

    # Initialize variables to store the MIDI state and nvoices count
    midi_state = None
    nvoices = None

    # Extract the global meta section which is always present
    global_meta = json_data["meta"]
    for meta_item in global_meta:
        # Check for options
        if "options" in meta_item:
            options = meta_item["options"]
            # Extract MIDI state from options
            if "[midi:on]" in options:
                midi_state = True
            else:
                midi_state = False

            # Extract nvoices count from options
            nvoices_match = re.search(r"\[nvoices:(\d+)\]", options)
            if nvoices_match:
                nvoices = int(nvoices_match.group(1))
            break

    return midi_state, nvoices


def extract_items_info(json_data):
    """
    Extracts information about UI items from the given DSP JSON data.

    Args:
        json_data (dict): DSP JSON data.

    Returns:
        list: A list of dictionaries containing information about each UI item.
    """

    def extract_from_ui(ui_items):
        """
        Recursive helper function to extract UI items information.

        Args:
            ui_items (list): List of UI items.

        Returns:
            list: A list of dictionaries containing information about each UI item.
        """
        info_list = []
        for item in ui_items:
            shortname = item.get("shortname", "")
            item_type = item.get("type", "")

            # get MIDI information
            midi_info = []
            for meta_item in item.get("meta", []):
                if "midi" in meta_item:
                    midi_info.extend(meta_item["midi"].split())

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
                        "midi": midi_info,  # Include MIDI information as a list
                    }
                )
            # slider and nentry, and has "min", "max", and "step"
            elif all(key in item for key in ["min", "max", "step"]):
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
                        "midi": midi_info,  # Include MIDI information as a list
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
    return "RB_" + type + "_" + shortname if test else shortname


def add_polyphony_control(
    sub_patch, set_param_pitch, set_param_gain, set_param_gate, is_freq, is_gain
):
    """
    Adds polyphony control to a sub-patch for MIDI note input.

    This function provides the flexibility to control pitch and gain parameters either
    by frequency/MIDI key and gain/MIDI velocity. It takes parameters for setting pitch,
    gain, and gate parameters, along with flags to specify control methods. The MIDI
    notein and relevant processing elements are added to the sub-patch for polyphonic control.

    Args:
        sub_patch (SubPatch): The sub-patch to which the polyphony control elements will be added.
        set_param_pitch (TextBox): The element for setting the pitch parameter.
        set_param_gain (TextBox): The element for setting the gain parameter.
        set_param_gate (TextBox): The element for setting the gate parameter.
        is_freq (bool): Flag indicating whether pitch is controlled by frequency or MIDI key.
        is_gain (bool): Flag indicating whether gain is controlled by gain or MIDI velocity.
    """

    # Add MIDI notein
    note_in = sub_patch.add_textbox("notein")

    # Pitch can be controlled by frequency or MIDI key
    if is_freq:
        # MIDI key to frequency conversion
        mtof = sub_patch.add_textbox("mtof")
        # freq patching
        sub_patch.add_line(note_in, mtof)
        sub_patch.add_line(mtof, set_param_pitch)
    else:
        # MIDI key patching
        sub_patch.add_line(note_in, set_param_pitch)

    # Gain can be controlled by gain or MIDI velocity
    if is_gain:
        # MIDI velocity scaled to 0-1
        scale_gain = sub_patch.add_textbox("scale 0 127 0 1")
        # Velocity/gain patching
        sub_patch.add_line(note_in, scale_gain, outlet=1)
        sub_patch.add_line(scale_gain, set_param_gain)
    else:
        # MIDI velocity directly controls gain
        sub_patch.add_line(note_in, set_param_gain, outlet=1)

    # Velocity/gate patching
    gate_op = sub_patch.add_textbox("> 0")
    sub_patch.add_line(note_in, gate_op, outlet=1)
    sub_patch.add_line(gate_op, set_param_gate)


def add_midi_control(item, sub_patch, set_param, codebox):
    """
    Adds MIDI control to the subpatch.

    This function handles the MIDI control for both input and output in the subpatch.
    It checks the MIDI control type and prepares the necessary MIDI input and output messages.
    The scaling for MIDI input and output messages is also defined based on the control type.

    Args:
        item (dict): The dictionary containing information about the UI item.
        sub_patch (Patcher): The subpatcher object to which MIDI control will be added.
        set_param (Textbox): The 'set' param object for the UI item.
        codebox (Textbox): The codebox~ object in the subpatcher.

    Returns:
        bool: True if MIDI control type is supported and added successfully, possible logs an error and return False otherwise.
    """

    # Get the MIDI information from the item dictionary
    midi_info = item.get("midi", None)
    if not midi_info:
        return False

    # Define the Faust to RNBO syntax mapping for both MIDI input and output
    midi_mapping = {
        "ctrl": {"in": "ctlin", "out": "ctlout"},
        "chanpress": {"in": "touchin", "out": "touchout"},
        "keyon": {"in": "notein", "out": "noteout"},
        "keyoff": {"in": "notein", "out": "noteout"},
        "key": {"in": "notein", "out": "noteout"},
        "pitchwheel": {"in": "bendin @bendmode 1", "out": "bendout @bendmode 1"},
        "pgm": {"in": "pgmin", "out": "pgmout"},
    }

    # Check if the MIDI control type is supported
    midi_type = midi_info[0]
    if midi_type not in midi_mapping:
        logging.error(f"MIDI control type '{midi_type}' not supported")
        return False

    # Prepare the MIDI input and output messages
    midi_type = midi_info[0]
    midi_args = " ".join(midi_info[1:])
    # TODO: handle all channels case: Faust 0 => RNBO -1
    midi_in = sub_patch.add_textbox(f"{midi_mapping[midi_type]['in']} {midi_args}")
    midi_out = sub_patch.add_textbox(f"{midi_mapping[midi_type]['out']} {midi_args}")

    # Scaling for MIDI input and output messages
    # Pitchwheel case using @bendmode 1 (-1, 1) mode
    if midi_type == "pitchwheel":
        scaling_in = f"scale -1 1 {item['min']} {item['max']}"
        scaling_out = f"scale {item['min']} {item['max']} -1 -1"
    # General case
    else:
        scaling_in = f"scale 0 127 {item['min']} {item['max']}"
        scaling_out = f"scale {item['min']} {item['max']} 0 127"

    # Create the scaling boxes
    scaling_in_box = sub_patch.add_textbox(scaling_in)
    # scaling_out_box = sub_patch.add_textbox(scaling_out)

    # Connect the input objects
    sub_patch.add_line(midi_in, scaling_in_box)
    sub_patch.add_line(scaling_in_box, set_param)

    # Connect the output objects
    # sub_patch.add_line(codebox, scaling_out_box)
    # sub_patch.add_line(scaling_out_box, midi_out)
    return True


def add_rnbo_object(
    patcher,
    dsp_name,
    codebox_code,
    items_info_list,
    midi,
    nvoices,
    test,
    num_inputs,
    num_outputs,
):
    """
    Adds DSP elements, routing, and parameter controls for a DSP to the given Patcher object.

    Parameters:
        patcher (Patcher): The Patcher object to which DSP elements and controls will be added.
        dsp_name (str): The name of the DSP.
        codebox_code (str): The code to be executed by the DSP effect.
        items_info_list (list): A list of dictionaries containing information about UI items.
        midi (bool): Indicates whether MIDI control is enabled.
        nvoices (int): The number of polyphony voices.
        num_inputs (int): The number of audio input channels.
        num_outputs (int): The number of audio output channels.

    Returns:
        rnbo (Object): The added rnbo~ object representing the DSP.
    """

    # Create the rnbo~ object
    rnbo_attributes = {"optimization": "O3", "title": dsp_name, "dumpoutlet": 1}
    # Add the polyphony attribute only if midi is True and nvoices > 0
    if midi and nvoices > 0:
        rnbo_attributes["polyphony"] = nvoices

    # Add the MIDI inlet only if midi is True
    inlets = max(1, num_inputs) + 1 if midi else max(1, num_inputs)
    # Port message dump message outlets are always added, add the MIDI outlet only if midi is True
    outlets = max(1, num_outputs) + 3 if midi else max(1, num_outputs) + 2
    # print(inlets, outlets)

    # Create the rnbo~ object
    rnbo = patcher.add_rnbo(
        title=dsp_name,
        numinlets=inlets,
        numoutlets=outlets,
        saved_object_attributes=rnbo_attributes,
    )

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

    # Parameter for polyphony handling
    set_param_pitch = None
    set_param_gain = None
    set_param_gate = None
    is_freq = False
    is_gain = False

    # MIDI controlled parameters
    has_midi = False

    # Add parameter control for button/checkbox and slider/nentry, annlyse for polyphony
    for item in items_info_list:
        shortname = item["shortname"]
        item_type = item["type"]
        label = build_label(item_type, shortname, test)

        # Add a global 'set' param object
        set_param = sub_patch.add_textbox(f"set {label}")

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

            param = sub_patch.add_textbox(
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

            param = sub_patch.add_textbox(
                # Does not work with @steps, with parameter values slightly different
                # f"param {label} {init_value} @min {min_value} @max {max_value} @steps {steps_value} ",
                f"param {label} {init_value} @min {min_value} @max {max_value}",
            )

        # Add a line to connect the parameter control to the 'set' param object
        sub_patch.add_line(param, set_param)
        # Add a line to connect the 'set' param object to the codebox
        sub_patch.add_line(set_param, codebox)

        # Analyze the parameter shortname for polyphony handing
        if midi and nvoices > 0:
            if shortname.endswith("freq"):
                set_param_pitch = set_param
                is_freq = True
            elif shortname.endswith("key"):
                set_param_pitch = set_param
                is_freq = False
            elif shortname.endswith("gain"):
                set_param_gain = set_param
                is_gain = True
            elif shortname.endswith("velocity"):
                set_param_gain = set_param
                is_gain = False
            elif shortname.endswith("gate"):
                set_param_gate = set_param

        # Possibly add MIDI input/output control
        if midi:
            has_midi = has_midi or add_midi_control(item, sub_patch, set_param, codebox)

    # After analyzing all UI items to get freq/gain/gate controls, possibly add polyphony control
    if midi and set_param_pitch and set_param_gain and set_param_gate:
        add_polyphony_control(
            sub_patch, set_param_pitch, set_param_gain, set_param_gate, is_freq, is_gain
        )
        has_midi = True

    # Possibly add MIDI input/output control in the global patcher
    if midi and has_midi:
        midi_in = patcher.add_textbox("midiin")
        midi_out = patcher.add_textbox("midiout")
        # See: https://rnbo.cycling74.com/learn/midi-in-rnbo
        # MIDI inlet will always be the right-most inlet, and inlets numbering starts at 0
        sub_patch.add_line(midi_in, rnbo, inlet=rnbo.numinlets - 1)
        # MIDI outlet will always be the third from the right-most outlet, and outlets numbering starts at 0
        sub_patch.add_line(rnbo, midi_out, outlet=rnbo.numoutlets - 3)

    return rnbo


def connect_dsp_effect(
    patcher, dsp_rnbo, effect_rnbo, dsp_num_outputs, effect_num_inputs
):
    """
    Connects a DSP module to an effect module within a patcher.

    Args:
        patcher (Patcher): The patcher object representing the audio patcher.
        dsp_rnbo (Module): The DSP module's RNBO.
        effect_rnbo (Module): The effect module's RNBO.
        dsp_num_outputs (int): Number of output channels of the DSP module.
        effect_num_inputs (int): Number of input channels of the effect module.

    Notes:
        This function establishes audio connections between the specified DSP module
        and effect module by adding appropriate lines to the patcher.

        Implementing this equivalent Faust written logic:
            connect(1,1) = _;
            connect(2,2) = _,_;
            connect(1,2) = _ <: _,_;
            connect(2,1) = _,_ :> _;
    """

    print(f"Connecting DSP to effect: {dsp_num_outputs} -> {effect_num_inputs}")

    match (dsp_num_outputs, effect_num_inputs):
        case (1, 1):
            print("1 -> 1")
            patcher.add_line(dsp_rnbo, effect_rnbo)
        case (1, 2):
            print("1 -> 2")
            patcher.add_line(dsp_rnbo, effect_rnbo, inlet=0, outlet=0)
            patcher.add_line(dsp_rnbo, effect_rnbo, inlet=1, outlet=0)
        case (2, 1):
            print("2 -> 1")
            patcher.add_line(dsp_rnbo, effect_rnbo, inlet=0, outlet=0)
            patcher.add_line(dsp_rnbo, effect_rnbo, inlet=0, outlet=1)
        case (2, 2):
            print("2 -> 2")
            patcher.add_line(dsp_rnbo, effect_rnbo, inlet=0, outlet=0)
            patcher.add_line(dsp_rnbo, effect_rnbo, inlet=1, outlet=1)


def add_compile_test(patcher, rnbo, export_path, cpp_filename):
    """
    Adds a series of objects and routing connections to the given Patcher object in order to set up a compile test.

    Parameters:
        patcher (Patcher): The Patcher object to which objects and routing connections will be added.
        rnbo (Object): The target object for routing.
        export_path (str): The path to the directory where the export will be saved.
        cpp_filename (str): The desired filename for the exported CPP code.

    Returns:
        None

    Example:
        add_compile_test(my_patcher, my_rnbo, "/path/to/export", "my_exported_code.cpp")
    """
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


def create_rnbo_patch(
    dsp_name,
    maxpat_path,
    export_path,
    cpp_filename,
    dsp_codebox_code,
    dsp_items_info_list,
    dsp_num_inputs,
    dsp_num_outputs,
    effect_codebox_code,
    effect_items_info_list,
    effect_num_inputs,
    effect_num_outputs,
    midi,
    nvoices,
    compile,
    test,
):
    """
    This function creates an RNBO Max patcher with the specified parameters.

    Parameters:
    - dsp_name (str): The name of the DSP.
    - maxpat_path (str): The path where the Max patcher will be created.
    - export_path (str): The path for exporting the C++ code.
    - cpp_filename (str): The filename for the exported C++ code.
    - dsp_codebox_code (str): The code for the DSP codebox~ section in the subpatcher.
    - dsp_items_info_list (list): A list of dictionaries containing information about the items to be added.
    - dsp_num_inputs (int): The number of DSP audio inputs.
    - dsp_num_outputs (int): The number of DSP audio outputs.
    - effect_codebox_code (str): The code for the effect codebox~ section in the subpatcher.
    - effect_items_info_list (list): A list of dictionaries containing information about the items to be added.
    - effect_num_inputs (int): The number of effect audio inputs.
    - effect_num_outputs (int): The number of effect audio outputs.
    - midi (bool): A flag indicating whether to include MIDI input/output control.
    - nvoices (int): The number of voices.
    - compile (bool): A flag indicating whether to include the C++ compilation and export machinery.
    - test (bool): A flag indicating whether the patch is for testing purposes.
    """

    # Create the patcher
    patcher = Patcher(maxpat_path)

    # Faust generated patch comment
    patcher.add_comment(
        "Faust generated RNBO patch, Copyright (c) 2023 Grame",
        patching_rect=[50.0, 10.0, 350.0, 100.0],
        fontsize=16,
    )

    # Create the DSP rnbo~ object
    dsp_rnbo = add_rnbo_object(
        patcher,
        dsp_name,
        dsp_codebox_code,
        dsp_items_info_list,
        midi,
        nvoices,
        test,
        dsp_num_inputs,
        dsp_num_outputs,
    )

    # Possibly create and connect the effect rnbo~ object
    if effect_codebox_code:
        effect_rnbo = add_rnbo_object(
            patcher,
            "Effect",
            effect_codebox_code,
            effect_items_info_list,
            midi,
            -1,
            test,
            effect_num_inputs,
            effect_num_outputs,
        )

        # Connect the DSP and effect rnbo~ objects
        # connect_dsp_effect(
        #     patcher,
        #     dsp_rnbo,
        #     effect_rnbo,
        #     dsp_num_outputs,
        #     effect_num_inputs,
        # )

    # Add loadbang and 'compile C++ and export' machinery
    if compile:
        add_compile_test(patcher, dsp_rnbo, export_path, cpp_filename)

    # Create the audio driver output
    audio_out = patcher.add_textbox("ezdac~")

    # And finally save the patch
    patcher.save()


def load_files_create_rnbo_patch(
    dsp_name,
    dsp_codebox_path,
    dsp_json_path,
    effect_codebox_path,
    effect_json_path,
    maxpat_path,
    export_path,
    cpp_filename,
    midi,
    nvoices,
    compile,
    test,
):
    """
    This function loads the codebox and JSON files, extracts relevant data, and creates the RNBO Max patch.

    Parameters:
    - dsp_name (str): The name of the DSP.
    - dsp_codebox_path (str): The path to the DSP codebox file.
    - dsp_json_path (str): The path to the DSP JSON file containing items info.
    - effect_codebox_path (str): The path to the effect codebox file.
    - effect_json_path (str): The path to the effect JSON file containing items info.
    - maxpat_path (str): The path where the Max patcher will be created.
    - export_path (str): The path for exporting the C++ code.
    - cpp_filename (str): The filename for the exported C++ code.
    - midi (bool): A flag indicating whether to include MIDI input/output control.
    - nvoices (int): The number of voices.
    - compile (bool): A flag indicating whether to include the C++ compilation and export machinery.
    - test (bool): A flag indicating whether the patch is for testing purposes.
    """

    with open(dsp_codebox_path) as codebox_file:
        dsp_codebox_code = codebox_file.read()

    with open(dsp_json_path) as json_file:
        json_data = json.load(json_file)
        dsp_items_info_list = extract_items_info(json_data)
        # print(dsp_items_info_list)
        dsp_num_inputs = json_data.get("inputs", 0)
        dsp_num_outputs = json_data.get("outputs", 0)
        options = get_midi_and_nvoices(json_data)

    if effect_codebox_path is not None and effect_json_path is not None:
        with open(effect_codebox_path) as codebox_file:
            effect_codebox_code = codebox_file.read()

        with open(effect_json_path) as json_file:
            json_data = json.load(json_file)
            effect_items_info_list = extract_items_info(json_data)
            # print(effect_items_info_list)
            effect_num_inputs = json_data.get("inputs", 0)
            effect_num_outputs = json_data.get("outputs", 0)

        create_rnbo_patch(
            dsp_name,
            maxpat_path,
            export_path,
            cpp_filename,
            dsp_codebox_code,
            dsp_items_info_list,
            dsp_num_inputs,
            dsp_num_outputs,
            effect_codebox_code,
            effect_items_info_list,
            effect_num_inputs,
            effect_num_outputs,
            # Take either the midi parameter or options[0] (= the midi state found in the JSON file)
            midi or options[0],
            # Take either the given nvoices, otherwise options[1](= the number of voices found in the JSON file) or -1
            nvoices if nvoices > 0 else options[1] if options[1] else -1,
            compile,
            test,
        )
    else:
        create_rnbo_patch(
            dsp_name,
            maxpat_path,
            export_path,
            cpp_filename,
            dsp_codebox_code,
            dsp_items_info_list,
            dsp_num_inputs,
            dsp_num_outputs,
            None,
            None,
            -1,
            -1,
            # Take either the midi parameter or options[0] (= the midi state found in the JSON file)
            midi or options[0],
            # Take either the given nvoices, otherwise options[1](= the number of voices found in the JSON file) or -1
            nvoices if nvoices > 0 else options[1] if options[1] else -1,
            compile,
            test,
        )


# Main function to parse command-line arguments and run the script
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("arg1", type=str, help="DSP name")
    parser.add_argument("arg2", type=str, help="DSP codebox file")
    parser.add_argument("arg3", type=str, help="DSP JSON file")
    parser.add_argument("--arg4", type=str, help="Effect codebox file")  # optional
    parser.add_argument("--arg5", type=str, help="Effect JSON file")  # optional
    parser.add_argument("arg6", type=str, help="RNBO maxpat file")
    parser.add_argument("arg7", type=str, help="C++ export folder path")
    parser.add_argument("arg8", type=str, help="C++ export filename")
    parser.add_argument("arg9", type=str, help="MIDI control")
    parser.add_argument("arg10", type=int, help="nvoices")
    parser.add_argument("arg11", type=str, help="compile")
    parser.add_argument("arg12", type=str, help="test")
    args = parser.parse_args()

    load_files_create_rnbo_patch(
        args.arg1,
        args.arg2,
        args.arg3,
        args.arg4,
        args.arg5,
        args.arg6,
        args.arg7,
        args.arg8,
        args.arg9 == "True",
        args.arg10,
        args.arg11 == "True",
        args.arg12 == "True",
    )


# Parse command line
if __name__ == "__main__":
    main()
