#ifndef SLICE_H
#define SLICE_H

#include "bitstream.h"
#include "macroblock.h"

typedef struct {
    int slice_vertical_position;
    int quantizer_scale_code;
    int intra_slice_flag;
} SliceHeader;

void slice_decode(Bitstream *bs, SliceHeader *header, Macroblock *mb, int mb_width);

#endif 