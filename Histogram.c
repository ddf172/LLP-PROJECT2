#include "Headers/Histogram.h"

HISTOGRAMTABLE *create_histogramtable(int split) {
    HISTOGRAMTABLE *ht = malloc(sizeof(HISTOGRAMTABLE));
    if (ht == NULL) {
        return NULL;
    }
    if (split < 1 || split > 256 || 256 % split != 0) {
        free(ht);
        return NULL;
    }
    ht->split = split;
    int *temp = (int *) calloc(split, sizeof(int));
    if (temp == NULL) {
        free(ht);
        return NULL;
    }
    ht->red = temp;
    temp = (int *) calloc(split, sizeof(int));
    if (temp == NULL) {
        free(ht->red);
        free(ht);
        return NULL;
    }
    ht->green = temp;
    temp = (int *) calloc(split, sizeof(int));
    if (temp == NULL) {
        free(ht->green);
        free(ht->red);
        free(ht);
        return NULL;
    }
    ht->blue = temp;
    temp = NULL;
    return ht;
}

bool destroy_histogramtable(HISTOGRAMTABLE *ht) {
    if (ht == NULL) {
        printf("ht is NULL error\n");
        return false;
    }
    if (ht->red != NULL) {
        free(ht->red);
    }
    if (ht->green != NULL) {
        free(ht->green);
    }
    if (ht->blue != NULL) {
        free(ht->blue);
    }
    free(ht);
    return true;
}

bool create_histogram(BITMAPDATA *btd, HISTOGRAMTABLE *ht) {
    if (btd == NULL || btd->pixels == NULL || ht == NULL) {
        return false;
    }
    for (int i = 0; i < btd->BMIH->biHeight; i++) {
        for (int j = 0; j < btd->BMIH->biWidth; j++) {
            int red = btd->pixels[i][j].R;
            int green = btd->pixels[i][j].G;
            int blue = btd->pixels[i][j].B;
            ht->red[red / ht->split]++;
            ht->green[green / ht->split]++;
            ht->blue[blue / ht->split]++;
        }
    }
    return true;
}

void print_histogram_values(HISTOGRAMTABLE *ht) {
    if (ht == NULL) {
        return;
    }
    for (int i = 0; i < ht->split; i++) {
        printf("Red %d: %d\n", i, ht->red[i]);
        printf("Green %d: %d\n", i, ht->green[i]);
        printf("Blue %d: %d\n", i, ht->blue[i]);
    }
}

void print_percentage_histogram_values(HISTOGRAMTABLE *ht, float total_pixels) {
    if (ht == NULL) {
        return;
    }
    printf("Blue:\n");
    for (int i = 0; i < ht->split; i++) {
        printf("    %d-%d : %.2f%%\n", i*ht->split, (i+1)*ht->split-1, (float) ht->blue[i] / total_pixels *100);
    }
    printf("Green:\n");
    for (int i = 0; i < ht->split; i++) {
        printf("    %d-%d : %.2f%%\n", i*ht->split, (i+1)*ht->split-1, (float) ht->green[i] / total_pixels * 100);
    }
    printf("Red:\n");
    for (int i = 0; i < ht->split; i++) {
        printf("    %d-%d : %.2f%%\n", i*ht->split, (i+1)*ht->split-1, (float) ht->red[i] / total_pixels * 100);
    }
}