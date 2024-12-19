#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ptrace.h>

int auth(char *login, unsigned int serial) {
    login[strcspn(login, "\n")] = '\0';

    int len = strnlen(login, 0x20); // Longueur maximale autorisée : 32 caractères
    if (len <= 5) {
        return 1; // fail if username is too short
    }

    // Détection de débogage avec ptrace
    if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
        puts("\033[32m.--------------------------.");
        puts("\033[31m| !! TAMPERING DETECTED !! |");
        puts("\033[32m'--------------------------'");
        return 1; // Échec si le programme est en cours de débogage
    }

    // Calcul initial du hash à partir du 4ème caractère du login
    int computed_hash = (login[3] ^ 0x1337) + 0x5eeded;

    // Parcourir chaque caractère du login pour mettre à jour le hash
    for (int i = 0; i < len; i++) {
        // Vérifier si le caractère est imprimable
        if (login[i] <= 0x1f) {
            return 1; 
        }

        // Calcul complexe pour mettre à jour le hash
        int char_hash = login[i] ^ computed_hash;
        int adjustment = (char_hash * 0x88233b2b) >> 32;
        computed_hash += char_hash - (((((char_hash - adjustment) >> 1) + adjustment) >> 10) * 0x539);
    }

    
    if (serial == computed_hash) {
        return 0; // Succès si le hash correspond
    }

    return 1; 
}

int main() {

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");


    char login[32];
    printf("-> Enter Login: ");
    fgets(login, sizeof(login), stdin);


    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");

    // Lecture du numéro de série
    unsigned int serial;
    printf("-> Enter Serial: ");
    scanf("%u", &serial);

    // Appeler la fonction d'authentification
    if (auth(login, serial) == 0) {
        puts("Authenticated!");
        system("/bin/sh"); 
        return 0;
    }

    return 1;
}
