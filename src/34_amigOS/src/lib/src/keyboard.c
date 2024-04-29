#include "../include/keyboard.h"
#include "../include/stdlib.h"
#include "../include/ports.h"

Dictionary* scancodes;
init_scancodes(){
    insert(scancodes, "30", "a");
}
void keyboard_handler(){
    printf("Keyboard");
}