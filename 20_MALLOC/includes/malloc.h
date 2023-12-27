#ifndef MALLOC_H
# define MALLOC_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
// #include <stdlib.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <fcntl.h>
#include <pthread.h>

#define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap))
#define BLOCK_SHIFT(start) ((void *) start + sizeof(t_block))

// Size of heap
#define TINY_HEAP_ALLOCATION_SIZE (4 * getpagesize())
#define SMALL_HEAP_ALLOCATION_SIZE (8 * getpagesize())
#define LARGE_HEAP_ALLOCATION_SIZE (16 * getpagesize())

// Size of blocks
#define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SiZE / 100)
#define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 100)

typedef enum	e_bool {
	FALSE,
	TRUE
}				t_bool;

typedef enum	e_heap_group {
	TINY,
	SMALL,
	LARGE
}				t_heap_group;


// Metadata structure for a block 
typedef struct      s_block {

    size_t          size;
    bool            freed;
    struct s_block  *prev;
    struct s_block  *next;

}                   t_block;

// Naviguate around the heap during mmap calls and access any block
typedef struct      s_heap {

    size_t          total_size;
    size_t          free_size;
    size_t          block_count;
    struct s_heap	*prev;
	struct s_heap	*next;
	t_heap_group	group;
    t_block         *blocks;

}                   t_heap;

extern t_heap           *g_heap;
extern pthread_mutex_t  g_malloc_mutex;

// Malloc functions
void    *ft_malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);

// Show functions
void    show_alloc_mem(void);

#endif