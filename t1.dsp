// ./build/bin/faust -t 0 -lang ocpp t1.dsp -o t1.cpp -pn t5

import("stdfaust.lib");
//process = +~_;
//process = fi.lowpass(3,1000);

//process = + ~ (_ <: @(3)*2, @(4) : + : *(13));

fi2 = _ <: *(0.1), (mem:*(0.2)) :> _;
smoo1 = *(0.1);
smoo2 = +~*(0.1);
smoo3 = +~(fi2);
smoo4 = fi2 : smoo1;
smoo5 = fi2 : smoo2;
smoo6 = fi2 : smoo3;
smoo7 = *(0.1) : +~*(0.9);
smoo8 = +~*(0.9) : *(0.1);

ex1 = @(1);
ex2 = _ <: par(i, 10, @(i)*(i/100+0.1)) :> _; // un simple fir
ex3 = _ <: par(i, 20, @(i)*(i/100+0.1)) :> _; // un simple fir

m2 = ex2,ex2 : -;
m3 = par(i,6,ex2) :> _; 

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
f3 = fi.notchw(100,1000);
f33 = f3:f3;

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
 
pfir(N,T) = _ <: mfir(N,T) :> _;

pf1 = pfir(10,4);

w4 = mfir(1,4);
w5 = mfir(5,10);
w6 = mfir(1,10);

w7 = + ~ mfir(1,4);
w8 = + ~ mfir(1,8);

ww1 = w4:w7;
ww2 = w7:w4;

ww3 = w7:w8;
ww4 = w8:w7;

ww5 = + ~ mfir(1,2) : mfir(1,3);
ww6 = mfir(1,2) : + ~ mfir(1,2);
ww7 = mfir(1,2) : +~*(0.75); // OK
ww8 = mfir(1,2) : +~(_ <: *(0.75), (mem:*(-0.1)) :> _); // OK
ww9 = mfir(1,2) : +~(_ <: *(0.75), (*(-0.1):mem) :> _); // OK

fir(N) = _ <: par(n,N, @(n):*(1/(1+n^2))):>_;

ww10 = fir(4) : + ~ (_ <: *(0.75), (*(-0.1):mem) :> _); // FAIL
ww11 = fir(2) : + ~ (_ <: *(0.75), (mem:*(-0.1)) :> _); // OK
ww12 = fir(3) : + ~ (_ <: *(0.75), (*(-0.1):mem) :> _); // OK
ww13 = fir(4) : + ~ (_ <: *(0.75), (*(-0.1):mem) :> _); // FAIL
ww14 = fir(4) : + ~ (_ <: *(0.75), (mem:*(-0.1)) :> _); // FAIL
ww15 = fir(4) : + ~ (_ <: *(0.75), mem :> _); // OK
ww16 = fir(4) : + ~ (_ <: _, (mem:*(-0.1)) :> _); // FAIL
ww17 = fir(3) : + ~ (_ <: _, (mem:*(-0.1)) :> _); // OK
ww18 = fir(3) : + ~ (_ <: _, (mem:*(2)) :> _); // OK
ww19 = fir(4) : + ~ (_ <: _, (mem:*(2)) :> _); // OK
ww20 = fir(4) : + ~ (_ <: _, (mem:*(-2)) :> _); // OK

xx1 = fir(6) : + ~ (_ <: _, (mem:*(-0.1)) :> _); // FAIL
xx2 = fir(6) : + ~ (_ <: _, (mem:*(-0.11)) :> _); // OK

// Le probleme semble venir de la factorisation entre la partie FIR et la partie IIR
xx5 = (_<:*(0.13),mem:>_) : + ~ *(0.13); // FAIL
xx6 = (_<:*(0.13),mem:>_) : + ~ *(0.14); // OK

FIR(lc) = _ <: rec(0,lc) :> _ 
with { 
	rec(n,(c,lc)) = (@(n):*(c)), rec(n+1,lc);
	rec(n,c) = @(n):*(c); 
};

// tentatives de simplifier le pb avec f1 pas assez optimisé

db0 = _ <: _,FIR((0.5, 0.7)) :> _; 
db1 = +~(*(0.59)) <: _,FIR((0.5, 0.7)) :> _; 



IIR(lc) = + ~ FIR(lc);

ii1 = IIR((0.01)); // peut utiliser des variables plutôt qu'un tableau
ii2 = IIR((0.01, 0.02)); // peut utiliser des variables plutôt qu'un tableau
ii3 = IIR((0.01, 0.02, 0.03)); // peut utiliser des variables plutôt qu'un tableau
ii4 = ii3:@(int(button("dt"))); // doit utiliser un tableau
ii5 = ii3:@(1); // peut utiliser des variables plutôt qu'un tableau


// test les performances de la permutation IIR/FIR
inv1 = FIR((0.1, -0.1, 0.2)) : IIR((0.3, -0.25, -0.05));
inv2 = IIR((0.3, -0.25, -0.05)) : FIR((0.1, -0.1, 0.2)) ;

minv1 = inv1,inv1,inv1;
minv2 = inv2,inv2,inv2;

m5v1 = par(i,5,inv1);
m5v2 = par(i,5,inv2);

m6v1 = par(i,6,inv1);
m6v2 = par(i,6,inv2);

m8v1 = par(i,8,inv1);
m8v2 = par(i,8,inv2);

//  ./build/bin/faust -t 0 -lang ocpp t1.dsp -fir -ff -sg -irt 5 -fls 5 -pn m8v1 -o m8v1irt5fls5.cpp
//  CXX=clang++-mp-18 fcbenchtool m8v1irt5fls5.cpp cl18 

// ./build/bin/faust -t 0 -lang ocpp t1.dsp -sg -pn m8v2 -o m8v2.cpp     

q1 = + ~ *(0.13);
q4 = q1, q1, q1, q1;

q(n,m) = par(i, n, seq(j, m, q1));

// même quantité de travail
q18 = q(1,8);
q24 = q(2,4);
q42 = q(4,2);
q81 = q(8,1);

q14 = q(1,4);
q22 = q(2,2);
q41 = q(4,1);

q116 = q(1,16);
q28 = q(2,8);
q44 = q(4,4);
q82 = q(8,2);
q161 = q(16,1);

// IIR order 2
qq1 = + ~ (_ <: *(0.13), (mem:*(0.17)) :> _);

qq(n,m) = par(i, n, seq(j, m, qq1));

// même quantité de travail
qq18 = qq(1,8);
qq24 = qq(2,4);
qq42 = qq(4,2);
qq81 = qq(8,1);

qq14 = qq(1,4);
qq22 = qq(2,2);
qq41 = qq(4,1);

qq116 = qq(1,16);
qq28 = qq(2,8);
qq44 = qq(4,4);
qq82 = qq(8,2);
qq161 = qq(16,1);

/*
fcexplorer.py t1.dsp -lang "ocpp" -fir "" -ff "" -pn "qq14 qq22 qq41  qq18 qq24 qq42 qq81  qq116 qq28 qq44 qq82 qq161"
for f in t1_*_qq*.cpp; do fcbenchtool $f; done 
mv t1_*.cpp tcode/
for f in t1_*_qq*; do sudo ./$f; done 
*/



// notch filter
nn1 = library("filters.lib").notchw(100,1000);
nn(n,m) = par(i, n, seq(j, m, nn1));

// même quantité de travail
nn18 = nn(1,8);
nn24 = nn(2,4);
nn42 = nn(4,2);
nn81 = nn(8,1);

nn14 = nn(1,4);
nn22 = nn(2,2);
nn41 = nn(4,1);

nn116 = nn(1,16);
nn28 = nn(2,8);
nn44 = nn(4,4);
nn82 = nn(8,2);
nn161 = nn(16,1);

/*
fcexplorer.py t1.dsp -lang "ocpp" -fir "" -ff "" -fls "3 6" -pn "nn14 nn22 nn41  nn18 nn24 nn42 nn81  nn116 nn28 nn44 nn82 nn161"
fcexplorer.py t1.dsp -lang "ocpp" -fir "" -fls "1 3 6" -pn "nn14 nn22 nn41  nn18 nn24 nn42 nn81  nn116 nn28 nn44 nn82 nn161"
for f in t1_*_nn*.cpp; do fcbenchtool $f; done 
mv t1_*.cpp tcode/
for f in t1_*_nn*; do sudo ./$f; done 
*/

/* 

with masterdev

fcexplorer.py t1.dsp -lang "cpp" -mcd "0 4 8 16" -vec "" -pn "nn14 nn22 nn41  nn18 nn24 nn42 nn81  nn116 nn28 nn44 nn82 nn161"

fcexplorer.py t1.dsp -lang "cpp" -mcd "0 4 8 16" -vec ""  -pn "qq14 qq22 qq41  qq18 qq24 qq42 qq81  qq116 qq28 qq44 qq82 qq161"
*/

// mfir(chans, taps)
mf1_800 = mfir(1,800);
mf2_400 = mfir(2,400);
mf4_200 = mfir(4,200);
mf8_100 = mfir(8,100);
mf8_1200 = mfir(8,1200);

mf1_250 = mfir(1,250);
mf1_500 = mfir(1,500);
mf1_1000 = mfir(1,1000);
mf1_2000 = mfir(1,2000);
mf1_4000 = mfir(1,4000);

// test density

h1 = FIR((1,0,0,1));
h2 = FIR((0,0,0,0,1,0,0,1));
h3 = FIR((0,0,0,0,1,0,0,0,0,1));

// miir: multiple notches in parallel

nw(n) = _ <: par(i, n, library("filters.lib").notchw(d,(i+1)*2*d)) :> _ with { d = 10000/n; };

// même quantité de travail
nw1 = nw(1);
nw2 = nw(2);
nw4 = nw(4);
nw8 = nw(8);
nw16 = nw(16);
nw32 = nw(32);
nw64 = nw(64);
nw128 = nw(128);
nw256 = nw(256);
nw512 = nw(512);
nw1024 = nw(1024);

// fcexplorer.py t1.dsp -lang "ocpp" -fir "" -mdd "10000" -mfs "10000" -pn "nw1 nw2 nw4 nw8 nw16 nw32 nw64 nw128"
// fcexplorer.py t1.dsp -lang "cpp" -mcd "0 4 8 16" -vec ""  -pn "nw1 nw2 nw4 nw8 nw16 nw32 nw64 nw128"
// for f in t1*nw*.cpp; do fcbenchtool $f; done 
