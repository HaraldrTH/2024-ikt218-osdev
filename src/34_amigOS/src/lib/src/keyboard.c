#include "../include/keyboard.h"
#include "../include/stdlib.h"
#include "../include/ports.h"

Dictionary* scancodes;
init_scancodes(){
    insert(scancodes, "30", "A");
}
void keyboard_handler(){
    printf("Keyboard");
    char* scancode = '\0';
    char* character = '\0';
    while (1)
    {
        int input = inb(0x60);
        int_to_string(input, scancode);
        character = get(scancodes, scancode);
        printf(character);
        character = "\0";
    }
}