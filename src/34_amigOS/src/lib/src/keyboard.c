#include "../include/keyboard.h"
#include "../include/stdlib.h"
#include "../include/ports.h"



void init_scancode_table(Dictionary* dict){
    create_pair("1f", "a");
    insert(scancode_table, "1f", "a");
}

void keyboard_handler(){
    printf("Keyboard");
    char* scancode = '\0';
    char* character = '\0';
    while (1)
    {
        int_to_string(inb(0x60), scancode);
        character = get(scancode_table, scancode);
        printf(character);
    }
}