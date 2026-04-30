// daptest.cc
// Build (clang++): clang++ -std=c++20 -g -O0 -Wall -Wextra -pedantic daptest.cc -o daptest
// Build (g++):     g++     -std=c++20 -g -O0 -Wall -Wextra -pedantic daptest.cc -o daptest
//
// DAP expectations:
// - Put breakpoint on line marked [BP1] then <leader>bn should stop there.
// - Step over/into should behave predictably with -O0.

#include <stdio.h>
#include <stdint.h>

#include <string>
#include <vector>

struct Point {
    int x;
    int y;
};

static int fib(int n)
{
    if (n <= 1) {
        return n;
    }

    return fib(n - 1) + fib(n - 2);
}

static int sum_vec(std::vector<int> const& v)
{
    int s = 0;

    for (size_t i = 0; i < v.size(); ++i) {
        s += v[i];
    }

    return s;
}

static int mutate(Point* p, int dx, int dy)
{
    p->x += dx;
    p->y += dy;
    return p->x + p->y;
}

int main(void)
{
    printf("start\n");

    int a = 3;
    int b = 4;
    int c = a + b;  // [BP1] breakpoint here

    Point p = {10, 20};
    int m = mutate(&p, 5, -2);

    std::vector<int> v = {1, 2, 3, 4, 5};
    int s = sum_vec(v);

    std::string msg = "hello";
    msg += " world";

    int f = fib(6);

    // Keep variables alive for the debugger
    printf(
        "c=%d m=%d s=%d msg=%s f=%d p=(%d,%d)\n", c, m, s, msg.c_str(), f, p.x, p.y);

    return 0;
}
