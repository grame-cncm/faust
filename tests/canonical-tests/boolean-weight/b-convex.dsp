// (1 - g) a + g b, g in {0, 1}
g = button("g");
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip, clip : \(a, b).((1 - g) * a + g * b);
