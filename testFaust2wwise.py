"""
Python script that runs faust2wwise on all the dsp files that exist within the examples directory.
Author's note : run with administrative permissions.
"""
import subprocess
import json
from pathlib import Path
import platform
import os

ROOT_DIR =  Path(__file__).resolve().parents[0]
FAUST_EXAMPLES_DIR = ROOT_DIR / "examples"
BASE_DIR = ROOT_DIR / "myTests"
OUTPUT_JSON_FILE = BASE_DIR / "test_results.json"

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

    return {
        "file": str(dsp_file),
        "output_dir": str(output_dir),
        "log_file": str(log_path),
        "success": success,
        "returncode": result.returncode
    }

def main():

    dsp_files = list(FAUST_EXAMPLES_DIR.rglob("*.dsp"))
    print(f"Found {len(dsp_files)} .dsp files.\n")

    BASE_DIR.mkdir(parents=True, exist_ok=True)
    results = []

    for dsp_file in dsp_files:
        print(f"Processing: {dsp_file}")
        result = run_faust2wwise_on_file(dsp_file)
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
