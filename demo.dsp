// demo for Peyrusse
t0 = @(1):abs;
t1 = @(2);
t2 = @(4);
t3 = @(8);
t4 = @(16);
t5 = @(32);

tt = @(2):abs;

// faust -lang cpp demo.dsp -pn t1 
// faust -lang cpp demo.dsp -pn t1 -mcd 0

// faust -lang ocpp demo.dsp -pn t1 
// faust -lang ocpp demo.dsp -pn t1 -mcd 0 

fir(N) = _ <: par(i, N, @(i):*(1/(2+i))) :> _;

f0 = fir(1);
f1 = fir(2);
f2 = fir(4);
f3 = fir(8);
f4 = fir(16);
f5 = fir(32);
f6 = fir(64);
f7 = fir(128);
f8 = fir(256);


// faust -lang ocpp demo.dsp -pn f2 
// faust -lang ocpp demo.dsp -pn f2 -mcd 0


iir(N) = + ~ (_ <: par(i, N, @(i):*(1/(2.07+i))) :> _);

i1 = iir(1);
i2 = iir(2);
i3 = iir(3);

mfir(N,T)   = par(n,N,_)
            <: par(t,T, par(n,N, @(t):*(1/(2+n+t))))
            :> par(n,N,_);

t33 = mfir(3,3);
t105 = mfir(10,5);
t510 = mfir(5,10); 
t225 = mfir(2,25); 
t150 = mfir(1,50);

// faust -lang ocpp demo.dsp -pn t33 -mcd 1 -vs 64 -fir  

// ...+ 5*(X@3) + ... + 2*(X@1) + ...
// 5*(X@3) -> 5*FIR[X,0,0,0,1] -> FIR[X,0,0,0,5]
// 2*(X@1) -> FIR[X,0,2]
// ...+ FIR[X,0,0,0,5] + ... + FIR[X,0,2] + ...
// ...+ FIR[X,0,2,0,5] + ...

f1i1 = f1:i1;
f2i1 = f2:i1;
i1f1 = i1:f1;
i1f2 = i1:f2;
i2f2 = i2:f2;

// FIR IIR systematic tests

// fir with alternate signs coefs 
afir(N) = _ <: par(i, N, @(i):*(sign(i)/(2+i))) :> _ 
with {
    sign(i) = i%2 : *(2) : -(1);
};

af1 = afir(1); // OK
af2 = afir(2); // OK
af3 = afir(3); // OK
af4 = afir(4); // OK
af5 = afir(5);

// multiples fir with alternate signs coefs
mafir(N,T)   = par(n,N,_)
            <: par(t,T, par(n,N, @(t):*(sign(t)/(2+n+t))))
            :> par(n,N,_)
with {
    sign(i) = i%2 : *(2) : -(1);
};

maf1 = mafir(1,1); // OK
maf2 = mafir(2,2); // OK
maf3 = mafir(3,3); // OK
maf4 = mafir(4,4); // OK
maf5 = mafir(5,5);


// multiples fir with alternate signs coefs with same input
mafsame(N,T)   = _
            <: par(t,T, par(n,N, @(t):*(sign(t)/(2+n+t))))
            :> par(n,N,_)
with {
    sign(i) = i%2 : *(2) : -(1);
};

mafs1 = mafsame(1,1); // OK
mafs2 = mafsame(2,2); // OK
mafs3 = mafsame(3,3); // OK
mafs4 = mafsame(4,4); // OK
mafs5 = mafsame(5,5); // OK

// iirs with alternate signs coefs
aiir(N) = + ~ (_ <: par(i, N, @(i):*(sign(i)/(2+i))) :> _)
with {
    sign(i) = i%2 : *(2) : -(1);
};

ai1 = aiir(1); // OK
ai2 = aiir(2); // OK
ai3 = aiir(3); // OK
ai4 = aiir(4); // OK
ai5 = aiir(5); // OK


// complex iirs (combine pre and post delay)
ciir(N) = + ~ (@(2) <: par(i, N, @(i):*(sign(i)/(2+i))) :> @(3))
with {
    sign(i) = i%2 : *(2) : -(1);
};

ci1 = ciir(1); // OK
ci2 = ciir(2); // OK
ci3 = ciir(3); // OK
ci4 = ciir(4); // OK
ci5 = ciir(5); // OK


// fake iirs (due to a variable post delay)
fiir(N) = + ~ (@(2) <: par(i, N, @(i):*(sign(i)/(2+i))) :> @(hslider("delay",11,0,100,1)))
with {
    sign(i) = i%2 : *(2) : -(1);
};

fk1 = fiir(1); // OK
fk2 = fiir(2); // OK
fk3 = fiir(3); // OK
fk4 = fiir(4); // OK
fk5 = fiir(5); // OK


// FIR with control rate parameters
cfir(N) = _ <: par(i, N, @(i):*(1/(2+i)):*(hslider("scale %i",0.1,0.1,1,0.1))) :> _;

cf0 = cfir(1); // OK
cf1 = cfir(2); // OK
cf2 = cfir(4); // OK
cf3 = cfir(8); // OK
cf4 = cfir(16); // OK

process = f4;
