#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void) {
    char buffer[100];    // taille buffer limite 100bytes
    unsigned int index = 0;  

    
    fgets(buffer, 100, stdin); 

    while (1) {

        unsigned int length = strlen(buffer);

        // Vérifier si l'index dépasse la longueur
        if (index >= length) {
            printf("%s", buffer);
            exit(0);
        }

        // Si le caractère est une lettre majuscule, le convertir en minuscule
        if (buffer[index] > '@' && buffer[index] < '[') {
            buffer[index] ^= 0x20;  // Convertir en minuscule
        }

        index++;
    }
}
