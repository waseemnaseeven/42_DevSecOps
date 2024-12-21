#include "../../includes/malloc.h"

// Fusionner les blocs libres adjacents dans un heap
void coalesce_free_blocks(t_heap *my_heap) {
    t_block *current = my_heap->blocks;

    while (current && current->next) {
        if (current->freed && current->next->freed) {
            size_t combined_size = current->size + sizeof(t_block) + current->next->size;

            // Fusionner les blocs
            current->size = combined_size;
            current->next = current->next->next;
            if (current->next) {
                current->next->prev = current;
            }
        } else {
            current = current->next;
        }
    }
}

t_block *get_first_block(t_block *block) {

    while (block->prev) {
        block = block->prev;
    }
    return (block);
}

t_block *get_last_block(t_block *block) {
    
    while (block->next) {
        block = block->next;
    }
    return (block);

}