
stereoEcho = par(i, 2, echo(delay, fback)) 
with {
  echo(d,f) = + ~ (@(d) : *(f));
  delay = hslider("delay", 5000, 1, 30000, 1) - 1;
  fback = hslider("feedback", 0.7, 0, 0.99, 0.01);
};

process = stereoEcho;
