"""
integrator.py

Module responsible for the integration of Faust-generated code into a Wwise plugin project, 
broken down into the following steps:
- integrate the compiled dsp file
- replace the vital for the integration files
- integrate parameters
- inject faust includes within the lua script
"""
import json
import os
import sys
import shutil
from parameters import Parameter
from processor import TemplateProcessor
from xmlinjector import inject_properties_to_xml
from typing import List, Dict, Any, Callable

FaustUIItem = Dict[str, Any]
FaustUITree = List[FaustUIItem]
CallbackFn = Callable[[FaustUIItem], None]

"""
Faust UI tree Parsing Utilities:
these functions recursively parse the Faust UI tree retrieved from the JSON file.
The parse_ui / parse_group / parse_items / parse_item methods are ported from the
TypeScript implementation implemented in the context of the faustwasm repository:
github.com/grame-cncm/faustwasm/blob/3ac9238bb0579bd2c51e67f5868997395766dbab/src/FaustWebAudioDsp.ts#L730C1-L730C30
"""
def parse_ui(ui_tree : FaustUITree, callback : CallbackFn) -> None:
    for group in ui_tree:
        parse_group(group, callback)

def parse_group(group : FaustUIItem, callback : CallbackFn) -> None:
    items = group.get("items", [])
    parse_items(items, callback)

def parse_items(items : List[FaustUIItem], callback : CallbackFn) -> None:
    for item in items:
        parse_item(item, callback)

def parse_item(item : FaustUIItem, callback : CallbackFn) -> None:
    if item["type"] in {"vgroup", "hgroup", "tgroup"}:
        parse_items(item.get("items", []), callback)
    else:
        callback(item)

def extract_parameters(ui_tree : FaustUITree)-> List[FaustUIItem]:
    """
    Extracts parameter items from the Faust UI tree and assigns unique shortnames as a new key in the dict.
    
    This function performs two operations in a single pass:
    - assigns unique shortnames to ALL items that have a 'shortname' property
    - collects only parameter-type items (sliders, entries, checkboxes, buttons), 
    filtering out BarGraphs which are curently not supported 
    
    As for the uniquification, it is necessary because Faust UI elements support groups where
    different groups may contain elements with the same name. Since we serialize all UI elements 
    under the same umbrella (rather than preserving grouping), we need unique identifiers to avoid 
    naming conflicts when defining RTPC values.
    
    Args:
        ui_tree: The Faust UI tree structure from the JSON file
        
    Returns:
        List of parameter items (dicts) with 'unq_shortname' added to each item
        that originally had a 'shortname'. Only returns items of parameter types.
    """

    result = []
    counter = 1
    
    def callback(item : FaustUIItem) -> None:
        nonlocal counter

        # uniquify_shortnames to ALL items that have shortname, by asigning them a new key. 
        # This ensures unique RTPC values across the entire UI tree
        if "shortname" in item:
            item["unq_shortname"] = f"{item['shortname']}{counter}"
            counter += 1
        
        # result.append(item) # TODO need to filter out non-input parameters such as the BarGraph
        if item["type"] in {"hslider", "vslider", "nentry", "checkbox", "button"}:
            result.append(item) # List of dicts
    
    parse_ui(ui_tree, callback)
    return result
    
def parameter_integration(cfg) -> None:
    """
    Processes the parameters from the Faust JSON and injects them into the template files and in the XML file.
    The method applied is broken down in the following steps:
    - Extract parameters from the Faust UI tree
    - Create Parameter objects for processing
    - Apply template substitutions to target files
    - Inject properties into the plugin XML configuration
    
    Args:
        cfg (Config): the configuration object
    """

    print("Integrating parameters...")
    
    # target files that are going to be replaced by template files that contains project-related placeholders for injection
    target_files = [
        f"SoundEnginePlugin/{cfg.plugin_name}{cfg.plugin_suffix}.cpp",
        f"SoundEnginePlugin/{cfg.plugin_name}{cfg.plugin_suffix}Params.h",
        f"SoundEnginePlugin/{cfg.plugin_name}{cfg.plugin_suffix}Params.cpp",
        f"WwisePlugin/{cfg.plugin_name}Plugin.cpp",
    ]
    xml_file = f"WwisePlugin/{cfg.plugin_name}.xml"

    with open(cfg.json_file, 'r') as f:
        faustdata = json.load(f)

    parameters_data = extract_parameters(faustdata["ui"])

    print(f"OK : Succesfully extracted parameters from {cfg.json_file} file.")

    parameters = [Parameter(d) for d in parameters_data]
    processor = TemplateProcessor(parameters)

    for file in target_files:
        file = os.path.join(cfg.output_dir, cfg.plugin_name, file)
        processor.process_file(file)
    xml_file = os.path.join(cfg.output_dir, cfg.plugin_name, xml_file)

    inject_properties_to_xml(parameters, xml_file)

def faust_dspfile_integration(cfg) -> None:
    """
    Copies the generated Faust DSP file (faustdsp.cpp) into the SoundEnginePlugin project directory.
    Args:
        cfg (Config): the configuration object
    """
    
    print("Architecture File Integration")
    
    faust_generated_arch_file = os.path.join(cfg.temp_dir, f"{cfg.dsp_filename}.cpp")
    faust_generated_destination = os.path.join(cfg.output_dir, cfg.plugin_name, "SoundEnginePlugin/faustdsp.cpp")
    
    if not os.path.isfile(faust_generated_arch_file):
        print(f"Error: Faust-generated file not found: {faust_generated_arch_file}")
        sys.exit(cfg.ERR_FAUST_COMPILE)
            
    shutil.copy2(faust_generated_arch_file, faust_generated_destination)
    print(f"OK : Copied Faust DSP to: {faust_generated_destination}")

def replace_custom_templates(cfg) -> None:
    """
    Replaces the generated plugin files with custom template files that include placeholders.
    These placeholders are used to inject the Faust logic into the Wwise plugin logic, using 
    a patch-based method.
    Args:
        cfg (Config): the configuration object
    """
    print("Replacing generated files with custom templates...")
    
    # Define the list of template files to replace (these contain {name} placeholders)
    template_files = [
        f"SoundEnginePlugin/ProjectName{cfg.plugin_suffix}.h",
        f"SoundEnginePlugin/ProjectName{cfg.plugin_suffix}.cpp",
        f"SoundEnginePlugin/ProjectName{cfg.plugin_suffix}Params.h",
        f"SoundEnginePlugin/ProjectName{cfg.plugin_suffix}Params.cpp",
        "WwisePlugin/ProjectNamePlugin.cpp"
    ]
    
    # Define the corresponding target files (using actual plugin name)
    target_files = [
        f"SoundEnginePlugin/{cfg.plugin_name}{cfg.plugin_suffix}.h",
        f"SoundEnginePlugin/{cfg.plugin_name}{cfg.plugin_suffix}.cpp",
        f"SoundEnginePlugin/{cfg.plugin_name}{cfg.plugin_suffix}Params.h",
        f"SoundEnginePlugin/{cfg.plugin_name}{cfg.plugin_suffix}Params.cpp",
        f"WwisePlugin/{cfg.plugin_name}Plugin.cpp"
    ]
    
    target_dir = os.path.join(cfg.output_dir, cfg.plugin_name)

    if os.path.isdir(target_dir):
        print("Replacing specific SoundEnginePlugin files...")
        
        for template, target in zip(template_files, target_files):
            template_path = os.path.join(cfg.wwise_template_dir, template)
            target_path = os.path.join(target_dir, target)
            
            if os.path.isfile(template_path):
                # Read template and replace placeholders
                with open(template_path, 'r') as f:
                    content = f.read()
                
                # Replace the ${name} placeholders with cfg.plugin name
                content = content.replace('${name}', cfg.plugin_name)
                                    
                # Write to target file
                with open(target_path, 'w') as f:
                    f.write(content)
                
                print(f"OK : Replaced: {target} with {template}")
            else:
                print(f"ERROR: Template file not found: {template_path}")
        
        print("OK: Custom templates applied successfully!")
    else:
        print(f"ERROR: Target directory {target_dir} not found")
        sys.exit(cfg.ERR_INTEGRATION)


def modify_lua_build_script(cfg) -> None:
    """
    Modifies the Lua build script (`PremakePlugin.lua`) injecting faust include directories at specific parts 
    of its content.
    """
    print("Modifying Lua build script for Faust includes...")
    
    original_dir = os.getcwd()
    plugin_dir = os.path.join(cfg.output_dir, cfg.plugin_name)
    os.chdir(plugin_dir)
    
    premake_file = "PremakePlugin.lua"
    if not os.path.isfile(premake_file):
        print(f"ERROR {cfg.ERR_INTEGRATION}: Could not find {premake_file}")
        sys.exit(cfg.ERR_INTEGRATION)
    
    with open(premake_file, 'r', encoding='utf-8') as f:
        lines = f.readlines()
    
    sections = [
        'Plugin.sdk.static.includedirs',
        'Plugin.sdk.shared.includedirs',
        'Plugin.authoring.includedirs'
    ]
    
    new_lines = []
    inside_section = False
    
    for i, line in enumerate(lines):
        stripped = line.strip()
        
        # Check if starting a section block
        if any(line.startswith(section) and '=' in line for section in sections):
            inside_section = True
            new_lines.append(line)
            continue
        
        # If inside a section, look for the line that contains just the closing brace '}'
        if inside_section:
            if stripped == '}':

                # Walk backwards to check if faust path exists
                already_added = False
                for check_line in reversed(new_lines):
                    if str(cfg.faust_include_dir) in check_line:
                        already_added = True
                        break
                    if check_line.strip() == '':  # empty line - skip
                        continue
                    if check_line.strip() == '{':  # hit start of block, stop checking
                        break
                
                if not already_added:
                    # Insert with the same indentation as the closing brace
                    indent = line[:line.index('}')]
                    insert_line = f'{indent}"{cfg.faust_include_dir.as_posix()}",\n' # convert to posix path before replacing
                    new_lines.append(insert_line)
                
                new_lines.append(line)
                inside_section = False
                continue
        
        # Normal line outside or inside section
        new_lines.append(line)
    
    # Writing back ..
    with open(premake_file, 'w', encoding='utf-8') as f:
        f.writelines(new_lines)
    
    print("OK : Updated Lua build script with Faust include paths")
    os.chdir(original_dir)