#include "test_harness.h"
#include "mpeg2_decoder.h"

TEST(mpeg2_decoder_create) {
    MPEG2Decoder *decoder = mpeg2_decoder_create();
    ASSERT(decoder != NULL, "Decoder should be created");
    ASSERT_EQUAL(0, decoder->current_frame_index, "Current frame index should be 0");
    mpeg2_decoder_destroy(decoder);
}

TEST(mpeg2_decode_frame) {
    MPEG2Decoder *decoder = mpeg2_decoder_create();
    uint8_t data[] = {0x00, 0x00, 0x01, 0xB3}; // Sequence header start code
    Bitstream *bs = bitstream_create(data, sizeof(data));
    Picture *output_frame = NULL;
    MPEG2Error err = mpeg2_decode_frame(decoder, bs, &output_frame);
    ASSERT_EQUAL(MPEG2_OK, err, "Decoding should succeed");
    ASSERT(output_frame == NULL, "No output frame for sequence header");
    bitstream_destroy(bs);
    mpeg2_decoder_destroy(decoder);
}

int main() {
    RUN_TEST(mpeg2_decoder_create);
    RUN_TEST(mpeg2_decode_frame);
    printf("%sAll MPEG-2 decoder tests passed!%s\n", KGRN, KNRM);
    return 0;
}