// x (a b)
a = hslider("a", 0.5, -2, 2, 0.001);
b = hslider("b", 0.5, -2, 2, 0.001);
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : \(x).(x * (a * b));
