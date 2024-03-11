struct gdt_entry;
struct gdt_ptr;

//Det under er generert av ChatPGT
//Prompt: Extend your OS by implementing the Global Descriptor Table (GDT) mechanism. 
//You should at minimum implement the NULL, Data, and Text descriptor.
//How to do in c

// Declare functions to load GDT
extern void gdt_flush(int i);  
//Slutt på ChatGPT her
void gdt_set_gate(int num, int base, int limit, int access, int gran);
void init_gdt();