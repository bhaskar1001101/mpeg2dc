#include "test_harness.h"
#include "idct.h"

TEST(idct_8x8) {
    int16_t input[64] = {100, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0};
    idct_8x8(input);
    
    // Check if all values are approximately 12.5 (100/64)
    for (int i = 0; i < 64; i++) {
        ASSERT(abs(input[i] - 13) <= 1, "IDCT output should be approximately 12.5");
    }
}

int main() {
    RUN_TEST(idct_8x8);
    printf("%sAll IDCT tests passed!%s\n", KGRN, KNRM);
    return 0;
}