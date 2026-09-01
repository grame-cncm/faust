## Framework de benchmark FAUST

Le contenu de ce dossier implémente le framework utilisé pour mesurer et comparer les performances du
code DSP généré par les backends FAUST, avec une attention particulière portée aux implémentations
`C++` et `Mojo`.

Le framework ne constitue pas un backend supplémentaire : il orchestre les différentes étapes
nécessaires pour transformer un même programme FAUST en programmes exécutables comparables, les
exécuter dans des conditions homogènes et collecter les résultats dans une représentation commune.

Le flux général peut être résumé de la manière suivante :

```text
programme FAUST
      |
      v
compilateur FAUST + architecture de benchmark
      |
      +---------------------+
      |                     |
      v                     v
 source C++            source Mojo
      |                     |
      v                     v
   clang++              mojo build
      |                     |
      +----------+----------+
                 |
                 v
          runtime benchmark
                 |
                 v
        rapport texte / CSV
                 |
                 v
          plots et snapshots
```

Le même framework comprend également un parcours d'inspection séparé du benchmark, utilisé pour
produire l'`LLVM IR` et l'assembly du kernel généré sans introduire dans le code observé la logique de
mesure et de reporting.

## Utilisation rapide

Cette section résume le parcours minimal permettant d'utiliser le benchmark à partir d'une copie du
repository.

Sur macOS, Pixi peut être installé avec Homebrew :

```sh
brew install pixi
```

Depuis le dossier du benchmark :

```sh
cd architecture/_bench
pixi install
```

`pixi install` installe l'environnement décrit par `pixi.toml` et `pixi.lock`. Il fournit notamment
l'environnement Mojo ainsi que Python et les dépendances utilisées par les scripts de reporting,
comme `pandas` et `matplotlib`.

Le framework utilise le compilateur FAUST construit dans le repository. Avant d'exécuter les tests,
il faut donc disposer du binaire FAUST correspondant dans l'arborescence de build du projet.

L'environnement peut ensuite être activé avec :

```sh
pixi shell
```

Une fois dans cet environnement, la commande principale est `bench` :

```sh
bench --help
```

Pour lancer directement tous les DSP disponibles avec tous les modes et tous les backends configurés :

```sh
bench run all all all all all
```

Un cas plus réduit, généralement plus pratique pour un test rapide, est par exemple :

```sh
bench run all all 48 64 all
```

Cette commande compare les modes scalar et vector, C++ et Mojo, à `48 kHz` avec des buffers de `64`
frames, sur tous les DSP présents dans le corpus du benchmark.

Les résultats sont accumulés dans :

```text
report/report.csv
```

Un graphique peut ensuite être produit avec :

```sh
bench plot compare_backends
```

Pour conserver l'état courant des mesures :

```sh
bench snapshot compare_backends
```

Enfin, les artifacts régénérables peuvent être supprimés avec :

```sh
bench clean
```

Il n'est pas nécessaire d'activer explicitement une shell Pixi. Les mêmes commandes peuvent être
exécutées directement avec `pixi run`, par exemple :

```sh
pixi run bench run all all 48 64 all
```

## Organisation du dossier

Les principaux composants sont organisés selon la structure conceptuelle suivante :

```text
architecture/_bench/
├── arch/
│   └── cpp/
│       ├── common.h
│       ├── bench.h
│       ├── bench.cpp
│       └── inspect.cpp
├── script/
│   └── implémentation Python du framework
├── src/
│   └── *.dsp
├── report/
│   ├── report.csv
│   ├── bin/
│   ├── tab/
│   ├── tmp/
│   ├── plot/
│   ├── snap/
│   ├── llvm/
│   └── asm/
├── pixi.toml
└── pixi.lock
```

Le dossier `src` contient les programmes FAUST utilisés comme cas de benchmark. Le framework accepte
à la fois ces sources et des chemins explicites fournis par l'utilisateur, et déduit du nom du fichier
l'identité du DSP utilisée dans les rapports.

`arch/cpp` contient les architectures dédiées au backend C++. Les architectures Mojo correspondantes
ne sont pas copiées dans `_bench` : le framework utilise directement `architecture/mojo/bench.mojo`
et `architecture/mojo/inspect.mojo`, ainsi que les packages dont elles dépendent.

`script` contient le code Python qui implémente la CLI, la génération des cas, la compilation, la
gestion des rapports et la production des graphiques. Le passage d'une implémentation shell à Python
permet de conserver la même logique sous macOS, Linux et Windows sans dépendre d'utilitaires ou de
sémantiques propres à une shell POSIX.

## Environnement Pixi

Le dossier constitue un workspace Pixi autonome. `pixi.toml` décrit la toolchain et les dépendances
nécessaires au framework, tandis que `pixi.lock` mémorise la résolution concrète de l'environnement.

L'environnement peut être activé avec :

```sh
pixi shell
```

Dans cette shell, le framework est exposé par la commande `bench` :

```sh
bench --help
```

Les mêmes commandes peuvent être exécutées sans entrer explicitement dans la shell avec `pixi run` :

```sh
pixi run bench --help
```

Pixi est utilisé principalement pour rendre reproductibles l'environnement Mojo et les dépendances
Python du framework. La logique du benchmark reste cependant indépendante de la shell depuis laquelle
la commande est invoquée.

## Configuration numérique

Le framework suppose une configuration numérique fixe, choisie pour comparer les backends dans les
mêmes conditions que celles utilisées pendant le développement du backend Mojo.

La précision interne du DSP est sélectionnée pendant la transpilation FAUST avec :

```text
-double
```

Le calcul interne produit par le générateur utilise donc une précision `f64`. Cette propriété appartient
à la phase de génération FAUST et n'est pas propagée comme dimension configurable aux compilations
suivantes.

L'interface externe des architectures utilise en revanche des échantillons `f32`. Pour C++, le type est
défini avec :

```text
-DFAUSTFLOAT=float
```

alors que Mojo utilise la define :

```text
-D DFAUST=DType.float32
```

On obtient donc le profil fixe suivant :

```text
calcul interne DSP     f64
buffers externes C++   f32
buffers externes Mojo  f32
```

La précision ne constitue donc pas un axe du benchmark et n'est pas sélectionnée par l'utilisateur.

## Modes scalaire et vectoriel

Le framework expose deux modes de génération :

- `scalar`, correspondant à la génération FAUST ordinaire ;
- `vec`, correspondant à la génération via le vector code container de FAUST.

Le mode vectoriel ajoute aux options de FAUST :

```text
-vec -vs 4 -dfs
```

Le mode `-vec` réorganise le kernel en sous-boucles en fonction des dépendances du DSP. Dans le backend
C++, ces boucles peuvent ensuite être auto-vectorisées par le compilateur, tandis que le backend Mojo
utilise cette structure comme base pour l'émission SIMD explicite décrite dans la documentation du
generator.

La valeur `-vs 4` correspond à la configuration SIMD utilisée dans le développement actuel et doit
rester cohérente avec la largeur vectorielle supposée par le code Mojo généré.

## Commande `run`

La commande principale du framework génère, compile et exécute une matrice de benchmarks :

```sh
bench run <modes> <langs> <sample-rates> <buffer-sizes> <sources...>
```

Par exemple :

```sh
bench run all all 48 64 all
bench run scalar cpp,mojo 48 64 carre_volterra
bench run vec mojo 48,192 64,512 multibandfilter
```

Les dimensions principales sont :

- mode : `scalar`, `vec` ou `all` ;
- langage : `cpp`, `mojo` ou `all` ;
- sample rate : valeur unique, liste séparée par des virgules ou `all` ;
- taille du buffer : valeur unique, liste séparée par des virgules ou `all` ;
- source : nom du DSP, chemin explicite, plusieurs sources ou `all`.

Les sample rates exprimés en kHz sont normalisés par le framework : une valeur comme `48` identifie
donc `48000 Hz`.

La commande résout d'abord la matrice demandée et génère les sources target pour chaque combinaison de
DSP, langage et mode. Les compilations sont ensuite spécialisées pour le sample rate et la taille de
buffer demandés.

## Génération des sources

La génération utilise toujours le compilateur FAUST construit dans le repository et combine la source
DSP avec l'architecture de benchmark du langage sélectionné.

Pour C++, la relation est conceptuellement :

```text
src/<dsp>.dsp + arch/cpp/bench.cpp
        |
        v
source benchmark C++
```

Pour Mojo, l'architecture réelle est utilisée directement :

```text
src/<dsp>.dsp + ../mojo/bench.mojo
        |
        v
architecture/mojo/<generated>.mojo
```

Les sources Mojo sont générées dans `architecture/mojo` parce que le programme résultant importe des
packages locaux tels que `conf`, `dsp`, `mem`, `meta` et `bench`. La position du fichier fait donc partie
de l'environnement nécessaire à la résolution des packages par le compilateur Mojo.

Le framework ne nécessite plus de symlink de `_bench` vers `architecture/mojo` : les chemins réels sont
résolus directement par le code Python.

## Compilation

Une fois la source target produite, le framework construit un exécutable spécifique à la configuration
demandée.

La compilation C++ utilise le compilateur C++ avec l'optimisation `-O3` et définit au minimum le type
externe, le sample rate, la taille du buffer et les paramètres nécessaires à l'architecture de benchmark.

La compilation Mojo utilise `mojo build` avec une optimisation équivalente et passe les defines
correspondantes à compile time. En particulier, l'architecture reçoit `DFAUST=DType.float32`, tandis que
le DSP contenu dans la source a déjà été généré par FAUST avec `-double`.

Les binaires peuvent être réutilisés lorsque la source correspondante n'a pas changé. Si le fichier
généré est plus récent, si le binaire n'existe pas ou si une recompilation est demandée, le framework
exécute une nouvelle build.

Avant une génération ou une compilation effective, les artifacts précédents associés au même cas sont
supprimés. De cette manière, une erreur de FAUST ou du compilateur target ne peut pas provoquer
l'exécution accidentelle d'une source ou d'un binaire obsolète.

## Architecture de benchmark

Les architectures `bench` ont pour rôle de transformer le DSP généré en un programme mesurable. Elles
n'utilisent pas de driver audio réel : elles initialisent le DSP, allouent directement les buffers et
appellent `compute` dans un environnement contrôlé.

Le comportement général est équivalent pour C++ et Mojo :

```text
initialisation DSP
        |
        v
allocation des buffers
        |
        v
initialisation des entrées
        |
        v
warmup
        |
        v
mesure de compute
        |
        v
checksum des sorties
        |
        +--> rapport texte
        |
        +--> CSV temporaire
```

Le warmup permet d'éviter que les premières exécutions influencent directement la mesure. La phase de
benchmark appelle ensuite `compute` de manière répétée et collecte le temps moyen ainsi que les valeurs
les plus rapides et les plus lentes observées pendant les mesures.

Le checksum des sorties n'est pas utilisé comme mesure de performance ; il sert à rendre le résultat du
calcul observable et à vérifier que les différentes implémentations produisent un résultat cohérent.

## Parallélisme et exécution

Les phases de génération et de build sont indépendantes pour une grande partie de la matrice des cas et
sont donc exécutées en parallèle. L'exécution des benchmarks reste en revanche contrôlée afin d'éviter
que plusieurs programmes mesurés simultanément ne se disputent les mêmes ressources de la machine.

Une erreur dans un DSP individuel n'interrompt pas l'ensemble du batch. Si une génération FAUST ou une
compilation échoue, le cas concerné est marqué comme indisponible et le framework poursuit les autres
cas résolus par la même invocation.

Cette séparation permet par exemple d'exécuter `all` sur une collection de DSP même lorsqu'une seule
source n'est momentanément pas supportée par le backend Mojo.

## Rapports

Chaque benchmark produit deux formes principales de sortie.

Le rapport texte est sauvegardé sous `report/tab` et contient les informations utiles à la lecture
directe d'une exécution individuelle. Le rapport structuré est en revanche accumulé dans le fichier
global :

```text
report/report.csv
```

Le CSV conserve l'identité complète du cas de benchmark, avec des informations telles que le langage,
le DSP, le mode, la configuration, les temps et le throughput. Les fragments produits par les
exécutables sont d'abord écrits dans la zone temporaire puis intégrés au rapport global.

La procédure de merge remplace une mesure précédente uniquement lorsqu'elle appartient à la même
identité de benchmark. Des exécutions appartenant à des DSP, modes ou configurations différents restent
donc simultanément disponibles dans le rapport.

Parmi les principales métriques sont présentes :

- temps moyen par invocation de `compute` ;
- temps par frame ;
- throughput en frames par seconde ;
- throughput en échantillons de sortie par seconde ;
- valeurs fast et slow de la mesure ;
- checksum du résultat.

Pour les DSP sans sorties, pour lesquels le throughput en échantillons de sortie n'est pas significatif,
le framework peut utiliser le throughput en frames par seconde comme référence.

## Plots

La commande :

```sh
bench plot <name>
```

produit un graphique SVG à partir du contenu accumulé dans `report/report.csv`.

Le plot regroupe les résultats par DSP et configuration et normalise le throughput par rapport à la
meilleure valeur du groupe, placée à `100%`. Il devient ainsi possible de comparer directement C++ et
Mojo, ainsi que leurs modes scalar et vec respectifs, sans perdre la séparation entre des cas distincts.

La barre représente la valeur moyenne mesurée ; le throughput absolu est indiqué au-dessus. Les valeurs
fast et slow sont représentées comme extrêmes de la mesure, ce qui rend immédiatement lisible la
variation observée pendant le benchmark.

Pour les DSP possédant au moins une sortie, `out_samp_per_s` est normalement utilisé ; pour les sinks
sans sortie, le plot utilise `frames_per_s`.

## Snapshots

La commande :

```sh
bench snapshot <name>
```

sauvegarde l'état courant des rapports dans un dossier dédié sous `report/snap`.

Le snapshot permet de conserver un ensemble de résultats avant de nouvelles modifications du generator
ou des architectures. Le rapport courant peut ainsi être régénéré ou nettoyé sans perdre les mesures
sélectionnées comme référence.

Les snapshots sont considérés comme des artifacts persistants et ne sont pas supprimés par la commande
de cleanup normale.

## Inspection LLVM et assembly

Le benchmark et l'inspection du code sont volontairement séparés. Les architectures de benchmark
contiennent le warmup, la mesure, le reporting et la logique de batching, éléments utiles à l'exécution
mais indésirables lorsqu'on veut analyser le code généré par le compilateur target.

Pour cette raison, le framework expose :

```sh
bench inspect llvm <mode> <lang> <sources...>
bench inspect asm <mode> <lang> <sources...>
```

La génération utilise `inspect.cpp` pour C++ et `inspect.mojo` pour Mojo. Les deux architectures exposent
un parcours de calcul identifiable, conceptuellement associé au symbole :

```text
inspect_compute
```

L'entry point appelle le `compute` généré en maintenant le code environnant minimal et en introduisant
les barrières nécessaires pour empêcher le compilateur d'éliminer le calcul pendant l'optimisation.

Les artifacts résultants sont sauvegardés respectivement sous :

```text
report/llvm/<lang>/
report/asm/<lang>/
```

L'inspection sert donc à analyser la forme du code produit, la présence effective d'instructions SIMD,
le traitement de l'état et les transformations appliquées par le compilateur target. Ses résultats ne
sont pas utilisés comme mesures de performance.

## Sources déjà transpilées

Le framework permet également de compiler et d'exécuter une source target déjà produite, en évitant la
phase de génération FAUST :

```sh
bench run-transpiled <mode> <lang> <sample-rate> <buffer-size> <path>
```

Ce mode est utile pendant l'analyse du backend lorsqu'on veut modifier manuellement le code transpilé et
comparer son comportement sans le régénérer à chaque exécution.

Le même principe est disponible pour l'inspection :

```sh
bench inspect-transpiled llvm <mode> <lang> <sample-rate> <buffer-size> <path>
bench inspect-transpiled asm <mode> <lang> <sample-rate> <buffer-size> <path>
```

Une source C++ peut être compilée directement depuis son chemin. Une source Mojo externe doit en revanche
être rendue temporairement disponible dans le contexte de `architecture/mojo`, car les imports du
programme dépendent des packages locaux de l'architecture.

Le framework effectue ce staging avec un nom temporaire dédié et le supprime à la fin de l'opération,
évitant ainsi de remplacer ou de supprimer des fichiers appartenant à l'architecture réelle.

## Cleanup

Les sources générées pour le benchmark et l'inspection sont des artifacts temporaires. Pendant une
exécution normale, le framework les suit et les supprime à la fin de la commande, y compris les chemins
temporaires créés pour les sources Mojo déjà transpilées.

La gestion centralisée en Python permet d'effectuer le cleanup même lorsqu'une génération ou une build
individuelle échoue, et d'appliquer la même logique en cas d'interruption de la commande.

La commande :

```sh
bench clean
```

supprime les artifacts régénérables du framework, notamment les binaires, les fichiers temporaires, les
rapports d'exécution, les plots et les sorties d'inspection. Les sources DSP et les architectures ne sont
pas modifiées et les snapshots restent disponibles.

Pendant le développement, il est possible de conserver les sources intermédiaires via l'option de
configuration `BENCH_KEEP_TMP`, utile lorsqu'on veut observer directement le code produit par FAUST avant
la compilation target.

## Workflow essentiel

Une session normale de comparaison peut donc être réduite à quelques commandes :

```sh
pixi shell

bench run all cpp,mojo 48 64 all
bench plot compare_backends
bench snapshot compare_backends
```

Pour analyser le code généré plutôt que le runtime :

```sh
bench inspect llvm vec mojo multibandfilter
bench inspect asm vec cpp multibandfilter
```

Le framework maintient volontairement les responsabilités séparées : FAUST génère le DSP, les
architectures construisent le programme exécutable, les compilateurs target produisent le code machine
et la couche Python coordonne les cas, collecte les mesures et organise les artifacts résultants.
