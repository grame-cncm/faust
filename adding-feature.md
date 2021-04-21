# Sur l'ajout de fonctionnalités dans les langages

## Avant toute chose

Ajouter une fonctionnalité à un très haut coût de développement, principalement
dû au fait que cette nouvelle fonctionnalité induit une cassure dans les
versions : il y aura le code d'après qui ne sera plus compilable par le langage
d'avant (ce qui peut être encore pire si votre fonctionnalité n'assure pas la
rétrocompatibilité : la cassure s'opère dans les deux sens). À ce sujet, il
peut être utile d'écrire un script de compatibilité. Aussi, la première
question à se poser au moment d'ajouter une fonctionnalité est :

La fonctionnalité que vous êtes sur le point d'ajouter est-elle vraiment
nécessaire ? Autrement dit : est-elle utile uniquement dans un nombre
négligeable de cas ? Est-elle compréhensible seulement par les quelques gourous
qui ont écrit le langage ? Peut-elle être émulée simplement directement dans le
langage (ou dans le compilateur) ? Va-t-elle être difficilement maintenable ?
La base de code n'est-elle pas trop instable pour se permettre d'ajouter une
nouvelle source de bugs potentielle ? Si vous avez hésité à répondre non à une
de ces questions, vous devriez fermer ce fichier et reconsidérer l'ajout d'une
fonctionnalité.

Ceci étant dit, passons aux choses sérieuses.

## Exemple pratique

Le problème considéré ici est l'ajout d'un système d'annotations d'intervalles
de signaux dans le langage Faust, permettant d'indiquer et de tester des
majorants/minorants calculés par le compilateur. Ce langage (comme tous les
DSL) n'est certes pas un très bon exemple pour le cas général, cependant,
certaines techniques devraient être assez similaires.

On se propose d'ajouter deux paires de primitives à Faust :

 * `upB(s)` et `loB(s)`, signaux à une entrée retournant respectivement le
 majorant et le minorant du signal `s` calculé par le compilateur. D'un point
 de vue du treillis des types Faust, il s'agit de constantes, calculable à la
 compilation (bien sûr), flottantes (donc pas booléennes), parallélisables (je
 crois), et ce quelque soit le signal en entrée

 * `isLt(s)` et `isGt(s)`

N.B. Il faudra sans doute ajouter deux autres primitives concernant la
résolution des signaux.

## Lexer/Parser

La première étape est d'étendre l'ensemble des programmes Faust valides pour
qu'ils contiennent (de préférence exactement) les chaînes de caractère
représentant ces primitives, en modifiant la syntaxe (lexing) et la sémantique
(parsing) de Faust. En effet, si l'on demande à Faust de compiler le programme
suivant :

    process = isLt(1);

on obtient l'erreur suivante

    1 : ERROR : undefined symbol : isLt

Pour ce faire, il nous faut modifier les fichiers décrivant le lexer et le
parser, ici écrits en Flex/Bison (pour plus de détails, voir le Dragon Book)

Dans Faust, ces fichiers se trouvent dans `compiler/parser`.

### Lexing

En Bison, la déclaration des tokens se fait dans le parser (faut pas
chercher), ici `faustparser.y`, déclarons donc 4 nouveaux tokens:

    %token ISLT
    %token ISGT
    %token UPB
    %token LOB

Il faut ensuite que ces Tokens soient associés à des chaînes de caractères
Faust, pour cela, modifions le lexer. Le fichier contenant le lexer se trouve
dans `faustlexer.l`. Il suffit d'ajouter (entre les deux `%%`) :
  
    "isLt" return ISLT;
    "isGt" return ISGT;
    "upB"  return UPB;
    "loB"  return LOB;
    
Recompilons le parser et le compilateur (`make parser` et `make` à la racine).
En compilant l'exemple

    process = isLt(1);

on obtient à présent

    1 : ERROR : syntax error

### Parsing

Puisque nous allons ajouter une primitive, celle-ci va logiquement être issue du
non-terminal `primitive`. Puisqu'il s'agit de primitives, nos tokens seront
d'ailleurs terminaux.

Attention : on parle ici de l'implantation d'une nouvelle primitive, pas d'une `xtended`.

Comme ils ont une arité de 1 et 2, il faut définir deux nouvelles boîtes

	| ISLT							{ $$ = boxPrim2(sigIsLt)}
	| ISGT							{ $$ = boxPrim2(sigIsGt)}
	| UPB							{ $$ = boxPrim1(sigUpB)}
	| LOB							{ $$ = boxPrim1(sigLoB)}

le parsing est terminé

## Signaux

Pour pouvoir compiler, il faut à présent définir les 4 signaux nommés précédemment : `sigIsLT, sigIsGt, sigUpB, sigLoB`.
