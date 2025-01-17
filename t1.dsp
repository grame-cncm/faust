// ./build/bin/faust -t 0 -lang ocpp t1.dsp -o t1.cpp -pn t5

import("stdfaust.lib");
//process = +~_;
//process = fi.lowpass(3,1000);

//process = + ~ (_ <: @(3)*2, @(4) : + : *(13));

ex1 = @(1);
ex2 = _ <: par(i, 10, @(i)*(i/100+0.1)) :> _; // un simple fir
ex3 = _ <: par(i, 20, @(i)*(i/100+0.1)) :> _; // un simple fir

ex4 = +~ex2;

t1 = _ <: @(1), @(2) :> *(4);  // OK
t2 = _ <: @(5), @(4) :> *(4) : @(2);  // OK
t2a = _ <: @(5), @(4) :> *(4) : @(20);  // Pourquoi ce n'est pas combiné en une seule ligne à retard ?
t2a1 = @(20) <: @(5), @(4) :> *(4);  // celle ci est combinée
t2a2 = _ <: @(5), @(4) :>  @(20) : *(4);  // Pourquoi ce n'est pas combiné en une seule ligne à retard ?
t2a3 = _ <: @(5), @(4) :>  @(2) : *(4);  // Pourquoi ce n'est pas combiné en une seule ligne à retard ?
t2a4 = _ <: @(0), @(1), @(1), @(3) :>  @(1) : *(4);  // Pourquoi ce n'est pas combiné en une seule ligne à retard ?
t2b = _ <: @(5), @(4) :> *(4) : @(2) : /(hslider("toto",1, 1, 4,1));  // OK


t2c = _ <: @(5), @(4) :> @(button("zzz"));  // BUG en mode fir
t2d = _ <: @(5), @(4) :> sqrt : @(button("zzz")); // le sqrt empeche le bug


t3 = _ <: @(5), @(4) :> *(4) : @(2) : abs;  // OK
t4 = (+:t1)~_;  // OK... VERIFIER LA PERFORMANCE (non factorisation de la multiplication par 4)
t4b = (+:t3)~_;  // OK... VERIFIER LES VALEURS
t5 = +~*(0.5);  // OK
t5b = +~*(0.314);  // OK
t6 = t3:t5; // OK
t7 = t5:t3; // OK
t8 = +~t1; // OK
t9 = +~t2; // OK
t10 = +~t3; // OK
t11 = +~(!:1); // OK
t12 = t3:t5; // Maintenant ça marche // NON IIR[ W0_0, abs(4.0f*(IN[0]@5+IN[0]@4)@2), 0.0f, 0.5f ]
t13 = t5:t3; // 

t14 = (+ : t1) ~ @(hslider("delay", 0, 0, 100, 1)); // Segmentation fault // le FIR n'est plus détecté
t15 = t5:t5b;

// test permuttaion IIR et FIR
t16 = t1:t5; // FIR -> IIR
t17 = t5:t1; // IIR -> FIR // une seule ligne à retard !
t18 = t5:t2; // FIR -> IIR

// t2
// Visiting node SigFIR[$,0,0,0,0,0,0,4,4] with max delay 0
// Visiting node SigInput[0] with max delay 7

t19 = +~t2;
// Visiting node SigIIR[nil,SigInput[0],0,0,0,0,0,0,0,4,4] with max delay 0


t20 = t19:@(2);
//Visiting node SigFIR[$,0,0,1] with max delay 0 (retard de 2)
//Visiting node SigIIR[nil,SigInput[0],0,0,0,0,0,0,0,4,4] with max delay 2


// avec de vrais exemples
f1 = fi.lowpass(3,1000);
f2 = fi.lowpass(5,1000);

d0b = _ <: @(100) , @(200);
d0c = +~_;

d1 = (+ : fi.lowpass(3,1000)) ~(@(99):*(0.7));

d0 = (+ : +~*(0.7)) ~ @(1); // fait planter le IIR

k1 = +~(*(g):@(1):*(i)) : *(h) <: *(h), (@(1):*(2*h)), (@(2):*(3*h)) :> _ with { 
	g= cos(i);
	h = sin(i);
	i = ma.SR/ma.PI;
};

r1 = hslider("vol", 0, 0, 1, 0.1) : +~(*(0.0));
r2 = *(r1);
r3 = hslider("vol", 0, 0, 1, 0.1) : seq(i,4, +~(*(0.0)));

zero = button("bidon") <: +~(*(0.0)), _ : -;
r4 = hslider("vol", 0, 0, 1, 0.1) : +~(*(zero));
r4b = hslider("vol", 0, 0, 1, 0.1) : seq(i, 1, +~(*(zero)));

phasor = 440/ma.SR : (+,1:fmod) ~ _;

w0 = + ~ _; // OK en mode FIR
w1 = + ~ (_ <: _, mem :> _);
w2 = mem <: _, mem :> _;
w3 = _,_ <: *(0.1),*(0.2), (mem:*(0.3)), (mem:*(0.4)) :> _,_;

mfir(N,T) = par(n,N,_) <: par(t,T, par(n,N, @(t):*(1/(1+n+t)))) :> par(n,N,_);

w4 = mfir(2,4);
w5 = mfir(5,10);
w6 = mfir(1,10);

w7 = + ~ mfir(1,4);

