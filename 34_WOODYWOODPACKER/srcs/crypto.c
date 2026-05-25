#include "woody.h"


/*
** generate_key — reads KEY_LEN bytes from /dev/urandom.
** Returns 0 on success, -1 on failure.
*/
int generate_key(uint8_t key[KEY_LEN]) {
    
    int fd;

    fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        return -1;
    }
    if (read(fd, key, KEY_LEN) != KEY_LEN) {
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

void    print_key(const uint8_t *key, size_t len) {
    
    size_t  i = 0;

    printf("key_value: ");
    while (i < len) {
        printf("%02X", key[i++]);
    }
    printf("\n");
}