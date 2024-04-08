global gdt_flush

gdt_flush:
    lgdt [eax]  ; Load the GDT pointer
    ret