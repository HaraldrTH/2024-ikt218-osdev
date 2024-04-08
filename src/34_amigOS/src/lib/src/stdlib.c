#include "../include/stdlib.h"
#include "../../34_amigOS/include/libc/stdint.h"

static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT= 25;

static int cursor_x = 0;
static int cursor_y = 0;

uint16_t* video = (uint16_t*)0xB8000;

void printf(char* str)
{
    while(*str != '\0')
    {
        putchar(*str);
        *str++;
    }
}

void putchar(char c){

        if(c == '\n')
        {
            cursor_x = 0;
            cursor_y++;
        }
        else
        {
            video[VGA_WIDTH*cursor_y+cursor_x] = (video[VGA_WIDTH*cursor_y+cursor_x] & 0xFF00) | c;
            cursor_x++;
        }

        if (cursor_x >= 80)
        {
            cursor_x = 0;
            cursor_y++;
        }
}