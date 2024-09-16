#ifndef MPEG2_DECODER_H
#define MPEG2_DECODER_H

#include <stdint.h>
#include <stdbool.h>

#include "bitstream.h"
#include "vld.h"
#include "picture.h"
#include "motion_comp.h"
#include "idct.h"
#include "error_handling.h"

typedef struct MPEG2Decoder {
    SequenceHeader sequence_header;
    GOPHeader gop_header;
    PictureHeader current_picture;
    Picture *frame_buffer[3];  // For I, P, and B frames
    int current_frame_index;
} MPEG2Decoder;

MPEG2Decoder* mpeg2_decoder_create();
void mpeg2_decoder_destroy(MPEG2Decoder *decoder);
MPEG2Error mpeg2_decode_frame(MPEG2Decoder *decoder, Bitstream *bs, Picture **output_frame);

#endif 