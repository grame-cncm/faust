# 🚀 Quick Start - Profiling eval.cpp

## TL;DR

```bash
# 1. Recompiler Faust
cd /Users/yannorlarey/Documents/Install/faust
make clean && make

# 2. Profiler une compilation
FAUST_PROFILE_EVAL=1 faust yourfile.dsp -o output.cpp
```

C'est tout! Le rapport apparaît automatiquement. ✨

---

## Exemple complet (30 secondes)

```bash
# Créer un fichier de test
cat > /tmp/test.dsp << 'EOF'
import("stdfaust.lib");
process = os.osc(440) : fi.lowpass(4, 1000);
EOF

# Compiler avec profiling
FAUST_PROFILE_EVAL=1 faust /tmp/test.dsp -o /tmp/test.cpp
```

**Vous verrez :**
```
Eval profiling enabled (FAUST_PROFILE_EVAL)

... compilation normale ...

========== EVAL.CPP PROFILING REPORT ==========

Function                           Calls          Total Time (ms)   Self Time (ms)    Avg (μs)       % Total
-------------------------------------------------------------------------------------------------------------------
realeval                           1234           123.456           45.678            100.048        45.2
eval                               5678           98.765            23.456            17.389         36.1
applyList                          456            45.678            23.456            100.171        16.7
...
-------------------------------------------------------------------------------------------------------------------
Total profiled time: 273.456 ms

===============================================
```

---

## Interprétation rapide

- **Total Time** = Temps incluant les sous-fonctions
- **Self Time** = Temps réel passé dans la fonction
- **Calls** = Nombre d'appels
- **Avg** = Temps moyen par appel

**Règle simple :** Regardez les fonctions avec un **% Total** élevé et un **Self Time** élevé.

---

## Cas d'usage courants

### Comparer deux versions

```bash
echo "Version A:"
FAUST_PROFILE_EVAL=1 faust versionA.dsp -o /dev/null 2>&1 | tail -15

echo "Version B:"
FAUST_PROFILE_EVAL=1 faust versionB.dsp -o /dev/null 2>&1 | tail -15
```

### Profiler tout un projet

```bash
for f in *.dsp; do
    echo "=== $f ==="
    FAUST_PROFILE_EVAL=1 faust "$f" -o /dev/null 2>&1 | grep -A 5 "PROFILING REPORT"
done
```

### Extraire les top 5 fonctions

```bash
FAUST_PROFILE_EVAL=1 faust file.dsp -o /dev/null 2>&1 | \
    awk '/Function.*Calls/,/---/ {if(NR>1) print}' | head -6
```

---

## Astuce pro

Créez un alias dans votre `.bashrc` ou `.zshrc` :

```bash
alias faustprof='FAUST_PROFILE_EVAL=1 faust'
```

Puis utilisez :

```bash
faustprof myfile.dsp -o output.cpp
```

---

## Documentation complète

- 📘 [RESUME_INSTRUMENTATION_FR.md](RESUME_INSTRUMENTATION_FR.md) - Guide complet
- 📙 [EXEMPLE_UTILISATION.md](EXEMPLE_UTILISATION.md) - Exemples avancés
- 📗 [PROFILING_README.md](PROFILING_README.md) - Documentation technique
- 📕 [FILES_SUMMARY.txt](FILES_SUMMARY.txt) - Liste des fichiers

---

## Questions fréquentes

**Q: Dois-je toujours activer le profiling?**
R: Non! Utilisez-le uniquement quand vous voulez analyser les performances.

**Q: Y a-t-il un impact sur les performances?**
R: Oui, environ 1-5% de ralentissement quand activé. Insignifiant quand désactivé.

**Q: Puis-je profiler d'autres fonctions?**
R: Oui! Ajoutez `PROFILE_FUNCTION();` au début de n'importe quelle fonction dans eval.cpp.

**Q: Le profiling fonctionne-t-il avec tous les backends?**
R: Oui! (C++, LLVM, Interpreter, etc.)

---

**Prêt à analyser vos compilations!** 🎯

Pour plus d'infos : [RESUME_INSTRUMENTATION_FR.md](RESUME_INSTRUMENTATION_FR.md)
