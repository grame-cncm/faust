// a + c * (b - a)
c = hslider("c", 0.5, 0, 1, 0.001);
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip, clip : \(a, b).(a + c * (b - a));
