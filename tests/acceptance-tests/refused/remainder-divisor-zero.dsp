// an integer remainder by a slider that may be 0 : the execution would stop (SIGFPE)
process = 10 % int(hslider("e", 1, 0, 10, 1));
