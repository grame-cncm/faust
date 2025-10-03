#!/usr/bin/env python3
"""
The Faust2Wwise conversion process is applied with the following steps:
    Preliminary/Preparation Step: Setup and Validation
        - intialize config
        - setup_environment and validate environment providing checks
    Step 1: Faust DSP Compilation
        - Compile dsp file and extract DSP json description
        - JSON Configuration Processing to initialize plugin configuration
    Step 2: Wwise Plugin Project Generation
        - Use Wwise wp.py script to create plugin project structure, generating the plugin template files
    Step 3: Integration step
        - Copy generated Faust DSP file to plugin SoundEngine directory
        - Replace template files with the generated files of the wwise plugin project
        - Integrate Faust into Wwise using a patch based method
        - Update Lua build script (PremakePlugin.lua) to include Faust headers
    Step 4: Configuration step
        - Use Wwise wp.py with `premake` to configure project before building
    Step 5: Plugin Compilation
        - Use Wwise wp.py build command to build the Wwise plugin
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
import jsonprocessor
from spkcfg import speaker_config_options
from typing import List,Optional

class Faust2WwiseOrchestrator:
    """
    Orchestrates the complete process of converting a Faust DSP file into a Wwise plugin,
    including the following steps:
      1. Validating environment and preparing config
      2. Compiling Faust DSP to C++ using architecture files and define plugin configuration
      3. Generating a Wwise plugin project
      4. Integrating compiled DSP code and metadata
      5. Running premake configuration and building the plugin
      6. Cleaning up temporary files
    """
        
    def __init__(self, wwiseroot:Path , faust_dsp_dir:Path, faust_include_dir:Path):
        
        self.cfg = config.Config(wwiseroot , faust_dsp_dir, faust_include_dir)

    def __getattr__(self, name:str):
        """
        This allows accessing configuration properties directly on the orchestrator with self instead of self.cfg
        For instance, `self.plugin_name` is used instead of `self.cfg.plugin_name`.
        """
        if hasattr(self.cfg, name):
            return getattr(self.cfg, name)
        raise AttributeError(f"'{self.__class__.__name__}' object has no attribute '{name}'")

    def __setattr__(self, name:str, value):
        """
        Allows modifying config values as if they were direct attributes of the orchestrator.
        """
        if name == 'cfg' or name not in getattr(self, 'cfg', {}).__dict__:
            super().__setattr__(name, value)
        else:
            setattr(self.cfg, name, value)

    # =========================================================================
    # PRELIMINARY/PREPARATION STEP: SETUP AND VALIDATION 
    # =========================================================================
    
    def setup_environment(self, args: Optional[List[str]]=None) -> None:
        """
        Sets up and validates environment, including the following steps:
        - parse arguments, 
        - initialize uninitialized configuration variables, 
        - create non existing directories, 
        - and validate environment.

        Args:
            args(List[str]): Optional list of arguments. If not provided, parse_arguments function makes 
            use of sys library to retrieve them.
        """
        
        if self.patch_version not in self.supportedWwiseVersions:
            sys.stderr.write(f"Unsupported Wwise version : {self.patch_version}. \
                Available Wwise (major) versions: {self.supportedWwiseVersions}")
            sys.exit(cfg.ERR_ENVIRONMENT)

        parsed_args = utils.parse_arguments(self.cfg, args)

        print("------------------------------------------Preliminary Step : setup and validate environment")

        # conditionally edit variables across different platforms (windows/macOs) 
        utils.platform_dependent_setup(self.cfg, parsed_args) 

        # Wwise-related options
        utils.create_wwise_config(self.cfg, parsed_args)

        if self.dsp_file:
            self.dsp_filename = Path(self.dsp_file).stem # extract name without extension
            self.plugin_name = utils.ensure_valid_plugin_name(self.dsp_filename) # Conform to the plugin name restrictions (Capitalized, first letter cannot be a number)
            self.json_file = os.path.join(self.temp_dir, f"{self.dsp_file}.json") # initialize json filepath

        # if the output_dir is not set, set it now accordingly 
        current_dir = os.getcwd()
        if (not self.output_dir):
            self.output_dir = os.path.join(current_dir,self.dsp_filename)
        self.temp_dir = os.path.join(self.output_dir, self.temp_dir)
        
        os.makedirs(self.output_dir, exist_ok=True)
        os.makedirs(self.temp_dir, exist_ok=True)

        # Set the path for storing the config after successful compilation
        self.cfg_json_path = os.path.join(self.output_dir, self.cfgJsonFileName)
        
        utils.validate_environment(self.cfg)
        
        self.cfg.print()
        
        print("OK : Preliminary step was completed successfully!")

    # =========================================================================
    # FAUST COMPILATION
    # =========================================================================
    
    def compile_dsp_file(self) -> None:
        """
        Compile the DSP file to a faustdsp.cpp file using Faust and inject parameter metadata 
        from the generated json file.
        """
        print("------------------------------------------Step 1: Compiling Faust DSP to C++")
        
        output_file = os.path.join(self.temp_dir, f"{self.dsp_filename}.cpp")
                
        # Build faust command
        cmd = [
            "faust",
            "-json",
            "-I", str(Path(self.faust_include_dir)),
            "-a", self.archfile,
            *self.faust_options,
            self.dsp_file,
            "-o", output_file
        ]
        
        if self.wwise_plugin_interface == "in-place":
            cmd.extend(["--in-place"])

        utils.run_system_command(cmd, self.ERR_FAUST_COMPILE)
        
        jsonprocessor.process_json_configuration(self.cfg)

        if (self.wwise_speaker_cfg_channel_mask and \
            self.num_outputs!=speaker_config_options[self.wwise_speaker_cfg_channel_mask]):
                print("Speaker configuration provided does not match with number of outputs supported by the Faust program.")
                print(f"Faust outputs: {self.num_outputs}")
                print(f"Channel config mask provided : {self.wwise_speaker_cfg_channel_mask} --> {speaker_config_options[self.wwise_speaker_cfg_channel_mask]} num channels")
                sys.exit(self.ERR_INVALID_INPUT)

        self.cfg.plugin_print() # print finalized configuration, after having parsed the faust't output json file
        self.cfg.lock()         # lock config to deprive any further modifications of its internal state, making it immutable
        self.cfg.to_json()      # save the config into a file immediately after locking

        print("OK : DSP compiling step was completed successfully!") 

    # =========================================================================
    # GENERATE PROJECT
    # =========================================================================
    
    def generate_wwise_project(self) -> None:
        """
        Generate a new Wwise plugin project using the Audiokinetic's wp python script.
        """
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

        if self.wwise_plugin_interface == "out-of-place":
            cmd.extend(["--out-of-place"])
        
        utils.run_system_command(cmd, self.ERR_GENERATION)
        os.chdir(original_dir)
        print("OK : Generation step was completed successfully!")

    # =========================================================================
    # STEP 3: INTEGRATION STEP (DSP ONLY)
    # =========================================================================
    
    def integration_step(self) -> None:
        """
        Perform the integration steps to integrate Faust into the generated plugin project,
        including the following steps:
            1.integrate the compiled dsp file into the wwise project,
            2.replace the customized template files with the ones generated by the wp tool,
            3.integrate parameters using the patch-based method into the template files,
            4.modify the lua script by injecting the faust include directory into the script 
        """
        print("------------------------------------------Step 3: Integration Step")
        
        try:
            integrator.faust_dspfile_integration(self.cfg) # integrate the compiled dsp file
            integrator.replace_custom_templates(self.cfg) # replace the vital for the integration files
            integrator.parameter_integration(self.cfg) # integrate parameters
            integrator.modify_lua_build_script(self.cfg) # inject faust includes within the lua script
            integrator.replace_channel_config_line(self.cfg) 
            
        except Exception as e:
            print(f"Error {self.ERR_INTEGRATION}: Failed to integrate parameters")
            print(f"Exception: {e}")
            sys.exit(self.ERR_INTEGRATION)

        print("OK : Integration step was completed successfully!")

    #==============================================================================
    # CONFIGURE(PREMAKE) & BUILD 
    #==============================================================================
    
    def configure_wwise_project(self) -> None:
        """
        Run the Wwise plugin configuration using "premake" command line argument.
        """        
        print("------------------------------------------Step 4: Configuring project files")
        
        original_dir = os.getcwd()
        plugin_dir = os.path.join(self.output_dir, self.plugin_name)
        os.chdir(plugin_dir)
        
        cmd = ["python", self.wp_script, "premake", self.wwise_platform]

        if self.wwise_toolset:
            cmd.extend(["--toolset", self.wwise_toolset])

        if self.wwise_debugger:
            cmd.append("--debugger")

        if self.wwise_disable_codesign:
            cmd.append("--disable-codesign")

        utils.run_system_command(cmd, self.ERR_CONFIGURATION)
        os.chdir(original_dir)

        print("OK : Configuring step was completed successfully!")
    
    def build_plugin(self) -> None:
        """
        Build the Wwise plugin using the build command line option.
        """
        print("------------------------------------------Step 5: Building plugin")
        
        original_dir = os.getcwd()
        plugin_dir = os.path.join(self.output_dir, self.plugin_name)
        os.chdir(plugin_dir)
        
        cmd = [
            "python", self.wp_script, "build",
            "-c", self.wwise_configuration,
            "-x", self.wwise_arch
        ]

        if self.wwise_toolset:
            cmd.extend(["--toolset", self.wwise_toolset])

        if self.wwise_build_hooks_file:
            cmd.extend(["--build-hooks-file", self.wwise_build_hooks_file])

        if self.wwise_toolchain_vers:
            cmd.extend(["--toolchain-vers", self.wwise_toolchain_vers])

        if self.wwise_toolchain_env_script:
            cmd.extend(["--toolchain-env-script", self.wwise_toolchain_env_script])
        
        cmd.extend([self.wwise_platform])
        
        utils.run_system_command(cmd, self.ERR_BUILD)
        os.chdir(original_dir)

        print("OK : Building step was completed successfully!")
            
    #==============================================================================
    # CLEANING
    #==============================================================================
    
    def cleanup(self) -> None:
        """
        Remove temporary directory after build.
        """
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
    
    def orchestrate(self, args: Optional[List[str]] = None) -> None:
        """
        Run the Faust2Wwise conversion process to integrate Faust dsp script into a Wwise plugin.
        Args:
            args (List[str], optional) : the arguments passed through the console. If not directly
            passed through the function, the arguments are obtained using the sys library.
        """
    
        self.setup_environment(args)    # preliminary step
        self.compile_dsp_file()         # step 1
        self.generate_wwise_project()   # step 2
        self.integration_step()         # step 3
        self.configure_wwise_project()  # step 4
        self.build_plugin()             # step 5
        self.cleanup()                  # outro
        
        self.cfg.print_summary()        # print summary info