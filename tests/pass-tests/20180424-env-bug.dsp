// environement should be passed as arguments without triggering an error

foo = environment {
    x = 1;
    y = 2;
};

faa(e) = e;

process = faa(foo).y; // the result should be 2 here



