#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p() {
    char buffer[80];
    unsigned int dangerous_value;

    fflush((FILE *)0x8049860);

    gets(buffer);

    dangerous_value = *(unsigned int *)((char *)&dangerous_value + 4);
    if ((dangerous_value & 0xb0000000) == 0xb0000000) {
        printf("Error: Dangerous value detected (%x)\n", dangerous_value);
        _exit(1);
    }

    puts(buffer);

    strdup(buffer);
}

int main(){
    p();
    return 0;
}