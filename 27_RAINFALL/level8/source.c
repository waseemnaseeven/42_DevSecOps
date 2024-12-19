#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables globales
char *auth = NULL;
char *service = NULL;

int main(void) {
    char input_buffer[128];
    char temp_buffer[30];
    char service_buffer[125];

    while (1) {

        printf("%p, %p \n", auth, service);


        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            return 0;  
        }


        if (strncmp(input_buffer, "auth ", 5) == 0) {

            auth = malloc(4);
            if (auth == NULL) {
                perror("malloc");
                exit(1);
            }

            memset(auth, '\0', 4);

            // Copie l'entrée utilisateur dans auth (si la longueur est < 30)
            strncpy(temp_buffer, input_buffer + 5, sizeof(temp_buffer) - 1);
            temp_buffer[sizeof(temp_buffer) - 1] = '\0';

            // Vérifie si l'entrée est plus longue que 30 caractères
            if (strlen(temp_buffer) <= 30) {
                strcpy(auth, temp_buffer);  // Copie dans auth
            }
        }

        if (strncmp(input_buffer, "reset", 5) == 0) {
            free(auth);  
            auth = NULL;
        }

        if (strncmp(input_buffer, "service", 7) == 0) {
            strncpy(service_buffer, input_buffer + 8, sizeof(service_buffer) - 1);
            service_buffer[sizeof(service_buffer) - 1] = '\0'; 
            service = strdup(service_buffer); 
        }

        if (strncmp(input_buffer, "login", 5) == 0) {
            
            if (auth != NULL && *(int *)(auth + 32) == 0) {
                system("/bin/sh"); 
            } else if (auth != NULL) {
                fwrite("Password:\n", 1, 10, stdout);
            }
        }
    }

    return 0;
}
