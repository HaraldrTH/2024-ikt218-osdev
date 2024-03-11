#include "../include/stdlib.h"
//Define video memory contants
#define VIDEO_MEMORY_ADDRESS 0xB8000
#define SCREEN_WIDTH = 80
#define SCREEN_HEIGHT = 80
void print_char(char character, int x, int y, unsigned char color){
    //Calculate the offset into video memory
    unsigned short *video_memory = (unsigned short*)VIDEO_MEMORY_ADDRESS;
    int offset = y*SCREEN_WIDTH+x;

    //Combine character and color attributes into a single byte:
    unsigned short attribute = color << 8;
    unsigned short = value = attribute | character;

    //Write the character and its attributes to video memory:

    video_memory[offset] = value;
}
void printf(int color, char* string){
        volatile char* video = (volatile char*)0xB8000;
        while (*string != 0){
            *video++ = *string++;
            *video++ = color;
        }
}