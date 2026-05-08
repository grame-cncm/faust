
from html import parser
import os
import sys
from pathlib import Path
import config
import utils
import argparse
from typing import List, Optional

DEFAULT_TOOLSET = "vc170"

class PluginInstaller:

    def __init__(self, wwiseroot:Path , faust_dsp_dir:Path, faust_include_dir:Path):        
        
        self.cfg = config.Config(wwiseroot , faust_dsp_dir, faust_include_dir)

    def setup_environment(self) -> None:
        """
        Sets up environment, for installing the Faust interpreter as a Wwise plugin,including the following steps:
        - parse arguments, 
        - initialize uninitialized configuration variables, 

        Args:
            args(List[str]): Optional list of arguments. If not provided, parse_arguments function makes 
            use of sys library to retrieve them.
        """

        if self.cfg.patch_version not in self.cfg.supportedWwiseVersions:
            sys.stderr.write(f"Unsupported Wwise version : {self.patch_version}. \
                Available Wwise (major) versions: {self.supportedWwiseVersions}")
            sys.exit(self.ERR_ENVIRONMENT)

        self._parse_arguments()
        
        # setup before installation
        self.cfg.plugin_name = "Faust_Interpreter_Wwise_Plugin"
        self.cfg.wwise_platform = "Authoring"
        self.cfg.build_location = os.path.join(self.cfg.faust_dsp_dir, "wwise", self.cfg.plugin_name)
        self.cfg.plugin_type = "source"
        self.cfg.cfg_json_path = None
        self.cfg.install_location = utils.get_installation_location(self.cfg)

    # =========================================================================
    # SETUP ENVIRONMENT 
    # =========================================================================
    def _print_usage(self) -> None:
        """
        Prints usage information for the `faust2wwise interpreter-install` subcommand.
        """
        print("Install the Faust interpreter as a Wwise plugin.")
        print("Usage:")
        print("faust2wwise interpreter-install [options]")
        print("")
        print("Platform: Windows with Wwise SDK")
        print("")
        print("Requirements: Wwise SDK, Faust compiler, Python")
        print("")
        print("Options:")
        print("  -h, --help                      Show this help message")
        print("  --toolset <toolset>             toolset used to build on Windows platforms (vc160, vc170).")
        print("  --configuration <config>        configuration to build (Debug, Release, Profile,...).")
        print("  --arch <arch>                   architecture to build (x32, x64, ...).")
        sys.exit(self.cfg.SUCCESS_EXIT_CODE)

    def _parse_arguments(self) -> argparse.Namespace:
        """
        Parses command-line arguments dedicated to the Faust Interpreter Wwise plugin installlation,
        making use of the configuration object that is used in the faust2wwise cli tool.

        The only args that are used are the : 
            - Wwise-related arguments (arch, toolset, configuration, etc.)

        Args:
            cfg (Config): The configuration object to populate.
            args (List[str], optional): Command-line argument list (used for testing). Defaults to sys.argv[1:].

        Returns:
            parsed_args : the parsed arguments.
        """

        sys.argv.remove('interpreter-install')

        parser = argparse.ArgumentParser(description="Converts Faust DSP files to Wwise plugins", 
                                         add_help=False)
        parser.add_argument('-h', '--help', action='store_true', help='Show help message')
        parser.add_argument('--toolset', help='toolset used to build on Windows platforms (vc160, vc170).')
        # parser.add_argument('--configuration', help='configuration to build (Debug, Release, Profile,...).') # TODO
        parser.add_argument('--arch', help='architecture to build (x32, x64, ...).')

        args = sys.argv[1:]
        parsed_args = parser.parse_args(args)

        if parsed_args.help:
            self._print_usage()

        #TODO : add configuration argument parsing and handling
        # if parsed_args.configuration:
        #     self.cfg.wwise_configuration = parsed_args.configuration
        self.cfg.wwise_arch = parsed_args.arch or utils.detect_arch(self.cfg)
        self.cfg.wwise_toolset = parsed_args.toolset or DEFAULT_TOOLSET

    # =========================================================================
    # INSTALL FAUST INTERPRETER AS A WWISE PLUGIN
    # =========================================================================

    def install_interpreter(self) -> None:
        
        """Installs the Faust interpreter as a Wwise plugin."""

        print("------------------------------------------Installing the Faust interpreter as a Wwise plugin...")
        
        self.setup_environment()

        # Entering project directory
        os.chdir(self.cfg.build_location)

        # Running premake
        utils.run_system_command(
            ["python", 
            self.cfg.wp_script, 
            "premake", self.cfg.wwise_platform], 
            error_code=self.cfg.ERR_CONFIGURATION)
        
        # Building and installing the Faust interpreter
        utils.run_system_command(
            ["python", 
            self.cfg.wp_script, 
            "build", self.cfg.wwise_platform, 
            "-x", self.cfg.wwise_arch, 
            "-t", self.cfg.wwise_toolset, 
            "-c", self.cfg.wwise_configuration],
            error_code=self.cfg.ERR_BUILD)

        print("OK : Faust interpreter plugin installed successfully!") 

        self.cfg.print_summary()