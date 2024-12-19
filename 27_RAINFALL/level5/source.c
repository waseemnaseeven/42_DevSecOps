#include <stdio.h>
#include <stdlib.h>

void o() {
    system('/bin/sh');
    _exit(1);
}

void n() {
    char buffer[516];

    fgets(buffer, 512, (FILE *)0x8049848);

    printf("%s", buffer);

    exit(1);
}

int main() {
    n();
    return 0;
}