#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char buffer[40];
    int input_length;

    if (argc < 3) {
        printf("Usage: %s <input_length> <data>\n", argv[0]);
        return 1;
    }

    input_length = atoi(argv[1]);

    if (input_length < 10) {
        // Copie les données de l'utilisateur dans le buffer sans vérification suffisante de la taille
        memcpy(buffer, argv[2], input_length * 4);

        if (input_length == 0x574f4c46) { // 'FLOW' en hexadécimal
            execl("/bin/sh", "sh", NULL);
        }
    } else {
        printf("Input length must be less than 10.\n");
        return 1;
    }

    return 0;
}

