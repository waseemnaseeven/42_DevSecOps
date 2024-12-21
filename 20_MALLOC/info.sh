#!/bin/bash

echo -e "Test the minimum bytes for memory allocation: "
cat /proc/sys/vm/mmap_min_addr

echo -e "To verify if the shared library used pthread, we should see : 'ELF 64-bit' 'LSB shared object'"
file libft_malloc_x86_64_Linux.so
ldd libft_malloc_x86_64_Linux.so

```
/usr/bin/time -v. L’exemple était :

Maximum resident set size (kbytes): 1212
Page size (bytes): 4096
En convertissant 1212 kB en octets (1212 * 1024 ≈ 1 241 088 octets), puis en divisant par 4096 (la taille de page), on obtenait environ 303 pages (1 241 088 / 4096 ≈ 303).
```