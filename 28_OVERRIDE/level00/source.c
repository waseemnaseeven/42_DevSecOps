#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool main(void)
{
    int password;

    puts("***********************************");
    puts("* \t     -Level00 -\t\t  *");
    puts("***********************************");
    printf("Password: ");
    scanf("%d", &password);

    if (password != 0x149c) { // 5276
        puts("\nInvalid Password!");
    } else {
        puts("\nAuthenticated!");
        system("/bin/sh");
    }

    return 0;
}
