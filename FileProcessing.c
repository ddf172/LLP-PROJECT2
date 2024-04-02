#include "Headers/FileProcessing.h"
#include "Headers/Bitmap.h"

FILE *openfile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File does not exist");
        return NULL;
    }
    return file;
}

bool read_file_prop(FILE *file, void *prop, size_t size, size_t number){
    if (file == NULL || prop == NULL){
        return false;
    }
    size_t temp = fread(prop, size, number, file);
    if (temp < 1){
        printf("INVALID FILE");
        return false;
    }
    return true;
}

bool read_file_header(FILE *file, BITMAPFILEHEADER *BMFH){
    if (file == NULL || BMFH == NULL){
        return false;
    }
    if (!read_file_prop(file, &BMFH->bfType, sizeof(BMFH->bfType), 1)){ return false;}
    if (!read_file_prop(file, &BMFH->bfSize, sizeof(BMFH->bfSize), 1)){ return false;}
    if (!read_file_prop(file, &BMFH->bfReserved1, sizeof(BMFH->bfReserved1), 1)){ return false;}
    if (!read_file_prop(file, &BMFH->bfReserved2, sizeof(BMFH->bfReserved2), 1)){ return false;}
    if (!read_file_prop(file, &BMFH->bfOffBits, sizeof(BMFH->bfOffBits), 1)){ return false;}
    return true;
}

bool read_info_header(FILE *file, BITMAPINFOHEADER *BMIH){
    if (file == NULL || BMIH == NULL){
        return false;
    }
    if (!read_file_prop(file, &BMIH->biSize, sizeof(BMIH->biSize),1 )){ return false;}
    if (!read_file_prop(file, &BMIH->biWidth, sizeof(BMIH->biWidth),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biHeight, sizeof(BMIH->biHeight),1 )){ return false;}
    if (!read_file_prop(file, &BMIH->biPlanes, sizeof(BMIH->biPlanes),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biBitCount, sizeof(BMIH->biBitCount),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biCompression, sizeof(BMIH->biCompression),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biSizeImage, sizeof(BMIH->biSizeImage),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biXPelsPerMeter, sizeof(BMIH->biXPelsPerMeter),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biYPelsPerMeter, sizeof(BMIH->biYPelsPerMeter),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biClrUsed, sizeof(BMIH->biClrUsed),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biClrImportant, sizeof(BMIH->biClrImportant),1)){ return false;}
    return true;
}

bool read_pixels(FILE *file, BITMAPDATA *btd){
    if (file == NULL || btd == NULL){
        return false;
    }
    int row_size = ((btd->BMIH->biBitCount * btd->BMIH->biWidth + 31) / 32) * 4;
    unsigned char *buffer = malloc(row_size);
    if (buffer == NULL){
        return false;
    }
    fseek(file, btd->BMFH->bfOffBits, SEEK_SET);
    for (int i=0; i<btd->BMIH->biHeight; i++){
        if (fread(buffer, row_size, 1, file) != 1){
            free(buffer);
            return false;
        }
        printf("Buffer: ");
        for (int j = 0; j < row_size; j++) {
            printf("%02x ", buffer[j]);
        }
        printf("\n");

        for (int j=0; j<btd->BMIH->biWidth; j++){
            btd->pixels[i][j].B = buffer[j*3];
            btd->pixels[i][j].G = buffer[j*3+1];
            btd->pixels[i][j].R = buffer[j*3+2];
        }
        fseek(file, get_padding(btd->BMIH), SEEK_CUR);
    }
    free(buffer);
    return true;
}

bool closefile(FILE *file) {
    if (fclose(file) != 0) {
        return false;
    }
    file = NULL;
    return true;
}

