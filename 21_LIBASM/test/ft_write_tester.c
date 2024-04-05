#include "../functions/includes/libasm.h"
#include "libasm_tester.h"
#include "../colors.h"

void ft_write_test(void) {

    printf("Testing write function with my ft_write\n");
    printf("The original write function with the string ");
    printf(BLUE "Hello World!\n\n" RESET);

    write(1, "Original Hello World!\n\n", strlen("original Hello World!\n\n"));
    ft_write(1, "My Hello World!\n", strlen("My Hello World!\n"));
}