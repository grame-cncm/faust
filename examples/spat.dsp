//==========================================================
//
// 					    GMEM SPAT
//	implementation du spatialisateur de L. Pottier en faust
//
//==========================================================




//------------------------------------------------------
// Volume d'une voie de sortie
//------------------------------------------------------
// 	i = numero de voie (entre 0 et n-1)
//  n = nombre total de voies
//	a = angle de la source (entre 0 et 1)
// 	d = distance de la source (entre 0 et 1)
//------------------------------------------------------

scaler(i,n,a,d) = sqrt(max(0.0, 1.0 - abs( fmod(a+0.5+float(n-i)/n, 1.0) - 0.5 ) * (n*d))) * (d/2.0+0.5);



//------------------------------------------------------
// spatialisateur a N sorties
//  n = nombre de sorties
//	a = angle de la source (entre 0 et 1)
// 	d = distance de la source (entre 0 et 1)
//
// utilise le constructeur parametrique : par(i,n,E(i))
// qui met en parallele n expressions E(0), E(1), ...E(n-1)
//------------------------------------------------------
smooth(c)	= *(1-c) : +~*(c);
spat(n,a,d)	= _ <: par(i, n, *( scaler(i, n, a, d) : smooth(0.9999) ));




//------------------------------------------------------
// EXEMPLE : une entrée mono spatialisée sur 8 sorties
//------------------------------------------------------

angle 			= hslider("angle",    0.0, 0, 1, 0.01);
distance 		= hslider("distance", 0.5, 0, 1, 0.01);

process 		= vgroup("Spatializer 1x8", spat(8, angle, distance));

 											
