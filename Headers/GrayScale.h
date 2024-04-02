#ifndef PROJECT_2_GRAYSCALE_H
#define PROJECT_2_GRAYSCALE_H
#include "Bitmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

extern int calculate_gray(int r,int g,int b);
extern PIXEL **create_gray_scale_pixel_array(PIXEL **pixels, size_t height, size_t width);



#endif //PROJECT_2_GRAYSCALE_H
