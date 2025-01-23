#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
#include "error.h"

//Construction
BMP_FILE* bmp_new(size_t height, size_t width) {
    ASSERTM(width > 0 && height > 0, "Message could not be delivered.");

    BMP_FILE *res = (BMP_FILE*) malloc(sizeof(BMP_FILE));
    ASSERT(res != NULL);

    //Ensures black coloring by default
    res->arr = (unsigned int*) calloc(width * height, sizeof(unsigned int));
    ASSERT(res->arr != NULL);

    res->height = height;
    res->width = width;

    return res;
}

BMP_FILE* bmp_fromFile(char *filename) {
    ERRC("Method unimplemented.", 2);
}

//Pixels
static inline int bmp_getIndexFromWH(BMP_FILE *bmp, size_t height, size_t width) {
    return height * bmp->height + width;
}

unsigned int bmp_get(BMP_FILE *bmp, size_t height, size_t width) {
    return bmp->arr[ bmp_getIndexFromWH(bmp, width, height) ];
}

void bmp_set(BMP_FILE *bmp, size_t height, size_t width, unsigned int color) {
    bmp->arr[ bmp_getIndexFromWH(bmp, width, height) ] = color;
}

size_t bmp_gpixelCount(BMP_FILE *bmp) {
    return bmp->width * bmp->height;
}

//Width
size_t bmp_gwidth(BMP_FILE *bmp) {
    return bmp->width;
}

void bmp_swidth(BMP_FILE *bmp, size_t width) {
    bmp->width = width;
}

//Height
size_t bmp_gheight(BMP_FILE *bmp) {
    return bmp->height;
}

void bmp_sheight(BMP_FILE *bmp, size_t height) {
    bmp->height = height;
}

//Size estimate
size_t bmp_constant_size() {
    ERRC("Method unimplemented.", 2);
}

size_t bmp_estimated_size(BMP_FILE *bmp) {
    //Be careful ! Since PIXEL_SIZE is 4, no need to add padding. If the system were to change, please take this into account.
    return PIXEL_SIZE * bmp_gpixelCount(bmp);
}

//File write

//Formats from 0xRRGGBBAA to 0xAARRGGBB
static unsigned int encodeColor(unsigned int val) {
    return ((val & 0x000000FF) << 24) | //Alpha channel is kept on leftmost pos
        ((val & 0xFF000000) >> 8) | //Moves RR to 1 byte on the right
        ((val & 0x00FF0000) >> 8) | //Moves GG to 1 byte on the right
        ((val & 0x0000FF00) >> 8); //Moves BB to 1 byte on the right
}

void bmp_write(BMP_FILE *bmp, char *filename) {
    FILE *fd;
    if (!(fd = fopen(filename, "wb")))
        ERRC("Fichier pas ouvrable.", 1);
    
    //File size
    unsigned int _32;
    unsigned short _16;
    unsigned char _8;

    //PRIMARY HEADER
    //File type
    _16 = 0x4d42;
    fwrite(&_16, sizeof(char), 2, fd);

    //Size (todo)
    _32 = 0;
    fwrite(&_16, sizeof(char), 4, fd);

    //Reserved
    _16 = 0;
    fwrite(&_16, sizeof(char), 2, fd);

    //Reserved
    fwrite(&_16, sizeof(char), 2, fd);

    //Offset
    _32 = 54;
    fwrite(&_32, sizeof(char), 4, fd);

    //INFORMATION HEADER
    //Bitmap header size
    _32 = 40;
    fwrite(&_32, sizeof(char), 4, fd);

    //Width, in pixels
    _32 = bmp_gwidth(bmp);
    fwrite(&_32, sizeof(char), 4, fd);

    //Height, in pixels
    _32 = bmp_gheight(bmp);
    fwrite(&_32, sizeof(char), 4, fd);

    //Planes
    _16 = 1;
    fwrite(&_16, sizeof(char), 2, fd);

    //Bits per pixel
    _16 = PIXEL_SIZE * 8;
    fwrite(&_16, sizeof(char), 2, fd);

    //Compression
    _32 = 0; //No compression
    fwrite(&_32, sizeof(char), 4, fd);

    //SizeImage
    _32 = 0;
    fwrite(&_32, sizeof(char), 4, fd);

    //Horizontal & Vertical resolution
    _32 = 2835;
    fwrite(&_32, sizeof(char), 4, fd);
    fwrite(&_32, sizeof(char), 4, fd);

    //Color constraints
    _32 = 0;
    fwrite(&_32, sizeof(char), 4, fd);
    fwrite(&_32, sizeof(char), 4, fd);

    //Image encoding
    for (int h = (int)bmp_gheight(bmp) - 1; h >= 0; h--) {
        for (int w = (int)bmp_gwidth(bmp) - 1; w >= 0; w--) {
            _32 = encodeColor( bmp_get(bmp, h, w) );
            fwrite(&_32, sizeof(char), 4, fd);
        }
    }

    fclose(fd);
}

//Destruction
void bmp_free(BMP_FILE *bmp) {
    //Free of board
    free(bmp->arr);

    //Free of struct
    free(bmp);
}