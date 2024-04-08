#include "../functions/includes/libasm.h"
#include "libasm_tester.h"
#include "../colors.h"
#include <errno.h>

void ft_read_test() {

    printf(BOLDWHITE "Testing read function with my ft_read\n\n" RESET);
    printf("The original read function with a file or a string\n");

    char bufread[1024];
    char buf[1024];
    int fd = open("input.txt", O_RDONLY);
    int fd2 = open("input2.txt", O_RDONLY);
    int invalid_fd = -1;
    if (fd == -1) {
        printf(BOLDRED "Cant open the input1\n" RESET);
        exit(1);
    }
    if (fd2 == -1) {
        printf(BOLDRED "Cant open the input2\n" RESET);
        exit(1);
    }
    if (read(fd, bufread, 1024) < 0) {
        printf(BOLDRED "Cant read the input1\n" RESET);
        exit(1);
    }
    if (ft_read(fd2, buf, 1024) < 0) {
        printf(BOLDRED "Cant read the input2\n" RESET);
        exit(1);
    }

    printf(BLUE "What the original function read: %s\n", bufread);
    printf(GREEN "What my function read: %s\n", buf);

    printf(RED "\nTesting ft_read with a bad file descriptor\n");

    char buffer[1024];
    errno = 0;
    ft_read(invalid_fd, buffer, 1024);
    if (errno != 0)
        printf(BOLDMAGENTA "2- Error occured during ft_read: errno = %d\n", errno);
    close(fd);
    close(fd2);
}