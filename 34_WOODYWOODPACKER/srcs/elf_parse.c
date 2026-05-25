#include "woody.h"

/*
** validate_elf64 — returns 1 if map is a valid x86-64 ELF64 binary.
** Checks: magic, class, machine, type, section header bounds.
*/
int     validate_elf64(void *map, size_t size)
{
    Elf64_Ehdr *e;

    if (size < sizeof(Elf64_Ehdr))
        return 0;
    e = (Elf64_Ehdr *)map;
    if (memcmp(e->e_ident, ELFMAG, SELFMAG) != 0)
        return 0;
    if (e->e_ident[EI_CLASS] != ELFCLASS64) {
        dprintf(STDERR_FILENO,
            "Error: not a 64-bit binary (EI_CLASS=%d)\n",
            e->e_ident[EI_CLASS]);
        return 0;
    }
    if (e->e_machine != EM_X86_64) {
        dprintf(STDERR_FILENO,
            "Error: not x86_64 (e_machine=%d)\n", e->e_machine);
        return 0;
    }
    if (e->e_type != ET_EXEC && e->e_type != ET_DYN)
        return 0;
    return 1;
}

/*
** find_text64 — returns a pointer to the .text Elf64_Shdr,
** or NULL if not found. Uses .shstrtab to match the name.
*/
Elf64_Shdr *find_text64(void *map)
{
    Elf64_Ehdr  *e;
    Elf64_Shdr  *s;
    char        *names;
    int          i;

    e     = (Elf64_Ehdr *)map;
    s     = (Elf64_Shdr *)((char *)map + e->e_shoff);
    names = (char *)map + s[e->e_shstrndx].sh_offset;
    i     = 0;
    while (i < e->e_shnum) {
        if (strcmp(names + s[i].sh_name, ".text") == 0)
            return &s[i];
        i++;
    }
    return NULL;
}