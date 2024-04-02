#ifndef PROJECT_2_FILEPROCESSING_H
#define PROJECT_2_FILEPROCESSING_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Bitmap.h"

extern FILE *openfile(char *filename);
extern bool read_file_prop(FILE *file, void *prop, size_t size, size_t number);
extern bool read_file_header(FILE *file, BITMAPFILEHEADER *BMFH);
extern bool read_info_header(FILE *file, BITMAPINFOHEADER *BMIH);
extern bool read_pixels(FILE *file, BITMAPDATA *btd);
extern bool closefile(FILE *file);

#endif //PROJECT_2_FILEPROCESSING_H
