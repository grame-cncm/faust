// BUG 2010 05 03 in Faust 0.9.22
//----------------------------------------------------------
// Faustpower definition not generated when power is used in 
// initialisation classes (that is in table contents).

mytbl(r) 	= rdtable(128, (1 : +~_ : _^2), r);
process(x) 	= mytbl(int(abs(x)*127)) : _^2;



