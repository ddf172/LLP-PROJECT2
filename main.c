#include <stdio.h>
#include "Headers/FileProcessing.h"
#include "Headers/Bitmap.h"
#include "Headers/Histogram.h"


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
    HISTOGRAMTABLE *ht = create_histogramtable(16);
    if (ht == NULL){
        return 1;
    }
    create_histogram(btd, ht);
    print_histogram_values(ht);
    destroy_histogramtable(ht);

    destroy_bitmapdata(btd);
    closefile(file);
    return 0;
}
