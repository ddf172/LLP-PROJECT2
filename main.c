#include <stdio.h>
#include "Headers/FileProcessing.h"
#include "Headers/Bitmap.h"


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
    printf("%d\n", BMIH->biWidth);
    BITMAPDATA *btd = create_bitmapdata(BMFH, BMIH);
    if (btd == NULL){
        return 1;
    }
    read_pixels(file, btd);

    for(int i=0; i<=BMIH->biHeight; i++){
        for(int j=0; j<=BMIH->biWidth; j++){
            printf("%x ", btd->pixels[i][j]);
        }
        printf("\n");
    }
    free(BMIH);
    free(BMFH);
    closefile(file);
    return 0;
}
