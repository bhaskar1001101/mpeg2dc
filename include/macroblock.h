#ifndef MACROBLOCK_H
#define MACROBLOCK_H

#include <stdint.h>
#include "bitstream.h"
#include "motion_comp.h"

typedef struct {
    int macroblock_address_increment;
    int macroblock_type;
    int quantizer_scale_code;
    MotionVector mv[2][2];  // [forward/backward][top/bottom]
    int motion_vertical_field_select[2][2];
    int coded_block_pattern;
    int16_t block[12][64];  // Up to 12 8x8 blocks (4Y + 2Cb + 2Cr for 4:2:2, or 4Y + 4Cb + 4Cr for 4:4:4)
} Macroblock;

void macroblock_decode(Bitstream *bs, Macroblock *mb, PictureType pic_type, int intra_vlc_format);

#endif 