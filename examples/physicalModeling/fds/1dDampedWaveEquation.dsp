import("stdfaust.lib");
//--------------------------------Model Settings-----------------------------//
nPoints = 100;

k = 1/ma.SR;
c = 344;
h = c*k;
s0 = 500;
lambda = c*k/h;

//----------------------------------Equations--------------------------------//
C1 = 1+(2*s0*k*k/h);
C2 = (2*s0*k*k/h)-1;
A = 2*(1-lambda*lambda)/C1;
B = lambda*lambda/C1;
C = C2/C1;

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
