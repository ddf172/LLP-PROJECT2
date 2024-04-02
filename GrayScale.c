#include "Headers/GrayScale.h"

int calculate_gray(int r,int g,int b){
    return (r + g + b) / 3;
}

PIXEL **create_gray_scale_pixel_array(PIXEL **pixels, size_t height, size_t width){
    PIXEL **temp = create_pixel_array(height, width);
    if (temp == NULL || pixels == NULL){
        return NULL;
    }
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            int gray = calculate_gray(pixels[i][j].R, pixels[i][j].G, pixels[i][j].B);
            temp[i][j].R = gray;
            temp[i][j].G = gray;
            temp[i][j].B = gray;
        }
    }
    return temp;
}