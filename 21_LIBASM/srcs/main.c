#include <stdio.h>

extern void hello_world(void);

int main() {
    printf("Calling assembly function...\n");
    hello_world();
    printf("Assembly function returned.\n");
    return 0;
}
