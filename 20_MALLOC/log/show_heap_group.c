#include "../includes/malloc.h"

void    show_heap_group(t_heap *my_heap) {

    if (my_heap->group == TINY) {
        ft_putendl_fd("GROUP IS TINY", 1);
    } else if (my_heap->group == SMALL) {
        ft_putendl_fd("GROUP IS SMALL", 1);
    } else {
        ft_putendl_fd("GROUP IS LARGE", 1);
    }
}