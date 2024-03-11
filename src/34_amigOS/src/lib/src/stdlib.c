#include "../include/stdlib.h"

//Prints to top of screen
void printf(int color, char* string){
        volatile char* video = (volatile char*)0xB8000;
        while (*string != 0){
            *video++ = *string++;
            *video++ = color;
        }
}