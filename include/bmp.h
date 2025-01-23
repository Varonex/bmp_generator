#pragma once

#include <stdio.h>
#include <stdlib.h>

#define PIXEL_SIZE 4

typedef struct _BMP_FILE{
    size_t width, height;
    unsigned int *arr;

} BMP_FILE;

//Construction
BMP_FILE* bmp_new(size_t height, size_t width);
BMP_FILE* bmp_fromFile(char *filename);

//Pixels
unsigned int bmp_get(BMP_FILE *bmp, size_t height, size_t width);
void bmp_set(BMP_FILE *bmp, size_t height, size_t width, unsigned int color);

size_t bmp_gpixelCount(BMP_FILE *bmp);

//Width
size_t bmp_gwidth(BMP_FILE *bmp);
void bmp_swidth(BMP_FILE *bmp, size_t width);

//Height
size_t bmp_gheight(BMP_FILE *bmp);
void bmp_sheight(BMP_FILE *bmp, size_t height);

//Size estimate
size_t bmp_constant_size();
size_t bmp_estimated_size(BMP_FILE *bmp);

//File write
void bmp_write(BMP_FILE *bmp, char *filename);

//Destruction
void bmp_free(BMP_FILE *bmp);