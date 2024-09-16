#include <stdio.h>
#include <stdlib.h>
#include "mpeg2_decoder.h"
#include "bitstream.h"
#include "vld.h"
#include "picture.h"
#include "motion_comp.h"
#include "idct.h"

#define MAX_FRAME_SIZE 1024 * 1024 // 1MB, adjust as needed

// Function prototypes
static int read_pes_packet(FILE *file, uint8_t *buffer, int max_size);
static void write_frame_to_yuv(FILE *file, Picture *pic);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.mpg> <output.yuv>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "rb");
    if (!input_file) {
        perror("Failed to open input file");
        return 1;
    }

    FILE *output_file = fopen(argv[2], "wb");
    if (!output_file) {
        perror("Failed to open output file");
        fclose(input_file);
        return 1;
    }

    MPEG2Decoder *decoder = mpeg2_decoder_create();
    if (!decoder) {
        fprintf(stderr, "Failed to create decoder\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    uint8_t *pes_buffer = malloc(MAX_FRAME_SIZE);
    if (!pes_buffer) {
        perror("Failed to allocate PES buffer");
        mpeg2_decoder_destroy(decoder);
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    int pes_size;
    // while ((pes_size = read_pes_packet(input_file, pes_buffer, MAX_FRAME_SIZE)) > 0) {
    //     // Create a bitstream from the PES packet
    //     Bitstream *bs = bitstream_create(pes_buffer, pes_size);
    //     if (!bs) {
    //         fprintf(stderr, "Failed to create bitstream\n");
    //         break;
    //     }

    //     // Decode the frame
    //     Picture *decoded_frame = NULL;
    //     int ret = mpeg2_decode_frame(decoder, bs, &decoded_frame);
    //     if (ret == MPEG2_OK && decoded_frame) {
    //         write_frame_to_yuv(output_file, decoded_frame);
    //     } else {
    //         fprintf(stderr, "Failed to decode frame: %s\n", mpeg2_error_string(ret));
    //     }

    //     bitstream_destroy(bs);
    // }

    free(pes_buffer);
    mpeg2_decoder_destroy(decoder);
    fclose(input_file);
    fclose(output_file);

    printf("Decoding completed.\n");
    return 0;
}

static int read_pes_packet(FILE *file, uint8_t *buffer, int max_size) {
    // Simplified PES packet reading - in practice, you'd need to handle
    // pack headers, system headers, and proper PES packet extraction
    uint32_t start_code;
    if (fread(&start_code, 1, 4, file) != 4) return 0;
    start_code = __builtin_bswap32(start_code); // Convert to little-endian

    if ((start_code & 0xFFFFFF00) != 0x00000100) {
        fprintf(stderr, "Invalid start code: %08X\n", start_code);
        return -1;
    }

    // Read PES packet length
    uint16_t pes_packet_length;
    if (fread(&pes_packet_length, 1, 2, file) != 2) return 0;
    pes_packet_length = __builtin_bswap16(pes_packet_length); // Convert to little-endian

    // Read PES packet data
    int to_read = (pes_packet_length < max_size) ? pes_packet_length : max_size;
    return fread(buffer, 1, to_read, file);
}

static void write_frame_to_yuv(FILE *file, Picture *pic) {
    // Write Y plane
    fwrite(pic->Y, 1, pic->width * pic->height, file);

    // Write Cb plane
    fwrite(pic->Cb, 1, pic->width * pic->height / 4, file);

    // Write Cr plane
    fwrite(pic->Cr, 1, pic->width * pic->height / 4, file);
}