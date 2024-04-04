#include "Headers/Stegnography.h"

void encode_char(unsigned char character, unsigned char *hex_array_row, int width){
    width *= 3;
    if (width < 8 || hex_array_row == NULL){
        printf("Width is less than 8\n");
        return;
    }
    unsigned char binary_character[8];
    for (int i=0; i<8; i++){
        binary_character[i] = (character >> i) & 0x01;
    }


    for (int i=0; i<8; i++){
        if (binary_character[i] == 1){
            hex_array_row[i] = hex_array_row[i] | 0x01;
        } else {
            hex_array_row[i] = hex_array_row[i] & 0xFE;
        }
    }
}

unsigned char decode_char(const unsigned char *hex_array_row, int width){
    width *= 3; // its hex not pixels
    if (width < 8 || hex_array_row == NULL){
        printf("Width is less than 8\n");
        return 0;
    }
    unsigned char character = 0;
    for (int i=0; i<8; i++){
        character = character | ((hex_array_row[i] & 0x01) << i);
    }
    return character;
}

void encode_message(const unsigned char *message, unsigned char **hex_array,size_t message_length, size_t height, size_t width){
    if (message == NULL || hex_array == NULL){
        return;
    }
    if (height < message_length+1){
        printf("Height is less than message length\n");
        return;
    }
    if (width*3 < 8){
        printf("Width is less than 8\n");
        return;
    }
    encode_char((unsigned char)message_length, hex_array[0],(int)width);
    for (int i=0; i<message_length; i++){
        encode_char(message[i], hex_array[i+1],(int)width);
    }
}

unsigned char *decode_message(unsigned char **hex_array, size_t height, size_t width){
    if (hex_array == NULL){
        return NULL;
    }
    if (width*3 < 8){
        printf("Width is less than 8\n");
        return NULL;
    }

    int message_length = decode_char(hex_array[0], (int)width);
    if (message_length < 0 || message_length > height-1){
        printf("Invalid message length\n");
        return NULL;
    }

    unsigned char *message = (unsigned char *) calloc(message_length+1, sizeof(unsigned char));
    if (message == NULL){
        return NULL;
    }
    for (int i=0; i<message_length; i++){
        message[i] = decode_char(hex_array[i+1], (int)width);
    }
    message[message_length] = '\0';
    return message;
}
