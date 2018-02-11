// Bug Julius 2018-02-11
// Missing interval computation for << and >>
//
// Expected behavior: two delay lines of same size (131072)
// should be allocated

x = nentry("Log2(Delay)",15,5,16,1);
process = @(pow(2.0f, x)), @(1<<int(x));
