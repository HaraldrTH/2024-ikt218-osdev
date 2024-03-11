#include "../include/stdlib.h"
//Define video memory contants
#define VIDEO_MEMORY_ADDRESS 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
// Function to print a character at a specific position on the screen
void print_char(char character, int x, int y, unsigned char color){
    //Calculate the offset into video memory
    unsigned short *video_memory = (unsigned short*)VIDEO_MEMORY_ADDRESS;
    int offset = y*SCREEN_WIDTH+x;

    //Combine character and color attributes into a single byte:
    unsigned short attribute = color << 8;
    unsigned short value = attribute | character;

    //Write the character and its attributes to video memory:

    video_memory[offset] = value;
}
// Function to clear the screen
void clear_screen(unsigned char color) {
    // Fill the entire screen with spaces and the given color
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            print_char(' ', x, y, color);
        }
    }
}
// Function to print a string starting from the current cursor position
void print_string(const char *string, unsigned char color) {
    // Initialize variables to track current position
    static int x = 0;
    static int y = 0;

    // Loop through characters in the string
    for (int i = 0; string[i] != '\0'; i++) {
        // Print the character
        print_char(string[i], x, y, color);

        // Move cursor to the next position
        x++;
        if (x >= SCREEN_WIDTH) {
            x = 0;
            y++;
        }
        if (y >= SCREEN_HEIGHT) {
            y = 0;
        }
    }
}
//Prints to top of screen
void printf(int color, char* string){
        volatile char* video = (volatile char*)0xB8000;
        while (*string != 0){
            *video++ = *string++;
            *video++ = color;
        }
}