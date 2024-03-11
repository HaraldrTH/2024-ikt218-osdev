global gdt_flush

gdt_flush:
    lgdt [eax]  ; Load the global descriptor table (GDT) pointer
    ret