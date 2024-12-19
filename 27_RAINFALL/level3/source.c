#include <stdio.h>
#include <stdlib.h>

void v(void) {
    char buffer[512];
    
    fgets(buffer, sizeof(buffer), stdin);
    
    printf(buffer);

    if (m == 0x40) {
        fwrite("Wait what?!\n", 1, 12, stdout);
        system("/bin/sh");
    }
}

int main(void) {
    v();
    return 0;
}
