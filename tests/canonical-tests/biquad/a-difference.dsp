// the difference equation, y the delayed output
import("stdfaust.lib");
b0 = 0.2; b1 = 0.4; b2 = 0.2; a1 = -0.5; a2 = 0.25;
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : \(x).((\(y).(b0 * x + b1 * x' + b2 * x'' - a1 * y - a2 * y')) ~ _);
