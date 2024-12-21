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

// Return pointer of the block or heap without the metadata
#define HEAP_SHIFT(start) ((void *)((char *) (start) + sizeof(t_heap)))
#define BLOCK_SHIFT(start) ((void *)((char *)(start) + sizeof(t_block)))

// Size of heap
#define TINY_HEAP_ALLOCATION_SIZE ((size_t)16 * sysconf(_SC_PAGESIZE))
#define SMALL_HEAP_ALLOCATION_SIZE ((size_t)64 * sysconf(_SC_PAGESIZE))

// Size of blocks, treshold size, at least 100 allocations
#define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SIZE / 128)// Treshold of 512bytes
#define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 128) // Treshold of 2048bytes

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

    struct s_heap   *prev;
    struct s_heap   *next;

    size_t          total_size;
    size_t          unused_space_size;
    size_t          current_offset;
    size_t          block_count;
	t_heap_group	group;
    t_block         *blocks;

}                   t_heap;

typedef struct  heap_group {
    t_heap      *TINY_HEAP;
    t_heap      *SMALL_HEAP;
    t_heap      *LARGE_HEAP;
}               heap_group;

extern heap_group       g_heap;
extern pthread_mutex_t  g_malloc_mutex;

// Malloc functions
void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);

// Heap functions
t_heap  *create_heap_from_aligned_size(size_t heap_size, t_heap_group group);
t_heap  *create_heap(size_t heap_size, t_heap_group group, t_heap* gl_heap);

// Block functions
t_block *create_block(t_heap *my_heap, size_t size);
t_block *find_free_block(t_heap *my_heap, size_t size);

// Log functions
void        show_alloc_mem(void);
void        show_alloc_mem_ex(void);
void        print_address_hex(size_t value); 

// Utils functions
t_block         *get_first_block(t_block *block);
t_block         *get_last_block(t_block *block);
char            *get_group_name(t_heap_group group);
size_t          heap_size_function(t_heap_group group, size_t total_block_size);
t_heap_group    get_group_size(size_t total_block_size);
void            coalesce_free_blocks(t_heap *my_heap); 

// Libc functions
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void    ft_putnbr_fd(size_t n, int fd);

#endif
