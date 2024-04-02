#include "Headers/Bitmap.h"
#include <stdio.h>
#include "stdlib.h"

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
    DWORD **temp = (DWORD **) malloc(sizeof(int *)*BMIH->biHeight);
    if (temp == NULL){
        free(btd);
        return NULL;
    }
    for (int i=0; i<=BMIH->biHeight; i++){
        DWORD *row = (DWORD *)malloc(sizeof(int) * BMIH->biWidth);
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

int get_padding(BITMAPINFOHEADER *BMIH){
    if (BMIH == NULL){
        return -1;
    }
    return ((BMIH->biBitCount * BMIH->biWidth + 31) / 32) * 4 - BMIH->biWidth * (BMIH->biBitCount/8);
}
