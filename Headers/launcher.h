#ifndef PROJECT_2_LAUNCHER_H
#define PROJECT_2_LAUNCHER_H

#include "FileProcessing.h"
#include "Stegnography.h"
#include "Bitmap.h"
#include "Histogram.h"
#include "GrayScale.h"


extern bool launch_validation(BITMAPDATA *btd);
extern BITMAPDATA *launch_read_bitmap(char *filename);
extern void launch_headers_info(BITMAPFILEHEADER *BMFH, BITMAPINFOHEADER *BMIH);
extern void launch_histogram(BITMAPDATA *btd);
extern void launch_gray_scale(BITMAPDATA *btd, char* filename);
extern void launch_encoding(BITMAPDATA *btd, char* filename,const unsigned char* message, size_t length);
extern void launch_decode_message(BITMAPDATA *btd);


#endif //PROJECT_2_LAUNCHER_H
