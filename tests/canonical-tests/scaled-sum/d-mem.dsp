// x * 0.5 + mem(x) * 0.5
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : \(x).(x * 0.5 + mem(x) * 0.5);
