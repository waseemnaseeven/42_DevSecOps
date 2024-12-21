// log/show_alloc_mem_ex.c

#include "../includes/malloc.h"

void print_block_hex(void *block_start, size_t size) {
    unsigned char *ptr = (unsigned char *)block_start;
    size_t i = 0;

    while (i < size) {
        if (i % 16 == 0) {
            if (i > 0) {
                ft_putchar_fd('\n', 1);
            }
            print_address_hex((size_t)(ptr + i));
            ft_putstr_fd(": ", 1);
        }

        unsigned char byte = ptr[i];
        char high_nibble = "0123456789abcdef"[byte >> 4];
        char low_nibble = "0123456789abcdef"[byte & 0x0F];
        ft_putchar_fd(high_nibble, 1);
        ft_putchar_fd(low_nibble, 1);
        ft_putchar_fd(' ', 1);
        i++;
    }
    ft_putchar_fd('\n', 1);
}

static void display_group_ex(t_heap *heap, char *group_name) {
    t_heap *current_heap = heap;
    while (current_heap) {
        ft_putstr_fd(group_name, 1);
        ft_putstr_fd(" : ", 1);
        print_address_hex((size_t)current_heap);
        ft_putstr_fd("\n", 1);

        t_block *current_block = current_heap->blocks;
        int block_num = 0;
        while (current_block) {
            block_num++;
            ft_putstr_fd("    Block ", 1);
            ft_putnbr_fd(block_num, 1);
            ft_putstr_fd(" : ", 1);

            if (current_block->freed) {
                ft_putstr_fd("\033[0;32mFREE ", 1);
            } else {
                ft_putstr_fd("\033[0;31mALLOCATED ", 1);
            }

            ft_putnbr_fd(current_block->size, 1);
            ft_putstr_fd(" bytes\033[0m\n", 1);

            void *start_address = BLOCK_SHIFT(current_block);
            void *end_address = (void *)((char *)start_address + current_block->size);

            ft_putstr_fd("        ", 1);
            print_address_hex((size_t)start_address);
            ft_putstr_fd(" - ", 1);
            print_address_hex((size_t)end_address);
            ft_putstr_fd(" : ", 1);
            ft_putnbr_fd(current_block->size, 1);
            ft_putstr_fd(" bytes\n", 1);

            if (!current_block->freed) {
                ft_putstr_fd("        Hexdump:\n", 1);
                print_block_hex(start_address, current_block->size);
            }

            current_block = current_block->next;
        }
        current_heap = current_heap->next;
    }
}

void show_alloc_mem_ex(void) {
    pthread_mutex_lock(&g_malloc_mutex);

    display_group_ex(g_heap.TINY_HEAP, "TINY");
    display_group_ex(g_heap.SMALL_HEAP, "SMALL");
    display_group_ex(g_heap.LARGE_HEAP, "LARGE");

    pthread_mutex_unlock(&g_malloc_mutex);
}


