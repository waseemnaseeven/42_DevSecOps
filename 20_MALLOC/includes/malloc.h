#ifndef MALLOC_H
# define MALLOC_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <fcntl.h>
#include <pthread.h>

// Space to return
#define HEAP_SHIFT(start) ((void *) start + sizeof(t_heap))
#define BLOCK_SHIFT(start) ((void *) start + sizeof(t_block))

// Size of heap
#define TINY_HEAP_ALLOCATION_SIZE ((size_t)4 * sysconf(_SC_PAGESIZE))
#define SMALL_HEAP_ALLOCATION_SIZE ((size_t)8 * sysconf(_SC_PAGESIZE))
#define LARGE_HEAP_ALLOCATION_SIZE ((size_t)16 * sysconf(_SC_PAGESIZE))

// Size of blocks
#define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SIZE / 100)
#define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 100)

typedef enum	e_heap_group {
	TINY,
	SMALL,
	LARGE
}				t_heap_group;

// Metadata structure for a block 
typedef struct      s_block {

    size_t          size;
    bool            freed;
    size_t          unused_space;
    struct s_block  *prev;
    struct s_block  *next;

}                   t_block;

// Naviguate around the heap during mmap calls and access any block
typedef struct      s_heap {

    size_t          total_size;
    size_t          unused_space_size; // free_size
    size_t          block_count; 
    struct s_heap	*prev;
	struct s_heap	*next;
	t_heap_group	group; // Type of heap (TINY, SMALL, LARGE)
    t_block         *blocks; // Pointer to the first block in the heap

}                   t_heap;

extern t_heap           *g_heap;
extern pthread_mutex_t  g_malloc_mutex;

// Malloc functions
void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);

// Show functions
void    show_alloc_mem(void);
// void    show_alloc_mem_ex(void);

#endif