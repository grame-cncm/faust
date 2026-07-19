#!/usr/bin/env python3
"""Display benchmark summary from JSON results."""

import json
import sys
from pathlib import Path

def main():
    results_file = Path("delay_benchmark_results.json")
    
    if not results_file.exists():
        print("No benchmark results found")
        return 0
    
    with open(results_file) as f:
        results = json.load(f)
    
    print("=== Benchmark Summary ===")
    for test, data in results.items():
        if data.get('best_mcd'):
            print(f"{data['description']:45s}: best with -mcd {data['best_mcd']:3d} ({data['best_time']:.3f} ms)")
    
    return 0

if __name__ == "__main__":
    sys.exit(main())