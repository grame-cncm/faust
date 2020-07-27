/************************************************************
*         Travaux dirigés sur les séries de Volterra
*   Programmation d'un filtre Moog simplifié en FAUST
*
*                           M2R ATIAM, UE TSM
*                   Thomas Hélie et Yann Orlarey
**************************************************************/

// Version utilisant la syntaxe étendue

import("math.lib");	// pour avoir PI et SR la frequence d'échantillonnage
import("oscillator.lib");
import("effect.lib"); 

// Chaine de traitement Volterra composée de trois modules M
// et d'un module de sortie S. A noter  que la deuxième entrée du
// premier module M est à 0

process = C, 0 : M : M : M : M : S;

C = square(freq) + square(freq+delta) : *(level)
	with {
		freq  = hslider("freq carre", 440, 20, 8000, 1);
		delta = hslider("delta", 2, 0, 6, 0.1);
		level = hslider("level",0.5, 0, 1, 0.01);
	};

// Module de traitement M.
// L'expression F1(x) ne sera calculée qu'une
// seule fois car Faust va optimiser le code.

M(x,y) = F1(x), F1(x^3 - F1(x)^3 + y);

// Module de sortie S.
// c'est un module M dont l'entrée du deuxième
// F1 est divisée par 3 et les sorties additionnées

S(x,y) = x + T3*y with { T3 = -1.0/3.0 * checkbox("NL"); };

// Fonction F1 avec définition locale du paramètre v controlé
// par la fréquence de coupure

F1 = *(v/(1.+v)) : + ~ /(1.+v)
	with {
		v = (2*PI/SR)*hslider("freq[unit:Hz]", 700, 1, 20000, 1);
	};
