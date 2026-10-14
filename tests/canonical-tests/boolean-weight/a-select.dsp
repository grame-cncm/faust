// select2(g, a, b)
g = button("g");
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip, clip : \(a, b).(select2(g, a, b));
