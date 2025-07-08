import os

class Config:
    def __init__(self, wwiseroot , faust_lib_dir, faust_include_dir):

        ################################################ paths
        self.faust_lib_dir = faust_lib_dir
        self.faust_include_dir = faust_include_dir
        self.archfile = os.path.join(self.faust_lib_dir, "wwise.cpp")
        
        ################################################ Wwise stuff
        self.wwiseroot = wwiseroot
        self.wp_script = os.path.join(self.wwiseroot, "Scripts", "Build", "Plugins", "wp.py")
        self.patch_version = ""
        self.wwise_template_dir = ""                # Directory where the template files are stored
        # configuration options
        self.wwise_platform = "Authoring"           # default
        self.wwise_plugin_interface = None          
        self.wwise_toolset = None
        self.wwise_debugger = False
        self.wwise_disable_codesign = False
        self.wwise_configuration = "Release"        # default
        self.wwise_arch = None
        self.wwise_build_hooks_file = None
        self.wwise_toolchain_vers = None
        self.wwise_toolchain_env_script = None

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

    def print(self):
        print("==========================================")
        print("FAUST2WWISE CONFIGURATION")
        print("==========================================")
        print(f"temp_dir {self.temp_dir}")
        print("========== FAUST CONFIGURATION ===========")
        print(f"dsp_file {self.dsp_file}")
        print(f"archfile {self.archfile}")
        print(f"faust_lib_dir: {self.faust_lib_dir}")
        print(f"faust_include_dir: {self.faust_include_dir}")
        print(f"output_dir {self.output_dir}")
        print(f"faust_options {self.faust_options}")
        print("=========== WWISE CONFIGURATION===========")
        print(f"wwiseroot {self.wwiseroot}")
        print(f"platform {self.wwise_platform}")
        if self.wwise_plugin_interface:
            print(f"plugin_interface {self.wwise_plugin_interface} (applicable only in case of an effect plugin)")
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
        print("========== PLUGIN CONFIGURATION ==========")
        print(f"plugin_type {self.plugin_type}")
        print(f"plugin_name {self.plugin_name}")
        print(f"author {self.author}")
        print(f"description {self.description}")
        print(f"dsp_filename {self.dsp_filename}")
        print("==========================================")
