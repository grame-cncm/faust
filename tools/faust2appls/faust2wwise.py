# #####################################################################
#                                                                   #
#                        faust2wwise generator                      #
#                          (c) Grame, 2025                          #
#                                                                   #
#####################################################################    

import os
import sys
import subprocess
from pathlib import Path
import importlib.util

def get_wwise_root_dir():
   
    wwise_root = os.environ.get("WWISEROOT")
    if wwise_root and Path(wwise_root).is_dir():
        return Path(wwise_root).resolve()

    print(
        "Warning: Wwise root directory not found.\n"
        "Make sure Wwise is installed and environment variables are set:\n"
        "  AudioKinetic Launcher -> Install options (tool icon) -> Set environment variables\n"
        "Then restart your terminal or IDE.\n"
        "Expected environment variables:\n"
        "  WWISEROOT (i.e. C:\\Program Files (x86)\\Audiokinetic\\Wwise<version>)"
    )
    return None

def get_faust_lib_dir():

    # `faust --libdir` is called to get the standard Faust library path.
    
    try:
        result = subprocess.run(
            ['faust', '--dspdir'],
            capture_output=True,
            text=True,
            check=True
        )
        path = result.stdout.strip()
        if os.path.isdir(path):
            return path
    except Exception as e:
        print(f"[Warning] faust --libdir failed: {e}")
    return None

def get_faust_include_dir():

    result = subprocess.run(
        ['faust', '--includedir'],
        capture_output=True,
        text=True,
        check=True
    )
    return result.stdout.strip()


def import_orchestrator(faust_lib_dir):

    arch_tools_dir = os.path.join(faust_lib_dir,"wwise")
    orchestrator_path = Path(os.path.join(arch_tools_dir,"orchestrator.py"))
    if not orchestrator_path.is_file():
        print(f"Warning: orchestrator.py not found at: {orchestrator_path}")
        return None

    sys.path.insert(0,arch_tools_dir) # insert the directory into the sys.path
    # import path as a python module
    spec = importlib.util.spec_from_file_location("orchestrator", orchestrator_path)
    orchestrator = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(orchestrator)
    return orchestrator

if __name__ == "__main__":

    wwise_root_dir = get_wwise_root_dir()
    faust_lib_dir = get_faust_lib_dir()
    faust_include_dir = get_faust_include_dir()

    print("Wwise installation:", wwise_root_dir or "Not found")
    print(f"faust_lib_dir {faust_lib_dir}")
    print(f"faust_include_dir {faust_include_dir}")
    

    orchestrator_module = import_orchestrator(faust_lib_dir)

    faust2wwiser = orchestrator_module.Faust2WwiseOrchestrator( \
        wwiseroot = wwise_root_dir,
        faust_lib_dir = faust_lib_dir,
        faust_include_dir = faust_include_dir)
    
    faust2wwiser.orchestrate()