import("stdfaust.lib");

//----------------------------------String Settings---------------------------//
/* Data:
 Music wire ASTM A 228
https://materials.gelsonluz.com/2020/09/astm-a228-properties-chem-mech-rankings.html

A. Stulov,
Physical modelling of the piano string scale,
Applied Acoustics,
Volume 69, Issue 11,
2008,
Pages 977-984,
ISSN 0003-682X,*/

L = 0.77; //[m]
//nPoints=int(Length/h);
nPoints = 77;

k = 1/ma.SR;
//Stability condition
coeff = c^2*k^2 + 4*sigma1*k;
h = sqrt((coeff + sqrt((coeff)^2 + 16*k^2*K^2))/2);

T = 667.1;                  // Tension [N]
radius = 0.5e-03;           // Radius (0.016 gauge) [m]
rho = 7.9*10^3;             // Density [kg/m^3];
Area = ma.PI*radius^2;      // Area of string section
I = (ma.PI*radius^4)/ 4;    // Moment of Inertia
Emod = 200e9;               // Young modulus [Pa]
K = sqrt(Emod*I/rho/Area);  // Stiffness parameter
c = sqrt(T/rho/Area);       // Wave speed
sigma1 = 0.01;              // Frequency dependent damping
sigma0 = 0.05;              // Frequency independent damping

mass = Area*L*rho;

//----------------------------------Equations--------------------------------//
den = 1+sigma0*k;
A = (2*h^4-2*c^2*k^2*h^2-4*sigma1*k*h^2+6*K^2*k^2)/den/h^4;
B = (sigma0*k*h^2-h^2+4*sigma1*k)/den/h^2;
C = (c^2*k^2*h^2+2*sigma1*k*h^2-4*K^2*k^2)/den/h^4;
D = -2*sigma1*k/den/h^2;
E = K^2*k^2/den/h^4;

midCoeff = E,C,A,C,E;
midCoeffDel = 0,D,B,D,0;

r = 2;
t = 1;

scheme(points) = par(i,points,midCoeff,midCoeffDel);

//----------------------------------Controls---------------------------------//
play = button("Play"):ba.impulsify;
inPoint = hslider("Input Point", floor(nPoints/2),0,nPoints-1,0.01);
outPoint = hslider("Output Point",floor(nPoints/2),0,nPoints-1,0.01):si.smoo;

//----------------------------------Force---------------------------------//
/*Hammer stiffness from:
A. Sutlov,
Experimental and theoretical studies of piano hammer,
Proceedings of SMAC 03,
pages 175-178*/

KHammer = 30000;

JCoeff = (k^2/den/rho/Area);

KH = 1000;
mH = 0.9;
omega0SqrH = KH/mH;
sigma0H = 14;
alpha = 2.5;
offset = 0.23;
forceScaling = 0.01;

//----------------------------------Process---------------------------------//
gain = 600;

process = (fd.linInterp1D(nPoints,inPoint):>
    fd.hammer(JCoeff,omega0SqrH,sigma0H,KHammer,alpha,k,offset,play*forceScaling)<:
        fd.linInterp1D(nPoints,inPoint):
            fd.model1D(nPoints,r,t,scheme(nPoints)))~si.bus(nPoints):
                fd.linInterp1DOut(nPoints,outPoint)*gain<:_,_;
