#!/usr/bin/env python3
"""
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

        print("OK : Preliminary step was completed successfully!")

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

        print("OK : DSP compiling step was completed successfully!")
    
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
        print("OK : Generation step was completed successfully!")

    # =========================================================================
    # STEP 3: INTEGRATION STEP (DSP ONLY)
    # =========================================================================
    
    def integration_step(self):

        print("------------------------------------------Step 3: Integration Step")
        
        try:
            integrator.architecture_file_integration(self.cfg) # edit the exported arch file
            integrator.replace_custom_templates(self.cfg) # replace the vital for the integration files
            integrator.parameter_integration(self.cfg) # integrate parameters
            integrator.modify_lua_build_script(self.cfg) # additional step : TODO ought to be absorbed by the replaceCustomTemplates
                                        # .. or by the integrator instead
        except Exception as e:
            print(f"Error {self.ERR_INTEGRATION}: Failed to integrate parameters")
            print(f"Exception: {e}")
            sys.exit(self.ERR_INTEGRATION)

        print("OK : Integration step was completed successfully!")

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

        print("OK : Configuring step was completed successfully!")
    
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

        print("OK : Building step was completed successfully!")
            
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
        
        print("OK : Cleaning step was completed successfully!")

    # =========================================================================
    # MAIN EXECUTION
    # =========================================================================
    
    def orchestrate(self, args=None):

        print(f"Converting {self.dsp_file or 'DSP file'} to Wwise plugin...")
    
        self.setup_environment(args)    # preliminary step
        self.compile_dsp_file()         # step 1
        self.generate_wwise_project()   # step 2
        self.integration_step()         # step 3
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