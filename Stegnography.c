#include "Headers/Stegnography.h"

unsigned char *encode_char(unsigned char character, unsigned char *hex_array){

    unsigned char binary_character[8];
    for (int i=0; i<8; i++){
        binary_character[i] = (character >> i);
    }
    for (int i = 0; i < 8; i++) {
        printf("%d ", binary_character[i]);
    }
    printf("\n");

//    for (int i=0; i<8; i++){
//        hex_array[i] = hex_array[i] | ((character >> i) & 0x01);
//    }
    return hex_array;
}
