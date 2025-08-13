"""
Python script that runs faust2wwise on all the dsp files that exist within the examples directory.
Author's note : run with administrative permissions.
"""
import subprocess
import json
from pathlib import Path
import platform
import os
import random

ROOT_DIR =  Path(__file__).resolve().parents[0]
FAUST_EXAMPLES_DIR = ROOT_DIR / "examples"
BASE_DIR = ROOT_DIR / "myTests"
OUTPUT_JSON_FILE = BASE_DIR / "test_results.json"

# these files are additional files that get imported by other dsp files, so they have to be excluded.
EXCLUDE_FILES = {
    "SAM/16_channel_volume/layout.dsp",         # ok, this file is imported by other dsp files
    "SAM/chorus/layout2.dsp",                   # ok, this file is imported by other dsp files
    "SAM/echo/layout2.dsp",                     # ok, this file is imported by other dsp files
    "SAM/effects/layout2.dsp",                  # ok, this file is imported by other dsp files
    "SAM/flanger/layout2.dsp",                  # ok, this file is imported by other dsp files
    "SAM/freeverb/layout2.dsp",                 # ok, this file is imported by other dsp files
    "SAM/virtualAnalog/layout2.dsp",            # ok, this file is imported by other dsp files
    "misc/sflooper.dsp",                        # ok, requires different arch file, builds with manual tweaking (#include faust/gui/SoundUI.h && faust/gui/LibsndfileReader.h in faustdsp.cpp + copying -I -L in compiler settings) 
    "SAM/echo/echo.dsp",                        # ok, builds when copying the faust\architecture\sam\headers into the SoundEnginePlugin directory
    "SAM/effects/echo.dsp",                     # ok, builds when copying the faust\architecture\sam\headers into the SoundEnginePlugin directory
    "SAM/effects/effects.dsp",                  # ok, builds when copying the faust\architecture\sam\headers into the SoundEnginePlugin directory
    "physicalModeling/faust-stk/bass.dsp",      # ok, builds when copying bass.h and instrument.h into the SoundEnginePlugin directory + change #include <bass.h> to "bass.h" in faustdsp.cpp
    "physicalModeling/faust-stk/harpsi.dsp",    # ok, builds when copying harpsichord.h and instrument.h into the SoundEnginePlugin directory + change #include <harpsichord.h> to "harpsichord.h" in faustdsp.cpp
    "physicalModeling/faust-stk/modalBar.dsp",  # ok, builds when copying modalBar.h and instrument.h into the SoundEnginePlugin directory + change #include from <> to "" in the include statements of the faustdsp.cpp for those two files
    "physicalModeling/faust-stk/piano.dsp",     # ok, builds when copying piano.h and instrument.h into the SoundEnginePlugin directory + change #include <piano.h> to "piano.h" in faustdsp.cpp
    "physicalModeling/faust-stk/voiceForm.dsp", # ok, builds when copying phonemes.h into the SoundEnginePlugin directory + change #include <phonemes.h> to "phonemes.h" in faustdsp.cpp
    "physicalModeling/mi-faust/08_TwoMassChain/2massChain.dsp", # ok, builds if remove the - symbol from the declare name statement, i.e. from "2-mass .." to "2_mass.."
    "autodiff/gain_dc/diff.dsp"                 # ok, builds if remove the + symbol from the declare name statement 
}

def moveJsonFile(json_source_path, json_target_path, log_path):

    if json_source_path.exists():
        try:
            os.rename(json_source_path, json_target_path)
        except Exception as e:
            with open(log_path, "a", encoding="utf-8") as log_file:
                log_file.write(f"\nWARNING: Could not move (rename) JSON file from {json_source_path} to {json_target_path}, continuing.\n")

def add_faust2wwise_arguments(command):

    # Define possible argument options
    argumentsList = [
        ["--out-of-place"],
        ["--platform","Windows_vc170","--toolset","vc170"],
        ["--disable-codesign"]
    ]
    
    selected_args = random.choice(argumentsList)
    command.extend(selected_args)
    return command

def run_faust2wwise_on_file(dsp_file, script="faust2wwise"):
    rel_path = dsp_file.relative_to(FAUST_EXAMPLES_DIR).with_suffix("")
    output_dir = BASE_DIR / rel_path
    output_dir.mkdir(parents=True, exist_ok=True)

    log_path = output_dir / "build.log"

    try:
        # Build command as a list, no shell quoting needed
        command = [
            str(script),
            "--output_dir", str(output_dir),
            str(dsp_file)
        ]

        command = add_faust2wwise_arguments(command)

        if (platform.system()=="Windows" and not
            ('MSYSTEM' in os.environ or 'MSYS' in os.environ)):
            command[0]+=".cmd"
        else:
            command.insert(0,"bash")

        result = subprocess.run(
            command,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            shell=True
        )

        with open(log_path, "w", encoding="utf-8") as log_file:
            log_file.write(f"COMMAND: {' '.join(command)}\n\n")
            log_file.write("=== STDOUT ===\n")
            log_file.write(result.stdout)
            log_file.write("\n\n=== STDERR ===\n")
            log_file.write(result.stderr)

        success = result.returncode == 0

    except Exception as e:
        with open(log_path, "w", encoding="utf-8") as log_file:
            log_file.write(f"COMMAND: {command}\n")
            log_file.write("\nERROR:\n")
            log_file.write(str(e))

        success = False

    # move the json file from the examples dir into the project dir
    json_source_path = dsp_file.with_name(dsp_file.name + ".json")
    json_target_path = output_dir / json_source_path.name
    moveJsonFile(json_source_path, json_target_path, log_path)

    return {
        "file": str(dsp_file),
        "output_dir": str(output_dir),
        "log_file": str(log_path),
        "success": success,
        "returncode": result.returncode
    }

def main():

    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("--limit", type=int, default=None)
    args = parser.parse_args()

    dsp_files = [
        f for f in FAUST_EXAMPLES_DIR.rglob("*.dsp")
        if str(f.relative_to(FAUST_EXAMPLES_DIR)).replace("\\", "/") not in EXCLUDE_FILES
    ]
    print(f"Found {len(dsp_files)} .dsp files.\n")

    totalFiles = len(dsp_files)
    import random
    if args.limit:
        dsp_files = random.sample(dsp_files, min(args.limit, len(dsp_files)))
        print(f"Picked {min(args.limit, len(dsp_files))} out of {totalFiles} .dsp files.\n")
        totalFiles = min(args.limit, len(dsp_files))

    BASE_DIR.mkdir(parents=True, exist_ok=True)
    results = []

    for i,dsp_file in enumerate(dsp_files):
        print(f"Processing: {dsp_file}")
        result = run_faust2wwise_on_file(dsp_file)
        print(f"{'Success' if result['success'] else 'Failed '} : ({i+1}/{totalFiles}) {dsp_file.name} ")
        results.append(result)

    with open(OUTPUT_JSON_FILE, "w", encoding="utf-8") as f:
        json.dump(results, f, indent=2)

    succeeded = [r for r in results if r.get("success")]
    failed = [r for r in results if not r.get("success")]

    print(f"\nResults saved to {OUTPUT_JSON_FILE}")
    print(f"Succeeded: {len(succeeded)}")
    print(f"Failed: {len(failed)}")

if __name__ == "__main__":
    main()
