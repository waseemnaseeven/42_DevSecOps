#ifndef WOODY_H
# define WOODY_H

# include <elf.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdint.h>


/* RC4 key len in bytes */
# define KEY_LEN         16

# define WOODY_OUT      "woody"

# define STUB64_PATH     "srcs/asm/woody_stub64.bin"
# define STUB32_PATH     "srcs/asm/woody_stub32.bin"

typedef struct {
    void        *map;          /* mmap of input binary           */
    size_t      file_size;    /* size of input binary           */
    uint8_t     key[KEY_LEN]; /* RC4 key                        */
    uint8_t     *stub;        /* loaded stub binary             */
    size_t      stub_size;   /* size of stub binary            */
    size_t      stub_data_off;/* offset of stub_data in stub   */
    int         is_32bit;     /* 1 if packing a 32-bit binary   */
} t_woody;


/* crypto.c */
int         generate_key(uint8_t key[KEY_LEN]);
void    print_key(const uint8_t *key, size_t len);


/* file_io.c */
void    *map_file(const char *path, size_t *out_size);
void    write_woody(void *buf, size_t size);


/* elf_parse.c */
int     validate_elf64(void *map, size_t size);
Elf64_Shdr  *find_text64(void *map);

/* stub_inject.c */

#endif