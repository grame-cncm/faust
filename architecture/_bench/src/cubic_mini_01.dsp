declare name "cubic_mini_01";

drive = hslider("drive", 0.5, 0.0, 2.0, 0.01);

cubic(x) = x - drive * x * x * x;

process = _ : cubic <: _,_;
