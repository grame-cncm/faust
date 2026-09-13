# Profiling de eval.cpp

Ce document explique comment utiliser le système de profiling intégré dans `eval.cpp`.

## Description

Le système de profiling permet de mesurer le temps passé dans les différentes fonctions du fichier `eval.cpp`. Il utilise des timers haute résolution pour collecter :

- **Total Time** : Temps total passé dans la fonction (incluant les appels aux sous-fonctions)
- **Self Time** : Temps propre à la fonction (excluant les sous-fonctions)
- **Call Count** : Nombre d'appels à chaque fonction
- **Average Time** : Temps moyen par appel
- **Percentage** : Pourcentage du temps total

## Activation du profiling

### Méthode 1 : Activation par code

Ajoutez ces lignes au début de la fonction que vous voulez profiler (par exemple dans `main.cpp` ou `libcode.cpp`) :

```cpp
#include "evaluate/eval_profiler.h"

// Avant la compilation
EvalProfiler::instance().enable();

// Votre code de compilation ici
// ...

// Après la compilation
EvalProfiler::instance().print_report(std::cerr);
```

### Méthode 2 : Variable d'environnement

Vous pouvez également ajouter une variable d'environnement pour activer le profiling automatiquement. Ajoutez dans `compiler/libcode.cpp` dans la fonction `compile_faust_llvm` ou similaire :

```cpp
// Au début de la fonction
if (getenv("FAUST_PROFILE_EVAL")) {
    EvalProfiler::instance().enable();
}

// À la fin de la fonction, avant le return
if (getenv("FAUST_PROFILE_EVAL")) {
    EvalProfiler::instance().print_report(std::cerr);
    EvalProfiler::instance().reset();
}
```

Puis utilisez :
```bash
FAUST_PROFILE_EVAL=1 faust fichier.dsp
```

## Fonctions instrumentées

Les fonctions suivantes sont actuellement instrumentées :

- `evalprocess()` - Point d'entrée principal
- `eval()` - Évaluation d'expressions
- `realeval()` - Évaluation réelle (fonction principale)
- `a2sb()` - Transformation abstractions -> boxes symboliques
- `real_a2sb()` - Implémentation réelle de a2sb
- `applyList()` - Application de fonctions
- `evalIdDef()` - Évaluation de définitions
- `iteratePar()` - Itérations parallèles
- `iterateSeq()` - Itérations séquentielles
- `boxSimplification()` - Simplification de boxes
- `eval2double()` - Évaluation vers double
- `eval2int()` - Évaluation vers int

## Exemple de sortie

```
========== EVAL.CPP PROFILING REPORT ==========

Function                           Calls          Total Time (ms)   Self Time (ms)    Avg (μs)       % Total
-------------------------------------------------------------------------------------------------------------------
realeval                           12456          1234.567          456.789           99.123         45.2
eval                               15678          987.654           123.456           62.987         36.1
applyList                          3456           456.789           234.567           132.123        16.7
...
-------------------------------------------------------------------------------------------------------------------
Total profiled time: 2734.567 ms

===============================================
```

## Ajout de nouvelles fonctions à profiler

Pour instrumenter une nouvelle fonction, ajoutez simplement `PROFILE_FUNCTION();` au début :

```cpp
static Tree maFonction(Tree arg1, Tree arg2)
{
    PROFILE_FUNCTION();  // <-- Ajouter cette ligne

    // Le reste du code
    // ...
}
```

## Désactivation

Pour désactiver le profiling :
```cpp
EvalProfiler::instance().disable();
```

## Performance

Le système de profiling a un impact minimal sur les performances quand il est désactivé (simple test de booléen). Quand activé, l'overhead est d'environ 1-5% selon la complexité du programme compilé.

## Notes

- Les mesures utilisent `std::chrono::high_resolution_clock` pour une précision nanoseconde
- Le profiler est thread-safe si une seule thread compile à la fois
- Les résultats sont triés par temps total décroissant
- Utilisez `reset()` pour réinitialiser les statistiques entre deux compilations
