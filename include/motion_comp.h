#ifndef MOTION_COMP_H
#define MOTION_COMP_H

#include "picture.h"

typedef struct {
    int16_t x;
    int16_t y;
} MotionVector;

void motion_comp_frame(Picture *ref, Picture *dest, int mb_x, int mb_y, MotionVector mv);
void motion_comp_field(Picture *ref_top, Picture *ref_bottom, Picture *dest, int mb_x, int mb_y, MotionVector mv_top, MotionVector mv_bottom);

#endif 