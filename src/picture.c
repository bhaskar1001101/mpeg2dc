#include "picture.h"
#include <stdlib.h>
#include <string.h>

Picture* picture_create(int width, int height, int chroma_format) {
    Picture *pic = (Picture*)malloc(sizeof(Picture));
    if (!pic) return NULL;

    pic->width = width;
    pic->height = height;
    pic->y_stride = width;
    pic->uv_stride = width / 2;

    // Allocate memory for Y plane
    pic->Y = (uint8_t*)malloc(width * height);
    if (!pic->Y) {
        free(pic);
        return NULL;
    }

    // Allocate memory for Cb and Cr planes
    int chroma_size = (width / 2) * (height / 2);
    pic->Cb = (uint8_t*)malloc(chroma_size);
    pic->Cr = (uint8_t*)malloc(chroma_size);
    if (!pic->Cb || !pic->Cr) {
        free(pic->Y);
        free(pic->Cb);
        free(pic->Cr);
        free(pic);
        return NULL;
    }

    // Initialize memory
    memset(pic->Y, 0, width * height);
    memset(pic->Cb, 128, chroma_size);
    memset(pic->Cr, 128, chroma_size);

    return pic;
}

void picture_destroy(Picture *pic) {
    if (pic) {
        free(pic->Y);
        free(pic->Cb);
        free(pic->Cr);
        free(pic);
    }
}
