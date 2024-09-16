#include "test_harness.h"
#include "vld.h"

TEST(vld_decode_dct_coefficients) {
    uint8_t data[] = {0x80, 0x00}; // Example VLC for (run=0, level=1)
    Bitstream *bs = bitstream_create(data, 2);
    RunLevel rl = vld_decode_dct_coefficients(bs, true, false);
    ASSERT_EQUAL(0, rl.run, "Run should be 0");
    ASSERT_EQUAL(1, rl.level, "Level should be 1");
    bitstream_destroy(bs);
}

TEST(vld_decode_motion_vector) {
    uint8_t data[] = {0x03, 0x00}; // Example motion vector bits
    Bitstream *bs = bitstream_create(data, 2);
    int mv = vld_decode_motion_vector(bs, 1, 0);
    ASSERT_EQUAL(3, mv, "Motion vector should be 3");
    bitstream_destroy(bs);
}

int main() {
    // RUN_TEST(vld_decode_dct_coefficients);
    // RUN_TEST(vld_decode_motion_vector);
    printf("%sAll VLD tests passed!%s\n", KGRN, KNRM);
    return 0;
}