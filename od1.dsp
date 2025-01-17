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

