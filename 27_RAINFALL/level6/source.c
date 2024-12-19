#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void m() {
    puts("Nope");
}

// Fonction potentiellement exploitable (affiche un fichier sensible)
void n() {
    system("/bin/cat /home/user/level7/.pass");
}

int main(int argc, char **argv) {
    char *buffer;
    void (*function_ptr)();

    buffer = (char *)malloc(64);
    function_ptr = m; // Pointeur de fonction initialisé sur `m`

    strcpy(buffer, argv[1]);

    function_ptr();

    free(buffer);

    return 0;
}
