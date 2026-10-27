// -2147483648 % -1 stops the execution (SIGFPE) although its exact result, 0, is an integer
process = int(hslider("x", 0, -2147483648, 0, 1)) % int(hslider("k", -1, -2, -1, 1));
