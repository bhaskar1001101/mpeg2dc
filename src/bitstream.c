#include "bitstream.h"
#include <stdlib.h>
#include <string.h>

Bitstream* bitstream_create(uint8_t *data, int length) {
    Bitstream *bs = (Bitstream*)malloc(sizeof(Bitstream));
    if (!bs) return NULL;

    bs->data = (uint8_t*)malloc(length);
    if (!bs->data) {
        free(bs);
        return NULL;
    }

    memcpy(bs->data, data, length);
    bs->bit_pos = 0;
    bs->byte_pos = 0;
    bs->total_bytes = length;

    return bs;
}

void bitstream_destroy(Bitstream *bs) {
    if (bs) {
        free(bs->data);
        free(bs);
    }
}

uint32_t bitstream_get_bits(Bitstream *bs, int n) {
    uint32_t val = 0;
    for (int i = 0; i < n; i++) {
        val <<= 1;
        val |= (bs->data[bs->byte_pos] >> (7 - bs->bit_pos)) & 1;
        bs->bit_pos++;
        if (bs->bit_pos == 8) {
            bs->bit_pos = 0;
            bs->byte_pos++;
        }
    }
    return val;
}

void bitstream_align_byte(Bitstream *bs) {
    if (bs->bit_pos > 0) {
        bs->bit_pos = 0;
        bs->byte_pos++;
    }
}

bool bitstream_eof(Bitstream *bs) {
    return bs->byte_pos >= bs->total_bytes;
}