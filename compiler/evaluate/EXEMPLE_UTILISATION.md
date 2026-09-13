# Exemples d'utilisation du profiler eval.cpp

## Exemple 1 : Profiler un fichier DSP simple

```bash
# Créer un fichier de test
cat > test.dsp << 'EOF'
import("stdfaust.lib");
process = no.noise;
EOF

# Compiler avec profiling
FAUST_PROFILE_EVAL=1 faust test.dsp -o test.cpp

# La sortie contiendra le rapport de profiling à la fin
```

## Exemple 2 : Comparer deux versions

```bash
# Version A : code simple
cat > simple.dsp << 'EOF'
process = 440 * 0.5;
EOF

# Version B : code complexe avec itérations
cat > complex.dsp << 'EOF'
process = par(i, 100, i * 0.01) :> _;
EOF

# Comparer les temps
echo "=== Simple ==="
FAUST_PROFILE_EVAL=1 faust simple.dsp -o /dev/null 2>&1 | tail -20

echo ""
echo "=== Complex ==="
FAUST_PROFILE_EVAL=1 faust complex.dsp -o /dev/null 2>&1 | tail -20
```

## Exemple 3 : Identifier les goulots d'étranglement

```bash
# Fichier avec beaucoup de récursion
cat > recursive.dsp << 'EOF'
import("stdfaust.lib");

// Fonction récursive
fib(0) = 1;
fib(1) = 1;
fib(n) = fib(n-1) + fib(n-2);

process = fib(10);
EOF

# Profiler
FAUST_PROFILE_EVAL=1 faust recursive.dsp -o recursive.cpp 2>&1 | tee profile.txt

# Analyser le rapport
echo ""
echo "Top 5 fonctions:"
grep -A 10 "EVAL.CPP PROFILING REPORT" profile.txt | head -15
```

## Exemple 4 : Profiler avec différentes options de compilation

```bash
cat > test.dsp << 'EOF'
import("stdfaust.lib");
process = os.osc(440) : fi.lowpass(4, 1000);
EOF

# Sans simplification
echo "=== Sans simplification ==="
FAUST_PROFILE_EVAL=1 faust test.dsp -o /dev/null 2>&1 | grep "boxSimplification"

# Avec simplification (option par défaut dans certains cas)
echo ""
echo "=== Avec simplification ==="
FAUST_PROFILE_EVAL=1 faust -light test.dsp -o /dev/null 2>&1 | grep "boxSimplification"
```

## Exemple 5 : Profiler un projet complet

```bash
#!/bin/bash

# Script pour profiler tous les fichiers .dsp d'un projet
PROJECT_DIR="./my_faust_project"
RESULTS_FILE="profiling_results.txt"

echo "Profiling all DSP files in $PROJECT_DIR" > $RESULTS_FILE
echo "==========================================" >> $RESULTS_FILE

for dsp_file in "$PROJECT_DIR"/*.dsp; do
    echo "" >> $RESULTS_FILE
    echo "File: $(basename $dsp_file)" >> $RESULTS_FILE
    echo "----------------------------------------" >> $RESULTS_FILE

    FAUST_PROFILE_EVAL=1 faust "$dsp_file" -o /dev/null 2>&1 | \
        grep -A 15 "EVAL.CPP PROFILING REPORT" >> $RESULTS_FILE
done

echo ""
echo "Results saved to $RESULTS_FILE"
cat $RESULTS_FILE
```

## Exemple 6 : Extraction des statistiques pour analyse

```bash
cat > test.dsp << 'EOF'
import("stdfaust.lib");
process = os.osc(440);
EOF

# Compiler et extraire seulement les données
FAUST_PROFILE_EVAL=1 faust test.dsp -o /dev/null 2>&1 | \
    awk '/EVAL.CPP PROFILING REPORT/,/===============/' | \
    grep -E "realeval|eval|applyList" | \
    awk '{printf "%s: %.2f ms (%s calls)\n", $1, $4, $2}'
```

Exemple de sortie :
```
realeval: 45.67 ms (1234 calls)
eval: 89.12 ms (5678 calls)
applyList: 23.45 ms (456 calls)
```

## Exemple 7 : Profiler avec différents backends

```bash
cat > test.dsp << 'EOF'
process = _ * 0.5;
EOF

# C++
echo "=== C++ backend ==="
FAUST_PROFILE_EVAL=1 faust -lang cpp test.dsp -o /dev/null 2>&1 | tail -15

# LLVM
echo ""
echo "=== LLVM backend ==="
FAUST_PROFILE_EVAL=1 faust -lang llvm test.dsp -o /dev/null 2>&1 | tail -15

# Interpreter
echo ""
echo "=== Interpreter backend ==="
FAUST_PROFILE_EVAL=1 faust -lang interp test.dsp -o /dev/null 2>&1 | tail -15
```

## Exemple 8 : Profiling dans un Makefile

```makefile
# Makefile avec support du profiling

# Activer le profiling avec: make PROFILE=1
ifdef PROFILE
    FAUST_FLAGS := FAUST_PROFILE_EVAL=1
endif

%.cpp: %.dsp
	$(FAUST_FLAGS) faust $(FAUST_OPTIONS) $< -o $@

profile-all:
	@echo "Profiling all DSP files..."
	@FAUST_PROFILE_EVAL=1 $(MAKE) all 2>&1 | tee profiling_report.txt
```

Usage :
```bash
# Compilation normale
make

# Compilation avec profiling
make PROFILE=1

# Ou directement
make profile-all
```

## Exemple 9 : Automatisation avec script Python

```python
#!/usr/bin/env python3

import subprocess
import re
import sys

def profile_dsp(dsp_file):
    """Profile un fichier DSP et retourne les statistiques."""
    env = {'FAUST_PROFILE_EVAL': '1'}
    cmd = ['faust', dsp_file, '-o', '/dev/null']

    result = subprocess.run(cmd, env=env, capture_output=True, text=True)

    # Extraire les statistiques
    output = result.stderr
    stats = {}

    # Parser le rapport
    lines = output.split('\n')
    in_report = False

    for line in lines:
        if 'EVAL.CPP PROFILING REPORT' in line:
            in_report = True
            continue
        if in_report and '---' not in line and line.strip():
            parts = line.split()
            if len(parts) >= 5:
                func_name = parts[0]
                try:
                    total_time = float(parts[3])
                    calls = int(parts[1])
                    stats[func_name] = {'time': total_time, 'calls': calls}
                except (ValueError, IndexError):
                    pass

    return stats

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: profile_dsp.py <file.dsp>")
        sys.exit(1)

    stats = profile_dsp(sys.argv[1])

    print(f"\nProfiling results for {sys.argv[1]}:")
    print("-" * 60)

    # Trier par temps total
    for func, data in sorted(stats.items(), key=lambda x: x[1]['time'], reverse=True):
        print(f"{func:30} {data['time']:10.2f} ms  ({data['calls']:6} calls)")
```

Usage :
```bash
chmod +x profile_dsp.py
./profile_dsp.py myfile.dsp
```

## Conseils d'analyse

### 1. Identifier les fonctions lentes
```bash
FAUST_PROFILE_EVAL=1 faust test.dsp -o /dev/null 2>&1 | \
    grep -A 20 "EVAL.CPP PROFILING REPORT" | \
    sort -k4 -rn | head -10
```

### 2. Compter les appels excessifs
```bash
# Fonctions appelées plus de 1000 fois
FAUST_PROFILE_EVAL=1 faust test.dsp -o /dev/null 2>&1 | \
    awk '/EVAL.CPP PROFILING/,/======/' | \
    awk '$2 > 1000 {print $1 ": " $2 " calls"}'
```

### 3. Calculer le ratio temps/appel
```bash
# Fonctions avec temps moyen > 100 microseconds
FAUST_PROFILE_EVAL=1 faust test.dsp -o /dev/null 2>&1 | \
    awk '/EVAL.CPP PROFILING/,/======/' | \
    awk '$5 > 100 {printf "%s: %.2f μs/call\n", $1, $5}'
```

## Intégration CI/CD

### GitHub Actions

```yaml
name: Performance Profiling

on: [push, pull_request]

jobs:
  profile:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2

      - name: Build Faust
        run: make

      - name: Profile test files
        run: |
          for f in tests/*.dsp; do
            echo "Profiling $f"
            FAUST_PROFILE_EVAL=1 ./faust "$f" -o /dev/null 2>&1 | \
              tee -a profile_results.txt
          done

      - name: Upload results
        uses: actions/upload-artifact@v2
        with:
          name: profiling-results
          path: profile_results.txt
```

Ces exemples couvrent la plupart des cas d'usage du profiler. Adaptez-les à vos besoins spécifiques!
