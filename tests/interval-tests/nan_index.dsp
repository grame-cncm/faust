// NaN : a function outside its domain, 0/0, fmod(x, 0). int(NaN) is undefined (x86 :
// INT_MIN) : each index keeps its guard, even clamped to the table.
y = hslider("y", 0.5, 0, 1, 0.01);  // reaches 0
z = hslider("z", 0.5, 0, 1, 0.01);  // reaches 0
t = rdtable(100, (+(1)~_));
clamp(v) = max(0, min(99, v));
process(x) = t(int(sqrt(x))), t(int(clamp(log(x)))), t(int(clamp(acos(2 * x)))),
             t(int(clamp(pow(x, 0.5)))), t(int(clamp(y / z))), t(int(clamp(fmod(x, z))));
