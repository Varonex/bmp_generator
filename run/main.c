#include <stdio.h>
#include <math.h>

#include "bmp.h"

double len(int x, int y) {
    return sqrt(x*x + y*y);
}

int main(int argc, char *argv[]) {
    size_t size = 250;
    size_t txC = size/2, tyC = size/2;
    size_t rad = txC/2;

    BMP_FILE *bmp = bmp_new(size, size);

    unsigned int color = 0xFFFFFFFF;
    for (int h = 0; h < bmp_gheight(bmp); h++) {
        for (int w = 0; w < bmp_gwidth(bmp); w++) {
            int lx = txC - w;
            int ly = tyC - h;

            if (len(lx, ly) < rad)
                bmp_set(bmp, h, w, color);
        }
    }

    bmp_write(bmp, "Test.bmp");

    return 0;
}