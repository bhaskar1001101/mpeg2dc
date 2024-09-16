#include "test_harness.h"
#include "bitstream.h"

TEST(bitstream_create) {
    uint8_t data[] = {0xAA, 0xBB, 0xCC};
    Bitstream *bs = bitstream_create(data, 3);
    ASSERT(bs != NULL, "Bitstream should be created");
    ASSERT_EQUAL(3, bs->total_bytes, "Total bytes should be 3");
    bitstream_destroy(bs);
}

TEST(bitstream_get_bits) {
    uint8_t data[] = {0xAA, 0xBB, 0xCC};
    Bitstream *bs = bitstream_create(data, 3);
    ASSERT_EQUAL(0xA, bitstream_get_bits(bs, 4), "Should get first 4 bits");
    ASSERT_EQUAL(0xAB, bitstream_get_bits(bs, 8), "Should get next 8 bits");
    bitstream_destroy(bs);
}

int main() {
    RUN_TEST(bitstream_create);
    RUN_TEST(bitstream_get_bits);
    printf("%sAll bitstream tests passed!%s\n", KGRN, KNRM);
    return 0;
}