# Analyse : pourquoi le calcul d'intervalle omet la garde des tables en simple précision

Date de l'analyse : 6 octobre 2026

## Objet

Plusieurs commits successifs cherchent à rendre sûre la génération des accès aux tables (`rdtable`, `rwtable`) en C++ :

| Commit | Contenu |
|---|---|
| `61805e389` | intervalles : les bornes d'une valeur flottante à la précision du programme |
| `080a0ec4e` | gardes de table : un index à quelques ulps d'un bord de sa table garde sa garde |
| `db66db07f` | intervalles : compensation de la libm, et précision double par défaut |
| `52de44cac` | gardes de table : un index alimenté par un flottant garde sa garde |
| `e1e052603` | gardes de table : un index borné par des constantes entières n'a pas besoin de garde (branche `table-guard-clamped-index`) |
| `f6967fcc9` | gardes de table : la garde d'écriture d'une `rwtable` ne dépend plus de celle de lecture (même branche) |
| `7c25f7fd9` | gardes de table : une comparaison tranchée par des bornes flottantes rend un index « alimenté par un flottant » (même branche) |

Malgré ces commits, `TABLE_BUG.dsp` produisait encore un accès hors table en simple précision. La question posée est : **pourquoi le calcul d'intervalle rend-il une information incorrecte, qui fait que la garde `max(0, min(i, size-1))` n'est pas fabriquée quand on génère en flottants ?**

## Résumé

Un intervalle doit être une **enveloppe** : toute valeur que le programme compilé peut produire doit appartenir à `[lo, hi]`. Pour cela, chaque borne doit être arrondie **vers l'extérieur** (`lo` vers −∞, `hi` vers +∞).

La bibliothèque d'intervalles de Faust arrondit au contraire **au plus près**. Depuis `61805e389`, en `-single`, chaque borne d'un intervalle flottant est en plus arrondie au float le plus proche (`programBound`). La borne obtenue n'est donc pas une borne : c'est la valeur que calculerait **un** programme particulier, qui arrondit chaque opération séparément et dans l'ordre écrit. Le compilateur C++ n'exécute pas forcément ce programme-là : clang fusionne par défaut `a*b + c` en une seule instruction FMA, qui n'arrondit qu'une fois.

Dans `TABLE_BUG.dsp`, la bibliothèque prouve `x ≥ 0.5` alors que le programme compilé calcule `x = 0.49999997`. La comparaison `x < 0.5` est déclarée toujours fausse, l'index est typé `[63:63]` et la garde est omise. À l'exécution, l'index vaut 64 dans une table de 64.

Les commits `080a0ec4e`, `52de44cac`, `e1e052603` et `7c25f7fd9` corrigent ce défaut **côté consommateur** (la garde de table), par des règles successives, alors qu'il est **à la source** (l'arrondi des bornes). La correction de fond est l'**arrondi dirigé** des bornes.

## Le programme en cause

```faust
a = hslider("a", 1.30550981, 1.30550981, 2, 0.01);
b = hslider("b", 1.10202765, 1.10202765, 2, 0.01);
c = hslider("c", -0.938707948, -0.938707948, 1, 0.01);
x = a*b + c : hbargraph("x", -2, 6);
process = rdtable(64, (+(1)~_), 63 + (x < 0.5));
```

Les valeurs minimales des sliders sont choisies pour que `a*b + c` tombe au bord de 0.5.

## Ce que fait la bibliothèque d'intervalles

- `Mul` (`compiler/interval/intervalMul.cpp`) calcule les quatre produits des bornes en double, arrondis au plus près.
- `Add` calcule la somme des bornes en double, arrondie au plus près.
- Le constructeur d'`interval` (`compiler/interval/interval_def.hh`) applique `programBound` à chaque borne d'un intervalle flottant (`lsb < 0`). En `-single` (`itv::programPrecision() == 1`, fixé dans `global.cpp` depuis `gFloatSize`), `programBound(b)` vaut `double(float(b))` : l'arrondi **au plus près** en float.
- Le commentaire de `programBound` revendique ce choix : « Round to nearest, not outward : a constant stays a point ».
- `Lt(x, y)` est `Gt(y, x)`, qui renvoie `[0:0]` dès que `x.lo() ≥ y.hi()` (`compiler/interval/intervalGt.cpp`).

## TABLE_BUG.dsp en chiffres

Valeurs des sliders à leur minimum, en float : `a = 1.3055098056793213`, `b = 1.1020276546478271`, `c = -0.9387079477310181`.

| Calcul | x | x < 0.5 | index |
|---|---|---|---|
| Borne basse calculée par la bibliothèque : RN(RN(a·b) + c) | **0.5 exactement** | 0, « prouvé » | 63 |
| Valeur réelle exacte de a·b + c | 0.49999996154 | 1 | 64 |
| Programme compilé par clang -O2 sur arm64 (`fmadd`) | 0.49999997 | 1 | **64** |
| Même programme avec `-ffp-contract=off` | 0.5 | 0 | 63 |

Le produit `a·b` est arrondi au float supérieur, avec une erreur de +3,8e-8 : `RN(a·b) = 1.438707947731018`. Ajouté à `c`, il donne exactement 0.5. La bibliothèque en conclut que `x < 0.5` vaut toujours 0.

La valeur réelle est pourtant sous 0.5, et le programme compilé aussi. Avant ma correction `7c25f7fd9`, faust générait :

```cpp
int iSlow0 = itbl0mydspSIG0[(static_cast<float>(fHbargraph0) < 0.5f) + 63];
```

### Reproduction de l'exécution

L'expression du code généré, isolée :

```cpp
#include <cstdio>
volatile float a = 1.30550981f, b = 1.10202765f, c = -0.938707948f;  // les sliders à leur minimum
int main() {
    float x = a * b + c;              // l'expression du code généré (fHbargraph0)
    int idx = (x < 0.5f) + 63;        // rdtable(64, ..., 63 + (x < 0.5))
    std::printf("x = %.9g  idx = %d\n", x, idx);
}
```

Résultats sur macOS arm64 :

```text
clang -O2 :                      x = 0.49999997  idx = 64
clang -O2 -ffp-contract=off :    x = 0.5         idx = 63
```

L'assembleur de la première version contient `fmadd s0, s0, s1, s2` : clang contracte `a*b + c` dans une même expression (`-ffp-contract=on` par défaut).

## Pourquoi seulement en simple précision

En `-double`, `programBound` laisse les bornes telles quelles. La borne basse reste la valeur calculée en double avec les valeurs décimales des sliders, `0.49999995997 < 0.5`. La comparaison vaut alors `[0:1]` et l'index `[63:64]`. La garde est générée par la règle normale, sans cas particulier :

```text
-double : WARNING : RDTbl read index [63:64] is outside of table size (64)
-single : (avant 7c25f7fd9) index [63:63], pas de garde
```

C'est donc `61805e389` qui a ouvert ce trou en simple précision. Ce commit corrigeait le cas inverse : une borne calculée sur les réels ne voit pas l'arrondi float vers le haut, et un index prouvé sous la taille de la table pouvait l'atteindre en float. Il a pour cela remplacé une estimation (la valeur réelle arrondie en double) par une autre estimation (la valeur d'un programme float particulier). **Aucune des deux n'est une borne : la borne correcte couvre les deux.**

Le défaut n'est pas propre au float. En double aussi les bornes sont arrondies au plus près, et une FMA en double peut aussi les dépasser, mais d'un écart 2^29 fois plus petit, que cet exemple ne déclenche pas.

Il existe aussi un second écart, distinct : en `-double`, les sliders restent des `FAUSTFLOAT`, c'est-à-dire des `float` par défaut. Le float de `1.30550981` vaut `1.3055098056793213`, ce qui est **sous** le minimum déclaré que la bibliothèque prend comme borne basse (`programBound` n'arrondit rien en double).

## Pourquoi les commits suivants ne suffisent pas

Ils corrigent au niveau de la garde de table un défaut qui est dans l'intervalle :

- **`080a0ec4e`** omet la garde seulement si l'index reste à plus de 4 ulps des bords. Il ne voit pas une erreur qui passe par une comparaison : une erreur de 1e-8 sur `x` devient une erreur de 1 sur l'index entier.
- **`52de44cac`** garde tout index alimenté par un flottant, en exemptant les comparaisons (« A comparison is exact (0 or 1) »). La valeur d'une comparaison est exacte, mais pas son intervalle prouvé quand des bornes flottantes la tranchent : c'est exactement le trou de `TABLE_BUG.dsp`. Il ajoute aussi des gardes inutiles, par exemple les 84 gardes doublées de `quantizedChords`.
- **`e1e052603`** retire ces gardes inutiles quand l'index est borné par un `min`/`max` entier : une exception à l'exception.
- **`7c25f7fd9`** bouche le trou des comparaisons tranchées.

Chaque commit ajoute une règle dans `sigPromotion.cpp`, et l'intervalle faux continue d'alimenter les autres usages des intervalles : décision des comparaisons, conversions en entier, simplifications. Je n'ai pas vérifié lesquels de ces usages produisent du code incorrect.

## La correction à la source : l'arrondi dirigé

Après chaque opération, arrondir `lo` vers −∞ et `hi` vers +∞, à la précision du programme (float en `-single`, double en `-double`).

Sur l'exemple, `RD(RD(a·b) + c) = 0.49999988079 < 0.5` (vérifié). `x < 0.5` vaut alors `[0:1]`, l'index `[63:64]`, et la garde vient de l'intervalle, sans règle spéciale.

L'arrondi dirigé couvre les deux façons dont le compilateur peut exécuter `a*b + c` :

- opérations séparées : `RD(RD(ab) + c) ≤ RD(RN(ab) + c) ≤ RN(RN(ab) + c)`, car `RD(ab) ≤ RN(ab)` et `RD` est croissant ;
- FMA : `RD(RD(ab) + c) ≤ RD(ab + c) ≤ RN(ab + c)`.

Le même raisonnement vaut, dans l'autre sens, pour `hi`. Une opération exacte n'élargit rien, puisque `RD = RU` quand le résultat est représentable. Les intervalles ne s'élargissent donc que là où le résultat du programme est réellement incertain.

### Points à trancher

- **Les constantes.** Garder l'arrondi au plus près quand les deux opérandes sont des points, pour qu'une constante reste un point (l'intention de « a constant stays a point »). C'est correct si Faust plie toujours lui-même les constantes et écrit leur valeur dans le code généré, ce que je n'ai pas vérifié.
- **La libm.** La compensation de `db66db07f` (2 ulps) élargit déjà vers l'extérieur ; elle reste.
- **`-ffast-math`.** La réassociation n'est pas couverte par l'arrondi dirigé. Il faut l'exclure explicitement des garanties.
- **Les sliders en `-double` avec `FAUSTFLOAT` float.** Leurs bornes doivent être arrondies vers l'extérieur à la précision float.

### Conséquences pour les commits existants

Avec l'arrondi dirigé, la garde serait de nouveau décidée par l'intervalle seul, comme avant `080a0ec4e`. On pourrait retirer :

- `52de44cac` (règle de l'index alimenté par un flottant) ;
- `e1e052603` (exception des index bornés par des constantes) et le message `-wall` associé ;
- `7c25f7fd9` (exception des comparaisons tranchées).

Le commit `f6967fcc9` reste valable : la garde d'écriture d'une `rwtable` était abandonnée quand l'index de lecture n'avait pas besoin de garde. C'est un bug indépendant, qui existait déjà avant la fusion de la vague B+C (`4180eeb24`).

## Recommandation

1. Implémenter l'arrondi dirigé dans la bibliothèque d'intervalles, avec l'exception des points constants.
2. Arrondir vers l'extérieur les bornes des sliders à la précision de `FAUSTFLOAT`.
3. Revenir à une garde de table décidée par l'intervalle seul, en retirant les règles de `sigPromotion.cpp` listées ci-dessus.
4. Conserver `f6967fcc9`.
5. Ajouter `TABLE_BUG.dsp` aux tests de régression, avec une vérification de la garde générée en `-single` et en `-double`.

## Limites de l'arrondi dirigé

La recommandation est implémentée dans la branche `intervals-directed-rounding`. Avec l'arrondi dirigé, un intervalle contient toutes les valeurs du programme compilé, que le compilateur C++ arrondisse chaque opération séparément ou fusionne `a*b + c` en FMA. Quatre cas restent hors de cette garantie. Le premier est un vrai risque, que la branche réintroduit ; les trois autres sont limités ou théoriques.

### 1. Les NaN

Les intervalles ne décrivent que des nombres : aucune valeur ne peut y être NaN. Plusieurs règles ignorent donc la partie de leur entrée où l'opération n'est pas définie. Par exemple, `Sqrt` intersecte son entrée avec [0, +∞] : `sqrt(x)` avec `x` dans [−1, 1] donne [0, 1], alors que le programme calcule NaN pour `x < 0`. Même chose pour `log` d'un négatif, `0/0`, `asin(2)`, etc.

C'est grave quand un NaN arrive dans un index de table, parce que `int(NaN)` est indéfini en C++ :

- sur x86, la conversion donne INT_MIN, soit une lecture à l'index −2 147 483 648 ;
- sur arm64, elle donne 0, donc pas de plantage.

Sur `rdtable(100, (+(1)~_), int(sqrt(_)))` :

| Compilateur | Code généré |
|---|---|
| branche `intervals-directed-rounding` | `itbl0mydspSIG0[static_cast<int>(std::sqrt(input0[i0]))]` : pas de garde, l'intervalle dit `[0:1]` |
| `master-dev` (`52de44cac`) | `itbl0mydspSIG0[std::max<int>(0, std::min<int>(…))]` : gardé |

**Sur ce point, la branche recule par rapport à `master-dev`.** La règle de `52de44cac` (« un index calculé à partir d'un float garde sa garde ») protégeait ce cas par accident, sans l'avoir prévu. En la retirant, on revient au comportement d'avant `080a0ec4e`.

La bonne correction est de modéliser le NaN dans l'intervalle :

- un indicateur « peut être NaN », mis par `sqrt`, `log`, la division, etc. quand leur entrée sort du domaine de la fonction ;
- `int()` d'un intervalle qui peut être NaN donne tout l'intervalle des `int`, et la garde est décidée par l'intervalle comme le reste.

### 2. La réassociation sous `-ffast-math`

L'intervalle est calculé dans l'ordre où l'expression est écrite. L'arrondi dirigé couvre cet ordre, que les opérations soient arrondies séparément ou fusionnées en FMA. Mais `-ffast-math` autorise le compilateur C++ à réassocier : il peut calculer `a + (b + c)` au lieu de `(a + b) + c`, et les arrondis tombent alors ailleurs. En float :

- `(1e8 − 1e8) + 0.5` donne `0.5` ;
- `1e8 + (−1e8 + 0.5)` donne `0`, parce que 0.5 est absorbé : l'écart entre deux floats autour de 1e8 est 8.

Aucun intervalle calculé dans le premier ordre ne peut garantir le second. `-ffast-math` suppose aussi qu'il n'y a jamais de NaN ni d'infini, ce qui rejoint le point 1.

Ce n'est pas théorique : 13 scripts de `tools/faust2appls` compilent avec `-ffast-math` (ou `-Ofast`). Sous ces options, les garanties des intervalles ne tiennent plus. Il faut au minimum le documenter.

### 3. L'arrondi accumulé d'un accumulateur flottant

Le domaine affine représente un accumulateur comme `x = +(r) ~ _` par une droite : `x(t) ≤ b0 + b1·t`, avec un taux `b1` d'environ `r`. Pour valider cette droite, il vérifie une récurrence sur les coefficients, et cette vérification arrondit à l'échelle de `b0`. Le programme, lui, arrondit à chaque échantillon à l'échelle de `x(t)`, qui grandit. Chaque pas peut ajouter jusqu'à un demi-ulp de `x(t)`, et ces erreurs ne sont pas dans la droite.

En pratique, aucun cas n'a été trouvé où cela compte. L'intervalle utilisé est l'enveloppe de la droite sur l'horizon de 2^31 échantillons, bien au-dessus de ce qu'atteint un accumulateur float, qui se fige vers 2^24 incréments. Et un accumulateur qui indexe une table passe presque toujours par un `fmod`/`frac`, où le taux disparaît. C'est un trou dans le raisonnement, pas un bug observé.

### 4. L'estimation du gain des IIR

Avec l'option `-fir` seulement (désactivée par défaut), Faust reconnaît les filtres IIR, et l'intervalle de leur sortie vaut `gain × max|entrée|`. Le code (`compiler/signals/sighorizon.cpp`) le dit lui-même : c'est une heuristique.

- Le gain utilisé est le pic de la réponse en fréquence, échantillonné sur 10 000 points.
- La borne correcte pour une entrée bornée quelconque est la norme L1 de la réponse impulsionnelle, toujours supérieure ou égale à ce pic, souvent nettement pour un filtre résonant.
- La grille de 10 000 points peut aussi manquer une résonance étroite.

Avec `-fir`, l'intervalle d'un IIR peut donc être trop étroit, indépendamment de tout arrondi. La correction est indiquée dans le commentaire du code : un calcul certifié de cette borne (la méthode WCPG de Volkova, Hilaire et Lauter).

### Ce qu'il reste à faire

1. Modéliser le NaN dans les intervalles, avant de fusionner la branche, puisqu'elle retire une protection qui existait ; ajouter `int(sqrt(_))` à `tests/interval-tests`.
2. Documenter que les garanties des intervalles ne tiennent pas sous `-ffast-math`.
3. Les accumulateurs flottants et le gain des IIR (`-fir`) peuvent attendre.
