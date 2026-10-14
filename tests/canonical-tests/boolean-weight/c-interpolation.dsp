// a + g (b - a)
g = button("g");
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip, clip : \(a, b).(a + g * (b - a));
