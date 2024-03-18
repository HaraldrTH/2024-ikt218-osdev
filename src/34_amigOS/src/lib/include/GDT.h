struct gdt_entry;
struct gdt_ptr;

void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void init_gdt();
void gdt_load(struct gdt_ptr *gdt_ptr);
