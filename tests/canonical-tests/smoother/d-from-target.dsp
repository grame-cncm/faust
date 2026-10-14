// y = x - (1 - c) (x - y'), from the target
c = hslider("c", 0.1, 0.001, 0.5, 0.001);
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : \(x).((\(y).(x - (1 - c) * (x - y))) ~ _);
