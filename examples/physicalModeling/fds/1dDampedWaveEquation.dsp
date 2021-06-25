import("stdfaust.lib");

declare name "1dDampedWaveEquation";
declare description "1D wave equation with added frequency independent damping.";
declare author "Riccardo Russo";

//--------------------------------Model Settings-----------------------------//
nPoints = 100;

k = 1/ma.SR;
c = 344;
h = c*k;
sigma0 = 5;
lambda = c*k/h;

//----------------------------------Equations--------------------------------//
A = 2*(1-lambda^2)/C1;
B = lambda^2/C1;
C = C2/C1;

C1 = (sigma0*k) + 1;
C2 = (sigma0*k) - 1;

midCoeff = B,A,B;
midCoeffDel = 0,C,0;

r = 1;
t = 1;

scheme(points) = par(i,points,midCoeff,midCoeffDel);

//----------------------------------Controls---------------------------------//
play = button("Play");
inPoint = hslider("Input Point",floor(nPoints/2),0,nPoints-1,0.01);
outPoint = hslider("Output Point",floor(nPoints/2),0,nPoints-1,0.01):si.smoo;

//----------------------------------Force---------------------------------//
forceModel = play:ba.impulsify;

//----------------------------------Process---------------------------------//
process = forceModel<:fd.linInterp1D(nPoints,inPoint):
  fd.model1D(nPoints,r,t,scheme(nPoints)):
  fd.linInterp1DOut(nPoints,outPoint)<:_,_;
