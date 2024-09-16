#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <stdint.h>
#include <stdbool.h>

typedef struct Bitstream {
    uint8_t *data;
    int bit_pos;
    int byte_pos;
    int total_bytes;
} Bitstream;

Bitstream* bitstream_create(uint8_t *data, int length);
void bitstream_destroy(Bitstream *bs);
uint32_t bitstream_get_bits(Bitstream *bs, int n);
void bitstream_align_byte(Bitstream *bs);
bool bitstream_eof(Bitstream *bs);

#endif 