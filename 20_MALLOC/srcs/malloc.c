// srcs/malloc.c

#include "../includes/malloc.h"

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

heap_group g_heap = {
    .TINY_HEAP = NULL,
    .SMALL_HEAP = NULL,
    .LARGE_HEAP = NULL,
};

// Aligne sur 16 octets (taille typique pour arch 64 bits)
static size_t align_size(size_t size) {
    size_t alignment = 16;
    return (size + alignment - 1) & ~(alignment - 1);
}

// Fonction pour allouer dans une zone spécifique (TINY, SMALL, LARGE)
static void* allocate_in_zone(t_heap **zone_head, size_t size, size_t heap_size, t_heap_group group) {
    t_heap *zone = *zone_head;
    t_block *block = NULL;

    // 1- Parcourir les heaps existantes pour trouver un bloc libre
    while (zone) {

        if (zone->group == group) {
            coalesce_free_blocks(zone);
            block = find_free_block(zone, size);
            if (block) {
                block->freed = false;
                // Here, we should split the block (shrink)
                // block->size > size + sizeof(t_block)
                return BLOCK_SHIFT(block);
            }
        }
        zone = zone->next;
    }

    // 2- Si aucun bloc libre n'est trouvé, créer une nouvelle heap
    if (!block) {
        t_heap *new_heap = create_heap_from_aligned_size(heap_size, group);
        if (!new_heap) {
            return NULL;
        }

        block = create_block(new_heap, size);
        if (!block) {
            return NULL;
        }
    }

    return BLOCK_SHIFT(block);
}


void *malloc(size_t size)
{
    if (size == 0)
        return (NULL);

    pthread_mutex_lock(&g_malloc_mutex);

    size_t aligned_size = align_size(size);

    t_heap_group group = get_group_size(aligned_size);

    void *allocated_block = NULL;
    if (group == TINY) {
        allocated_block = allocate_in_zone(&g_heap.TINY_HEAP, aligned_size, TINY_HEAP_ALLOCATION_SIZE, TINY);
    }
    else if (group == SMALL) {
        allocated_block = allocate_in_zone(&g_heap.SMALL_HEAP, aligned_size, SMALL_HEAP_ALLOCATION_SIZE, SMALL);
    }
    else if (group == LARGE) {
        // For LARGE, create a new heap
        size_t heap_size = align_size(size + sizeof(t_heap) + sizeof(t_block));
        allocated_block = allocate_in_zone(&g_heap.LARGE_HEAP, aligned_size, heap_size, LARGE);
    }

    if (allocated_block && getenv("MALLOC_DEBUG")) {
        // Afficher le message de débogage
        ft_putstr_fd("[MALLOC] Allocated ", 1);
        ft_putnbr_fd(size, 1);
        ft_putstr_fd(" bytes at ", 1);
        print_address_hex((size_t)allocated_block);
        ft_putstr_fd("\n", 1);
    }

    pthread_mutex_unlock(&g_malloc_mutex);
    return allocated_block;
}
