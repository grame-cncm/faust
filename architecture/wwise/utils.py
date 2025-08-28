"""
utils.py

Utility functions for the faust2wwise tool, including:

- Command-line argument parsing and validation
- Help messages for general and Wwise-specific options
- Wwise configuration setup and verification
- Environment validation
- System command execution

This module is intended to assist with the orchestration of plugin generation from Faust DSP files to Wwise-compatible plugins.
"""

import sys
import os
import platform
import subprocess
import argparse
from typing import List, Optional
from spkcfg import speaker_config_options

def print_usage() -> None:
    """
    Prints general usage information for the faust2wwise command-line tool.
    """
    print("Usage:")
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

def print_wwise_help() -> None:
    """
    Prints Wwise-specific command-line options and examples.
    Includes options for both premake and build steps.
    """
    print("")
    print("Wwise Plugin Options:")
    print("")
    print("Common options for both Premake and Build:")
    print("  --platform <platform>           platform to premake (Authoring_Windows, Authoring, Windows_vc160, Windows_vc170, WinGC)")
    print("  --in-place                      Use in-place processing (default). Uses the same audio buffer for input and output; suitable for most effects without data flow changes")
    print("  --out-of-place                  Use out-of-place processing. Requires separate input and output buffers; needed for effects like time-stretching that alter data flow")
    print("  --wwise-help                    show this help message and exit")
    print("")
    print("Premake:")
    print("  --toolset <toolset>             toolset used to build on Windows platforms (vc160, vc170).")
    print("  --debugger                      Enable lua debugger for premake scripts")
    print("  --disable-codesign              Disable codesign post-build steps")
    print("")
    print("Build:")
    print("  --configuration <config>        configuration to build (Debug, Release, Profile,...).")
    print("  --arch <arch>                   architecture to build (x32, x64, ...).")
    print("  --build-hooks-file <path>       path to a Python file defining one or more of the supported hooks (postbuild) to be called at various step during the build process")
    print("  --toolchain-vers <path>         Path to a \'ToolchainVers\' text file, containing a list of supported toolchain versions to pass to the platform\'s toolchain_setup script, to setup and define a set of env-vars to re-run each build step with.")
    print("  --toolchain-env-script <path>   Path to a \'GetToolchainEnv\' script, which, when executed with a version provided by the toolchain-vers file, returns a comma separated list of environment variables to apply for build step.")
    print("  --spkcfg <in_uChannelMask>      Specify an explicit speaker configuration using one of the standard channel mask macros defined in AkSpeakerConfig.h")
    print("")
    print("Example:")
    print("  faust2wwise myfaustfile.dsp -double -o myWwisePlugin --platform Authoring_Windows --toolset vc170 --configuration Release --arch x64")
    print("")

def detect_arch(cfg) -> str:
    """
    Automatically detects the system architecture and sets sensible defaults
    for platform/toolset compatibility.
    Returns:
        arch (str if platform found): detected architecture.
        Exits with an error if the architecture is not recognized/supported.
    """
    arch = platform.machine().lower()
    if arch == "amd64":
        return "x64"
    elif arch == "x86_64":
        return "x86_64"
    elif arch in ["i386", "i686", "x86"]:
        return "x32"
    elif arch in ("arm64", "aarch64"):
        return "arm64"
    elif arch.startswith("arm"):
        return "arm32"
    else:
        sys.stderr.write(
            f"[Error] Unknown or unsupported architecture: '{arch}'.\n"
            "Please verify if Wwise supports this platform and if yes, update the detect_arch() function to handle this platform .\n"
        )
        sys.exit(cfg.ERR_ENVIRONMENT)

def platform_dependent_setup(cfg, parsed_args:argparse.Namespace) -> None:
    """
    Applies platform-specific configuration to the given config object.
    Sets the default Wwise platform and toolset based on the current operating system 
    and the parsed command-line arguments.

    - On Windows:
        - Uses the specified toolset if provided.
        - Otherwise, selects a default based on the Wwise platform.
        - Sets the default Wwise platform to "Authoring".
    - On macOS:
        - Disables toolset usage.
        - Sets the default Wwise platform to "Mac".
        
    Args:
        cfg (Config): The configuration object to modify.
        parsed_args (argparse.Namespace): Parsed arguments from argparse.

    Raises:
        ValueError: If a toolset is provided on a non-Windows platform.
    """

    # Premake-specific options - toolset
    cursys = platform.system()
    if parsed_args.toolset:
        if cursys != "Windows":
            raise ValueError (f"{cursys} detected. Wwise does not support toolset options for this platform. This option is only for windows environments.")
        cfg.wwise_toolset = parsed_args.toolset
    elif cursys == "Windows":
        if parsed_args.platform == "Windows_vc160":
            cfg.wwise_toolset = "vc160"
        else: # in all other cases : Authoring_Windows, Authoring, Windows_vc170, WinGC
            cfg.wwise_toolset = "vc170"
        print(f"[WARNING] Using default toolset '{cfg.wwise_toolset}' — it would be better to override it with --toolset command line option.")
    
    # set default platform
    if cursys == "Darwin":
        cfg.wwise_platform = "Mac"  # default platform for MacOs
    elif cursys == "Windows":
        cfg.wwise_platform = "Authoring" # default platform for Windows

def create_wwise_config(cfg, parsed_args:argparse.Namespace) -> None:
    """
    Populates Wwise-related configuration values into the given config object,
    using the parsed command-line arguments.

    Args:
        cfg (Config): The configuration object to modify.
        parsed_args (argparse.Namespace): Parsed arguments from argparse.
    """
    
    # Overwrite any platform specific defaults in case explicit platform is passed as an argument
    if parsed_args.platform:
        cfg.wwise_platform = parsed_args.platform

    cfg.wwise_plugin_interface = parsed_args.plugin_interface   # default value in-place. In case of being a source plugin, it will be reset to None, but it is not known at initialization time, only after compiling the dsp file with the Faust compiler.

    cfg.wwise_debugger = parsed_args.debugger
    cfg.wwise_disable_codesign = parsed_args.disable_codesign

    # Build-specific options
    if parsed_args.configuration:
        cfg.wwise_configuration = parsed_args.configuration

    if parsed_args.arch:
        cfg.wwise_arch = parsed_args.arch
    else:
        cfg.wwise_arch = detect_arch(cfg)

    if parsed_args.build_hooks_file:
        cfg.wwise_build_hooks_file = parsed_args.build_hooks_file

    if parsed_args.toolchain_vers:
        cfg.wwise_toolchain_vers = parsed_args.toolchain_vers

    if parsed_args.toolchain_env_script:
        cfg.wwise_toolchain_env_script = parsed_args.toolchain_env_script
    
    if parsed_args.spkcfg:
        cfg.wwise_speaker_cfg_channel_mask = parsed_args.spkcfg

def parse_arguments(cfg, args:Optional[argparse.Namespace] = None) -> argparse.Namespace:
    """
    Parses command-line arguments and updates the configuration object.

    This includes:
        - DSP file path
        - Output directory
        - Faust options
        - Wwise-related arguments (platform, toolset, configuration, etc.)

    Args:
        cfg (Config): The configuration object to populate.
        args (List[str], optional): Command-line argument list (used for testing). Defaults to sys.argv[1:].
    """
    parser = argparse.ArgumentParser(description="Converts Faust DSP files to Wwise plugins",
                                    add_help=False)
    parser.add_argument('-h', '--help', action='store_true', help='Show help message')
    parser.add_argument('-o', '--output_dir', help='Output directory')
    parser.add_argument('dsp_file', nargs='?', help='DSP file to convert')
    parser.add_argument('faust_options', nargs='*', help='Additional Faust options')
    
    # Wwise options
    parser.add_argument('--platform', help='Target platform for Wwise plugin (Authoring_Windows, Authoring, Windows_vc160, Windows_vc170, WinGC)')
    # mutually exclussive in-place and out-of-place effect plugin options. in-place is the default choice.
    plugin_interface_group = parser.add_mutually_exclusive_group()
    plugin_interface_group.add_argument('--in-place', dest='plugin_interface', action='store_const', const='in-place', help='Uses the same audio buffer for input and output; suitable for most effects without data flow changes.')
    plugin_interface_group.add_argument('--out-of-place', dest='plugin_interface', action='store_const', const='out-of-place', help='Use out-of-place processing. Requires separate input and output buffers; needed for effects like time-stretching that alter data flow.')
    parser.set_defaults(plugin_interface='in-place')
    # wwise premake options
    parser.add_argument('--toolset', help='toolset used to build on Windows platforms (vc160, vc170).')
    parser.add_argument('--debugger', action='store_true', help='Enable lua debugger for premake scripts')
    parser.add_argument('--disable-codesign', action='store_true', help='Disable codesign post-build steps')
    # wwise build options
    parser.add_argument('--configuration', help='configuration to build (Debug, Release, Profile,...).')
    parser.add_argument('--arch', help='architecture to build (x32, x64, ...).')
    parser.add_argument('--build-hooks-file', help='path to a Python file defining one or more of the supported hooks (postbuild) to be called at various step during the build process')
    parser.add_argument('--toolchain-vers', help='Path to a \'ToolchainVers\' text file, containing a list of supported toolchain versions to pass to the platform\'s toolchain_setup script, to setup and define a set of env-vars to re-run each build step with.')
    parser.add_argument('--toolchain-env-script', help='Path to a \'GetToolchainEnv\' script, which, when executed with a version provided by the toolchain-vers file, returns a comma separated list of environment variables to apply for build step.')
    parser.add_argument('--spkcfg', type=str, choices=list(speaker_config_options.keys()), help='Explicit speaker configuration defined by a standard channel mask (e.g. AK_SPEAKER_SETUP_5POINT1), as specified in AkSpeakerConfig.h from the official Wwise SDK.')

    if args is None:
        args = sys.argv[1:]
    
    parsed_args, unknown_args = parser.parse_known_args(args)
    
    if parsed_args.help:
        print_usage()
        print_wwise_help()
        sys.exit(1)

    if parsed_args.output_dir:
        cfg.output_dir = parsed_args.output_dir
    
    if parsed_args.dsp_file:
        cfg.dsp_file = parsed_args.dsp_file
        cfg.dsp_file = os.path.join(os.getcwd(), cfg.dsp_file )
    
    all_faust_options = (parsed_args.faust_options or []) + unknown_args
    cfg.faust_options = " ".join(all_faust_options)
    cfg.faust_options = cfg.faust_options.split() if isinstance(cfg.faust_options, str) else (cfg.faust_options or [])

    return parsed_args

def ensure_valid_plugin_name(name: str) -> str:
    """
    Converts the plugin name to a valid format accepted by Wwise.

    Adjustments include:
        - Prefixing with "Dsp_" if name starts with a number or is invalid
        - Replacing spaces with underscores
        - Capitalizing the first character

    Args:
        name (str): The raw plugin name to validate

    Returns:
        str: A sanitized, Wwise-compatible plugin name

    Note:
        Faust compiles files that starts with a number, but wwise is not handling such project names
    """
    
    name = name.replace(" ", "_")

    if not name or not (name[0].isalpha() or name[0] == '_'):
        name = "Dsp_" + name
    
    return name.capitalize()

def check_wwise_required_arguments(cfg) -> List[str]:
    """
    Checks whether all required Wwise configuration parameters are set.

    Args:
        cfg (Config): The configuration object to validate.

    Returns:
        List[str]: A list of missing required arguments, if any.
    """
    missing = []
    if not cfg.wwise_platform:
        missing.append("platform (--platform)")
    if not cfg.wwise_configuration:
        missing.append("configuration (--configuration)")
    if not cfg.wwise_arch:
        missing.append("arch (--arch)")

    windows_platforms = {"Authoring_Windows", "Windows_vc160", "Windows_vc170", "WinGC"}
    if cfg.wwise_platform in windows_platforms and not cfg.wwise_toolset:
        missing.append("toolset (--toolset) [required for Windows platforms]")

    return missing


def wwise_platform_and_toolset_compatible(cfg) -> bool:

    """
    Ensures that platform and toolset are compatible (on Windows only):
    - If no toolset is provided, a default is assigned based on the platform.
    - If an invalid combination is detected, the function returns False.
    - On non-Windows platforms, the toolset (if specified) is ignored with a warning.

    Args:
        cfg (Config): The configuration object.

    Returns:
        bool: True if compatible, False if an invalid combination is detected.
    """
        
    if (platform.system() == "Windows"):
        default_toolset = "vc170"

        # Strict compatibility
        if cfg.wwise_platform == 'Windows_vc160':
            if cfg.wwise_toolset is None or cfg.wwise_toolset != 'vc160':
                return False  # Incompatible

        elif cfg.wwise_platform == 'Windows_vc170':
            if cfg.wwise_toolset is None:
                cfg.wwise_toolset = default_toolset
                print(f"[WARNING] No toolset provided. Defaulting to '{default_toolset}' for platform 'Windows_vc170'.")
            elif cfg.wwise_toolset != 'vc170':
                return False  # Incompatible

        else:  # Authoring, Authoring_Windows, WinGC
            if cfg.wwise_toolset is None:
                cfg.wwise_toolset = default_toolset
                print(f"[WARNING] No toolset provided. Defaulting to '{default_toolset}' for platform '{cfg.wwise_platform}'.")

        return True  # Compatible
    else: # if not on windows platform
        if cfg.wwise_toolset is not None: # if toolset defined
            print(f"[WARNING] Toolset was defined explicitly, but it is only supported on Windows platforms. Ignoring it.")
            cfg.wwise_toolset=None
        return True # Ignoring 

def validate_environment(cfg) -> None:
    """
    Validates the environment setup before building the plugin.
    Various checks are applied. These include:
        - if WWISEROOT is set
        - if DSP file is provided
        - if given DSP file exists
        - if architecture file exists
        - if required Wwise configuration parameters are set properly
        - if platform and toolset(if given) are compatible

    If invalid, exits the program with a specific error code.
    """
        
    # Check if WWISEROOT is set
    if not cfg.wwiseroot:
        print(f"Error {cfg.ERR_ENVIRONMENT}: WWISEROOT environment variable is not set.")
        print("Please set it to your Wwise installation directory or make sure wwise is installed.")
        sys.exit(cfg.ERR_ENVIRONMENT)
    
    # Check if dsp file provided
    if not cfg.dsp_file:
        print(f"Error {cfg.ERR_INVALID_INPUT}: No DSP file provided")
        print_usage()
        sys.exit(cfg.ERR_INVALID_INPUT)
    
    # Check if the given dsp file exists
    if not os.path.isfile(cfg.dsp_file):
        print(f"Error {cfg.ERR_INVALID_INPUT}: DSP file '{cfg.dsp_file}' not found")
        sys.exit(cfg.ERR_INVALID_INPUT)

    # Check if architecture file exists
    if not os.path.isfile(cfg.archfile):
        print(f"Error {cfg.ERR_ENVIRONMENT}: Wwise architecture file not found at {cfg.archfile}")
        print(f"Make sure the wwise.cpp architecture file is installed in {cfg.faust_lib_dir}")
        sys.exit(cfg.ERR_ENVIRONMENT)

    # Check if required wwise arguments are set properly
    missing = check_wwise_required_arguments(cfg)
    if missing:
        print(f"Error {cfg.ERR_INVALID_INPUT}: Missing required Wwise arguments:")
        for arg in missing:
            print(f"  - {arg}")
        sys.exit(cfg.ERR_INVALID_INPUT)

    # Check compatibility between platform and toolset wwise arguments
    if not wwise_platform_and_toolset_compatible(cfg) :
        print(f"Error {cfg.ERR_INVALID_INPUT}: {cfg.wwise_platform} and {cfg.wwise_toolset} are incompatible command line options")
        print(f"Make sure you explicitly define compatible options. For instance: 'Windows_vc160' platform with 'vc160' toolset.")
        sys.exit(cfg.ERR_INVALID_INPUT)

def run_system_command(cmd : List[str], error_code:Optional[int]=None) -> subprocess.CompletedProcess :

    """
    Executes a system based command with consistent output and error handling.

    Args:
        cmd (List[str]): Command to run.
        error_code (int, optional): Custom error code for failure.

    Returns:
        subprocess.CompletedProcess: The result of the command execution, if successful, otherwise exits program before return.

    Raises:
        SystemExit: On command failure, exits with the provided error code.
    """
    
    print("Running command:", " ".join(cmd))

    try:
        result = subprocess.run(
            cmd,
            check=True,
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
