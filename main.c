#include <stdio.h>
#include "Headers/FileProcessing.h"
#include "Headers/Bitmap.h"
#include "Headers/Histogram.h"
#include "Headers/GrayScale.h"


int main(int argc, char **argv) {
    FILE *file = open_file("test.bmp");
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

    destroy_bitmapdata(btd);
    close_file(file);
    return 0;
}
