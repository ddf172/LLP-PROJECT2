#include <stdio.h>
#include "Headers/FileProcessing.h"
#include "Headers/Bitmap.h"
#include "Headers/Histogram.h"
#include "Headers/GrayScale.h"
#include "Headers/Stegnography.h"
#include "Headers/launcher.h"
#include "string.h"


int main(int argc, char **argv) {
    switch (argc){
        case 2: {
            BITMAPDATA *btd = launch_read_bitmap(argv[1]);
            if (btd == NULL || !launch_validation(btd)) {
                return 1;
            }
            launch_headers_info(btd->BMFH, btd->BMIH);
            launch_histogram(btd);
            printf("Decode steganography? [Y/n]");
            char c;
            scanf("%c", &c);
            if ( c== 'Y' || c == 'y'){
                launch_decode_message(btd);
            }
            break;
        }
        case 3: {
            BITMAPDATA *btd = launch_read_bitmap(argv[1]);
            if (btd == NULL || !launch_validation(btd)) {
                return 1;
            }
            launch_gray_scale(btd, argv[2]);
            break;
        }
        case 4:{
            BITMAPDATA *btd = launch_read_bitmap(argv[1]);
            if (btd == NULL || !launch_validation(btd)) {
                return 1;
            }
            launch_encoding(btd, argv[2], (unsigned char *) argv[3], strlen(argv[3]));
            break;
        }
        default:
            printf("No arguments\n");
            break;
    }
    return 0;
}
