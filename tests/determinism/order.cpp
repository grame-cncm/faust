// The probe of the argument evaluation order : prints the order in which a
// compiler evaluates the three arguments of one call. A determinism pair must
// join two compilers that answer differently (build-two.sh checks it) : two
// compilers that agree cannot reveal an unsequenced construction.
#include <cstdio>
static int  g(const char* s) { std::printf("%s", s); return 0; }
static void f(int, int, int) {}
int main() { f(g("1"), g("2"), g("3")); std::printf("\n"); return 0; }
