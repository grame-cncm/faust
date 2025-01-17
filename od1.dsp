import("music.lib");

// Tests pour ondemand
t1 = button("play") : ondemand(1); // OK
t2 = button("play"),_ : ondemand(@(1)); // OK
t3 = _ <: (button("play1"),_:ondemand(_)), (button("play2"),_:ondemand(_)); // OK
t4 = _ <: (button("play1"),_:ondemand(@(1))), (button("play2"),_:ondemand(@(1))); // OK
t5 = _ <: (button("play1"),_:ondemand(@(1))), (button("play1"),_:ondemand(@(1))); // OK

// gen = +(1)~_;
gen = 1 : +~_;
t6 = gen;
t7 = button("play"):ondemand(gen); // OK
t8 = gen,t7; // NON, pas de distinction entre gen et ondemand (gen)

t9 = button("play"), 1 : ondemand(+~_); // OK en mode fir
t10 = gen, t9;

// t11: Verifier que les deux integrateurs sont bien distingués
// Ca semble correct
t11 = _ <: 	+~_, 
			(button("play"),_ : ondemand(+~_));

// t12: Verifier que les deux integrateurs sont bien distingués
// Ca semble correct là aussi
t12 = 1:t11;

// t13: Verifier que les deux integrateurs sont bien distingués
// Là c'est incorrect, il ne genere qu'un seul circuit d'intégration !
t13 = +(1)~_, (button("play") : ondemand(+(1)~_));

// t14: Verifier que les deux integrateurs sont bien distingués
// OK désomais
t14 = (button("play1") : ondemand(+(1)~_)), (button("play2") : ondemand(+(1)~_));

// Vérifier les imbrications de ondemand
// OK
t15 = button("play1") : ondemand(button("play2") : ondemand(+(1)~_));

// Verifier les FIR
fir(n) = _ <: par(i,n, @(i)/(3+i)) :> _;

t16 = fir(5); // FIR OK
t16b= button("play"),_:ondemand(fir(5));
t17 = +~fir(5); // IIR ?

// bug avec echo_bug.dsp
// mauvais partage d'une expression commune entre deux ondemand

// t18 reproduit bien le problème !
t18 = _ <: 
		ondemand(*(0.5):+~*(0.1))(button("play1")), 
		ondemand(*(0.5):+~*(0.1))(button("play2")); 

C = +(1)~_;
t19 = C, ondemand(C)(button("play1"));

t20 = _ <: +~_, ondemand(+~_)(button("play1")), ondemand(+~_)(button("play2"));
t21 = ondemand(*(0.5):+~*(0.1))(button("play1"));

t22 = ondemand(\(x,y).(x^2+y^2))(button("play1"));
t22b = ondemand(\(x,y).(x^2+y^2))(button("play2"));

// incorrect car le calcul n'est pas dupliqué
t23 = _,_ <: t22,t22b;

f1 = fir(25);
r25 = +~fir(25);
r26 = +~fir(26);
r27 = +~fir(27);

r3 = _ <: r25,r26,r27:>_;

w1 = waveform{1.1,2.2,3.3};
w2 = ondemand(w1)(button("play1"));

// tests avec phasor.dsp qui ne marche pas


phasor_imp(freq, reset, phase) = (select2(prefix(1, clk), +(inc), phase) : decimal) ~ _
with {
    clk = reset>0;
    inc = freq/SR;
};

phas1 = phasor_imp(700, reset, phase), reset, phase
with {  
    reset = waveform {0., 0., 0., 0., 1., 1., 0., 0., 0., 0., 0} : !,_;
    phase = waveform {0.1, 0.8, 0.9, 0.2} : !,_;
};

phas2 = ondemand(phas1)(button("play1")),
		ondemand(phas1)(button("play2"));