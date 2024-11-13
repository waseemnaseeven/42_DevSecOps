#include "../includes/malloc.h"

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
t_heap *g_heap = NULL;

// La fonction align_size ajuste la taille de la mémoire demandée pour la rendre alignée avec la taille de la structure t_block.
static  size_t align_size(size_t size) {
    return (size + sizeof(t_block) - 1) & ~(sizeof(t_block) - 1);
}

t_heap *create_heap(size_t heap_size, t_heap_group group) {

    t_heap  *my_heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
    if (my_heap == MAP_FAILED)
        return (NULL);
    my_heap->total_size = heap_size;
    my_heap->unused_space_size = heap_size - sizeof(t_heap);
    my_heap->block_count = 0;
    my_heap->prev = NULL;
    my_heap->next = g_heap;
    my_heap->group = group;
    my_heap->blocks = NULL;
    if (g_heap)
        g_heap->prev = my_heap;
    g_heap = my_heap;
    return (my_heap);
}

t_block *find_free_block(t_heap *my_heap, size_t size) {
    
    t_block *current = my_heap->blocks;

    while (current) {
        if (current->freed && current->size >= size)
            return current;
        current = current->next;
    }
    return (NULL);
}

t_block *create_block(t_heap *my_heap, size_t size) {
    printf("My size on create_block: %ld", size);

    if (my_heap->unused_space_size < size + sizeof(t_block))
        return (NULL);
    t_block *block = (t_block *)((void *)HEAP_SHIFT(my_heap) + my_heap->block_count * sizeof(t_block));
    block->size = size;
    block->freed = false;
    block->unused_space = block->size - size;
    printf("unused_space is : %ld", block->unused_space);
    block->prev = NULL;
    block->next = my_heap->blocks;
    if (my_heap->blocks)
        my_heap->blocks->prev = block;
    my_heap->blocks = block;
    my_heap->unused_space_size -= (size + sizeof(t_block));
    my_heap->block_count++;
    return (block);
}

/*
    1- Aligner la taille
    2- Si la heap est initialise, chercher un free_block
        a- Si free_chunk
            - split le block (si la difference entre la taille demande et la taille du bloc libre trouve est suffisamment grande pour stocker les metadata [info taille du bloc, ptr vers le block suivant] ou encore un bloc minimal [4bytes] ALORS le bloc peut etre divise en 2 parties)
            -  marque le bloc comme utilise
        b- etendre la heap
    3- Si la heap n'est pas initialise, on la creer:


*/

void    *malloc(size_t size)
{
    if (size == 0)
        return (NULL);

    pthread_mutex_lock(&g_malloc_mutex);

    size_t total_block_size = align_size(size);
    printf("total block size: %ld\n", total_block_size);
    t_heap  *my_heap = g_heap;
    t_block *block = NULL;

    // Compare size and find free_block
    while (my_heap) {
        if ((my_heap->group == TINY && total_block_size <= TINY_BLOCK_SIZE) || (my_heap->group == SMALL && total_block_size <= SMALL_BLOCK_SIZE)) {
            block = find_free_block(my_heap, total_block_size);
            if (block) {
                block->freed = false;
                break;
            }
        }
        my_heap = my_heap->next;
    }

    // Compare_size and create_heap and create_block
    if (!block) {
        // Verify if size requested is chunk
        t_heap_group group = (total_block_size <= TINY_BLOCK_SIZE) ? TINY : (total_block_size <= SMALL_BLOCK_SIZE) ? SMALL : LARGE;
        printf("group is : %d", group);
        size_t heap_size = (group == TINY) ? TINY_HEAP_ALLOCATION_SIZE : (group == SMALL) ? SMALL_HEAP_ALLOCATION_SIZE : total_block_size + sizeof(t_heap);

        my_heap = create_heap(heap_size, group);
        if (!my_heap) {
            pthread_mutex_unlock(&g_malloc_mutex);
            return (NULL);
        }
        block = create_block(my_heap, total_block_size);
    }

    if (block)
        block->freed = false;
    block->unused_space = (block->size > size) ? (block->size - size) : 0;
    
    if (getenv("MALLOC_DEBUG")) {
        printf("[MALLOC] Allocated %zu bytes at %p", size, BLOCK_SHIFT(block));
    }

    pthread_mutex_unlock(&g_malloc_mutex);
    return block ? BLOCK_SHIFT(block) : NULL;
}

