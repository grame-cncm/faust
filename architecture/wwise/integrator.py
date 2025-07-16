import json
import os
import sys
import shutil
from pathlib import Path
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

def add_number_suffix_to_shortnames(ui_tree):

    def recurse(items, counter):
        for item in items:
            if "shortname" in item:
                item["unq_shortname"] = f"{item['shortname']}{counter}"
                counter += 1
            if "items" in item:
                counter = recurse(item["items"], counter)
        return counter

    recurse(ui_tree, 1)

def parameter_integration(cfg):

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

    # uniquify_shortnames by adding a new key in the dict. 
    # This is done for defining unique rtpc values.
    # Note: Faust UI elements support groups of elements so that different groups may contain elements with the same name
    # However, currently we do not support this grouping of elements, but we serialize all ui elements under the same umberella.
    # Therefore, uniquifying UI elements is done to discard the concern of two parameters sharing the same name in different depths of the nested ui dictionary of the exported faust compiled program.
    add_number_suffix_to_shortnames(faustdata["ui"]) 

    parameters_data = extract_parameters(faustdata["ui"])

    print(f"OK : Succesfully extracted parameters from {cfg.json_file} file.")

    parameters = [Parameter(d) for d in parameters_data]
    processor = TemplateProcessor(parameters)


    for file in target_files:
        file = os.path.join(cfg.output_dir, cfg.plugin_name, file)
        processor.process_file(file)
    xml_file = os.path.join(cfg.output_dir, cfg.plugin_name, xml_file)

    inject_properties_to_xml(parameters, xml_file)

def faust_dspfile_integration(cfg):
    # Copy generated faust dsp file to SoundEnginePlugin dir

    print("Architecture File Integration")
    
    faust_generated_arch_file = os.path.join(cfg.temp_dir, f"{cfg.dsp_filename}.cpp")
    faust_generated_destination = os.path.join(cfg.output_dir, cfg.plugin_name, "SoundEnginePlugin/faustdsp.cpp")
    
    if not os.path.isfile(faust_generated_arch_file):
        print(f"Error: Faust-generated file not found: {faust_generated_arch_file}")
        sys.exit(cfg.ERR_FAUST_COMPILE)
            
    shutil.copy2(faust_generated_arch_file, faust_generated_destination)
    print(f"OK : Copied Faust DSP to: {faust_generated_destination}")

def replace_custom_templates(cfg):

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


def modify_lua_build_script(cfg):
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
    current_section = None
    
    for i, line in enumerate(lines):
        stripped = line.strip()
        
        # Check if starting a section block
        if any(line.startswith(section) and '=' in line for section in sections):
            inside_section = True
            # Remember which section we are in (not strictly necessary here)
            current_section = next(section for section in sections if line.startswith(section))
            new_lines.append(line)
            continue
        
        # If inside a section, look for the line that contains just the closing brace '}'
        if inside_section:
            if stripped == '}':
                # Insert your include path line before this closing brace if not already present
                # But first check if faust include path already in previous lines in this block
                block_start_idx = len(new_lines) - 1
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
                current_section = None
                continue
        
        # Normal line outside or inside section
        new_lines.append(line)
    
    # Writing back ..
    with open(premake_file, 'w', encoding='utf-8') as f:
        f.writelines(new_lines)
    
    print("OK : Updated Lua build script with Faust include paths")
    os.chdir(original_dir)