import sys
import os
import platform
import subprocess

# help utility using Faust standard approach
def print_usage():
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

def print_wwise_help():
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
    print("")
    print("Example:")
    print("  faust2wwise myfaustfile.dsp --platform Authoring_Windows --toolset vc170 --configuration Release --arch x64")
    print("")

def create_wwise_config(cfg, parsed_args):
    """
    Populates cfg with Wwise-related configuration options from parsed_args.
    """
    def detect_arch():
        arch = platform.machine().lower()
        if arch in ["amd64", "x86_64"]:
            return "x64"
        elif arch in ["i386", "i686", "x86"]:
            return "x32"
        elif "arm" in arch:
            return "arm64"
        else:
            return "x64"
        
    # Common to both premake and build
    if parsed_args.platform:
        cfg.wwise_platform = parsed_args.platform
    cfg.wwise_plugin_interface = parsed_args.plugin_interface

    # Premake-specific options
    cursys = platform.system()
    if parsed_args.toolset:
        if cursys != "Windows":
            raise ValueError (f"{cursys} detected. Wwise does not support toolset options for this platform. This option is only for windows environments.")
        cfg.wwise_toolset = parsed_args.toolset
    elif cursys == "Windows":
        if cfg.wwise_platform == "Windows_vc160":
            cfg.wwise_toolset = "vc160"
        else: # in all other cases : Authoring_Windows, Authoring, Windows_vc170, WinGC
            cfg.wwise_toolset = "vc170"
        print(f"[WARNING] Using default toolset '{cfg.wwise_toolset}' — it would be better to override it with --toolset command line option.")

    cfg.wwise_debugger = parsed_args.debugger
    cfg.wwise_disable_codesign = parsed_args.disable_codesign

    # Build-specific options
    if parsed_args.configuration:
        cfg.wwise_configuration = parsed_args.configuration

    if parsed_args.arch:
        cfg.wwise_arch = parsed_args.arch
    else:
        cfg.wwise_arch = detect_arch()

    if parsed_args.build_hooks_file:
        cfg.wwise_build_hooks_file = parsed_args.build_hooks_file

    if parsed_args.toolchain_vers:
        cfg.wwise_toolchain_vers = parsed_args.toolchain_vers

    if parsed_args.toolchain_env_script:
        cfg.wwise_toolchain_env_script = parsed_args.toolchain_env_script

def parse_arguments(cfg, args=None):
    import argparse
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
    # TODO: extend here with wwise related configuration options?
    cfg.faust_options = cfg.faust_options.split() if isinstance(cfg.faust_options, str) else (cfg.faust_options or [])

    # Wwise-related options
    create_wwise_config(cfg, parsed_args)

def ensure_valid_plugin_name(name: str) -> str:
    """
    Check if plugin name is valid (i.e. if starts with a number, or if it has spaces)
    Faust compiles files that starts with a number, but wwise is not handling such project names
    Therefore, if invalid, prefix with 'Dsp_',
    replace spaces with underscore _,
    & always capitalize the first letter..
    """
    
    name = name.replace(" ", "_")

    if not name or not (name[0].isalpha() or name[0] == '_'):
        name = "Dsp_" + name
    
    return name.capitalize()

def check_wwise_required_arguments(cfg):
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


def wwise_platform_and_toolset_compatible(cfg):
    if (platform.system() == "Windows"):
        default_toolset = "vc170"

        # Strict compatibility
        if cfg.wwise_platform == "Windows_vc160":
            if cfg.wwise_toolset is None or cfg.wwise_toolset != "vc160":
                return False  # Incompatible

        elif cfg.wwise_platform == "Windows_vc170":
            if cfg.wwise_toolset is None:
                cfg.wwise_toolset = default_toolset
                print(f"[WARNING] No toolset provided. Defaulting to '{default_toolset}' for platform 'Windows_vc170'.")
            elif cfg.wwise_toolset != "vc170":
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

def validate_environment(cfg):
    
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

def run_system_command(cmd, error_code=None):

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
