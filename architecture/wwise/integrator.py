import json
import os
from parameters import Parameter
from processor import TemplateProcessor
import pdb
from xmlinjector import inject_properties_to_xml

def extract_parameters(ui_tree)->list:
    
    result = []

    def walk(tree):
        for node in tree:
            if node["type"] in ("vgroup", "hgroup"):
                walk(node.get("items", []))  # recurse
            else:
                result.append(node)

    walk(ui_tree)
    return result  # List of dicts

def integrateParameters(plugin_name, plugin_suffix, json_file_path):

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
        file = os.path.join(plugin_name,file)
        processor.process_file(file)
    xml_file = os.path.join(plugin_name,xml_file)

    inject_properties_to_xml(parameters, xml_file)

if __name__ == "__main__":
    import sys

    if len(sys.argv) != 4:
        print("Usage: python3 inject_parameters.py plugin_name plugin_suffix path/to/faust.json")
        sys.exit(1)

    plugin_name = sys.argv[1]
    plugin_suffix = sys.argv[2]
    json_file_path = sys.argv[3]
    integrateParameters(plugin_name, plugin_suffix, json_file_path)