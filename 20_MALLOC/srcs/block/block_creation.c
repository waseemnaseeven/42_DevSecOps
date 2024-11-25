#include "../../includes/malloc.h"

t_block *find_free_block(t_heap *my_heap, size_t size) {
    
    t_block *current = my_heap->blocks;

    while (current) {
        if (current->freed && current->size >= size)
            return current;
        current = current->next;
    }
    return (NULL);
}

// t_block *create_block(t_heap *my_heap, size_t size) {
//     // printf("My size on create_block: %ld", size);

//     if (my_heap->unused_space_size < size + sizeof(t_block))
//         return (NULL);
//     t_block *block = (t_block *)((void *)my_heap + sizeof(t_heap) + my_heap->total_size - my_heap->unused_space_size);
//     block->size = size;
//     block->freed = false;
//     block->unused_space = block->size - size;
//     block->prev = NULL;
//     block->next = my_heap->blocks;
//     if (my_heap->blocks)
//         my_heap->blocks->prev = block;
//     my_heap->blocks = block;
//     my_heap->unused_space_size -= (size + sizeof(t_block));
//     my_heap->block_count++;
//     return (block);
// }

t_block *create_block(t_heap *my_heap, size_t size) {
    if (my_heap->unused_space_size < size + sizeof(t_block))
        return NULL;

    // Calculate the address for the new block
    t_block *block = (t_block *)((char *)my_heap + my_heap->current_offset);

    // Initialize the block
    block->size = size;
    block->freed = false;
    block->prev = NULL;
    block->next = my_heap->blocks;

    if (my_heap->blocks)
        my_heap->blocks->prev = block;
    my_heap->blocks = block;

    my_heap->current_offset += sizeof(t_block) + size;
    my_heap->unused_space_size -= (size + sizeof(t_block));
    my_heap->block_count++;

    return block;
}
