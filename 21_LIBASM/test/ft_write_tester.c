#include "../functions/includes/libasm.h"
#include "libasm_tester.h"
#include "../colors.h"
#include <errno.h>

void ft_write_test(void) {

    printf(BOLDWHITE "Testing write function with my ft_write\n\n" RESET);
    printf("The original write function with the string ");
    printf(BLUE "Hello World!\n\n" RESET);

    int valid_fd = 1;
    write(1, "Original Hello World!\n\n", strlen("original Hello World!\n\n"));
    ft_write(valid_fd, "My Hello World!\n", strlen("My Hello World!\n"));
    errno = 0;
    if (errno != 0)
        printf(BOLDMAGENTA "1- Error occured during ft_write: errno = %d\n", errno);
    

    int fd = -1;
    printf(RED "\nTesting ft_write with a bad file descriptor\n");
    errno = 0;
    ft_write(fd, "My Hello World!\n", strlen("My Hello World!\n"));
    if (errno != 0)
        printf(BOLDMAGENTA "2- Error occured during ft_write: errno = %d\n", errno);
    
    
}