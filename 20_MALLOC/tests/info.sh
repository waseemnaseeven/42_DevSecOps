#!/bin/bash

echo -e "Test the minimum bytes for memory allocation: "
cat /proc/sys/vm/mmap_min_addr

echo -e "To verify if the shared library used pthread, we should see : 'ELF 64-bit' 'LSB shared object'"
file libft_malloc_x86_64_Linux.so
ldd libft_malloc_x86_64_Linux.so

