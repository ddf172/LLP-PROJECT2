#include <stdio.h>
#include "Headers/FileProcessing.h"
#include "Headers/Bitmap.h"
#include "Headers/Histogram.h"
#include "Headers/GrayScale.h"
#include "Headers/Stegnography.h"
#include "Headers/launcher.h"


int main(int argc, char **argv) {
    BITMAPDATA *btd = launch_read_bitmap("tux.bmp");
    launch_encoding(btd, "encoded.bmp", (unsigned char*)"Hello World", 11);
    destroy_bitmapdata(btd);
    btd = launch_read_bitmap("encoded.bmp");
    launch_decode_message(btd);
    launch_gray_scale(btd, "gray.bmp");
    destroy_bitmapdata(btd);
    return 0;
}
