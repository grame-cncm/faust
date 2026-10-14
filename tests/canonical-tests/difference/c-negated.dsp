// 0 - (b - a)
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip, clip : \(a, b).(0 - (b - a));
