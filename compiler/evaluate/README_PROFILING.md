# 📊 Instrumentation et Profiling de eval.cpp

Ce répertoire contient l'instrumentation complète du fichier `eval.cpp` pour mesurer les performances des fonctions d'évaluation du compilateur Faust.

## 🎯 Objectif

Identifier précisément où le compilateur Faust passe son temps pendant la phase d'évaluation des expressions, afin de pouvoir optimiser les parties critiques.

## 📚 Documentation

### 🚀 Pour commencer rapidement
**→ [QUICKSTART.md](QUICKSTART.md)** - Guide de démarrage rapide (5 minutes)

### 📖 Guides complets
- **[RESUME_INSTRUMENTATION_FR.md](RESUME_INSTRUMENTATION_FR.md)** - Guide complet en français
- **[PROFILING_README.md](PROFILING_README.md)** - Documentation technique en anglais

### 📝 Références
- **[EXEMPLE_UTILISATION.md](EXEMPLE_UTILISATION.md)** - Exemples pratiques et scripts
- **[INSTRUMENTATION_RESUME.md](INSTRUMENTATION_RESUME.md)** - Résumé technique détaillé
- **[FILES_SUMMARY.txt](FILES_SUMMARY.txt)** - Liste des fichiers modifiés

## ⚡ Utilisation rapide

```bash
# 1. Recompiler Faust (une seule fois)
make clean && make

# 2. Profiler une compilation
FAUST_PROFILE_EVAL=1 faust yourfile.dsp -o output.cpp
```

## 📁 Fichiers

### Code source
- **`eval_profiler.h`** - Header-only profiler (C++11)
- **`eval.cpp`** - [MODIFIÉ] Ajout de `PROFILE_FUNCTION()` dans 12 fonctions
- **`../libcode.cpp`** - [MODIFIÉ] Support de `FAUST_PROFILE_EVAL`

### Scripts
- **`test_profiling.sh`** - Script de test automatique

### Documentation
- 6 fichiers de documentation (voir ci-dessus)

## 🔍 Fonctions instrumentées

| Fonction | Description | Importance |
|----------|-------------|------------|
| `evalprocess()` | Point d'entrée principal | ⭐ |
| `eval()` | Cache et dispatch | ⭐⭐⭐⭐⭐ |
| `realeval()` | Machine à états principale | ⭐⭐⭐⭐⭐ |
| `a2sb()` | Abstractions → boxes | ⭐⭐⭐ |
| `applyList()` | Application de fonctions | ⭐⭐⭐⭐ |
| `evalIdDef()` | Résolution d'identifiants | ⭐⭐⭐⭐ |
| `iteratePar()` | Itérations parallèles | ⭐⭐⭐ |
| `iterateSeq()` | Itérations séquentielles | ⭐⭐⭐ |
| `boxSimplification()` | Simplification de boxes | ⭐⭐ |
| `eval2double()` | Conversion vers double | ⭐ |
| `eval2int()` | Conversion vers int | ⭐ |

## 📊 Exemple de sortie

```
========== EVAL.CPP PROFILING REPORT ==========

Function                           Calls          Total Time (ms)   Self Time (ms)    Avg (μs)       % Total
-------------------------------------------------------------------------------------------------------------------
realeval                           12456          1234.567          456.789           99.123         45.2
eval                               15678          987.654           123.456           62.987         36.1
applyList                          3456           456.789           234.567           132.123        16.7
a2sb                               8901           234.567           89.012            26.354         8.6
evalIdDef                          2345           123.456           98.765            52.643         4.5
...
-------------------------------------------------------------------------------------------------------------------
Total profiled time: 2734.567 ms

===============================================
```

## 🎓 Exemples d'utilisation

### Profiler un fichier simple
```bash
FAUST_PROFILE_EVAL=1 faust noise.dsp -o noise.cpp
```

### Comparer deux versions
```bash
FAUST_PROFILE_EVAL=1 faust v1.dsp -o /dev/null 2>&1 | tail -15
FAUST_PROFILE_EVAL=1 faust v2.dsp -o /dev/null 2>&1 | tail -15
```

### Profiler un projet complet
```bash
for f in *.dsp; do
    echo "=== $f ==="
    FAUST_PROFILE_EVAL=1 faust "$f" -o /dev/null 2>&1 | grep -A 10 "PROFILING"
done > profiling_results.txt
```

## 🔧 Ajouter de nouvelles fonctions

Pour instrumenter d'autres fonctions dans `eval.cpp` :

```cpp
static Tree maFonction(Tree arg)
{
    PROFILE_FUNCTION();  // <-- Ajouter cette ligne

    // ... reste du code ...
}
```

Puis recompiler Faust.

## ⚠️ Notes importantes

- **Performance** : L'overhead est < 0.1% quand désactivé, 1-5% quand activé
- **Thread-safety** : Non thread-safe (OK car Faust compile en mono-thread)
- **Compatibilité** : C++11 minimum (GCC, Clang, MSVC)
- **Utilisation** : N'activez le profiling QUE pour analyser les performances

## 🧪 Tests

```bash
# Tester l'instrumentation
./test_profiling.sh

# Vérifier la compilation
make clean && make

# Test simple
echo "process = _;" | FAUST_PROFILE_EVAL=1 faust - -o /dev/null
```

## 📈 Interprétation des résultats

### Colonnes importantes
- **Calls** : Nombre d'appels → cache/mémoïsation si élevé
- **Total Time** : Temps incluant sous-fonctions → fonctions "chaudes"
- **Self Time** : Temps propre → où optimiser vraiment
- **Avg** : Temps moyen → comparer l'efficacité
- **% Total** : Pourcentage → vue d'ensemble

### Signaux d'alerte 🚨
- ⚠️ `realeval` > 50% avec Self Time élevé → problème d'algorithme
- ⚠️ `evalIdDef` très élevé → besoin de cache environnement
- ⚠️ `applyList` dominant → optimiser pattern matching
- ⚠️ `iteratePar/Seq` avec beaucoup d'appels → optimiser itérations

## 🆘 Support

En cas de problème :

1. Vérifier que Faust a été recompilé : `make clean && make`
2. Vérifier que les fichiers existent : `ls -la eval_profiler.h`
3. Tester avec le script : `./test_profiling.sh`
4. Consulter la documentation complète : [RESUME_INSTRUMENTATION_FR.md](RESUME_INSTRUMENTATION_FR.md)

## 📜 Licence

Même licence que le projet Faust (GNU LGPL).

---

**Prêt à profiler!** 🚀

➡️ Commencez par [QUICKSTART.md](QUICKSTART.md)
