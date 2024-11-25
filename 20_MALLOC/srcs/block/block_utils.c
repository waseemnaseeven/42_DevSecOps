#include "../../includes/malloc.h"

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