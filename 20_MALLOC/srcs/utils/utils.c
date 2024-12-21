#include "../../includes/malloc.h"

void print_address_hex(size_t value) {
    char hex[16] = "0123456789abcdef";
    char buffer[32]; 
    int i = 0;

    if (value == 0) {
        ft_putstr_fd("0x0", 1);
        return;
    }

    while (value > 0 && i < 32) {
        buffer[i++] = hex[value % 16];
        value /= 16;
    }
    ft_putstr_fd("0x", 1);
    while (i > 0) {
        ft_putchar_fd(buffer[--i], 1);
    }
}