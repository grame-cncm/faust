import json
import os
from parameters import Parameter
from processor import TemplateProcessor
from xmlinjector import inject_properties_to_xml

def parse_ui(ui_tree, callback):
    for group in ui_tree:
        parse_group(group, callback)

def parse_group(group, callback):
    items = group.get("items", [])
    parse_items(items, callback)

def parse_items(items, callback):
    for item in items:
        parse_item(item, callback)

def parse_item(item, callback):
    if item["type"] in {"vgroup", "hgroup", "tgroup"}:
        parse_items(item.get("items", []), callback)
    else:
        callback(item)

def extract_parameters(ui_tree)->list:
    result = []
    parse_ui(ui_tree, lambda item: result.append(item))
    # return result # TODO need to filter out non-input parameters such as the BarGraph 
    return [p for p in result if p["type"] in {"hslider", "vslider", "nentry", "checkbox", "button"}] # List of dicts

def integrateParameters(output_dir, plugin_name, plugin_suffix, json_file_path):

    # @TODO: make this a configuration file.
    target_files = [
        "SoundEnginePlugin/faustdsp.cpp",
        f"SoundEnginePlugin/{plugin_name}{plugin_suffix}.cpp",
        f"SoundEnginePlugin/{plugin_name}{plugin_suffix}Params.h",
        f"SoundEnginePlugin/{plugin_name}{plugin_suffix}Params.cpp",
        f"WwisePlugin/{plugin_name}Plugin.cpp",
    ]
    xml_file = f"WwisePlugin/{plugin_name}.xml"

    with open(json_file_path, 'r') as f:
        faustdata = json.load(f)

    parameters_data = extract_parameters(faustdata["ui"])

    print(f"OK : Succesfully extracted parameters from {json_file_path} file.")

    parameters = [Parameter(d) for d in parameters_data]
    processor = TemplateProcessor(parameters)


    for file in target_files:
        file = os.path.join(output_dir, plugin_name, file)
        processor.process_file(file)
    xml_file = os.path.join(output_dir, plugin_name, xml_file)

    inject_properties_to_xml(parameters, xml_file)

if __name__ == "__main__":
    import sys

    if len(sys.argv) != 5:
        print("Usage: python3 inject_parameters.py output_dir plugin_name plugin_suffix path/to/faust.json")
        sys.exit(1)

    output_dir = sys.argv[1]
    plugin_name = sys.argv[2]
    plugin_suffix = sys.argv[3]
    json_file_path = sys.argv[4]
    integrateParameters(output_dir, plugin_name, plugin_suffix, json_file_path)