#include "../include/keyboard.h"
#include "../include/stdlib.h"
#include "../include/ports.h"

Dictionary* scancodes;
init_scancodes(){
    insert(scancodes, "30", "A");
}
void keyboard_handler(){
    char* scancode = '\0';
    char* character = '\0';
    int input = inb(0x60);
    int_to_string(input, scancode);
    character = get(scancodes, scancode);
}