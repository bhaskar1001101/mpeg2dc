#include "test_harness.h"
#include "motion_comp.h"

TEST(motion_comp_frame) {
    uint8_t ref[256];
    uint8_t dest[256];
    for (int i = 0; i < 256; i++) {
        ref[i] = i;
    }
    Picture ref_pic = {ref, NULL, NULL, 16, 16, 16, 8};
    Picture dest_pic = {dest, NULL, NULL, 16, 16, 16, 8};
    MotionVector mv = {1, 1};
    
    motion_comp_frame(&ref_pic, &dest_pic, 0, 0, mv);
    
    ASSERT_EQUAL(17, dest[0], "First pixel should be moved by (1,1)");
}

int main() {
    RUN_TEST(motion_comp_frame);
    printf("%sAll motion compensation tests passed!%s\n", KGRN, KNRM);
    return 0;
}