// a function named as the hyperbolic tangent, declared in another header : a foreign
// function, unbounded, and no line can hold its delay
h = ffunction(float tanhf|tanh|tanhl (float), "mymath.h", "");
process = @(int(50 + 50 * h(_)));
