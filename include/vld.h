#ifndef VLD_H
#define VLD_H

#include "bitstream.h"

typedef struct {
    int16_t run;
    int16_t level;
} RunLevel;

RunLevel vld_decode_dct_coefficients(Bitstream *bs, bool intra, bool mpeg1);
int vld_decode_motion_vector(Bitstream *bs, int f_code, int prev_mv);

#endif 