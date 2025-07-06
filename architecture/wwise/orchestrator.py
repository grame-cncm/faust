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
import shutil
from pathlib import Path
import integrator
import config
import utils
import jsoninjector

class Faust2WwiseOrchestrator:
    def __init__(self, wwiseroot , faust_lib_dir, faust_include_dir):
        
        self.cfg = config.Config(wwiseroot , faust_lib_dir, faust_include_dir)

    def __getattr__(self, name):
        if hasattr(self.cfg, name):
            return getattr(self.cfg, name)
        raise AttributeError(f"'{self.__class__.__name__}' object has no attribute '{name}'")

    def __setattr__(self, name, value):
        if name == 'cfg' or name not in getattr(self, 'cfg', {}).__dict__:
            super().__setattr__(name, value)
        else:
            setattr(self.cfg, name, value)

    # =========================================================================
    # PRELIMINARY/PREPARATION STEP: SETUP AND VALIDATION 
    # =========================================================================
    
    def setup_environment(self, args=None):

        print("------------------------------------------Preliminary Step : setup and validate environment")
        
        utils.parse_arguments(self.cfg,args)
        # self.setup_platform_paths() # This is discarded, not needed now!
        
        if self.dsp_file:
            self.dsp_filename = Path(self.dsp_file).stem # extract name without extension
            self.plugin_name = utils.ensure_valid_plugin_name(self.dsp_filename) # Conform to the plugin name restrictions (Capitalized, first letter cannot be a number)
                
        current_dir = os.getcwd()
        if (not self.output_dir):
            self.output_dir = os.path.join(current_dir,self.dsp_filename)
        self.temp_dir = os.path.join(self.output_dir, self.temp_dir)
        
        os.makedirs(self.output_dir, exist_ok=True)
        os.makedirs(self.temp_dir, exist_ok=True)
        
        utils.validate_environment(self.cfg)
        self.cfg.print()

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
        
        utils.run_system_command(cmd, self.ERR_FAUST_COMPILE)
        
        jsoninjector.process_json_configuration(self.cfg)
    
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
        
        utils.run_system_command(cmd, self.ERR_GENERATION)
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
            
            integrator.integrateParameters(
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

        utils.run_system_command(cmd, self.ERR_CONFIGURATION)
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
        
        utils.run_system_command(cmd, self.ERR_BUILD)
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
        # self.cleanup()                  # outro
        
        print("")
        print("=====================================")
        print("Faust2Wwise conversion completed!")
        print(f"Generated plugin: {self.plugin_name}")
        print(f"Location: {os.path.join(self.output_dir, self.plugin_name)}")
        print("=====================================")
        print("")