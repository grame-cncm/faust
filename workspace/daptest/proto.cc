#include "stdio.h"
#include "cx/libcx.hh"

proc compute(float** inputs) -> void
{
    for (int i = 0; i < 100; i++) {
        if (i % 10 == 0) {
            printf("\n");
        }
        printf("%.1f ", inputs[i][0]);
    }
    printf("\n");
}

int main() {
    f32* inputs = cast(f32*, malloc(100 * sizeof(f32)));
    memset(inputs, 0, 100 * sizeof(f32));
    compute(&inputs);
    return 0;
}
