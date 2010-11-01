n = 666;

fact(0)	= 1;
fact(n)	= n*fact(n-1);

ack(0) = 1;
ack(1) = 1;
ack(n) = 1 + ack(n-1) + ack(n-2);

process = ack (15), fact(10);
