#!/usr/bin/env python3
"""

comment : first working Python converted version of the original bash script

Next change is to identify the platform specific variables ( apart from variables any other part of the code ? Cause not sure .. ) and isolate it so as to address the way it is going to be utilized throughout this script structure.. 

@Documentation :
The Faust2Wwise conversion process is applied with the following steps:
    Preliminary/Preparation Step: Setup and Validation
        Declare all variables
        Define basic script functions
        Preprocessing & Initialization (i.e. platform paths depending on the platform (win/macOs))
        Validate environment providing checks
        Prepare the ground in general
    Step 1: Faust DSP Compilation
        Compile dsp file
        Extract DSP json description
        JSON Configuration Processing
            Initialize/override value of
                PLUGIN_TYPE
                PLUGIN_NAME
                AUTHOR
                DESCRIPTION
    Step 2: Wwise Plugin Project Generation
        Use Wwise wp.py script to create plugin project structure, generating the plugin template files
    Step 3: Integration step (DSP only)
        Copy generated Faust DSP file to plugin SoundEngine directory
        Replace plugin header and source (cpp) file in the SoundEnginePlugin directory
        Update Lua build script (PremakePlugin.lua) to include Faust headers
    Step 4: Configuration step
        Use Wwise wp.py with `premake` to configure project before building
    Step 5: Plugin Compilation
        Use Wwise wp.py build command with Release configuration
        Generate static and dynamic libraries for Wwise integration
    Outro step: Cleanup
        Remove temporary files
"""

import os
import sys
import argparse
import subprocess
import json
import shutil
from pathlib import Path
import platform
from integrator import integrateParameters
import pdb


class Faust2WwiseOrchestrator:
    def __init__(self, wwiseroot , faust_lib_dir, faust_include_dir):
        
        ################################################ paths
        self.faust_lib_dir = faust_lib_dir
        self.faust_include_dir = faust_include_dir
        self.archfile = os.path.join(self.faust_lib_dir, "wwise.cpp")
        
        ################################################ Wwise stuff
        self.wwiseroot = wwiseroot
        # self.wp_script = os.path.join(self.wwiseroot, "Scripts", "Build", "Plugins", "wp.py")
        self.wp_script = os.path.join(self.wwiseroot, "Scripts/Build/Plugins/wp.py")
        # self.wwiseroot_msys = ""
        self.patch_version = ""
        self.wwise_template_dir = ""
        
        ############################################### faust parameters obta
        # Project configuration
        ### script arguments
        self.output_dir = None
        self.faust_options = ""
        self.dsp_file = ""
        self.json_file = ""
        ### additional
        self.dsp_filename = ""
        
        ################################################ plugin config
        self.plugin_type = ""
        self.plugin_name = ""
        self.plugin_suffix = ""
        self.author = ""
        self.description = ""
        
        ################################################ helper vars
        self.temp_dir = "_temp_" # Temp dir to store temp data ( i.e. jsonfile )

        ################################################ error codes
        self.ERR_INVALID_INPUT = 2
        self.ERR_ENVIRONMENT = 3
        self.ERR_FAUST_COMPILE = 4
        self.ERR_JSON_PARSE = 5
        self.ERR_GENERATION = 6
        self.ERR_INTEGRATION = 7
        self.ERR_CONFIGURATION = 8
        self.ERR_BUILD = 9

    # =========================================================================
    # PRELIMINARY/PREPARATION STEP: SETUP AND VALIDATION 
    # =========================================================================
    
    # help utility using Faust standard approach
    def print_usage(self):
        print("faust2wwise [options] file.dsp")
        print("Converts Faust DSP files to Wwise plugins")
        print("")
        print("Platform: Windows/macOS/Linux with Wwise SDK")
        print("")
        print("Requirements: Wwise SDK, Faust compiler, Python")
        print("")
        print("Options:")
        print("  -h, --help     Show this help message")
        print("  -o <dir>       Output directory (default: current directory)")
        print("")
        print("Example:")
        print("  faust2wwise sine.dsp")
        sys.exit(1)
    
    def parse_arguments(self, args=None):

        parser = argparse.ArgumentParser(description="Converts Faust DSP files to Wwise plugins",
                                         add_help=False)
        parser.add_argument('-h', '--help', action='store_true', help='Show help message')
        parser.add_argument('-o', '--output_dir', help='Output directory')
        parser.add_argument('dsp_file', nargs='?', help='DSP file to convert')
        parser.add_argument('faust_options', nargs='*', help='Additional Faust options')
        
        if args is None:
            args = sys.argv[1:]
        
        parsed_args, unknown_args = parser.parse_known_args(args)
        
        if parsed_args.help:
            self.print_usage()
        
        if parsed_args.output_dir:
            self.output_dir = parsed_args.output_dir
        
        if parsed_args.dsp_file:
            self.dsp_file = parsed_args.dsp_file
            self.dsp_file = os.path.join(os.getcwd(), self.dsp_file )
        
        all_faust_options = (parsed_args.faust_options or []) + unknown_args
        self.faust_options = " ".join(all_faust_options)
        # TODO: extend here with wwise related configuration options?
        self.faust_options = self.faust_options.split() if isinstance(self.faust_options, str) else (self.faust_options or [])

        # pdb.set_trace()
    
    def print_configuration(self):
        print("------------------------------------------")
        print("FAUST2WWISE CONFIGURATION")
        print("------------------------------------------")
        print(f"TEMP_DIR {self.temp_dir}")
        print("========== FAUST CONFIGURATION ===========")
        print(f"DSP_FILE {self.dsp_file}")
        print(f"ARCHFILE {self.archfile}")
        print(f"FAUSTARCH {os.environ.get('FAUSTARCH', '')}")
        print(f"FAUSTLIB {os.environ.get('FAUSTLIB', '')}")
        print(f"FAUST_LIB_DIR: {self.faust_lib_dir}")
        print(f"FAUSTINC {os.environ.get('FAUSTINC', '')}")
        print(f"FAUST_INCLUDE_DIR: {self.faust_include_dir}")
        print(f"OUTPUT_DIR {self.output_dir}")
        print(f"FAUST_OPTIONS {self.faust_options}")
        print("=========== WWISE CONFIGURATION===========")
        print(f"WWISEROOT {self.wwiseroot}")
        print("========== PLUGIN CONFIGURATION ==========")
        print(f"PLUGIN_TYPE {self.plugin_type}")
        print(f"PLUGIN_NAME {self.plugin_name}")
        print(f"AUTHOR {self.author}")
        print(f"DESCRIPTION {self.description}")
        print(f"DSP_FILENAME {self.dsp_filename}")
        print("------------------------------------------")
    
    def validate_environment(self):
        
        # Check if WWISEROOT is set
        if not self.wwiseroot:
            print(f"Error {self.ERR_ENVIRONMENT}: WWISEROOT environment variable is not set.")
            print("Please set it to your Wwise installation directory or make sure wwise is installed.")
            sys.exit(self.ERR_ENVIRONMENT)
        
        # Check if dsp file provided
        if not self.dsp_file:
            print(f"Error {self.ERR_INVALID_INPUT}: No DSP file provided")
            self.print_usage()
            sys.exit(self.ERR_INVALID_INPUT)
        
        # Check if the given dsp file exists
        if not os.path.isfile(self.dsp_file):
            print(f"Error {self.ERR_INVALID_INPUT}: DSP file '{self.dsp_file}' not found")
            sys.exit(self.ERR_INVALID_INPUT)

        # Check if architecture file exists
        if not os.path.isfile(self.archfile):
            print(f"Error {self.ERR_ENVIRONMENT}: Wwise architecture file not found at {self.archfile}")
            print(f"Make sure the wwise.cpp architecture file is installed in {self.faust_lib_dir}")
            sys.exit(self.ERR_ENVIRONMENT)
    
    def setup_environment(self, args=None):

        print("------------------------------------------Preliminary Step : setup and validate environment")
        
        self.parse_arguments(args)
        # self.setup_platform_paths() # This is discarded, not needed now!
        
        if self.dsp_file:
            self.dsp_filename = Path(self.dsp_file).stem # extract name without extension
            self.plugin_name = self.dsp_filename.capitalize() #capitalize first letter
                
        current_dir = os.getcwd()
        if (not self.output_dir):
            self.output_dir = os.path.join(current_dir,self.dsp_filename)
        self.temp_dir = os.path.join(self.output_dir, self.temp_dir)
        
        os.makedirs(self.output_dir, exist_ok=True)
        os.makedirs(self.temp_dir, exist_ok=True)
        
        self.validate_environment()
        self.print_configuration()

    def run_system_command(self, cmd, error_code=None):
    
        # Run a system based command with consistent output and error handling.
        
        print("Running command:", " ".join(cmd))

        try:
            result = subprocess.run(
                cmd,
                check=True,
                # capture_output=True,
                # text=True,
            )
            if result.stdout:
                print(result.stdout.strip())
            if result.stderr:
                print(result.stderr.strip())
            return result

        except subprocess.CalledProcessError as e:
            print("Error: Command failed:", " ".join(cmd))
            if e.stdout:
                print(e.stdout.strip())
            if e.stderr:
                print(e.stderr.strip())
            print(f"Exiting with error code {error_code or e.returncode}")
            sys.exit(error_code or e.returncode)

    # =========================================================================
    # FAUST COMPILATION
    # =========================================================================
    
    def compile_dsp_file(self):

        print("------------------------------------------Step 1: Compiling Faust DSP to C++")
        
        output_file = os.path.join(self.temp_dir, f"{self.dsp_filename}.cpp")
                
        # Build faust command
        cmd = [
            "faust",
            "-json",
            "-a", self.archfile,
            *self.faust_options,
            self.dsp_file,
            "-o", output_file
        ]
        
        self.run_system_command(cmd, self.ERR_FAUST_COMPILE)
        
        self.process_json_configuration()
      
    def process_json_configuration(self):
        
        print("Parsing json configuration file..")
        
        # Move JSON file to temp directory
        json_source = f"{self.dsp_file}.json"
        self.json_file = os.path.join(self.temp_dir, f"{self.dsp_file}.json")
        
        if os.path.exists(json_source):
            shutil.move(json_source, self.json_file)
        
        if not os.path.isfile(self.json_file):
            print(f"Error {self.ERR_JSON_PARSE}: JSON file not found at {self.json_file}")
            sys.exit(self.ERR_JSON_PARSE)
        
        try:
            # Fix the invalid JSON syntax due to unescaped backslashes in the Windows paths issue,
            # ...by escaping backslashes
            with open(self.json_file, 'r') as f:
                content = f.read()            
            # Check for Windows-like paths and fix backslashes
            if any(c + ':\\' in content for c in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'):
                content = content.replace('\\', '\\\\')
                with open(self.json_file, 'w') as f:
                    f.write(content)
            
            # Parse JSON
            with open(self.json_file, 'r') as f:
                json_data = json.load(f)
            
            # Extract inputs/outputs
            dsp_inputs = json_data.get('inputs', 0)
            dsp_outputs = json_data.get('outputs', 0)
            
            # Determine plugin type based on inputs
            if dsp_inputs > 0:
                self.plugin_type = "effect"
                self.plugin_suffix = "FX"
                #TODO: FX can be in-place and out-of-place
            else:
                self.plugin_type = "source"
                self.plugin_suffix = "Source"
            
            #Set the wwise_template_dir, the directory where the wwise template files are stored 
            self.wwise_template_dir = os.path.join(self.faust_lib_dir, "wwise", self.patch_version or "default", self.plugin_type) 

            # Extract project name & override in case it is provided as a declaration in faust dsp file
            # i.e. declare name "Name"
            temp_plugin_name = json_data.get('name')
            if temp_plugin_name:
                self.plugin_name = temp_plugin_name
                print(f"PLUGIN_NAME changed to {self.plugin_name}")
            
            # extract author from meta dict
            meta = json_data.get('meta', [])
            self.author = "Unknown"
            for item in meta:
                if isinstance(item, dict) and 'author' in item:
                    self.author = item['author']
                    break
            
            # Extract description from meta dict
            self.description = "No description provided"
            for item in meta:
                if isinstance(item, dict) and 'description' in item:
                    self.description = item['description']
                    break
            
            print(f"PLUGIN_TYPE {self.plugin_type}")
            print(f"PLUGIN_NAME {self.plugin_name}")
            print(f"AUTHOR {self.author}")
            print(f"DESCRIPTION {self.description}")
            
        except json.JSONDecodeError as e:
            print(f"Error {self.ERR_JSON_PARSE}: Failed to parse JSON: {e}")
            sys.exit(self.ERR_JSON_PARSE)
        except Exception as e:
            print(f"Error {self.ERR_JSON_PARSE}: Failed to process JSON configuration: {e}")
            sys.exit(self.ERR_JSON_PARSE)
        
        print(f"OK : {self.json_file} was parsed successfully!")

    # =========================================================================
    # GENERATE PROJECT
    # =========================================================================
    
    def generate_wwise_project(self):
        
        print("------------------------------------------Step 2: Generating Wwise plugin project")
        
        # Change to output directory
        original_dir = os.getcwd()
        os.chdir(self.output_dir)
            
        cmd = [
            "python", self.wp_script, "new", f"--{self.plugin_type}",
            "--name", self.plugin_name,
            "--display-name", self.plugin_name,
            "--author", self.author,
            "--description", self.description,
            "--no-prompt"
        ]
        
        self.run_system_command(cmd, self.ERR_GENERATION)
        os.chdir(original_dir)

    # =========================================================================
    # STEP 3: INTEGRATION STEP (DSP ONLY)
    # =========================================================================
    
    def integrate_dsp_files(self):

        print("------------------------------------------Step 3: Integration Step")
        
        self.architecture_file_integration() # edit the exported arch file
        self.replace_custom_templates() # replace the vital for the integration files
        self.parameter_integration() # integrate parameters
        self.modify_lua_build_script() # additional step : TODO ought to be absorbed by the replaceCustomTemplates
                                        # .. or by the integrator instead
    
    def architecture_file_integration(self):
        # Copy generated faust dsp file to SoundEnginePlugin dir

        print("Architecture File Integration")
        
        faust_generated_arch_file = os.path.join(self.temp_dir, f"{self.dsp_filename}.cpp")
        faust_generated_destination = os.path.join(self.output_dir, self.plugin_name, "SoundEnginePlugin/faustdsp.cpp")
        
        if not os.path.isfile(faust_generated_arch_file):
            print(f"Error: Faust-generated file not found: {faust_generated_arch_file}")
            sys.exit(self.ERR_FAUST_COMPILE)
                
        shutil.copy2(faust_generated_arch_file, faust_generated_destination)
        print(f"OK : Copied Faust DSP to: {faust_generated_destination}")
    
    def replace_custom_templates(self):

        print("Replacing generated files with custom templates...")
        
        # Define the list of template files to replace (these contain {name} placeholders)
        template_files = [
            f"SoundEnginePlugin/ProjectName{self.plugin_suffix}.h",
            f"SoundEnginePlugin/ProjectName{self.plugin_suffix}.cpp",
            f"SoundEnginePlugin/ProjectName{self.plugin_suffix}Params.h",
            f"SoundEnginePlugin/ProjectName{self.plugin_suffix}Params.cpp",
            "WwisePlugin/ProjectNamePlugin.cpp"
        ]
        
        # Define the corresponding target files (using actual plugin name)
        target_files = [
            f"SoundEnginePlugin/{self.plugin_name}{self.plugin_suffix}.h",
            f"SoundEnginePlugin/{self.plugin_name}{self.plugin_suffix}.cpp",
            f"SoundEnginePlugin/{self.plugin_name}{self.plugin_suffix}Params.h",
            f"SoundEnginePlugin/{self.plugin_name}{self.plugin_suffix}Params.cpp",
            f"WwisePlugin/{self.plugin_name}Plugin.cpp"
        ]
        
        target_dir = os.path.join(self.output_dir, self.plugin_name)

        if os.path.isdir(target_dir):
            print("Replacing specific SoundEnginePlugin files...")
            
            for template, target in zip(template_files, target_files):
                template_path = os.path.join(self.wwise_template_dir, template)
                target_path = os.path.join(target_dir, target)
                
                if os.path.isfile(template_path):
                    # Read template and replace placeholders
                    with open(template_path, 'r') as f:
                        content = f.read()
                    
                    # Replace the ${name} placeholders with self.plugin name
                    content = content.replace('${name}', self.plugin_name)
                                        
                    # Write to target file
                    with open(target_path, 'w') as f:
                        f.write(content)
                    
                    print(f"OK : Replaced: {target} with {template}")
                else:
                    print(f"ERROR: Template file not found: {template_path}")
            
            print("OK: Custom templates applied successfully!")
        else:
            print(f"ERROR: Target directory {target_dir} not found")
            sys.exit(self.ERR_INTEGRATION)
    
    def parameter_integration(self):
        print("Integrating parameters...")

        try:
            
            integrateParameters(
                self.output_dir, 
                self.plugin_name, 
                self.plugin_suffix, 
                self.json_file
            )
            
        except Exception as e:
            print(f"Error {self.ERR_INTEGRATION}: Failed to integrate parameters")
            print(f"Exception: {e}")
            sys.exit(self.ERR_INTEGRATION)

    def modify_lua_build_script(self):
        print("Modifying Lua build script for Faust includes...")
        
        original_dir = os.getcwd()
        plugin_dir = os.path.join(self.output_dir, self.plugin_name)
        os.chdir(plugin_dir)
        
        premake_file = "PremakePlugin.lua"
        if not os.path.isfile(premake_file):
            print(f"ERROR {self.ERR_INTEGRATION}: Could not find {premake_file}")
            sys.exit(self.ERR_INTEGRATION)
        
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
                        if self.faust_include_dir in check_line:
                            already_added = True
                            break
                        if check_line.strip() == '':  # empty line - skip
                            continue
                        if check_line.strip() == '{':  # hit start of block, stop checking
                            break
                    
                    if not already_added:
                        # Insert with the same indentation as the closing brace
                        indent = line[:line.index('}')]
                        insert_line = f'{indent}"{Path(self.faust_include_dir).as_posix()}",\n' # convert to posix path before replacing
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

    #==============================================================================
    # CONFIGURE(PREMAKE) & BUILD 
    #==============================================================================
    
    def configure_wwise_project(self):

        print("------------------------------------------Step 4: Configuring project files")
        
        original_dir = os.getcwd()
        plugin_dir = os.path.join(self.output_dir, self.plugin_name)
        os.chdir(plugin_dir)
        
        cmd = ["python", self.wp_script, "premake", "Authoring"]

        self.run_system_command(cmd, self.ERR_CONFIGURATION)
        os.chdir(original_dir)
    
    def build_plugin(self):

        print("------------------------------------------Step 5: Building plugin")
        
        original_dir = os.getcwd()
        plugin_dir = os.path.join(self.output_dir, self.plugin_name)
        os.chdir(plugin_dir)
        
        cmd = [
            "python", self.wp_script, "build",
            "-c", "Release",
            "-x", "x64", 
            "-t", "vc170",
            "Authoring"
        ]
        
        self.run_system_command(cmd, self.ERR_BUILD)
        os.chdir(original_dir)
            

    #==============================================================================
    # CLEANING
    #==============================================================================
    
    def cleanup(self):

        print("------------------------------------------Outro")
        print(f"# Cleaning up temporary files ({self.temp_dir})")
        
        try:
            if os.path.exists(self.temp_dir):
                shutil.rmtree(self.temp_dir)
                print(f"Cleaned up temporary directory: {self.temp_dir}")
        except Exception as e:
            print(f"Warning: Could not clean up temporary directory: {e}")

    # =========================================================================
    # MAIN EXECUTION
    # =========================================================================
    
    def orchestrate(self, args=None):

        print(f"Converting {self.dsp_file or 'DSP file'} to Wwise plugin...")
    
        self.setup_environment(args)    # preliminary step
        self.compile_dsp_file()         # step 1
        self.generate_wwise_project()   # step 2
        self.integrate_dsp_files()      # step 3
        self.configure_wwise_project()  # step 4
        self.build_plugin()             # step 5
        self.cleanup()                  # outro
        
        print("")
        print("=====================================")
        print("Faust2Wwise conversion completed!")
        print(f"Generated plugin: {self.plugin_name}")
        print(f"Location: {os.path.join(self.output_dir, self.plugin_name)}")
        print("=====================================")
        print("")