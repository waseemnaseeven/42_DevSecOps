#include "woody.h"

// 1.  mmap source → map, file_size
// 2.  Valider ELF64 + EM_X86_64
// 3.  Générer key → afficher
// 4.  Trouver .text → sh_offset, sh_size, sh_addr
// 5.  Sauvegarder orig_entry = ehdr->e_entry  ← explicite dans l'algo
// 6.  Allouer buf[file_size + stub_size]
// 7.  memcpy(buf, map, file_size)
// 8.  rc4(key, buf + sh_offset, sh_size)      ← chiffrer dans buf
// 9.  stub_vaddr = p_vaddr + p_filesz         ← lire AVANT extension
// 10. p_filesz += stub_size                   ← étendre dans buf
//     p_memsz  += stub_size
// 11. Copier stub → stub_copy
//     Patcher stub_copy (text_vaddr, text_size, key, orig_entry)
// 12. memcpy(buf + file_size, stub_copy, stub_size)
// 13. ehdr_buf->e_entry = stub_vaddr          ← patcher dans buf
// 14. write_woody(buf, file_size + stub_size)
// 15. munmap + free → exit(0)

/*
** usage — prints usage message to stderr and exits with code 1.
*/
static void usage(const char *prog)
{
    // dprintf(STDERR_FILENO,
        // "Usage: %s [-k HEXKEY] <elf64_binary>\n", prog);
    // exit(1);
     dprintf(STDERR_FILENO,
        "Usage: %s <elf64_binary>\n", prog);
    exit(1);
}

int main(int ac, char** av) {

    t_woody         w;
    const char      *target;
    unsigned char   *elf_class;

    memset(&w, 0, sizeof(w));
    if (ac == 2) {
        target = av[1];
        if (generate_key(w.key) != 0) {
            dprintf(STDERR_FILENO, "Error: key generation failed\n");
            return 1;
        }
        print_key(w.key, KEY_LEN);
    
    // } else if (ac == 4 && strcmp(av[1], "-k") == 0) {
        // target = av[3];
        // if (parse_hex_key(av[2], w.key) < 0) {
            // dprintf(STDERR_FILENO, "Error: invalid key format\n");
            // return 1;
        // }
        // print_key(w.key, KEY_LEN);
    } else {
        usage(av[0]);
    }
    w.map = map_file(target, &w.file_size);
    if (!w.map) {
        return 1;
    }
    elf_class = ((unsigned char *)w.map)[EI_CLASS];
    if (elf_class == ELFCLASS64 && validate_elf64(w.map, w.file_size)) {
        // w.stub = load_stub(STUB64_PATH, &w.stub_size);
        // if (w.stub) {
            // pack64(&w);
            // free(w.stub);
        // }
    // } else if (elf_class == ELFCLASS32 && validate_elf32(w.map, w.file_size)) {
    //     w.stub = load_stub(STUB32_PATH, &w.stub_size);
    //     if (w.stub) {
    //         pack32(&w);
    //         free(w.stub);
    //     }
    } else {
        dprintf(STDERR_FILENO,
            "Error: unsupported binary. x86_64 or x86 ELF only.\n");
        munmap(w.map, w.file_size);
        return 1;
    }

    munmap(w.map, w.file_size);
    return 0;
}