import sys
import os
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
    sys.exit(1)

def parse_arguments(cfg, args=None):
    import argparse
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
        print_usage()
    
    if parsed_args.output_dir:
        cfg.output_dir = parsed_args.output_dir
    
    if parsed_args.dsp_file:
        cfg.dsp_file = parsed_args.dsp_file
        cfg.dsp_file = os.path.join(os.getcwd(), cfg.dsp_file )
    
    all_faust_options = (parsed_args.faust_options or []) + unknown_args
    cfg.faust_options = " ".join(all_faust_options)
    # TODO: extend here with wwise related configuration options?
    cfg.faust_options = cfg.faust_options.split() if isinstance(cfg.faust_options, str) else (cfg.faust_options or [])

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
