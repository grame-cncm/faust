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
Take the DSP name, the DSP compiled as codebox file and its associated JSON file, possibly the effect
compiled as codebox file and its associated JSON file, and the maxpat output file name.
Addionally, the C++ export path and filename can be specified, and the C++ code 
will be exported and compiled if 'compile' is True.
The 'test' option allows to generate a patch with the 'RB_xx' prefixed labels for the parameters, 
to be used with the C++ RNBO test application with the rnbo_dsp class. 
The 'subpatcher' option allows to generate sub-patch as foo.rnbopat files.

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
    - the subpatch can be generated as flat or as a foo.rnbopat file then loaded as a 'p' subpatcher
    - the polyphony control is added if the MIDI state is True and the nvoices count is > 0. Effect is added as a 'p' subpatcher.
    - possibly loadbang box and 'compile C++ and export' machinery
    - possibly midiin/midiout objects
    - dac~ object and possibly adc~ object (if the DSP has inputs)
"""

from py2max.py2max import *
import argparse
import json
import logging
import re
from typing import Dict, List, Tuple, Optional


def get_midi_and_nvoices(json_data: dict) -> Tuple[bool, int]:
    """
    Extracts the MIDI state and nvoices count from the given JSON data.

    Args:
        json_data (dict): The JSON data in dictionary format.

    Returns:
        Tuple[bool, int]: A tuple containing the MIDI state (True or False) and nvoices count (int).
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
            midi_state = "[midi:on]" in options
            # Extract nvoices count from options
            nvoices_match = re.search(r"\[nvoices:(\d+)\]", options)
            if nvoices_match:
                nvoices = int(nvoices_match.group(1))
            break

    return midi_state, nvoices


def extract_items_info(json_data: dict) -> List[dict]:
    """
    Extracts information about UI items from the given DSP JSON data.

    Args:
        json_data (dict): DSP JSON data.

    Returns:
         List[dict]: A list of dictionaries containing information about each UI item.
    """

    def extract_from_ui(ui_items: List) -> List[dict]:
        """
        Recursive helper function to extract UI items information.

        Args:
            ui_items (List): List of UI items.

        Returns:
            List: A list of dictionaries containing information about each UI item.
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
            # bargraph with "min", "max"
            elif item_type in ["vbargraph", "hbargraph"]:
                info_list.append(
                    {
                        "shortname": shortname,
                        "type": item_type,
                        "min": item["min"],
                        "max": item["max"],
                        "midi": midi_info,  # Include MIDI information as a list
                    }
                )
            # slider and nentry, and has "min", "max", and "step"
            elif all(key in item for key in ["min", "max", "step"]):
                info_list.append(
                    {
                        "shortname": shortname,
                        "type": item_type,
                        "init": item.get("init", 0),
                        "min": item["min"],
                        "max": item["max"],
                        "step": item["step"],
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
def build_label(item_type: str, shortname: str, test: bool) -> str:
    if test:
        return "RB_" + item_type + "_" + shortname
    elif shortname[0].isdigit():
        return "cb_" + shortname
    else:
        return shortname


def add_polyphony_control(
    sub_patch: Patcher,
    set_param_pitch: Box,
    set_param_gain: Box,
    set_param_gate: Box,
    is_freq: bool,
    is_gain: bool,
) -> None:
    """
    Adds polyphony control to a sub-patch for MIDI note input.

    This function provides the flexibility to control pitch and gain parameters either
    by frequency/MIDI key and gain/MIDI velocity. It takes parameters for setting pitch,
    gain, and gate parameters, along with flags to specify control methods. The MIDI
    notein and relevant processing objects are added to the sub-patch for polyphonic control.

    Args:
        sub_patch (Patcher): The sub-patch to which the polyphony control elements will be added.
        set_param_pitch (Box): The objects for setting the pitch parameter.
        set_param_gain (Box): The objects for setting the gain parameter.
        set_param_gate (Box): The objects for setting the gate parameter.
        is_freq (bool): Flag indicating whether pitch is controlled by frequency or MIDI key.
        is_gain (bool): Flag indicating whether gain is controlled by gain or MIDI velocity.

    Returns:
        None
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


def add_midi_control(
    item: dict,
    sub_patch: Patcher,
    codebox: Box,
    param: Optional[Box] = None,
    set_param: Optional[Box] = None,
    change: Optional[Box] = None,
) -> bool:
    """
    Adds MIDI control to the subpatch.

    This function handles the MIDI control for both input and output in the subpatch.
    It checks the MIDI control type and prepares the necessary MIDI input and output messages.
    The scaling for MIDI input and output messages is also defined based on the control type.

    Args:
        item (dict): The dictionary containing information about the UI item.
        sub_patch (Patcher): The subpatcher object to which MIDI control will be added.
        codebox (Box): The codebox~ object in the subpatcher.
        param (Optional[Box]): The param object for the input UI items.
        set_param (Optional[Box]): The 'set' param object for the input UI items.
        change (Optional[Box]): The change object for bargraph UI items.

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
        "pitchwheel": {"in": "bendin @bendmode 2", "out": "bendout @bendmode 2"},
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

    # Scaling for MIDI input and output messages
    # Pitchwheel case using @bendmode 2 (-8192, 8192) mode
    if midi_type == "pitchwheel":
        scaling_in = f"scale -8192 8192 {item['min']} {item['max']}"
        scaling_out = f"scale {item['min']} {item['max']} -8192 8192"
    # General case
    else:
        scaling_in = f"scale 0 127 {item['min']} {item['max']}"
        scaling_out = f"scale {item['min']} {item['max']} 0 127"

    # Connect the input objects
    if set_param:
        # Create MIDI object (TODO: handle all channels case: Faust 0 => RNBO -1)
        midi_in = sub_patch.add_textbox(f"{midi_mapping[midi_type]['in']} {midi_args}")
        midi_out = sub_patch.add_textbox(
            f"{midi_mapping[midi_type]['out']} {midi_args}"
        )
        # Create the scaling box
        scaling_in_box = sub_patch.add_textbox(scaling_in)
        scaling_out_box = sub_patch.add_textbox(scaling_out)
        # Input connections
        sub_patch.add_line(midi_in, scaling_in_box)
        sub_patch.add_line(scaling_in_box, set_param)
        # Output connections
        sub_patch.add_line(param, scaling_out_box)
        sub_patch.add_line(scaling_out_box, midi_out)

    # Connect the output objects
    if change:
        # Create MIDI object (TODO: handle all channels case: Faust 0 => RNBO -1)
        midi_out = sub_patch.add_textbox(
            f"{midi_mapping[midi_type]['out']} {midi_args}"
        )
        # Create the scaling box
        scaling_out_box = sub_patch.add_textbox(scaling_out)
        # Connections
        sub_patch.add_line(change, scaling_out_box)
        sub_patch.add_line(scaling_out_box, midi_out)

    return True


def generate_io_info(
    midi: bool, num_inputs: int, num_outputs: int
) -> Tuple[int, int, dict, dict]:
    """
    Generate inlet and outlet information dictionaries based on the number of inputs and outputs.

    Args:
        midi (bool): A flag indicating whether to include MIDI inlet/outlet.
        num_inputs (int): The number of input signals.
        num_outputs (int): The number of output signals.

    Returns:
        Tuple: A tuple containing four elements:
            - inlets (int): Total number of inlet ports, including MIDI if applicable.
            - outlets (int): Total number of outlet ports, including MIDI if applicable.
            - inletInfo (dict): Dictionary containing information about the input ports.
            - outletInfo (dict): Dictionary containing information about the output ports.
    """
    inletInfo = {"IOInfo": []}
    outletInfo = {"IOInfo": []}

    if midi:
        inlets = max(1, num_inputs) + 1
        # First inlets are signals
        for i in range(1, num_inputs + 1):
            io_entry = {"comment": "", "index": i, "tag": f"in{i}", "type": "signal"}
            inletInfo["IOInfo"].append(io_entry)
        # Last inlet is MIDI
        io_entry = {
            "comment": "",
            "index": inlets,
            "tag": f"in{inlets}",
            "type": "midi",
        }
        inletInfo["IOInfo"].append(io_entry)
        # The MIDI outlet is added, then port message and dump outlets are always added
        outlets = max(1, num_outputs) + 3
        # First outlets are signals
        for i in range(1, num_outputs + 1):
            io_entry = {"comment": "", "index": i, "tag": f"out{i}", "type": "signal"}
            outletInfo["IOInfo"].append(io_entry)
        # Next outlet is MIDI
        io_entry = {"comment": "", "index": i, "tag": f"out{i}", "type": "midi"}
        outletInfo["IOInfo"].append(io_entry)
    else:
        inlets = max(1, num_inputs)
        # All inlets are signals
        for i in range(1, num_inputs + 1):
            io_entry = {"comment": "", "index": i, "tag": f"in{i}", "type": "signal"}
            inletInfo["IOInfo"].append(io_entry)
        # Port message and dump outlets are always added
        outlets = max(1, num_outputs) + 2
        # All outlets are signals
        for i in range(1, num_outputs + 1):
            io_entry = {"comment": "", "index": i, "tag": f"out{i}", "type": "signal"}
            outletInfo["IOInfo"].append(io_entry)

    return inlets, outlets, inletInfo, outletInfo


def add_codebox_object(
    patcher: Patcher,
    sub_patcher: Patcher,
    rnbo: Box,
    prefix: str,
    codebox_code: str,
    items_info_list: List[dict],
    midi: bool,
    nvoices: int,
    test: bool,
    num_inputs: int,
    num_outputs: int,
) -> None:
    """
    Add a codebox~ object and parameter controls to a Max/MSP subpatcher.

    This function sets up a codebox~ object and associated parameter controls
    within a Max/MSP subpatcher. It generates input and output lines, handles
    UI elements like buttons, sliders, and MIDI controls, and provides polyphony
    control when applicable.

    Parameters:
        patcher (Patcher): The main Max/MSP patcher.
        sub_patcher (Patcher): The subpatcher where the codebox~ will be added.
        rnbo (Box): The rnbo object.
        prefix (str): The prefix to be added to the label.
        codebox_code (str): The code to be added to the codebox~.
        items_info_list (list[dict]): List of dictionaries containing UI item information.
        midi (bool): Whether MIDI controls should be added.
        nvoices (int): Number of voices for polyphony control.
        test (bool): Whether the code is for testing purposes.
        num_inputs (int): Number of audio inputs.
        num_outputs (int): Number of audio outputs.
    """
    # Create codebox~ section in the subpatcher
    codebox = sub_patcher.add_codebox_tilde(
        code=codebox_code, patching_rect=[500.0, 500.0, 400.0, 200.0]
    )

    # Generating the lines of code for inputs
    for i in range(num_inputs):
        input_box = sub_patcher.add_textbox(f"in~ {i + 1}")
        sub_patcher.add_line(input_box, codebox, inlet=i)

    # Generating the lines of code for outputs
    for i in range(num_outputs):
        output_box = sub_patcher.add_textbox(f"out~ {i + 1}")
        sub_patcher.add_line(codebox, output_box, outlet=i)

    # Parameter for polyphony handling
    set_param_pitch = None
    set_param_gain = None
    set_param_gate = None
    is_freq = False
    is_gain = False

    # Counter of bargraph to be used to outlet computation
    bargraph_count = 0

    # Add parameter control for button/checkbox and slider/nentry, annlyse for polyphony
    for item in items_info_list:
        shortname = item["shortname"]
        item_type = item["type"]
        label = build_label(item_type, shortname, test)
        label_path = prefix + label
        # print(label_path)

        # button and checkbox use a 'toggle' object
        if item_type in ["button", "checkbox"]:
            # Add a global 'set' param object
            set_param = sub_patcher.add_textbox(f"set {label}")

            # Upper level parameter control with a 'toggle' and 'attrui' objects
            toggle = patcher.add_textbox("toggle")
            # Set the position and size of the toggle button on the canvas
            toggle.patching_rect = [
                toggle.patching_rect[0],
                toggle.patching_rect[1],
                24.0,
                24.0,
            ]
            param_wrap = patcher.add_textbox(
                "attrui",
                maxclass="attrui",
                attr=label,
                parameter_enable=1,
                minimum=0,
                maximum=1,
                saved_attribute_attributes={
                    "valueof": {
                        "parameter_initial": [label_path, 0],
                        "parameter_initial_enable": 1,
                    }
                },
            )
            patcher.add_line(toggle, param_wrap)
            patcher.add_line(param_wrap, rnbo)

            param = sub_patcher.add_textbox(
                f"param {label} 0 @min 0 @max 1",
            )

            # Add a line to connect the parameter control to the 'set' param object
            sub_patcher.add_line(param, set_param)
            # Add a line to connect the 'set' param object to the codebox
            sub_patcher.add_line(set_param, codebox)

            # Possibly add MIDI input control
            if midi:
                add_midi_control(
                    item, sub_patcher, codebox, param=param, set_param=set_param
                )

        # bargraph with "min", "max"
        elif item_type in ["vbargraph", "hbargraph"]:
            min_value = item["min"]
            max_value = item["max"]

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
                        "parameter_initial": [label_path, 0],
                        "parameter_initial_enable": 1,
                    }
                },
            )
            patcher.add_line(param_wrap, rnbo)

            param = sub_patcher.add_textbox(
                f"param {label} 0 @min {min_value} @max {max_value}",
            )

            # Signal transformed in control
            snapshot = sub_patcher.add_textbox("snapshot~ 10")
            change = sub_patcher.add_textbox("change")

            # Connect codebox outN to snapshot
            sub_patcher.add_line(codebox, snapshot, outlet=num_outputs + bargraph_count)
            # Connect snapshot to range
            sub_patcher.add_line(snapshot, change)
            # And finally change to param
            sub_patcher.add_line(change, param)

            # Possibly add MIDI output control
            if midi:
                add_midi_control(item, sub_patcher, codebox, change=change)

            # Next bargraph
            bargraph_count += 1

        # slider and nentry use a 'param' object
        else:
            min_value = item["min"]
            max_value = item["max"]
            init_value = item["init"]
            steps_value = (max_value - min_value) / item["step"]

            # Add a global 'set' param object
            set_param = sub_patcher.add_textbox(f"set {label}")

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
                        "parameter_initial": [label_path, init_value],
                        "parameter_initial_enable": 1,
                    }
                },
            )
            patcher.add_line(param_wrap, rnbo)

            param = sub_patcher.add_textbox(
                # Does not work with @steps, with parameter values slightly different
                # f"param {label} {init_value} @min {min_value} @max {max_value} @steps {steps_value} ",
                f"param {label} {init_value} @min {min_value} @max {max_value}",
            )

            # Add a line to connect the parameter control to the 'set' param object
            sub_patcher.add_line(param, set_param)
            # Add a line to connect the 'set' param object to the codebox
            sub_patcher.add_line(set_param, codebox)

            # Possibly add MIDI input control
            if midi:
                add_midi_control(
                    item, sub_patcher, codebox, param=param, set_param=set_param
                )

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

    # After analyzing all UI items to get freq/gain/gate controls, possibly add polyphony control
    if midi and nvoices > 0 and set_param_pitch and set_param_gain and set_param_gate:
        add_polyphony_control(
            sub_patcher,
            set_param_pitch,
            set_param_gain,
            set_param_gate,
            is_freq,
            is_gain,
        )


def create_rnbo_object(
    patcher: Patcher,
    dsp_name: str,
    midi: bool,
    nvoices: int,
    num_inputs: int,
    num_outputs: int,
):
    """
    Create and configure the rnbo~ object.

    This function creates and configures the rnbo~ object within a Max/MSP patcher.
    It sets attributes such as optimization, title, and polyphony (if applicable)
    based on the provided parameters.

    Parameters:
        patcher (Patcher): The Max/MSP patcher where the rnbo~ object will be added.
        dsp_name (str): The name of the DSP module.
        midi (bool): Whether MIDI controls should be added.
        nvoices (int): Number of voices for polyphony control.
        num_inputs (int): Number of audio inputs.
        num_outputs (int): Number of audio outputs.

    Returns:
        rnbo (Box): The created rnbo~ object.
    """
    # Create the rnbo~ object
    rnbo_attributes = {"optimization": "O3", "title": dsp_name, "dumpoutlet": 1}
    # Add the polyphony attribute only if midi is True and nvoices > 0
    if midi and nvoices > 0:
        rnbo_attributes["polyphony"] = nvoices

    # Prepare the inlet and outlet information
    inlets, outlets, inletInfo, outletInfo = generate_io_info(
        midi, num_inputs, num_outputs
    )

    # Create the rnbo~ object
    rnbo = patcher.add_rnbo(
        inletInfo=inletInfo,
        outletInfo=outletInfo,
        title=dsp_name,
        numinlets=inlets,
        numoutlets=outlets,
        saved_object_attributes=rnbo_attributes,
    )
    # And return it
    return rnbo


def add_rnbo_object_flat(
    patcher: Patcher,
    dsp_name: str,
    codebox_code: str,
    items_info_list: List[dict],
    midi: bool,
    nvoices: int,
    test: bool,
    num_inputs: int,
    num_outputs: int,
) -> Box:
    """
    Adds DSP elements, routing, and parameter controls for a DSP to the given Patcher object in flat mode.

    Parameters:
        patcher (Patcher): The Patcher object to which DSP elements and controls will be added.
        dsp_name (str): The name of the DSP.
        codebox_code (str): The code to be executed by the DSP effect.
        items_info_list (List[dict]): A list of dictionaries containing information about UI items.
        midi (bool): Indicates whether MIDI control is enabled.
        nvoices (int): The number of polyphony voices.
        num_inputs (int): The number of audio input channels.
        num_outputs (int): The number of audio output channels.

    Returns:
        Box: The added rnbo~ object representing the DSP.
    """

    # Create the rnbo~ object
    rnbo = create_rnbo_object(patcher, dsp_name, midi, nvoices, num_inputs, num_outputs)

    # Create the codebox subpatcher
    sub_patcher = rnbo.subpatcher
    add_codebox_object(
        patcher,
        sub_patcher,
        rnbo,
        "",
        codebox_code,
        items_info_list,
        midi,
        nvoices,
        test,
        num_inputs,
        num_outputs,
    )

    return rnbo


def add_rnbo_object_subpatcher(
    patcher: Patcher,
    rnbopat_path: str,
    dsp_name: str,
    codebox_code: str,
    items_info_list: List[dict],
    midi: bool,
    nvoices: int,
    test: bool,
    num_inputs: int,
    num_outputs: int,
) -> Box:
    """
    Adds DSP elements, routing, and parameter controls for a DSP to the given Patcher object in 'p' subpatcher.

    Parameters:
        patcher (Patcher): The Patcher object to which DSP elements and controls will be added.
        rnbopat_path (str): The path to the directory where the maxpat will be saved.
        dsp_name (str): The name of the DSP.
        codebox_code (str): The code to be executed by the DSP effect.
        items_info_list (List[dict]): A list of dictionaries containing information about UI items.
        midi (bool): Indicates whether MIDI control is enabled.
        nvoices (int): The number of polyphony voices.
        num_inputs (int): The number of audio input channels.
        num_outputs (int): The number of audio output channels.

    Returns:
        Box: The added rnbo~ object representing the DSP.
    """

    # Create the rnbo~ object
    rnbo = create_rnbo_object(patcher, dsp_name, midi, nvoices, num_inputs, num_outputs)

    # Create the codebox subpatcher in a rnbopat file
    rnbopat = Patcher(rnbopat_path, classnamespace="rnbo")
    add_codebox_object(
        patcher,
        rnbopat,
        rnbo,
        "poly/" + dsp_name + "/" if nvoices > 0 else dsp_name + "/",
        codebox_code,
        items_info_list,
        midi,
        nvoices,
        test,
        num_inputs,
        num_outputs,
    )

    # Save the rnbopat file
    rnbopat.save()

    # Get the subpatcher
    sub_patcher = rnbo.subpatcher

    # Add the DSP subpatcher
    if nvoices > 0:
        p_dsp_box = sub_patcher.add_textbox(
            f"p @title {dsp_name} @file {rnbopat_path} @polyphony {nvoices}"
        )
    else:
        p_dsp_box = sub_patcher.add_textbox(f"p @title {dsp_name} @file {rnbopat_path}")

    # Generating the lines of code for inputs
    for i in range(num_inputs):
        input_box = sub_patcher.add_textbox(f"in~ {i + 1}")
        sub_patcher.add_line(input_box, p_dsp_box, inlet=i)

    # Generating the lines of code for outputs
    for i in range(num_outputs):
        output_box = sub_patcher.add_textbox(f"out~ {i + 1}")
        sub_patcher.add_line(p_dsp_box, output_box, outlet=i)

    # Possibly add MIDI input/output control in the global patcher
    # and connect the DSP rnbo~ object to the midiin/midiout objects.
    # midi_in/midi_out are only needed in polyphonic mode
    if midi and nvoices > 0:
        midi_in = sub_patcher.add_textbox("midiin")
        midi_out = sub_patcher.add_textbox("midiout")
        connect_midi_subpatcher(
            sub_patcher, p_dsp_box, midi_in, midi_out, num_inputs, num_outputs
        )

    return rnbo


def add_rnbo_object_poly_effect(
    patcher: Patcher,
    dsp_rnbopat_path: str,
    effect_rnbopat_path: str,
    dsp_name: str,
    dsp_codebox_code: str,
    effect_codebox_code: str,
    dsp_items_info_list: List[dict],
    effect_items_info_list: List[dict],
    midi: bool,
    nvoices: int,
    test: bool,
    dsp_num_inputs: int,
    dsp_num_outputs: int,
    effect_num_inputs: int,
    effect_num_outputs: int,
) -> Box:
    """
    Adds DSP elements, routing, and parameter controls for a DSP to the given Patcher object for DSP and effect.

    Parameters:
        patcher (Patcher): The Patcher object to which DSP elements and controls will be added.
        dsp_rnbopat_path (str): The path to the directory where the DSP maxpat will be saved.
        effect_rnbopat_path (str): The path to the directory where the effect maxpat will be saved.
        dsp_name (str): The name of the DSP.
        dsp_codebox_code (str): The code to be executed by the DSP.
        effect_codebox_code (str): The code to be executed by the effect.
        dsp_items_info_list (List[dict]): A list of dictionaries containing information about UI items for the DSP.
        effect_items_info_list (List[dict]): A list of dictionaries containing information about UI items for the effect.
        midi (bool): Indicates whether MIDI control is enabled.
        nvoices (int): The number of polyphony voices.
        dsp_num_inputs (int): The number of audio input channels.
        dsp_num_outputs (int): The number of audio output channels.
        effect_num_inputs (int): The number of audio input channels.
        effect_num_outputs (int): The number of audio output channels.

    Returns:
        Box: The added rnbo~ object representing the DSP.
    """

    # Create the rnbo~ object
    rnbo = create_rnbo_object(
        patcher, dsp_name, midi, nvoices, dsp_num_inputs, effect_num_outputs
    )

    # Create the DSP codebox subpatcher in a dsp_rnbo_pat file
    dsp_rnbo_pat = Patcher(dsp_rnbopat_path, classnamespace="rnbo")
    add_codebox_object(
        patcher,
        dsp_rnbo_pat,
        rnbo,
        "poly/" + dsp_name + "/" if nvoices > 0 else dsp_name + "/",
        dsp_codebox_code,
        dsp_items_info_list,
        midi,
        nvoices,
        test,
        dsp_num_inputs,
        dsp_num_outputs,
    )

    # Save the rnbo_pat file
    dsp_rnbo_pat.save()

    # Create the effect codebox subpatcher in a rnbo_effect_pat file
    effect_rnbo_pat = Patcher(effect_rnbopat_path, classnamespace="rnbo")
    add_codebox_object(
        patcher,
        effect_rnbo_pat,
        rnbo,
        "poly/" + dsp_name + "[1]/" if nvoices > 0 else dsp_name + "/",
        effect_codebox_code,
        effect_items_info_list,
        midi,
        -1,
        False,
        effect_num_inputs,
        effect_num_outputs,
    )

    # Save the rnbo_effect_pat file
    effect_rnbo_pat.save()

    # Get the subpatcher
    sub_patcher = rnbo.subpatcher

    # Add the DSP subpatcher
    if nvoices > 0:
        p_dsp_box = sub_patcher.add_textbox(
            f"p @title {dsp_name} @file {dsp_rnbopat_path} @polyphony {nvoices}"
        )
    else:
        p_dsp_box = sub_patcher.add_textbox(
            f"p @title {dsp_name} @file {dsp_rnbopat_path}"
        )

    # Add the effect subpatcher
    p_effect_box = sub_patcher.add_textbox(
        f"p @title {dsp_name} @file {effect_rnbopat_path}"
    )

    # Generating the lines of code for inputs
    for i in range(dsp_num_inputs):
        input_box = sub_patcher.add_textbox(f"in~ {i + 1}")
        sub_patcher.add_line(input_box, p_dsp_box, inlet=i)

    # Connect the DSP to the effect
    connect_dsp_effect(
        sub_patcher,
        p_dsp_box,
        p_effect_box,
        dsp_num_outputs,
        effect_num_inputs,
    )

    # Generating the lines of code for outputs
    for i in range(effect_num_outputs):
        output_box = sub_patcher.add_textbox(f"out~ {i + 1}")
        sub_patcher.add_line(p_effect_box, output_box, outlet=i)

    # Possibly add MIDI input/output control in the global patcher
    # and connect the DSP rnbo~ object to the midiin/midiout objects
    if midi:
        midi_in = sub_patcher.add_textbox("midiin")
        midi_out = sub_patcher.add_textbox("midiout")
        connect_midi_subpatcher(
            sub_patcher, p_dsp_box, midi_in, midi_out, dsp_num_inputs, dsp_num_outputs
        )

    return rnbo


def connect_dsp_effect(
    patcher: Patcher,
    dsp_box: Box,
    effect_box: Box,
    dsp_num_outputs: int,
    effect_num_inputs: int,
) -> None:
    """
    Connects a DSP module to an effect module within a patcher.

    Args:
        patcher (Patcher): The main patcher where objects will be added.
        dsp_box (Box): The rnbo DSP module
        effect_box (Box): The rnbo effect module
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
    Returns:
        None
    """

    # print(f"Connecting DSP to effect: {dsp_num_outputs} -> {effect_num_inputs}")

    # Python 3.10 and later
    # match (dsp_num_outputs, effect_num_inputs):
    #     case (1, 1):
    #         # print("1 -> 1")
    #         patcher.add_line(dsp_box, effect_box)
    #     case (1, 2):
    #         # print("1 -> 2")
    #         patcher.add_line(dsp_box, effect_box, inlet=0, outlet=0)
    #         patcher.add_line(dsp_box, effect_box, inlet=1, outlet=0)
    #     case (2, 1):
    #         # print("2 -> 1")
    #         patcher.add_line(dsp_box, effect_box, inlet=0, outlet=0)
    #         patcher.add_line(dsp_box, effect_box, inlet=0, outlet=1)
    #     case (2, 2):
    #         # print("2 -> 2")
    #         patcher.add_line(dsp_box, effect_box, inlet=0, outlet=0)
    #         patcher.add_line(dsp_box, effect_box, inlet=1, outlet=1)

    if dsp_num_outputs == 1:
        if effect_num_inputs == 1:
            # print("1 -> 1")
            patcher.add_line(dsp_box, effect_box)
        elif effect_num_inputs == 2:
            # print("1 -> 2")
            patcher.add_line(dsp_box, effect_box, inlet=0, outlet=0)
            patcher.add_line(dsp_box, effect_box, inlet=1, outlet=0)
    elif dsp_num_outputs == 2:
        if effect_num_inputs == 1:
            # print("2 -> 1")
            patcher.add_line(dsp_box, effect_box, inlet=0, outlet=0)
            patcher.add_line(dsp_box, effect_box, inlet=0, outlet=1)
        elif effect_num_inputs == 2:
            # print("2 -> 2")
            patcher.add_line(dsp_box, effect_box, inlet=0, outlet=0)
            patcher.add_line(dsp_box, effect_box, inlet=1, outlet=1)


def add_compile_test(
    patcher: Patcher, rnbo: Box, export_path: str, cpp_filename: str
) -> None:
    """
    Adds a series of objects and routing connections to the given Patcher object in order to set up a compile test.

    Parameters:
        patcher (Patcher): The main patcher where objects will be added.
        rnbo (Box): The rnbo DSP module
        export_path (str): The path to the directory where the export will be saved.
        cpp_filename (str): The desired filename for the exported CPP code.

    Returns:
        None
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
    # Right most outlet of rnbo is dump outlet
    patcher.add_line(rnbo, route, outlet=rnbo.numoutlets - 1)


def create_audio_output(patcher: Patcher, rnbo: Box, num_outputs: int) -> None:
    """
    Creates the output audio object.

    Parameters:
        patcher (Patcher): The main patcher where objects will be added.
        rnbo (Box): The rnbo DSP module
        num_outputs (int): The number of output channels to create.

    Returns:
        None

    Description:
        This function create an 'dac~' audio output with the specified number of output channels,
        then connect the rnbo object to the audio outputs.
    """

    # Create the toggle button for audio output activation
    toggle = patcher.add_textbox("toggle")

    # Set the position and size of the toggle button on the canvas
    toggle.patching_rect = [
        toggle.patching_rect[0],
        toggle.patching_rect[1],
        24.0,
        24.0,
    ]

    # Generate a string for the 'dac~' object with the specified number of output channels
    dac_str = "dac~ " + " ".join(str(i + 1) for i in range(num_outputs))

    # Create an audio output object with the generated 'dac~' string and the specified number of inlets
    audio_out = patcher.add_textbox(dac_str, numinlets=num_outputs)

    # Connect the toggle button to the audio output object using a patch line
    patcher.add_line(toggle, audio_out)

    # Connect the DSP rnbo~ object to audio_out using separate lines for each output channel
    for i in range(num_outputs):
        patcher.add_line(rnbo, audio_out, inlet=i, outlet=i)


def create_audio_input(patcher: Patcher, rnbo: Box, num_inputs: int) -> None:
    """
     Creates the input audio object.

    Parameters:
        patcher (Patcher): The main patcher where objects will be added.
        rnbo (Box): The rnbo DSP module
        num_inputs (int): The number of input channels to create.

    Returns:
        None

    Description:
         This function create an 'adc~' audio input with the specified number of input channels,
         then connect the audio inputs to the rnbo object.
    """

    # Generate a string for the 'adc~' object with the specified number of input channels
    adc_str = "adc~ " + " ".join(str(i + 1) for i in range(num_inputs))

    # Create an audio input object with the generated 'adc~' string and the specified number of outlets
    audio_in = patcher.add_textbox(adc_str, numoutlets=num_inputs)

    # Connect audio_in to the DSP rnbo~ object using separate lines for each input channel
    for i in range(num_inputs):
        patcher.add_line(audio_in, rnbo, inlet=i, outlet=i)


def connect_midi_rnbo(patcher: Patcher, rnbo: Box, midi_in: Box, midi_out: Box) -> None:
    """
    Connects MIDI input, a DSP, and MIDI output in a Max/MSP patcher.

    Parameters:
        patcher (Patcher): The Max/MSP patcher to add connections to.
        rnbo (Box): The DSP object.
        midi_in (Box): The MIDI input object.
        midi_out (Box): The MIDI output object.

    Returns:
        None
    """

    # MIDI inlet will always be the right-most inlet, and inlets numbering starts at 0
    inlet_index = rnbo.numinlets - 1
    # MIDI outlet will always be the third from the right-most outlet, and outlets numbering starts at 0
    outlet_index = rnbo.numoutlets - 3

    patcher.add_line(midi_in, rnbo, inlet=inlet_index)
    patcher.add_line(rnbo, midi_out, outlet=outlet_index)


def connect_midi_subpatcher(
    patcher: Patcher,
    pbox: Box,
    midi_in: Box,
    midi_out: Box,
    inlet: int,
    outlet: int,
) -> None:
    """
    Connects MIDI input, a DSP, and MIDI output in a 'p' subpatcher.

    Parameters:
        patcher (Patcher): The Max/MSP patcher to add connections to.
        rnbo (Box): The DSP object.
        midi_in (Box): The MIDI input object.
        midi_out (Box): The MIDI output object.
        inlet: (int): The index of the inlet to connect to.
        outlet: (int) : The index of the outlet to connect to.

    Returns:
        None
    """

    patcher.add_line(midi_in, pbox, inlet=inlet)
    patcher.add_line(pbox, midi_out, outlet=outlet)


def create_rnbo_patch_flat(
    dsp_name: str,
    maxpat_path: str,
    export_path: str,
    cpp_filename: str,
    dsp_codebox_code: str,
    dsp_items_info_list: List[Dict],
    dsp_num_inputs: int,
    dsp_num_outputs: int,
    midi: bool,
    nvoices: int,
    effect_codebox_code: Optional[str] = None,
    effect_items_info_list: Optional[List[dict]] = None,
    effect_num_inputs: int = -1,
    effect_num_outputs: int = -1,
    compile: bool = False,
    test: bool = False,
    subpatcher: bool = False,
) -> None:
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
    - effect_codebox_code (Optional[str]): The code for the effect codebox~ section in the subpatcher.
    - effect_items_info_list (Optional[List[dict]]): A list of dictionaries containing information about the items to be added.
    - effect_num_inputs (int): The number of effect audio inputs.
    - effect_num_outputs (int): The number of effect audio outputs.
    - midi (bool): A flag indicating whether to include MIDI input/output control.
    - nvoices (int): The number of voices in polyphonic mode.
    - compile (bool): A flag indicating whether to include the C++ compilation and export machinery.
    - test (bool): A flag indicating whether the patch is for testing purposes.
    - subpatcher (bool): A flag indicating whether to save subpatchers as foo.rnbopat files.

    Returns:
        None
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
    dsp_rnbo = add_rnbo_object_flat(
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

    # Possibly add MIDI input/output control in the global patcher
    # and connect the DSP rnbo~ object to the midiin/midiout objects
    if midi:
        midi_in = patcher.add_textbox("midiin")
        midi_out = patcher.add_textbox("midiout")
        connect_midi_rnbo(patcher, dsp_rnbo, midi_in, midi_out)

    # Save subpatcher as an abstraction
    if subpatcher:
        dsp_rnbo.subpatcher.save_as(maxpat_path.rsplit(".", 1)[0] + "." + "rnbopat")

    # Possibly create and connect the effect rnbo~ object
    if effect_codebox_code:
        effect_rnbo = add_rnbo_object_flat(
            patcher,
            "Effect",
            effect_codebox_code,
            effect_items_info_list,
            midi,
            -1,
            False,
            effect_num_inputs,
            effect_num_outputs,
        )

        # Connect the DSP and effect rnbo~ objects
        connect_dsp_effect(
            patcher,
            dsp_rnbo,
            effect_rnbo,
            dsp_num_outputs,
            effect_num_inputs,
        )

        # Save subpatcher as an abstraction with the '_effect' suffix
        if subpatcher:
            effect_rnbo.subpatcher.save_as(
                maxpat_path.rsplit(".", 1)[0] + "_effect." + "rnbopat"
            )

        # Connect the effect rnbo~ object to the midiin/midiout objects
        if midi:
            connect_midi_rnbo(patcher, effect_rnbo, midi_in, midi_out)

    # Add loadbang and 'compile C++ and export' machinery
    if compile:
        add_compile_test(patcher, dsp_rnbo, export_path, cpp_filename)

    # Connect the appropriate rnbo~ object to audio_out
    if effect_codebox_code:
        # Create the audio driver output
        create_audio_output(patcher, effect_rnbo, effect_num_outputs)
    else:
        # Create the audio driver output
        create_audio_output(patcher, dsp_rnbo, dsp_num_outputs)

    # Possibly create the audio driver input
    if dsp_num_inputs > 0:
        create_audio_input(patcher, dsp_rnbo, dsp_num_inputs)

    # And finally save the patch
    patcher.save()


# New version using 'p' subpatcher, to be used when MIDI out is fixed in C++ export
def create_rnbo_patch(
    dsp_name: str,
    maxpat_path: str,
    export_path: str,
    cpp_filename: str,
    dsp_codebox_code: str,
    dsp_items_info_list: List[Dict],
    dsp_num_inputs: int,
    dsp_num_outputs: int,
    midi: bool,
    nvoices: int,
    effect_codebox_code: Optional[str] = None,
    effect_items_info_list: Optional[List[dict]] = None,
    effect_num_inputs: int = -1,
    effect_num_outputs: int = -1,
    compile: bool = False,
    test: bool = False,
    subpatcher: bool = False,
) -> None:
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
    - effect_codebox_code (Optional[str]): The code for the effect codebox~ section in the subpatcher.
    - effect_items_info_list (Optional[List[dict]]): A list of dictionaries containing information about the items to be added.
    - effect_num_inputs (int): The number of effect audio inputs.
    - effect_num_outputs (int): The number of effect audio outputs.
    - midi (bool): A flag indicating whether to include MIDI input/output control.
    - nvoices (int): The number of voices in polyphonic mode.
    - compile (bool): A flag indicating whether to include the C++ compilation and export machinery.
    - test (bool): A flag indicating whether the patch is for testing purposes.
    - subpatcher (bool): A flag indicating whether to save subpatchers as foo.rnbopat files.

    Returns:
        None
    """

    # Create the patcher
    patcher = Patcher(maxpat_path)

    # Faust generated patch comment
    patcher.add_comment(
        "Faust generated RNBO patch, Copyright (c) 2023 Grame",
        patching_rect=[50.0, 10.0, 350.0, 100.0],
        fontsize=16,
    )

    if effect_codebox_code:
        # Create the DSP rnbo~ object in 'p' subpatcher with DSP and effect
        dsp_rnbo = add_rnbo_object_poly_effect(
            patcher,
            maxpat_path.rsplit(".", 1)[0] + "." + "rnbopat",
            maxpat_path.rsplit(".", 1)[0] + "_effect." + "rnbopat",
            dsp_name,
            dsp_codebox_code,
            effect_codebox_code,
            dsp_items_info_list,
            effect_items_info_list,
            midi,
            nvoices,
            test,
            dsp_num_inputs,
            dsp_num_outputs,
            effect_num_inputs,
            effect_num_outputs,
        )
    else:
        if subpatcher:
            # Create the DSP rnbo~ object in 'p' subpatcher mode with DSP
            dsp_rnbo = add_rnbo_object_subpatcher(
                patcher,
                maxpat_path.rsplit(".", 1)[0] + "." + "rnbopat",
                dsp_name,
                dsp_codebox_code,
                dsp_items_info_list,
                midi,
                nvoices,
                test,
                dsp_num_inputs,
                dsp_num_outputs,
            )
        else:
            # Create the DSP rnbo~ object in flat mode with DSP
            dsp_rnbo = add_rnbo_object_flat(
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

    # Possibly add MIDI input/output control in the global patcher
    # and connect the DSP rnbo~ object to the midiin/midiout objects
    if midi:
        midi_in = patcher.add_textbox("midiin")
        midi_out = patcher.add_textbox("midiout")
        connect_midi_rnbo(patcher, dsp_rnbo, midi_in, midi_out)

    # Add loadbang and 'compile C++ and export' machinery
    if compile:
        add_compile_test(patcher, dsp_rnbo, export_path, cpp_filename)

    # Create the audio driver output
    create_audio_output(patcher, dsp_rnbo, dsp_num_outputs)

    # Possibly create the audio driver input
    if dsp_num_inputs > 0:
        create_audio_input(patcher, dsp_rnbo, dsp_num_inputs)

    # And finally save the patch
    patcher.save()


def load_files_create_rnbo_patch(
    dsp_name: str,
    dsp_codebox_path: str,
    dsp_json_path: str,
    effect_codebox_path: Optional[str],
    effect_json_path: Optional[str],
    maxpat_path: str,
    export_path: str,
    cpp_filename: str,
    midi: bool,
    nvoices: int,
    compile: bool,
    test: bool,
    subpatcher: bool,
) -> None:
    """
    This function loads the codebox and JSON files, extracts relevant data in the JSON, and creates the RNBO Max patch.

    Parameters:
    - dsp_name (str): The name of the DSP.
    - dsp_codebox_path (str): The path to the DSP codebox file.
    - dsp_json_path (str): The path to the DSP JSON file containing items info.
    - effect_codebox_path (Optional[str]): The path to the effect codebox file.
    - effect_json_path (Optional[str]): The path to the effect JSON file containing items info.
    - maxpat_path (str): The path where the Max patcher will be created.
    - export_path (str): The path for exporting the C++ code.
    - cpp_filename (str): The filename for the exported C++ code.
    - midi (bool): A flag indicating whether to include MIDI input/output control.
    - nvoices (int): The number of voices in polyphonic mode.
    - compile (bool): A flag indicating whether to include the C++ compilation and export machinery.
    - test (bool): A flag indicating whether the patch is for testing purposes (causing control parameter special naming).
    - subpatcher (bool): A flag indicating whether to save subpatchers as foo.rnbopat files.

    Returns:
        None
    """

    with open(dsp_codebox_path) as codebox_file:
        dsp_codebox_code = codebox_file.read()

    with open(dsp_json_path, encoding="utf-8") as json_file:
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
            # Take either the midi parameter or options[0] (= the midi state found in the JSON file)
            midi or options[0],
            # Take either the given nvoices, otherwise options[1](= the number of voices found in the JSON file) or -1
            nvoices if nvoices > 0 else options[1] if options[1] else -1,
            effect_codebox_code,
            effect_items_info_list,
            effect_num_inputs,
            effect_num_outputs,
            compile,
            test,
            subpatcher,
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
            # Take either the midi parameter or options[0] (= the midi state found in the JSON file)
            midi or options[0],
            # Take either the given nvoices, otherwise options[1](= the number of voices found in the JSON file) or -1
            nvoices
            if nvoices is not None and nvoices > 0
            else options[1]
            if options[1]
            else -1,
            compile=compile,
            test=test,
            subpatcher=subpatcher,
        )


# Main function to parse command-line arguments and run the script
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--dsp-name", type=str, help="DSP name")
    parser.add_argument("--dsp-codebox", type=str, help="DSP codebox file")
    parser.add_argument("--dsp-json", type=str, help="DSP JSON file")
    parser.add_argument("--effect-codebox", type=str, help="Effect codebox file")
    parser.add_argument("--effect-json", type=str, help="Effect JSON file")
    parser.add_argument("--maxpat", type=str, help="RNBO maxpat file")
    parser.add_argument("--cpp-export", type=str, help="C++ export folder path")
    parser.add_argument("--cpp-filename", type=str, help="C++ export filename")
    parser.add_argument("--midi", type=str, help="MIDI control")
    parser.add_argument("--nvoices", type=int, help="Set nvoices value")
    parser.add_argument("--compile", type=str, help="Whether to compile to C++ code")
    parser.add_argument(
        "--test",
        type=str,
        help="Whether to activate test mode with special labels",
    ),
    parser.add_argument(
        "--subpatcher",
        type=str,
        help="Whether to generate subpatchers as foo.rnbopat files",
    )
    args = parser.parse_args()
    # print(args)

    load_files_create_rnbo_patch(
        args.dsp_name,
        args.dsp_codebox,
        args.dsp_json,
        args.effect_codebox,
        args.effect_json,
        args.maxpat,
        args.cpp_export,
        args.cpp_filename,
        args.midi == "True",
        args.nvoices,
        args.compile == "True",
        args.test == "True",
        args.subpatcher == "True",
    )


# Parse command line
if __name__ == "__main__":
    main()
