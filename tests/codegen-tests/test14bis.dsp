// bug dans version 0.9.9.3-bis 
// (ne se produit pas avec les version 0.9.9.2 et 0.9.9.3)
// le compilateur se plaint de ne pas avoir de type associé 
// à la deuxième sortie qui est pourtant inutilisée
process = (+ <: _, _)~ _ : _,!;