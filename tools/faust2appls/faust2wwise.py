# #####################################################################
#                                                                   #
#                        faust2wwise generator                      #
#                          (c) Grame, 2025                          #
#                                                                   #
#####################################################################    

"""
faust2wwise.py

The cross-platform entry point for converting Faust DSP files into Wwise plugins.

This script:
- Detects installed Wwise and Faust directories
- Dynamically loads the orchestrator script
- Initializes and runs the Faust2WwiseOrchestrator

Requires:
- Wwise SDK installed and WWISEROOT environment variable set
- Faust compiler available in PATH
- Faust `wwise/orchestrator.py` present in the architecture tools
"""

import os
import sys
import subprocess
from pathlib import Path
import importlib.util
from typing import Optional
from types import ModuleType

def get_wwise_root_dir() -> Optional[Path]:
    """
    Returns the Wwise root directory if found via the WWISEROOT environment variable.
    Prints a warning and returns None if not found.
    """
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

def get_faust_dsp_dir() -> Optional[Path]:
    """
    Calls `faust --dspdir` to get the directory containing the Faust dsp libraries.
    Raises exception if the subprocess call fails.
    Returns:
        The directory containing the Faust dsp libraries if successful, otherwise None
    """    
    try:
        result = subprocess.run(
            ['faust', '--dspdir'],
            capture_output=True,
            text=True,
            check=True
        )
        path = result.stdout.strip()
        if os.path.isdir(path):
            return Path(path).resolve()
    except Exception as e:
        print(f"[Warning] faust --libdir failed: {e}")
    return None

def get_faust_include_dir() -> Path:
    """
    Returns the directory containing the Faust headers using `faust --includedir`.
    Does not raise exception if the subprocess call fails, since it is called after the get_faust_dsp_dir().
    Returns:
        The directory containing the Faust headers
    """
    result = subprocess.run(
        ['faust', '--includedir'],
        capture_output=True,
        text=True,
        check=True
    )
    return Path(result.stdout.strip()).resolve()


def import_orchestrator(faust_dsp_dir:str)-> Optional[ModuleType]:
    """
    Loads dynamically the orchestrator module from the Faust DSP architecture dir.

    Args:
        faust_dsp_dir (str): The directory where Faust DSP architectures are located.

    Returns:
        A loaded Python module if successful, otherwise None if the `orchestrator.py` is missing.
    """
        
    arch_tools_dir = os.path.join(faust_dsp_dir,"wwise")
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
    faust_dsp_dir = get_faust_dsp_dir()
    faust_include_dir = get_faust_include_dir()

    print("Wwise installation:", wwise_root_dir or "Not found")
    print(f"faust_dsp_dir {faust_dsp_dir}")
    print(f"faust_include_dir {faust_include_dir}")
    

    orchestrator_module = import_orchestrator(faust_dsp_dir)

    faust2wwiser = orchestrator_module.Faust2WwiseOrchestrator( \
        wwiseroot = wwise_root_dir,
        faust_dsp_dir = faust_dsp_dir,
        faust_include_dir = faust_include_dir)
    
    faust2wwiser.orchestrate()