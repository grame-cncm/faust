"""
config.py

The Config class. Responsible for storing and managing paths, parameters,
and plugin metadata for integrating Faust DSP files into the Wwise plugin generation pipeline.

Note: 
Some fields are set during initialization, while others are computed or updated during later 
processing steps.
"""

import os
from typing import Final, Any, get_type_hints

class Config:
    """
    Configuration class for Faust-to-Wwise plugin integration.

    This class holds all configuration data used throughout the plugin generation process, including:
        - Paths to Faust and Wwise resources
        - Parameters passed through the console
        - Plugin configuration (name, author, type, ..)
        - Error codes for proper diagnostics

    The configuration follows a two-stage setup:
        1. Initial setup — most variables are initialized.
        2. Plugin generation — plugin metadata is finalized after compiling the DSP file using the Faust compiler.

    The config can be locked to prevent mutation after setup is complete.
    """
    faust_dsp_dir: Final[str] 
    faust_include_dir: Final[str]
    archfile: Final[str]
    wwiseroot: Final[str]
    wp_script: Final[str]
    ERR_INVALID_INPUT: Final[int]
    ERR_ENVIRONMENT: Final[int]
    ERR_FAUST_COMPILE: Final[int]
    ERR_JSON_PARSE: Final[int]
    ERR_GENERATION: Final[int]
    ERR_INTEGRATION: Final[int]
    ERR_CONFIGURATION: Final[int]
    ERR_BUILD: Final[int]

    def __init__(self, wwiseroot , faust_dsp_dir, faust_include_dir) -> None :
        """
        Initialize the Config instance.

        Args:
            wwiseroot (Path): Path to the root directory of the Wwise installation.
            faust_dsp_dir (Path): Path to the Faust architecture library directory.
            faust_include_dir (Path): Path to the Faust include files directory.

        Notes:
            This method sets up the initial paths and configuration variables.
            Additional plugin parameters are configured after compiling the DSP file
            using the Faust compiler.
        """
        ################################################  paths
        # Faust paths
        self.faust_dsp_dir = faust_dsp_dir          # Directory containing the Faust dsp libraries
        self.faust_include_dir = faust_include_dir
        self.archfile = os.path.join(self.faust_dsp_dir, 'wwise.cpp')
        # Wwise paths
        self.wwiseroot = wwiseroot                  # Root dir of the Wwise installation
        self.wp_script = os.path.join(self.wwiseroot, 'Scripts', 'Build', 'Plugins', 'wp.py')
        self.patch_version = None                   # Derived from wwise version and used for defining the wwise_template_dir
        self.wwise_template_dir = None              # Directory where the template files are stored
        
        # temp path
        self.temp_dir = "_temp_"                    # Temp dir to store temp data ( i.e. jsonfile )

        ############################################### Parameters
        # Faust parameters
        self.dsp_file = None
        self.dsp_filename = None
        self.output_dir = None
        self.json_file = None
        self.faust_options = None
        # Wwise parameters
        self.wwise_platform = None
        self.wwise_plugin_interface = None          
        self.wwise_toolset = None
        self.wwise_debugger = False
        self.wwise_disable_codesign = False
        self.wwise_configuration = "Release"        # default
        self.wwise_arch = None
        self.wwise_build_hooks_file = None
        self.wwise_toolchain_vers = None
        self.wwise_toolchain_env_script = None
        self.wwise_speaker_cfg_channel_mask = None 

        ################################################ plugin configuration
        self.plugin_type = None
        self.plugin_name = None
        self.plugin_suffix = None
        self.author = None
        self.description = None
        self.num_inputs = None
        self.num_outputs = None
        
        ################################################ error codes
        self.SUCCESS_EXIT_CODE = 0
        self.ERR_ENV_VARS_NOT_FOUND = 1     # used outside the scope of this python module, but defined here as well for clarity
        self.ERR_INVALID_INPUT = 2
        self.ERR_ENVIRONMENT = 3
        self.ERR_FAUST_COMPILE = 4
        self.ERR_JSON_PARSE = 5
        self.ERR_GENERATION = 6
        self.ERR_INTEGRATION = 7
        self.ERR_CONFIGURATION = 8
        self.ERR_BUILD = 9

        ################################################ config internal 
        self._locked = False
        self._final_attrs = self._get_final_attrs()
        self._final_values = {}

    def print(self) -> None :
        """Prints the full Faust-to-Wwise configuration, including paths, parameters, and error codes."""
        print("==========================================")
        print("FAUST2WWISE CONFIGURATION")
        
        print("================= Paths ==================")
        print("Faust paths:")
        print(f"faust_dsp_dir: {self.faust_dsp_dir}")
        print(f"faust_include_dir: {self.faust_include_dir}")
        print(f"archfile {self.archfile}")
        print("Wwise paths:")
        print(f"wwiseroot {self.wwiseroot}")
        print(f"wp_script {self.wp_script}")
        print(f"wwise_template_dir -> unresolved yet and will be defined after compiling the dsp file with Faust")
        print(f"patch_version {self.patch_version}")
        print("Other:")
        print(f"temp_dir {self.temp_dir}")

        print("============== Parameters ================")
        print("Faust params:")
        print(f"dsp_file {self.dsp_file}")
        print(f"dsp_filename {self.dsp_filename}")
        print(f"json_file {self.json_file}")
        print(f"output_dir {self.output_dir}")
        print(f"faust_options {self.faust_options}")
        print("Wwise params:")
        print(f"platform {self.wwise_platform}")
        if self.wwise_toolset:
            print(f"toolset {self.wwise_toolset}")
        if self.wwise_debugger:
            print(f"debugger {self.wwise_debugger}")
        if self.wwise_disable_codesign:
            print(f"disable_codesign{self.wwise_disable_codesign}")
        print(f"configuration {self.wwise_configuration}")
        if self.wwise_arch:
            print(f"arch {self.wwise_arch}")
        if self.wwise_build_hooks_file:
            print(f"build_hooks_file {self.wwise_build_hooks_file}")
        if self.wwise_toolchain_vers:
            print(f"toolchain_vers {self.wwise_toolchain_vers}")
        if self.wwise_toolchain_env_script:
            print(f"toolchain_env_script {self.wwise_toolchain_env_script}")
        if self.wwise_speaker_cfg_channel_mask:
            print(f"wwise_speaker_cfg_channel_mask {self.wwise_speaker_cfg_channel_mask}")
        print(f"plugin_interface --> unresolved yet and will be defined after compiling the dsp file with Faust")

        print("============= Error Codes ================")
        print(f"ERR_INVALID_INPUT {self.ERR_INVALID_INPUT}")
        print(f"ERR_ENVIRONMENT {self.ERR_ENVIRONMENT}")
        print(f"ERR_FAUST_COMPILE {self.ERR_FAUST_COMPILE}")
        print(f"ERR_JSON_PARSE {self.ERR_JSON_PARSE}")
        print(f"ERR_GENERATION {self.ERR_GENERATION}")
        print(f"ERR_INTEGRATION {self.ERR_INTEGRATION}")
        print(f"ERR_CONFIGURATION {self.ERR_CONFIGURATION}")
        print(f"ERR_BUILD {self.ERR_BUILD}")

        print("========== Plugin Configuration ==========")
        print("unresolved yet and will be defined after compiling the dsp file with Faust")
        print("==========================================")
    
    def plugin_print(self) -> None :
        """Prints the resolved plugin metadata (name, author, type, etc.)."""
        print("========== PLUGIN CONFIGURATION ==========")
        print(f"plugin_type {self.plugin_type}")
        print(f"plugin_name {self.plugin_name}")
        print(f"plugin_suffix {self.plugin_suffix}")
        print(f"num_inputs {self.num_inputs}")
        print(f"num_outputs {self.num_outputs}")
        print(f"author {self.author}")
        print(f"description {self.description}")
        if self.wwise_plugin_interface:
            print(f"plugin_interface {self.wwise_plugin_interface}")
        print(f"wwise_template_dir {self.wwise_template_dir}")    
        print("==========================================")
    
    def print_summary(self) -> None:
        """Prints the summary info after successful Faust to Wwise integration."""
        print("")
        print("=====================================")
        print("Faust2Wwise conversion completed!")
        print(f"Generated plugin: {self.plugin_name}")
        print(f"Plugin type: {self.plugin_type}" + (" (in-place)" if self.plugin_type == "effect" and self.wwise_plugin_interface=="in-place" else " (out-of-place)" if self.plugin_type == "effect" else ""))
        print(f"IO: num inputs({self.num_inputs}), num outputs({self.num_outputs})")
        print(f"Location: {os.path.join(self.output_dir, self.plugin_name)}")
        print(f"Installation: {os.path.join(self.wwiseroot, 'Authoring', self.wwise_arch, self.wwise_configuration, 'bin', 'Plugins', self.plugin_name)}.(ext)")
        print("=====================================")
        print("")

    def _get_final_attrs(self) -> set[str]:
        """Return names of attributes marked as Final."""
        hints = get_type_hints(self.__class__, include_extras=True)
        return {name for name, typ in hints.items() if getattr(typ, '__origin__', None) is Final}

    def __setattr__(self, name : str, value: Any) -> None:
        if name in getattr(self, '_final_attrs', set()):
            if name in self.__dict__:
                raise AttributeError(f"Cannot reassign final attribute '{name}'")
            self._final_values[name] = value

        if getattr(self, '_locked', False) and not name.startswith('_'):
            raise AttributeError(f"Cannot modify '{name}': Config is locked.")

        super().__setattr__(name, value)

    def lock(self) -> None:
        """Locks the config to prevent further changes."""
        self._locked = True

