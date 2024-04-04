#ifndef PROJECT_2_STEGNOGRAPHY_H
#define PROJECT_2_STEGNOGRAPHY_H

#include "stdio.h"
#include "stdlib.h"

extern void encode_char(unsigned char character, unsigned char *hex_array_row, int width);
extern unsigned char decode_char(const unsigned char *hex_array_row, int width);
extern void encode_message(const unsigned char *message, unsigned char **hex_array,size_t message_length, size_t height, size_t width);
extern unsigned char *decode_message(unsigned char **hex_array, size_t height, size_t width);

#endif //PROJECT_2_STEGNOGRAPHY_H
