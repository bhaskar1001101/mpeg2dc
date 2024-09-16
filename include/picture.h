#ifndef PICTURE_H
#define PICTURE_H

#include <stdint.h>

#define MAX_MB_WIDTH 120
#define MAX_MB_HEIGHT 68

typedef enum {
    PICTURE_TYPE_I = 1,
    PICTURE_TYPE_P = 2,
    PICTURE_TYPE_B = 3
} PictureType;

typedef struct {
    int horizontal_size;
    int vertical_size;
    int mb_width;
    int mb_height;
    int chroma_format;
    int progressive_sequence;
    int progressive_frame;
    int frame_rate_code;
    int bit_rate;
    int vbv_buffer_size;
} SequenceHeader;

typedef struct {
    int time_code;
    int closed_gop;
    int broken_link;
} GOPHeader;

typedef struct {
    PictureType picture_coding_type;
    int temporal_reference;
    int vbv_delay;
    int full_pel_forward_vector;
    int forward_f_code;
    int full_pel_backward_vector;
    int backward_f_code;
} PictureHeader;

typedef struct {
    uint8_t *Y;
    uint8_t *Cb;
    uint8_t *Cr;
    int width;
    int height;
    int y_stride;
    int uv_stride;
} Picture;

Picture* picture_create(int width, int height, int chroma_format);
void picture_destroy(Picture *pic);

#endif 