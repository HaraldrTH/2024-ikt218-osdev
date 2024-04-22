#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include "lib/include/stdlib.h"
#include "lib/include/GDT.h"
#include "lib/include/IDT.h"
#include "lib/include/IRQ.h"
#include "lib/include/keyboard.h"
#include "lib/include/mem.h"



struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();


int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    init_gdt();
    init_idt();
    init_irq();
    memory_init();
    register_interrupt_handler(33, keyboard_handler);
    asm volatile ("int $0x0");
    asm volatile ("int $0x1");
    asm volatile ("int $0x2");



    while(true){}

    return 0;
}