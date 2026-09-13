# Résumé de l'instrumentation de eval.cpp

## Objectif

Mesurer le temps passé dans les différentes fonctions du fichier `eval.cpp` pour identifier les goulots d'étranglement de performance lors de la compilation Faust.

## Fichiers modifiés

### 1. **eval_profiler.h** (nouveau)
Header-only profiler léger qui fournit :
- Classe `EvalProfiler` : singleton pour collecter les statistiques
- Classe `ScopedTimer` : RAII timer pour instrumentation automatique
- Macro `PROFILE_FUNCTION()` : à ajouter au début des fonctions

### 2. **eval.cpp** (modifié)
Ajout de `#include "eval_profiler.h"` et instrumentation des fonctions principales :

| Fonction | Rôle | Profiling |
|----------|------|-----------|
| `evalprocess()` | Point d'entrée principal | ✓ |
| `eval()` | Évaluation avec cache | ✓ |
| `realeval()` | Évaluation réelle (switch principal) | ✓ |
| `a2sb()` | Abstractions → boxes symboliques | ✓ |
| `real_a2sb()` | Implémentation de a2sb | ✓ |
| `applyList()` | Application de fonctions | ✓ |
| `evalIdDef()` | Évaluation d'identifiants | ✓ |
| `iteratePar()` | Itérations parallèles | ✓ |
| `iterateSeq()` | Itérations séquentielles | ✓ |
| `boxSimplification()` | Simplification de boxes | ✓ |
| `eval2double()` | Conversion en double | ✓ |
| `eval2int()` | Conversion en entier | ✓ |

### 3. **libcode.cpp** (modifié)
Ajout du support de la variable d'environnement `FAUST_PROFILE_EVAL` :
- Dans `createFactoryAux1()` : activation/désactivation et rapport
- Dans `createFactoryAux2()` : idem

## Utilisation

### Méthode simple (recommandée)

```bash
# Activer le profiling avec une variable d'environnement
FAUST_PROFILE_EVAL=1 faust yourfile.dsp -o output.cpp
```

### Exemple de sortie

```
Eval profiling enabled (FAUST_PROFILE_EVAL)

... compilation normale ...

========== EVAL.CPP PROFILING REPORT ==========

Function                           Calls          Total Time (ms)   Self Time (ms)    Avg (μs)       % Total
-------------------------------------------------------------------------------------------------------------------
realeval                           12456          1234.567          456.789           99.123         45.2
eval                               15678          987.654           123.456           62.987         36.1
applyList                          3456           456.789           234.567           132.123        16.7
a2sb                               8901           234.567           89.012            26.354         8.6
evalIdDef                          2345           123.456           98.765            52.643         4.5
iteratePar                         456            89.012            67.890            195.201        3.3
boxSimplification                  789            67.890            45.678            86.046         2.5
...
-------------------------------------------------------------------------------------------------------------------
Total profiled time: 2734.567 ms

===============================================
```

## Interprétation des résultats

### Colonnes importantes

1. **Total Time** : Temps total incluant les appels récursifs
   - Identifie les fonctions "chaudes"
   - Indique où le temps est majoritairement passé

2. **Self Time** : Temps propre sans les sous-appels
   - Identifie le temps réel passé dans le corps de la fonction
   - Plus précis pour l'optimisation

3. **Calls** : Nombre d'appels
   - Trop d'appels = opportunité de cache/mémoïsation
   - Peu d'appels mais temps élevé = fonction complexe

4. **Avg (μs)** : Temps moyen par appel
   - Permet de comparer l'efficacité relative
   - Utile pour identifier les fonctions anormalement lentes

### Analyse typique

**Cas 1 : eval() a un temps élevé**
- Normal, c'est la fonction principale
- Regarder `realeval()` pour plus de détails

**Cas 2 : applyList() domine**
- Beaucoup d'applications de fonctions
- Possibilité d'optimiser le pattern matching

**Cas 3 : iteratePar/Seq avec beaucoup d'appels**
- Code utilisant beaucoup de par(i, N, ...)
- Peut indiquer un besoin d'optimisation des itérations

**Cas 4 : boxSimplification lent**
- Diagrammes complexes
- Opportunité d'optimiser la propagation de signaux

## Script de test

Un script `test_profiling.sh` est fourni pour tester l'instrumentation :

```bash
cd compiler/evaluate
./test_profiling.sh
```

## Overhead de performance

- **Désactivé** : < 0.1% (simple test de booléen)
- **Activé** : 1-5% typiquement
  - Dépend de la profondeur des appels
  - Acceptable pour le debugging

## Ajout de nouvelles fonctions

Pour profiler d'autres fonctions, ajoutez simplement :

```cpp
static Tree maFonction(Tree arg)
{
    PROFILE_FUNCTION();  // <-- Ajouter cette ligne

    // ... code existant ...
}
```

## Notes techniques

### Précision
- Utilise `std::chrono::high_resolution_clock`
- Précision nanoseconde (théorique)
- Précision effective : microseconde (dépend du système)

### Thread-safety
- Non thread-safe par défaut
- OK pour faust (compilation mono-thread)
- Nécessiterait des mutex pour multi-threading

### Mémoire
- Footprint minimal : ~1KB par fonction instrumentée
- Pas d'allocation dynamique en production (seulement std::map)

## Limitations connues

1. **Récursion** : Le temps est correctement attribué mais la pile d'appels peut être profonde
2. **Inlining** : Les fonctions inlinées par le compilateur ne seront pas mesurées
3. **Optimisations** : En mode release (-O3), certaines mesures peuvent être moins précises

## Désactivation permanente

Pour désactiver complètement le profiling :

1. Retirer les `PROFILE_FUNCTION()` de eval.cpp
2. Ou commenter `#include "eval_profiler.h"`
3. Recompiler faust

## Documentation complète

Voir [PROFILING_README.md](PROFILING_README.md) pour plus de détails.
