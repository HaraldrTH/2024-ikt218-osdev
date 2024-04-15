global gdt_flush

gdt_flush:
    MOV eax, [esp+4]
    lgdt [eax]  ; Load the GDT pointer
    
    MOV   AX, 0x10 ; 0x10 is a stand-in for your data segment
    MOV   DS, AX
    MOV   ES, AX
    MOV   FS, AX
    MOV   GS, AX
    MOV   SS, AX
    JMP   0x08:.reload_CS ; 0x08 is a stand-in for your code segment
    

.reload_CS:
   ; Reload data segment registers:
   
   RET

    