#include "motion_comp.h"
#include <string.h>

void motion_comp_frame(Picture *ref, Picture *dest, int mb_x, int mb_y, MotionVector mv) {
    int src_x = mb_x * 16 + mv.x;
    int src_y = mb_y * 16 + mv.y;
    int dst_x = mb_x * 16;
    int dst_y = mb_y * 16;

    // Compensate Y (luma) component
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            int src_idx = (src_y + y) * ref->y_stride + (src_x + x);
            int dst_idx = (dst_y + y) * dest->y_stride + (dst_x + x);
            dest->Y[dst_idx] = ref->Y[src_idx];
        }
    }

    // Compensate Cb and Cr (chroma) components
    src_x /= 2;
    src_y /= 2;
    dst_x /= 2;
    dst_y /= 2;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int src_idx = (src_y + y) * ref->uv_stride + (src_x + x);
            int dst_idx = (dst_y + y) * dest->uv_stride + (dst_x + x);
            dest->Cb[dst_idx] = ref->Cb[src_idx];
            dest->Cr[dst_idx] = ref->Cr[src_idx];
        }
    }
}

void motion_comp_field(Picture *ref_top, Picture *ref_bottom, Picture *dest, int mb_x, int mb_y, MotionVector mv_top, MotionVector mv_bottom) {
    int src_x_top = mb_x * 16 + mv_top.x;
    int src_y_top = mb_y * 16 + mv_top.y;
    int src_x_bottom = mb_x * 16 + mv_bottom.x;
    int src_y_bottom = mb_y * 16 + mv_bottom.y;
    int dst_x = mb_x * 16;
    int dst_y = mb_y * 16;

    // Compensate Y (luma) component
    for (int y = 0; y < 16; y++) {
        Picture *ref = (y % 2 == 0) ? ref_top : ref_bottom;
        MotionVector mv = (y % 2 == 0) ? mv_top : mv_bottom;
        int src_x = (y % 2 == 0) ? src_x_top : src_x_bottom;
        int src_y = (y % 2 == 0) ? src_y_top : src_y_bottom;

        for (int x = 0; x < 16; x++) {
            int src_idx = (src_y + y / 2) * ref->y_stride + (src_x + x);
            int dst_idx = (dst_y + y) * dest->y_stride + (dst_x + x);
            dest->Y[dst_idx] = ref->Y[src_idx];
        }
    }

    // Compensate Cb and Cr (chroma) components
    src_x_top /= 2;
    src_y_top /= 2;
    src_x_bottom /= 2;
    src_y_bottom /= 2;
    dst_x /= 2;
    dst_y /= 2;
    for (int y = 0; y < 8; y++) {
        Picture *ref = (y % 2 == 0) ? ref_top : ref_bottom;
        MotionVector mv = (y % 2 == 0) ? mv_top : mv_bottom;
        int src_x = (y % 2 == 0) ? src_x_top : src_x_bottom;
        int src_y = (y % 2 == 0) ? src_y_top : src_y_bottom;

        for (int x = 0; x < 8; x++) {
            int src_idx = (src_y + y / 2) * ref->uv_stride + (src_x + x);
            int dst_idx = (dst_y + y) * dest->uv_stride + (dst_x + x);
            dest->Cb[dst_idx] = ref->Cb[src_idx];
            dest->Cr[dst_idx] = ref->Cr[src_idx];
        }
    }
}
