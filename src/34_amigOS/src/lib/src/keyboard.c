#include "../include/keyboard.h"
#include "../include/stdlib.h"
#include "../include/ports.h"




void keyboard_handler(){
    printf("Keyboard");
    char* scancode = '\0';
    char* character = '\0';
    while (1)
    {
        int_to_string(inb(0x60), scancode);
    }
}