// twgo.dsp - test the transformer-normalized, one-multiply, 
// digital waveguide resonator with an impulse. 
// Code from Julius Orion Smith
// http://ccrma.stanford.edu/~jos/pasp/Faust_Implementation.html

import("music.lib"); // PI, SR 

fr = hslider("freq",440,0,10000,1); 

G = 1; 
C = cos(2*PI*fr/SR); 

wgo(x) = (*(G)+x, _ <: _, ((+:*(C)) <: _,_), _ : +,-) ~ cross
	 with { cross = _,_ <: !,_,_,!; }; 

process = 1-1' : wgo;

