#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int language = 0;

void greetuser(char *username) {
    char greeting[64];

    if (language == 1) {
        
        strncpy(greeting, "Hyvää päivää ", sizeof(greeting));
    } else if (language == 2) {
        // Salutation en néerlandais
        strncpy(greeting, "Goedemiddag! ", sizeof(greeting));
    } else {
        strncpy(greeting, "Hello ", sizeof(greeting));
    }
    
    strcat(greeting, username);

    puts(greeting);
}

int main(int argc, char *argv[]) {
    char buffer[160]; // 0x08048532 <+9>:     sub    $0xa0,%esp
    char *lang;

    if (argc == 3) {
        // 0x08048564: Copy first argument to buffer (max 40 bytes)
        strncpy(buffer, argv[1], 40);

        // 0x08048584: Copy second argument to buffer + 40 (max 32 bytes)
        strncpy(buffer + 40, argv[2], 32);

        // Obtenir la valeur de la variable d'environnement LANG
        lang = getenv("LANG");
        if (lang != NULL) {
            if (strncmp(lang, "fi", 2) == 0) {
                language = 1;
            } else if (strncmp(lang, "nl", 2) == 0) {
                language = 2;
            }
        }
        char* username = buffer;
        greetuser(username);

    } else {
        printf("Usage: %s <arg1> <arg2>\n", argv[0]);
        return 1;
    }

    return 0;
}
