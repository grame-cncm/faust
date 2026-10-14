// 0.5 * x + 0.5 * x'
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : \(x).(0.5 * x + 0.5 * x');
