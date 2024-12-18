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

#define ALIGN_SIZE 

#define HEAP_SHIFT(start) ((void *)((char *) (start) + sizeof(t_heap)))
#define BLOCK_SHIFT(start) ((void *)((char *)(start) + sizeof(t_block)))


// Size of heap
// #define TINY_HEAP_ALLOCATION_SIZE ((size_t)4 * sysconf(_SC_PAGESIZE))
// #define SMALL_HEAP_ALLOCATION_SIZE ((size_t)8 * sysconf(_SC_PAGESIZE))

#define TINY_HEAP_ALLOCATION_SIZE ((size_t)16 * sysconf(_SC_PAGESIZE))
#define SMALL_HEAP_ALLOCATION_SIZE ((size_t)64 * sysconf(_SC_PAGESIZE))

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

    size_t          requested_size; // The actual size requested with malloc
    size_t          size; // Aligned size of the allocated block
    bool            freed; // If the block is free or not
    size_t          unused_space; 
    struct s_block  *prev;
    struct s_block  *next;
    struct s_block  *next_alloc;

}                   t_block;

// Naviguate around the heap during mmap calls and access any block
typedef struct      s_heap {

    struct s_heap   *prev;
    struct s_heap   *next;
    size_t          total_size;
    size_t          unused_space_size; // free_size
    size_t          current_offset; // follow actual position
    size_t          block_count;
	t_heap_group	group; // Type of heap (TINY, SMALL, LARGE)
    t_block         *blocks; // Pointer to the first block in the heap
    t_block         *last_allocated_block;

}                   t_heap;

extern t_heap           *g_heap;
extern pthread_mutex_t  g_malloc_mutex;

// Malloc / Free / Realloc functions
void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);

// Heap functions
t_heap *create_heap_from_aligned_size(size_t heap_size, t_heap_group group);
t_heap *create_heap(size_t heap_size, t_heap_group group, t_heap* gl_heap);

// Block functions
t_block *create_block(t_heap *my_heap, size_t size);
t_block *find_free_block(t_heap *my_heap, size_t size);

// Log functions
void    show_alloc_mem(void);
void    show_alloc_mem_basic(void);
void    show_alloc_mem_ex(void);

// Utils Methods
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
#endif