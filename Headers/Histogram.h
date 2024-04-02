#ifndef PROJECT_2_HISTOGRAM_H
#define PROJECT_2_HISTOGRAM_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Bitmap.h"

typedef struct {
    int *red;
    int *green;
    int *blue;
    int split;
} HISTOGRAMTABLE;

extern HISTOGRAMTABLE *create_histogramtable(int split);
extern bool destroy_histogramtable(HISTOGRAMTABLE *ht);
extern bool create_histogram(BITMAPDATA *btd, HISTOGRAMTABLE *ht);
extern void print_histogram_values(HISTOGRAMTABLE *ht);


#endif //PROJECT_2_HISTOGRAM_H
