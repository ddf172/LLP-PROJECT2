#include "Headers/launcher.h"

bool launch_validation(BITMAPDATA *btd){
    if (btd == NULL){
        return false;
    }
    if (btd->BMIH->biCompression != 0 || btd->BMIH->biBitCount != 24){
        printf("Unsupported file\n");
        return false;
    }
    return true;
}

BITMAPDATA *launch_read_bitmap(char *filename) {
    FILE *file = open_file(filename);
    if (file == NULL) {
        return NULL;
    }
    BITMAPFILEHEADER *BMFH = malloc(sizeof(BITMAPFILEHEADER));
    if (BMFH == NULL) {
        return NULL;
    }
    if (!read_file_header(file, BMFH)) {
        return NULL;
    }
    BITMAPINFOHEADER *BMIH = malloc(sizeof(BITMAPINFOHEADER));
    if (BMIH == NULL) {
        return NULL;
    }
    if (!read_info_header(file, BMIH)) {
        return NULL;
    }
    BITMAPDATA *btd = create_bitmapdata(BMFH, BMIH);
    if (btd == NULL) {
        return NULL;
    }
    read_pixels(file, btd);
    if (btd->pixels == NULL) {
        return NULL;
    }
    close_file(file);
    return btd;
}


void launch_headers_info(BITMAPFILEHEADER *BMFH, BITMAPINFOHEADER *BMIH) {
    if (BMFH == NULL || BMIH == NULL) {
        return;
    }
    print_file_header(BMFH);
    printf("\n");
    print_info_header(BMIH);
}

void launch_histogram(BITMAPDATA *btd) {
    if (btd==NULL){
        return;
    }
    HISTOGRAMTABLE *ht = create_histogramtable(16);
    if (ht == NULL) {
        return;
    }
    if (!create_histogram(btd, ht)) {
        printf("Error creating histogram\n");
        return;
    }
    print_percentage_histogram_values(ht, (float)(btd->BMIH->biHeight * btd->BMIH->biWidth));
    if (!destroy_histogramtable(ht)) {
        printf("Error destroying histogram\n");
        return;
    }
}

void launch_gray_scale(BITMAPDATA *btd, char* filename) {
    if (btd == NULL){
        return;
    }
    FILE *file = create_file(filename);
    if (file == NULL){
        return;
    }
    PIXEL **gray_scale = create_gray_scale_pixel_array(btd->pixels, btd->BMIH->biHeight, btd->BMIH->biWidth);
    if (gray_scale == NULL){
        return;
    }
    write_to_file(file, btd->BMIH, btd->BMFH, gray_scale);
    destroy_pixel_array(gray_scale, btd->BMIH->biHeight);
    close_file(file);
}

void launch_encoding(BITMAPDATA *btd, char* filename,const unsigned char* message, size_t length) {
    if (btd == NULL || message == NULL || filename == NULL){
        return;
    }
    FILE *file = create_file(filename);
    if (file == NULL){
        return;
    }
    unsigned char **hex_array = create_hex_array_from_pixels(btd->pixels, btd->BMIH->biHeight, btd->BMIH->biWidth);
    if (hex_array == NULL){
        return;
    }
    encode_message(message, hex_array, length,btd->BMIH->biHeight, btd->BMIH->biWidth);
    PIXEL **pixels_array = create_pixel_array_from_hex(hex_array, btd->BMIH->biHeight, btd->BMIH->biWidth);
    write_to_file(file, btd->BMIH, btd->BMFH, pixels_array);
    destroy_hex_array(hex_array, btd->BMIH->biHeight);
    destroy_pixel_array(pixels_array, btd->BMIH->biHeight);
    close_file(file);
}

void launch_decode_message(BITMAPDATA *btd) {
    if (btd == NULL){
        return;
    }
    unsigned char **hex_array = create_hex_array_from_pixels(btd->pixels, btd->BMIH->biHeight, btd->BMIH->biWidth);
    if (hex_array == NULL){
        return;
    }
    unsigned char *message = decode_message(hex_array, btd->BMIH->biHeight, btd->BMIH->biWidth);
    if (message == NULL){
        return;
    }
    printf("Message: %s\n", message);
    destroy_hex_array(hex_array, btd->BMIH->biHeight);
    free(message);
}
