import("stdfaust.lib");

/*
WARNING:
- At the moment, 2D models with more than 30x20 points might crash the c++
  compiler.

- 2D models need to be compiled with the command line compiler, the online
  compiler might not work.
*/

declare name "2dKirchhoffThinPlate";
declare description "Linear plate model with impulse excitation based on Kirchhoff-Love plates theory with added damping.";
declare author "Riccardo Russo";

//--------------------------------Model Settings-----------------------------//
nPointsX = 20;
nPointsY = 10;

k = 1/ma.SR;
K = 20;       //Plate stiffness parameter
s0 = 2;       //Frequency independent damping
s1 = 0.05;    //Frequency dependent damping
c=344;        //Speed of sound in the plate

coeff = c^2*k^2+4*s1*k;
h = sqrt((coeff+sqrt(coeff*coeff+16*K*K*k*k)));

lambda = c*k/h;

//----------------------------------Equations--------------------------------//
mu = K*K*k*k/(h^4);
den = 1+s0*k;
A = 2*(1-10*mu-2*lambda*lambda-4*s1*k*k)/den;
B = (s0*k+4*k*k-1)/den;
C = (8*mu + lambda*lambda + 2*s1*k*k)/den;
D = -2*mu/den;
E = -mu/den;
F = -2*s1*k*k/den;

midCoeff = 0,0,E,0,0,
           0,D,C,D,0,
           E,C,A,C,E,
           0,D,C,D,0,
           0,0,E,0,0;

midCoeffDelay1 = 0,0,0,0,0,
                 0,0,F,0,0,
                 0,F,B,F,0,
                 0,0,F,0,0,
                 0,0,0,0,0;

r = 2;
t = 1;

coefficients = midCoeff,midCoeffDelay1;

scheme(pointsX,pointsY) = par(i, pointsX,
                                par(j,pointsY, coefficients));

//----------------------------------Controls---------------------------------//
inPointX=hslider("Input Point X",floor(nPointsX/2),0,nPointsX-1,0.01);
inPointY=hslider("Input Point Y",floor(nPointsY/2),0,nPointsY-1,0.01);
outPointX=hslider("Output Point X",floor(nPointsX/2),0,nPointsX-1,0.01);
outPointY=hslider("Output Point Y",floor(nPointsY/2),0,nPointsY-1,0.01);
hit = button("Play");

//----------------------------------Force---------------------------------//
forceModel = hit:ba.impulsify;

//----------------------------------Process---------------------------------//
process =
    forceModel<:fd.linInterp2D(nPointsX,nPointsY,inPointX,inPointY):
        fd.model2D(nPointsX,nPointsY,r,t,scheme(nPointsX,nPointsY)):
            fd.linInterp2DOut(nPointsX,nPointsY,outPointX,outPointY);
