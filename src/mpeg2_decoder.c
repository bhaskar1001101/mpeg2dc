#include <stdio.h>
#include "mpeg2_decoder.h"
#include "error_handling.h"
#include "slice.h"
#include "macroblock.h"
#include <stdlib.h>
#include <string.h>

#define MAX_FRAME_SIZE 1024 * 1024 // 1MB, adjust as needed

static MPEG2Error decode_sequence_header(MPEG2Decoder *decoder, Bitstream *bs);
static MPEG2Error decode_group_of_pictures_header(MPEG2Decoder *decoder, Bitstream *bs);
static MPEG2Error decode_picture_header(MPEG2Decoder *decoder, Bitstream *bs);
static MPEG2Error decode_slice(MPEG2Decoder *decoder, Bitstream *bs);

MPEG2Decoder* mpeg2_decoder_create() {
    MPEG2Decoder *decoder = (MPEG2Decoder*)calloc(1, sizeof(MPEG2Decoder));
    if (!decoder) return NULL;

    // Initialize frame buffers
    for (int i = 0; i < 3; i++) {
        decoder->frame_buffer[i] = NULL;
    }
    decoder->current_frame_index = 0;

    return decoder;
}

void mpeg2_decoder_destroy(MPEG2Decoder *decoder) {
    if (decoder) {
        for (int i = 0; i < 3; i++) {
            if (decoder->frame_buffer[i]) {
                picture_destroy(decoder->frame_buffer[i]);
            }
        }
        free(decoder);
    }
}

MPEG2Error mpeg2_decode_frame(MPEG2Decoder *decoder, Bitstream *bs, Picture **output_frame) {
    MPEG2Error err;
    uint32_t start_code;

    *output_frame = NULL;

    while (!bitstream_eof(bs)) {
        start_code = bitstream_get_bits(bs, 32);

        switch (start_code) {
            case 0x000001B3: // Sequence Header
                err = decode_sequence_header(decoder, bs);
                break;

            case 0x000001B8: // Group of Pictures
                err = decode_group_of_pictures_header(decoder, bs);
                break;

            case 0x00000100: // Picture Start
                err = decode_picture_header(decoder, bs);
                break;

            case 0x00000101 ... 0x000001AF: // Slice Start
                err = decode_slice(decoder, bs);
                break;

            case 0x000001B7: // Sequence End
                return MPEG2_OK;

            default:
                fprintf(stderr, "Unknown start code: %08X\n", start_code);
                return MPEG2_ERROR_SYNTAX;
        }

        if (err != MPEG2_OK) {
            return err;
        }
    }

    // If we've decoded a full frame, prepare it for output
    if (decoder->current_picture.picture_coding_type == PICTURE_TYPE_I ||
        decoder->current_picture.picture_coding_type == PICTURE_TYPE_P) {
        *output_frame = decoder->frame_buffer[decoder->current_frame_index];
        decoder->current_frame_index = (decoder->current_frame_index + 1) % 3;
    }

    return MPEG2_OK;
}

static MPEG2Error decode_sequence_header(MPEG2Decoder *decoder, Bitstream *bs) {
    // Parse sequence header fields
    decoder->sequence_header.horizontal_size = bitstream_get_bits(bs, 12);
    decoder->sequence_header.vertical_size = bitstream_get_bits(bs, 12);
    // ... parse other sequence header fields ...

    // Allocate frame buffers if not already done
    if (!decoder->frame_buffer[0]) {
        for (int i = 0; i < 3; i++) {
            decoder->frame_buffer[i] = picture_create(
                decoder->sequence_header.horizontal_size,
                decoder->sequence_header.vertical_size,
                decoder->sequence_header.chroma_format
            );
            if (!decoder->frame_buffer[i]) {
                return MPEG2_ERROR_MEMORY;
            }
        }
    }

    return MPEG2_OK;
}

static MPEG2Error decode_group_of_pictures_header(MPEG2Decoder *decoder, Bitstream *bs) {
    // Parse GOP header fields
    decoder->gop_header.time_code = bitstream_get_bits(bs, 25);
    decoder->gop_header.closed_gop = bitstream_get_bits(bs, 1);
    decoder->gop_header.broken_link = bitstream_get_bits(bs, 1);

    return MPEG2_OK;
}

static MPEG2Error decode_picture_header(MPEG2Decoder *decoder, Bitstream *bs) {
    // Parse picture header fields
    decoder->current_picture.temporal_reference = bitstream_get_bits(bs, 10);
    decoder->current_picture.picture_coding_type = bitstream_get_bits(bs, 3);
    decoder->current_picture.vbv_delay = bitstream_get_bits(bs, 16);
    // ... parse other picture header fields ...

    return MPEG2_OK;
}

static MPEG2Error decode_slice(MPEG2Decoder *decoder, Bitstream *bs) {
    SliceHeader slice_header;
    Macroblock mb;

    // Parse slice header
    slice_header.slice_vertical_position = bitstream_get_bits(bs, 8);
    slice_header.quantizer_scale_code = bitstream_get_bits(bs, 5);

    // Decode macroblocks in the slice
    while (bitstream_get_bits(bs, 23) != 0) { // Check for next slice start code
        // macroblock_decode(bs, &mb, decoder->current_picture.picture_coding_type, decoder->sequence_header.intra_vlc_format);

        // Process the macroblock (perform IDCT, motion compensation, etc.)
        // This is where you'd call your IDCT and motion compensation functions
        // ...

        // Add the decoded macroblock to the current picture
        // ...
    }

    return MPEG2_OK;
}