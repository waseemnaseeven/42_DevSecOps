// srcs/show_alloc_mem.c

#include "../includes/malloc.h"


static void display_group(t_heap *heap, char *group_name, size_t *total_memory) {
    t_heap *current_heap = heap;
    while (current_heap) {
        ft_putstr_fd(group_name, 1);
        ft_putstr_fd(" : ", 1);
        print_address_hex((size_t)current_heap);
        ft_putstr_fd("\n", 1);

        t_block *current_block = current_heap->blocks;
        while (current_block) {
            if (!current_block->freed) {
                void *start_address = BLOCK_SHIFT(current_block);
                void *end_address = (void *)((char *)start_address + current_block->size);

                print_address_hex((size_t)start_address);
                ft_putstr_fd(" - ", 1);
                print_address_hex((size_t)end_address);
                ft_putstr_fd(" : ", 1);
                ft_putnbr_fd(current_block->size, 1);
                ft_putstr_fd(" bytes\n", 1);

                *total_memory += current_block->size;
            }
            current_block = current_block->next;
        }
        current_heap = current_heap->next;
    }
}

void show_alloc_mem(void) {
    pthread_mutex_lock(&g_malloc_mutex);

    size_t total = 0;

    display_group(g_heap.TINY_HEAP, "TINY", &total);
    display_group(g_heap.SMALL_HEAP, "SMALL", &total);
    display_group(g_heap.LARGE_HEAP, "LARGE", &total);

    ft_putstr_fd("Total : ", 1);
    ft_putnbr_fd(total, 1);
    ft_putstr_fd(" bytes\n\n", 1);

    pthread_mutex_unlock(&g_malloc_mutex);
}