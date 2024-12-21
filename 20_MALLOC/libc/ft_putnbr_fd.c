#include <unistd.h>

void    ft_putchar_fd(char c, int fd) {
    write(fd,  &c, 1);
}

void	ft_putnbr_fd(size_t n, int fd) {
    char c;
    
    if (n >= 10)
        ft_putnbr_fd(n / 10, fd);
    c = '0' + (n % 10);
    ft_putchar_fd(c, fd);
}
