#!/usr/bin/env python3
"""
Benchmark script for testing JAX delay line optimizations.

This script tests various delay line configurations with different -mcd values
to help determine optimal settings for different DSP types.
"""

import subprocess
import tempfile
import json
import time
import sys
import os
from pathlib import Path

# Test configurations
DELAY_TESTS = {
    "single_small": {
        "dsp": """
import("stdfaust.lib");
process = _ : @(8);  // Single small delay
""",
        "description": "Single small delay (8 samples)"
    },
    "single_large": {
        "dsp": """
import("stdfaust.lib");
process = _ : @(512);  // Single large delay
""",
        "description": "Single large delay (512 samples)"
    },
    "comb_filter": {
        "dsp": """
import("stdfaust.lib");
process = _ : +~(@(100) : *(0.7));  // Comb filter
""",
        "description": "Comb filter with 100 sample delay"
    },
    "multi_delay": {
        "dsp": """
import("stdfaust.lib");
delay1 = 8;
delay2 = 32;
delay3 = 128;
delay4 = 512;
comb1 = +~(@(delay1) : *(0.7));
comb2 = +~(@(delay2) : *(0.6));
comb3 = +~(@(delay3) : *(0.5));
comb4 = +~(@(delay4) : *(0.4));
process = _ <: comb1, comb2, comb3, comb4 :> /(4);
""",
        "description": "Multiple parallel comb filters"
    },
    "reverb_like": {
        "dsp": """
import("stdfaust.lib");
// Simplified reverb-like structure
ap1 = fi.allpass_comb(1024, 0.05, 0.7);
ap2 = fi.allpass_comb(512, 0.03, 0.7);
ap3 = fi.allpass_comb(256, 0.02, 0.7);
process = _ : ap1 : ap2 : ap3;
""",
        "description": "Reverb-like allpass chain"
    },
    "variable_delay": {
        "dsp": """
import("stdfaust.lib");
maxdelay = 1000;
delaytime = os.osc(0.5) * 200 + 300;  // Modulated delay time
process = de.delay(maxdelay, delaytime);
""",
        "description": "Variable delay with modulation"
    }
}

MCD_VALUES = [4, 8, 16, 32, 64, 128]

def compile_dsp(dsp_code, mcd_value, output_path):
    """Compile a DSP file with specified -mcd value."""
    # Write DSP to temp file
    with tempfile.NamedTemporaryFile(mode='w', suffix='.dsp', delete=False) as f:
        f.write(dsp_code)
        dsp_path = f.name
    
    try:
        repo_root = Path(__file__).parent.parent.parent
        faust_bin = repo_root / "build" / "bin" / "faust"
        arch_file = repo_root / "architecture" / "jax" / "minimal.py"

        cmd = [
            str(faust_bin),
            "-lang", "nnx",
            "-a", str(arch_file),
            # The uninstalled build/bin/faust has no default library path, so
            # point it at the repo's libraries for import("stdfaust.lib").
            "-I", str(repo_root / "libraries"),
            "-mcd", str(mcd_value),
            dsp_path,
            "-o", output_path
        ]
        
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode != 0:
            print(f"Compilation failed: {result.stderr}")
            return False
        return True
    finally:
        os.unlink(dsp_path)

def benchmark_dsp(py_path, duration=1.0, iterations=50):
    """Run benchmark on compiled DSP."""
    cmd = [
        sys.executable,
        py_path,
        "--benchmark", str(iterations),
        "--jit",
        "-d", str(duration)
    ]
    
    env = os.environ.copy()
    env["JAX_PLATFORMS"] = "cpu"
    
    result = subprocess.run(cmd, capture_output=True, text=True, env=env)
    
    if result.returncode != 0:
        print(f"\nBenchmark failed with return code {result.returncode}")
        print(f"Stderr: {result.stderr[:500]}")
        print(f"Stdout: {result.stdout[:500]}")
        return None
    
    # Parse output for timing info (check both stdout and stderr)
    combined_output = result.stdout + result.stderr
    for line in combined_output.split('\n'):
        if "Average time:" in line:
            # Extract time in ms
            time_str = line.split("Average time:")[1].split("ms")[0].strip()
            return float(time_str)
    
    return None

def main():
    print("="*80)
    print("JAX Delay Line Optimization Benchmark")
    print("="*80)
    print()
    
    results = {}
    failures = 0

    for test_name, test_config in DELAY_TESTS.items():
        print(f"\nTesting: {test_config['description']}")
        print("-" * 60)
        
        test_results = {}
        best_mcd = None
        best_time = float('inf')
        
        for mcd in MCD_VALUES:
            with tempfile.NamedTemporaryFile(suffix='.py', delete=False) as f:
                py_path = f.name
            
            try:
                # Compile with specific mcd value
                if not compile_dsp(test_config['dsp'], mcd, py_path):
                    print(f"  -mcd {mcd:3d}: Compilation failed")
                    failures += 1
                    continue
                
                # Benchmark
                avg_time = benchmark_dsp(py_path, duration=0.5, iterations=20)
                
                if avg_time is not None:
                    test_results[mcd] = avg_time
                    print(f"  -mcd {mcd:3d}: {avg_time:8.3f} ms", end="")
                    
                    if avg_time < best_time:
                        best_time = avg_time
                        best_mcd = mcd
                        print(" ⭐ (best so far)")
                    else:
                        speedup = (avg_time / best_time - 1) * 100
                        print(f" ({speedup:+.1f}% vs best)")
                else:
                    print(f"  -mcd {mcd:3d}: Benchmark failed")
                    failures += 1
            
            finally:
                if os.path.exists(py_path):
                    os.unlink(py_path)
        
        results[test_name] = {
            "description": test_config['description'],
            "times": test_results,
            "best_mcd": best_mcd,
            # None (JSON null) rather than float('inf'), which json.dump would
            # write as the non-standard token Infinity.
            "best_time": best_time if best_mcd is not None else None
        }
        
        if best_mcd is not None:
            print(f"\n  🏆 Best: -mcd {best_mcd} ({best_time:.3f} ms)")
    
    # Summary
    print("\n" + "="*80)
    print("SUMMARY")
    print("="*80)
    print()
    
    print("Optimal -mcd values by DSP type:")
    print("-" * 60)
    for test_name, result in results.items():
        if result['best_mcd'] is not None:
            print(f"  {result['description']:40s} : -mcd {result['best_mcd']:3d}")
    
    print("\n" + "="*80)
    print("RECOMMENDATIONS")
    print("="*80)
    print("""
Based on these benchmarks:

1. Simple delays: Lower -mcd values (4-8) often perform better
2. Complex filter networks: Default -mcd 16 is usually good
3. Variable delays: May benefit from specific tuning
4. Reverb algorithms: May need higher -mcd values for correctness

Always verify correctness when changing -mcd values!
""")
    
    # Save results to JSON for further analysis
    with open("delay_benchmark_results.json", "w") as f:
        json.dump(results, f, indent=2)
    print(f"Results saved to delay_benchmark_results.json")

    if failures:
        print(f"\n{failures} compile/benchmark run(s) failed")
        sys.exit(1)

if __name__ == "__main__":
    main()