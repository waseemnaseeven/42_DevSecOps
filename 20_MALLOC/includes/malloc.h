#ifndef MALLOC_H
#define MALLOC_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

#define PAGESIZE 4096

void    *malloc(size_t size);


#endif