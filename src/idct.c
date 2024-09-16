#include "idct.h"
#include <math.h>

#define PI 3.14159265358979323846

void idct_8x8(int16_t *block) {
    double tmp[64];
    double result[64];
    int i, j, u, v;

    // Convert input to double for precision
    for (i = 0; i < 64; i++) {
        tmp[i] = (double)block[i];
    }

    // Perform 2D IDCT
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            double sum = 0.0;
            for (u = 0; u < 8; u++) {
                for (v = 0; v < 8; v++) {
                    double cu = (u == 0) ? 1.0 / sqrt(2) : 1.0;
                    double cv = (v == 0) ? 1.0 / sqrt(2) : 1.0;
                    sum += cu * cv * tmp[u * 8 + v] *
                           cos((2 * i + 1) * u * PI / 16.0) *
                           cos((2 * j + 1) * v * PI / 16.0);
                }
            }
            result[i * 8 + j] = sum / 4.0;
        }
    }

    // Round and convert back to int16_t
    for (i = 0; i < 64; i++) {
        block[i] = (int16_t)round(result[i]);
    }
}
