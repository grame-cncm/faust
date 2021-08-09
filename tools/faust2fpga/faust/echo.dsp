stereoEcho = par(i, 1, echo(delay, fback)) 
with {
  echo(d,f) = + ~ (@(d) : *(f));
  delay = 50000 - 1;
  fback = 0.7;
};

process = stereoEcho;
