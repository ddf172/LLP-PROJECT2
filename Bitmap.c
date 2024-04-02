#include "Headers/Bitmap.h"

void print_file_header(BITMAPFILEHEADER *BMFH){
    if (BMFH == NULL){
        return;
    }
    printf("BITMAP FILE HEADER\n");
    printf("bfType: ox%x\n", BMFH->bfType);
    printf("bfSize: %d\n", BMFH->bfSize);
    printf("bfReserved1: %d\n", BMFH->bfReserved1);
    printf("bfReserved2: %d\n", BMFH->bfReserved2);
    printf("bfOffBits: %d\n", BMFH->bfOffBits);
}

void print_info_header(BITMAPINFOHEADER *BMIH){
    if (BMIH == NULL){
        return;
    }
    printf("BITMAP INFO HEADER\n");
    printf("biSize: %d\n", BMIH->biSize);
    printf("biWidth: %d\n", BMIH->biWidth);
    printf("biHeight: %d\n", BMIH->biHeight);
    printf("biPlanes: %d\n", BMIH->biPlanes);
    printf("biBitCount: %d\n", BMIH->biBitCount);
    printf("biCompression: %d\n", BMIH->biCompression);
    printf("biSizeImage: %d\n", BMIH->biSizeImage);
    printf("biXPelsPerMeter: %d\n", BMIH->biXPelsPerMeter);
    printf("biYPelsPerMeter: %d\n", BMIH->biYPelsPerMeter);
    printf("biClrUsed: %d\n", BMIH->biClrUsed);
    printf("biClrImportant: %d\n", BMIH->biClrImportant);
}

BITMAPDATA *create_bitmapdata(BITMAPFILEHEADER *BMFH, BITMAPINFOHEADER *BMIH){
    BITMAPDATA *btd = malloc(sizeof(BITMAPDATA));
    if (btd == NULL || BMFH == NULL || BMIH == NULL){
        return NULL;
    }
    btd->BMFH = BMFH;
    btd->BMIH = BMIH;
    PIXEL **temp = (PIXEL **) malloc(sizeof(PIXEL *)*BMIH->biHeight);
    if (temp == NULL){
        free(btd);
        return NULL;
    }
    for (int i=0; i<BMIH->biHeight; i++){
        PIXEL *row = (PIXEL *)malloc(sizeof(PIXEL) * BMIH->biWidth);
        if (row == NULL){
            for (int j=0; j<i; j++){
                free(temp[j]);
            }
            free(temp);
            free(btd);
            return NULL;
        }
        temp[i] = row;
        row = NULL;
    }
    btd->pixels = temp;
    temp = NULL;
    return btd;
}

bool destroy_bitmapdata(BITMAPDATA *btd){
    if (btd == NULL){
        return false;
    }
    if (btd->pixels != NULL) {
        if (btd->BMIH == NULL){
            printf("BMIH is NULL error\n");
            return false;
        }
        for (int i = 0; i < btd->BMIH->biHeight; i++) {
            free(btd->pixels[i]);
        }
        free(btd->pixels);
    }
    if (btd->BMFH != NULL){
        free(btd->BMFH);
    }
    if (btd->BMIH != NULL){
        free(btd->BMIH);
    }
    free(btd);
    return true;
}

int get_padding(BITMAPINFOHEADER *BMIH){
    if (BMIH == NULL){
        return -1;
    }
    return ((BMIH->biBitCount * BMIH->biWidth + 31) / 32) * 4 - BMIH->biWidth * (BMIH->biBitCount/8);
}
