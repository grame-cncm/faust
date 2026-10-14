// (1 / a) x
a = hslider("a", 1.5, 1, 2, 0.001);
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : \(x).((1 / a) * x);
