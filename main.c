#include <stdio.h>
#include "Headers/FileProcessing.h"
#include "Headers/Bitmap.h"
#include "Headers/Histogram.h"
#include "Headers/GrayScale.h"


int main(int argc, char **argv) {
    FILE *file = openfile("test.bmp");
    if (file == NULL){
        return 1;
    }
    BITMAPFILEHEADER *BMFH = malloc(sizeof(BITMAPFILEHEADER));
    if (BMFH == NULL){
        return 1;
    }

    if (!read_file_header(file, BMFH)){
        return 1;
    }
    BITMAPINFOHEADER *BMIH = malloc(sizeof(BITMAPINFOHEADER));
    if (BMIH == NULL){
        return 1;
    }
    if (!read_info_header(file, BMIH)){
        return 1;
    }
    BITMAPDATA *btd = create_bitmapdata(BMFH, BMIH);
    if (btd == NULL){
        return 1;
    }

    read_pixels(file, btd);

    PIXEL **gray_scale = create_gray_scale_pixel_array(btd->pixels, btd->BMIH->biHeight, btd->BMIH->biWidth);
    if (gray_scale == NULL){
        return 1;
    }
    for(int i = 0; i < btd->BMIH->biHeight; i++){
        for(int j = 0; j < btd->BMIH->biWidth; j++){
            printf("%d %d %d | ", gray_scale[i][j].R, gray_scale[i][j].G, gray_scale[i][j].B);
        }
        printf("\n");
    }

    destroy_bitmapdata(btd);
    closefile(file);
    return 0;
}
