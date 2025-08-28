"""
Python script that runs faust2wwise on all the dsp files that exist within a given directory.
Author's note : run with administrative permissions.
"""

import os
import sys
from pathlib import Path
import argparse
import json
import subprocess
import platform
import random

class TestFaustExamples:
    """
    TestFaustExamples automates the process of compiling multiple Faust .dsp files into Wwise plugins 
    using the `faust2wwise` script. It supports selective compilation, logging, and (future) cleanup.

    Attributes:
        outdirName (str): Name of the output directory for compiled results.
        jsonfileName (str): Default name of the test results JSON file.
        EXCLUDED_FILES (set): Set of relative paths to be excluded from testing.
    """

    outdirName = "myF2Wtests"
    jsonfileName = "testResults.json"

    # these files are additional files that get imported by other dsp files, so they have to be excluded.
    EXCLUDED_FILES = {
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

    def __init__(self, wwiseroot:Path) -> None:
        """
        Initializes the tester.
        Args:
            wwiseroot (Path): Path to the root directory of the Wwise SDK installation.
        """
        self.wwiseroot = wwiseroot

        self.outdir = os.path.join(os.getcwd(), self.outdirName)
        self.clean = False
        self.testdir = None
        self.limit = None
        self.jsonfile = None

        self.platform_dependent_setup()


    def parse_arguments(self)-> None:
        """
        Parses command-line arguments for test mode initializing self.clean, 
        self.testdir, self.limit, and self.jsonfile accordingly.
        """
        sys.argv.remove('test')

        parser = argparse.ArgumentParser()
        parser.add_argument("-c","--clean", required=False, nargs="?", const="__DEFAULT__", default=None, type=str, help="clean installed wwise plugins using the json file existing in the output dir where the compiled examples are placed. Provide a path or a json file or leave blank to use current directory.")
        parser.add_argument("-t","--testdir", required=True, type=str, help = "Directory where the faust dsp examples are located.")
        parser.add_argument("-l","--limit", required=False, type=int, help="Use only a random portion of the dsp files existing in directory")
        parsed_args = parser.parse_args()

        # if clean installations made by previous tests
        if parsed_args.clean is not None:
            self.clean = True
            if parsed_args.clean != "__DEFAULT__": # if path or json file was additionaly passed with --clean
                if (parsed_args.clean.endswith(".json")): # a json file was given
                    self.jsonfileName = os.path.basename(parsed_args.clean)
                    self.outdir = os.path.dirname(parsed_args.clean)
                else:                               # a path to the json was given
                    self.outdir = Path(parsed_args.clean)
        else:                                       # if test
            self.testdir = parsed_args.testdir
            if parsed_args.limit:
                self.limit = parsed_args.limit
        
        self.jsonfile = os.path.join(self.outdir, self.jsonfileName)

    def moveJsonFile(self,json_source_path:Path, json_target_path:Path, log_path:Path) -> None:
        """
        Function used to move the Faust extracted JSON file to the test output directory.

        Args:
            json_source_path (Path): Original path of the .json file.
            json_target_path (Path): Target path in the output directory.
            log_path (Path): Path to the build log file to append logs in case of any exception.
        """
        if json_source_path.exists():
            try:
                os.rename(json_source_path, json_target_path)
            except Exception as e:
                with open(log_path, "a", encoding="utf-8") as log_file:
                    log_file.write(f"\nWARNING: Could not move (rename) JSON file from {json_source_path} to {json_target_path}, continuing.\n")

    def add_faust2wwise_arguments(self,command: list[str]) -> list[str]:
        """
        Randomly selects a set of additional command-line arguments to add to faust2wwise.
        Args:
            command (list[str]): Existing command list to append arguments to.
        Returns:
            list[str]: Modified command list with added arguments.
        """
        # Define possible argument options
        argumentsList = [
            ["--out-of-place"],
            ["--disable-codesign"]
        ]

        for arg in self.additional_arguments:
            argumentsList.append(arg)    
        
        selected_args = random.choice(argumentsList)
        command.extend(selected_args)
        return command

    def run_faust2wwise_on_file(self,dsp_file:Path, script: str ="faust2wwise") -> dict:
        """
        Runs `faust2wwise` on a single .dsp file and captures logs and output.
        Args:
            dsp_file (Path): Path to the .dsp file.
            script (str): Name or path of the faust2wwise script (default: 'faust2wwise').
        Returns:
            dict: Result object containing file path, success status, and logs.
        """
        rel_path = dsp_file.relative_to(self.testdir).with_suffix("")
        output_dir = self.outdir / rel_path
        output_dir.mkdir(parents=True, exist_ok=True)

        log_path = output_dir / "build.log"

        try:
            # Build command as a list, no shell quoting needed
            command = [
                str(script),
                "--output_dir", str(output_dir),
                str(dsp_file)
            ]

            command = self.add_faust2wwise_arguments(command)

            # optional condition, but required when using msys
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
        self.moveJsonFile(json_source_path, json_target_path, log_path)

        return {
            "file": str(dsp_file),
            "output_dir": str(output_dir),
            "log_file": str(log_path),
            "success": success,
            "returncode": result.returncode
        }

    def test_faust2wwise(self) -> None:
        """
        Entry point for running the tests. used to either clean or apply tests.
        """
        self.parse_arguments()

        self.outdir =  self.resolve_output_dir()

        if (self.clean):
            self.clean_tests()
        else :
            self.apply_tests()

    def apply_tests(self) -> None:
        """
        Function used to apply the tests.
        """
        self.testdir = Path(self.testdir).resolve()

        dsp_files = [
            f for f in self.testdir.rglob("*.dsp")
            if str(f.relative_to(self.testdir)).replace("\\", "/") not in self.EXCLUDED_FILES
        ]
        print(f"Found {len(dsp_files)} .dsp files.\n")

        totalFiles = len(dsp_files)

        if self.limit:
            if self.limit >= totalFiles: 
                self.limit = totalFiles
                print(f"Warning : Limit ({self.limit}) greater than number of available samples ({totalFiles}). Testing all available samples.")
            dsp_files = random.sample(dsp_files, min(self.limit, len(dsp_files)))
            print(f"Picked {min(self.limit, len(dsp_files))} out of {totalFiles} .dsp files.\n")
            totalFiles = min(self.limit, len(dsp_files))

        self.outdir.mkdir(parents=True, exist_ok=True)

        results = []

        for i,dsp_file in enumerate(dsp_files):
            result = self.run_faust2wwise_on_file(dsp_file)
            print(f"{'Success' if result['success'] else 'Failed '} : ({i+1}/{totalFiles}) {dsp_file} ")
            results.append(result)

        with open(self.jsonfile, "w", encoding="utf-8") as f:
            json.dump(results, f, indent=2)

        succeeded = [r for r in results if r.get("success")]
        failed = [r for r in results if not r.get("success")]

        print(f"\nResults saved to {self.jsonfile}")
        print(f"Succeeded: {len(succeeded)}")
        print(f"Failed: {len(failed)}")

    def platform_dependent_setup(self) -> None:
        """
        Function that will eventually be used for platform depended setup.
        """
        mySystem = platform.system()

        if (mySystem=="Windows" and not
            ('MSYSTEM' in os.environ or 'MSYS' in os.environ)):
            self.installation_dir = self.wwiseroot / "Authoring" / "x64" / "Release" / "bin" / "Plugins"
            self.plugin_extensions = [".dll", ".exp", ".lib", ".pdb", ".xml"]

            self.additional_arguments = [
                ["--platform","Windows_vc170","--toolset","vc170"]
            ]

        elif (mySystem=="Darwin"):
            wwise_version = Path(self.wwiseroot).name
            self.installation_dir = Path("/Library/Application Support/Audiokinetic") / wwise_version / "Authoring/x64/Release/bin/Plugins"
            self.plugin_extensions = [".dll", ".a", ".dylib", ".xml"]

            self.additional_arguments = []

    def resolve_output_dir(self):
        base_path = Path(self.outdir).resolve()
        parent_dir = base_path.parent
        base_name = base_path.name

        # if no conflict
        if not (parent_dir / base_name).exists():
            return base_path

        # else if there are already other testF2W dirs, rename the outdir by adding the next available suffix after the base_name
        counter = 1
        while True:
            new_name = f"{base_name}({counter})"
            candidate_path = parent_dir / new_name
            if not candidate_path.exists():
                # Update self.outdir by adding a suffix --> i.e "parent_dir/<base_name>(1)""
                self.outdir = str(candidate_path)
                return candidate_path.resolve()
            counter += 1

        return Path(self.outdir).resolve()

    def clean_tests(self) -> None:
        """
        Deletes previously installed Wwise plugins based on the test results.
        Currently non implemented. Requires a way to retrieve the configuration
        and arch options used when compiling the tests in the first place.
        """
        print("Clean installed plugins currently not supported. Exiting.")
        sys.exit(1)

        self.jsonfile =  Path(self.jsonfile).resolve()

        with open(self.jsonfile, "r", encoding="utf-8") as f:
            results = json.load(f)

        total_deleted = []
        total_not_found = []

        for result in results:
            if result.get("success"):
                plugin_base = Path(result["output_dir"]).name
                deleted, not_found = self.delete_plugin_files(plugin_base)
                total_deleted.extend(deleted)
                total_not_found.extend(not_found)

        # === SUMMARY ===
        print(f"\n Deleted {len(total_deleted)} plugin-related files:")
        for p in total_deleted:
            print(f" - {p}")

        if total_not_found:
            print(f"\ {len(total_not_found)} files were not found (possibly already deleted?):")
            for p in total_not_found:
                print(f" - {p}")


    def delete_plugin_files(self,plugin_base_name:str)->tuple[list[Path], list[Path]]:
        """
        Function used to delete all related plugin files based on a base name and their file extensions.
        Args:
            plugin_base_name (str): Base name of the plugin files to delete.
        Returns:
            tuple: (deleted files, files not found)
        """
        deleted = []
        not_found = []

        for ext in self.plugin_extensions:
            file_path = self.installation_dir / f"{plugin_base_name}{ext}"
            if file_path.exists():
                try:
                    os.remove(file_path)
                    deleted.append(file_path)
                except Exception as e:
                    print(f"Error deleting {file_path}: {e}")
            else:
                not_found.append(file_path)

        return deleted, not_found