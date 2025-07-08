import sys
import os
import shutil
import json
from utils import ensure_valid_plugin_name

def process_json_configuration(cfg):
    
    print("Parsing json configuration file..")
    
    # Move JSON file to temp directory
    json_source = f"{cfg.dsp_file}.json"
    cfg.json_file = os.path.join(cfg.temp_dir, f"{cfg.dsp_file}.json")
    
    if os.path.exists(json_source):
        shutil.move(json_source, cfg.json_file)
    
    if not os.path.isfile(cfg.json_file):
        print(f"Error {cfg.ERR_JSON_PARSE}: JSON file not found at {cfg.json_file}")
        sys.exit(cfg.ERR_JSON_PARSE)
    
    try:
        # Fix the invalid JSON syntax due to unescaped backslashes in the Windows paths issue,
        # ...by escaping backslashes
        with open(cfg.json_file, 'r') as f:
            content = f.read()            
        # Check for Windows-like paths and fix backslashes
        if any(c + ':\\' in content for c in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'):
            content = content.replace('\\', '\\\\')
            with open(cfg.json_file, 'w') as f:
                f.write(content)
        
        # Parse JSON
        with open(cfg.json_file, 'r') as f:
            json_data = json.load(f)
        
        # Extract inputs/outputs
        dsp_inputs = json_data.get('inputs', 0)
        dsp_outputs = json_data.get('outputs', 0)
        
        # Determine plugin type based on inputs
        if dsp_inputs > 0:
            cfg.plugin_type = "effect"
            cfg.plugin_suffix = "FX"
            #TODO: FX can be in-place and out-of-place
        else:
            cfg.plugin_type = "source"
            cfg.plugin_suffix = "Source"
        
        #Set the wwise_template_dir, the directory where the wwise template files are stored 
        cfg.wwise_template_dir = os.path.join(cfg.faust_lib_dir, "wwise", cfg.patch_version or "default", cfg.plugin_type) 
        if (cfg.plugin_type == "effect"):
            cfg.wwise_template_dir = cfg.wwise_template_dir+" ("+cfg.wwise_plugin_interface+")" # append the {space}(in-place) or {space}(out-of-place) at the end

        # Extract project name & override in case it is provided as a declaration in faust dsp file
        # i.e. declare name "Name"
        temp_plugin_name = json_data.get('name')
        if temp_plugin_name:
            cfg.plugin_name = ensure_valid_plugin_name(temp_plugin_name) # Conform to the plugin name restrictions (Capitalized, first letter cannot be a number)
            print(f"PLUGIN_NAME changed to {cfg.plugin_name}")
        
        # extract author from meta dict
        meta = json_data.get('meta', [])
        cfg.author = "Unknown"
        for item in meta:
            if isinstance(item, dict) and 'author' in item:
                cfg.author = item['author']
                break
        
        # Extract description from meta dict
        cfg.description = "No description provided"
        for item in meta:
            if isinstance(item, dict) and 'description' in item:
                cfg.description = item['description']
                break
        
        print("================================")
        print("DSP file plugin config")
        print("================================")
        print(f"plugin_type {cfg.plugin_type}")
        print(f"plugin_name {cfg.plugin_name}")
        print(f"author {cfg.author}")
        print(f"description {cfg.description}")
        print("================================")
        
    except json.JSONDecodeError as e:
        print(f"Error {cfg.ERR_JSON_PARSE}: Failed to parse JSON: {e}")
        sys.exit(cfg.ERR_JSON_PARSE)
    except Exception as e:
        print(f"Error {cfg.ERR_JSON_PARSE}: Failed to process JSON configuration: {e}")
        sys.exit(cfg.ERR_JSON_PARSE)
    
    print(f"OK : {cfg.json_file} was parsed successfully!")
