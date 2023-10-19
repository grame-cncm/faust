
SR = min(192000.0, max(1.0, fconstant(int fSamplingFreq, <math.h>)));

// test various simplifications
t1 (x) = -x; // OK
t2 (x) = 0 - x; // OK
t3 (x) = -1*x; // OK
t4 (x) = -1*(-1*x); // OK
t5 (x,y) = -y + x; // OK
t6 (x,y) = -1*(x-y); // OK
t7 (x,y) = -1*(-1*(x-y)); // OK
t8 (x,y,z) = -1*(z + -1*(x-y)); // OK
t9 (x,y,z) = -1*z + (x-y); // OK
t10(x,y) = -3*(x-y); // OK
t11(x,y) = 3*(x-y) +(y-x); // pas simplifié !!!!
t11b(x,y) = 3*abs(y-x) + abs(y-x); // OK
t12(x) = -k, -k*x with {k=SR;}; // OK
t13(x) = (0 - (0 - x)); // OK (avec double simplification)
t14(x) = -1*(0 - (0 - x)); // OK (avec double simplification)

t15(x) = -k, -k*x, k*x with {k=SR;}; // OK
t16(x) = -k, -k*x, k with {k=SR;}; // OK
t17(x,y) = -1*(x+y), -1*(x+y); // OK
t18(x) = -1*(x@10), -1*(x@10); // OK
t19(x) = (3*x)@1, (3*x)@2; // Pas optimal, 2 multiplications
t20(x) = (3*x)@1, (4*x)@2; // OK, une seule ligne à retard
t21(x) = (-1*k*x)@1, (-1*x*k)@2 with {k=SR;}; // Optimal une seule ligne à retard

process(x,y,z) = (t1(x), t2(x), t3(x), t4(x), t5(x,y), t6(x,y), 
    t7(x,y), t8(x,y,z), t9(x,y,z), t10(x,y), t11(x,y), t11b(x,y), 
    t12(x), t13(x), t14(x), t15(x),  t16(x), t17(x, y), t18(x), t19(x), t20(x), t21(x));